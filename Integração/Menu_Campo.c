#include "campo_minado.h"
#define MAX_LEN 128


/*Prototipos*/
void menu_jogo();
void Jogar();
void Regras();
void Ranking();
void Creditos();

void retornar();
int continuar();
void img_text(char *path, char *name);



int main(){
	system(" ");
	
	while(1)
    	menu_jogo();	
   
    return 0;
}


/*Funcao que vai colocar as logos do campo minado ao puxar de um arquivo*/
void img_text(char *nome, char *mensagem){
    FILE *fptr;
    
    fptr = fopen(nome, "r");	
	if(fptr == (FILE *)NULL){
        printf("%s", mensagem);
        return;
    }
    
    char read_string[MAX_LEN];
    while(fgets(read_string,sizeof(read_string),fptr) != NULL){
        printf("%s", read_string);
    }
    fclose(fptr);
}


void retornar(){
	char opcao[MAX_LEN];
	
	while(1){
		printf("\nSe deseja retornar, aperte S: ");
	    scanf(" %[^\n]s", opcao);
        
        if(strlen(opcao)==1 && toupper(opcao[0]) == 'S')
        	break;
			
		printf("A entrada nao e valida!\n");
	}
}


/*Funcao que permite continuar jogando o jogo*/
int continuar(){
    char opcao[MAX_LEN];
    
	while(1){
        printf("\nDeseja continuar jogando?(S/N): ");
        scanf(" %[^\n]s", opcao);
		
		if(strlen(opcao)==1){
			if(toupper(opcao[0]) == 'S')
	            return 1;
			
			if(toupper(opcao[0]) == 'N')
	            return 0;		
		}
		
        printf("Digite um valor valido!\n");
    }
}


/*Funcao que cria o menu do jogo.*/
void menu_jogo(){
    char opcao[MAX_LEN]; 
    
	clear();
    img_text("Arquivos/Campo Minado.txt", "Campo Minado\n\n");
    
    printf("\nSeja Bem-Vindo ao Campo Minado!\n");
    printf("\n1 - Jogar");
	printf("\n2 - Regras");
	printf("\n3 - Ranking");
	printf("\n4 - Creditos");
	printf("\n5 - Sair\n");
    
	while(1){
        printf("\nX: ");
        scanf(" %[^\n]s", opcao);
        
        if(strlen(opcao)==1 && opcao[0]>='1' && opcao[0]<='5')
        	break;
			
		printf("A opcao nao e valida!\n");	
	}

    clear();
   
    switch(opcao[0]){
    	case '1':
    		Jogar();
    		break;
		
		case '2':
			Regras();
			break;
				
		case '3':
    		Ranking();
    		break;
    		
    	case '4':
    		Creditos();
    		break;
    		
    	default:
    		exit(0);
	}
}


void Jogar(){
	
	char opcao[MAX_LEN];
    int lin, col, minas; 

    while(1){
    	clear();

    	printf("Digite a dificuldade que deseja jogar\n");
        printf("\n1 - Iniciante\n");	
        printf("2 - Intermediario\n");
        printf("3 - Especialista\n");
        printf("4 - Personalizado\n");
        printf("5 - Voltar\n");

        while(1){
            printf("\nEscolha uma opcao: ");
            scanf(" %[^\n]s", opcao);
        
        	if(strlen(opcao)==1 && opcao[0]>='1' && opcao[0]<='5')
        		break;
			
			printf("A opcao nao e valida!\n");
	    }

        switch(opcao[0]){
            case '1': //Configura o Jogo no modo Iniciante.
                lin=9, col=9, minas=10;
                break;
                
            case '2': //Configura o Jogo no modo Intermediario.
                lin=16, col=16, minas=40;
                break;
                
            case '3': //Configura o Jogo no modo Especialista.
                lin=30, col=16, minas=99;
                break;
                
            case '4': //Configura o Jogo no modo Personalizado.
            	lin=0, col=0, minas=0;
                break;
                
            default:
                return;
        }
        
        clear();
        campo_init(lin, col, minas);
        
		if(continuar() == 0)
			break; 
	}
}



/*Funcao ira mostrar as regras do jogo*/
void Regras(){

	img_text("Arquivos/Regras.txt", "Regras:\n");

    printf("\n\n1 - Se voce descobrir uma mina, o jogo acaba.\n");
    printf("2 - Se descobrir um quadrado vazio, o jogo continua.\n");
    printf("3 - Se aparecer um numero, ele informara quantas minas estao escondidas nos oito quadrados que o cercam. \n");
    
    img_text("Arquivos/regras_r.txt", "Aqui era para ter as regras gerais do jogo.");
    
	printf("\n\n");
    retornar();
}


/*Funcao que ira apenas motrar o ranking atual do jogo*/
void Ranking(){

    img_text("Arquivos/Ranking.txt", "Ranking:\n");
    printf("\n\n");
    img_text("Arquivos/ranking_jogadores.txt", "Aqui era para ter o Ranking dos jogadores.");
    
	printf("\n\n");
    retornar();
}


/*Funcao que ira mostrar os creditos na tela*/
void Creditos(){
	
	img_text("Arquivos/Cr�ditos.txt", "Cr�ditos:\n");

    printf("\n\n1 - Camila Lacerda\n2 - Felipe de Jesus\n");
    printf("3 - Luiz Felipe A. Soares\n4 - Pedro Poppolino\n\n");

    retornar();
}
