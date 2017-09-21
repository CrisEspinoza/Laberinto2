#include <stdio.h>
#include "struct.h"
#include <string.h>
#include <stdlib.h>

// Variables que se declaran fuera de las funciones, denominadas variables globales.
int CONTUNI = 0;
int CONTCERRADOS = 0;
int ORIGEN = 0 ;
int ENTRADA = 0;
int CONACTUAL = 0;
int BANDERA = 0;
int RECORRIDO = 0;
int VUELTA = 0;

Lista* crearLista() // Creamos la lista nueva 
{
    Lista* lista = (Lista*)malloc(sizeof(Lista)); // Pedimos memoria para la nueva lista 
    lista->primero = NULL; // Declaramos 
    lista->ultimo = NULL; // El ultimo elemento de la lista apunta a NULL, ya que no contiene elementos en la Lista
    lista->largo = 0 ; // El largo de la lista es igual a "0".
    return lista; // Se retorna la lista creada
}

Nodo* crearNodo(char direccion[], int fila, int columna)
{
    Nodo* nuevoNodo = (Nodo*)malloc(sizeof(Nodo)); // Pedimos memoria para el nuevo nodo declarado
    if (nuevoNodo != NULL)
    {
        nuevoNodo->camino = (char*)malloc(sizeof(char)*20); // Pedimos memoria para lo que contiene la matriz y es un char
        nuevoNodo->camino = direccion; // Asignamos lo que recibe la funcion a la variable direccion
        nuevoNodo->fila = fila; // Asignamo el valor de file que recibe a lo que pertenece a la estructura
        nuevoNodo->columna = columna; // Asignamos el valor de columna que recibe a lo que pertenece a ala estructura
        nuevoNodo->siguiente = NULL; // Se declara NULL le siguiente nodo ya que no apunta a nada.
    }
    return nuevoNodo; // Se retorna el nuevo nodo creado
}

Lista* agregarNodo(Lista* lista , Nodo* nodo)
{
    if(lista->primero == NULL) // En el caso que la lista tenga solamente largo 1
    {
        lista->primero = nodo; // Agregamos a la posicion 0
        lista->primero->siguiente = lista->primero; // Agregamos el valor anterior a la posición 1 de la lista 
        lista->ultimo = lista->primero; // el ultimo elemento de la lista va a ser el primero de la anterior
    }
    else
    {
        lista->ultimo->siguiente = nodo; // Dejamos declarado que ya el ultimo no apunta a nulo, si no que apunta al nodo siguiente
        nodo->siguiente = lista->primero; // El siguiente noso va a ser el primero que se encuentra en la lista
        lista->ultimo = nodo; // El ultimo nodo sera ahora el que se va agregar 
    }

    return lista; // Retornamos la lista
}

Nodo* buscarNodo(Lista* lista, int numero)
{
    int contador  = 0;
    if (numero >= lista->largo) 
    {
        while (contador != numero)
        {
            lista->primero = lista->primero->siguiente; // Avanzamos en la lista para seguir verificando si se encuentra el elemento
            contador++;
        }
    return lista->primero; // Devuelve el nodo que cumple la condicion
    }
    return NULL; // En caso que no se encuentre retornamos NULL
}

Lista* crearRuta ()
{
    Lista* ruta = crearLista(); // Definimos la lista de la rutas posibles dentro del laberinto
    // Creamos los nuevos nodos que tendran las rutas posibles dentro del laberinto
    Nodo* nuevo = crearNodo("Abajo",1,0); 
    Nodo* nuevo1 = crearNodo("Arriba",-1,0);
    Nodo* nuevo2 = crearNodo("Derecha",0,1);
    Nodo* nuevo3 = crearNodo("Izquierda",0,-1);
    // Agregamos las rutas a la lista declarada anteriormente
    ruta = agregarNodo(ruta,nuevo);
    ruta = agregarNodo(ruta,nuevo1); 
    ruta = agregarNodo(ruta,nuevo2);
    ruta = agregarNodo(ruta,nuevo3);
    return ruta; // Devolvemos la lista con las rutas posibles dentro del laboratorio
}

