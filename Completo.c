#include <stdlib.h>
#include <string.h>
#include <stdio.h>

///Variables Globales

const int saludMax= 100;
const int ptEnergiaMag= 50;

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

typedef struct nodo Nodo;

typedef struct col Col;

typedef Col* Cola;

PilaInv newPilaInv();
void push(PilaInv *p, Item item);
Item pop(PilaInv *p);
Item top(PilaInv p);


void insertar_hab(ListaHab *L, Habilidad habilidad);
void mostrar_hab(ListaHab *L);
Cola newCola();
int esVacia(Cola c);
Personaje first(Cola c);
void queue(Personaje x, Cola c);
void dqueue(Cola c);
ListaHab newListaH();
void insertar_hab(ListaHab *L, Habilidad habilidad);
void mostrar_hab(ListaHab *L);
Item estaEn(ListaIte*L, int n);
void mostarItem(Personaje p);
void mostrar_ite(ListaIte *L);
void insertarItemT(Personaje p, Item ite, int i, int j);
void insertarItem(Personaje p, Item ite);

void insertar_ite(ListaIte*L, Item ite);
void eliminar_ite(ListaIte*L, Item ite);
void moverItem(Personaje p);

Personaje NewMago (int jug, int turno);
Personaje NewSoldado (int jug, int turno);
Personaje NewArquero (int jug, int turno);
Personaje NewDuende (int jug, int turno);
void SumarAccion(Personaje p);
void MostrarTablero();
void newTerreno();
void BuscarEnT(Personaje p);
int ConvertirLetra(char a);
int FueraDRango(Personaje p, int j, int i );
void ShowCPersonaje(Personaje p);
void consultarCasilla();
void MoverenTablero(Personaje p);
void selectPersonajes(Cola personajes);

Habilidad create_incendiar();
Habilidad create_congelar();
Habilidad create_Restaurar();
Habilidad create_Electrocutar();




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
	NINGUNO, ELECTRIFICADO, INCENDIADO, CONGELADO, RESTAURAR
};

typedef enum efecto Efecto;



typedef struct s_terreno
{
	Personaje personaje;
	Efecto efecto;
	ListaIte items;
}STRUCT_TER;

typedef STRUCT_TER *Terreno;

Terreno Tablero[10][20];

//############################ Fin estructuras de los TAD's ###############################

//-----------------------------------------------------------------------------------------

////########################## Manejo de colas ############################################

