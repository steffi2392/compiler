#include <stdio.h>
#include "ast.h"
#include "table.h"
#include "symtab.h"
#include "typecheck.h"

static void test_basic(); 
static void test_if(); 
static void test_if_else(); 
static void test_while(); 
static void test_dowhile(); 
static void test_and(); 
static void test_or(); 
static void test_for();
static void test_read_print(); 
static void test_function(); 
static void test_call();
  
ast_node root = NULL;

extern int yyparse(); 
extern int yydebug; 
int parseError = 0; 
symboltable symtab; 
table symbol_table; 


int main(){
  /*  test_basic(); 
  reset_num_quads(); 
  test_if(); 
  reset_num_quads(); 
  test_if_else(); 
  reset_num_quads(); 
  test_while(); 
  reset_num_quads(); 
  test_dowhile(); 
  reset_num_quads(); 
  test_and(); 
  reset_num_quads(); 
  test_or(); 
  reset_num_quads(); 
  test_for(); 
  reset_num_quads(); 
  test_read_print(); 
  reset_num_quads(); 
  */ 
  test_function(); 
  reset_num_quads(); 
  test_call(); 
}

static void test_basic(){
  // manually set up the tree 
  root = create_ast_node(ROOT);
  ast_node minus = create_ast_node(OP_MINUS);
  ast_node assign = create_ast_node(OP_ASSIGN);
  ast_node plus = create_ast_node(OP_PLUS);
  ast_node negate = create_ast_node(OP_NEG);
  ast_node inc = create_ast_node(OP_INC);

  ast_node x = create_ast_node(IDENT);
  x->value.string = "x";

  ast_node y = create_ast_node(IDENT);
  y->value.string = "y";

  ast_node z = create_ast_node(IDENT);
  z->value.string = "z";

  ast_node three = create_ast_node(INT_LITERAL);
  three->value.int_value = 3;

  root->left_child = minus;
  minus->left_child = assign;
  minus->left_child->right_sibling = negate;

  negate->left_child = z;

  assign->left_child = x;
  assign->left_child->right_sibling = plus;

  plus->left_child = inc;
  inc->left_child = y;
  plus->left_child->right_sibling = three;

  // now actually do stuff with it                                                      
  generate_traverse(root);

  printf("\n\n********** basic test **********\n\n"); 
  print_ast(root, 0);
  print_code(root->left_child->code);

  /*  ast_node node_list[] = {minus, assign, plus, negate, inc}; 
  int i; 
  for (i = 0; i < 5; i++){
    destroy_ast_node(node_list[i]); 
    }*/ 
}

static void test_if(){
  // manually set up the tree    
  root = create_ast_node(ROOT);
  ast_node ifNode = create_ast_node(IF_STMT); 
  ast_node afterIf = create_ast_node(OP_ASSIGN); 
  ast_node equals = create_ast_node(OP_EQUALS); 
  ast_node compound = create_ast_node(CMPD); 
  ast_node inIf = create_ast_node(OP_ASSIGN); 
  ast_node plus = create_ast_node(OP_PLUS); 

  ast_node x = create_ast_node(IDENT); 
  x->value.string = "x"; 
  ast_node y = create_ast_node(IDENT); 
  y->value.string = "y"; 
  ast_node a = create_ast_node(IDENT); 
  a->value.string = "a"; 
  ast_node b = create_ast_node(IDENT); 
  b->value.string = "b"; 
  ast_node e = create_ast_node(IDENT); 
  e->value.string = "e"; 
  ast_node f = create_ast_node(IDENT); 
  f->value.string = "f"; 
  ast_node five = create_ast_node(INT_LITERAL); 
  five->value.int_value = 5; 

  root->left_child = ifNode; 

  ifNode->right_sibling = afterIf; 
  ifNode->left_child = equals; 

  equals->left_child = x; 
  x->right_sibling = y; 
  equals->right_sibling = compound; 

  compound->left_child = inIf; 
  inIf->left_child = a; 
  a->right_sibling = b; 

  afterIf->left_child = e; 
  e->right_sibling = plus;
  plus->left_child = f; 
  f->right_sibling = five; 

  // now actually do stuff with it
  generate_traverse(root);
  printf("\n\n********** if test **********\n\n");
  print_ast(root, 0);
  print_code(root->left_child->code);
  /*
  ast_node node_list[] = {ifNode, afterIf, equals, compound, inIf, plus, x, y, a, 
			  b, e, f, five}; 
  int i; 
  for (i = 0; i < 13; i++){
    destroy_ast_node(node_list[i]); 
    printf("test\n"); 
    }*/ 
}