Tablero *cargar(char nombre[])
{
    FILE *archivo; // Declaramos un puntero File para poder leer el archivo de ENTRADA.

    archivo = fopen (nombre, "r"); // Estamos abriendo el archivo en modo lectura

    Tablero *matriz; // Declaramos un variable de tipo de la structura tablero.
    int caracter;

    //Verificamos si el archivo se encuentra nulo
    if( archivo == NULL)
    {
        printf("Error al abrir archivo \n");
        return 0;
    }
    
    int fila,columna;
    fscanf(archivo, "%d %d", &fila, &columna); //Primero leemos las dimensiones del tablero.

    matriz = createBoard(fila,columna); //Creamos un tablero con las dimensiones que tendra el tablero

    while(getc(archivo) != '\n'); // Que lea el archivo siempre y cuando no sea un salto de linea

    int i,j;

    for(i = 0; i < matriz->fila; i++)
    {
        for(j = 0; j <= matriz->columna; j++)
        {
            matriz->mapa[i][j] = getc(archivo); // Cada caracter que lea sera almacenado en la variable de tipo (struct Tablero)
        }

        char c;
        while((c = getc(archivo)) == '\n' || c == '\r');
        fseek(archivo, -1, SEEK_CUR);
    }

    fclose(archivo); // Cerramos el archivo
 
    return matriz; //Retornamo la variable matriz, con el tablero contenido, el cual se leyó desde el archivo ingresado
}

void print(Tablero *matriz)
{
    for (int i = 0; i < matriz->fila; i++)
    {
        for (int j = 0; j < matriz->columna; j++)
        {
            printf("%c", matriz->mapa[i][j]); //Imprimos por pantalla cada una de las caracteristicas que guarda dentro de si el tablero
        }
        printf("\n");
    }
}

Tablero* createBoard(int n,int m)
{
    int i,j;
    // Procedemos a crear una variable de tipo Tablero y a solicitar memoria para dicha variable
    Tablero *matriz;
    matriz = (Tablero*)malloc(sizeof(Tablero));

    matriz->mapa = (char**)malloc(n*sizeof(char*)); // Inicializamos una de variables que contiene nuestra estructura con tantas filas diga el archivo
    matriz->fila = n;
    matriz->columna = m;

    for (i=0; i<n ;i++)
    {
        matriz->mapa[i] = (char*)malloc(m*sizeof(char)); // Aca inicializamos las columnas que rescatamos desde el archivo

        for (j=0; j<m ;j++)
        {
            matriz->mapa[i][j] = 'X'; // Asignamos un elemento neutro que demostrara que el tablero esta creado pero no utilizado 
        }
    }

    return matriz; // retornamos el tablero inicilizado (con elemento que representa estar vacio)
}

int *buscarPos(Tablero *mapa, char busca)
{
    // Inicializamos la variable de tipo Tablero y solicitamos memoria para dicha variable
    Tablero *matriz;
    matriz = (Tablero*)malloc(sizeof(Tablero));

    matriz = mapa; //Hacemos un asignacion respecto a la variable que estan pasando como parametro 
    // Declaramos un arreglo de interos para almacenar la posicion donde se encontrara la posicion que andamos buscando
    int *arreglo; 
    arreglo = (int*)malloc(sizeof(int)*3);
    int i,j;
    // Almacenamos el caracter que andamos buscando dentro de la matriz
    char e;
    e = busca;

    for (i=0; i<matriz->fila ;i++)
    {
        for (j=0; j<matriz->columna ;j++)
        {
            if(matriz->mapa[i][j] == e)
            {
                // Si cumple todas las condiciones anteriores, almacenados las posiciones de donde se encuentra el caracter que andamos buscando
                arreglo[0] = i;
                arreglo[1] = j;
            }
        }
    }

    return arreglo; //Retornamos el arreglo que contiene las posiciones donde se encuentra el caracter que andamos buscando.
}

