#include <stdio.h>
#include "ast.h"
#include "table.h"
#include "symtab.h"
#include "typecheck.h" 

ast_node root = NULL;

// test: 
//void buildSymTab(ast_node parent, symboltable symtab);

extern int yyparse();
extern int yydebug;
int parseError = 0;
symboltable symtab;
table symbol_table; 

  int main(){
    int haveRoot = 0;
    symtab = create_symboltable();
    symbol_table = create_table(); 
    /*  yydebug = 1;*/
    haveRoot = yyparse();


    if (parseError)
      fprintf(stderr, "There was an error when forming the tree - it may be weird.\n");

    if (haveRoot == 0) {
      print_ast(root, 0);
      traverse(root, symtab); 
      print_symboltable(symtab); 
    }

    int level; 
    symnode x = lookup_in_symboltable(symtab, "x", 1, &level); 
    if (x == NULL)
      printf("Did not find x.\n");
    else
      printf("Found x at level %d.\n", level); 
    return 0;
  }

