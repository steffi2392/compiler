#include <stdio.h>
#include "ast.h"
#include "table.h"
#include "symtab.h"
#include "typecheck.h"

ast_node root = NULL;

extern int yyparse(); 
extern int yydebug; 
int parseError = 0; 
symboltable symtab; 
table symbol_table; 

int main(){
  // manually set up the tree
  root = create_ast_node(ROOT); 
  ast_node minus = create_ast_node(OP_MINUS); 
  ast_node assign = create_ast_node(OP_ASSIGN); 
  ast_node plus = create_ast_node(OP_PLUS);
 
  ast_node x = create_ast_node(IDENT); 
  x->value.string = "x"; 

  ast_node y = create_ast_node(IDENT);
  y->value.string = "y";

  ast_node z = create_ast_node(IDENT);
  z->value.string = "z"; 

  ast_node three = create_ast_node(INT_LITERAL); 
  three->value.int_value = 3; 

  root->left_child = minus; 
  minus->left_child = assign; 
  minus->left_child->right_sibling = z; 

  assign->left_child = x; 
  assign->left_child->right_sibling = plus; 

  plus->left_child = y; 
  plus->left_child->right_sibling = three; 

  // now actually do stuff with it
  generate_traverse(root); 
  print_ast(root, 0); 
  print_code(root->left_child->code); 
}



