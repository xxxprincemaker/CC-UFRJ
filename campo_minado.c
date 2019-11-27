#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>


/*protótipos de função*/
int partida(int lin, int col, int minas);
int ** gera_tabuleiro(int lin, int col);
void mostra_tab(int **tab, int lin, int col);
void bombardeio(int **tab, int lin, int col, int bombas);
void descobre_minas(int **tab, int lin, int col);
int minas_arredores(int **tab, int i, int j);
void descobre_blocos(int **tab, int i, int j);
int calcula_livres(int **tab, int lin, int col);
void bota_bandeiras(int **tab, int lin, int col);


int main(){ 
    int lin, col, minas, resultado;
    char nome[25];
    system(" ");//Para fazer o VT100 funcionar no Windows 10
    
    printf("Entre com as coordenadas do tabuleiro: ");
    scanf("%d%d", &lin, &col);  

    printf("Entre com o numero de minas: ");
    scanf("%d", &minas);

    //vai ser chamado de acordo com o modo
    resultado = partida(lin, col, minas);

    if(resultado<0){
        printf("\nVoce perdeu!\n");
    }
    else{
        printf("\nParabens, voce venceu!!\n"); 
        printf("Por favor, digite o seu nome: ");
        scanf(" %[^\n]s", nome);

        /*Grava no arquivo se tiver batido record*/
    }

    return 0;
}



int partida(int lin, int col, int minas){
    int **tab, i, j, tempo=1;
    int c, livres, jogada;
    char op, l;

    tab = gera_tabuleiro(lin+2, col+2);
    bombardeio(tab, lin, col, minas);
    

    printf("\033c \n");
    mostra_tab(tab, lin, col);
    printf("\nEntre com a sua jogada: ");
    scanf(" %c %c", &op, &l);
    scanf(" %d", &c);
    printf("EI");

    /*O cronômetro começa*/

    livres = lin*col - minas;
    while(1){
        op = toupper(op);
        i = (toupper(l)-'A')+1;
        j = c;
        jogada = 0;

        switch(op){
            case '?':
                if(tab[i][j]==0 || tab[i][j]==-1)
                    tab[i][j] += -10;
                else if(tab[i][j]/10==-2)
                    tab[i][j] = tab[i][j]%10 - 10;
                else
                    jogada = 1;
                break;


            case '@':
                if(tab[i][j]==0 || tab[i][j]==-1)
                    tab[i][j] += -20;
                else if(tab[i][j]/10==-1)
                    tab[i][j] = tab[i][j]%10 - 20;
                else
                    jogada = 1;
                break;


            case 'R':
                if(tab[i][j]/10==-2 || tab[i][j]/10==-1)
                    tab[i][j] %= 10;
                else
                    jogada = 1; 
                break;

            
            case 'A':
                if(tab[i][j]/10!=-2 && tab[i][j]<1){
                    if(tab[i][j]%10==-1){
                        descobre_minas(tab, lin, col);
                        tab[i][j] = -41;

                        printf("\033c \n");
                        mostra_tab(tab, lin, col);
                        return -1;
                    }

                    descobre_blocos(tab, i, j);
                    livres = calcula_livres(tab, lin, col);
                    if(!livres)
                        goto VITORIA;
                }
                else
                    jogada = 1;
                break;


            default:
                jogada = 1;
        }

        printf("\033c \n");
        mostra_tab(tab, lin, col);
        if(jogada)
            printf("\nJogada invalida!");
        

        printf("\nEntre com a sua jogada: ");
        scanf(" %c %c %d", &op, &l, &c);
        printf("EI");
    }


VITORIA:
    bota_bandeiras(tab, lin, col);
    printf("\033c \n");
    mostra_tab(tab, lin, col);
    return tempo; //Do cronômetro
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
    
    printf("  ");
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
