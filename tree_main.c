/* tree_main.c
 * Driver program for a parser that builds an abstract syntax tree. 
 * Written by THC, modified by Steffi
 */ 

#include <stdio.h> 
#include "ast.h"
#include "table.h"
ast_node root = NULL; 

extern int yyparse(); 
extern int yydebug; 
int parseError = 0; 
table symbol_table;

int main(){
  int haveRoot = 0; 
  symbol_table = create_table();
  
  /*  yydebug = 1;*/
  haveRoot = yyparse(); 
 

  if (parseError)
    fprintf(stderr, "There was an error when forming the tree - it may be weird.\n"); 

  if (haveRoot == 0)
    print_ast(root, 0);

  return 0; 
}
