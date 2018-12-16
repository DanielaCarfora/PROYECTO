#include <stdio.h>
#include <stdlib.h>




srand (time(NULL));



///Variables Globales

const int saludMax=50;



typedef struct s_personaje
{
    char nombre [16];
    int ptSalud;
    int ptEnergia;
    PilaInv inventario;
    ListaHab habilidades;
    int danio;
    int rango;
    int armadura;
    int evasion;
    int velocidad;
    int ptAccion;
    int jugador; // jugador al cual pertenece el jugador
}STRUCT_PER;

typedef STRUCT_PER *Personaje;


enum efecto
{
    NINGUNO, ELECTRIFICADO, INCENDIADO, CONGELADO
};

typedef enum efecto Efecto;




typedef struct s_item
{
    char nombre [32];
    int costo;
    int rango;
    void (*efecto)(Terreno*);
}STRUCT_ITE;

typedef STRUCT_ITE *Item;




typedef struct s_terreno
{
    Personaje personaje;
    Efecto efecto;
    ListaIte items;
}STRUCT_TER;

typedef STRUCT_TER *Terreno;


typedef struct  habilidad
{
    char nombre [16];
    int costoEnergia;
    int costoAccion;
    int rango;
    void (*efecto)(Terreno*);
}STRUCT_HAB;

typedef STRUCT_HAB *Habilidad;


///--------------------Funcion para evaluar si se puede aplicar una habilidad
// La funcion retorna cero si el personaje no tiene los puntos de accion o la energia necesaria para usar la habilidad
//retorna uno si se puede usar la habilidad
int Evalhabilidad(Personaje p, Habilidad h)
{
    if(p>ptAccion < h->costoAccion)return 0;
    if(p>ptEnergia < h->costoAccion)return 0;

    return 1;

}


///Para saber si hay un personaje en un terreno del tablero
//Devuelve 1 si hay un personaje Devuelve 0 sino 
int HayPersonaje(Terreno *t){
    return (t->personaje!=NULL)
}



void afectaPersonaje(){
    if (t->efecto == INCENDIADO){
        t->personaje->ptSalud=(t->personaje->ptSalud)*0.70; ///Incendia la casilla objetivo y causa 30% de daño a los puntos de salud ACTUALES
    }

    if (t->efecto == CONGELADO){
        t->personaje->ptAccion=0;               ///Reduce a cero los puntos de acción que tenga el personaje

    }
    if (t->efecto == ELECTRIFICADO){
        if ((t->personaje->ptEnergia)*0.50<=0){
            t->personaje->ptEnergia=1;          ///Los puntos de energía no pueden bajar de 0

        }else{
            t->personaje->ptEnergia=(t->personaje->ptEnergia)*0.50; //elimina el 50% de la cantidad de puntos de energía TOTAL del personaje
        }
        


    }
    /*if (t->efecto == NINGUNO){
        t->personaje->ptSalud=(saludMax*0.30)+(t->personaje->ptSalud); ///Cura el 30% de los puntos de salud del personaje

    }*/
}



void incendiar (Terreno *t)
{
    t->efecto = INCENDIADO; 
    if (HayPersonaje(t)){
        afectaPeronaje(t);
    }
}

void congelar (Terreno *t)
{
    t->efecto = CONGELADO;   
    if (HayPersonaje(*t)){
        afectaPeronaje(*t);
    }
}

void electrocutar(Terreno *t)
{
    t->efecto = ELECTRIFICADO;
    if (HayPersonaje(*t)){
        afectaPeronaje(*t);
    }
}

void restaurar(Terreno *t)
{
    t->efecto = RESTAURAR;	
}


Habilidad create_incendiar(){
    Habilidad h=malloc(sizeof(Habilidad));
    h->nombre = "Incendiar";
    h->costoEnergia = 2;
    h->costoAccion = 7;
    h->rango= 3;
    h->efecto= &incendiar;

    return h;
}

Habilidad create_congelar(){
    Habilidad h=malloc(sizeof(Habilidad));
    h->nombre = "Congelar";
    h->costoEnergia = 4;
    h->costoAccion = 4;
    h->rango= 3;
    h->efecto= &congelar;

    return h;
}

Habilidad create_Electrocutar(){
    Habilidad h=malloc(sizeof(Habilidad));
    h->nombre = "Electrocutar";
    h->costoEnergia = 10;
    h->costoAccion = 5;
    h->rango= 4;
    h->efecto= &electrocutar;

    return h;
}

Habilidad create_Restaurar(){
    Habilidad h=malloc(sizeof(Habilidad));
    h->nombre = "Restaurar";
    h->costoEnergia = 5;
    h->costoAccion = 4;
    h->rango= 2;
    h->efecto= &restaurar;

    return h;
}


///******************************Inicializa un personaje

Personaje NewMago (int jug, int orden){
    //orden tiene el orden el que juega el personaje
    Personaje p=malloc(sizeof(Personaje));
    p->nombre = "Mago";
    p->ptSalud=100;
    p->ptEnergia=50;
    p->inventario=NULL;
    p->habilidades=createListaH();
    p->danio=10;
    p->rango=6;
    p->evasion=50;
    p->jugador=jug;
    p->ptAccion=0;
    p->velocidad=orden;

    return p;
}


///****************************************************************************************
///****************************************************************************************
///****************************************************************************************
///****************************************************************************************
///*****************************Para Atacar************************************************

///Variables Globales

Terreno Tablero [10][20];
int posi, posj;                 ///Variables para maneja el tablero en los ataques



///Realiza el ataque entre dos personajes
//El primer parametro qu recibe es el personaja que esta atacando y el segundo es el que esta siendo atacado

void ataca (Personaje *p1, Personaje *p2){
    
    int dan = p1->danio;

    int evac = p2->evasion; ///Evacion del personaje atacado
    int arm = p2->armadura; ///armadura del personaje atacado


    int n=rand() %100;

    if (n<evasion){
        //Se produce el ataque
        p2->ptSalud=(p2->ptSalud)- (dan-(dan*arm));


    }else{
        //El personaje atacado evade el ataque
        printf("Se evadio el ataque \n");

    }

}


///Funcion para buscar un personaje en el tablero
void BuscarEnT(Personaje p){
    for(int i=0; i<10; i++){
        for(int j=0; j<20; j++){
            if(Tablero[i][j]->personaje==p){
                posi=i;
                posj=j;

            }
        }
    }

}

int ConvertirLetra(char a){
    if(a=='A'){
        return 0;
    }
    if(a=='B'){
        return 1;
    }
    if(a=='C'){
        return 2;
    }
    if(a=='D'){
        return 3;
    }
    if(a=='E'){
        return 4;
    }
    if(a=='F'){
        return 5;
    }
    if(a=='G'){
        return 6;
    }
    if(a=='H'){
        return 7;
    }
    if(a=='I'){
        return 8;
    }
    if(a=='J'){
        return 9;
    }


}




void atacar (Personaje *p){

    BuscarEnT(p);
    mostrarTablero();
    char a;
    int i;
    int j;
    printf("Elija el personaje que quiere atacar \n");
    printf("Ingrese sus coordenadas (Ejemplo :A1 -Columna: A Fila :1)\n");
    printf("Ingrese su Columna\n");
    scanf("%c", &a);
    printf("Ingrese su Fila\n");
    scanf("%d", &i);
    
    j= ConvertirLetra(a);

    if (Tablero[j][i]->personaje==NULL){
        printf("No hay personaje en ese terreno \n");

    }











}


