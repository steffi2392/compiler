/* intermediate.h
 * 
 * Defines some structs and stuff for intermediate code. 
 * Might not end up using this, but it'll be helpful for now. 
 * 
 * By Steffi Ostrowski
 */ 

#ifndef INTERMEDIATE_H
#define INTERMEDIATE_H

//#import "ast.h"

/* opcodes for the quads */ 
typedef enum {assn, array_assn, add, sub, mult, divide, mod, eq, neq, lt, leq, gt, 
	      geq, f_add, f_sub, f_mult, f_divide, f_mod, f_eq, f_neq, f_lt, f_leq, 
	      f_gt, f_geq, and, or, not, enter, leave, ifFalse, jumpTo, read, print, 
              rtrn, get_rtrn, func_dec, goto_sub, exit_sub, push, pop, vardec, 
              pardec, array_lkup, halt, end} opcode_type; 

/* Structure for a quad. Knows its opcode and up to 3 addresses - these are strings
   which can then be looked up in the symbol table. It also knows its next and
   previous instructions */  
typedef struct quad_struct *quad; 
struct quad_struct {
  opcode_type opcode; 
  char * address1; 
  char * address2; 
  char * address3; 
  
  quad next; 
  quad prev; 
  int num; 
}; 

typedef struct quad_list_struct *quad_list; 
struct quad_list_struct {
  quad first; 
}; 

/* Create a quad with a given opcode and return a pointer to that quad. */
quad create_quad(opcode_type opcode); 
quad create_full_quad(opcode_type opcode, char * addr1, char * addr2, char * addr3); 
void destroy_quad(quad q); 
void destroy_quad_list(quad_list q); 

/* Create a quad_list and return a pointer to it */ 
//quad_list create_quad_list(); 
// void generate_traverse(ast_node node); 


#endif
