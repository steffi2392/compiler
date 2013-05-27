/* symtab.c
 * Functions for the symbol table.
 * Written by THC for CS 57, extended by Steffi and Mehdi
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "symtab.h"

#define NOHASHSLOT -1

/*
 * Functions for symnodes.
 */

/* Create a symnode and return a pointer to it. */
static symnode create_symnode(char *name, id_type nodeType, types data, int line_number) {
  symnode node = malloc(sizeof(struct symnode));
  node->name = strdup(name);
  node->next = NULL;
  node->node_type = nodeType; 
  /* If it's an array, then it's the type of the content of the array */
  /* If it's a var then it's the type of the var (int double) */
  /* If function, return type (int, double, void) */ 
  node->data_type = data;
  printf("data_type set to: %d\n", data); 
  node->parameters = NULL;  
  node->line_number = line_number;
  return node;
}

/* Destroy a symnode. */
static void destroy_symnode(symnode node) {
  free(node->name);
  //free(node->type); 
  free(node);
}

/* Print a symnode. */
void print_symnode(symnode node, int num_spaces) {
  int i;
  for (i = 0; i < num_spaces; i++){
    printf(" ");
  }

  printf("Name: %s, Type: %d, isVar: %d \n", node->name, node->data_type, node->node_type);
}


/* Set the name in this node. */
void set_node_name(symnode node, char *name) {
  if (node->name != NULL)
    free(node->name);
  node->name = strdup(name);
}

/* Set the type in this node. */
void set_node_type(symnode node, id_type type){
  //if (node->type != NULL)
  //  free(node->type); 
  node->node_type = type; 
  }
  void set_node_data_type(symnode node, types type){
  //if (node->type != NULL)
  //  free(node->type); 
  node->data_type = type; 
}

/* Does the identifier in this node equal name? */
int name_is_equal(symnode node, char *name) {
  return !strcmp(node->name, name);
}

void set_node_param(symnode node, ast_node* param){
	if (node->node_type == Function)
		node->parameters = param;
	}
	
int type_is_equal(symnode node, types type) {
  return (node->data_type == type);
}

/* Doesn't need to check the type, because you can't have 2 variables with different types */ 
int node_is_equal(symnode node, char *name, id_type type) {
  return name_is_equal(node, name) && (node->node_type == type); 
}


/*
 * Functions for symhashtables.
 */

/* Create an empty symhashtable and return a pointer to it.  The
   parameter entries gives the initial size of the table. */
static symhashtable create_symhashtable(int entries) {
  symhashtable hashtable = malloc(sizeof(struct symhashtable));
  hashtable->size = entries;
  hashtable->table = calloc(entries, sizeof(struct symnode));
  int i;
  for (i = 0; i < entries; i++)
    hashtable->table[i] = NULL;
  hashtable->outer_scope = NULL;
  hashtable->level = -1;
  return hashtable;
}

/* Destroy a symhashtable. */
static void destroy_symhashtable(symhashtable hashtable) {
  int i;
  for (i = 0; i < hashtable->size; i++) {
    symnode node, next;

    for (node = hashtable->table[i]; node != NULL; node = next) {
      next = node->next;
      destroy_symnode(node);
    }
  }
}

/* Print a symhashtable. */
static void print_symhashtable(symhashtable hashtable, int num_spaces) {
  int i;
  for (i = 0; i < hashtable->size; i++) {
    symnode node, next;

    for (node = hashtable->table[i]; node != NULL; node = next) {
      next = node->next;
      print_symnode(node, num_spaces);
    }
  }
}

/* Peter Weinberger's hash function, from Aho, Sethi, & Ullman
   p. 436. */
static int hashPJW(char *s, int size) {
  unsigned h = 0, g;
  char *p;

  for (p = s; *p != '\0'; p++) {
      h = (h << 4) + *p;
      if ((g = (h & 0xf0000000)) != 0)
	h ^= (g >> 24) ^ g;
    }

  return h % size;
}

