#include <stdio.h>
#include <stdlib.h>

#define VERTICES 8

int grafo[VERTICES][VERTICES] = { { 0, 7, 0, 5, 0, 0, 0} ,
								  { 7, 0, 8, 9, 7, 0, 0},
								  { 0, 8, 0, 0, 5, 0, 0},
								  { 5, 9, 0, 0,15, 6, 0},
								  { 0, 7, 5,15, 0, 8, 9},
								  { 0, 0, 0, 6, 8, 0,11},
								  { 0, 0, 0, 0, 9,11, 0},
								  { 0, 0, 0, 0, 9,11, 0}};
								
int distancia[VERTICES];
int anterior[VERTICES];
int cor[VERTICES];

int *fita=NULL;
int tamFita=0;

void Empilha(int VerticeEmp);
int Desempilha();

void ImprimeFita();


int main(int argc, char *argv[]) {
	ImprimeFita();
	Empilha(1);
	Empilha(3);
	Empilha(2);
	Empilha(4);
	ImprimeFita();
	return 0;
}

int Desempilha(){
	int i,primeiro,temp;
	primeiro=-1;
	
	for (i=0, temp=-1; i<tamFita; i++){
		if (i==0){
			primeiro= fita[0];
		}
		fita[i] = fita[i+1];
	}
	
	if (tamFita > 0){
		tamFita--;
		fita = realloc(fita, (tamFita * sizeof(int)));
	}
	return primeiro;
}

void Empilha(int VerticeEmp){
	int novoTam = tamFita + 1;
	if (!fita ){
		fita = (int *)malloc(novoTam * sizeof(int));
	}else{
		fita = (int *)realloc(fita, (novoTam * sizeof(int)));	
	}
		
	fita[novoTam-1] = VerticeEmp;
	tamFita++;
}

void ImprimeFita(){
	int i;
	printf("\n Fita: ");
	
	for(i=0; i < tamFita; i++){
		printf("%d, ", fita[i]);
	}
}
