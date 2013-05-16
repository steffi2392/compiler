/* intermediate.h
 * 
 * Defines some structs and stuff for intermediate code. 
 * Might not end up using this, but it'll be helpful for now. 
 * 
 * By Steffi Ostrowski
 */ 

#ifndef INTERMEDIATE_H
#define INTERMEDIATE_H

/* opcodes for the quads */ 
typedef enum {assn, add, sub, mult, div} opcode_type; 

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
}; 

typedef struct quad_list_struct *quad_list; 
struct quad_list {
  quad first; 
}

/* Create a quad with a given opcode and return a pointer to that quad. */
quad create_quad(opcode_type opcode); 
void destroy_quad(quad q); 

/* Create a quad_list and return a pointer to it */ 
quad_list create_quad_list(); 

#endif
