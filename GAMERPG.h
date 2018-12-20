#ifndef _GAMERPG_H_
#define _GAMERPG_H_

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

///Variables Globales

Terreno Tablero [10][20];
int posi, posj;                 ///Variables para maneja el tablero en los ataques

typedef struct s_personaje STRUCT_PER;
typedef STRUCT_PER *Personaje;

typedef struct  s_habilidad STRUCT_HAB;
typedef STRUCT_HAB *Habilidad;

typedef struct s_item STRUCT_ITE;
typedef STRUCT_ITE *Item;

typedef struct s_terreno STRUCT_TER;
typedef STRUCT_TER *Terreno;

typedef struct nodo_lhab NODO_LHAB;
typedef NODO_LHAB *ListaHab;

typedef struct nodo_lite NODO_LITE;
typedef NODO_LITE *ListaIte;

typedef struct nodo_pinv NODO_PINV;
typedef NODO_PINV *PilaInv;

void push(PilaInv *P, Item item);
Item pop(PilaInv *P);

void insertar_hab(ListaHab *L, Habilidad habilidad);
void mostrar_hab(ListaHab *L);



//-----------------------------------------------------------------------------------------

//############################ Estructuras de los TAD's ###################################

typedef struct s_personaje
{
	char nombre [16];
	int ptSalud;
	int ptEnergia;
	PilaInv inventario;
	ListaHab habilidades;
	int danio;
	int rango;
	int armadura; // de 0 a 100
	int evasion; // de 0 a 100
	int velocidad;
	int ptAccion;
	int jugador; // jugador al cual pertenece el jugador
	char inicial; // inicial del nombre a mostrar en el tablero
}STRUCT_PER;

typedef STRUCT_PER *Personaje;



typedef struct  s_habilidad
{
	char nombre [16];
	int costoEnergia;
	int costoAccion;
	int rango;
	void (*efecto)(Terreno*);
}STRUCT_HAB;

typedef STRUCT_HAB *Habilidad;

typedef struct s_item
{
	char nombre [32];
	int costo;
	int rango;
	void (*efecto)(Terreno*);
}STRUCT_ITE;

typedef STRUCT_ITE *Item;

enum efecto
{
	NINGUNO, ELECTRIFICADO, INCENDIADO, CONGELADO
};

typedef enum efecto Efecto;

typedef struct s_terreno
{
	Personaje personaje;
	Efecto efecto;
	ListaIte items;
}STRUCT_TER;

typedef STRUCT_TER *Terreno;


typedef struct turno {
    int pi;     //Posicion en filas del personaje
    int pj;     //Posicion en columnas del personaje
    int velocity;   //Velocidad del personaje;
    struct turnos *tnext;


}Turno;

typedef Turno *Turnos;


//############################ Fin estructuras de los TAD's ###############################

//-----------------------------------------------------------------------------------------

////########################## Manejo de colas ############################################

typedef struct nodo{
    Personaje per;
    struct nodo *sig;
} Nodo;

typedef struct col{
    Nodo *alfa;
    Nodo *omega;
    int size;
} Col;

typedef Col* Cola;

Cola newCola(){
    Cola c= malloc(sizeof(Col));
    c->alfa=NULL;
    c->omega=NULL;
    c->size= 0;
}

int esVacia(Cola c){return(c->alfa==NULL && c->omega==NULL);}

Personaje first(Cola c){return((c->alfa)->per);}

void queue(Personaje x, Cola c){
    Nodo *q=malloc(sizeof(Nodo));
    q->per=x;
    q->sig=NULL;
    if(c->alfa==NULL) c->alfa=q;
    else (c->omega)->sig=q;
    c->omega=q;
    (c->size)++;
}
void dqueue(Cola c){
    Nodo *q=c->alfa;
    if(c->alfa==c->omega) c->omega=NULL;
    c->alfa=q->sig;
    free(q);
    (c->size)--;
}

///########################### Fin manejo de colas ########################################

/// --------------------------------------------------------------------------------------