int noEstarCerrado(int fila, int columna,Tablero *campo,Position *cerrados)
{
    // Inicializamos una variable de tipo Tablero y a la misma ves pedimos memoria para dicha variable y le asignamos el parametro que recibe
    Tablero *matriz;
    matriz = (Tablero*)malloc(sizeof(Tablero));
    matriz = campo;
    // Inicialamos una variable de tipo Position, luego pedimos memoria y la asignamos a la variable que se esta pasando como parametro.
    Position *estadosCerrados;
    estadosCerrados = (Position*)malloc(sizeof(Position)*(matriz->fila*matriz->columna)); 
    estadosCerrados = cerrados;

    for (int i = 0; i < CONTCERRADOS; i++)
    {
        if (estadosCerrados[i].columna == columna && estadosCerrados[i].fila == fila) //En caso qe estas sean iguales
        {
            return 0; // Retornamos un 0, verificando que si se encuentra dentro del arreglos de estados cerrados
        }
    }

    return 1; // Si no se encuentra devolvemos un 1, que significa que dicha posicion no se encuentra en estados cerrados
}

int buscarCamino (Tablero *campo, Position *Actuales, Position *Cerrados, Position *Pendientes, int* posicion , char obj , int* posobj ) 
{
    // Inicializamos una variable de tipo Tablero y a la misma ves pedimos memoria para dicha variable y le asignamos el parametro que recibe
    Tablero *matriz;
    matriz = (Tablero*)malloc(sizeof(Tablero));
    matriz = campo;

    int j,i;

    char objetivo;
    objetivo = obj;
    // Inicialamos una variable de tipo Position, luego pedimos memoria y la asignamos a la variable que se esta pasando como parametro.
    Position *estadosPendientes;
    Position *estadosCerrados;
    Position *estadosActuales;
    Position *caminoC;
    Position *caminoaux;

    int* posicionActual = posicion;
    int* posobjetivo = posobj;

    estadosActuales = (Position*)malloc(sizeof(Position)*(matriz->fila*matriz->columna));
    estadosCerrados = (Position*)malloc(sizeof(Position)*(matriz->fila*matriz->columna));    
    estadosPendientes = (Position*)malloc(sizeof(Position)*(matriz->fila*matriz->columna));
    caminoC = (Position*)malloc(sizeof(Position)*(matriz->fila*matriz->columna));
    caminoaux = (Position*)malloc(sizeof(Position)*(matriz->fila*matriz->columna));

    Lista* ruta = crearRuta();

    /*for (int z = 0 ; z < matriz->fila*matriz->columna; z++)
    {
        estadosPendientes[z] = Pendientes[z];
        estadosCerrados[z] = Cerrados[z];
        estadosActuales[z] = Actuales[z];
    }*/

    estadosPendientes = Pendientes;
    estadosCerrados = Cerrados;
    estadosActuales = Actuales;

    if (ENTRADA == 0)
    {
        estadosActuales[ORIGEN].fila = posicionActual[0];        
        estadosActuales[ORIGEN].columna = posicionActual[1];
        estadosActuales[ORIGEN].origen = ORIGEN;
        ENTRADA = 1 ;
    } 

    while(matriz->mapa[estadosActuales[ORIGEN].fila][estadosActuales[ORIGEN].columna] != objetivo)
    {
        for (i = 0; i < 4; i++)
    {
        Nodo* aux = buscarNodo(ruta,i);
        if ( (estadosActuales[ORIGEN].fila + aux->fila) >= 0 && (estadosActuales[ORIGEN].columna + aux->columna) >= 0 )
        {    
            if ( (estadosActuales[ORIGEN].fila + aux->fila) < matriz->fila && (estadosActuales[ORIGEN].columna + aux->columna) < matriz->columna )  
            {   
                if(matriz->mapa[(estadosActuales[ORIGEN].fila + aux->fila)][(estadosActuales[ORIGEN].columna + aux->columna)] != '*')
                {
                    if (noEstarCerrado( (estadosActuales[ORIGEN].fila + aux->fila) ,(estadosActuales[ORIGEN].columna + aux->columna) , matriz , estadosCerrados ) == 1 )
                    {
                        // Gregamos el nuevo estado abierto a los estados pendientes para que sean abiertos en su momento, ademas de agregar quine lo abrio
                        estadosPendientes[CONTUNI].fila = (estadosActuales[ORIGEN].fila + aux->fila);
                        estadosPendientes[CONTUNI].columna = (estadosActuales[ORIGEN].columna + aux->columna); 
                        estadosPendientes[CONTUNI].origen = ORIGEN;
                        estadosPendientes[CONTUNI].camino = (char*)malloc(sizeof(char)*25);
                        estadosPendientes[CONTUNI].camino = aux->camino;
                        // Aumentamos el contador para no sobreescribir ningun estado pendiente
                        CONTUNI++;
                    }
                }
            }
        }

        // Las siguientes 4 condiciones es para que el laberinto pueda ser de una manera circular.

        if ((estadosActuales[ORIGEN].fila + aux->fila) == matriz->fila)
        {
            if ( matriz->mapa[0][(estadosActuales[ORIGEN].columna + aux->columna)] != '*')
            {
                estadosPendientes[CONTUNI].fila = 0;
                estadosPendientes[CONTUNI].columna = (estadosActuales[ORIGEN].columna + aux->columna); 
                estadosPendientes[CONTUNI].origen = ORIGEN;
                estadosPendientes[CONTUNI].camino = (char*)malloc(sizeof(char)*25);
                estadosPendientes[CONTUNI].camino = aux->camino;             
                CONTUNI++;            
            }
        }

        if ((estadosActuales[ORIGEN].columna + aux->columna) == matriz->columna)
        {
            if ( matriz->mapa[estadosActuales[ORIGEN].fila + aux->fila][0] != '*')
            {
                estadosPendientes[CONTUNI].fila = estadosActuales[ORIGEN].fila + aux->fila;
                estadosPendientes[CONTUNI].columna = 0; 
                estadosPendientes[CONTUNI].origen = ORIGEN;
                estadosPendientes[CONTUNI].camino = (char*)malloc(sizeof(char)*25);
                estadosPendientes[CONTUNI].camino = aux->camino;
                CONTUNI++;
            }   
        }

        if ((estadosActuales[ORIGEN].fila + aux->fila) == -1)
        {
            if ( matriz->mapa[(matriz->fila) - 1][estadosActuales[ORIGEN].columna + aux->columna] != '*')
            {
                estadosPendientes[CONTUNI].fila = (matriz->fila) - 1;
                estadosPendientes[CONTUNI].columna = estadosActuales[ORIGEN].columna + aux->columna; 
                estadosPendientes[CONTUNI].origen = ORIGEN;
                estadosPendientes[CONTUNI].camino = (char*)malloc(sizeof(char)*25);
                estadosPendientes[CONTUNI].camino = aux->camino;
                CONTUNI++;
            }
        }

        if ((estadosActuales[ORIGEN].columna + aux->columna) == -1)
        {
            if ( matriz->mapa[estadosActuales[ORIGEN].fila + aux->fila][(matriz->columna) - 1] != '*')
            {
                estadosPendientes[CONTUNI].fila = estadosActuales[ORIGEN].fila + aux->fila;
                estadosPendientes[CONTUNI].columna = (matriz->columna) - 1; 
                estadosPendientes[CONTUNI].origen = ORIGEN;
                estadosPendientes[CONTUNI].camino = (char*)malloc(sizeof(char)*25);
                estadosPendientes[CONTUNI].camino = aux->camino;
                CONTUNI++;
            }
        } 
    }

    

    // Aca declaramos el nuevo estado cerrado
    estadosCerrados[CONTCERRADOS].fila = estadosActuales[ORIGEN].fila;
    estadosCerrados[CONTCERRADOS].columna = estadosActuales[ORIGEN].columna;
    ORIGEN++;
    // Cambiamo el estado estado actual y colocamos el ORIGEN desde donde proviene, ademas de aumentar el ORIGEN para que cada estado actual tena un ORIGEN distinto.
    estadosActuales[ORIGEN].fila = estadosPendientes[CONTCERRADOS].fila;
    estadosActuales[ORIGEN].columna = estadosPendientes[CONTCERRADOS].columna;
    estadosActuales[ORIGEN].origen = ORIGEN;
    estadosActuales[ORIGEN].camino = (char*)malloc(sizeof(char)*25);
    estadosActuales[ORIGEN].camino = estadosPendientes[CONTCERRADOS].camino;
    estadosPendientes[CONTCERRADOS].estado = 1; 
    // Aumentamos el contador de estados cerrados para asi no sobreescribir ninguno
    CONTCERRADOS++;
    }
    caminoCorrec(estadosPendientes, estadosActuales,campo,posicionActual,caminoC);    

    return 1;
}

