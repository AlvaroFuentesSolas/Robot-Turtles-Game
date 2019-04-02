#include "Secuencia.h"
#include <fstream>


void crearVacia(tMazo &mazo){ 

	mazo.numCartas = 0;
	mazo.posInicio = 0;

}

bool sacar(tMazo &mazo, bool top, tCarta &carta){

	bool sacarlacarta = true;

	if (mazo.numCartas > 0){

		if (top){ //top true = sacas una carta de la parte superior del mazo

			carta = mazo.cartas[mazo.posInicio];

			for (int i = 0; i < mazo.numCartas; i++){
				mazo.cartas[i] = mazo.cartas[i + 1];
			}

		}
		else{ // top false = sacas una carta de la parte inferior del mazo
			carta = mazo.cartas[mazo.numCartas];
		}
		//Independientemente de que top sea true o false quito una carta
		mazo.numCartas--;
	}
	else{
		sacarlacarta = false;
	}

	return sacarlacarta;
}

void insertar(tMazo &mazo, tCarta carta, bool top){

	if (top){
		mazo.cartas[mazo.numCartas] = carta;
	}
	else{
		for (int i = 0; i < mazo.numCartas; i++){
			mazo.cartas[i + 1] = mazo.cartas[i];
	
		}
	}
	mazo.numCartas++;
		

}

void crearMazoAleatorio(tMazo &mazo){//crea el mazo de cartas de manera ordenada : primero las de avaza, segundo las de giroIzq...
	
	int i = 0;
	int posicion;
	
	while (i < NUM_CARTAS_AVANZA){
		mazo.cartas[i] = AVANZAR;
		i++;
	}
	posicion = i;
	while (i < posicion + NUM_CARTAS_IZQUIERDA){
		mazo.cartas[i] = GIRO_IZQUIERDA;
		i++;
	}
	posicion = i;
	while (i < posicion + NUM_CARTAS_DERECHA){
		mazo.cartas[i] = GIRO_DERECHA;
		i++;
	}
	posicion = i;
	while (i < posicion + NUM_CARTAS_LASER){
		mazo.cartas[i] = LANZAR_LASER;
		i++;
	}
	
		
	mazo.numCartas = MAX_CARTAS_MAZO;

	random_shuffle(begin(mazo.cartas), end(mazo.cartas));//desordena el mazo de cartas

}


// tJuego -------- line.size();  funcion auxiliar -> tCasilla(string letra) transforma cada signo en un simbolo del enum