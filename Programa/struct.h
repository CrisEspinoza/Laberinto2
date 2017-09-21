#include <stdio.h>
#include <string.h>

// Definimos las estructuras a ocupar dentro de la aplicacion

typedef struct{

	int fila;
	int columna;
	char **mapa;

}Tablero;

typedef struct{

	int fila;
	int columna;
	int origen;
	int estado;
	char* camino;

}Position;


typedef struct Nodo{
	char* camino;
	int fila;
	int columna;
	struct Nodo* siguiente;
}Nodo;

typedef struct{
	int largo;
	Nodo* primero;
	Nodo* ultimo;	
}Lista;


// Declaramos cada una de las funciones que se encuentran dentro de la aplicacion.
Tablero *cargar(char nombre[]);
void print(Tablero *b);
Tablero* createBoard(int n,int m);
int buscarCamino (Tablero *campo, Position *Actuales, Position *Cerrados, Position *Pendientes, int* posicion , char obj , int* posobj );
int *buscarPos(Tablero *mapa, char busca);
void caminoCorrec (Position *pendiente, Position *actuales, Tablero *campo, int* posicion, Position *caminoC);
void saveTablero (Tablero *campo, Position* camino1, char nombre[]);
int verificar (Tablero *campo, Position *camin,int fila , int columna); 
Lista* crearLista();
Nodo* crearNodo(char direccion[], int fila, int columna);
Lista* agregarNodo(Lista* lista , Nodo* nodo);
Nodo* buscarNodo(Lista* lista, int numero);