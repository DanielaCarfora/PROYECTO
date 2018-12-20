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
	char *nombre;
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
    struct turno *tnext;


}Turno;

typedef Turno *Turnos;


Terreno Tablero [10][20];



int main(){
Personaje p=malloc(sizeof(Personaje));
    p->nombre = "Mago";
    p->ptSalud=100;
    p->ptEnergia=50;
    p->inventario= NULL;
    p->habilidades= NULL;
    p->danio=10;
    p->rango=6;
    p->evasion=50;
    p->jugador=1;
    p->ptAccion=0;
    p->velocidad= 1;
    p->inicial='M';



printf("\nNombre: %s \n", p->nombre);

//ShowCPersonaje(p);



}






