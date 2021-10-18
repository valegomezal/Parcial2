#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "funcionesmatrices.h"
#include "ctime.h"

#define SIZE_DATA (1024*1024*64*3)

static double MEM_CHUNK[SIZE_DATA];

// Estrategia declaración de todas las variables de forma global

int N, numThreads;
double *matrizA, *matrizB, *matrizC;

void * multiplicacionMatricesT(void *arg) {
        
	int i, j, k; // contadores
	int idThreads; // identificador del hilo
	int porcion; // porción de la matriz A a enviar
	int inicioFila, finFila; // inicio y fin de la porción de la matriz A
	
	idThreads 	= *((int *) (arg)); // Se obtiene el identificador del hilo secuencialmente
	porcion 	= N/numThreads; // Porcion a computar 
	inicioFila 	= idThreads*porcion;
	finFila 	= (idThreads+1)*porcion;
 
	for (i=inicioFila; i<finFila; i++)
        	for (j=0; j<N; j++) {
                          double *ptrA, *ptrB, suma = 0.0;
                          ptrA = matrizA+(i*N);   // Fila
                          ptrB = matrizB+j;       // Columna
                          for (k=0; k<N; k++, ptrA++, ptrB+=N)
                                  suma += (*ptrA * *ptrB);
                          matrizC[(i*N)+j] = suma;
                }
	return 0;
}

int main(int argc, char **argv) {
	// ** -->doble puntero
	
	int cT; // contador general de hilos
	pthread_t * hilos; // declarando apuntadores a hilo (posix)

       	N = (int) atof(argv[1]);
       	numThreads = (int) atof(argv[2]);

	matrizA = MEM_CHUNK;
	matrizB = matrizA + (N*N);
	matrizC = matrizB + (N*N);

	matrizInit(N, matrizA, matrizB, matrizC);

	/*printf("Impresión Matriz A:\n");
	imprimirMatriz(N, matrizA);

	printf("Impresión Matriz B:\n");
	imprimirMatriz(N, matrizB);*/

	sampleStart();
	
	// Declaración de hilos y asignación de memoria
	hilos = (pthread_t *) malloc(numThreads*sizeof(pthread_t));
	// Se reparte el trabajo invocando cada hilo
	for (cT=0; cT<numThreads; cT++) {
		int *tID; // puntero identificador del hilo
		tID = (int *) malloc(sizeof(int));
		*tID = cT; // se apunta al contador general de hilo
		pthread_create(&hilos[cT], NULL, multiplicacionMatricesT, (void *) tID);
	}
	
	// Espera a que todos los hilos terminen al tiempo (sincronización)
	for (cT=0; cT<numThreads; cT++) {
		pthread_join(hilos[cT], NULL);
	}

	sampleStop();
	printTime();

	return 0;
}
