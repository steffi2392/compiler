#include <stdio.h>
#include "ast.h"
#include "table.h"
#include "symtab.h"
#include "typecheck.h"

static void test_basic(); 
static void test_if(); 
static void test_if_else(); 
static void test_while(); 

ast_node root = NULL;

extern int yyparse(); 
extern int yydebug; 
int parseError = 0; 
symboltable symtab; 
table symbol_table; 


int main(){
  test_basic(); 
  reset_num_quads(); 
  test_if(); 
  reset_num_quads(); 
  test_if_else(); 
  reset_num_quads(); 
  test_while(); 
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
