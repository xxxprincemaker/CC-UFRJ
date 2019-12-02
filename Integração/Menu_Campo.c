#include "campo_minado.h"
#include "escreve_ranking.h"
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
void campo_init(char modo, int lin, int col, int minas);
void escreve_placar(char modo, char nome[], double secs);


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
        scanf(" %[^\n]s", &opcao);
		
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
        printf("\n1 - Iniciante (9x9)\n");	
        printf("2 - Intermediario (16x16)\n");
        printf("3 - Especialista (16x30)\n");
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
                lin=16, col=30, minas=99;
                break;
                
            case '4': //Configura o Jogo no modo Personalizado.
            	lin=0, col=0, minas=0;
                break;
                
            default:
                return;
        }
        
        clear();
        campo_init(opcao[0], lin, col, minas);
        
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
    printf("Iniciante:\n");
    img_text("CC-UFRJ/ranking_iniciante.txt", "Aqui era para ter o Ranking dos jogadores.");
    printf("\n\nIntermediario:\n");
    img_text("CC-UFRJ/ranking_intermediario.txt", "Aqui era para ter o Ranking dos jogadores.");
    printf("\nEspecialista:\n");
    img_text("CC-UFRJ/ranking_especialista.txt", "Aqui era para ter o Ranking dos jogadores.");

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


void campo_init(char modo, int lin, int col, int minas){ 
    int i, resultado;
    char nome[MAX_LEN], op1[MAX_LEN], op2[MAX_LEN];
	 

    if(modo == '4'){
    	
    	while(1){
        	printf("Entre com as dimensoes do tabuleiro (linha e coluna): ");
        	scanf(" %s %[^\n]s", op1, op2);  
    		
			lin = (int) NumReal(op1);
			col = (int) NumReal(op2);
				
			if(lin>8 && col>8 && lin<=24 && col<=30)
				break;
			
			printf("Dimensoes invalidas! A dimensao minima � 9x9 e a maxima � 24x30.\n\n");
		}
        
        /*Caso coloque uma quantidade maior de minas do que o disponivel, retornar erro.*/
        while (1){
            printf("\nEntre com o numero de minas: ");
            scanf(" %[^\n]s", op1);
            
            minas = NumReal(op1);

            if(minas>9 && minas <= (lin-1)*(col-1))
                break;
                    
			printf("A quantidade de minas deve ser maior que 10 e menor que %d.\n", (lin-1)*(col-1)+1);
        }
    }

    //vai ser chamado de acordo com o modo
    resultado = partida(lin, col, minas);
    
    if(resultado<0){
        printf("\nVoce perdeu!\n");
        return;
    }
        
    printf("\nParabens, voce venceu!!\n\n"); 
    if(modo=='4')
    	return;
    	
    while(1){
    	printf("Por favor, digite o seu nome (30 caracteres): ");
    	scanf(" %[^\n]s", nome);
		
		if(strlen(nome)<=30){
			for(i=0; nome[i]!='\0'; i++){
				if(toupper((nome[i])<'A' || toupper(nome[i])>'Z') && nome[i]!=' ')
					break;
			}
			if(nome[i]=='\0')
				break;	
		}
		
		printf("Nome invalido! O nome deve ter at� 30 caracteres e apenas letras do alfabeto.\n\n");
	}
	
	
    /*Grava no arquivo se tiver batido record*/
    //escrever_ranking(,nome,);
    //escreve_placar(modo, nome, resultado);

}