void caminoCorrec (Position *pendiente, Position *actuales, Tablero *campo, int* posicion, Position *caminoC) 
{
    // Inicializamos una variable de tipo Tablero y a la misma ves pedimos memoria para dicha variable y le asignamos el parametro que recibe
    Tablero *matriz;
    matriz = (Tablero*)malloc(sizeof(Tablero));
    matriz = campo;
    // Inicializamos y soliciamos memoria para una variable de tipo Position, ademas le asiganmos la variable que se recibe como parametro.
    Position *estadosPendientes;
    Position *estadosActuales;
    Position *caminoFinal;
    int* posicionActual = posicion;


    estadosActuales = (Position*)malloc(sizeof(Position)*(matriz->fila*matriz->columna));
    estadosPendientes = (Position*)malloc(sizeof(Position)*(matriz->fila*matriz->columna));
    caminoFinal = (Position*)malloc(sizeof(Position)*(matriz->fila*matriz->columna));
    // asiganmos cada uno de los estados a las variables que se estan recibiendo como parametros
    estadosPendientes = pendiente;
    estadosActuales = actuales;
    caminoFinal = caminoC;   
    // Agregamos el primero estado al RECORRIDO final, ya que desde ahi parte el camino correcto hacia el objetivo que se desea
    if (BANDERA == 0 )
    {
        caminoFinal[RECORRIDO].fila = estadosActuales[ORIGEN].fila;
        caminoFinal[RECORRIDO].columna = estadosActuales[ORIGEN].columna;
        caminoFinal[RECORRIDO].camino = (char*)malloc(sizeof(char)*25);
        caminoFinal[RECORRIDO].camino = estadosActuales[ORIGEN].camino;
        BANDERA = 1;
    }

    if (caminoFinal[RECORRIDO].fila == posicionActual[0] && caminoFinal[RECORRIDO].columna == posicionActual[1])
    {
        // Reiniciamos todas las variables globales que se ocuparon para asi volver a buscar en otra oprtunidad.
        CONTUNI = 0;
        CONTCERRADOS = 0;
        ORIGEN = 0 ;
        ENTRADA = 0;
        CONACTUAL = 0;
        BANDERA = 0;      
        // Hacemos el llamado a la funcion que se encarga de escribir el camino correcto dentro del archivo
        saveTablero (matriz,caminoFinal,"Salida.out");
        // Agregamos este contador para saber de que manera abrir el archivo, para no perder informacino dentro del archivo
        VUELTA++;
        RECORRIDO = 0;
    }

    else 
    {
        for (int i = 0; i <= CONTUNI; i++)
        {
            if (estadosActuales[i].fila == caminoFinal[RECORRIDO].fila && estadosActuales[i].columna == caminoFinal[RECORRIDO].columna)
            {
                for (int j = 0; j <= CONTUNI; j++)
                {
                    if (estadosActuales[i].fila == estadosPendientes[j].fila && estadosActuales[i].columna == estadosPendientes[j].columna) 
                    {
                        for (int z = 0; z < CONTUNI; z++)
                        {
                            if (estadosPendientes[j].origen == estadosActuales[z].origen) 
                            {
                                // Aumentamos para asi no sobreescribir ninguna posiciones que lleva al camino hacia el objetivo 
                                RECORRIDO++;
                                // Si cumple las condiciones finales agregamos a la lista de camino correcto las posiciones que sirven para llegar al objetivo
                                caminoFinal[RECORRIDO].fila = estadosActuales[z].fila;
                                caminoFinal[RECORRIDO].columna = estadosActuales[z].columna;
                                caminoFinal[RECORRIDO].camino = (char*)malloc(sizeof(char)*25);
                                caminoFinal[RECORRIDO].camino = estadosActuales[z].camino;
                                // Hacemos el llamado recursivo hasta encontrar el camino final para el objetivo
                                
                                caminoCorrec (estadosPendientes,estadosActuales,matriz,posicionActual,caminoFinal);
                            }
                        }
                    }
                }
            }
        }
    }
}

