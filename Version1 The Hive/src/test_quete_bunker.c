#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include "lib/structure.h"

int main(){
  srand(time(NULL));
  clrscr();

  int choix;
  perso_t player;
  quete_t quete;
  cell_t map[D][D];
  int quest_map[6][2];
  int sortie = 0;

  item_t * pass_card = creer_item("pass card", misc, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);

  init_player(&player);
  map_init(map,quest_map,player);
  init_quete(&quete,quest_map);

  printf ("\033[34;01m\n   Menu test quête bunker\033[00m\n");
  printf("   1. Avec pass\n");
  printf("   2. Sans pass\n");
  printf("\n   Votre réponse : ");
  saisie:
  scanf("%d", &choix);
  if(choix == 1){
    add_item_to_inventory(&player,*pass_card);
  }
  else if (choix != 2){
    printf("   Veuillez ressaisir : ");
    goto saisie;
  }

  clrscr();

  sortie = quete_bunker(&player,&quete);
  switch(sortie){
    case 0: printf("\n   Le jeu continue!\n"); break;
    case 1: printf("\n   Fin du jeu\n"); break;
    case -1: printf("\n   Pb dans la quête\n"); break;
    default: break;
  }

  free(pass_card);
}
