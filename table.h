/* table.h
 */ 

#ifndef TABLE_H
#define TABLE_H

typedef struct table_struct *table; 
struct table_struct {
  char** id_list; 
  int capacity; /* capacity of the list */
  int num; /* number of things in the list */ 
};

table create_table(); 
char* add_id(table t, char* id); 
char * lookup(table t, char *id); 

#endif
