#include "juego.h"



/*int main(){


	tJuego juego;

	cargarJuego(juego);
	mostrarJuego(juego);
	system("Pause");
	return 0;
}
*/
tCasilla char2casilla(char casilla);
string casilla2char(tCasilla casilla);
bool accionRobar(tJuego &juego);
bool comprobarCondicionSecuencia(int numCartas, int numAvanzar, int numGiroIzquierda, int numGiroDerecha, int numLaser, tTecla micarta);

bool cargarJuego(tJuego &juego){
	ifstream fichero;
	string nombrefichero;
	string line;
	int jugadores;
	string participantes;
	bool cargar = false;
	bool salir = false;
	bool totalparticipantes = false;
	char casilla_letra;
	bool datos = false;

	int i = 0;
	while (datos == false){
		cout << "Introduce el nombre del fichero: ";
		cin >> nombrefichero;
		cout << "Introduce el numero de jugadores que van a participar: ";
		cin >> participantes;
		fichero.open(nombrefichero);
		if (participantes == "1"){ //como "participantes" es un string, creamos un int(jugadores)con el mismo valor para poder añadirlo a numJugadores 
			jugadores = 1;
		}
		if (participantes == "2"){
			jugadores = 2;
		}
		if (participantes == "3"){
			jugadores = 3;
		}
		if (participantes == "4"){
			jugadores = 4;
		}
		if (participantes != "1" && participantes != "2" && participantes != "3" && participantes != "4"){
			jugadores = 8; // nos valdria cualquier numero mayor que 4 para que no entre en el siguiente "if"
		}

		if ((fichero.is_open()) && (0 < jugadores) && (jugadores < 5)){
			datos = true;
			juego.numJugadores = jugadores;
			int p = juego.turnoActual; //asi no modificamos la posicion del jugador actual
			while (!fichero.eof()){// mientras no sea el final del fichero lee hasta que encontramos el tablero segun el numero de participantes
				fichero >> line;
				if ((line == participantes) || (salir = false)){
					for (int x = 0; x < NUM_FILAS; x++){
						getline(fichero, line);
						fichero >> line;
						for (int y = 0; y < NUM_COLUMNAS; y++){
							casilla_letra = line.at(y);
							juego.tablero[x][y] = char2casilla(casilla_letra);
							if (juego.tablero[x][y].estado == TORTUGA){
								juego.tablero[x][y].tortuga.numero = i;//Añadimos a cada tortuga su numero correspondiente
								if (i == 0){
									juego.tablero[x][y].tortuga.direccion = SUR;// Añadimos a cada tortuga su direccion correspondiente en el tablero
									juego.jugadores[p].direccionActual = SUR; //Añadimos a cada jugador la misma direccion que a su tortuga
									juego.jugadores[p].posicionActual.x = 0;//Indicamos en que posicion del tablero se encuentran
									juego.jugadores[p].posicionActual.y = 0;

								}
								if (i == 1){
									juego.tablero[x][y].tortuga.direccion = OESTE;
									juego.jugadores[p].direccionActual = OESTE;
									juego.jugadores[p].posicionActual.x = 0;
									juego.jugadores[p].posicionActual.y = 7;

								}
								if (i == 2){
									juego.tablero[x][y].tortuga.direccion = ESTE;
									juego.jugadores[p].direccionActual = ESTE;
									juego.jugadores[p].posicionActual.x = 7;
									juego.jugadores[p].posicionActual.y = 0;
								}
								if (i == 3){
									juego.tablero[x][y].tortuga.direccion = NORTE;
									juego.jugadores[p].direccionActual = NORTE;
									juego.jugadores[p].posicionActual.x = 7;
									juego.jugadores[p].posicionActual.y = 7;
								}
								i++;
								p++;
							}

						}
						cout << "\n";
						salir = true; //no queremos seguir leyendo el fichero, ya tenemos el tablero que queremos
					}
				}
			}
			cargar = true;
		}
		else{
			cout << "Los datos introducidos son erroneos, intentelo de nuevo\n";
			datos = false;
		}
	}
	
	string nombre;
	int p = juego.turnoActual;
	while ((p < jugadores) && (cargar)){
		cout << "Introduce el nombre de tu jugador: ";
		cin >> nombre; "\n";
		juego.jugadores[p].nombre = nombre; //Introducimos el nombre de jugador
		crearVacia(juego.jugadores[p].mazo); //Creamos un mazo 
		crearMazoAleatorio(juego.jugadores[p].mazo); //Rellenamos el mazo a cada jugador
		juego.jugadores[p].jugada.avanzar = 0; //Inicializamos la mano del jugador
		juego.jugadores[p].jugada.giroDerecha = 0;
		juego.jugadores[p].jugada.giroIzquierda = 0;
		juego.jugadores[p].jugada.laser = 0;
		p++;
	}
	int j = juego.turnoActual;
	while (juego.turnoActual < juego.numJugadores){
		int j = 0;
		while (j < 3){ 
			accionRobar(juego);
			j++;
		}
		juego.turnoActual++;
	}
	juego.turnoActual = j;
return cargar;
}

