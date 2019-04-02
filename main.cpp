/*GRUPO 13
ALVARO FUENTES SOLAS 71946914Q
EDUARDO MARTINEZ MORA 02595856F
*/

#include <iostream>
#include "Juego.h"
#include "Secuencia.h"
#include "Puntuaciones.h"
using namespace std;

bool cargarJuego(tJuego &juego);
bool movimientoRobar(tJuego &juego);
void main(){
	bool salir = false;
	tPuntuaciones puntos;
	cargarPuntuaciones(puntos);
	while (salir == false){
		tJuego jugar;
		int eleccion = 4;
		jugar.turnoActual = 0;
		int color = 4;
		cout << "Elige una de las siguientes opciones: \n"
			<< "1. Jugar\n" << "2. Mostrar Puntuaciones\n" << "0. Salir\n";
		cin >> eleccion;
		if (eleccion == 0){
			salir = true;
		}
		else if (eleccion == 1){
			if (cargarJuego(jugar)){
				mostrarJuego(jugar);
				while (ejecutarTurno(jugar) == false){ //si NO se ha encontrado la joya, cambiar turno y ejecutar turno constantemente
					mostrarJuego(jugar);
					cambiarTurno(jugar);
					
				}
			mostrarJuego(jugar);
			cout << "ENHORABUENA " << jugar.jugadores[jugar.turnoActual].nombre << ", HAS GANADO\n";
			actualizarPuntuacion(puntos, jugar.jugadores[jugar.turnoActual].nombre, jugar.numJugadores);
			guardarPuntuaciones(puntos);
			}
			else{
				cout << "No se ha podido cargar el tablero, vuelva a intentarlo \n";
			}

		}
		else if (eleccion == 2){
			mostrarPuntuaciones(puntos);
		}
		
	}
	
}