typedef struct nodo{ // Cola de personajes para controlar turnos
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

    return c;
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
////########################## Manejo de pilas ############################################

typedef struct nodo_pinv // Inventario del personaje
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

Item pop(PilaInv *p){ // Elimina del inventario del personaje

    if (p==NULL) return 0;
	NODO_PINV *q = *p; //Variable auxiliar para manipular el nodo. Apunta al primero.
    Item item; //variable auxiliar para retornar el item

    *p = (*p)->sig;
    item = q->items;
    free(q);


    return item; // falta agregarlo al terreno actual

}

Item top(PilaInv p){
    return p->items;
}

////########################## Fin de Operaciones de pilas ################################
//-----------------------------------------------------------------------------------------


////########################## Operaciones de listas ######################################

ListaHab newListaH(){
    return NULL;
}


void insertar_hab(ListaHab *L, Habilidad habilidad){

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

Item estaEn(ListaIte*L,int n){
    NODO_LITE *q = *L; // q es un apuntador a NODO_LITE, apunta al inicio de la Lista
    int j=1; // contador para el numero de item deseado
    Item ite = q->items;
    while(q != NULL && j!=n){
        q = q->sig;
        j++;
        ite = q->items;
    }
    if (q != NULL) return ite;
    else return 0;
}


void mostarItem(Personaje p){ // Funcion auxiliar para mostrar items.
    BuscarEnT(p);
    mostrar_ite(&(Tablero[posi][posj]->items));
}

void mostrar_ite(ListaIte *L){

    NODO_LITE *q = *L; // q es un apuntador a NODO_LHAB, apunta al inicio de la Lista

    if(q==NULL){
        printf("\nNo posee items\n");
    }else{

        printf("Items:\n\n");

        int n=1; // contador para el numero de items

        while (q!=NULL){
            printf("%d. %s\n",n,q->items->nombre);
            printf("Costo: %d\n",q->items->costo);
            printf("Rango: %d\n",q->items->rango);
            printf("\n");

            q= q->sig;
            n++;
        }
    }
}

void insertarItemT(Personaje p, Item ite, int i, int j){ // Funcion auxiliar para insertar item en el terreno deseado
    insertar_ite((&(Tablero[i][j])->items),ite);
}

void insertarItem(Personaje p, Item ite){ // Funcion auxiliar para insertar item en el terreno actual
    BuscarEnT(p);
    insertar_ite((&(Tablero[posi][posj])->items),ite);
}

void insertar_ite(ListaIte*L, Item ite){ // Iserta Item en el terreno
	NODO_LITE *q = *L; // q es un apuntador a NODO_LITE, apunta al inicio de la Lista
	q->items = ite;
    q->sig = *L;
    *L = q;

}

void eliminar_ite(ListaIte*L, Item ite){ // Elimina la primera ocurrencia del item de la lista L
    NODO_LITE *p = *L, *q; // p es un apuntador a NODO_LITE, apunta al inicio de la Lista
    if (p != NULL){
        if (p->items == ite){
            *L = p->sig;
            free(p);
    }
        else {
            while (p->sig != NULL && (p->sig)->items != ite) p = p->sig;
            if (p->sig != NULL) {
                q = p->sig;
                p->sig = q->sig;
                free(q);
            }
        }
    }
}

void moverItem(Personaje p){
    mostarItem(p);
    int i;
    printf("indique el numero de item deseado:");
    scanf("%d", &i);
    BuscarEnT(p);
    Item ite = estaEn(&((Tablero[posi][posj])->items),i);
    if (&ite!=NULL){
        push(&(p->inventario),ite);
        eliminar_ite((&(Tablero[posi][posj])->items),ite);
    }
}
////########################## Fin de Operaciones de listas ###############################

//-----------------------------------------------------------------------------------------



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
    strcpy(p->nombre, "Soldado");
    p->ptSalud=100;
    p->ptEnergia=50;
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
    strcpy(p->nombre, "Arquero");
    p->ptSalud=100;
    p->ptEnergia=50;
    p->inventario= newPilaInv();
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
    strcpy(p->nombre,"Duende");
    p->ptSalud=100;
    p->ptEnergia=50;
    p->inventario= newPilaInv();
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


//############################ Operaciones sobre TAD #####################################

void SumarAccion(Personaje p){ // Al inicio de cada turno se suman 5 puntos de accion
    p->ptAccion= p->ptAccion+5;


}

///---------------------------------TERRENO------------------------------------///

Terreno Tablero [10][20];


void MostrarTablero(){
    char Taa[10][20];

    for(int i=0; i<10; i++){
        for(int j=0; j<20; j++){
                if(Tablero[i][j]->efecto!=NINGUNO) Taa[i][j]= 178;
                if(Tablero[i][j]->personaje!=NULL) Taa[i][j]= Tablero[i][j]->personaje->inicial;
                if(Tablero[i][j]->items!=NULL) Taa[i][j]= '*';
                else Taa[i][j]=176;
            printf("%c",Taa[i][j]);
        } printf("\n");
    }
}



void newTerreno(){

    for(int i=0; i<10; i++){
        for(int j=0; j<20; j++){
            Tablero[i][j]=NULL;
        }
    }

}
///---------------------------------------------------------------------------------------------
///---------------------------------------------------------------------------------------------
///---------------------------------------------------------------------------------------------
///---------------------------------------------------------------------------------------------

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


int HayPersonaje(Terreno t){
    return (t->personaje!=NULL);
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
        if(HayPersonaje(Tablero[i][j])) ShowCPersonaje(Tablero[i][j]->personaje); // FUNCION IMPRIMIR DATOS PERSONAJE
        if(Tablero[i][j]->items!=NULL)mostrar_ite(&(Tablero[i][j]->items));
}

void MoverenTablero(Personaje p){
    int newi, newj;
    char a;
    MostrarTablero();


    printf("Ingrese la posicion a donde se quiere mover (Ejemplo :A1 -Columna: A Fila :1) \n");

    printf("Ingresa la columna \n");
    scanf("%c", &a);
    printf("Ingresa la fila \n");
    scanf("%d", &newi);

    newj= ConvertirLetra(a);

    if(FueraDRango(p, newj, newi)){
        //La funcion fueraDrango llama a busca tablero y establece la posicion del personaje en las variables globales posi y posj
        printf("El movimento esta fuera del rango del personaje \n");

    }else{
        Tablero[newi][newj]->personaje= p;
        Tablero[posi][posj]->personaje=NULL;
    }
}
///--------------------------------------PERSONAJES------------------------------------///

void ShowCPersonaje(Personaje p){ // Imprime personaje
    printf("\nNombre: %s"
           "\nPuntos de Salud: %d"
           "\nPuntos de Energia: %d"
           "\nDanio: %d"
           "\nRango: %d"
           "\nArmadura: %d"
           "\nEvasion: %d"
           "\nVelocidad: %d"
           "\nPuntos de Accion: %d"
           "\nJugador: %d \n"
           ,p->nombre, p->ptSalud, p->ptEnergia, p->danio, p->rango, p->armadura, p->evasion, p->velocidad, p->ptAccion, p->jugador);
 }


void selectPersonajes(Cola personajes){
    int n1,s1,n2,s2;
    Personaje p1, p2, p3, p4;
    printf("Personajes disponibles\n");
    printf("1.Mago\n2.Soldado\n3.Arquero\n4.Duende\n\n");
    printf("Jugador 1...\n");
    printf("Selecione el numero de su primer personaje:\n");
    scanf("%d",&n1);
    printf("Selecione el numero de su segundo personaje:\n");
    scanf("%d",&s1);
    switch(n1){
        case 1:
            p1 = NewMago(1,1);
            //MagoH(p1);
            break;
        case 2:
            p1 = NewSoldado(1,1);
            //SoldadoH(p1);
            break;
        case 3:
            p1 = NewArquero(1,1);
            //ArqueroH(p1);
            break;
        case 4:
            p1 = NewDuende(1,1);
            //DuendeH(p1);
            break;
        default:
            printf("Numero de personaje invalido, se elegira aleatoriamente" );
            p1 = NewDuende(1,1);
            break;

    }


    switch(s1){
        case 1:
            p2 = NewMago(1,3);
            //MagoH(p2);
            break;
        case 2:
            p2 = NewSoldado(1,3);
            //SoldadoH(p2);
            break;
        case 3:
            p2 = NewArquero(1,3);
            //ArqueroH(p2);
            break;
        case 4:
            p2 = NewDuende(1,3);
            //DuendeH(p2);
            break;
        default:
            printf("Numero de personaje invalido, se elegira aleatoriamente" );
            p2 = NewArquero(1,3);
            break;
    }


    printf("\nPersonajes del jugador 1 creados exitosamente\n");
    printf("1. Mago\n2.Soldado\n3.Arquero\n4.Duende\n");
    printf("\nSu turno jugador 2...\n Selecion el numero del primer personaje:\n");
    scanf("%d",&n2);
    printf("Selecione el numero de su segundo personaje:\n");
    scanf("%d",&s2);
    switch(n2){
        case 1:
            p3 = NewMago(2,2);
            //MagoH(p3);
            break;
        case 2:
            p3 = NewSoldado(2,2);
            //SoldadoH(p3);
            break;
        case 3:
            p3 = NewArquero(2,2);
            //ArqueroH(p3);
            break;
        case 4:
            p3 = NewDuende(2,2);
            //DuendeH(p3);
            break;
        default:
            printf("Numero de personaje invalido, se elegira aleatoriamente" );
            p3 = NewSoldado(2,2);
            break;
    }


    switch(s2){
        case 1:
            p4 = NewMago(2,4);
            //MagoH(p4);
            break;
        case 2:
            p4 = NewSoldado(2,4);
            //SoldadoH(p4);
            break;
        case 3:
            p4 = NewArquero(2,4);
            //ArqueroH(p4);
            break;
        case 4:
            p4 = NewDuende(2,4);
            //DuendeH(p4);
            break;
        default:
            printf("Numero de personaje invalido, se elegira aleatoriamente" );
            p4 = NewMago(2,4);
            break;
    }
    
    queue(p1, personajes);
    queue(p3, personajes);
    queue(p2, personajes);
    queue(p4, personajes);


}



///Para saber si hay un personaje en un terreno del tablero
//Devuelve 1 si hay un personaje Devuelve 0 sino



int EvaluaPersonaje(Personaje per){
    return (per->ptSalud<=0);

}

void EliminaPersonaje(Personaje per){
    Terreno t[10][20];
    if (EvaluaPersonaje(per)){
        Item ite = top(per->inventario);
        while(ite!=NULL){  /// AGREGAR AL SUELO ITEMS
            BuscarEnT(per);
            insertar_ite(&(t[posi][posj]->items),ite); // agrega al suelo
            pop(&(per->inventario)); // elimina del inventario del personaje
            ite = top(per->inventario);
        }
        t[posi][posj]->personaje = NULL;
        free(per);
	}

}
///-------------------------------------------------------ITEMS----------------------------------///
void pSalud(Terreno t){
    if((t)->personaje->ptAccion>=3){
        (t)->personaje->ptSalud= (t)->personaje->ptSalud+(saludMax*0.30);
        (t)->personaje->ptAccion=((t)->personaje->ptAccion)-3;
        if((t)->personaje->ptSalud>100){
            (t)->personaje->ptSalud=100;
        }


    }else{
        printf("El personaje no tiene suficientes puntos de acccion \n");


    }


}



void pEnergia(Terreno t){
    if((t)->personaje->ptAccion>=3){
        (t)->personaje->ptEnergia=(t)->personaje->ptEnergia +(ptEnergiaMag*0.30); /// se quito un +
        (t)->personaje->ptAccion=((t)->personaje->ptAccion)-3;
        if((t)->personaje->ptEnergia>50){
            (t)->personaje->ptEnergia=50;
        }


    }else{
        printf("El personaje no tiene suficientes puntos de acccion \n");


    }
}

void gnul(Terreno t){
    if((t)->personaje->ptAccion>=5){

        for(int i=0; i<10; i++){
            for(int j=0; j<20; j++){
                if(Tablero[i][j]==(t)){
                    posi=i;
                    posj=j;

                }
            }
        }

        for(int i=posi-1; i<posi+2; i++ ){
            for(int j=posj-1; j<posj+2; j++){
                Tablero[i][j]->efecto=NINGUNO;
            }
        }


    }else{
        printf("El personaje no tiene suficientes puntos de acccion \n");


    }
}


Item create_psalud(Terreno t){
    Item ite = malloc(sizeof(Item));
    strcpy(ite->nombre, "PosionSalud");
    ite->costo = 3;
    ite->rango = 0;
    ite->efecto= pSalud;

    return ite;
}

Item create_penergia(Terreno t){
    Item ite = malloc(sizeof(Item));
    strcpy(ite->nombre, "PosionEnergia");
    ite->costo = 3;
    ite->rango = 0;
    ite->efecto= pEnergia;

    return ite;
}

Item create_gnul(Terreno t){
    Item ite = malloc(sizeof(Item));
    strcpy(ite->nombre, "GranadaNulificadora");
    ite->costo = 5;
    ite->rango = 5;
    ite->efecto =gnul;

    return ite;
}



void busquedaItems(Personaje p){
    int y,i,j;
    do{
        printf("\nEl item disponible es:");
        Item ite=top(p->inventario);
        puts(ite->nombre);
        printf("Elija la accion a tomar:");
        printf("\n1)Siguiente item \n2)Usar \n 3)Salir");
        scanf("%d",&y);
        switch(y){
            case 1:{
                insertarItem(p,ite); // Inserto Item al terreno
                pop(&(p->inventario)); // Elimino item del inventario del personaje
                break;
            case 2:
                printf("\nIngrese coordenadas del tablero para usar item:" );
                scanf("%d %d",&i,&j);
                insertarItemT(p,ite,i,j);
                pop(&(p->inventario));
                break;
            case 3:
                break; // Rregresa al menu anterior
            }
        }
    }while(p->inventario!=NULL);
}

void usarItem(Personaje per){
    int i;
    printf("Ingrese el numero del item deseado:\n1.PosionSalud\n2.PosionEnergia\n3.GranadaNulificadora\n");
    scanf("%d",&i);
    BuscarEnT(per);
    switch(i){
        case 1:
            pSalud(&(Tablero[posi][posj]));
            break;
        case 2:
            pEnergia(&(Tablero[posi][posj]));
            break;
        case 3:
            gnul(&(Tablero[posi][posj]));
            break;
    }
}



///---------------------------------HABILIDADES--------------------------------------///

//Funcion para evaluar si se puede aplicar una habilidad
// La funcion retorna cero si el personaje no tiene los puntos de accion o la energia necesaria para usar la habilidad
//retorna uno si se puede usar la habilidad

int Evalhabilidad(Personaje p, Habilidad h)
{
    if(p->ptAccion < h->costoAccion)return 0;
    if(p->ptEnergia < h->costoAccion)return 0;

    return 1;

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
        if(t->efecto == RESTAURAR){
            t->personaje->ptSalud= t->personaje->ptSalud + (saludMax *0.30);
            if(t->personaje->ptSalud>100){
                t->personaje->ptSalud=100;
            }
        t->efecto=NINGUNO;

        }

        }
    }
}