////########################## Manejo de las listas #######################################

typedef struct nodo_lhab{

	Habilidad habilidad;
	struct nodo_lhab *sig;
}NODO_LHAB;

typedef NODO_LHAB *ListaHab;

typedef struct nodo_lite
{
	Item items;
	struct nodo_lite *sig;
}NODO_LITE;

typedef NODO_LITE *ListaIte;


////########################## Fin manejo de las listas ###################################

//-----------------------------------------------------------------------------------------

////########################## Operaciones de listas ######################################

ListaHab newListaH(){
    return NULL;
}

void insertar_hab(ListaHab *L, Habilidad habilidad){ // revisa si funciona Mariana

	 NODO_LHAB *q = malloc(sizeof(NODO_LHAB));
	 q->habilidad = habilidad;
     q->sig = *L;
     *L = q;
}

void mostrar_hab(ListaHab *L){

    NODO_LHAB *q = *L; // q es un apuntador a NODO_LHAB, apunta al inicio de la Lista

    if(q==NULL){
        printf("\nNo posee habilidades\n");
    }else{

        printf("Habilidades:\n\n");

        while (q!=NULL){
            printf("%s\n",q->habilidad->nombre);
            printf("Costo de energia: %d\n",q->habilidad->costoEnergia);
            printf("Costo de accion: %d\n",q->habilidad->costoAccion);
            printf("Rango: %d\n",q->habilidad->rango);
            printf("\n");

            q= q->sig;
        }
    }
}

void mostrar_ite(ListaIte *L){

    NODO_LITE *q = *L; // q es un apuntador a NODO_LHAB, apunta al inicio de la Lista

    if(q==NULL){
        printf("\nNo posee items\n");
    }else{

        printf("Items:\n\n");

        while (q!=NULL){
            printf("%s\n",q->items->nombre);
            printf("Costo: %d\n",q->items->costo);
            printf("Rango: %d\n",q->items->rango);
            printf("\n");

            q= q->sig;
        }
    }
}

void insertar_ite(ListaIte*L, Item ite){ // Iserta Item en el terreno
	NODO_LITE *q = *L; // q es un apuntador a NODO_LITE, apunta al inicio de la Lista
	q->Items = ite;
    q->sig = *L;
    *L = q;

}
////########################## Fin de Operaciones de listas ###############################

//-----------------------------------------------------------------------------------------

////########################## Manejo de pilas ############################################

typedef struct nodo_pinv
{
	Item items;
	struct nodo_pinv *sig;
}NODO_PINV;

typedef NODO_PINV *PilaInv;

////########################## Fin de manejo de pilas #####################################

//-----------------------------------------------------------------------------------------

////########################## Operaciones de pilas #######################################

PilaInv newPilaInv(){
    return NULL;
}

void push(PilaInv *p, Item item){

	//crear un nuevo nodo
	NODO_PINV *q = malloc(sizeof(NODO_PINV));
	q->items = item;

	//agregamos la pila a continuacion del nuevo nodo
	q->sig = *p;

	//El comienzo de la pila es el nuevo nodo
	*p = q;
}

Item pop(PilaInv *p){

    if (p==NULL) return 0;
	NODO_PINV *q = *p; //Variable auxiliar para manipular el nodo. Apunta al primero.
    Item item; //variable auxiliar para retornar el item

    *p = (*p)->sig;
    item = q->items;
    free(q);


    return item; // falta agregarlo al terreno actual

}

Item top(PilaInv *P){
    return p->items;
}

////########################## Fin de Operaciones de pilas ################################

//-----------------------------------------------------------------------------------------

//############################ Primittivas del TAD ########################################

Personaje NewMago (int jug, int turno){
    //orden tiene el orden el que juega el personaje
    Personaje p=malloc(sizeof(Personaje));
    strcpy(p->nombre, "Mago");
    p->ptSalud=100;
    p->ptEnergia=50;
    p->inventario= newPilaInv();
    p->habilidades= newListaH();
    p->danio=10;
    p->rango=6;
    p->evasion=50;
    p->jugador=jug;
    p->ptAccion=0;
    p->velocidad= turno;
    p->inicial='M';

    return p;
}

