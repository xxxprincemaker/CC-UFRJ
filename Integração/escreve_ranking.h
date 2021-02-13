#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LEN 128
#define min(a,b) (a<b? a:b)

/*Struct servira para a ordenacao.*/
typedef struct _RANK{
    char nome[31];
    int tempo;
}RANK;

/*Prototipos*/
void ordena_struct(RANK winners[], int tam);

void escrever_ranking(char modo, char new_winner[30], int new_winner_time){
    
    char *file_name, string[MAX_LEN];

    //Ira ser substituida pelo nome do usuario digitado, *PARAMETRO
    //char modo = '2', new_winner[30] = "Luiz Da Silva"; 
    //int k, pos_file, pos[3] = {0, 11, 22};
    
    //Ira ser substituido pelo tempo que o usuario marcou. *PARAMETRO
    //int new_winner_time = 25;

    /*Devera ser preenchido com o modo digitado pelo usuario.
    Ele sera colocado como parametro.*/
    //k = modo - '0';

    /*CRIA A STRUCT PARA 10 PESSOAS NO RANKING*/
    RANK winner[11];
    int cont=0, i=0, j; //max;

    /*Inicia o Arquivo de acordo com o modo*/
    switch(modo){
        case '1':
            file_name = "CC-UFRJ/ranking_iniciante.txt";
            break;
        case '2':
            file_name = "CC-UFRJ/ranking_intermediario.txt";
            break;
        case '3':
            file_name = "CC-UFRJ/ranking_especialista.txt";
            break;
        default:
            NULL;
    }

    FILE *arquivo;

    /*Teste basico para checar se foi aberto com sucesso.*/
    if(!(arquivo = fopen(file_name,"r+"))){
        fprintf(stderr,"Erro na abertura do arquivo %s.\n", file_name);
        exit(1);
    }
    
    while(fgets(string, sizeof(string), arquivo)){
	    cont++;
	}

    /*
	if(!feof(arquivo)){
		pos_file = SEEK_CUR;
	    fscanf(arquivo, "%d", &max);
	}
	printf("%d\n", max);*/

    rewind(arquivo);

    /*Pega o conteudo do ranking e passa para struct criada.*/
    for(i=0; i<cont && !feof(arquivo); i++)
        fscanf(arquivo,"%d %[^\n]s", &winner[i].tempo, winner[i].nome);

    /*Reboobina o arquivo.*/
    rewind(arquivo);

    /*Inserir o novo vencedor no struct*/
    strcpy(winner[i].nome, new_winner);
    winner[i].tempo = new_winner_time;

    /*Ordenar a struct*/
    ordena_struct(winner, i+1); // i+1 para incluir o novo arquivo.
    printf("\n");

    for (j = 0; j < i+1; j++){
        printf("%d %s\n", winner[j].tempo ,winner[j].nome);
    }

	i = min(i,10); 

    /*fseek(arquivo, 0, pos_file);
    fprintf(arquivo, "%d\n", i);*/

    /*Escreve a nova struct no arquivo.*/
    for(j=0; j<=i; j++){
        fprintf(arquivo, "%d %s\n" , winner[j].tempo, winner[j].nome);
    }
	fclose(arquivo);
}

/*Ira ordenar o conteudo da struct RANK* usando Booble sort*/
void ordena_struct(RANK winners[], int tam){
    
    int i, j;
    RANK temp;

    for(i = 0; i < tam-1; i++){
        for (j = i; j < tam; j++){
            if (winners[i].tempo > winners[j].tempo){
                temp = winners[i];
                winners[i] = winners[j];
                winners[j] = temp;
            }
        }
    }
}
