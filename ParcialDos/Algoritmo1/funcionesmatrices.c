#include <stdio.h>
#include "funcionesmatrices.h"

void matrizInit(int N, double *matrizA, double *matrizB, double *matrizC) {
	for (int i=0; i<N; i++) 
		for (int j=0; j<N; j++) {
			matrizA[j+(i*N)] = 2.0*(i+j);
			matrizB[j+(i*N)] = 3.2*(i+j);
			matrizC[j+(i*N)] = 1.0;
		}
}

void multiplicacionMatrices(int N, double *matrizA, double *matrizB, double *matrizC) {
	for (int i=0; i<N; i++)
		for (int j=0; j<N; j++) {
			double *ptrA, *ptrB, suma = 0.0;
			ptrA = matrizA+(i*N); 	// Fila
			ptrB = matrizB+j;	// Columna
			for (int k=0; k<N; k++, ptrA++, ptrB+=N)
				suma += (*ptrA * *ptrB);
			matrizC[(i*N)+j] = suma;
		}
}

void imprimirMatriz(int N, double *matriz) {
	for (int i=0; i<N; i++) {
		for (int j=0; j<N; j++)
			printf("%f\t", matriz[j+(i*N)]);
		printf("\n");
	}
}