void saveTablero (Tablero *campo, Position* camino1, char nombre[])
{    
    // Incializamos y solicitamos memoria para una variable de tipo Tablero, ademas le asiganamos la variable que recibimos como parametro
    Tablero *matriz;
    matriz = (Tablero*)malloc(sizeof(Tablero));
    matriz = campo;
    // Inicializamos y soliciamos memoria para una variable de tipo Position, ademas le asiganmos la variable que se recibe como parametro.
    Position *camino;
    camino = (Position*)malloc(sizeof(Position)*(matriz->fila*matriz->columna));
    camino = camino1;

    FILE *txt;  // Incialzamos una variable de tipo FILE para poder trabajar con los archivos

    // Hacemos una comparacion para verificar si es el primero o segundo camino que se esta recibiendo 
    if (VUELTA == 0) 
    {
        txt = fopen(nombre, "wt"); // Abrimos le archivo en modo escritura y que se cree si no exite el archivo nombrado
    }

    else
    {
        txt = fopen(nombre, "a"); // Abrimos el archivo en modo sobreescritura, para no perder el camino anterior que esta en el archivo
        fprintf(txt,"\n");
        fprintf(txt,"\n");
    }

    for (int i = 0; i< matriz->fila ; i++)
    {
        for(int j = 0; j< matriz->columna ; j++)
        {
            if (verificar(matriz,camino,i,j) == 1)
            {
                fprintf(txt,"X"); // Escribimos con una X, si es camino se encuentra dentro del arreglo camino
            }
            else
            {
                fprintf(txt,"%c",matriz->mapa[i][j]); // En caso contratio escribimos lo que se enceuntre en esa posicion
            }
        }

        fprintf(txt,"\n"); // Para poder dar la forma de un tablero
    }

    for (int i = RECORRIDO ; i >= 0 ; i--)
    {
        fprintf(txt,"%s",camino[i].camino);
        fprintf(txt,"\n");
    }

    fclose(txt); // Cerramos el archivo
}

int verificar (Tablero *campo, Position *camin,int fila , int columna)
{   
    //Inicializamos la variable de tipo Tablero y pedimos memoria para dicha variable, ademas asignamos la variable que esta recibiendo como parametro
    Tablero *matriz;
    matriz = (Tablero*)malloc(sizeof(Tablero));
    matriz = campo;

    // Inicializamos una variable de tipo Position y solicitamos memoria para dicha variable, ademas le asignamos la varable que recibe como parametro la funcion.
    Position *camino;
    camino = (Position*)malloc(sizeof(Position)*(matriz->fila*matriz->columna));
    camino = camin;

    for (int i = 0; i <= RECORRIDO; i++)
    {
        if (fila == camino[i].fila && columna == camino[i].columna) // Verificamos si las posiciones pasadas como parametros pertenecen alguna del arreglo camino
        {
            return 1; // En caso verdadero se devuelve un 1, representado que se encuentra dentro del arreglo
        }              
    }

    return 0; // En caso que no se encuentre devolvemos un 0, demostrando que no se encuentre dentro del arreglo camino
}