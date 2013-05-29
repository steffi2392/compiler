/* intermediate.c
 * generates intermediate code given an AST
 */ 

#include <stdlib.h>
#include <stdio.h>
#include <string.h> 
#include "ast.h" 
#include "intermediate.h" 

/* Prototypes */ 
//static void generate_traverse(ast_node node, quad_list inter_code); 
static void generate_traverse_recurse(ast_node node); 
static void implement_node(ast_node node); 
static char * new_address();
static int get_num_addresses();  
static void add_quad_list(ast_node node, quad_list quads);
static void add_quad_list_to_beginning(ast_node node, quad_list quads);  
static void add_quad(ast_node node, quad q); 
static void add_quad_to_beginning(ast_node node, quad q); 
static char * process_left(ast_node node); 
static char * process_right(ast_node node); 
static void build_code(ast_node node, quad new_quad, char * address1, char * address2, char * address3); 
static void process_assign(ast_node node); 
static void process_math(ast_node node); 
static void process_float_math(ast_node node); 
static void process_negate(ast_node node); 
static void process_inc(ast_node node, char * inc); 
static void process_cmpd(ast_node node); 
static void process_if(ast_node node); 
static void process_ifelse(ast_node node); 
static void process_while(ast_node node); 
static void process_dowhile(ast_node node); 
static void process_and(ast_node node); 
static void process_or(ast_node node); 
static void process_for_header(ast_node node); 
static void process_for(ast_node node); 
static void process_read(ast_node node); 
static void process_print(ast_node node); 
static void process_return(ast_node node); 
static void process_function(ast_node node); 
static void process_params(ast_node node); 
static void process_vardec(ast_node node); 
static void process_call(ast_node node); 
static void process_id(ast_node node); 
static void process_array(ast_node node); 
static void process_root(ast_node node); 
static void error(); 

#define MAX_LEN 201

int num_addresses = 0; 
int num_quads = 0; 

// used for printing code - converts opcode enum to its string
static char* opcode_table[] = {"assn", "array_assn", "add", "sub", "mult", "divide", 
			       "mod", "eq", "neq", "lt", "leq", 
			       "gt", "geq", "f_add", "f_sub", "f_mult", "f_divide",
			       "f_mod", "f_eq", "f_neq", "f_lt", "f_leq", 
			       "f_gt", "f_geq", "and", "end_and",  "or", "end_or", 
			       "not", "end_not", "enter", "leave", "ifFalse", "jumpTo", "read", 
			       "print", "rtrn", "get_rtrn", "func_dec", "goto_sub", 
			       "exit_sub", "push", "pop", "vardec", "pardec", 
			       "array_lkup", "halt", "end", "whileloop", "end_whileloop", 
			       "forloop", "end_forloop", "dowhileloop", "end_dowhileloop", 
                               "ifstmt", "end_ifstmt", "ifelse", "elsestmt", "end_elsestmt"}; 

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