static void test_if_else(){
  // manually set up the tree                                                           
  root = create_ast_node(ROOT);
  ast_node ifNode = create_ast_node(IF_ELSE_STMT);
  ast_node afterIf = create_ast_node(OP_ASSIGN);
  ast_node equals = create_ast_node(OP_EQUALS);
  ast_node if_compound = create_ast_node(CMPD);
  ast_node else_compound = create_ast_node(CMPD); 
  ast_node inIf = create_ast_node(OP_ASSIGN);
  ast_node plus = create_ast_node(OP_PLUS);
  ast_node else_assign = create_ast_node(OP_ASSIGN); 

  ast_node x = create_ast_node(IDENT);
  x->value.string = "x";
  ast_node y = create_ast_node(IDENT);
  y->value.string = "y";
  ast_node a = create_ast_node(IDENT);
  a->value.string = "a";
  ast_node b = create_ast_node(IDENT);
  b->value.string = "b";
  ast_node c = create_ast_node(IDENT); 
  c->value.string = "c"; 
  ast_node d = create_ast_node(IDENT); 
  d->value.string = "d"; 
  ast_node e = create_ast_node(IDENT);
  e->value.string = "e";
  ast_node f = create_ast_node(IDENT);
  f->value.string = "f";
  ast_node five = create_ast_node(INT_LITERAL);
  five->value.int_value = 5;

  root->left_child = ifNode;

  ifNode->right_sibling = afterIf;
  ifNode->left_child = equals;

  equals->left_child = x;
  x->right_sibling = y;
  equals->right_sibling = if_compound;

  if_compound->left_child = inIf;
  inIf->left_child = a;
  a->right_sibling = b;

  if_compound->right_sibling = else_compound; 
  else_compound->left_child = else_assign; 
  else_assign->left_child = c; 
  c->right_sibling = d; 

  afterIf->left_child = e;
  e->right_sibling = plus;
  plus->left_child = f;
  f->right_sibling = five;

  // now actually do stuff with it 
  generate_traverse(root);
  printf("\n\n********** if else test **********\n\n");
  print_ast(root, 0);
  print_code(root->left_child->code);
  /*
  ast_node node_list[] = {ifNode, afterIf, equals, if_compound, else_compound, 
			  inIf, plus, else_assign, x, y, a, b, c, d, e, f, five};
  int i; 
  for (i = 0; i < 17; i++){
    destroy_ast_node(node_list[i]);
    }*/ 

}

