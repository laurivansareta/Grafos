#include <stdio.h>
#include <stdlib.h>

#define VERTICES 8
#define INFINITO 10000000
#define BRANCO 0
#define CINZA 1
#define PRETO 2

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
void ImprimeMatriz();
void ImprimeDados();

void BFS(int A, int VAtual);

void inicializa(int VInicial);
void processaAdjacentes(int VAtual);
void processaBranco(int VAtual, int VAnterior);

int main(int argc, char *argv[]) {
	ImprimeMatriz();
	BFS(0,0);
	ImprimeDados();
	ImprimeFita();
	return 0;
}

void BFS(int A, int VAtual){
	int processando=-1;
	inicializa(VAtual);
	Empilha(VAtual);
	
	do{
		processando = Desempilha();
		processaAdjacentes(processando);		
	} while (processando != -1);
}

void processaBranco(int VAtual, int VAnterior){
	cor[VAtual] = CINZA;
	distancia[VAtual] = distancia[VAnterior] + 1;
	anterior[VAtual] = VAnterior;
	Empilha(VAtual);
}

void processaAdjacentes(int VAtual){
	int i;
	for (i=0; i < tamFita; i++){
		if (cor[i] == BRANCO){
			processaBranco(i, VAtual);	
		}
	}
	cor[VAtual] = PRETO;
}

void inicializa(int VInicial){
	int i;
	for (i=0; i < VERTICES; i++){
		distancia[i] = INFINITO;
		anterior[i] = -1;
		cor[i] = BRANCO;
	}
	
	tamFita = 0;
	
	//primeira distância é zero
	distancia[VInicial] = 0;
	anterior[VInicial] = 0;
	cor[VInicial] = CINZA;
	
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

void ImprimeMatriz(){
	int i, j;
	printf("\n-------------MATRIZ----------------");
	for (i=0; i<VERTICES; i++){
		printf("\n");
		for (j=0; j<VERTICES; j++){
			printf(" |%d|", grafo[i][j]);
		}			
	}	
	printf("\n-----------------------------");
}

void ImprimeDados(){
	int i;
	printf("\n------DADOS---------\n");
	for (i=0; i<VERTICES; i++){
		printf("Distancia: |%d| ", distancia[i]);
		printf("anterior: |%d| ", anterior[i]);
		printf("Cor: |%d| ", cor[i]);
		
		printf("\n");
	}
	printf("\n---------------");
}

void ImprimeFita(){
	int i;
	printf("\n Fita: ");
	
	for(i=0; i < tamFita; i++){
		printf("%d, ", fita[i]);
	}
}
