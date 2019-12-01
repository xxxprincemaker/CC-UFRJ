#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 128

/*Struct servira para a ordenacao.*/
typedef struct _RANK{
    char nome[30];
    float tempo[1];
}RANK;

/*Prototipos*/
void ordena_struct(RANK winners[], int tam);

int main(){

    //Ira ser substituida pelo nome do usuario digitado, *PARAMETRO
    char modos, new_winner[30] = " - Luiz Gabriel da Silva\n"; 
    int modo[2];
    //Ira ser substituido pelo tempo que o usuario marcou. *PARAMETRO
    float new_winner_time = 8.5;
    modos = '1';

    /*Devera ser preenchido com o modo digitado pelo usuario.
    Ele sera colocado como parametro.*/
    switch(modos){
        case '1':
            modo[0] = 1;
            modo[1] = 11;
            break;
        case '2':
            modo[0] = 12;
            modo[1] = 22;
            break;
        case '3':
            modo[0] = 23;
            modo[1] = 33;
            break;
        default:
            return;
    }

    /*CRIA A STRUCT PARA 10 PESSOAS NO RANKING*/
    RANK winner[10];
    int cont=0, i=0, j;

    /*Inicia o Arquivo*/
    char *file_name = "CC-UFRJ/Integração/Arquivos/ranking_winners.txt", string[MAX_LEN];
    FILE *arquivo;

    /*Teste basico para checar se foi aberto com sucesso.*/
    if(!(arquivo = fopen(file_name,"r+"))){
        fprintf(stderr,"Erro na abertura do arquivo %s.\n", file_name);
        exit(1);
    }

    /*Pega o conteudo do ranking e passa para struct criada.*/
    while(fgets(string, sizeof(string), arquivo) != NULL){
        if (cont >= modo[0] && cont < modo[1]){
            if (string[0] != '-'){
                printf("%s", string);
                sscanf(string, "%f" "%[^32]s", winner[i].tempo, winner[i].nome);
                i++; //Contador de structs validas que foram preenchidas.
            }else break;
        }
        cont++;
    }

    /*Reboobina o arquivo.*/
    rewind(arquivo);

    /*Inserir o novo vencedor no struct*/
    strcpy(winner[i].nome, new_winner);
    winner[i].tempo[0] = new_winner_time;

    /*Ordenar a struct*/
    ordena_struct(winner, i+1); // i+1 para incluir o novo arquivo.
    printf("\n");

    for (j = 0; j < i+1; j++){
        printf("%0.2f%s", winner[j].tempo[0] ,winner[j].nome);
    }

    j = 0;

    /*Escreve a nova struct no arquivo.*/
    while(fgets(string, sizeof(string), arquivo) != NULL){
        if (cont >= modo[0] && cont < modo[1]){
            if (j <= i+1){
                //printf("%0.2f%s", winner[j].tempo[0] ,winner[j].nome);
                fprintf(arquivo, "%.2f%s" , winner[j].tempo[0], winner[j].nome);
            }else fputs("-", arquivo);
            j++;
        }
        cont++;
    }
    fclose(arquivo);
}

/*Ira ordenar o conteudo da struct RANK* usando Booble sort*/
void ordena_struct(RANK winners[], int tam){
    
    int i, j;
    RANK temp;

    for(i = 0; i < tam; i++){
        for (j = 0; j < tam-1; j++){
            if (winners[j].tempo[0] > winners[j+1].tempo[0]){
                temp = winners[j];
                winners[j] = winners[j+1];
                winners[j+1] = temp;
            }
        }
    }
}

