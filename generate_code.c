File Edit Options Buffers Tools C Help                                                             
#include <stdio.h>
#include "ast.h"
#include "table.h"
#include "symtab.h"
#include "typecheck.h"

ast_node root = NULL;

int main(){
  root = create_ast_node(ROOT); 
  ast_node minus = create_ast_node(OPMINUS); 
  ast_node assign = create_ast_node(OP_ASSIGN); 
  ast_node plus = create_ast_node(OP_PLUS);
 
  ast_node x = create_ast_node(IDENT); 
  x->value.string = "x"; 

  ast_node y = create_ast_node(IDENT);
  y->value.string = "y";

  ast_node z = create_ast_node(IDENT);
  z->value.string = "z"; 

  ast_node three = create_ast_node(INT_TYPE); 
  three->value.int_value = 3; 

  root->left_child = minus; 
  minus->left_child = assign; 
  minus->left_child->right_sibling = z; 

  minus->left_child = x; 
  minus->left_child->right_sibling = plus; 

  plus->left_child = y; 
  plus->left_child->right_sibling = three; 

    
}