Personaje NewSoldado (int jug, int turno){
    //orden tiene el orden el que juega el personaje
    Personaje p=malloc(sizeof(Personaje));
    strcpy(p->nombre = "Soldado");
    p->ptSalud=100;
    p->ptEnergia=70;
    p->inventario= newPilaInv();
    p->habilidades=newListaH();
    p->danio=20;
    p->rango=4;
    p->evasion=60;
    p->jugador=jug;
    p->ptAccion=0;
    p->velocidad= turno;
    p->inicial='S';

    return p;
}

Personaje NewArquero (int jug, int turno){
    //orden tiene el orden el que juega el personaje
    Personaje p=malloc(sizeof(Personaje));
    strcpy(p->nombre = "Arquero");
    p->ptSalud=100;
    p->ptEnergia=40;
    p->inventario= newPilaInv;
    p->habilidades= newListaH();
    p->danio=20;
    p->rango=10;
    p->evasion=30;
    p->jugador=jug;
    p->ptAccion=0;
    p->velocidad= turno;
    p->inicial='A';

    return p;
}

Personaje NewDuende (int jug, int turno){
    //orden tiene el orden el que juega el personaje
    Personaje p=malloc(sizeof(Personaje));
    strcpy(p->nombre = "Duende");
    p->ptSalud=100;
    p->ptEnergia=60;
    p->inventario= newPilaInv;
    p->habilidades=newListaH();
    p->danio=10;
    p->rango=4;
    p->evasion=80;
    p->jugador=jug;
    p->ptAccion=0;
    p->velocidad= turno;
    p->inicial='D';

    return p;
}

//############################ Fin primittivas del TAD ####################################

//-----------------------------------------------------------------------------------------


//############################ Operaciones sobre TAD


/*
Personaje selectPersonaje(int ttt){
int n1;
printf("1. Mago\n2.Soldado\n3.Arquero\n4.Duende\n");
printf("Selecione el numero de su personaje:\n");
scanf("%d",n1);
switch(n1){
        case 1: Personaje p1 = NewMago(1,ttt);
        case 2: Personaje p1 = NewSoldado(1,ttt);
        case 3: Personaje p1 = NewArquero(1,ttt);
        case 4: Personaje p1 = NewDuende(1,ttt);
}

return p1;

}
*/


void selectPersonajes(personajes){
    int n1,s1;
    Personaje *p1, *p2, *p3, *p4;
    printf("1. Mago\n2.Soldado\n3.Arquero\n4.Duende\n");
    printf("Jugador 1\n");
    printf("Selecione el numero de su primer personaje:\n");
    scanf("%d",n1);
    printf("Selecione el numero de su segundo personaje:\n");
    scanf("%d",s1);
    switch(n1){
        case 1: p1 = NewMago(1,1);
        case 2: p1 = NewSoldado(1,1);
        case 3: p1 = NewArquero(1,1);
        case 4: p1 = NewDuende(1,1);
}


    switch(s1){
        case 1: p2 = NewMago(1,3);
        case 2: p2 = NewSoldado(1,3);
        case 3: p2 = NewArquero(1,3);
        case 4: p2 = NewDuende(1,3);
}


    printf("Personajes del jugador 1 creados exitosamente\n");
    printf("1. Mago\n2.Soldado\n3.Arquero\n4.Duende\n");
    printf("Su turno jugador 2...\n Selecion el numero se primer personaje:\n");
    scanf("%d",n2);
    printf("Selecione el numero de su segundo personaje:\n");
    scanf("%d",s2);
    switch(n2){
        case 1: p3 = NewMago(2,2);
        case 2: p3 = NewSoldado(2,2);
        case 3: p3 = NewArquero(2,2);
        case 4: p3 = NewDuende(2,2);
}


    switch(s2){
        case 1: p4 = NewMago(2,4);
        case 2: p4 = NewSoldado(2,4);
        case 3: p4 = NewArquero(2,4);
        case 4: p4 = NewDuende(2,4);
}

queue(p1, personajes);
queue(p3, personajes);
queue(p2, personajes);
queue(p4, personajes);



    return 0;
}

