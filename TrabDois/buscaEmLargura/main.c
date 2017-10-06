#include <stdio.h>
#include <stdlib.h>

#define VERTICES 21
#define INFINITO 10000000
#define BRANCO 0
#define CINZA 1
#define PRETO 2

int grafo[VERTICES][VERTICES] = {   {0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
									{1,	0,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
									{0,	1,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
									{0,	1,	0,	0,	1,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
									{0,	0,	1,	1,	0,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
									{0,	0,	0,	0,	1,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
									{0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
									{0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
									{0,	0,	0,	0,	0,	0,	1,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0},
									{0,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1},
									{1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	1,	0,	0,	0,	0,	0,	0,	0},
									{0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0},
									{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0},
									{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0},
									{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	1,	0,	0,	0},
									{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	1,	0,	0,	0,	0},
									{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	1,	1,	1,	0},
									{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	1,	0,	0,	0,	0},
									{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	1,	1},
									{0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	1,	0,	1},
									{0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	0}};
									
char IndiceParaVertice[VERTICES] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','z'};
								  								
int distancia[VERTICES];
int anterior[VERTICES];
int cor[VERTICES];

//Armazena os vérices cinzas que precisam ser processados
int *fita=NULL;
int tamFita=0;

void Empilha(int VerticeEmp);
int Desempilha();

void ImprimeFita();
void ImprimeMatriz();
void ImprimeDados();
void ImprimeCaminho(int Inicial, int Final);

void BFS(int VAtual);

void inicializa(int VInicial);
void processaAdjacentes(int VAtual);
void processaBranco(int VAtual, int VAnterior);

int main(int argc, char *argv[]) {
	int vInicio=0;
	int vFim=20;
	
	ImprimeMatriz();
	
	printf("\n ->> Digite o vertice Inicial \n");
	scanf("%i", &vInicio);
	
	printf("\n ->> Digite o vertice Final \n");
	scanf("%i", &vFim);
	
	//função que vai fazer a busca em largura.
	BFS(vInicio);
	
	//Imprime os resultados do processamento
	ImprimeDados();
	ImprimeCaminho(vInicio, vFim);
	
	return 0;
}

void BFS(int VAtual){
	int processando=-1;
			
	inicializa(VAtual);
	
	//Empilha o vértice origem.
	Empilha(VAtual);
		
	do{
		//enquanto existir vérices cinzas vai desempilhando
		processando = Desempilha();
		
		//Para cada vértice cinza vai visitar seus adjacentes.
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
	for (i=0; i < VERTICES; i++){
		
		//se for adjacente e estiver branco vai atualizar as informações e empilhar o mesmo;
		if ((grafo[VAtual][i] > 0) && (cor[i] == BRANCO)){
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
	distancia[VInicial] = -1;
	anterior[VInicial] = -1;
	cor[VInicial] = CINZA;
	
}

//Remove o primeiro vértice da fila, reordena e diminui o tamanho da fila..
int Desempilha(){
	int i,primeiro,temp;
	primeiro=-1;
	
	for (i=0, temp=-1; i<tamFita; i++){
		if (i==0){
			primeiro= fita[0];
		}
		fita[i] = fita[i+1];
	}
	
	//diminui o tamanho da fila.
	if (tamFita > 0){
		tamFita--;
		fita = realloc(fita, (tamFita * sizeof(int)));
	}
	return primeiro;
}

//Coloca o vértice passado na última possição da fila.
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
		//soma um para ficar o caminho correto e não o índice.
		printf("V-%c Distancia: |%d| ", IndiceParaVertice[i], distancia[i]+1);
		printf("Anterior: |%c| ", IndiceParaVertice[anterior[i]]);
		printf("Cor: |%d| ", cor[i]);
		
		printf("\n");
	}
	printf("\n---------------");
}

void ImprimeCaminho(int Inicial, int Final){
	int i;
	printf("\n Inicial %c Final %c, Custo Total: %d, caminho: ", IndiceParaVertice[Inicial], IndiceParaVertice[Final], distancia[Final]);
	i=Final;
	
	while(i>Inicial){		
		printf("%c, ", IndiceParaVertice[anterior[i]]);
		i = anterior[i];
	}
	printf("\n---------------");
}

void ImprimeFita(){
	int i;
	printf("\n Fita: ");
	
	for(i=0; i < tamFita; i++){
		printf("%c, ", IndiceParaVertice[fita[i]]);
	}
}

