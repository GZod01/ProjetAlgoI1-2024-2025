//  gcc .\main.c
//  .\a.exe
#define clrscr() printf("\e[1;1H\e[2J")
#include <stdio.h>
#include <string.h>
#include <unistd.h>


#define ANSI_COLOR_RED     "\e[31m"
#define ANSI_COLOR_GREEN   "\e[32m"
#define ANSI_COLOR_RESET   "\e[0m"

void initial(int t[6][2]){
    int i;
    for ( i = 0; i < 6; i++){
        t[i][0]=4;
        t[i][1]=4;
    }
}
void intVersPosition(int x, int c[2]){
    if (x<=6){
        c[0]=x-1;
        c[1]=1;
    }
    else{
        c[0]=12-x;
        c[1]=0;
    }
}

void afficherValeur(int pos, int t[6][2], int pos_dep, int pos2){
    int coordpos[2],x,y;
    intVersPosition(pos,coordpos);
    x=coordpos[0];
    y=coordpos[1];
    if(pos_dep!=-1 && pos==pos_dep){
        printf(ANSI_COLOR_GREEN " %i",t[x][y]);
        return;
    }
    else if(pos2!=-1 && pos==pos2){
        printf( ANSI_COLOR_RED " %i",t[x][y]);
        return;
    }else{
        printf(ANSI_COLOR_RESET " %i",t[x][y]);
        return;
    }
}

#define aV(p) afficherValeur(p,t,pos1,pos2)


void superAfficherL(int t[6][2], int pos1, int pos2){
    clrscr();
    // printf("%i,%i\n",pos1,pos2);
    printf("-------------\n");
    printf(" f e d c b a\n");
    aV(12);aV(11);aV(10);aV(9);aV(8);aV(7);
    printf(ANSI_COLOR_RESET "\n");
    aV(1);aV(2);aV(3);aV(4);aV(5);aV(6);
    printf(ANSI_COLOR_RESET "\n");
    printf(" A B C D E F\n");
    printf("-------------\n");
}
#define afficher(t) superAfficherL(t,-1,-1)

int joueur(int i){
    char n[1];
    do{
        printf("Quelle case voulez vous jouer joueur %i ?\n",i+1);
        fflush(stdin);
        scanf("%s",n);
    } while (strchr(i==0?"ABCDEF":"abcdef",n[0])==NULL);
    printf("Vous avez choisi la case %c\n",n[0]);
    int x;
    x=(int)n[0]-((i==0)?(((int)'A')-1):(((int)'a')-7));
    return x;
}



void graine(int t[6][2], int position_depart){
    int coord[2],coord_depart[2],nombre;
    int position=position_depart;
    intVersPosition(position_depart,coord);
    intVersPosition(position,coord_depart);
    nombre = t[coord_depart[0]][coord_depart[1]];
    while (nombre>0){
        position++;
        position=((position-1)%12)+1;
        if (position==position_depart){
            continue;
        }
        intVersPosition(position,coord);
        t[coord[0]][coord[1]]++;
        t[coord_depart[0]][coord_depart[1]]--;
        fflush(stdout);
        superAfficherL(t,position_depart,position);
        sleep(1);
        nombre--;

    }
}

int main(){
    int t[6][2], numero_tour=0, n, coord[2];
    initial(t);
    do{
        afficher(t);
        n=joueur(numero_tour%2);
        intVersPosition(n,coord);
        graine(t,n);
        numero_tour++;
    } while (1);
}