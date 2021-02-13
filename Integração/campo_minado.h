#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#define LONG long long int

/*prototipos*/
void clear();
LONG NumReal(char *num);
int ver_jogada(char *op, char *l, char *aux, int lin, int col);
int ** gera_tabuleiro(int lin, int col);
void bombardeio(int **tab, int lin, int col, int bombas);
void descobre_minas(int **tab, int lin, int col);
int minas_arredores(int **tab, int i, int j);
void descobre_blocos(int **tab, int i, int j);
int calcula_livres(int **tab, int lin, int col);
void bota_bandeiras(int **tab, int lin, int col);

int partida(int lin, int col, int minas);
void mostra_tab(int **tab, int lin, int col);



/*Funcao que limpa a tela.*/
void clear(){
    //system("@cls||clear");
	printf("\033[2J \033c");
}


LONG NumReal(char *num){
	int i, cont = 0;
	LONG tam;
	
	for(i=0; num[i]!='\0'; i++){
		if(num[i]=='0')
			cont++;
		if(num[i]<'0' || num[i]>'9')
			return -1;
	}

	tam = cont - i;

	if(tam==0)
		return 0;

	tam = atoll(num);
	return tam;
}


int ver_jogada(char *op, char *l, char *aux, int lin, int col){
	int c;
	
	if(strlen(op)!=1 || strlen(l)!=1)
		return 0;
	
	op[0] = toupper(op[0]);
	l[0] = toupper(l[0]);
	
	if(op[0]!='A' && op[0]!='@' && op[0]!='?' && op[0]!='R')
		return 0;
	
	c = (int) NumReal(aux);

	if(c<0 || c>col || l[0]<'A' || l[0]>='A'+lin)
		return 0;				

	return c;
}


int partida(int lin, int col, int minas){
    int **tab, i, j, tempo=1;
    int c, livres, jogada=0;
    char op[100], l[100], aux[100];
    time_t inicio, fim;

    tab = gera_tabuleiro(lin+2, col+2);
    bombardeio(tab, lin, col, minas);


    while(1){
    	mostra_tab(tab, lin, col);
	
    	if(jogada)
			printf("\nJogada invalida!");
		
		printf("\nEntre com a sua jogada: ");
    	scanf(" %s %s %[^\n]s", op, l, aux);
    	
		if(c = ver_jogada(op, l, aux, lin, col))
			break;		
		
		jogada = 1;
	}
	
   	time(&inicio);
    livres = lin*col - minas;
    while(1){
        i = (l[0]-'A')+1;
        j = c;
    	jogada = 0;

        switch(op[0]){
            case '?':
                if(tab[i][j]==0 || tab[i][j]==-1)
                    tab[i][j] += -10;
                else if(tab[i][j]/10==-2)
                    tab[i][j] = tab[i][j]%10 - 10;
                else
                    jogada = 2;
                break;


            case '@':
                if(tab[i][j]==0 || tab[i][j]==-1)
                    tab[i][j] += -20;
                else if(tab[i][j]/10==-1)
                    tab[i][j] = tab[i][j]%10 - 20;
                else
                    jogada = 2;
                break;


            case 'R':
                if(tab[i][j]/10==-2 || tab[i][j]/10==-1)
                    tab[i][j] %= 10;
                else
                    jogada = 3; 
                break;

            
            case 'A':
                if(tab[i][j]/10!=-2 && tab[i][j]<1){
                    if(tab[i][j]%10==-1){
                        descobre_minas(tab, lin, col);
                        tab[i][j] = -41;

                        mostra_tab(tab, lin, col);
                        return -1;
                    }

                    descobre_blocos(tab, i, j);
                    livres = calcula_livres(tab, lin, col);
                    if(!livres)
                        goto VITORIA;
                }
                else
                    jogada = 4;
                break;
        }
        
		mostra_tab(tab, lin, col);
		switch(jogada){
			case 2:
				printf("\nO bloco escolhido ja foi aberto!");
				break;
			
			case 3:
				printf("\nNao ha simbolo para remover no bloco escolhido!");
				break;
				
			case 4:
				printf("\nNao ha como abrir o bloco escolhido!");
				break;
		}
		
		while(1){
		    if(jogada==1)
		        printf("\nJogada invalida!");
		    
			printf("\nEntre com a sua jogada: ");
			scanf(" %s %s %[^\n]s", op, l, aux);
			
			if(c = ver_jogada(op, l, aux, lin, col))
				break;
			
			jogada = 1;
			mostra_tab(tab, lin, col);	
		}
    }


VITORIA:
	time(&fim);
    bota_bandeiras(tab, lin, col);
    mostra_tab(tab, lin, col);
	tempo = inicio - fim;
    return tempo; //Do jogador
}



