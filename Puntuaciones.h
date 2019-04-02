#ifndef puntuaciones_h
#define puntuaciones_h
#include <string>

using namespace std;

const int MAX_JUGADORES_HISTORIAL = 10;  // poner la dimensión que se desee a la lista

typedef struct {
	string nombre;
	int puntuacion;
} tPuntuacionJugador; 


typedef struct {
	tPuntuacionJugador puntuaciones[MAX_JUGADORES_HISTORIAL];
	int num_jugadores;
} tPuntuaciones;

bool cargarPuntuaciones(tPuntuaciones &puntos);
bool guardarPuntuaciones(const tPuntuaciones &puntos);
void mostrarPuntuaciones(const tPuntuaciones &puntos);
bool actualizarPuntuacion(tPuntuaciones &puntos, const string &nombre, int nuevos);

#endif

/*NUEVAS  FUNCIONES PRACTICA 4

1. ampliarpuntuaciones(tPuntuaciones &t) --------------> new y delete

2. generar() --------------> new

3. liberar(tPuntuaciones &t) --------------> delete

4. ordenar

*/