void incendiar (Terreno t)
{
    (t)->efecto = INCENDIADO;
        afectaPersonaje((t));
}

void congelar (Terreno t)
{
    (t)->efecto = CONGELADO;
        afectaPersonaje((t));
}

void electrocutar(Terreno t)
{
    (t)->efecto = ELECTRIFICADO;
        afectaPersonaje((t));
}

void restaurar(Terreno t)
{
    (t)->efecto = RESTAURAR;
        afectaPersonaje((t));
}


Habilidad create_incendiar(){
    Habilidad h=malloc(sizeof(Habilidad));
    strcpy(h->nombre,"Incendiar");
    h->costoEnergia = 2;
    h->costoAccion = 7;
    h->rango= 3;
    h->efecto= &(incendiar);

    return h;
}

Habilidad create_congelar(){
    Habilidad h=malloc(sizeof(Habilidad));
    strcpy(h->nombre,"Congelar");
    h->costoEnergia = 4;
    h->costoAccion = 4;
    h->rango= 3;
    h->efecto= &(congelar);

    return h;
}

Habilidad create_Electrocutar(){
    Habilidad h=malloc(sizeof(Habilidad));
    strcpy(h->nombre,"Electrocutar");

    h->costoEnergia = 10;
    h->costoAccion = 5;
    h->rango= 4;
    h->efecto= &(electrocutar);

    return h;
}

