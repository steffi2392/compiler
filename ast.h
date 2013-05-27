/* 
 * ast.h
 *
 * File defining an enum and a struct for node types in an abstract
 * syntax tree.
 *
 * Written by THC for CS 57.  You should modify this file as
 * appropriate.
 *
 */

#ifndef AST_H_
#define AST_H_

#include "intermediate.h"

/* You should fill in the various node types.  The following are given
   to you to start with.  You may add or remove node types as you
   wish. */
typedef enum { ROOT, 
	       OP_ASSIGN, OP_PLUS, OP_MINUS, OP_NEG, OP_TIMES, OP_DIVIDE,
	       OP_EQUALS, OP_NEQUALS, OP_MOD, OP_LT, OP_LEQ, OP_GT, 
	       OP_GEQ, OP_AND, OP_OR, OP_NOT, OP_INC, OP_DEC, 
	       IF_STMT, IF_ELSE_STMT, WHILE_STMT, DO_WHILE_STMT, FOR_STMT,
	       READ_STMT, PRINT_STMT, RETURN_STMT,
	       IDENT, CALL, 
	       INT_TYPE, DOUBLE_TYPE,VOID_TYPE, FUNCDEC, CMPD, 
	       ARRAY,
	       INT_LITERAL, DOUBLE_LITERAL, PARAMS, STRING_LIT, FOR_STRT, FOR_COND, FOR_UPDT, ARGS} ast_node_type;
		   
typedef enum {Int, Double, Void} types;

/* Structure for nodes of the abstract syntax tree.  Uses the
   left-child/right-sibling representation, so that each node can have
   a variable number of children.  You should add or remove fields as
   appropriate. */
typedef struct ast_node_struct *ast_node;

struct ast_node_struct {
  ast_node_type node_type;
  ast_node left_child, right_sibling;
  types type; 	
  int line_number;	
 union {
    char * string;		/* for ID */
    int int_value;		/* for INT_LITERAL */
    double double_value;	/* for DOUBLE_LITERAL */
  } value;

  // for quad generation: 
  quad_list code; 
  char * location; 
};

/* Create a node with a given token type and return a pointer to the
   node. */
ast_node create_ast_node(ast_node_type node_type, int line_number);

/* Print the contents of a subtree of an abstract syntax tree, given
   the root of the subtree and the depth of the subtree root. */
void print_ast(ast_node root, int depth);

// MAYBE THIS SHOULDN'T GO HERE BUT I'M BAD AT LINKING FILES AND THIS WORKS
void generate_traverse(ast_node node);
quad_list create_quad_list();
void print_code(quad_list code);
void reset_num_quads();
void add_to_code(quad_list code, quad q); 
#endif
