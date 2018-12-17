#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include _GAMERPG_H_

int main(){
    int a, b,c,d;
    Terreno Tablero[10][20];
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
        seleccionPersonajes();
        int orden=1;
        while (orden<=4){
            printf("Bienvenido\n"); // no se como poner el nombre del personaje segun el orden
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
                    Tablero x = MostrarTablero();
                    break;
                case 2 :
                    void consultar casilla(); // HACER FUNCION CONSULTAR CASILLA
                    break;
                case 3 :
                     atacar();
                   break;
                case 4 :
                   // Padilla terminar
                   break;
                case 5 :
                    //  Terminar
                    break;
                case 6 :
                    // Terminar
                    break;
                case 7 :
                    orden ++;
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
                                break;
                            case 2: /*remueve el tope del inventario y lo agrega a los items que se encuentran
                                en la casilla donde está parado el personaje.*/
                                break;
                            case 3: /*revisa el item que se encuentra al tope del inventario, si el item es un
                                ARMA o ARMADURA, lo equipa en el campo correspondiente
                                y el item que se encontraba previamente equipado pasa ahora al tope del inventario.*/
                                break;
                            case 4:
                                Item z=top(&Personaje->inventario);
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

