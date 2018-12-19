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

	printf("Personajes del jugador 2 creados exitosamente\n");

queue(p1, personajes);
queue(p3, personajes);
queue(p2, personajes);
queue(p4, personajes);




}




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
        if(t->efecto == RESTAURAR){
        	t->personaje->ptSalud= t->personaje->ptSalud + (saludMax *0.30);
        	if(t->personaje->ptSalud>100){
        		ptSalud=100;
        	}


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
    	afectaPeronaje(t);
}
