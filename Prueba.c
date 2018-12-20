#include <stdlib.h>
#include <string.h>
#include <stdio.h>



int posi, posj;



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
	char nombre[16];
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
	char *nombre;
	int costoEnergia;
	int costoAccion;
	int rango;
	void (*efecto)(Terreno*);
}STRUCT_HAB;

typedef STRUCT_HAB *Habilidad;

typedef struct s_item
{
	char *nombre;
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
    struct turno *tnext;


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
	q->items = ite;
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

Item top(PilaInv p){
    return p->items;
}
















Terreno Tablero [10][20];


int main(){
Personaje p=malloc(sizeof(Personaje));
    p->nombre = "Mago";
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


void ShowCPersonaje(Personaje p){
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





int main(){
Personaje p=NewMago(1, 1);

printf("\nNombre: %s \n", p->nombre);

ShowCPersonaje(p);



}