tCasilla char2casilla(char casilla){ //Funcion que convierte los char del fichero 

	tCasilla cas;
	switch (casilla)
	{
	case '#': cas.estado = MURO;
		break;
	case '@': cas.estado = HIELO;
		break;
	case '$': cas.estado = JOYA;
		break;
	case 'C': cas.estado = CAJA;
		break;
	case '*': cas.estado = VACIA;
		break;
	case 'D' :
		cas.estado = TORTUGA;
		cas.tortuga.direccion = SUR;
		break;
	case 'U':
		cas.estado = TORTUGA;
		cas.tortuga.direccion = NORTE;
		break;
	case 'R':
		cas.estado = TORTUGA;
		cas.tortuga.direccion = ESTE;
		break;
	default:
		cas.estado = TORTUGA;
		cas.tortuga.direccion = OESTE;
		break;
	}
	
	return cas;
}

tTecla solicitarTecla(){

	tTecla cartaelegida;
	int dir;
	dir = _getch();
	if (dir == 224){
		dir = _getch();
		if (dir == 72){
			cartaelegida = AVANZA;
			cout << "^ ";
		}
		else if (dir == 77){
			cartaelegida = DERECHA;
			cout << "> ";
		}
		else if (dir == 75){
			cartaelegida = IZQUIERDA;
			cout << "< ";
		}
		else{
			cout << "El movimiento introducio es invalido \n";
		}
	}
	else if (dir == 13){
		cartaelegida = SALIR;
	}
	else if (dir == 32){
		cartaelegida = LASER;
		cout << "~ ";
	}
	else{
		cout << "Tecla introducida erronea, vuelva a intentarlo \n ";
	}
	
return cartaelegida;
}

