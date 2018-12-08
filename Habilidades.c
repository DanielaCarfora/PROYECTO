#include <stdio.h>



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
int Evalincendiar(Personaje p, Habilidad h)
{
    if(p>ptAccion < h->costoAccion)return 0;
    if(p>ptEnergia < h->costoAccion)return 0;

    return 1;

}



void incendiar (Terreno *t)
{
    t->efecto = INCENDIADO; ///Falta definir el manejo de cada casilla del terreno para guardar el efecto
}

void congelar (Terreno *t)
{
    t->efecto = CONGELADO;   ///Falta definir el manejo de cada casilla del terreno
}

void electrocutar(Terreno *t)
{
    t->efecto = ELECTRIFICADO;	///Falta definir el manejo de cada casilla del terreno
}

void restaurar(Terreno *t)
{
    t->efecto = RESTAURAR;	///Falta definir el manejo de cada casilla del terreno
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
