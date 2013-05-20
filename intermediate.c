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
static int get_num_addresses();  
static void add_quad_list(ast_node node, quad_list quads); 
static void add_quad(ast_node node, quad q); 
static char * process_left(ast_node node); 
static char * process_right(ast_node node); 
static void build_code(ast_node node, quad new_quad, char * address1, char * address2, char * address3); 
static void process_root(ast_node node); 
static void process_assign(ast_node node); 
static void process_math(ast_node node); 
static void process_negate(ast_node node); 
static void process_inc(ast_node node, char * inc); 
static void process_cmpd(ast_node node); 
static void process_func(ast_node node); 
static void process_if(ast_node node); 
static void process_ifelse(ast_node node); 
static void process_while(ast_node node); 
static void error(); 

#define MAX_LEN 201

int num_addresses = 0; 
int num_quads = 0; 

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
  new_quad->num = num_quads; 

  num_quads++; 
  return new_quad; 
}

void reset_num_quads(){
  num_quads = 0; 
}

/* Create a quad_list. first is initially NULL. */ 
quad_list create_quad_list(){
  quad_list new_quad_list = malloc(sizeof(struct quad_list_struct)); 
  new_quad_list->first = NULL; 

  return new_quad_list; 
}

void destroy_quad(quad q){
  if (q != NULL){
    if (q->address1 != NULL)
      free(q->address1); 
    if (q->address2 != NULL)
      free(q->address2); 
    if (q->address3 != NULL)
      free(q->address3); 
  }
}

void destroy_quad_list(quad_list q){
  if (q != NULL){
    quad curr = q->first;
    while (curr != NULL && q != NULL && curr != q->first){
      quad next = curr->next; 
      destroy_quad(curr); 
      curr = next; 
    }
    destroy_quad(curr); 
  } 
}

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
  if (node != NULL){
    if (node->node_type == ROOT){
      process_root(node); 
    }
    // generate code for assignment operator
    else if (node->node_type == OP_ASSIGN){
      process_assign(node); 
    }
    // generate code for negate operator
    else if (node->node_type == OP_NEG) {
      process_negate(node); 
    }
    // generate code for  +, -, *, /, %, =, !=, <, <=, >, >=
    else if (node->node_type > 0 && node->node_type <= 16 ){
      process_math(node); 
    }
    else if (node->node_type == OP_INC){
      process_inc(node, "1"); 
    }
    else if (node->node_type == OP_DEC){
      process_inc(node, "-1"); 
    }
    else if (node->node_type == IF_STMT){
      process_if(node); 
    }
    else if (node->node_type == IF_ELSE_STMT){
      process_ifelse(node); 
    }
    else if (node->node_type == CMPD){
      process_cmpd(node); 
    }
    else if (node->node_type == WHILE_STMT){
      process_while(node); 
    }
    /*
    else if (node->node_type == CALL){
      process_call(node); 
    }
    */ 
  }
}

static char * new_address(){
  char * buffer = malloc(10); 
  sprintf(buffer, "t%d", num_addresses); 
  num_addresses += 1; 

  return buffer; 
}

static int get_num_addresses(){
  return num_addresses; 
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

// adds a quad q to the end of the code of some node
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
    printf("%d. (%d, %s, %s, %s)\n", code->first->num, code->first->opcode, code->first->address1, code->first->address2, code->first->address3); 
  else
    printf("code->first is NULL inside print_code\n"); 

  quad curr; 
  for (curr = code->first->next; curr != code->first; curr = curr->next){
    printf("%d. (%d, %s, %s, %s)\n", curr-> num, curr->opcode, curr->address1, curr->address2, curr->address3); 
  }
}

// processes the left child of a node (if it's an ID, int_literal, or double_literal)
static char * process_left(ast_node node){
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
  else if (node->left_child != NULL && node->left_child->location != NULL){
    left = strdup(node->left_child->location);
  }
  return left; 
}

// processes the right child of a node (if it's an ID, int_literal, or double_literal)
static char * process_right(ast_node node){
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
  return right; 
}