static void test_while(){
  root = create_ast_node(ROOT); 
  ast_node while_node = create_ast_node(WHILE_STMT); 
  ast_node after_while = create_ast_node(OP_ASSIGN); 
  ast_node condition = create_ast_node(OP_EQUALS); 
  ast_node compound = create_ast_node(CMPD); 
  ast_node equals1 = create_ast_node(OP_EQUALS); 
  ast_node equals2 = create_ast_node(OP_EQUALS); 

  ast_node x = create_ast_node(IDENT);
  x->value.string = "x";
  ast_node y = create_ast_node(IDENT);
  y->value.string = "y";
  ast_node a = create_ast_node(IDENT);
  a->value.string = "a";
  ast_node b = create_ast_node(IDENT);
  b->value.string = "b";
  ast_node c = create_ast_node(IDENT);
  c->value.string = "c";
  ast_node d = create_ast_node(IDENT);
  d->value.string = "d";
  ast_node e = create_ast_node(IDENT);
  e->value.string = "e";
  ast_node f = create_ast_node(IDENT);
  f->value.string = "f";

  root->left_child = while_node; 
  while_node->left_child = condition;
  condition->right_sibling = compound; 

  condition->left_child = x; 
  x->right_sibling = y; 

  compound->left_child = equals1; 
  equals1->right_sibling = equals2; 
  equals1->left_child = a; 
  a->right_sibling = b; 
  equals2->left_child = c; 
  c->right_sibling = d; 

  while_node->right_sibling = after_while; 
  after_while->left_child = e; 
  e->right_sibling = f; 

  generate_traverse(root); 
  printf("\n\n********** while test **********\n\n");
  print_ast(root, 0);
  print_code(root->left_child->code);

}
static void test_dowhile(){
  root = create_ast_node(ROOT);
  ast_node dowhile_node = create_ast_node(DO_WHILE_STMT);
  ast_node after_while = create_ast_node(OP_ASSIGN);
  ast_node condition = create_ast_node(OP_LT);
  ast_node compound = create_ast_node(CMPD);
  ast_node equals1 = create_ast_node(OP_EQUALS);
  ast_node equals2 = create_ast_node(OP_EQUALS);

  ast_node x = create_ast_node(IDENT);
  x->value.string = "x";
  ast_node y = create_ast_node(IDENT);
  y->value.string = "y";
  ast_node a = create_ast_node(IDENT);
  a->value.string = "a";
  ast_node b = create_ast_node(IDENT);
  b->value.string = "b";
  ast_node c = create_ast_node(IDENT);
  c->value.string = "c";
  ast_node d = create_ast_node(IDENT);
  d->value.string = "d";
  ast_node e = create_ast_node(IDENT);
  e->value.string = "e";
  ast_node f = create_ast_node(IDENT);
  f->value.string = "f";

  root->left_child = dowhile_node;
  dowhile_node->left_child = compound;
  compound->right_sibling = condition;

  condition->left_child = x;
  x->right_sibling = y;

  compound->left_child = equals1;
  equals1->right_sibling = equals2;
  equals1->left_child = a;
  a->right_sibling = b;
  equals2->left_child = c;
  c->right_sibling = d;

  dowhile_node->right_sibling = after_while;
  after_while->left_child = e;
  e->right_sibling = f;
  
  printf("\n\n********** do while test **********\n\n");
  print_ast(root, 0);
  generate_traverse(root); 
  print_code(root->left_child->code);
}

static void test_and(){
  root = create_ast_node(ROOT); 
  ast_node and = create_ast_node(OP_AND); 
  ast_node lt = create_ast_node(OP_LT); 
  ast_node equals = create_ast_node(OP_EQUALS);
  ast_node assign = create_ast_node(OP_ASSIGN); 
  ast_node x = create_ast_node(IDENT); 
  x->value.string = "x"; 
  ast_node five = create_ast_node(INT_LITERAL); 
  five->value.int_value = 5; 

  ast_node y = create_ast_node(IDENT); 
  y->value.string = "y"; 

  ast_node two = create_ast_node(INT_LITERAL); 
  two->value.int_value = 2; 

  ast_node z = create_ast_node(IDENT); 
  z->value.string = "z"; 

  ast_node one = create_ast_node(INT_LITERAL); 
  one->value.int_value = 1; 

  root->left_child = and; 
  and->right_sibling = assign; 
  
  and->left_child = lt; 
  lt->right_sibling = equals; 
  lt->left_child = x; 
  x->right_sibling = five; 

  equals->left_child = y; 
  y->right_sibling = two; 

  assign->left_child = z; 
  z->right_sibling = one; 

  printf("\n\n********** and test **********\n\n");
  print_ast(root, 0);
  generate_traverse(root);
  print_code(root->left_child->code);
}

