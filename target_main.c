/* target_main.c
 * Driver program for generating target code. 
 */ 

#include <stdlib.h>
#include "intermediate.h" 
#include "ast.h"
#include "symtab.h"

static void test1(); 
static void while_test(); 

//extern int yyparse(); 
extern int yydebug; 
//int parseError =0; 
//table symbol_table; 
//symboltable symtab;

int main(){
  test1(); 

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

static void while_test(){
  quad_list code = create_quad_list(); 

  add_to_code(code, create_full_quad(vardec, "int", "x", NULL)); 
  add_to_code(code, create_full_quad(func_dec, "int", "main", NULL)); 
  add_to_code(code, create_full_quad(enter, NULL, NULL, NULL)); 
  add_to_code(code, create_full_quad(vardec, "int", NULL, NULL)); 
  add_to_code(code, create_full_quad(lt, "t0", "y", "5")); 

  print_code(code); 
  generate_target(code); 
}
