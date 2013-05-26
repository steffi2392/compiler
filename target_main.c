/* target_main.c
 * Driver program for generating target code. 
 */ 

#include "intermediate.h" 
//#include "ast.h"
#include "symtab.h"

//extern int yyparse(); 
extern int yydebug; 
//int parseError =0; 
//table symbol_table; 
//symboltable symtab;

int main(){
  //  int haveRoot = 0; 
  //symbol_table = create_table(); 

  //haveRoot = yyparse(); 

  
  quad x_dec = create_quad(vardec); 
  x_dec->address1 = "int"; 
  x_dec->address2 = "x"; 

  quad y_dec = create_quad(vardec); 
  y_dec->address1 = "double"; 
  y_dec->address2 = "y"; 

  quad_list code = create_quad_list(); 
  code->first = x_dec; 
  x_dec->next = y_dec; 
  y_dec->next = x_dec; 
  

  print_code(code); 
  generate_target(code); 
}
