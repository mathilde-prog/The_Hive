#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structure.h"

int main(){
  srand(time(NULL));

  cell_t map[D][D];
  perso_t player;
  item_t * Tab_Items = malloc(20 * sizeof(item_t));
  int nb_items_available = 0;

  creation_tab_item(Tab_Items, &nb_items_available);

  map_init(map);
  init_player(&player);

  check_the_map(player,map);

  item_t * fishing_rod = creer_item("fishing_rod",misc,0,0,0,0,0,0,0,0,0,0,0);
  item_t * map_item = creer_item("map",misc,0,0,0,0,0,0,0,0,0,0,0);
  item_t * medical_kit = creer_item("medical_kit",misc,0,0,0,0,0,0,0,0,0,0,0);

  printf("TEST map : \n");
  (item_in_inventory(player,"map") == -1) ? printf("Test OK\n") : printf("Test KO\n");
  add_item_to_inventory(&player,*map_item);
  (item_in_inventory(player,"map") != -1) ? printf("Test OK\n\n") : printf("Test KO\n\n");

  printf("TEST fishing_rod : \n");
  (item_in_inventory(player,"fishing_rod") == -1) ? printf("Test OK\n") : printf("Test KO\n");
  add_item_to_inventory(&player,*fishing_rod);
  item_in_inventory(player,"fishing_rod") != -1 ? printf("Test OK\n\n") : printf("Test KO\n\n");

  printf("TEST medical_kit : \n");
  (item_in_inventory(player,"medical_kit") == -1) ? printf("Test OK\n") : printf("Test KO\n");
  add_item_to_inventory(&player,*medical_kit);
  (item_in_inventory(player,"map") != -1) ? printf("Test OK\n") : printf("Test KO\n");

  return EXIT_SUCCESS;
}