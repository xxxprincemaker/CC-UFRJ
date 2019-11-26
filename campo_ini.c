#include<stdio.h>
#include<stdlib.h>

/*

Em ANSI/VT100, você consegue alterar as informações do display.
ESC é representado por '^[' que para o printf (em octal) é \033 

Links uteis: 
    - http://www.termsys.demon.co.uk/vtansi.htm
    - https://espterm.github.io/docs/VT100%20escape%20codes.html

*/


int ** gera_tabuleiro(int lin, int col, int bombas);
void mostra_tab(int **tab, int lin, int col);


int main(){ 
    int **tab, lin, col, minas, livres;

    
    printf("Entre com as coordenadas do tabuleiro: ");
    scanf("%d%d", &lin, &col);    
    //printf("\033c"); limpa tudo da tela

    printf("Entre com o nÃºmero de minas: ");
    scanf("%d", &minas);

    tab = gera_tabuleiro(lin+2, col+2, minas);

    printf("\n");
    //printf("\033[33;47m");
    mostra_tab(tab, lin+2, col+2);

    livres = lin*col - minas;

    return 0;
}


void mostra_tab(int **tab, int lin, int col){
    int i, j;
    
    printf("   ");
    for(j=0; j<col; j++){
        printf("%d ", j);
    }
    printf("\n");

    for(i=0; i<lin; i++){
        printf("%d: ", i);
        for(j=0; j<col; j++){
            printf("%d ", tab[i][j]);
        }
        printf("\n"); 
    }
}


int ** gera_tabuleiro(int lin, int col, int bombas){
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

   // bombardeio(aux, lin, col, bombas);

    return aux;
}
