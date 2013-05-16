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

void destroy_quad(quad q){
  free(q->address1); 
  free(q->address2); 
  free(q->address3); 
  free(q->next); 
  free(q->prev); 
  free(q); 
}

/* generates intermediate code for the node, returns a 
   linked list of quads. */ 
// ACTUALLY MAYBE YOU DON'T NEED THIS? 
quad_list generate_intermediate(ast_node node){
  
  generate_traverse(node, inter_code); 
  return quad_list; 
}

/* actually does the fun stuff */ 
static void generate_traverse(ast_node node){
  if (node != NULL){
    ast_node child = node->left_child; 
    while (node != NULL){
      // generate code to prepare for child

      generate_traverse(child, inter_code); 
      child = child->right_sibling; 
    } 
    // generate code to implement node's action
    implement_node(node); 
  }
}

// generates code to implement node's action
static void implement_node(ast_node node){

  // generate code for assignment operator
  if (node !=NULL && node->node_type == OP_ASSIGN){
    quad new_quad = create_quad(assn);
    // get location to being assigned to                                                                                     
    char * target = NULL;
    if (node->left_child != NULL && node->left_child->node_type == IDENT){
      target = strdup(node->left_child->string); // DO I NEED TO DUPLICATE THE STRING?                                       
    }
    else if (node->left_child != NULL){
      target = strdup(node->left_child->location);
    }

    // get location of value                                                                                                 
    char * value = NULL;
    if (node->right_child != NULL && node->right_child->node_type == IDENT){
      value =strdup(node->right_child->string);
    }
    else if (node->right_child != NULL){
      value =strdup(node->right_child->location);
    }

    if (target != NULL && value != NULL){
      new_quad->address1 = target; 
      new_quad->address2 = value; 
    }
    else{
      destroy_quad(new_quad); 
    }
  }

  // generate code for plus, minus, multiply, or divide operator
  else if (node != NULL && (node->node_type == OP_PLUS || node->node_type == OP_MINUS || node->node_type == OP_TIMES
			    || node->node_type == OP_DIVIDE)){
    
    if (node->node_type == OP_PLUS)
      quad new_quad = create_quad(add); 
    else if (node->node_type == OP_MINUS)
      quad new_quad = create_quad(sub); 
    else if (node->node_type == OP_TIMES)
      quad new_quad = create_quad(mult); 
    else if (node->node_type == OP_DIVIDE)
      quad new_quad = create_quad(div); 

    // location being assigned to is new!
    char * target = new_address();

    // get left argument
    char * left = NULL; 
    if (node->left_child != NULL && node->left_child->node_type == IDENT){
      left = strdup(node->left_child->string); 
    }
    else if (node->left_child != NULL){
      left = strdup(node->left_child->location); 
    }

    // get right argument
    char * right = NULL; 
    if (node->right_child != NULL && node->right_child->node_type == IDENT){
      right = strdup(node->right_child->string); 
    }
    else if (node->right_child != NULL){
      right = strdup(node->right_child->location); 
    }

    if (target != NULL && left != NULL && right != NULL){
      new_quad->address1 = target; 
      new_quad->address2 = left; 
      new_quad->address3 = right; 
    }
    else {
      destroy_quad(new_quad); 
    }
  } 
}