Habilidad create_Restaurar(){
    Habilidad h=malloc(sizeof(Habilidad));
    strcpy(h->nombre,"Restaurar");

    h->costoEnergia = 5;
    h->costoAccion = 4;
    h->rango= 2;
    h->efecto= &(restaurar);

    return h;
}




void usarHabilidad(Personaje per, Habilidad h1, Habilidad h2, Habilidad h3, Habilidad h4){
    int h; // alamacena el numero de la habiliad escogida por el usuario

    if(per->inicial=='M'){
        printf("Ingrese el numero de la habilidad deseada:\n1.Incendiar\n2.Congelar\n3.Electrocutar\n4.Restaurar\n");
        scanf("%d",&h);
        switch(h){
        case 1:
            Evalhabilidad(per,h1);
            break;
        case 2:
            Evalhabilidad(per, h2);
            break;
        case 3:
            Evalhabilidad(per, h3);
            break;
        case 4:
            Evalhabilidad(per, h4);
            break;

    }
    }

    if(per->inicial=='D'){
        printf("Ingrese el numero de la habilidad deseada: n1.Congelar n2.Restaurar\n");
        scanf("%d",&h);
        switch(h){
        case 1:
            Evalhabilidad(per,h2);
            break;
        case 2:
            Evalhabilidad(per, h4);
            break;

    }
    }

    if(per->inicial=='A'){
        printf("Ingrese el numero de la habilidad deseada: \n1.Incendiar\n2.Electrocutar\n");
        scanf("%d",&h);
        switch(h){
        case 1:
            Evalhabilidad(per,h1);
            break;
        case 2:
            Evalhabilidad(per, h3);
            break;

    }
    }

    if(per->inicial=='S'){
        printf("Ingrese el numero de la habilidad deseada: \n1.Incendiar\n");
        scanf("%d",&h);
        switch(h){
        case 1:
            Evalhabilidad(per,h1);
            break;


    }
    }

}