quad create_full_quad(opcode_type opcode, char * addr1, char * addr2, char * addr3){
  quad new_quad = malloc(sizeof(struct quad_struct)); 
  new_quad->opcode = opcode; 
  new_quad->address1 = addr1; 
  new_quad->address2 = addr2; 
  new_quad->address3 = addr3; 
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

void generate_traverse(ast_node node){
  generate_traverse_recurse(node); 
  
  // add the end quad
  quad end_quad = create_quad(end);
  add_quad(node, end_quad);
}

/* actually does the fun stuff */ 
static void generate_traverse_recurse(ast_node node){
  if (node != NULL){
    ast_node child = node->left_child; 
    while (child != NULL){
      generate_traverse_recurse(child); 
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
    else if (node->node_type > 0 && node->node_type <= 16 && node->node_type != 14 && node->node_type != 15){
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
    else if (node->node_type == DO_WHILE_STMT){
      process_dowhile(node); 
    }
    else if (node->node_type == OP_AND){
      process_and(node); 
    }
    else if (node->node_type == OP_OR){
      process_or(node); 
    }
    else if (node->node_type == FOR_STRT || node->node_type == FOR_COND || node->node_type == FOR_UPDT){
      process_for_header(node); 
    }
    else if (node->node_type == FOR_STMT){
      process_for(node); 
    }
    else if (node->node_type == READ_STMT){
      process_read(node); 
    }
    else if (node->node_type == PRINT_STMT){
      process_print(node); 
    }
    else if (node->node_type == RETURN_STMT){
      process_return(node); 
    }
    else if (node->node_type == FUNCDEC){
      process_function(node); 
    }
    else if (node->node_type == PARAMS){
      process_params(node); 
    }
    else if (node->node_type == INT_TYPE || node->node_type == DOUBLE_TYPE){
      process_vardec(node); 
    }
    else if (node->node_type == CALL){
      process_call(node); 
    } 
    else if (node->node_type == IDENT){
      process_id(node); 
    } 
    else if (node->node_type == ARRAY){
      process_array(node); 
    }
  }
}

// Gives a new address (ex: t5)
static char * new_address(){
  char * buffer = malloc(10); 
  sprintf(buffer, "$t%d", num_addresses); 
  num_addresses += 1; 

  return buffer; 
}

static int get_num_addresses(){
  return num_addresses; 
}

// adds a quadlist to the end of the code of some node
static void add_quad_list(ast_node node, quad_list quads){
  if (node->code->first == NULL && quads != NULL ){
    node->code = quads; 
  }
  else if (quads != NULL && quads->first != NULL) {
    
    quad code_old_last = node->code->first->prev; 
    
    node->code->first->prev->next = quads->first;
    node->code->first->prev = quads->first->prev; 
    quads->first->prev = code_old_last; 
    node->code->first->prev->next = node->code->first; 
  }
}

// adds a quadlist to the beginning of the code of some node
static void add_quad_list_to_beginning(ast_node node, quad_list quads){
  if (node->code->first == NULL){
    node->code = quads; 
  }
  else if (quads != NULL && quads->first != NULL){
    quads->first->prev->next = node->code->first; 
    quad quads_old_last = quads->first->prev; 
    quads->first->prev = node->code->first->prev;

    node->code->first->prev = quads_old_last; 
    quads->first->prev->next = quads->first; 
    node->code->first = quads->first; 
  }
}

// adds a quad q to the end of the code of some node
static void add_quad(ast_node node, quad q){
  if (node->code->first == NULL && q != NULL){
    node->code->first = q; 
    q->next = q; 
    q->prev = q; 
  }
  else if (q != NULL) {
    q->prev = node->code->first->prev; 
    q->next = node->code->first; 
    node->code->first->prev->next = q; 
    node->code->first->prev = q; 
  }
}

void add_to_code(quad_list code, quad q){
  if (code->first == NULL && q != NULL){
    code->first = q; 
    q->next = q; 
    q->prev = q; 
  }
  else if (q != NULL){
    q->prev = code->first->prev; 
    q->next = code->first; 
    code->first->prev->next = q; 
    code->first->prev = q; 
  }
}

// adds a quad q to the beginning of the code of some node
static void add_quad_to_beginning(ast_node node, quad q){
  if (node->code->first == NULL && q != NULL){
    node->code->first = q; 
    q->next = q; 
    q->prev = q; 
  }
  else if (q != NULL){
    q->next = node->code->first; 
    q->prev = node->code->first->prev; 
    node->code->first->prev = q; 
    q->prev->next = q; 
    node->code->first = q; 
  }
}

void print_code(quad_list code){
  if (code->first != NULL)
    printf("%d. (%s, %s, %s, %s)\n", code->first->num, opcode_table[code->first->opcode], code->first->address1, code->first->address2, code->first->address3); 
  else
    printf("code->first is NULL inside print_code\n"); 

  quad curr; 
  for (curr = code->first->next; curr != code->first; curr = curr->next){ 
    printf("%d. (%s, %s, %s, %s)\n", curr-> num, opcode_table[curr->opcode], curr->address1, curr->address2, curr->address3); 
  }
}

/* processes the left child of a node 
 * 1. If it's an ID, int_literal, or double_literal, it gives you the value.
 * 2. If it has a location it gives you the location
 */
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
  else if (node->left_child != NULL && node->left_child->node_type == STRING_LIT){
    left = node->left_child->value.string; 
  }
  else if (node->left_child != NULL && node->left_child->location != NULL){
    left = strdup(node->left_child->location);
  }
  return left; 
}

/* processes the left child of a node     
 * 1. If it's an ID, int_literal, or double_literal, it gives you the value. 
 * 2. If it has a location it gives you the location  
 */ 
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

/* Handles mathy operations (all the same pattern)
 * Format: (operation, target location, left argument, right argument)
 */ 
static void process_math(ast_node node){
  // if its a float - process float math
  if (node->type == Double){
    process_float_math(node); 
  }

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
  else if (node->node_type == OP_NOT){
    new_quad = create_quad(not); 
  }
   
  // location being assigned to is new!   
  char * target = new_address();
       
  // get left argument     
  char * left = process_left(node);  
  
  // get right argument (if it's not OP_NOT)
  char * right = NULL; 
  if (node->node_type != OP_NOT)
    right = process_right(node);
  
  if (new_quad != NULL && target != NULL && left != NULL){                
    build_code(node, new_quad, target, left, right);  
  }            
  else {  
    destroy_quad(new_quad);        
    error("process math");                 
  }          
}

// process float math
static void process_float_math(ast_node node){
  quad new_quad = NULL; 

  switch (node->node_type){
  case OP_PLUS:
    new_quad = create_quad(f_add);
    break;
  case OP_MINUS: 
    new_quad = create_quad(f_sub); 
    break; 
  case OP_TIMES: 
    new_quad = create_quad(f_mult); 
    break;
  case OP_DIVIDE:
    new_quad = create_quad(f_divide); 
    break;
  case OP_EQUALS: 
    new_quad = create_quad(f_eq); 
    break;
  case OP_NEQUALS: 
    new_quad = create_quad(f_neq); 
    break;
  case OP_LT: 
    new_quad = create_quad(f_lt); 
    break;
  case OP_LEQ: 
    new_quad = create_quad(f_leq); 
    break;
  case OP_GT: 
    new_quad = create_quad(f_gt); 
    break;
  case OP_GEQ: 
    new_quad = create_quad(f_geq); 
    break;
  }

  // location being assigned to is new!
  char *target = new_address(); 
  char * left = process_left(node); 
  char *right = process_right(node); 

  if (new_quad != NULL && target != NULL && left != NULL && right != NULL){
    build_code(node, new_quad, target, left, right);
  }
  else {
    destroy_quad(new_quad);
    error("process_float_math");
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
}

// Format: (assn, target location, value location, null)
static void process_assign(ast_node node){
  char * target = NULL; 
  // deal with arrays a little differently
  if (node->left_child->node_type == ARRAY){
    quad array_quad = create_quad(array_assn); 
    ast_node array = node->left_child; 

    // (array_assn, array, index, value)
    array_quad->address1 = process_left(array); 
    array_quad->address2 = process_right(array); ; 
    array_quad->address3 = process_right(node); 
    
    // add code to calculuate right hand side, then to find array location
    add_quad_list(node, node->left_child->right_sibling->code); 
    add_quad(node, array_quad); 
  }
  else {
    quad new_quad = create_quad(assn);
    // get location to being assigned
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
      error("process_assign");
    }
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
    error("process_negate"); 
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
    error("process inc"); 
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
  quad ifFalse_quad = create_quad(ifFalse); 
  char * loc = strdup(node->left_child->location); 
  ifFalse_quad->address1 = loc; 

  // indicate that this is an if-statement
  quad if_false = create_quad(ifstmt); 
  add_quad(node, if_false); 

  // add the code for the condition
  add_quad_list(node, node->left_child->code); 

  // add the ifFalse quad
  add_quad(node, ifFalse_quad); 

  // add the compound 
  if (node->left_child->right_sibling != NULL){
    add_quad_list(node, node->left_child->right_sibling->code); 
  }

  // indicate that the if ends here
  quad if_end = create_quad(end_ifstmt); 
  add_quad(node, if_end); 

  // Backpatch if_quad by filling in the number of the quad it should go to
  // if it is false. 
  char * buffer = malloc(10); 
  sprintf(buffer, "%d", num_quads); 
  ifFalse_quad->address2 = buffer; 
}

static void process_ifelse(ast_node node){
  quad if_quad = create_quad(ifFalse);
  char * loc = strdup(node->left_child->location);
  if_quad->address1 = loc;

  // indicate that it's an ifelse
  quad ifelse_quad = create_quad(ifelse); 
  add_quad(node, ifelse_quad); 

  // add the code for the condition     
  add_quad_list(node, node->left_child->code);

  // add the ifFalse quad
  add_quad(node, if_quad);

  // add the compound 
  if (node->left_child->right_sibling != NULL){
    add_quad_list(node, node->left_child->right_sibling->code);
  }

  // if part is over
  quad end_if_quad = create_quad(end_ifstmt); 
  add_quad(node, end_if_quad); 

  // do the goto
  quad jump_quad = create_quad(jumpTo); 
  add_quad(node, jump_quad); 
  
  // if part is starting
  quad else_quad = create_quad(elsestmt); 
  add_quad(node, else_quad); 

  // add the else compound
  if (node->left_child->right_sibling->right_sibling != NULL){
    add_quad_list(node, node->left_child->right_sibling->right_sibling->code); 
  }

  // else part is over
  quad end_else = create_quad(end_elsestmt); 
  add_quad(node, end_else); 
  
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
  
  // indicate that it's a while loop
  quad while_quad = create_quad(whileloop); 
  add_quad(node, while_quad); 

  // add the code for the condition
  add_quad_list(node, node->left_child->code); 
  
  // add the ifFalse quad
  add_quad(node, if_false); 

  // add the code for the body
  if (node->left_child->right_sibling != NULL){
    add_quad_list(node, node->left_child->right_sibling->code); 
  }

  // mark the end of the body
  quad end_while = create_quad(end_whileloop); 
  add_quad(node, end_while); 

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

static void process_dowhile(ast_node node){
  // indicate that its a dowhile loop
  quad dowhile_quad = create_quad(dowhileloop); 
  add_quad(node, dowhile_quad); 

  // add the compound (body of dowhile loop)
  add_quad_list(node, node->left_child->code); 
  int beginning = node->code->first->next->num;
  
  quad end_loop = create_quad(end_dowhileloop); 
  add_quad(node, end_loop); 

  // add the code for the condition
  add_quad_list(node, node->left_child->right_sibling->code); 

  // test the condition (move on if it fails) and add its quad to code
  quad if_false = create_quad(ifFalse); 
  char * loc = strdup(node->left_child->right_sibling->location); 
  if_false->address1 = loc; 
  add_quad(node, if_false); 

  // unconditional jump to top of compound
  quad jump_to = create_quad(jumpTo); 
  char * buffer = malloc(10); 
  sprintf(buffer, "%d", beginning); 
  jump_to->address1 = buffer; 
  add_quad(node, jump_to); 
  
  // backpatch the if_false quad
  buffer = malloc(10); 
  sprintf(buffer, "%d", num_quads); 
  if_false->address2 = buffer; 
}

static void process_and(ast_node node){
  quad and_quad = create_quad(and); 
  add_quad(node, and_quad); 

  // address the value of the and will be stored here: 
  char * and_address = new_address(); 
  node->location = and_address; 

  char * left = process_left(node); 
  char * right = process_right(node); 

  // do the code for the left child
  add_quad_list(node, node->left_child->code); 
  
  // if the left child is false, short circuit
  quad if_false = create_quad(ifFalse); 
  char * loc = strdup(left); 
  if_false->address1 = loc; 
  add_quad(node, if_false); 

  // do the code for the right child
  add_quad_list(node, node->left_child->right_sibling->code); 
  quad assign = create_quad(assn); 
  assign->address1 = and_address; 
  assign->address2 = right;
  add_quad(node, assign); 

  // unconditional jump to code after the and
  quad jump_to = create_quad(jumpTo); 
  add_quad(node, jump_to); 

  // first was false, so the value is false (short circuited)
  quad assign2 = create_quad(assn); 
  assign2->address1 = and_address; 
  assign2->address2 = left;
  add_quad(node, assign2); 
  int short_circuit = assign2->num; 

  // backpatch the unconditional jump:
  char * buffer = malloc(10); 
  sprintf(buffer, "%d", num_quads); 
  jump_to->address1 = buffer; 

  // backpatch the short circuit
  buffer = malloc(10); 
  sprintf(buffer, "%d", short_circuit); 
  if_false->address2 = buffer; 

  quad end_and_quad = create_quad(end_and); 
  add_quad(node, end_and_quad); 
}

static void process_or(ast_node node){
  quad or_quad = create_quad(or);
  add_quad(node, or_quad); 

  // the value of the OR will be stored here: 
  char * or_address = new_address(); 
  node->location = or_address; 

  char * left = process_left(node); 
  char * right = process_right(node); 

  // add the code for the left child
  add_quad_list(node, node->left_child->code); 

  // if the left child is false, go to test for right child
  quad if_false = create_quad(ifFalse); 
  char * loc = strdup(left); 
  if_false->address1 = loc; 
  add_quad(node, if_false); 

  // unconditional jump (short circuiting)
  quad short_circuit = create_quad(jumpTo); 
  add_quad(node, short_circuit); 

  // add the code for the right child - if_false jumps here!
  add_quad_list(node, node->left_child->right_sibling->code);
  int if_false_jumps_here = node->left_child->right_sibling->code->first->num; 
  char * buffer = malloc(10); 
  sprintf(buffer, "%d", if_false_jumps_here); 
  if_false->address2 = buffer; 

  // OR gets the value of the right child
  quad assign_from_right = create_quad(assn); 
  assign_from_right->address1 = or_address; 
  assign_from_right->address2 = right; 
  add_quad(node, assign_from_right); 

  // unconditional jump (done) 
  quad done_jump = create_quad(jumpTo); 
  add_quad(node, done_jump); 

  // OR gets the value of the left child - short circuit jumps here!
  quad assign_from_left = create_quad(assn); 
  assign_from_left->address1 = or_address; 
  assign_from_left->address2 = left; 
  add_quad(node, assign_from_left); 
  
  // backpatch short_circuit
  buffer = malloc(10); 
  sprintf(buffer, "%d", assign_from_left->num); 
  short_circuit->address1 = buffer; 

  // backpatch done_jump (goes to next generated quad)
  buffer = malloc(10); 
  sprintf(buffer, "%d", num_quads); 
  done_jump->address1 = buffer; 

  quad end_or_quad = create_quad(end_or); 
  add_quad(node, end_or_quad); 
}

/* Handles START, CONDITION, and UPDATE of a for-loop, 
 * they just get values from their children 
 */ 
static void process_for_header(ast_node node){
  node->code = node->left_child->code; 
  node->location = node->left_child->location; 
}

static void process_for(ast_node node){
  // add start and condition code
  add_quad_list(node, node->left_child->code); 

  // indicate that it's a for-loop 
  // while loops are the same thing, so pretend it's one! shhhh ... 
  quad for_quad = create_quad(whileloop);
  add_quad(node, for_quad);

  add_quad_list(node, node->left_child->right_sibling->code); 
  int cond_start = node->left_child->right_sibling->code->first->num; 

  // if the condition is false, exit the loop 
  char * condition_location = node->left_child->right_sibling->location; 
  quad if_false = create_quad(ifFalse); 
  if_false->address1 = condition_location; 
  add_quad(node, if_false); 

  // add the code for the compound
  add_quad_list(node, node->left_child->right_sibling->right_sibling->right_sibling->code); 
  
  // add update code
  add_quad_list(node, node->left_child->right_sibling->right_sibling->code); 

  quad end_for = create_quad(end_whileloop); 
  add_quad(node, end_for); 

  // unconditional jump back to the condition
  quad jump = create_quad(jumpTo); 
  char * buffer = malloc(10); 
  sprintf(buffer, "%d", cond_start); 
  jump->address1 = buffer; 
  add_quad(node, jump); 

  // backpatch the if_false quad
  buffer = malloc(10); 
  sprintf(buffer, "%d", num_quads); 
  if_false->address2 = buffer; 
}

// (read, location, NULL, NULL)
static void process_read(ast_node node){
  quad read_quad = create_quad(read); 
  char * left = process_left(node);
  printf("left: %s\n", left); 
  read_quad->address1 = left; 

  if (node->left_child != NULL)
    add_quad_list(node, node->left_child->code); 
  add_quad(node, read_quad); 
}

// (rtrn, location, NULL, NULL); 
static void process_return(ast_node node){
  quad return_quad = create_quad(rtrn); 
  char * left = process_left(node); 
  return_quad->address1 = left; 
  node->location = left; 

  add_quad_list(node, node->left_child->code); 
  add_quad(node, return_quad); 
}

// (print, location or string lit, NULL, NULL)
static void process_print(ast_node node){
  quad print_quad = create_quad(print); 
  char *left = process_left(node); 
  print_quad->address1 = left; 

  add_quad_list(node, node->left_child->code); 
  add_quad(node, print_quad); 
} 

/* builds the code of a function; 
 * 1. Function declaration: (func_dec, type, name, NULL)
 * 2. Code of its children
 */ 
static void process_function(ast_node node){
  // create a quad with address1 = type and address2 = name
  quad func_dec_node = create_quad(func_dec);
  char * type; 

  if (node->left_child->node_type == INT_TYPE){
    type = "int"; 
  }
  else if (node->left_child->node_type == DOUBLE_TYPE){
    type = "double"; 
  }
  else if (node->left_child->node_type == VOID_TYPE){
    type = "void"; 
  }
  
  char * name = node->left_child->right_sibling->value.string; 
  func_dec_node->address1 = type; 
  func_dec_node->address2 = name;
  add_quad(node, func_dec_node); 

  // enter scope - hackity hack hack hack
  quad enter_quad = create_quad(enter);
  add_quad(node, enter_quad); 

  build_code(node, NULL, NULL, NULL, NULL); 

  // exit hacky scope
  quad leave_quad = create_quad(leave); 
  add_quad(node, leave_quad); 
 
  // default return
  quad return_quad = create_quad(rtrn); 
  add_quad(node, return_quad); 
  
  // leave subroutine (return addr will be in a register)
  quad exit_sub_quad = create_quad(exit_sub);
  add_quad(node, exit_sub_quad); 

  // if it's main, add halt
  if (strcmp(name, "main") == 0){
    quad halt_quad = create_quad(halt); 
    add_quad(node, halt_quad); 
  }

}

/* pop each value off the stack that corresponds with a parameter 
 * and assign the value to said parameter 
 */ 
static void process_params(ast_node node){
  ast_node param = node->left_child; 
  while (param != NULL){
    // add the code for the variable declaration
    param->code->first->opcode = pardec; 
    // add_quad_list(node, param->code);
    //print_code(param->code); 
    add_quad(node, param->code->first); 
    param = param->right_sibling; 
  }
}

/* declare a variable
 * This only happens if it has a left child (otherwise it's saying the type
 * of a function.
 * Format: (vardec, type, name, NULL)
 */  
static void process_vardec(ast_node node){
  int assign; 

  if (node->left_child != NULL){
    quad vardec_quad = create_quad(vardec);

    // get the data type
    if (node->node_type == INT_TYPE)
      vardec_quad->address1 = "int"; 
    else if (node->node_type == DOUBLE_TYPE)
      vardec_quad->address1 = "double"; 

    if (node->left_child->node_type == OP_ASSIGN){
      vardec_quad->address2 = node->left_child->left_child->value.string; 
      assign = 1; 
    }
    
    // process array declaration                                    
    else if (node->left_child->node_type == ARRAY){
      int size; 
      // get the size of the array
      if (node->left_child->left_child->right_sibling == NULL)
	size = 1; 
      else{
	size = node->left_child->left_child->right_sibling->value.int_value; 
      }
      char buffer[MAX_LEN];
      snprintf(buffer, MAX_LEN, "%d", size);
      vardec_quad->address3 = strdup(buffer);

      // get the name of the array     
      vardec_quad->address2 = process_left(node->left_child);
    
    }
    else {
      vardec_quad->address2 = node->left_child->value.string; 
    }

    if (vardec_quad->address2 != NULL)
      node->location = strdup(vardec_quad->address2);
 
    add_quad(node, vardec_quad);
    if (assign){
      add_quad_list(node, node->left_child->code); 
    }

  }
}

/* processes a call 
 * 1. push the params onto the stack
 * 2. goto_sub the function (location will be stored in symbol table maybe?) 
 * 3. get the return value (will be in a register) 
 */ 
static void process_call(ast_node node){
  // 1. push the params onto the stack in reverse order
  ast_node args = node->left_child->right_sibling; 

  ast_node curr; 
  for (curr = args->left_child; curr != NULL; curr = curr->right_sibling){
    quad push_quad = create_quad(push); 
    push_quad->address1 = curr->location;
    
    // it's a literal!
    if (push_quad->address1 == NULL){
      char buffer[MAX_LEN];
      char *val; 
      if (curr->type == Int){
	snprintf(buffer, MAX_LEN, "%d", curr->value.int_value);
        val = strdup(buffer);
	push_quad->address1 = val;
      }
      else{
	snprintf(buffer, MAX_LEN, "%f", curr->value.double_value); 
	val = strdup(buffer); 
	push_quad->address1 = val; 
      }
    }
 
    add_quad_to_beginning(node, push_quad); 
    add_quad_list_to_beginning(node, curr->code); 
  }

  // 2. jump to the function's subroutine
  quad goto_sub_quad = create_quad(goto_sub); 
  goto_sub_quad->address1 = node->left_child->value.string; 
  add_quad(node, goto_sub_quad); 

  // 3. get the return value 
  quad get_return = create_quad(get_rtrn); 
  get_return->address1 = new_address(); 
  node->location = get_return->address1; 
  add_quad(node, get_return); 
} 

static void process_id(ast_node node){
  node->location = node->value.string; 
}

// Format: (array_lkup, target, name, index)
static void process_array(ast_node node){
  quad array_quad = create_quad(array_lkup);

  // where you'll put value of array once you look it up                                                                         
  array_quad->address1 = new_address();

  array_quad->address2 = process_left(node);
  array_quad->address3 = process_right(node);
  add_quad(node, array_quad);
  node->location = array_quad->address1;
}

/* Process the root
 * 1. generate code for global vars and such (all before funcdecs)
 * 2. code for main function (if there is one)
 * 3. HALT quad
 * 4. code for all other functions
 */ 
static void process_root(ast_node node){
  // 1. generate code for everything before the function declarations
  /*  ast_node curr; 
  for (curr = node->left_child; curr != NULL && curr->node_type != FUNCDEC; curr = curr->right_sibling){
    add_quad_list(node, curr->code); 
  }

  ast_node first_funcdec = curr; 
  // 4. add the code for all the other functions
  for (curr = first_funcdec; curr != NULL; curr = curr->right_sibling){
    //name = curr->left_child->right_sibling->value.string; 
    //if (strcmp(name, "main") != 0){
      add_quad_list(node, curr->code); 
      //}
      }*/ 

  ast_node curr; 
  // add all global declarations first
  for (curr = node->left_child; curr != NULL; curr = curr->right_sibling){
    if (curr->node_type != FUNCDEC)
      add_quad_list(node, curr->code); 
  }

  // now add all the functions
  for (curr = node->left_child; curr != NULL; curr = curr->right_sibling){
    if (curr->node_type == FUNCDEC)
      add_quad_list(node, curr->code); 
  }
}

static void error(char * string){
  printf("Error found during generation of intermediate code in %s.\n", string); 
}
