/* target_main.c
 * Driver program for generating target code. 
 */ 

#include <stdlib.h>
#include "intermediate.h" 
#include "ast.h"
#include "symtab.h"

static void test1(); 

//extern int yyparse(); 
extern int yydebug; 
//int parseError =0; 
//table symbol_table; 
//symboltable symtab;

int main(){
  test1(); 
  //  int haveRoot = 0; 
  //symbol_table = create_table(); 

  //haveRoot = yyparse(); 
  /*
  quad x_dec = create_quad(vardec); 
  x_dec->address1 = "int"; 
  x_dec->address2 = "x"; 

  quad y_dec = create_quad(vardec); 
  y_dec->address1 = "double"; 
  y_dec->address2 = "y"; 

  quad halt_quad = create_quad(halt); 

  quad_list code = create_quad_list(); 
  code->first = x_dec; 
  x_dec->next = y_dec; 
  y_dec->next = halt_quad; 
  halt_quad->next = x_dec; 
  

  print_code(code); 
  generate_target(code); 
  */ 
}

/* int x; 
 * double y; 
 *
 * int f(){
 *   x = 0; 
 *   x = x + 1; 
 *   return x; 
 * }
 * 
 * int main(){
 *   f(); 
 * }
 */ 
static void test1(){
  quad_list code = create_quad_list(); 

  add_to_code(code, create_full_quad(vardec, "int", "x", NULL)); 
  add_to_code(code, create_full_quad(vardec, "double", "y", NULL)); 
  add_to_code(code, create_full_quad(func_dec, "int", "f", NULL)); 
  add_to_code(code, create_full_quad(enter, NULL, NULL, NULL)); 
  add_to_code(code, create_full_quad(assn, "x", "0", NULL)); 
  add_to_code(code, create_full_quad(add, "t0", "x", "1")); 
  add_to_code(code, create_full_quad(assn, "x", "t0", NULL)); 
  add_to_code(code, create_full_quad(rtrn, "x", NULL, NULL)); 
  add_to_code(code, create_full_quad(leave, NULL, NULL, NULL)); 
  add_to_code(code, create_full_quad(exit_sub, NULL, NULL, NULL)); 
  add_to_code(code, create_full_quad(func_dec, "int", "main", NULL));
  add_to_code(code, create_full_quad(enter, NULL, NULL, NULL));
  add_to_code(code, create_full_quad(goto_sub, "f", NULL, NULL));
  add_to_code(code, create_full_quad(get_rtrn, "t1", NULL, NULL));
  add_to_code(code, create_full_quad(leave, NULL, NULL, NULL));
  add_to_code(code, create_full_quad(exit_sub, NULL, NULL, NULL));
  add_to_code(code, create_full_quad(halt, NULL, NULL, NULL));
  add_to_code(code, create_full_quad(end, NULL, NULL, NULL)); 

  print_code(code);
  generate_target(code);
}