///---------------------------------------ATACAR--------------------------------------///

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



int PuedeAtacar(Personaje p){
    if(p->ptAccion<2){
        return 0;

    }else{
        return 1;
    }

}



void atacar (Personaje p){

    BuscarEnT(p);
    MostrarTablero();
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
        if(FueraDRango( p, j, i)){
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











int main(){

    newTerreno();
    ///-------------------------Creacion de habilidades---------------------------
/*
    Habilidad incen = create_incendiar();
    Habilidad cong = create_congelar();
    Habilidad electro = create_Electrocutar();
    Habilidad restau = create_Restaurar();
*/
///-------------------------Creacion de habilidades---------------------------
    int a, b,c,d;
    Cola personajes = newCola();

    printf("Bienvenidos al Juego de Roles\n"
          "Eliga su opcion\n"
          "1. Nueva Partida\n"
          "2. SALIR\n");
    scanf("%d",&a);
    while(a!=1 && a!=2){
         printf("Opcion NO valida\n"
                "Eliga su opcion\n"
                "1. Nueva Partida\n"
                "2. SALIR\n");
        scanf("%d",&a);
    }
    if (a==1){
        selectPersonajes(personajes);
        while (1){
          // Al inicio del turno s ele deben asignar 5 ptAccion a cada personaje
            SumarAccion(first(personajes));
            printf("Escoge una opcion: \n"
                   "1)Mostrar tablero\n"
                   "2)Consultar casilla\n"
                   "3)Atacar\n"
                   "4)Moverse\n"
                   "5)Usar habilidad\n"
                   "6)Usar item\n"
                   "7)Terminar turno\n"
                   "8)Inventario\n"
                   "9)Menu sistema\n"
                  );
            scanf("%d",&b);

            switch (b){
              case 1 :
                MostrarTablero();
                break;
              case 2 :
                consultarCasilla();
                break;
              case 3 :
                atacar(first(personajes));
                break;
              case 4 :
                MoverenTablero(first(personajes));
                break;
              case 5 :
               // usarHabilidad(first(personajes), incen, cong, electro, restau);
                break;
              case 6 :
                usarItem(first(personajes));
                break;
              case 7 :

                if (EvaluaPersonaje(first(personajes))){EliminaPersonaje(first(personajes));}
                else {
                  dqueue(personajes);
                  queue(first(personajes),personajes);
                }
                break;
              case 8 : printf("\n1)Recoger item"
                                "\n2)Soltar item"
                                "\n3)Equipar item"
                                "\n4)Consultar tope"
                                "\n5)Volver\n"
                                 );
                         scanf("%d",&c);
                         switch(c){
                            case 1: /*lista en orden todos los items del piso y los enumera en un menú,
                            el jugador procede entonces a especificar uno de ellos.
                            El item sera removido del piso y agregado al tope del inventario. */
                               moverItem(first(personajes));
                               break;
                            case 2:
                              /// Item w = top((first(personajes))->inventario);
                               /*remueve el tope del inventario y lo agrega a los items que se encuentran
                                en la casilla donde está parado el personaje.*/
                               insertarItem(first(personajes),top((first(personajes))->inventario)); // debe ser la lista de items del terreno en el que esta parado el personaje.
                               break;
                            case 3:
                                /*revisa el item que se encuentra al tope del inventario, si el item es un
                                ARMA o ARMADURA, lo equipa en el campo correspondiente
                                y el item que se encontraba previamente equipado pasa ahora al tope del inventario.*/
                                busquedaItems(first(personajes));
                                break;
                            case 4:
                                //Item z=top(Personaje->inventario);
                                printf("El tope del inventario es: %s", (top((first(personajes))->inventario))->nombre);///MODIFICADO
                                break;
                            case 5:
                                break; // vuelve al menu anterior

                            }
                        break;
                case 9 :
                    printf("\n1)Volver"
                                "\n2)Salir\n");
                    scanf("%d", &d);
                        switch(d){
                            case 1: break; // lleva al usuario al menu anterior
                            case 2:
                                printf("Cerrando partida...");
                                return 0;

                    }
                    break;

                default : printf( "\n ERROR" );

                        }
                    }
                }
}