static void test_or(){
  root = create_ast_node(ROOT);
  ast_node or = create_ast_node(OP_OR);
  ast_node lt = create_ast_node(OP_LT);
  ast_node equals = create_ast_node(OP_EQUALS);
  ast_node assign = create_ast_node(OP_ASSIGN);
  ast_node x = create_ast_node(IDENT);
  x->value.string = "x";
  ast_node five = create_ast_node(INT_LITERAL);
  five->value.int_value = 5;

  ast_node y = create_ast_node(IDENT);
  y->value.string = "y";

  ast_node two = create_ast_node(INT_LITERAL);
  two->value.int_value = 2;

  ast_node z = create_ast_node(IDENT);
  z->value.string = "z";

  ast_node one = create_ast_node(INT_LITERAL);
  one->value.int_value = 1;

  root->left_child = or;
  or->right_sibling = assign;

  or->left_child = lt;
  lt->right_sibling = equals;
  lt->left_child = x;
  x->right_sibling = five;

  equals->left_child = y;
  y->right_sibling = two;

  assign->left_child = z;
  z->right_sibling = one;

  printf("\n\n********** or test **********\n\n");
  print_ast(root, 0);
  generate_traverse(root);
  print_code(root->left_child->code);
}

static void test_for(){
  root = create_ast_node(ROOT); 
  ast_node for_node = create_ast_node(FOR_STMT); 
  ast_node start = create_ast_node(FOR_STRT); 
  ast_node cond = create_ast_node(FOR_COND); 
  ast_node update = create_ast_node(FOR_UPDT); 
  ast_node compound = create_ast_node(CMPD); 
  
  ast_node assign1 = create_ast_node(OP_ASSIGN);
  ast_node lt = create_ast_node(OP_LT); 
  ast_node assign2 = create_ast_node(OP_ASSIGN); 
  ast_node plus = create_ast_node(OP_PLUS); 
  ast_node assign3 = create_ast_node(OP_ASSIGN); 
  ast_node plus2 = create_ast_node(OP_PLUS); 
  ast_node after_for = create_ast_node(OP_ASSIGN); 

  ast_node i = create_ast_node(IDENT); 
  i->value.string = "i"; 

  ast_node zero = create_ast_node(INT_LITERAL); 
  zero->value.int_value = 0; 

  ast_node i2 = create_ast_node(IDENT); 
  i2->value.string = "i"; 

  ast_node five = create_ast_node(INT_LITERAL); 
  five->value.int_value = 5; 

  ast_node i3 = create_ast_node(IDENT); 
  i3->value.string = "i"; 

  ast_node i4 = create_ast_node(IDENT); 
  i4->value.string = "i"; 

  ast_node one = create_ast_node(INT_LITERAL); 
  one->value.int_value = 1; 

  ast_node x = create_ast_node(IDENT); 
  x->value.string = "x"; 
  
  ast_node y = create_ast_node(IDENT); 
  y->value.string = "y"; 

  ast_node one2 = create_ast_node(INT_LITERAL); 
  one2->value.int_value = 1; 

  ast_node a = create_ast_node(IDENT); 
  a->value.string = "a"; 

  ast_node b =create_ast_node(IDENT); 
  b->value.string = "b"; 

  root->left_child = for_node; 
  for_node->right_sibling = after_for; 
  for_node->left_child = start; 
  
  start->left_child = assign1; 
  assign1->left_child = i; 
  i->right_sibling = zero; 
  start->right_sibling = cond; 

  cond->left_child = lt; 
  lt->left_child = i2; 
  i2->right_sibling = five; 
  cond->right_sibling = update; 

  update->left_child = assign2;
  assign2->left_child = i3; 
  i3->right_sibling = plus; 
  plus->left_child = i4; 
  i4->right_sibling = one; 
  update->right_sibling = compound; 

  compound->left_child = assign3; 
  assign3->left_child = x; 
  x->right_sibling = plus2; 
  plus2->left_child = y; 
  y->right_sibling = one2; 

  after_for->left_child = a; 
  a->right_sibling = b; 

  printf("\n\n********** for test **********\n\n");
  print_ast(root, 0);
  generate_traverse(root);
  print_code(root->left_child->code);
}

