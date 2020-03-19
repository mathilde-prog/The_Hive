//backup_and_load.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"

/******************** BACK_UP *************************/

/* save: save information about the character, his inventory, his equipment and the map. */
void save (perso_t player, int map[D][D]){
  save_info_player(player);
  save_inventory(player);
  save_equipment(player);
  save_map(map);
}

/* save_inventory: saves the player's inventory */
void save_inventory (perso_t player){
  int i;

  FILE * fic = fopen("txt/save_inventory.txt","w");
  for(i = 0; i < player.nb_items_inventory; i++){
    fprintf(fic,"%s %d\n%d %d %d\n%d %d %d\n\n",player.inventory[i].name, player.inventory[i].type, player.inventory[i].attack, player.inventory[i].defense, player.inventory[i].equipable, player.inventory[i].pc_nature, player.inventory[i].pc_urban, player.inventory[i].pc_military);
  }
  printf("save_inventory.txt - Successfully backed up!\n");
  fclose(fic);
}

/* save_info_player: saves player information */
void save_info_player (perso_t player){
  FILE * fic = fopen("txt/save_info_player.txt","w");
  fprintf(fic,"pv = %d\npe = %d\npa = %d\n", player.pv, player.pe, player.pa);
  fprintf(fic,"posX = %d\nposY = %d\n", player.posX, player.posY);
  fprintf(fic,"turns = %d\n", player.turns);

  /* No special competence for version 1 */
  //fprintf(fic,"competence = %d\n", player.competence);

  printf("save_info_player.txt - Successfully backed up!\n");
  fclose(fic);
}

/* save_equipment: saves the player's equipment */
void save_equipment (perso_t player){
  FILE * fic = fopen("txt/save_equipment.txt","w");

  (player.head != NULL) ? fprintf(fic, "head = %d\n", player.head->index) : fprintf(fic, "head = -1\n");
  (player.left_hand != NULL) ? fprintf(fic, "left_hand = %d\n", player.left_hand->index) : fprintf(fic, "left_hand = -1\n");
  (player.right_hand != NULL) ? fprintf(fic, "right_hand = %d\n", player.right_hand->index) : fprintf(fic, "right_hand = -1\n");
  (player.body != NULL) ? fprintf(fic, "body = %d\n", player.body->index) : fprintf(fic, "body = -1\n");

  printf("save_equipment.txt - Successfully backed up!\n");
  fclose(fic);
}

/* save_map: save the map of the game */
void save_map (int map[D][D]){
  int l, c;
  FILE * fic = fopen("txt/save_map.txt","w");

  for(l = 0; l < D; l++){
    for(c = 0; c < D; c++){
      fprintf(fic, "%2d ", map[l][c]);
    }
      fprintf(fic, "\n");
  }

  printf("save_map.txt - Successfully backed up!\n");
  fclose(fic);
}

/******************************************************/

/******************** LOAD ****************************/

/* load: load information about the character, his inventory, his equipment and the map. */
int load (perso_t * player, int map[D][D]){
  if(!load_inventory (player)){
    printf("Failed to load the inventory\n");
    return 0;
  }
  if(!load_info_player (player)){
    printf("Failed to load the character information\n");
    return 0;
  }
  if(!load_map(map)){
    printf("Failed to load the map\n");
    return 0;
  }
  if(!load_equipment (player)){
    printf("Failed to load the equipement\n");
    return 0;
  }

  return 1;
}

/* load_inventory: loads the player's inventory */
int load_inventory (perso_t * player){
  FILE * fic = fopen("txt/save_inventory.txt","r");
  player->nb_items_inventory = 0;
  if(fic){
    fscanf(fic,"%s%d%d%d%d%d%d%d",player->inventory[player->nb_items_inventory].name, &player->inventory[player->nb_items_inventory].type, &player->inventory[player->nb_items_inventory].attack, &player->inventory[player->nb_items_inventory].defense, &player->inventory[player->nb_items_inventory].equipable, &player->inventory[player->nb_items_inventory].pc_nature, &player->inventory[player->nb_items_inventory].pc_urban, &player->inventory[player->nb_items_inventory].pc_military);
    while(!feof(fic)){
      player->inventory[player->nb_items_inventory].index = player->nb_items_inventory;
      (player->nb_items_inventory)++;
      fscanf(fic,"%s%d%d%d%d%d%d%d",player->inventory[player->nb_items_inventory].name, &player->inventory[player->nb_items_inventory].type, &player->inventory[player->nb_items_inventory].attack, &player->inventory[player->nb_items_inventory].defense, &player->inventory[player->nb_items_inventory].equipable, &player->inventory[player->nb_items_inventory].pc_nature, &player->inventory[player->nb_items_inventory].pc_urban, &player->inventory[player->nb_items_inventory].pc_military);
    }
    fclose(fic);
    return 1;
  }
  else {
    printf("Error, 'save_inventory.txt' not found...\n");
    return 0;
  }
}