void mostrarJuego(const tJuego &juego){
	
	system("cls");
	tCasilla figura;
	int color = 0;
	for (int x = 0; x < NUM_FILAS; x++){
		for (int y = 0; y < NUM_COLUMNAS; y++){
				figura = juego.tablero[x][y];
			if (figura.estado == CAJA){
				color = 6;
			}
			if (figura.estado == TORTUGA){
				if (figura.tortuga.numero == 0){
					color = 5;
				}
				if (figura.tortuga.numero == 1){
					color = 13;
				}
				if (figura.tortuga.numero == 2){
					color = 9;
				}
				if (figura.tortuga.numero == 3){
					color = 2;
				}
			}
			if (figura.estado == VACIA){
				color = 1;
			}
			if (figura.estado == MURO){
				color = 8;
			}
			if (figura.estado == HIELO){
				color = 11;
			}
			if (figura.estado == JOYA){
				color = 4;
			}
			colorFondo(color);
			cout << casilla2char(figura); //muestra el tablero
		}
		cout << "\n";
		color = 0;
		colorFondo(color);
	}
	int i = 0;
	cout << "JUGADORES:\n";
	int n = juego.numJugadores;
	while (i < n){
		if (i == 0){
			colorFondo(5); cout << setw(10) << juego.jugadores[i].nombre;
		}
		if (i == 1){
			colorFondo(13); cout << setw(10) << juego.jugadores[i].nombre;
		}
		if (i == 2){
			colorFondo(9); cout << setw(10) << juego.jugadores[i].nombre;
		}
		if (i == 3){
			colorFondo(2); cout << setw(10) << juego.jugadores[i].nombre;
		}
		colorFondo(0);
		cout << ": " << juego.jugadores[i].jugada.avanzar; colorFondo(10), cout << "^"; colorFondo(0);
		cout << juego.jugadores[i].jugada.giroIzquierda; colorFondo(10); cout << "<"; colorFondo(0);
		cout << juego.jugadores[i].jugada.giroDerecha; colorFondo(10); cout << ">"; colorFondo(0);
		cout << juego.jugadores[i].jugada.laser; colorFondo(10); cout << "~\n"; colorFondo(0);
		i++;
	}
	
}

string casilla2char(tCasilla casilla){

	string figura;

	switch (casilla.estado)
	{
	case MURO: figura = "||";
		break;
	case HIELO: figura = "**";
		break;
	case CAJA: figura = "[]";
		break;
	case JOYA: figura = "00";
		break;
	case VACIA: figura = "  ";
		break;
	default:
		if (casilla.tortuga.direccion == NORTE){
			figura = "^^";
		}
		else if (casilla.tortuga.direccion == SUR){
			figura = "vv";
		}
		else if (casilla.tortuga.direccion == ESTE){
			figura = ">>";
		}
		else{
			figura = "<<";
		}
		break;
	}

	return figura;
}

bool ejecutarTurno(tJuego &juego){
	bool joya = false;
	int numeroCartas = juego.jugadores[juego.turnoActual].mazo.numCartas;
	int avanzar = juego.jugadores[juego.turnoActual].jugada.avanzar;
	int derecha = juego.jugadores[juego.turnoActual].jugada.giroDerecha;
	int izquierda = juego.jugadores[juego.turnoActual].jugada.giroIzquierda;
	int laser = juego.jugadores[juego.turnoActual].jugada.laser;

	bool existesecuencia = true; // si hay cartas para hacer la secuencia
	bool movimientossecuencia = true; // si los movimientos seleccionados se pueden realizar en el tablero
	bool error = true;
	char opcion;
	tTecla cartajugada;
	tMazo jugada;
	cout << juego.jugadores[juego.turnoActual].nombre << " pulsa la letra que desees ejecutar:"
		 << "\n" << "R - Robar " << "\n" << "E - Crear y ejecutar una secuencia" << "\n";
	while (error){
		cin >> opcion; "\n";
		if (opcion == 'R' || opcion == 'r'){
			accionRobar(juego);
			error = false;
		}
		if (opcion == 'E' || opcion == 'e'){
			bool salir = false;
			cout << "Introduce el movimiento que desee ejecutar: " << "\n";
			int i = 0;
			while (i < MAX_CARTAS_JUGADA && salir == false){ //si el jugador no ha elegido 10 movimientos o pulsado la tecla enter

				cartajugada = solicitarTecla(); "\n";
				crearVacia(jugada);
				if (cartajugada == AVANZA){
					jugada.cartas[i] = AVANZAR;
					i++;
				}
				if (cartajugada == DERECHA){
					jugada.cartas[i] = GIRO_DERECHA;
					i++;
				}
				if (cartajugada == IZQUIERDA){
					jugada.cartas[i] = GIRO_IZQUIERDA;
					i++;
				}
				if (cartajugada == LASER){
					jugada.cartas[i] = LANZAR_LASER;
					i++;
				}
				if (cartajugada == SALIR){// tecla enter
					salir = true;
				}

				jugada.numCartas = i;
			}

			if (comprobarCondicionSecuencia(numeroCartas, avanzar, derecha, izquierda, laser, jugada) == true){
				if (accionSecuencia(juego, jugada)){
					joya = true;
				}
				bool top = false;

				for (int i = 0; i < jugada.numCartas; i++)
					insertar(juego.jugadores[juego.turnoActual].mazo, jugada.cartas[i], top);
				//volvemos a insertar en el mazo las cartas seleccionadas por el jugador
			}
			else{
				cout << "Lo siento,NO tienes cartas, para hacer esa secuencia";
			}
			error = false;
		}
		if (opcion != 'R' && opcion != 'E' && opcion != 'r' && opcion != 'e') {
			cout << "Letra incorrecta, vuelva a intentarlo: ";
		}
	}
	return joya;
}

