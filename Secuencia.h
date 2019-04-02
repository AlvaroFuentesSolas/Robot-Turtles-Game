#pragma once

#include <algorithm>
#include <string>
using namespace std;

// N�mero m�ximo de cartas en el mazo
const int MAX_CARTAS_MAZO = 38;
const int NUM_CARTAS_AVANZA = 18;
const int NUM_CARTAS_IZQUIERDA = 8;
const int NUM_CARTAS_DERECHA = 8;
const int NUM_CARTAS_LASER = 4;


// Tipos de cartas
typedef enum { AVANZAR, GIRO_IZQUIERDA, GIRO_DERECHA, LANZAR_LASER } tCarta;

// Mazos de cartas
typedef tCarta tCartas[MAX_CARTAS_MAZO];
typedef struct {
	tCartas cartas;	// Array de cartas
	int posInicio;	// Puntero a la primera carta (top)
	int numCartas;	// Numero de cartas desde posInicio (buffer circular)
} tMazo;

// Mano de cada jugador
typedef struct {
	unsigned int avanzar;
	unsigned int giroIzquierda;
	unsigned int giroDerecha;
	unsigned int laser;	
}tMano;

// Crea una secuencia vac�a de cartas
void crearVacia(tMazo &mazo);

// Saca la carta de la parte superior (top=true) / inferior (top=false) del mazo y la devuelve en cartaEliminada.
bool sacar(tMazo &mazo, bool top, tCarta &carta);

// Inserta la carta en la parte superior (top=true) / inferior (top=false) del mazo.
void insertar(tMazo &mazo, tCarta carta, bool top);

// Crea un mazo aleatorio de cartas
void crearMazoAleatorio(tMazo &mazo);

// Convierte una carta a String
string cartaToString(tCarta carta);


/*
NUEVAS FUNCIONES PRACTICA 4

1. liberar(tMazo ) --------------> delete, lo llamamos desde el main y desde la secuencia de jugadas de los jugadores

2. En crearMazoAleatorio  --------------> new
3. En insertar --------------> new
4. En sacar --------------> delete
*/