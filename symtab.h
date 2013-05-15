/* symtab.h
 * Declarations for the symbol table.
 * Written by THC for CS 57, extended by Steffi and Mehdi
 */

#ifndef SYMTAB_H_
#define SYMTAB_H_

/* Node in a linked list within the symbol table. */

typedef struct symnode *symnode;
struct symnode {
  char *name;	    /* name in this symnode */
  symnode next;	    /* next symnode in list */
  int isVar;        /* 1 if it's a var, 0 if function */
  char *type;       /* data type */
};

/* Set the name in this node. */
void set_node_name(symnode node, char *name);

void set_node_type(symnode node, char *type); 

/* Does the identifier in this node equal name? */
int name_is_equal(symnode node, char *name);

/* Is the node of type type? */
int type_is_equal(symnode node, char *type); 

/* Does the node have the same attributes? */
/* Doesn't check type. DOES IT NEED TO CHECK TYPE? */ 
int node_is_equal(symnode node, char *name, int isVar); 

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

/* Print a symbol table. */ 
void print_symboltable(symboltable symtab); 

/* Insert an entry into the innermost scope of symbol table.  First
   make sure it's not already in that scope.  Return a pointer to the
   entry. */
symnode insert_into_symboltable(symboltable symtab, char *name, int isVar, char *type);

/* Lookup an entry in a symbol table.  If found return a pointer to it
   and fill in level.  Otherwise, return NULL and level is
   undefined. */
symnode lookup_in_symboltable(symboltable symtab, char *name, int isVar, int *level);

/* Enter a new scope. */
void enter_scope(symboltable symtab);

/* Leave a scope. */
void leave_scope(symboltable symtab);

#endif
