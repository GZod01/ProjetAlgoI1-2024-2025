//  gcc .\main.c
//  .\a.exe

#define clear_screen() printf("\e[1;1H\e[2J")
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define ANSI_COLOR_RED     "\e[31m"
#define ANSI_COLOR_GREEN   "\e[32m"
#define ANSI_COLOR_RESET   "\e[0m"

/// @brief utiliser pour initialiser le tableau de jeu en le remplissant de 4
/// @param t le tableau de jeu
void initial(int t[6][2]){
    for (int i = 0; i < 6; i++){
        t[i][0]=4;
        t[i][1]=4;
    }
}

/// @brief convertit une position en coordonnées
/// @param x la position
/// @param c les coordonnées [x,y]
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

/// @brief affiche une valeur du tableau de jeu
/// @param pos la position de la valeur
/// @param t le tableau de jeu
/// @param pos_dep la position de départ si en jeu sinon -1
/// @param pos2 la position de jeu actuelle si en jeu sinon -1
void afficherValeur(int pos, int t[6][2], int pos_dep, int pos2){
    int coordpos[2],x,y;
    intVersPosition(pos,coordpos);
    x=coordpos[0];
    y=coordpos[1];
    if(pos_dep!=-1 && pos==pos_dep) printf(ANSI_COLOR_RED);
    else if(pos2!=-1 && pos==pos2) printf(ANSI_COLOR_GREEN);
    else printf(ANSI_COLOR_RESET);
    printf(" %i",t[x][y]);
}

#define aV(p) afficherValeur(p,t,pos1,pos2)

/// @brief affiche le tableau de jeu
/// @param t le tableau de jeu
/// @param pos1 la position de départ
/// @param pos2 la position de jeu actuelle
void superAfficherL(int t[6][2], int pos1, int pos2){
    clear_screen();
    printf("------------\n");
    printf(" f e d c b a\n");
    for (int i =12; i>6; i--) aV(i);
    printf(ANSI_COLOR_RESET "\n");
    for (int i=1;i<7;i++) aV(i);
    printf(ANSI_COLOR_RESET "\n");
    printf(" A B C D E F\n");
    printf("------------\n");
}

#define afficher(t) superAfficherL(t,-1,-1)

/// @brief prend l'input du joueur
/// @param i le numéro du joueur
/// @return renvoie la position choisie par le joueur
int joueur(int i){
    char n[1];
    do{
        printf("Quelle case voulez vous jouer joueur %i ?\n",i+1);
        fflush(stdin);
        scanf("%s",n);
    } while (strchr(i==0?"ABCDEFq":"abcdefq",n[0])==NULL);
    printf("Vous avez choisi la case %c\n",n[0]);
    int x;
    x=(int)n[0]-((i==0)?(((int)'A')-1):(((int)'a')-7));
    if (n[0]=='q')return -1;
    return x;
}

/// @brief action principale du jeu, joue les graines a partir d'une position
/// @param t le tableau de jeu
/// @param position_depart la position choisie par le joueur
/// @return retourne le nombre de graines volées
int graine(int t[6][2], int position_depart){
    int coord[2],coord_depart[2],nombre;
    int position=position_depart;
    intVersPosition(position_depart,coord);
    intVersPosition(position,coord_depart);
    nombre = t[coord_depart[0]][coord_depart[1]];
    int nombre_vol=0;
    while (nombre>0){
        position++;
        position=((position-1)%12)+1;
        if (position==position_depart)continue;
        intVersPosition(position,coord);
        if(coord_depart[1]!=coord[1] && t[coord[0]][coord[1]]==1 || t[coord[0]][coord[1]]==2){
            nombre_vol+=t[coord[0]][coord[1]];
            t[coord[0]][coord[1]]=0;
            superAfficherL(t,position_depart,position);
            sleep(1);
            continue;
        }
        t[coord[0]][coord[1]]++;
        t[coord_depart[0]][coord_depart[1]]--;
        superAfficherL(t,position_depart,position);
        sleep(1);
        nombre--;
    }
    return nombre_vol;
}

/// @brief fonction principale
/// @return 0
int main(){
    int t[6][2], numero_tour=0, n, coord[2];
    initial(t);
    int vol_joueur1=0, vol_joueur2=0;
    do{
        int ok=0;
        for(int i=0;i<6;i++){
            if(t[i][0]!=0 || t[i][1]!=0){
                ok=1;
            }
        }
        if(ok==0)break;
        afficher(t);
        printf("Vol joueur 1: %i\n",vol_joueur1);
        printf("Vol joueur 2: %i\n",vol_joueur2);
        n=joueur(numero_tour%2);
        if(n==-1)break;
        intVersPosition(n,coord);
        int res =graine(t,n);
        if(numero_tour%2==0)vol_joueur1+=res;
        else vol_joueur2+=res;
        numero_tour++;
    } while (1);
    printf("Fin de la partie\n");
    if(vol_joueur1>vol_joueur2)printf("Joueur 1 gagne\n");
    else if(vol_joueur1<vol_joueur2)printf("Joueur 2 gagne\n");
    else printf("Egalité\n");
    printf("Score joueur 1: %i\n",vol_joueur1);
    printf("Score joueur 2: %i\n",vol_joueur2);
    return 0;
}