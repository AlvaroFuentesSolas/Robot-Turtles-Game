#include "Puntuaciones.h"
#include <fstream>
#include <iostream>

bool cargarPuntuaciones(tPuntuaciones &puntos){

	bool abierto = false;
	ifstream fichero;
	fichero.open("puntuaciones.txt");
	if (fichero.is_open() == true){
		abierto = true;
		for (int i = 0; !fichero.eof() && i < MAX_JUGADORES_HISTORIAL; i++){
			fichero >> puntos.puntuaciones[i].nombre;
			fichero >> puntos.puntuaciones[i].puntuacion;
			puntos.num_jugadores = i;
		}
		
		fichero.close();
	}


return abierto;

}

bool guardarPuntuaciones(const tPuntuaciones &puntos){

	ofstream salida;
	bool guardado = false;
	salida.open("puntuaciones.txt");

	if (salida.is_open()){
		for (int i = 0; i < puntos.num_jugadores; i++){
			salida << puntos.puntuaciones[i].nombre << " " << puntos.puntuaciones[i].puntuacion << "\n";
		}
		salida.close();
		guardado = true;
	}
	else{
		cout << "No se ha podido abrir el fichero con los nombres y las puntuaciones";
	}

	return guardado;

}

bool existe(const tPuntuaciones &puntos, const string nombre){

	int i = 0;
	bool existe = false;
	while (i < puntos.num_jugadores && existe == false){
		if (puntos.puntuaciones[i].nombre == nombre){
			existe = true;
		}
	    i++;
	}


	return existe;
}

int posMenorPuntos(const tPuntuaciones &puntos){

	int mispuntos = puntos.puntuaciones[0].puntuacion;
	int posicion = 0;

	for (int i = 1; i < puntos.num_jugadores; i++){

		if (puntos.puntuaciones[i].puntuacion < mispuntos){
			mispuntos = puntos.puntuaciones[i].puntuacion;
			posicion = i;
		}
	}

	return posicion;
}

int posJugador(const tPuntuaciones &puntos, const string nombre){
	
	int i = 0;
	int posicion = -1;

	while (i < puntos.num_jugadores){
		if (puntos.puntuaciones[i].nombre == nombre){
			posicion = i;
		}
		i++;
	}

	return posicion;
}

bool actualizarPuntuacion(tPuntuaciones &puntos, const string &nombre, int nuevos){
	
	int i = 0;
	bool actualizar = true;

	if (existe(puntos, nombre)){
			puntos.puntuaciones[posJugador(puntos, nombre)].puntuacion = puntos.puntuaciones[posJugador(puntos, nombre)].puntuacion + nuevos;
	}
	else{
	
		if (puntos.num_jugadores < MAX_JUGADORES_HISTORIAL){
			puntos.puntuaciones[puntos.num_jugadores].nombre = nombre;
			puntos.puntuaciones[puntos.num_jugadores].puntuacion = nuevos; 
			puntos.num_jugadores++;
		}
		else if (puntos.num_jugadores == MAX_JUGADORES_HISTORIAL){

			int posicion = posMenorPuntos(puntos);

			if (puntos.puntuaciones[posicion].puntuacion < nuevos){
				puntos.puntuaciones[posicion].nombre = nombre;
				puntos.puntuaciones[posicion].puntuacion = nuevos;
			}
			else{
				actualizar = false;
			}
		}
	}

	return actualizar;
}

void mostrarPuntuaciones(const tPuntuaciones &puntos){
	
	tPuntuacionJugador aux;

	tPuntuaciones mis_puntuaciones = puntos; //lo copiamos en un "tPuntuaciones" auxiliar porque "puntos" es constante

	for (int i = 0; i < puntos.num_jugadores - 1; i++){ // ordenamos dicho array de mayor a menor segun las puntuaciones
		for (int x = i + 1; x < puntos.num_jugadores; x++){

			if (mis_puntuaciones.puntuaciones[i].puntuacion < mis_puntuaciones.puntuaciones[x].puntuacion){
				aux = mis_puntuaciones.puntuaciones[i];
				mis_puntuaciones.puntuaciones[i] = mis_puntuaciones.puntuaciones[x];
				mis_puntuaciones.puntuaciones[x] = aux;
			}
		}
	}
	
	
	for (int i = 0; i < puntos.num_jugadores; i++){ //mostramos los jugadores y sus puntos en orden
		cout << mis_puntuaciones.puntuaciones[i].nombre << " " << mis_puntuaciones.puntuaciones[i].puntuacion << endl;
	}


}