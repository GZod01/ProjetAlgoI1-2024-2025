#include <stdio.h>
#define hello() printf("Bonjour\n")
#define happyBirthday(x) printf("Joyeux anniversaire %s\n",x)
#define watchingSeriesSeasonEpisode(serie,season,episode) printf("Entrain de regarder %s Saison %i Episode %i\n",serie,season,episode)
#define goodBye 0
typedef int life;
life main(){
    hello();  
    happyBirthday("Ambre");
    watchingSeriesSeasonEpisode("Arcane",1,5);
    return goodBye;
}