// handles mathy operations (all the same pattern)
static void process_math(ast_node node){
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
  else if (node->node_type == OP_MOD){
    new_quad = create_quad(mod); 
  }
  else if (node->node_type == OP_EQUALS){
    new_quad = create_quad(eq); 
  }
  else if (node->node_type == OP_NEQUALS){
    new_quad = create_quad(neq); 
  }
  else if (node->node_type == OP_LT){
    new_quad = create_quad(lt); 
  }
  else if (node->node_type == OP_LEQ){
    new_quad = create_quad(leq); 
  }
  else if (node->node_type == OP_GT){
    new_quad = create_quad(gt); 
  }
  else if (node->node_type == OP_GEQ){
    new_quad = create_quad(geq); 
  }
  else if (node->node_type == OP_AND){
    new_quad = create_quad(and); 
  }
  else if (node->node_type == OP_OR){
    new_quad = create_quad(or); 
  }
  else if (node->node_type == OP_NOT){
    new_quad = create_quad(not); 
  }
   
  // location being assigned to is new!   
  char * target = new_address();
       
  // get left argument     
  char * left = process_left(node);  
                 
  // get right argument         
  char * right = process_right(node);       

  if (new_quad != NULL && target != NULL && left != NULL && right != NULL){                
    build_code(node, new_quad, target, left, right);  
  }            
  else {  
    destroy_quad(new_quad);        
    error();                 
  }          
}

// builds the code for nodes that just take the code from their children and then
// add their own
static void build_code(ast_node node, quad new_quad, char * address1, char * address2, char * address3){
  // builds code from its children
  ast_node child;
  for (child = node->left_child; child != NULL; child = child->right_sibling){
    add_quad_list(node, child->code);
  }

  // only adds a new quad if there is one
  if (new_quad != NULL){
    new_quad->address1 = address1;
    new_quad->address2 = address2; 
    new_quad->address3 = address3; 

    if (address1 != NULL){
      node->location = strdup(address1); 
    }

    add_quad(node, new_quad); 
  }
  // get the code from the children (that exist) and then add the new line
  /* if (node->left_child != NULL){
    add_quad_list(node, node->left_child->code); 
  }
  if (node->left_child->right_sibling != NULL){
    add_quad_list(node, node->left_child->right_sibling->code); 
    }*/ 
}

static void process_root(ast_node node){
  build_code(node, NULL, NULL, NULL, NULL); 
}

static void process_assign(ast_node node){
  quad new_quad = create_quad(assn);
  // get location to being assigned
  char * target = NULL;
  if (node->left_child != NULL && node->left_child->node_type == IDENT){
    target = strdup(node->left_child->value.string); // DO I NEED TO DUPLICATE THE STRING? 
  }
  else if (node->left_child != NULL){
    target = strdup(node->left_child->location);
  }

  // get location of value               
  char * value = process_right(node);

  if (target != NULL && value != NULL){
    build_code(node, new_quad, target, value, NULL);
  }
  else{
    destroy_quad(new_quad);
    error();
  }
}

static void process_negate(ast_node node){
  quad new_quad = create_quad(mult); 
  char * target = new_address(); 

  char * value = process_left(node);
  char * multby = strdup("-1"); 
  
  if (value != NULL){
    build_code(node, new_quad, target, value, multby); 
  }
  else{
    destroy_quad(new_quad); 
    error(); 
  }
}

// handle increments and decrements
static void process_inc(ast_node node, char * inc){
  quad new_quad = create_quad(add); 
  char * target = process_left(node); 
  char *value = target; 
  char *amount = strdup(inc); 

  if (value != NULL){
    build_code(node, new_quad, target, value, amount); 
  }
  else{
    destroy_quad(new_quad); 
    error(); 
  }
}

/* builds the code for a compound: 
 * enter scope
 * code of its children
 * leave scope
 */ 
static void process_cmpd(ast_node node){
  quad enter_scope = create_quad(enter); 
  quad exit_scope = create_quad(leave); 

  add_quad(node, enter_scope); 
  build_code(node, exit_scope, NULL, NULL, NULL); 
}