void MostrarTablero(){
    Terreno Tablero[10][20];
    for(int i=0; i<10; i++){
        for(int j=0; j<20; j++){
                if(Tablero[i][j]->efecto!=NINGUNO) Tablero[i][j]=178;
                if(Tablero[i][j]->personaje!=NULL) Tablero[i][j]= Personaje->inicial;
                if(Tablero[i][j]->items!=NULL) Tablero[i][j]= '*';
                else Tablero[i][j]=176;
            printf("%c",Tablero[i][j]);
        } printf("\n");
    }
}

void busquedaItem(PilaInv*p, ListaIte*a, item ite){ // Recibe el Item a buscar, la pila de inventario y la lista del terreno.
	while(p!=NULL && ite != p->items){
		Item b=pop(&p);
		insertar_ite(&a,b)
	}
	return 0;
}

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
int HayPersonaje(Terreno t){
    return (t->personaje!=NULL)
}



void afectaPersonaje(Terreno t){
    if (HayPersonaje(t)){
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
}
    /*if (t->efecto == NINGUNO){
        t->personaje->ptSalud=(saludMax*0.30)+(t->personaje->ptSalud); ///Cura el 30% de los puntos de salud del personaje
    }*/
}

void incendiar (Terreno t)
{
    t->efecto = INCENDIADO;
        afectaPeronaje(t);
}

void congelar (Terreno t)
{
    t->efecto = CONGELADO;
        afectaPeronaje(t);
}

void electrocutar(Terreno t)
{
    t->efecto = ELECTRIFICADO;
        afectaPeronaje(t);
}

void restaurar(Terreno t) // TERMINAR
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

///****************************************************************************************
///****************************************************************************************
///****************************************************************************************
///****************************************************************************************
///*****************************Para Atacar************************************************


///Realiza el ataque entre dos personajes
//El primer parametro que recibe es el personaje que esta atacando y el segundo es el que esta siendo atacado