static void test_read_print(){
  root = create_ast_node(ROOT); 
  ast_node read_node = create_ast_node(READ_STMT); 
  ast_node x = create_ast_node(IDENT); 
  x->value.string = "x"; 
  ast_node print_node = create_ast_node(PRINT_STMT); 

  root->left_child = read_node; 
  read_node->left_child = x; 

  printf("\n\n********** read/write test **********\n\n");
  print_ast(root, 0);
  generate_traverse(root);
  print_code(root->left_child->code);

}

static void test_function(){
  root = create_ast_node(ROOT); 
  ast_node func_dec = create_ast_node(FUNCDEC); 
  ast_node type = create_ast_node(INT_TYPE); 
  ast_node name = create_ast_node(IDENT); 
  name->value.string = "main"; 
  ast_node params_node = create_ast_node(PARAMS); 
  ast_node int_node = create_ast_node(INT_TYPE); 
  ast_node x = create_ast_node(IDENT); 
  x->value.string = "x"; 
  ast_node double_node = create_ast_node(DOUBLE_TYPE); 
  ast_node y = create_ast_node(IDENT); 
  y->value.string = "y"; 
  ast_node cmpd = create_ast_node(CMPD); 
  ast_node assign = create_ast_node(OP_ASSIGN); 
  ast_node a_dec = create_ast_node(INT_TYPE); 
  ast_node a0 = create_ast_node(IDENT); 
  a0->value.string = "a"; 
  ast_node a = create_ast_node(IDENT); 
  a->value.string = "a"; 
  ast_node b = create_ast_node(IDENT); 
  b->value.string = "b"; 
  ast_node return_node = create_ast_node(RETURN_STMT); 
  ast_node a2 = create_ast_node(IDENT); 
  a2->value.string = "a"; 

  root->left_child = func_dec; 
  func_dec->left_child = type; 
  type->right_sibling = name; 
  name->right_sibling = params_node;
  params_node->right_sibling = cmpd; 
  
  params_node->left_child = int_node; 
  int_node->left_child = x; 
  int_node->right_sibling = double_node; 
  double_node->left_child = y; 

  //  cmpd->left_child = a_dec; 
  //a_dec->right_sibling = assign; 
  a_dec->left_child = a0; 
  
  cmpd->left_child = assign; 
  assign->left_child = a_dec; 
  a_dec->right_sibling = b; 
  assign->right_sibling = return_node; 
  return_node->left_child = a2; 

  printf("\n\n********** function test **********\n\n");
  print_ast(root, 0);
  generate_traverse(root);
  print_code(root->left_child->code);

}

static void test_call(){
  root = create_ast_node(ROOT);
  ast_node call = create_ast_node(CALL); 
  ast_node name = create_ast_node(IDENT); 
  name->value.string = "main"; 

  ast_node args = create_ast_node(ARGS); 
  ast_node x = create_ast_node(IDENT); 
  x->value.string = "x"; 

  ast_node plus = create_ast_node(OP_PLUS);
  ast_node one = create_ast_node(INT_LITERAL); 
  one->value.int_value = 1; 
  ast_node two = create_ast_node(DOUBLE_LITERAL); 
  two->value.double_value = 2; 

  root->left_child = call; 
  call->left_child = name; 
  name->right_sibling = args; 
  
  args->left_child = x; 
  x->right_sibling = plus; 
  plus->left_child = one; 
  one->right_sibling = two; 

  printf("\n\n********** call test **********\n\n");
  print_ast(root, 0);
  generate_traverse(root);
  print_code(root->left_child->code);
}