int ** gera_tabuleiro(int lin, int col){
    int i, j, **aux;

    aux = (int **) malloc(lin*sizeof(int *));

    for(i=0; i<lin; i++){
        aux[i] = (int *) calloc(col, sizeof(int)); 
    }  
    
    for(i=0; i<lin; i++){
        aux[i][0] = 7;
        aux[i][col-1] = 7;
    }

    for(j=0; j<col; j++){
        aux[0][j] = 7;
        aux[lin-1][j] = 7;
    }

    return aux;
}


void bombardeio(int **tab, int lin, int col, int bombas){
    int i, j;
    srand(time(NULL));

    while(bombas){
        i = rand()%lin + 1;
        j = rand()%col + 1;

        if(tab[i][j]==0){
            tab[i][j]=-1;
            bombas--;
        }
    }
} 


void mostra_tab(int **tab, int lin, int col){
    int i, j;
    char *simb = "*X@?";
    
	clear();
    printf("\n  ");
    for(j=1; j<=col; j++){
        printf("%3d", j);
    }
    printf("\n");

    for(i=1; i<=lin; i++){
        printf("%c:", 'A'+i-1);
        for(j=1; j<=col; j++){
            printf("\033[0m");
            
            if(tab[i][j]<-1){
                if(tab[i][j]==-41)
                    printf("\033[5;31m");
                if(tab[i][j]==-30)
                    printf("\033[31m");
                if(tab[i][j]/10==-2 || tab[i][j]/10==-1)
                    printf("\033[33m");
                printf("\033[1m%3c", simb[4+tab[i][j]/10]);
                continue;
            }

            if(tab[i][j]==-1 || tab[i][j]==0){
                printf("%3d", 0);
                continue;
            }

            if(tab[i][j]==9){
                printf("\033[2m%3c",'-');
                continue;   
            }
            
            if(tab[i][j]%4==1)
                printf("\033[34m");
            if(tab[i][j]%4==2)
                printf("\033[32m");
            if(tab[i][j]%4==3)
                printf("\033[31m");
            if(tab[i][j]%4==0)
                printf("\033[35m");

            printf("%3d", tab[i][j]);
        }
        printf("\033[0m \n"); 
    }
}


void descobre_minas(int **tab, int lin, int col){
    int i, j;

    for(i=1; i<=lin; i++){
        for(j=1; j<=col; j++){

            if(tab[i][j]/10==-2){
                if(tab[i][j]%10 != -1)
                    tab[i][j] = -30;
                continue;
            }

            if(tab[i][j]%10 == -1){
                tab[i][j] = -40;   
            }
        }
    }
}


int minas_arredores(int **tab, int i, int j){
    int cont = 0;

    if(tab[i-1][j-1]%10 == -1)
        cont++;

    if(tab[i-1][j]%10 == -1)
        cont++;

    if(tab[i-1][j+1]%10 == -1)
        cont++;

    if(tab[i][j-1]%10 == -1)
        cont++;

    if(tab[i][j+1]%10 == -1)
        cont++;

    if(tab[i+1][j-1]%10 == -1)
        cont++;

    if(tab[i+1][j]%10 == -1)
        cont++;

    if(tab[i+1][j+1]%10 == -1)
        cont++;

    return cont;
}


void descobre_blocos(int **tab, int i, int j){
    int minas = minas_arredores(tab, i, j);

    if(minas){
        tab[i][j] = minas;
        return;
    }

    tab[i][j] = 9;

    if(tab[i-1][j-1]<1 && tab[i-1][j-1]/10 != -2)
        descobre_blocos(tab, i-1, j-1);

    if(tab[i-1][j]<1 && tab[i-1][j]/10 != -2)
        descobre_blocos(tab, i-1, j);

    if(tab[i-1][j+1]<1 && tab[i-1][j+1]/10 != -2)
        descobre_blocos(tab, i-1, j+1);

    if(tab[i][j-1]<1 && tab[i][j-1]/10 != -2)
        descobre_blocos(tab, i, j-1);

    if(tab[i][j+1]<1 && tab[i][j+1]/10 != -2)
        descobre_blocos(tab, i, j+1);

    if(tab[i+1][j-1]<1 && tab[i+1][j-1]/10 != -2)
        descobre_blocos(tab, i+1, j-1);

    if(tab[i+1][j]<1 && tab[i+1][j]/10 != -2)
        descobre_blocos(tab, i+1, j);

    if(tab[i+1][j+1]<1 && tab[i+1][j+1]/10 != -2)
        descobre_blocos(tab, i+1, j+1);
}


int calcula_livres(int **tab, int lin, int col){
    int i, j, cont=0;

    for(i=1; i<=lin; i++){
        for(j=1; j<=col; j++){
            if(tab[i][j]%10==0)
                cont++;
        }
    }

    return cont;
}


void bota_bandeiras(int **tab, int lin, int col){
    int i, j;

    for(i=1; i<=lin; i++){
        for(j=1; j<=col; j++){
            if(tab[i][j]%10==-1)
                tab[i][j] = -21;
        }
    }
}