bool avanzarTortuga(tJuego &juego){
	tCasilla posicionsiguiente;
	tCoordenada pos, pos1;
	bool joya = false;
	pos = siguienteCasilla(juego.jugadores[juego.turnoActual].posicionActual, juego.jugadores[juego.turnoActual].direccionActual);
	if (casillaEnTablero(pos) == true){
		if (juego.tablero[pos.x][pos.y].estado == VACIA){
			intercamBiarCasillas(juego, juego.jugadores[juego.turnoActual].posicionActual, pos);
			juego.jugadores[juego.turnoActual].jugada.avanzar--;
			juego.jugadores[juego.turnoActual].posicionActual = pos;
		}
		if (juego.tablero[pos.x][pos.y].estado == CAJA){ // si la posicion siguiente a la tortuga es una caja...
			pos1 = siguienteCasilla(pos, juego.jugadores[juego.turnoActual].direccionActual);
			if (juego.tablero[pos1.x][pos1.y].estado == VACIA){ // ... comprobamos que la siguiente a la caja este vacia... 
				intercamBiarCasillas(juego, pos, pos1);
				intercamBiarCasillas(juego, juego.jugadores[juego.turnoActual].posicionActual, pos);
				juego.jugadores[juego.turnoActual].posicionActual = pos;
				juego.jugadores[juego.turnoActual].jugada.avanzar--; 
				// ... si es asi, el movimiento se va a realizar seguro, sino no se resta de la mano del jugador
			}
		}
		if (juego.tablero[pos.x][pos.y].estado == JOYA){
			intercamBiarCasillas(juego, juego.jugadores[juego.turnoActual].posicionActual, pos);
			juego.tablero[juego.jugadores[juego.turnoActual].posicionActual.x][juego.jugadores[juego.turnoActual].posicionActual.y].estado = VACIA;
			joya = true;
			juego.jugadores[juego.turnoActual].jugada.avanzar--;
			/*Si se cumple una de estas tres condiciones entonces quitamos una carta de la mano del jugador, sino pasariamos al siguiente movimiento
			seleccionado por el jugador */
		}
	}
	return joya;
}

void girarTorturaIzquierda(tJuego &juego){
	bool salir = false;
	int pos1 = juego.jugadores[juego.turnoActual].posicionActual.x;
	int pos2 = juego.jugadores[juego.turnoActual].posicionActual.y;
	
	if (juego.jugadores[juego.turnoActual].direccionActual == NORTE && salir == false){
		juego.tablero[pos1][pos2].tortuga.direccion = OESTE;
		juego.jugadores[juego.turnoActual].direccionActual = OESTE;
		casilla2char(juego.tablero[pos1][pos2]);
		salir = true;
	}
	if (juego.jugadores[juego.turnoActual].direccionActual == OESTE && salir == false){
		juego.tablero[pos1][pos2].tortuga.direccion = SUR;
		juego.jugadores[juego.turnoActual].direccionActual = SUR;
		casilla2char(juego.tablero[pos1][pos2]);
		salir = true;
	}
	if (juego.jugadores[juego.turnoActual].direccionActual == SUR && salir == false){
		juego.tablero[pos1][pos2].tortuga.direccion = ESTE;
		juego.jugadores[juego.turnoActual].direccionActual = ESTE;
		casilla2char(juego.tablero[pos1][pos2]);
		salir = true;
	}
	if (juego.jugadores[juego.turnoActual].direccionActual == ESTE && salir == false){
		juego.tablero[pos1][pos2].tortuga.direccion = NORTE;
		juego.jugadores[juego.turnoActual].direccionActual = NORTE;
		casilla2char(juego.tablero[pos1][pos2]);
		salir = true;
	}
}

