#include <stdio.h>
#include <stdlib.h>

#define VERTICES 8
#define INFINITO 10000000

int grafo[VERTICES][VERTICES] = {   {0,	2,	0,	6,	5,	0,	0,	0},
									{2,	0,	7,	7,	0,	0,	0,	0},
									{0,	7,	0,	0,	6,	2,	0,	0},
									{6,	7,	0,	0,	0,	0,	0,	0},
									{5,	0,	6,	0,	0,	0,	4,	5},
									{0,	0,	2,	0,	0,	0,	4,	6},
									{0,	0,	0,	0,	4,	4,	0,	1},
									{0,	0,	0,	0,	5,	6,	1,	0}};
								 					  
								
int distancia[VERTICES];
int anterior[VERTICES];
int aberto[VERTICES];

void Inicializa(int inicio);
void prism(int inicio);
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
	prism(vInicio);
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

void prism(int inicio){	
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
			if (grafo[VAtual][i] < distancia[i]){
				distancia[i] = grafo[VAtual][i];
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
	printf("\n Inicial %d, Custo Total: %d, caminho: ", Inicial, distancia[Final]);
	i=0;
	
	while(i<VERTICES){		
		printf("%d, ", i);
		i = anterior[i];
	}
	printf("\n---------------");
}

void ImprimeDados(){
	int i;
	printf("\n------DADOS---------\n");
	for (i=0; i<VERTICES; i++){
		printf("V-%d  Distancia: |%d| ", i, distancia[i]);
		printf("Anterior: |%c| ", anterior[i]);
		//printf("aberto: |%d| ", aberto[i]);
		
		printf("\n");
	}
	printf("\n---------------");
}
