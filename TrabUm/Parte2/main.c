#include <stdio.h>
#include <stdlib.h>

int matrizAdjacencia[7][7] = {  {0,2,0,6,12,0,0} ,
							    {-2,0,1,0,0,5,0},
								{0,-1,0,0,0,0,40},
								{-6,0,0,0,0,4,0},
								{-12,0,0,0,0,0,30},
								{0,-5,0,-4,0,0,8},
								{0,0,-40,0,-30,-8,0} };


int matrizIncidencia[7][9] = {	{2,6,12,0,0,0,0,0,0},
								{-2,0,0,1,5,0,0,0,0},
								{0,0,0,-1,0,40,0,0,0},
								{0,-6,0,0,0,0,4,0,0},
								{0,0,-12,0,0,0,0,0,30},
								{0,0,0,0,-5,0,-4,8,0},
								{0,0,0,0,0,-40,0,-8,-30} };


int caminhoIncidencia[7] = {-1,-1,-1,-1,-1,-1,-1};
int custoTotalIncidencia =0;

int caminhoAdjacencia[7] = {-1,-1,-1,-1,-1,-1,-1};
int custoTotalAdjacencia =0;

int buscaMenorValorIncidencia(int linha); // busca o pr�ximo vertice a ser visitado
void insereCaminhoIncidencia(int vertice); // insere o v�rtice no vetor do caminho
void buscaCaminhoIncidencia(int origem, int destino); // fun��o principal que utiliza a matriz de Incid�ncia


int buscaMenorValorAdjacencia(int vertice); // busca o pr�ximo vertice a ser visitado
void insereCaminhoAdjacencia(int vertice); // insere o v�rtice no vetor do caminho
void buscaCaminhoAdjacencia(int origem, int destino); // fun��o principal que utiliza a matriz de Adjac�ncia


int main() {
    int verticeOrigem, verticeDestino;

    printf("Informe o verticie de saida: ");
    scanf("%d",&verticeOrigem );

    printf("Informe o verticie de chegada: ");
    scanf("%d",&verticeDestino );



    buscaCaminhoIncidencia(verticeOrigem, verticeDestino);
    buscaCaminhoAdjacencia(verticeOrigem, verticeDestino);

	return 0;
}

// utilizando matriz de adjacencia
void buscaCaminhoAdjacencia(int origem, int destino){

 int proximoVertice, i;
	printf("\n\n\n\Programa que encontrar o caminho, \nsaindo do vertice %d e chegando no vertice %d, \nutilizando matriz de Adjacencia.\n", origem, destino);
    proximoVertice = buscaMenorValorAdjacencia(origem); //busca o pr�ximo v�rtice a partir da origem
    // repete o processo at� passar por todos os v�rtices, passando os pr�ximos para a fun��o
	while(proximoVertice != destino){
        proximoVertice = buscaMenorValorAdjacencia(proximoVertice);
	}
	insereCaminhoAdjacencia(destino);
    printf("\nCaminho: ");
    for(i = 0; i < 9; i++){
        if (caminhoAdjacencia[i] == -1){
            i=9;
        } else{
            printf("%d ", caminhoAdjacencia[i]);
        }
    }
    printf("\nCusto total de: %d ", custoTotalAdjacencia);

    printf("\n");
}

int buscaMenorValorAdjacencia(int linha){
    insereCaminhoAdjacencia(linha);
    int proximoVertice = 0;
    int i, menorValor = 999999;
    // busca a coluna com menor valor >0
    for(i = 0; i<9; i++){
        if(matrizAdjacencia[linha][i] > 0 && matrizAdjacencia[linha][i] < menorValor){
            menorValor = matrizAdjacencia[linha][i];
            proximoVertice =i;
        }
    }
    custoTotalAdjacencia += menorValor;
    //retorna o valor da coluna, que � o pr�ximo v�rtice a ser visitado
    return proximoVertice;
}
// insere no -1 que encontra
void insereCaminhoAdjacencia(int vertice){
   int i;
   for(i=0; i<5; i++){
     if(caminhoAdjacencia[i] == -1){
        caminhoAdjacencia[i] = vertice;
        i = 5;
     }
   }
}


// utilizando matriz de incidencia
void buscaCaminhoIncidencia(int origem, int destino){
    int proximoVertice, i;
	printf("Programa que encontrar o caminho, \nsaindo do vertice %d e chegando no %d, \nutilizando matriz de Incidencia.\n", origem, destino);

    //o que inicia � o v�rtice de origem
	proximoVertice = buscaMenorValorIncidencia(origem);
    //vai at� chegar no destino
	while(proximoVertice != destino){
        proximoVertice = buscaMenorValorIncidencia(proximoVertice);
	}
    insereCaminhoIncidencia(destino);
    printf("\nCaminho: ");
    for(i = 0; i < 9; i++){
        if (caminhoIncidencia[i] == -1){
            i=9;
        } else{
            printf("%d ", caminhoIncidencia[i]);
        }
    }
    printf("\nCusto total de: %d ", custoTotalIncidencia);

    printf("\n");
}

int buscaMenorValorIncidencia(int linhaColuna) {
    insereCaminhoIncidencia(linhaColuna);
    int menorValor = 999999;
    int i, valor, colunaMenorValor;
    for (i = 0; i < 9; i++) {
         // busca coluna com menor valor >0
        if (matrizIncidencia[linhaColuna][i] > 0 && matrizIncidencia[linhaColuna][i] < menorValor) {
            menorValor = matrizIncidencia[linhaColuna][i];
            colunaMenorValor = i;
        }
    }

    custoTotalIncidencia += menorValor;
    // verifica se � o valor igual na mesma coluna na qual foi encontrada coluna com menor valor, posi��o diferente da posi��o do menor valor
    for (i = 0; i < 9; i++) {
        if (i != linhaColuna) {
            if (matrizIncidencia[i][colunaMenorValor] < 0)
                valor = matrizIncidencia[i][colunaMenorValor] * -1;
            else
                valor = matrizIncidencia[i][colunaMenorValor];

            if (valor == menorValor)
                return i;
        }
    }
	return 0;
}

// insere no -1 que encontra
void insereCaminhoIncidencia(int vertice){
   int i;
   for(i=0; i<5; i++){
     if(caminhoIncidencia[i] == -1){
        caminhoIncidencia[i] = vertice;
        i = 5;
     }
   }
}