void girarTorturaDerecha(tJuego &juego){
	bool salir = false;
	int pos1 = juego.jugadores[juego.turnoActual].posicionActual.x;
	int pos2 = juego.jugadores[juego.turnoActual].posicionActual.y;
	if (juego.jugadores[juego.turnoActual].direccionActual == NORTE && salir == false){
		juego.tablero[pos1][pos2].tortuga.direccion = ESTE;
		juego.jugadores[juego.turnoActual].direccionActual = ESTE;
		casilla2char(juego.tablero[pos1][pos2]);
		salir = true;
	}
	if (juego.jugadores[juego.turnoActual].direccionActual == ESTE && salir == false){
		juego.jugadores[juego.turnoActual].direccionActual = SUR;
		juego.tablero[pos1][pos2].tortuga.direccion = SUR;
		casilla2char(juego.tablero[pos1][pos2]);
		salir = true;
	}
	if (juego.jugadores[juego.turnoActual].direccionActual == SUR && salir == false){
		juego.jugadores[juego.turnoActual].direccionActual = OESTE;
		juego.tablero[pos1][pos2].tortuga.direccion = OESTE;
		casilla2char(juego.tablero[pos1][pos2]);
		salir = true;
	}
	if (juego.jugadores[juego.turnoActual].direccionActual == OESTE && salir == false){
		juego.jugadores[juego.turnoActual].direccionActual = NORTE;
		juego.tablero[pos1][pos2].tortuga.direccion = NORTE;
	}
}

void lanzarLaser(tJuego &juego){

	tCasilla casillasiguiente;
	tCoordenada pos, pos1;
	pos = siguienteCasilla(juego.jugadores[juego.turnoActual].posicionActual, juego.jugadores[juego.turnoActual].direccionActual);
	if (casillaEnTablero(pos) == true){
		while (juego.tablero[pos.x][pos.y].estado == VACIA){
			pos = siguienteCasilla(pos, juego.jugadores[juego.turnoActual].direccionActual);
		}
		if (juego.tablero[pos.x][pos.y].estado == HIELO){
			juego.tablero[pos.x][pos.y].estado = VACIA;
		}
	}
}

bool accionRobar(tJuego &juego){
	bool robar = false;
	bool top = false;
	tCarta carta;
	if (sacar(juego.jugadores[juego.turnoActual].mazo, top, carta)){
		if (carta == AVANZAR){
			juego.jugadores[juego.turnoActual].jugada.avanzar++;//llamamos a la funcion de Secuencia
		}
		if (carta == GIRO_IZQUIERDA){
			juego.jugadores[juego.turnoActual].jugada.giroIzquierda++;
		}
		if (carta == GIRO_DERECHA){
			juego.jugadores[juego.turnoActual].jugada.giroDerecha++;
		}
		if (carta == LASER){
			juego.jugadores[juego.turnoActual].jugada.laser++;
		}
		robar = true;
	}
	return robar;
	
}

