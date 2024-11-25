//  gcc .\main.c
//  .\a.exe
#ifdef _WIN32
#include <conio.h>
#else
#include <stdio.h>
#define clrscr() printf("\e[1;1H\e[2J")
#endif
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int initial(int t[6][2]){
    int i;
    for ( i = 0; i < 6; i++){
        t[i][0]=4;
    }
    for ( i = 0; i < 6; i++){
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

char* afficherValeur(int x, int y, int t[6][2], int pos_dep, int pos2){
    // char couleur[10]="\x1b[0m";
    printf("cool%i,%i",x,y);
    char colortogo='d';
    int coordpos[2],coordpos2[2];
    if(pos_dep!=-1){
        intVersPosition(pos_dep,coordpos);
    }
    if(pos2!=-1){
        intVersPosition(pos2,coordpos2);
    }
    if(pos_dep!=-1 && coordpos[0]==x && coordpos[1]==y){
        // printf("cool%i,%i",x,y);
        colortogo='r';
    }
    else if(pos2!=-1 && coordpos2[0]==x && coordpos2[1]==y){
        // printf("cool2%i,%i",x,y);
        colortogo='g';
    }
    // switch (colortogo){
    //     case 'r':
    //         strcpy(couleur,"\x1b[31m");
    //         break;
    //     case 'g':
    //         strcpy(couleur,"\x1b[32m");
    //         break;
    //     case 'y':
    //         strcpy(couleur,"\x1b[33m");
    //         break;
    //     default:
    //         strcpy(couleur,"\x1b[0m");
    //         break;
    // }
    static char returnval[100];
    if(colortogo=='r'){
        sprintf(returnval,ANSI_COLOR_RED "%c%i(%i,%i)(%i,%i)\t",colortogo,t[x][y],x,y,pos_dep,pos2);
    }
    else if (colortogo=='g'){
        sprintf(returnval, ANSI_COLOR_GREEN "%c%i(%i,%i)(%i,%i)\t",colortogo,t[x][y],x,y,pos_dep,pos2);
    }
    else{
        sprintf(returnval, ANSI_COLOR_RESET "%c%i(%i,%i)(%i,%i)\t",colortogo,t[x][y],x,y,pos_dep,pos2);
    }
    {
        /* code */
    }
    
    return returnval;
}

#define aV(x,y) afficherValeur(x,y,t,pos1,pos2)


void superAfficherL(int t[6][2], int pos1, int pos2){
    clrscr();
    // printf("%i,%i\n",pos1,pos2);
    printf("-------------\n");
    printf(" f e d c b a\n");
    printf(" %s %s %s %s %s %s\n" ANSI_COLOR_RESET, aV(0,0),aV(1,0),aV(2,0),aV(3,0),aV(4,0),aV(5,0));
    printf(" %s %s %s %s %s %s\n" ANSI_COLOR_RESET, aV(0,1),aV(1,1),aV(2,1),aV(3,1),aV(4,1),aV(5,1));
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
        sleep(1);
        superAfficherL(t,position_depart,position);
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