/* load_info_player: loads player information */
int load_info_player (perso_t * player){
  FILE * fic = fopen("txt/save_info_player.txt","r");
  if(fic){
    // Version avec compétence spéciale (pas en version1)
    // fscanf(fic,"pv = %d\npe = %d\npa = %d\nposX = %d\nposY = %d\ncompetence = %d\nturns = %d\n",&player->pv, &player->pe, &player->pa, &player->posX, &player->posY, &player->competence, &player->turns);
    fscanf(fic,"pv = %d\npe = %d\npa = %d\nposX = %d\nposY = %d\nturns = %d\n",&player->pv, &player->pe, &player->pa, &player->posX, &player->posY, &player->turns);
    fclose(fic);
    return 1;
  }
  else {
    printf("Error, 'save_info_player.txt' not found...\n");
    return 0;
  }
}

/* load_equipment: loads the player's equipment */
int load_equipment (perso_t * player){
  FILE * fic = fopen("txt/save_equipment.txt","r");
  int ind_head = 0, ind_lh = 0, ind_rh = 0, ind_body = 0;

  if(fic){
    fscanf(fic,"head = %d\nleft_hand = %d\nright_hand = %d\nbody = %d\n", &ind_head, &ind_lh, &ind_rh, &ind_body);
    (ind_head != -1) ? (player->head = &player->inventory[ind_head]) : (player->head = NULL);
    (ind_lh != -1) ? (player->left_hand = &player->inventory[ind_lh]) : (player->left_hand = NULL);
    (ind_rh != -1) ? (player->right_hand = &player->inventory[ind_rh]) : (player->right_hand = NULL);
    (ind_body != -1) ? (player->body = &player->inventory[ind_body]) : (player->body = NULL);

    fclose(fic);
    return 1;
  }
  else {
    printf("Error, 'save_equipment.txt' not found...\n");
    return 0;
  }
}

/* load_map: loads the map of the game */
int load_map (int map[D][D]){
  int l, c;
  FILE * fic = fopen("txt/save_map.txt","r");

  if(fic){
    for(l = 0; l < D; l++){
      for(c = 0; c < D; c++){
        fscanf(fic,"%d",&map[l][c]);
      }
    }
    fclose(fic);
    return 1;
  }
  else {
    printf("Error, 'save_map.txt' not found...\n");
    return 0;
  }
}

/*****************************************************/
/* backup_exists: returns 1 if a backup exists and 0 if there is none */
int backup_exists (){
  FILE * fic1, * fic2, * fic3, * fic4;
  fic1 = fopen("txt/save_inventory.txt","r");
  fic2 = fopen("txt/save_equipment.txt","r");
  fic3 = fopen("txt/save_info_player.txt","r");
  fic4 = fopen("txt/save_map.txt","r");

  if(fic1){
    fclose(fic1);
    if(fic2){
      fclose(fic2);
      if(fic3){
        fclose(fic3);
        if(fic4){
          fclose(fic4);
          return 1;
        }
      }
    }
  }
  return 0;
}

/* init_or_load_game:
   If a backup of the game exists, offers the player to continue the game or start a new one.
   Loads the game if saved, otherwise uses functions to initialize the player and the map.
*/
int init_or_load_game(perso_t * player, int map[D][D]){
  int choise;

  if(backup_exists()){
    printf("1. Continue the game saved last time\n");
    printf("2. New game\n");
    printf("Exit: -1\n\n");

    do {
      printf("N°");
      scanf("%d",&choise);
      if((choise != -1) && (choise < 1 || choise > 2)){
        printf("Incorrect value, please re-enter\n");
      }
    } while ((choise != -1) && (choise < 1 || choise >2));

    if(choise != -1){
      switch (choise){
        case 1: return load(player, map); break;
        case 2: init_player(player);
                map_init(map);
                return 1;
                break;
        default: break;
      }
    }
  }
  else {
      init_player(player);
      map_init(map);
      return 1;
  }
  return 0;
}