void ataca (Personaje p1, Personaje p2){

    int dan = p1->danio;

    int evac = p2->evasion; ///Evacion del personaje atacado
    int arm = p2->armadura; ///armadura del personaje atacado
	p1->ptAccion=p1->ptAccion-2;

    int n=rand() %100;

    if (n>p2->evasion){
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
    return a - 65;
}



int FueraDRango(Personaje p, int j, int i ){
    BuscarEnT(p);
    int rang=p->rango;
    int k, l;

    for(k=posi-rang; k<=posi+rang; k++){

    if(((j<=posj+rang )&&(j>posj))|| (j>=posj-rang &&(j<posj))){
           /* if(((i<=posi+rang )&&(i>posi))|| (i>=posi-rang &&(i<posi))){
                return 0;
                    if(){
                    }else{
                    }
            */
            return 0;
    }
    else{
            return 1;
        }

    }
}


void EliminaPersonaje (Personaje p){
    free(p);/// AGREGAR AL SUELO ITEMS

}

void EvaluaPersonaje(Personaje p){
    if(p->ptSalud<=0){
        BuscarEnT(p);
        Tablero [posi][posj] ->personaje==NULL;
        EliminaPersonaje(Personaje *p);
    }else{
        return;


    }



}


int PuedeAtacar(Personaje p){
    if(p->ptAccion<2){
        return 0;

    }else{
        return 1;
    }

}



void atacar (Personaje p){

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

    if (Tablero[i][j]->personaje==NULL){
        printf("No hay personaje en ese terreno \n");

    }else{
        if(FueraDRango(Personaje p, j, i)){
            printf("El personaje que se quiere atacar esta fuera de rango \n");

        }else{
            if(PuedeAtacar(p)){
                ataca(p, Tablero[i][j]->personaje);
                EvaluaPersonaje(p);

            }else{
                printf("El personaje con el que se quiere atacar NO tiene los suficientes puntos de accion \n");

            }


        }

    }

}

void consultarCasilla(){
    int i,j;
    printf("Ingrese las coordenadas del terreno a consultar:");
    scanf("%d,%d",&i,&j);
    printf("Terreno:\n");
    switch (Tablero[i][j]->efecto){
        case 0 :
            printf("NINGUNO");
            break;
        case 1 :
            printf("ELECTRIFICADO");
            break;
        case 2 :
            printf("INCENDIADO");
            break;
        case 3 :
            printf("CONGELADO");
            break;
               }
        if(HayPersonaje(Tablero[i][j])) printf(%c, (Tablero[i][j]->personaje)->nombre); // FUNCION IMPRIMIR DATOS PERSONAJE
        if(Tablero[i][j]->items!=NULL)mostrar_ite(Tablero[i][j]->items);
}


void EscribeOrigen(int *oi,int *oj){
    printf("Origen\n"
           "Escoge la pieza:\n");

    do{
        printf("Fila: ");
        scanf("%d",oi);
    }while(*oi<0 || *oi>7);

    do{
        printf("\n Columna: ");   // elige columna
        scanf("%d",oj);
    } while(*oj<0 || *oj>7);
}

void EscribeDestino(int *di,int *dj){
    printf("\nDestino\n");

    do{
        printf("\nEscoge el destino:\nFila: ");   // elige fila
        scanf("%d",di);
    }while(*di<0 || *di>7);

    do{
        printf("\nColumna: ");   // elige Columna
        scanf("%d",dj);
    }while(*dj<0 || *dj>7);
}

int ConfirmaOrigen(int i,int j,Terreno Tablero[10][20]) {///por lo que dice abajo se tiene que cambiar esta funcion y que reciba o el jugador o el personaje->jugador
     if(Tablero[i][j]->personaje!=NULL)return 1; ///falta poner una condicion de si ese jugador pertenece al jugado
     else{ printf("\nNo hay personaje en esa posicion o es otro jugador\n"); return 0;
     }
}

int ConfirmaDestino(int *oi,int *oj,int *di, int *dj, Terreno Tablero[10][20]) {
     if(oj+1==dj || oj-1==dj){
        if(oi+1==di || oi-1==di)return 1;
     }else return 0;
}




//Inserta los turnos de mayor a menor
// Turnos *T DEBE ser variable global??????????????

void insertOrdturnos (int ppi, int ppj, int vv, , Turnos *T){
    turnos *p =malloc(sizeof(turno)), *q;
    p->velocity=vv;
    p->pi=ppi;
    p->pj=ppj;
    if(*T==NULL || x>(*T)->velocity){
        p->tnext=*T;
        *T=p;
    }else{
        q=*T;
        while(q->tnext!=NULL && x<(q->tnext)->velocity) q=q->tnext;
        p->tnext=q->tnext; q->tnext=p;


    }

}


//Busca en el tablero los personajes para asignarles un turno

void BuscarTurnos (Turnos *T){
    *T=NULL;

    for(int i=0; i<10; i++){
        for(int j=0; j<20; j++){
            if(Tablero[i][j]->personaje!=NULL){
                insertOrdturnos(i, j,(Tablero[i][j]->personaje)->velocity);


            }
        }
    }




}

void elegirHabilidad(){
    int h; // alamacena el numero de la habiliad escogida por el usuario
    printf("Ingrese el numero de la habilidad deseada:\n1.Incendiar\n2.Congelar\n3.Electrocutar\n4.Restaurar");
    scanf("%d",h);
    switch(h){
        case 1: 
            Evalhabilidad();
            break;
        case 2: 
            Evalhabilidad();
            break;
        case 3:
            Evalhabilidad();
            break;
        case 4:
            Evalhabilidad();
            break;

    }
}

//############################ Fin operaciones  del TAD ###################################


//-----------------------------------------------------------------------------------------

#endif

