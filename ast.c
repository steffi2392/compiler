/* ast.c
 *
 * Written by THC for CS 57.  Relies on an enum and a struct for
 * various node types that appear in ast.h.  You should modify the
 * enum and struct as appropriate.
 *
 * This file contains functions to create a node and to print out an
 * abstract syntax tree, for debugging.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

/* Define a table of token types and their associated strings.  You
   should modify this table as appropriate.  The order of entries
   should match the order of enumerated values in ast_node_type. */
struct token_lookup {
  char *token;
  ast_node_type node_type;
};
static struct token_lookup token_table[] = {
  { "ROOT", ROOT },
  { "=", OP_ASSIGN },
  { "+", OP_PLUS },
  { "-", OP_MINUS },
  { "-", OP_NEG },
  { "*", OP_TIMES },
  { "/", OP_DIVIDE },
  { "==", OP_EQUALS },
  {"!=",OP_NEQUALS },
  {"%", OP_MOD},
  {"<", OP_LT},
  {"<=", OP_LEQ},
  {">",OP_GT},
  {">=", OP_GEQ},
  {"&&", OP_AND},
  {"||", OP_OR},
  {"!", OP_NOT},
  {"++", OP_INC},
  {"--", OP_DEC},
  { "IF", IF_STMT },
  {"IFELSE", IF_ELSE_STMT },
  {"WHILE", WHILE_STMT},
  {"DOWHILE",DO_WHILE_STMT},
  {"FOR",FOR_STMT},
  {"READ",READ_STMT},
  {"PRINT",PRINT_STMT},
  {"RETURN",RETURN_STMT},
  {"ID", IDENT },
  {"CALL", CALL},
  {"INT", INT_TYPE},
  {"DOUBLE", DOUBLE_TYPE},
  {"VOID", VOID_TYPE},
  {"FUNC DEC", FUNCDEC},
  {"CMPD", CMPD},
  {"ARRAY", ARRAY},
  {"INTLIT", INT_LITERAL },
  {"DOUBLELIT", DOUBLE_LITERAL },
  {"PARAMETERS", PARAMS},
  {"STRING",STRING_LIT },
  {"START", FOR_STRT},
  {"CONDITION", FOR_COND},
  {"UPDATE", FOR_UPDT},
  { NULL, 0 }
};

/* Create a node with a given token type and return a pointer to the
   node. */
ast_node create_ast_node(ast_node_type node_type) {
  ast_node new_node = malloc(sizeof(struct ast_node_struct));
  new_node->node_type = node_type;
  new_node->left_child = new_node->right_sibling = NULL;
  new_node->isVar = 1; 
  //  new_node->code = create_quad_list(); 
  return new_node;
}

/* Print the contents of a subtree of an abstract syntax tree, given
   the root of the subtree and the depth of the subtree root. */
void print_ast(ast_node root, int depth) {
  /* Print two spaces for every level of depth. */
  int i;
  for (i = 0; i < depth; i++)
    printf("  ");

  /* Print the node type. */
  printf("%s ", token_table[root->node_type].token);

  /* Print attributes specific to node types. */
  switch (root->node_type) {
  case IDENT:			/* print the id */
    printf("%s", root->value.string);
    break;

  case INT_LITERAL:		/* print the int literal */
    printf("%d", root->value.int_value);
    break;
    
  case DOUBLE_LITERAL:		/* print the double literal */
    printf("%f", root->value.double_value);
    break;
  
  case STRING_LIT:             /* print the string literal */
    printf("%s", root->value.string);
    break;

  default:
    break;
  }

  printf("\n");

  /* Recurse on each child of the subtree root, with a depth one
     greater than the root's depth. */
  ast_node child;
  for (child = root->left_child; child != NULL; child = child->right_sibling)
    print_ast(child, depth + 1);
}  
