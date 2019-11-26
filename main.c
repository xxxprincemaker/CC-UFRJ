#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_LEN 128

/*Funcao que ira criar colocar a logo campo minado puxando de um arquivo*/
void img_text(){

    char *filename = "campo_minado.txt";
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

/*Funcao que ira criar o menu do jogo.*/
void menu_jogo(){

    char opcao, opcao2;
    int person[2] = {0}; 

    img_text();
    
    printf("\nSeja Bem-Vindo ao Campo Minado!\n");

    while(1){
        printf("\n1 - Iniciar\n2 - Sair\n");
        printf("\nX:");
        scanf(" %c", &opcao);
			
			if(opcao>='1' && opcao<='2')
				break;
			
			printf("\n\nA opção não é válida!\n\n");	
		}

    clrscr();

    if (opcao != '1'){
        //Chama a funcao de creditos.
        return;
    }else{
        printf("Digite a dificuldade que deseja jogar\n");
        do{
            printf("\n1 - Iniciante\n");	
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
                    break;
                case '2':
                    //Chama o Jogo no modo intermediario.
                    break;
                case '3':
                    //Chama o Jogo no modo Especialista.
                    break;
                case '4':
                    printf("\nDigite o tamanho do tabuleiro:");
                    scanf("%d %d", &person[0], &person[1]);
                    //Chama o Jogo no modo personalizado.
                    break;
                default:
                    return menu_jogo();
            }

        }while(1);
    }

}

int main(void){

    
    menu_jogo();

    return 0;
}