static void process_if(ast_node node){
  quad if_quad = create_quad(ifFalse); 
  char * loc = strdup(node->left_child->location); 
  if_quad->address1 = loc; 

  // add the code for the condition
  add_quad_list(node, node->left_child->code); 

  // add the ifFalse quad
  add_quad(node, if_quad); 

  // add the compound 
  if (node->left_child->right_sibling != NULL){
    add_quad_list(node, node->left_child->right_sibling->code); 
  }

  // Backpatch if_quad by filling in the number of the quad it should go to
  // if it is false. 
  char * buffer = malloc(10); 
  sprintf(buffer, "%d", num_quads); 
  if_quad->address2 = buffer; 
}

static void process_ifelse(ast_node node){
  quad if_quad = create_quad(ifFalse);
  char * loc = strdup(node->left_child->location);
  if_quad->address1 = loc;

  // add the code for the condition     
  add_quad_list(node, node->left_child->code);

  // add the ifFalse quad
  add_quad(node, if_quad);

  // add the compound 
  if (node->left_child->right_sibling != NULL){
    add_quad_list(node, node->left_child->right_sibling->code);
  }

  // do the goto
  quad jump_quad = create_quad(jumpTo); 
  add_quad(node, jump_quad); 
  
  // add the else compound
  if (node->left_child->right_sibling->right_sibling != NULL){
    add_quad_list(node, node->left_child->right_sibling->right_sibling->code); 
  }
  
  // Backpatch if_false
  int ifFalse_backpatch = jump_quad->next->num; 
  char * buffer = malloc(10); 
  sprintf(buffer, "%d", ifFalse_backpatch); 
  if_quad->address2 = buffer; 

  // Backpatch the jump_quad
  buffer = malloc(10); 
  sprintf(buffer, "%d", num_quads); 
  jump_quad->address1 = buffer; 
}

static void process_while(ast_node node){
  quad if_false = create_quad(ifFalse); 
  char * loc = strdup(node->left_child->location); 
  if_false->address1 = loc; 

  // Get the num of the quad that starts the code that computes
  // the condition. 
  int start_of_condition = node->left_child->code->first->num; 
  
  // add the code for the condition
  add_quad_list(node, node->left_child->code); 
  
  // add the ifFalse quad
  add_quad(node, if_false); 

  // add the compound (body of while loop)
  if (node->left_child->right_sibling != NULL){
    add_quad_list(node, node->left_child->right_sibling->code); 
  }

  // create the jumpTo quad that takes you back to the condition
  // and add it to the code
  quad back_to_condition = create_quad(jumpTo); 
  char *buffer = malloc(10); 
  sprintf(buffer, "%d", start_of_condition); 
  back_to_condition->address1 = buffer; 
  add_quad(node, back_to_condition); 

  // backpatch the ifFalse quad
  buffer = malloc(10); 
  sprintf(buffer, "%d", num_quads); 
  if_false->address2 = buffer; 
}

/* builds the code of a function; finds its compound and takes that code */
/* THIS IS VERY UNFINISHED - it's more complicated than this */ 
static void process_func(ast_node node){
  // the 3rd child of a funcdec node is the compound
  ast_node cmpd = node->left_child->right_sibling->right_sibling; 

  // check to make sure everything is ok, then builds its code (doesn't add new code)
  if (cmpd->node_type == CMPD){
    build_code(node, NULL, NULL, NULL, NULL); 
    // then somehow fill in the location of the node to be the loc of whatever it returned
  }
  else {
    error();
  } 
}

/* processes a call by generating code for the function it's calling. 
 * Gets the function by looking it up in the symbol table. 
 */ 
// THIS IS NOT HOW WE'RE GOING TO DO THIS. 
/*
static void process_call(ast_node node){
  int level; 
  char * func_name = node->left_child->value.string; 
  symnode func = lookup_in_symboltable(symtab, func_name, 0, &level);    

  // somehow get to the ast node from the symnode
  }*/ 

static void error(){
  printf("Error found during generation of intermediate code.\n"); 
}
