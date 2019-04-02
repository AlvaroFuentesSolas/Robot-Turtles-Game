#pragma once

#include <Windows.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <locale.h>
#include <iomanip>   
#include <stdio.h>
#include <cmath>
#include <conio.h>
#include "Secuencia.h"
using namespace std;

// Constantes
const int NUM_FILAS = 8;
const int NUM_COLUMNAS = 8;
const int MAX_HIELOS = 12;
const int MAX_JUGADORES = 4;
const int MAX_CARTAS_JUGADA = 10;
const int NUM_TIPOS_CASILLAS = 6;
const int PALETA[NUM_TIPOS_CASILLAS + MAX_JUGADORES] = { 1, 11, 7, 4, 12, 5, 13, 9, 10, 3 };

// Direcciones
typedef enum { NORTE, SUR, ESTE, OESTE } tDir;

// Estado de cada casilla
typedef enum { VACIA, HIELO, MURO, CAJA, JOYA, TORTUGA } tEstadoCasilla;

// Tortuga en tablero
typedef struct {
	int numero;
	tDir direccion;
}tTortuga;

// Casilla en tablero
typedef struct { 
		tEstadoCasilla estado; 
		tTortuga tortuga; 
}tCasilla;

// Tablero
typedef tCasilla tTablero[NUM_FILAS][NUM_COLUMNAS];

// Tipos de acciones
typedef enum { EJECUTAR_JUGADA, ROBAR_CARTA, NINGUNA} tAccion;

// Coordenadas
typedef struct {
	int x;
	int y;
} tCoordenada;

// Informaci�n del jugador
typedef struct {
	string nombre;
	tMazo mazo;
	tMano jugada;
	tDir direccionActual;	
	tCoordenada posicionActual;
}tJugador;

// Juego
typedef struct {
	unsigned int numJugadores;
	unsigned int turnoActual;
	tJugador jugadores[MAX_JUGADORES];
	tTablero tablero;
}tJuego;

// Tipos de teclas
typedef enum { AVANZA, DERECHA, IZQUIERDA, LASER, SALIR, NADA } tTecla;

// Lee la acci�n del jugador actual y la ejecuta. Devuelve true si se ha ejecutado el turno y false en caso contrario.
bool ejecutarTurno(tJuego &juego); 

// Lee una tecla introducida por el usuario
tTecla solicitarTecla(); 

// El jugador con el turno roba una carta de su mazo si hay cartas disponibles.
bool accionRobar(tJuego &juego);

// Comprueba si la secuencia introducida por el jugador actual se puede ejecutar
bool comprobarCondicionSecuencia (int numCartas, int numAvanzar, int numGiroIzquierda, int numGiroDerecha, int numLaser, tMazo mazo);

// Intercambia dos casillas del tablero
void intercamBiarCasillas(tJuego &juego, tCoordenada origen, tCoordenada destino);

// Comprueba que usa casilla esta desntro del tablero
bool casillaEnTablero(tCoordenada casilla);

// Calcula la siguiente casilla en la dirección indicada
tCoordenada siguienteCasilla(tCoordenada origen, tDir direccion);

// Avanza la tortuga con el turno actual
bool avanzarTortuga(tJuego &juego);

// Gira la tortuga con el turno hacia la izquierda
void girarTorturaIzquierda(tJuego & juego);

// Gira la tortuga con el turno hacia la derecha
void girarTorturaDerecha(tJuego & juego);

// Lanza el laser de la tortuga con el turno
void lanzarLaser(tJuego &juego);

// El jugador con el ejecuta una secuencia de cartas. El segundo par�metro indica un subconjunto de las cartas del jugador actual.
bool accionSecuencia(tJuego &juego, tMazo &cartas);

// Cambia el turno al jugador siguiente.
void cambiarTurno(tJuego &juego);

// Muestra el estado del juego
void mostrarJuego(const tJuego &juego);

// Inicializa el juego
bool cargarJuego(tJuego &juego);

// Carga el tablero y lo almacena en la estructura juego
bool cargarTablero(string nombreTablero, tJuego &juego, int numJugadores);

// Carga una casilla en el tablero con la informaci�n del fichero
void cargarCasilla(tJuego &juego, tCoordenada coordenada, int &numJugador, char caracter);

// Dibuja el tablero en pantalla
void dibujarTablero(const tTablero tablero);

// Dibuja una casilla
void dibujaCasilla(tCasilla casilla);

// Dibuja una direcci�n
void dibujarDireccion(tDir direccion);

// Establece el color de fondo de una casilla
void colorFondo(int color);

// Actualiza la mano de un jugador al coger una carta nueva
void incluirCarta(tMano &mano, tCarta carta);