/* Look up an entry in a symhashtable, returning either a pointer to
   the symnode for the entry or NULL.  slot is where to look; if slot
   == NOHASHSLOT, then apply the hash function to figure it out. */
static symnode lookup_symhashtable(symhashtable hashtable, char *name,
				   id_type type, int slot) {
  symnode node;

  if (slot == NOHASHSLOT)
    slot = hashPJW(name, hashtable->size);

  for (node = hashtable->table[slot];
       node != NULL && !node_is_equal(node, name, type);
       node = node->next)
    ;

  return node;
}

/* Insert a new entry into a symhashtable, but only if it is not
   already present. */
static symnode insert_into_symhashtable(symhashtable hashtable, char *name, id_type type, types data, int line_number) {
  int slot = hashPJW(name, hashtable->size);
  symnode node = lookup_symhashtable(hashtable, name, type, slot);

  if (node == NULL) {
    node = create_symnode(name, type, data, line_number);
    node->next = hashtable->table[slot];
    hashtable->table[slot] = node;
  }

  return node;
}


/*
 * Functions for symboltables.
 */

static const int HASHSIZE = 211;

/* Create an empty symbol table. */
symboltable create_symboltable() {
  symboltable symtab = malloc(sizeof(struct symboltable));
  symtab->inner_scope = create_symhashtable(HASHSIZE);
  symtab->inner_scope->outer_scope = NULL;
  symtab->inner_scope->level = 0;
  return symtab;
}

/* Destroy a symbol table. */
void destroy_symboltable(symboltable symtab) {
  symhashtable table, outer;

  for (table = symtab->inner_scope; table != NULL; table = outer) {
    outer = table->outer_scope;
    destroy_symhashtable(table);
  }
}

/* Print a symbol table. */
void print_symboltable(symboltable symtab) {
  symhashtable table, outer;
  int num_spaces = 0;
  printf("\n Printing Symbol Table: \n");
  for (table = symtab->inner_scope; table != NULL; table = outer) {
    outer = table->outer_scope;
    print_symhashtable(table, num_spaces);
    num_spaces += 4;
  }
}

/* Insert an entry into the innermost scope of symbol table.  First
   make sure it's not already in that scope.  Return a pointer to the
   entry. */
symnode insert_into_symboltable(symboltable symtab, char *name, id_type type, types data, int line_number) {
  if (symtab->inner_scope == NULL) {
    fprintf(stderr, "Error: inserting into an empty symbol table\n");
    exit(1);
  }

  symnode node = lookup_symhashtable(symtab->inner_scope, name, type, NOHASHSLOT);

  if (node == NULL)
    node = insert_into_symhashtable(symtab->inner_scope, name, type, data, line_number);
  else {
	fprintf(stderr, "Error: ID has already been declared\n");
	exit(1);
	}
  return node;
}

/* Lookup an entry in a symbol table.  If found return a pointer to it
   and fill in level.  Otherwise, return NULL and level is
   undefined. */
symnode lookup_in_symboltable(symboltable symtab, char *name, id_type type, int *level) {
  symnode node;
  symhashtable hashtable;

  for (node = NULL, hashtable = symtab->inner_scope;
       node == NULL && hashtable != NULL;
       hashtable = hashtable->outer_scope) {
    node = lookup_symhashtable(hashtable, name, type, NOHASHSLOT);
    *level = hashtable->level;
  }

  return node;
}

/* Enter a new scope. */
void enter_scope(symboltable symtab) {
  symhashtable hashtable = create_symhashtable(HASHSIZE);
  hashtable->outer_scope = symtab->inner_scope;
  hashtable->level = symtab->inner_scope->level + 1;
  symtab->inner_scope = hashtable;
}

/* Leave a scope. */
void leave_scope(symboltable symtab) {
  symhashtable hashtable = symtab->inner_scope;
  symtab->inner_scope = hashtable->outer_scope;
  destroy_symhashtable(hashtable);
}
