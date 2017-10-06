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
								  
char IndiceParaVertice[VERTICES] = {'A','B','C','D','E','F','G'};								  
								
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
	int vInicio=0;
	int vFim=6;
	
	ImprimeMatriz();
	
	printf("\n ->> Digite o vertice Inicial \n");
	scanf("%i", &vInicio);
	
	printf("\n ->> Digite o vertice Final \n");
	scanf("%i", &vFim);
	
	// Chamada da função que executa o algoritimo, passando o vértice origem como parâmetro.
	Dijkstra(vInicio);
	ImprimeDados();
	ImprimeCaminho(vInicio, vFim);
	return 0;
}

void inicializa(int inicio){
	int i;
	for (i=0; i < VERTICES; i++){
		distancia[i] = INFINITO;
		anterior[i] = -1;
		aberto[i] = 1;
	}
	//primeira distância é zero
	distancia[inicio] = 0;
	aberto[inicio] = 0;
	anterior[inicio] = -1;
	
}

void Dijkstra(int inicio){	
	int i,j;
	int VAtual = inicio;
		
	inicializa(inicio);
		
	while(VAtual != -1){		
		/* Calcula o caminho de todos os vértices adjacentes ao atual, e retorna a menor distância
		 entre os que estão abertos. */
		VAtual = CalculaMinimo(VAtual, inicio);
	}
}

void CalculaArestasVerticeAtual(int VAtual, int VInicial){	
	int i;
	int valMin = INFINITO;
	
	for (i=0; i<VERTICES; i++){
		//Verifica se o vértice atual é adjacente
		if (aberto[i] && (grafo[VAtual][i] != 0)){
			//Se o custo atual mais o do vértice atual for menor do que o custo atual substitui e atualiza o anterior.
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
			
	//Procura o vértice menor
	for (j=0; j<VERTICES; j++){
	
		//se for o vértice origem ele ignora e vai para o próximo
		if (j==VInicial) continue;
		//Se o vértice estiver aberto, for o menor custo vai guardar o valor e a aresta mínima.
		if ((aberto[j]) && (grafo[VAtual][j] > 0) && (distancia[j] < valMin)){
			valMin = grafo[VAtual][j];
			min = j;
		}
	}
	//Fecha o vértice de menor custo pois foi atualizado e o retorna.
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
