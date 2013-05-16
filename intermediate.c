/* intermediate.c
 * generates intermediate code given an AST
 */ 

#import <stdio.h>
#import "ast.h"
#import "intermediate.h" 

/* Prototypes */ 
static void generate_traverse(ast_node node, quad_list inter_code); 

/* create a quad with a given opcode and return a pointer 
   to it.  Initializes all addresses to NULL */
quad create_quad(opcode_type opcode){
  quad new_quad = malloc(sizeof(struct quad_struct)); 
  new_quad->opcode = opcode; 
  new_quad->address1 = NULL; 
  new_quad->address2 = NULL; 
  new_quad->address3 = NULL; 
  new_quad->next = NULL; 
  new_quad->prev = NULL; 
  return new_quad; 
}

/* Create a quad_list. first is initially NULL. */ 
quad_list create_quad_list(){
  quad_list new_quad_list = malloc(sizeof(struct quad_list_struct)); 
  new_quad_list->first = NULL; 

  return new_quad_list; 
}

/* generates intermediate code for the node, returns a 
   linked list of quads. */ 
quad_list generate_intermediate(ast_node node){
  quad_list inter_code = create_quad_list(); 

  generate_traverse(node, inter_code); 
  return quad_list; 
}

/* actually does the fun stuff */ 
static void generate_traverse(ast_node node, quad_list inter_code){
  if (node != NULL){
    ast_node child = node->left_child; 
    while (node != NULL){
      // generate code to prepare for child
      generate_traverse(child, inter_code); 
      child = child->right_sibling; 
    } 
    // generate code to implement node's action
  }
}