bool accionSecuencia(tJuego &juego, tMazo &cartas){
	bool joya = false;
	tCasilla posicionsiguiente;
	int i = 0;
	while (i < cartas.numCartas && joya == false){
		if (cartas.cartas[i] == AVANZAR){
			joya = avanzarTortuga(juego);
			/* Aqui no quitamos la carta de avanza de la mano del jugador porque no sabemos si se ha realizado el movimiento,
			la restamos en la funcion de avanza, comprobando anteriormente el tablero*/
		}
		if (cartas.cartas[i] == LASER){
			lanzarLaser(juego);
			juego.jugadores[juego.turnoActual].jugada.laser--;

		}
		if (cartas.cartas[i] == GIRO_IZQUIERDA){
			girarTorturaIzquierda(juego);
			juego.jugadores[juego.turnoActual].jugada.giroIzquierda--;

		}
		if (cartas.cartas[i] == GIRO_DERECHA){
			girarTorturaDerecha(juego);
			juego.jugadores[juego.turnoActual].jugada.giroDerecha--;

		}
		i++;
	}
return joya;
}

void cambiarTurno(tJuego &juego){
	
	if (juego.turnoActual < juego.numJugadores){
		juego.turnoActual++;
	}
	if (juego.turnoActual == juego.numJugadores){
		juego.turnoActual = 0;
	}
}

void incluirCarta(tMano &mano, tCarta carta){

	if (carta == AVANZAR){
	mano.avanzar++;
	}
	else if (carta == GIRO_DERECHA){
	mano.giroDerecha++;
	}
	else if (carta == GIRO_IZQUIERDA){
	mano.giroDerecha++;
	}
	else {
	mano.laser++;
	}

	}

bool comprobarCondicionSecuencia(int numCartas, int numAvanzar, int numGiroIzquierda, int numGiroDerecha, int numLaser, tMazo mimazo){
	bool comprobacion = false; //si un movimiento es erroneo, se cancela toda la secuencia y se pasa el turno
	int i = 0;
	while (i < mimazo.numCartas){
		if (mimazo.cartas[i] == AVANZAR){
			if (numAvanzar > 0){
				comprobacion = true;
				numAvanzar--;
			}
		}
		if (mimazo.cartas[i] == GIRO_DERECHA){
			if (numGiroDerecha > 0){
				comprobacion = true;
				numGiroDerecha--;
			}
		}
		if (mimazo.cartas[i] == GIRO_IZQUIERDA){
			if (numGiroDerecha > 0){
				comprobacion = true;
				numGiroIzquierda--;
			}
		}
		if (mimazo.cartas[i] == LANZAR_LASER){
			if (numLaser > 0){
				comprobacion = true;
				numLaser--;
			}
		}
		i++;
	}
	return comprobacion;

}

void intercamBiarCasillas(tJuego &juego, tCoordenada origen, tCoordenada destino){

	tEstadoCasilla estado;
	estado = juego.tablero[destino.x][destino.y].estado; //lo guardamos en una constante aparte para no perder ese estado
	juego.tablero[destino.x][destino.y].estado = juego.tablero[origen.x][origen.y].estado;
	if (juego.tablero[destino.x][destino.y].estado == TORTUGA){
		juego.tablero[destino.x][destino.y].tortuga.direccion = juego.tablero[origen.x][origen.y].tortuga.direccion;
		juego.tablero[destino.x][destino.y].tortuga.numero = juego.tablero[origen.x][origen.y].tortuga.numero;
	}
	juego.tablero[origen.x][origen.y].estado = estado;
		
}

bool casillaEnTablero(tCoordenada casilla){
	bool dentro = false;
	if ((0 < casilla.x < 7) && (0 < casilla.y < 7)){
		dentro = true;
	}
	return dentro;
}

tCoordenada siguienteCasilla(tCoordenada origen, tDir direccion){
	tCoordenada final;
	
	if (direccion == NORTE){
		origen.x--;	
		origen.y;
		final = origen;
		}
	if (direccion == SUR){
		origen.x++;
		origen.y;
		final = origen;
	}
	if (direccion == ESTE){
		origen.x;
		origen.y++;
		final = origen;
	}
	if (direccion == OESTE){
		origen.x;
		origen.y--;
		final = origen;
	}

	return final;
}

void colorFondo(int colorFondo){ 
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE); 
	SetConsoleTextAttribute(handle, 15 | (colorFondo << 4));
}
