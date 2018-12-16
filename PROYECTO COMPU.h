#ifndef _GAMERPG_H_
#define _GAMERPG_H_


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
	int armadura;
	int evasion;
	int velocidad;
	int ptAccion;
	int jugador; // jugador al cual pertenece el jugador
}STRUCT_PER;

typedef STRUCT_PER *Personaje;

typedef struct  s_habilidad;
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

//############################ Fin estructuras de los TAD's ###############################

//-----------------------------------------------------------------------------------------

//############################ Primittivas del TAD ########################################


//############################ Fin primittivas del TAD ####################################

//-----------------------------------------------------------------------------------------

//############################ Operaciones sobre TAD ######################################



//############################ Fin operaciones  del TAD ###################################


//-----------------------------------------------------------------------------------------


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

	Terreno 

    return item; // falta agregarlo al terreno actual
    
}

void busquedaItem(PilaInv*p, ListaIte*a, item ite){ // Recibe el Item a buscar, la pila de inventario y la lista del terreno.
	while(p!=NULL && ite != p->items){
		Item b=pop(&p);
		insertar_ite(&a,b)
	}	
		
}
	
	
}

////########################## Fin de Operaciones de pilas ################################

//-----------------------------------------------------------------------------------------


#endif
