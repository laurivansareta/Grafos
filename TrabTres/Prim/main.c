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
void Prim(int inicio);
void ImprimeMatriz();
void ImprimeDados(int Inicial);
void CalculaArestasVerticeAtual(int VAtual, int VInicial);
int CalculaMinimo(int VAtual, int VInicial);
void ImprimeCusto(int Inicial);

								

int main(int argc, char *argv[]) {
	int vInicio=0;
	int vFim=6;
	
	ImprimeMatriz();
	
	printf("\n ->> Digite o vertice Inicial \n");
	scanf("%i", &vInicio);
	
	// Chamada da função que executa o algoritimo, passando o vértice origem como parâmetro.
	Prim(vInicio);
	ImprimeDados(vInicio);
	ImprimeCusto(vInicio);
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

void Prim(int inicio){	
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
		if ((aberto[j]) && (distancia[j] < valMin)){
			valMin = distancia[j];
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

void ImprimeCusto(int Inicial){
	int i, custo;
	custo = 0;
	i=0;
	
//	printf("\n---------------\n");
	
	while(i<VERTICES){		
//		printf("%d, ", distancia[i]);
		custo = custo + distancia[i];		
		i++;
	}
	printf("\n---------------");
	printf("\n Custo Total: %d", custo);
}

void ImprimeDados(int Inicial){
	int i;
	printf("\n------Geradora minima---------");
	for (i=0; i<VERTICES; i++){		
		if (i != Inicial)
			printf("(%d, %d)", i, anterior[i]);
		//printf("aberto: |%d| ", aberto[i]);
		
		printf("\n");
	}
	
}
