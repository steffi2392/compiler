/* symtab.h
 * Declarations for the symbol table.
 * Written by THC for CS 57, extended by Steffi and Mehdi
 */
#include "ast.h"
#ifndef SYMTAB_H_
#define SYMTAB_H_

/* Node in a linked list within the symbol table. */

typedef enum {Int, Double, Void} types;
typedef enum {Function, Var, Array} id_type;

typedef struct symnode *symnode;
struct symnode {
  char *name;	    /* name in this symnode */
  symnode next;	    /* next symnode in list */
  id_type node_type;        /* 2 if Array, 1 if it's a var, 0 if function */
  types data_type;       /* data type */
  ast_node* parameters;
  int line_number;
  int offset; 
  };

/* Set the name in this node. */
void set_node_name(symnode node, char *name);

void set_node_type(symnode node, id_type type); 
void set_node_data_type(symnode node, types type);
void set_node_param(symnode node, ast_node* param);
/* Does the identifier in this node equal name? */
int name_is_equal(symnode node, char *name);

/* Is the node of type type? */
int type_is_equal(symnode node, types data); 

/* Does the node have the same attributes? */
/* Doesn't check type. DOES IT NEED TO CHECK TYPE? */ 
int node_is_equal(symnode node, char *name, id_type type); 

/* Hash table for a given scope in a symbol table. */

typedef struct symhashtable *symhashtable;
struct symhashtable {
  int size;			/* size of hash table */
  symnode *table;		/* hash table */
  symhashtable outer_scope;	/* ptr to symhashtable in next outer scope */
  int level;			/* level of scope, 0 is outermost */
};

/* Symbol table for all levels of scope. */

typedef struct symboltable *symboltable;
struct symboltable {
  symhashtable inner_scope;	/* pointer to symhashtable of innermost scope */
};

/* Create an empty symbol table. */
symboltable create_symboltable();

/* Destroy a symbol table. */
void destroy_symboltable(symboltable symtab);

/* Insert an entry into the innermost scope of symbol table.  First
   make sure it's not already in that scope.  Return a pointer to the
   entry. */
symnode insert_into_symboltable(symboltable symtab, char *name, id_type type, types data, int line_number);

/* Lookup an entry in a symbol table.  If found return a pointer to it
   and fill in level.  Otherwise, return NULL and level is
   undefined. */
symnode lookup_in_symboltable(symboltable symtab, char *name, id_type type, int *level);

/* Enter a new scope. */
void enter_scope(symboltable symtab);

/* Leave a scope. */
void leave_scope(symboltable symtab);

/* Print a symbol table. */
void print_symboltable(symboltable symtab);

#endif
