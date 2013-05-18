/* intermediate.c
 * generates intermediate code given an AST
 */ 

#import <stdlib.h>
#import <stdio.h>
#import <string.h> 
#import "ast.h" 
#import "intermediate.h" 

/* Prototypes */ 
//static void generate_traverse(ast_node node, quad_list inter_code); 
static void implement_node(ast_node node); 
static char * new_address(); 
static void add_quad_list(ast_node node, quad_list quads); 
static void add_quad(ast_node node, quad q); 

#define MAX_LEN 201

int num_addresses = 0; 

/* create a quad with a given opcode and return a pointer 
   to it.  Initializes all addresses to NULL */
quad create_quad(opcode_type opcode){
  quad new_quad = malloc(sizeof(struct quad_struct)); 
  new_quad->opcode = opcode; 
  new_quad->address1 = NULL; 
  new_quad->address2 = NULL; 
  new_quad->address3 = NULL; 
  new_quad->next = new_quad; 
  new_quad->prev = new_quad; 
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
/*quad_list generate_intermediate(ast_node node){
  
  generate_traverse(node, inter_code); 
  return quad_list; 
  }*/ 

/* actually does the fun stuff */ 
void generate_traverse(ast_node node){
  if (node != NULL){
    ast_node child = node->left_child; 
    while (child != NULL){
      // generate code to prepare for child

      generate_traverse(child); 
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
      target = strdup(node->left_child->value.string); // DO I NEED TO DUPLICATE THE STRING?  
    }
    else if (node->left_child != NULL){
      target = strdup(node->left_child->location);
    }

    // get location of value                                                                                                 
    char * value = NULL;
    ast_node right_child = node->left_child->right_sibling; 
    if (right_child != NULL && right_child->node_type == IDENT){
      value =strdup(right_child->value.string);
    }
    else if (right_child != NULL && right_child->node_type == INT_LITERAL){
      char buffer[MAX_LEN];
      int int_lit = right_child->value.int_value; 
      snprintf(buffer, MAX_LEN, "%d", int_lit); 
      value = strdup(buffer); 
    }
    else if (right_child != NULL && right_child->node_type == DOUBLE_LITERAL){
      char buffer[MAX_LEN]; 
      double double_lit = right_child->value.double_value; 
      snprintf(buffer, MAX_LEN, "%f", double_lit); 
      value = strdup(buffer); 
    }
    else if (right_child != NULL){
      value =strdup(right_child->location);
    }

    if (target != NULL && value != NULL){
      new_quad->address1 = target; 
      new_quad->address2 = value; 
      node->location = strdup(target); 

      // get the code from the children and then add the new line
      add_quad_list(node, node->left_child->code); 
      add_quad_list(node, node->left_child->right_sibling->code); 
      add_quad(node, new_quad); 
    }
    else{
      destroy_quad(new_quad); 
    }
  }

  // generate code for plus, minus, multiply, or divide operator
  else if (node != NULL && (node->node_type == OP_PLUS || node->node_type == OP_MINUS || node->node_type == OP_TIMES
			    || node->node_type == OP_DIVIDE)){
    
    quad new_quad = NULL; 
    if (node->node_type == OP_PLUS){
      new_quad = create_quad(add);
    } 
    else if (node->node_type == OP_MINUS){
      new_quad = create_quad(sub); 
    }
    else if (node->node_type == OP_TIMES){
      new_quad = create_quad(mult); 
    }
    else if (node->node_type == OP_DIVIDE){
      new_quad = create_quad(divide); 
    }

    // location being assigned to is new!
    char * target = new_address();

    // get left argument
    char * left = NULL; 
    if (node->left_child != NULL && node->left_child->node_type == IDENT){
      left = strdup(node->left_child->value.string); 
    }
    else if (node->left_child != NULL && node->left_child->node_type == INT_LITERAL){
      char buffer[MAX_LEN]; 
      int int_lit  = node->left_child->value.int_value; 
      snprintf(buffer, MAX_LEN, "%d", int_lit); 
      left = strdup(buffer); 
    }
    else if (node->left_child != NULL && node->left_child->node_type == DOUBLE_LITERAL){
      char buffer[MAX_LEN];
      double double_lit = node->left_child->value.double_value;
      snprintf(buffer, MAX_LEN,"%f", double_lit);
      left = strdup(buffer);
    }
    else if (node->left_child != NULL){
      left = strdup(node->left_child->location); 
    }

    // get right argument
    ast_node right_child = node->left_child->right_sibling; 
    char * right = NULL; 
    if (right_child != NULL && right_child->node_type == IDENT){
      right = strdup(right_child->value.string); 
    }
    else if (right_child != NULL && right_child->node_type == INT_LITERAL){
      char buffer[MAX_LEN]; 
      int int_lit = right_child->value.int_value; 
      snprintf(buffer, MAX_LEN, "%d", int_lit); 
      right = strdup(buffer); 
    }
    else if (right_child != NULL && right_child->node_type == DOUBLE_LITERAL){
      char buffer[MAX_LEN];
      double double_lit = right_child->value.double_value;
      snprintf(buffer, MAX_LEN,"%f", double_lit);
      right = strdup(buffer);
    }
    else if (right_child != NULL){
      right = strdup(right_child->location); 
    }

    if (new_quad != NULL && target != NULL && left != NULL && right != NULL){
      new_quad->address1 = target; 
      new_quad->address2 = left; 
      new_quad->address3 = right; 

      node->location = strdup(target); 

      // get the code from the children and then add the new line                                                                       
      add_quad_list(node, node->left_child->code);
      add_quad_list(node, node->left_child->right_sibling->code);
      add_quad(node, new_quad);

    }
    else {
      destroy_quad(new_quad); 
    }
  } 
}

static char * new_address(){
  char * buffer = malloc(10); 
  sprintf(buffer, "t%d", num_addresses); 
  num_addresses += 1; 

  return buffer; 
}

static void add_quad_list(ast_node node, quad_list quads){
  printf("inside add_quad_list\n"); 
  if (node->code->first == NULL && quads != NULL ){
    printf("inside if \n"); 
    node->code = quads; 
    //    node->code->first = quads->first;
  }
  else if (quads != NULL && quads->first != NULL) {
    printf("inside else \n"); 
    // testing
    if (node->code == NULL)
      printf("node->code\n"); 
    else if (node->code->first == NULL)
      printf("node->code->first\n"); 
    else if (node->code->first->prev == NULL)
      printf("node->code->first->prev\n"); 
    else if (node->code->first->prev->next == NULL)
      printf("node->code->first->prev->next\n"); 

    if (quads->first == NULL)
      printf("quads->first\n"); 
    else if (quads->first->prev == NULL)
      printf("quads->first->prev\n"); 

    quad code_old_last = node->code->first->prev; 
    
    node->code->first->prev->next = quads->first;
    node->code->first->prev = quads->first->prev; 
    quads->first->prev = code_old_last; 
    node->code->first->prev->next = node->code->first; 
  }
}

static void add_quad(ast_node node, quad q){
  printf("add_quad\n"); 
  if (node->code->first == NULL && q != NULL){
    printf("inside if\n"); 
    node->code->first = q; 
    q->next = q; 
    q->prev = q; 
  }
  else if (q != NULL) {
    printf("inside else\n"); 
    printf("node->code->first: (%d, %s, %s, %s)\n", node->code->first->opcode, node->code->first->address1, node->code->first->address2, node->code->first->address3); 
    printf("quad: (%d, %s, %s, %s)\n", q->opcode, q->address1, q->address2, q->address3); 
    q->prev = node->code->first->prev; 
    q->next = node->code->first; 
    node->code->first->prev->next = q; 
    node->code->first->prev = q; 
  }
}

void print_code(quad_list code){
  if (code->first != NULL)
    printf("(%d, %s, %s, %s)\n", code->first->opcode, code->first->address1, code->first->address2, code->first->address3); 
  else
    printf("code->first is NULL inside print_code\n"); 

  quad curr; 
  for (curr = code->first->next; curr != code->first; curr = curr->next){
    printf("(%d, %s, %s, %s)\n", curr->opcode, curr->address1, curr->address2, curr->address3); 
  }
}
