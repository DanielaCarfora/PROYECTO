
#include "GAMERPG.h"

int main(){

    newTerreno();
    Habilidad incendiar = create_incendiar();
    Habilidad congelar = create_congelar();
    Habilidad electrocutar = create_Electrocutar();
    Habilidad restaurar = create_Restaurar();
    int a, b,c,d;

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
        
        printf("Se deben seleccionar los personajes\n");
        printf("Jugador 1 - Primer Personaje\n");
        Cola personajes = newCola();
        selectPersonaje(personajes);
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
                usarHabilidad(first(personajes));
                break;
              case 6 :
                usarItem(first(personajes));
                break;
              case 7 :
                Personaje pp = first(personajes);
                if (EvaluaPersonaje(pp)){
                  EliminaPersonaje(pp); 
                else {
                  dequeue(personajes);
                  queue(pp,personajes);
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
                               Item w = top(&((first(personajes))->inventario))/*remueve el tope del inventario y lo agrega a los items que se encuentran
                                en la casilla donde está parado el personaje.*/
                               insertarItem(first(personajes),w); // debe ser la lista de items del terreno en el que esta parado el personaje.
                               break;
                            case 3: 
                                /*revisa el item que se encuentra al tope del inventario, si el item es un
                                ARMA o ARMADURA, lo equipa en el campo correspondiente
                                y el item que se encontraba previamente equipado pasa ahora al tope del inventario.*/
                                busquedaItems(first(personajes));
                                break;
                            case 4:
                                Item z=top(&Personaje->inventario);
                                printf("El tope del inventario es: %s", z->nombre);
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
                    break

                default : printf( "\n ERROR" );
   }
}
