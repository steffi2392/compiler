/* table.c
 */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"

table create_table(){
  table new_table = (table) malloc(sizeof(struct table_struct));
  new_table->id_list = (char**) malloc(10 * sizeof(char*)); 
  new_table->capacity = 10; 
  new_table->num = 0; 
  return new_table; 
}

char* add_id(table t, char *id){
  if(t->num >= t->capacity) {
     t->id_list = (char**) realloc(t->id_list, t->capacity * 2 * sizeof(char*)); 
   // t = (table) realloc(t, t->capacity * 2 * sizeof(char*)); 
    t->capacity *= 2; 
  }

  t->id_list[t->num] = strdup(id); 
  t->num++;
  return t->id_list[t->num-1];
}

char * lookup(table t, char *id){
  int i; 
  for (i = 0; i < t->num; i++){
    if (strcmp(t->id_list[i], id) == 0){
      return t->id_list[i]; 
    }
  }
  return NULL; 
}
