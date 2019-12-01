#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 128

/*Struct servira para a ordenacao.*/
typedef struct _RANK{
    char nome[MAX_LEN];
    float tempo;
}RANK;

/*Prototipos*/
void ordena_struct(RANK winners[], int tam);

int main(){

    int cont=0;
    char *file_name = "CC-UFRJ/Integração/Arquivos/ranking_winners.txt";
    FILE *arquivo;
    /*Teste basico para checar se foi aberto com sucesso.*/
    if(!(arquivo = fopen(file_name,"r+"))){
        fprintf(stderr,"Erro na abertura do arquivo %s.\n", file_name);
        return 1;
    }
    


}

/*Ira ordenar o conteudo da struct RANK*/
void ordena_struct(RANK winners[], int tam){
    
    int i, j;
    RANK temp[1];

    for(i = 0; i < tam; i++){
        for (j = 0; j < tam-1; j++){
            if (winners[j].tempo > winners[j+1].tempo){
                temp[0] = winners[j];
                winners[j] = winners[j+1];
                winners[j+1] = temp[0];
            }
        }
    }
}

