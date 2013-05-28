/* target_main.c
 * Driver program for generating target code. 
 */ 

#include <stdlib.h>
#include "intermediate.h" 
#include "ast.h"
#include "symtab.h"

static void test1(); 
static void while_test(); 
static void dowhile_test(); 
static void if_test(); 

//extern int yyparse(); 
extern int yydebug; 
//int parseError =0; 
//table symbol_table; 
//symboltable symtab;

int main(){
  //  test1(); 
  //  while_test(); 
  //  dowhile_test(); 
  if_test(); 
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
  add_to_code(code, create_full_quad(vardec, "int", "y", NULL));
  add_to_code(code, create_full_quad(assn, "y", "1", NULL)); 
  add_to_code(code, create_full_quad(whileloop, NULL, NULL, NULL)); 
  add_to_code(code, create_full_quad(lt, "t0", "y", "5")); 
  add_to_code(code, create_full_quad(ifFalse, "t0", "14", NULL)); 
  add_to_code(code, create_full_quad(enter, NULL, NULL, NULL)); 
  add_to_code(code, create_full_quad(mult, "t1", "y", "2")); 
  add_to_code(code, create_full_quad(assn, "x", "t1", NULL)); 
  add_to_code(code, create_full_quad(add, "t2", "y", "1")); 
  add_to_code(code, create_full_quad(assn, "y", "t2", NULL)); 
  add_to_code(code, create_full_quad(leave, NULL, NULL, NULL));
  add_to_code(code, create_full_quad(end_whileloop, NULL, NULL, NULL)); 
  add_to_code(code, create_full_quad(jumpTo, "3", NULL, NULL)); 
  add_to_code(code, create_full_quad(assn, "x", "3", NULL)); 
  add_to_code(code, create_full_quad(leave, NULL, NULL, NULL)); 
  add_to_code(code, create_full_quad(exit_sub, NULL, NULL, NULL)); 
  add_to_code(code, create_full_quad(halt, NULL, NULL, NULL)); 
  add_to_code(code, create_full_quad(end, NULL, NULL, NULL)); 

  print_code(code); 
  generate_target(code); 
}

static void dowhile_test(){
  quad_list code = create_quad_list();

  add_to_code(code, create_full_quad(vardec, "int", "x", NULL));
  add_to_code(code, create_full_quad(func_dec, "int", "main", NULL));
  add_to_code(code, create_full_quad(enter, NULL, NULL, NULL));
  add_to_code(code, create_full_quad(vardec, "int", "y", NULL));
  add_to_code(code, create_full_quad(assn, "y", "1", NULL));
  add_to_code(code, create_full_quad(dowhileloop, NULL, NULL, NULL));
  add_to_code(code, create_full_quad(enter, NULL, NULL, NULL));
  add_to_code(code, create_full_quad(mult, "t0", "y", "2"));
  add_to_code(code, create_full_quad(assn, "x", "t0", NULL));
  add_to_code(code, create_full_quad(leave, NULL, NULL, NULL));
  add_to_code(code, create_full_quad(end_dowhileloop, NULL, NULL, NULL));
  add_to_code(code, create_full_quad(lt, "t1", "y", "5"));
  add_to_code(code, create_full_quad(ifFalse, "t1", "12", NULL));
  add_to_code(code, create_full_quad(jumpTo, "5", NULL, NULL));
  add_to_code(code, create_full_quad(assn, "x", "3", NULL));
  add_to_code(code, create_full_quad(leave, NULL, NULL, NULL));
  add_to_code(code, create_full_quad(exit_sub, NULL, NULL, NULL));
  add_to_code(code, create_full_quad(halt, NULL, NULL, NULL));
  add_to_code(code, create_full_quad(end, NULL, NULL, NULL));

  print_code(code);
  generate_target(code);
}

static void if_test(){
  quad_list code = create_quad_list();

  add_to_code(code, create_full_quad(vardec, "int", "x", NULL));
  add_to_code(code, create_full_quad(func_dec, "int", "main", NULL));
  add_to_code(code, create_full_quad(enter, NULL, NULL, NULL));
  add_to_code(code, create_full_quad(vardec, "int", "y", NULL));
  add_to_code(code, create_full_quad(assn, "y", "1", NULL));
  add_to_code(code, create_full_quad(ifstmt, NULL, NULL, NULL));
  add_to_code(code, create_full_quad(lt, "t0", "y", "5"));
  add_to_code(code, create_full_quad(ifFalse, "t0", "13", NULL));
  add_to_code(code, create_full_quad(enter, NULL, NULL, NULL));
  add_to_code(code, create_full_quad(mult, "t1", "y", "2"));
  add_to_code(code, create_full_quad(assn, "x", "t1", NULL));
  add_to_code(code, create_full_quad(add, "t2", "y", "1")); 
  add_to_code(code, create_full_quad(assn, "y", "t2", NULL)); 
  add_to_code(code, create_full_quad(leave, NULL, NULL, NULL));
  add_to_code(code, create_full_quad(end_ifstmt, NULL, NULL, NULL));
  add_to_code(code, create_full_quad(assn, "x", "3", NULL));
  add_to_code(code, create_full_quad(leave, NULL, NULL, NULL));
  add_to_code(code, create_full_quad(exit_sub, NULL, NULL, NULL));
  add_to_code(code, create_full_quad(halt, NULL, NULL, NULL));
  add_to_code(code, create_full_quad(end, NULL, NULL, NULL));

  print_code(code);
  generate_target(code);
}

static void ifelse_test(){
  quad_list code = create_quad_list();

  add_to_code(code, create_full_quad(vardec, "int", "x", NULL)); 
  add_to_code(code, create_full_quad(func_dec, "int", "main", NULL));
  add_to_code(code, create_full_quad(enter, NULL, NULL, NULL));
  add_to_code(code, create_full_quad(vardec, "int", "y", NULL)); 
  add_to_code(code, create_full_quad(assn, "y", "1", NULL)); 
  add_to_code(code, create_full_quad(ifelse, NULL, NULL, NULL));
  add_to_code(code, create_full_quad(lt, "t0", "y", "5"));
  add_to_code(code, create_full_quad(ifFalse, "t0", "16", NULL));
  add_to_code(code, create_full_quad(enter, NULL, NULL, NULL));
  add_to_code(code, create_full_quad(add, "t1", "y", "1"));
  add_to_code(code, create_full_quad(assn, "y", "t1", NULL));
  add_to_code(code, create_full_quad(leave, NULL, NULL, NULL));
  add_to_code(code, create_full_quad(end_ifstmt, NULL, NULL, NULL));
  add_to_code(code, create_full_quad(jumpTo, "18", NULL, NULL)); 
  add_to_code(code, create_full_quad(elsestmt, NULL, NULL, NULL)); 
  add_to_code(code, create_full_quad(enter, NULL, NULL, NULL)); 
  add_to_code(code, create_full_quad(divide, "t2", "y", "5")); 
  add_to_code(code, create_full_quad(assn, "y", "t2", NULL)); 
  add_to_code(code, create_full_quad(leave, NULL, NULL, NULL)); 
  add_to_code(code, create_full_quad(end_elsestmt, NULL, NULL, NULL)); 
  add_to_code(code, create_full_quad(assn, "x", "3", NULL));
  add_to_code(code, create_full_quad(leave, NULL, NULL, NULL));
  add_to_code(code, create_full_quad(exit_sub, NULL, NULL, NULL));
  add_to_code(code, create_full_quad(halt, NULL, NULL, NULL));
  add_to_code(code, create_full_quad(end, NULL, NULL, NULL));

  print_code(code);
  generate_target(code);
}
