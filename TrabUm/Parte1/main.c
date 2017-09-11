#include <stdio.h>
#include <stdlib.h>

int matrizAdjacencia[5][5] = { { 0, 30,-15, 0, 20 } ,
							    {-30,-10, 0, 50, 0  },
								{ 15, 10, 0, 5,-10 },
								{ 0, 50,-5, 0,-30  },
								{-20, 0,10, 30, 0  } };


int matrizIncidencia[5][8] = {  { 20, -15,  30,   0,   0,   0,  0,  0 },
								{  0,   0, -30,   0, -10,   0,  0, 50 },
								{  0,  15,   0, -10,  10,   0,  5,  0 },
								{  0,   0,   0,   0,   0, -30, -5, 50 },
								{ -20,  0,   0,   10,  0,  30,  0,  0 } };

int caminhoIncidencia[5] = {-1,-1,-1,-1,-1};
int custoTotalIncidencia =0;

int caminhoAdjacencia[5] = {-1,-1,-1,-1,-1};
int custoTotalAdjacencia =0;

int buscaMenorValorIncidencia(int linha); // busca o pr�ximo vertice a ser visitado
void insereCaminhoIncidencia(int vertice); // insere o v�rtice no vetor do caminho
void buscaCaminhoIncidencia(); // fun��o principal que utiliza a matriz de Incid�ncia


int buscaMenorValorAdjacencia(int vertice); // busca o pr�ximo vertice a ser visitado
void insereCaminhoAdjacencia(int vertice); // insere o v�rtice no vetor do caminho
void buscaCaminhoAdjacencia(); // fun��o principal que utiliza a matria de Adjac�ncia



int main() {
    buscaCaminhoIncidencia();
    buscaCaminhoAdjacencia();

	return 0;
}


// utilizando matriz de adjacencia
void buscaCaminhoAdjacencia(){

 int proximoVertice, i;
	printf("\n\n\n\Programa que encontrar o caminho, \nsaindo do vertice 0 e passando por todos os vertices, \nutilizando matriz de Adjacencia.\n");
    proximoVertice = buscaMenorValorAdjacencia(0); //busca o pr�ximo v�rtice a partir do v�rtice 0
    // repete o processo at� passar por todos os v�rtices, passando os pr�ximos para a fun��o
	while(caminhoAdjacencia[4] == -1){
        proximoVertice = buscaMenorValorAdjacencia(proximoVertice);
	}
    printf("\nCaminho: ");
    for(i = 0; i < 5; i++){
        printf("%d ", caminhoAdjacencia[i]);
    }
    printf("\nCusto total de: %d ", custoTotalAdjacencia);

    printf("\n");
}

int buscaMenorValorAdjacencia(int linha){
    insereCaminhoAdjacencia(linha);
    int proximoVertice = 0;
    //busca o pr�ximo v�rtice at� todos serem visitados
    if(caminhoAdjacencia[4] == -1){
        int i, menorValor = 999999;
        // busca a coluna com menor valor >0
        for(i = 0; i<5; i++){
            if(matrizAdjacencia[linha][i] > 0 && matrizAdjacencia[linha][i] < menorValor){
                menorValor = matrizAdjacencia[linha][i];
                proximoVertice =i;
            }
        }
        custoTotalAdjacencia += menorValor;
    }
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
void buscaCaminhoIncidencia(){
    int proximoVertice, i;
	printf("Programa que encontrar o caminho, \nsaindo do vertice 0 e passando por todos os vertices, \nutilizando matriz de Incidencia.\n");


	proximoVertice = buscaMenorValorIncidencia(0);
    // repete o processo at� passar por todos os v�rtices, passando os pr�ximos para a fun��o
	while(caminhoIncidencia[4] == -1){
        proximoVertice = buscaMenorValorIncidencia(proximoVertice);
	}

    printf("\nCaminho: ");
    for(i = 0; i < 5; i++){
        printf("%d ", caminhoIncidencia[i]);
    }
    printf("\nCusto total de: %d ", custoTotalIncidencia);

    printf("\n");
}

int buscaMenorValorIncidencia(int linhaColuna) {
    insereCaminhoIncidencia(linhaColuna);
    //busca o pr�ximo v�rtice at� todos serem visitados
    if(caminhoIncidencia[4] == -1){
        int menorValor = 999999;
        int i, valor, colunaMenorValor;
        for (i = 0; i < 8; i++) {
            // busca coluna com menor valor >0
            if (matrizIncidencia[linhaColuna][i] > 0 && matrizIncidencia[linhaColuna][i] < menorValor) {
                menorValor = matrizIncidencia[linhaColuna][i];
                colunaMenorValor = i;
            }
        }

        custoTotalIncidencia += menorValor;
        // verifica se � o valor igual na mesma coluna na qual foi encontrada coluna com menor valor, posi��o diferente da posi��o do menor valor
        for (i = 0; i < 5; i++) {
            if (i != linhaColuna) {
                if (matrizIncidencia[i][colunaMenorValor] < 0)
                    valor = matrizIncidencia[i][colunaMenorValor] * -1;
                else
                    valor = matrizIncidencia[i][colunaMenorValor];

                if (valor == menorValor)
                    return i;
            }
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
