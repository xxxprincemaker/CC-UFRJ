#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "campo_minado.h"
#define MAX_LEN 128
#define ERRO printf("Digite um valor valido!\n");

/*Prototipos*/
void img_text(char name[255]);
void clrscr();
int continues();
int regras_jogo();
int creditos();
void menu_jogo();
void mostra_ranking();


/*Funcao que ira criar colocar as logos do campo minado puxando de um arquivo*/
void img_text(char name[255]){

    char *filename = name;
    FILE *fptr;
    if(!(fptr = fopen(filename, "r"))){
        fprintf(stderr,"Erro na abertura do arquivo %s.\n", filename);
        return;
    }
    char read_string[MAX_LEN];
    while(fgets(read_string,sizeof(read_string),fptr) != NULL){
        printf("%s", read_string);
    }
    fclose(fptr);
    return;
}

/*Funcao que limpa a tela.*/
void clrscr(){
    system("@cls||clear");
}

/*Funcao que ira continuar jogando o jogo*/
int continues(){
    char opcao;
    while(1){
        printf("Deseja continuar jogando?(S/N):");
        scanf(" %c", &opcao);
        if (opcao == 'S' || opcao == 's'){
            return 1;
        }else if (opcao == 'N' || opcao == 'n'){
            return 0;
        }else{ //Limpar o buffer para nao ter erro.
            ERRO
            setbuf(stdin,0);
            //opcao = "\000";
            continue;
        }
    }
}


/*Funcao ira mostrar as regras do jogo*/
int regras_jogo(){
    
    char opcao;

    img_text("regras.txt");

    printf("\n\n1 - Se você descobrir uma mina, o jogo acaba.\n");
    printf("2 - Se descobrir um quadrado vazio, o jogo continua.\n");
    printf("3 - Se aparecer um número, ele informará quantas minas estão escondidas nos oito quadrados que o cercam. \n");
    
    img_text("regras_r.txt");
    
    while (1){    
        printf("\n\nAceita as regras e deseja prosseguir?(S/N):");
        scanf(" %c", &opcao);
        if (opcao == 'S' || opcao == 's'){
            return 1;
        }else if (opcao == 'N' || opcao == 'n'){
            return 0;
        }else{ //Limpar o buffer para nao ter erro.
            ERRO
            setbuf(stdin,0);
            //opcao = "\000";
            continue;
        }
    }

}
/*Funcao que ira mostrar os creditos na tela*/
int creditos(){

    char opcao;

    img_text("creditos.txt");

    printf("\n\n1 - Camila Lacerda\n2 - Felipe de Jesus\n");
    printf("3 - Luiz Felipe A. Soares\n4 - Pedro Pompolino\n\n");

    while(1){
        /*Poderia ser feito de forma recursiva.*/
        printf("Deseja retornar?(S/N):");
        scanf(" %c", &opcao);
        if (opcao == 'S' || opcao == 's'){
            clrscr();
            menu_jogo();
        }
        else if (opcao == 'N' || opcao == 'n') return 0;
        else{ //Limpar o buffer para nao ter erro.
            ERRO
            setbuf(stdin,0);
            //opcao = NULL;
            continue;
            }
        }
}

/*Funcao que ira apenas motrar o ranking atual do jogo*/
void mostra_ranking(){

    char opcao;

    img_text("ranking_image.txt");
    printf("\n\n");
    img_text("ranking.txt");
    while(1){
        /*Poderia ser feito de forma recursiva.*/
        printf("\n\nDeseja retornar?(S/N):");
        scanf(" %c", &opcao);
        if (opcao == 'S' || opcao == 's'){
            clrscr();
            menu_jogo();
        }
        else if (opcao == 'N' || opcao == 'n') return;
        else{ //Limpar o buffer para nao ter erro.
            ERRO
            setbuf(stdin,0);
            //opcao = NULL;
            continue;
            }
        }
}

/*Funcao que ira criar o menu do jogo.*/
void menu_jogo(){

    char opcao, opcao2;
    int aux, opcao3; 

    img_text("campo_minado.txt");
    
    printf("\nSeja Bem-Vindo ao Campo Minado!\n");

    while(1){
        printf("\n1 - Iniciar\n2 - Ranking\n3 - Créditos\n4 - Sair\n");
        printf("\nX:");
        scanf(" %c", &opcao);
			
			if(opcao>='1' && opcao<='5')
				break;
			
			printf("\n\nA opção não é válida!\n\n");	
		}

    clrscr();

    if (opcao != '1'){
        //Chama a funcao de creditos.
        if(opcao == '2'){
            //Chama o placar.
            mostra_ranking();
        }else if(opcao == '3'){
            //Chama os creditos
            creditos();
        }else{
            //Sai do Jogo.
            return;
        }
    }else{

        aux = regras_jogo();

        /*Modo de checar se o jogador aceita e concordou com as regras!*/
        if (aux == 0) return;

        clrscr();

        printf("Digite a dificuldade que deseja jogar\n");
        do{
            printf("\n1 - Iniciante \n");	
            printf("2 - Intermediario\n");
            printf("3 - Especialista\n");
            printf("4 - Personalizado\n");
            printf("5 - Sair\n\n");

            while(1){
                printf("Escolha uma opção: ");
                scanf(" %c", &opcao2);
                
                if(opcao2>='1' && opcao2<='5')
                    break;
                
                printf("A opção não é válida!\n\n");	
		    }

            clrscr();

            switch(opcao2){
                case '1':
                    //Chama o Jogo no modo iniciante.
                    campo_init(9,9,10);
                    opcao3 = continues(); // Determina se o jogador deseja continuar jogando
                    if (opcao3 == 1) clrscr(), menu_jogo();
                    else return;
                    break;
                case '2':
                    //Chama o Jogo no modo intermediario.
                    campo_init(16,16,40);
                    opcao3 = continues();
                    if (opcao3 == 1) clrscr(), menu_jogo();
                    else return;
                    break;
                case '3':
                    //Chama o Jogo no modo Especialista.
                    campo_init(30,16,99);
                    opcao3 = continues();
                    if (opcao3 == 1) clrscr(), menu_jogo();
                    else return;
                    break;
                case '4':
                    campo_init(0,0,0);
                    opcao3 = continues();
                    if (opcao3 == 1) clrscr(), menu_jogo();
                    else return;
                    break;
                default:
                    return menu_jogo();
            }

        }while(1);
    }

}

int main(){

    menu_jogo();

    return 0;
}