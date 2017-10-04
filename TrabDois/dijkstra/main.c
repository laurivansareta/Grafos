#include <stdio.h>
#include <stdlib.h>

#define VERTICES 7
#define INFINITO 10000000

int grafo[VERTICES][VERTICES] = { { 0, 7, 0, 5, 0, 0, 0} ,
								  { 7, 0, 8, 9, 7, 0, 0},
								  { 0, 8, 0, 0, 5, 0, 0},
								  { 5, 9, 0, 0,15, 6, 0},
								  { 0, 7, 5,15, 0, 8, 9},
								  { 0, 0, 0, 6, 8, 0,11},
								  { 0, 0, 0, 0, 9,11, 0}};
								
int distancia[VERTICES];
int anterior[VERTICES];
int aberto[VERTICES];

void Inicializa();
void Dijkstra(int inicio);
void ImprimeMatriz();
void ImprimeDados();
void CalculaArestasVerticeAtual(int VAtual, int VInicial);
int CalculaMinimo(int VAtual, int VInicial);
void ImprimeCaminho(int Inicial, int Final);

								

int main(int argc, char *argv[]) {
	ImprimeMatriz();
	Dijkstra(0);
	ImprimeDados();
	ImprimeCaminho(0, 6);
	return 0;
}

void inicializa(int inicio){
	int i;
	for (i=0; i < VERTICES; i++){
		distancia[i] = INFINITO;
		anterior[i] = -1;
		aberto[i] = 1;
	}
	//primeira dist�ncia � zero
	distancia[inicio] = 0;
	aberto[inicio] = 0;
	anterior[inicio] = -1;
	
}

void Dijkstra(int inicio){	
	int i,j, VAtual;
		
	inicializa(inicio);
	
	VAtual = inicio;
	
	while(VAtual != -1){		
		VAtual = CalculaMinimo(VAtual, inicio);
	}
}

void CalculaArestasVerticeAtual(int VAtual, int VInicial){	
	int i;
	int valMin = INFINITO;
	
	for (i=0; i<VERTICES; i++){
		if (aberto[i] && (grafo[VAtual][i] != 0)){
			if ((distancia[VAtual] + grafo[VAtual][i]) < distancia[i]){
				distancia[i] = (distancia[VAtual] + grafo[VAtual][i]);
				anterior[i] = VAtual;
			}
		}		
	}	
}

int CalculaMinimo(int VAtual, int VInicial){
	
	CalculaArestasVerticeAtual(VAtual, VInicial);
	int j;
	int min = -1;
	int valMin = INFINITO;
			
	//Procura o v�rtice menor
	for (j=0; j<VERTICES; j++){
	
		//se for o inicial ele ignora e vai para o pr�ximo
		if (j==VInicial) continue;
		
		if ((aberto[j]) && (grafo[VAtual][j] > 0) && (distancia[j] < valMin)){
			valMin = grafo[VAtual][j];
			min = j;
		}
	}
	aberto[min] = 0;	
	return min;
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

void ImprimeCaminho(int Inicial, int Final){
	int i;
	printf("\n Inicial %d, Final %d, Custo Total: %d, caminho: ", Inicial, Final, distancia[Final]);
	i=Final;
	
	while(i>=Inicial){		
		printf("%d, ", i);
		i = anterior[i];
	}
	printf("\n---------------");
}

void ImprimeDados(){
	int i;
	printf("\n------DADOS---------\n");
	for (i=0; i<VERTICES; i++){
		printf("Distancia: |%d| ", distancia[i]);
		printf("anterior: |%d| ", anterior[i]);
		//printf("aberto: |%d| ", aberto[i]);
		
		printf("\n");
	}
	printf("\n---------------");
}
