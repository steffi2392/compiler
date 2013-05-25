%{
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "ast.h"
#include "table.h"

#define YYSTYPE ast_node
#define YYDEBUG 1

extern int yylex();
int yyerror(char *s);
extern char *yytext;

extern int lineNumber;
extern ast_node root;
extern int parseError;

extern char savedLiteralText[];
extern table symbol_table;
%}

%token INT DOUBLE ID VOID IF ELSE WHILE DO FOR RETURN READ PRINT NUM FNUM STRING BADTOKEN OR AND ISEQUAL NOTEQUAL LEQ GEQ INCREMENT DECREMENT
%right '='
%left OR
%left AND
%left ISEQUAL NOTEQUAL
%left '<' LEQ '>' GEQ
%left '+' '-'
%left '*' '/' '%'
%left '!' INCREMENT DECREMENT UMINUS

%expect 2

%%

program : declarationList {
  ast_node t = create_ast_node(ROOT, lineNumber);
  t->left_child = $1;
  $$ = t;
  root = $$;}
;

declarationList : declaration { $$ = $1; }
| declarationList declaration {
  ast_node t = $1;
    while (t->right_sibling != NULL)
      t = t->right_sibling;
    t->right_sibling = $2;
    $$ = $1;
 }
;

declaration : varDeclaration { $$ = $1; }
| funcDeclaration { $$ = $1; }
;

varDeclaration : varSpec varList ';' {
  ast_node t = $1;
  t->left_child = $2;
    ast_node vars = $2;
  do {
	if (vars->node_type == OP_ASSIGN || vars->node_type == ARRAY) 	vars->left_child->type = $1->type;
	else vars->type = $1->type;
	
	vars = vars->right_sibling;
	}
  while (vars != NULL);
  

  $$ = t;
 }
;

varSpec : INT {$$ = create_ast_node(INT_TYPE, lineNumber);
	$$->type = Int;}
| DOUBLE {$$ = create_ast_node(DOUBLE_TYPE, lineNumber);
	$$->type = Double;}
;

varList : varDecl { $$ = $1; }
| varList ',' varDecl {
  ast_node t = $1;
  if (t != NULL) {
    while (t->right_sibling != NULL)
      t = t->right_sibling;
    t->right_sibling = $3;
    $$ = $1;
  }
  else 
    $$ = NULL;
 }
;

varDecl : id { $$ = $1; }
| id '=' expr { 
  $$ = create_ast_node(OP_ASSIGN, lineNumber);
  $$->left_child = $1;
  $$->left_child->right_sibling = $3;
  }
| id '[' expr ']'{
  $$ = create_ast_node(ARRAY, lineNumber);
  $$->left_child = $1;
  $$->left_child->right_sibling = $3;
  }
;

funcDeclaration : varSpec id '(' formalParams ')' compound {
  ast_node t = create_ast_node(FUNCDEC, lineNumber);
  t->type = $1->type;
  ast_node current = $1;
  t->left_child = current;
  current->right_sibling = $2;
  current = $2;
  
  if ($4 != NULL){
    current->right_sibling = $4;
    current = $4;
    
    while (current->right_sibling != NULL) current=current->right_sibling;
    current->right_sibling = $6;
  }
  else current->right_sibling = $6;
  
  $$ = t;
 }
| VOID id '(' formalParams ')' compound {
  ast_node t = create_ast_node(FUNCDEC, lineNumber); 
  ast_node current = create_ast_node(VOID_TYPE, lineNumber); 
  t->left_child = current; 
  current->right_sibling = $2; 
  current = $2; 

  if ($4 != NULL){
    current->right_sibling = $4; 
    current = $4; 

    while (current->right_sibling != NULL) current=current->right_sibling;
    current->right_sibling = $6;
  }
  else current->right_sibling = $6; 

  $$ = t; 
 }

formalParams : formalList {
	ast_node a = create_ast_node(PARAMS, lineNumber);
	a->left_child= $1;
	$$ = a;}
| VOID {$$ = NULL;}
| {$$ = create_ast_node(PARAMS, lineNumber);}
;

formalList : formalParam { 
	/*ast_node params = create_ast_node(PARAMS, lineNumber);
	params->left_child = $1;
	$$ = params;*/
	$$ = $1;
	}
| formalList ',' formalParam {
  /*ast_node params = create_ast_node(PARAMS, lineNumber);*/
  ast_node t = $1;
  if (t != NULL) {
    while (t->right_sibling != NULL)
      t = t->right_sibling;
    t->right_sibling = $3;
    /*params->left_child = t;*/
    $$ = t;
  }
 }
/*| error ',' formalParam {$$ = NULL;}*/
;

formalParam : varSpec id {
  /*  ast_node t = create_ast_node(PARAM, lineNumber);*/
  $$ = $1;
  $$->left_child = $2;
  $$->left_child->type = $$->type;
  /*$$ = t;*/
 }
| varSpec id '[' ']' { 
  ast_node t = $1;
  ast_node array = create_ast_node(ARRAY, lineNumber);
  t->left_child = array;
  t->left_child->left_child = $2;
  t->left_child->left_child->type = t->type;
  $$ = t;
 }
;

compound : '{' localDec statementList '}' {
  ast_node t = create_ast_node(CMPD, lineNumber);
  if ($2 == NULL)
    t->left_child = $3;
  else {
    t->left_child = $2;
    ast_node current = $2;
    while (current->right_sibling != NULL)
      current = current->right_sibling;
    current->right_sibling = $3;
  }
  $$ = t;
 }
;

localDec : localDec varDeclaration {
  ast_node t = $1;
  if (t != NULL) {
    while (t->right_sibling != NULL)
      t = t->right_sibling;
    t->right_sibling = $2;
    $$ = $1;
  }
  else
    $$ = $2;
 }
| /* empty */ {$$ = NULL;}
;

statementList : statementList statement {
  ast_node t = $1;
  if (t != NULL) {
    while (t->right_sibling != NULL)
      t = t->right_sibling;
    t->right_sibling = $2;
    $$ = $1;
  }
  else 
    $$ = $2;
 }

| /* empty */ {$$ = NULL;}
;

statement : exprStatement {$$ = $1;}
| compound         {$$ = $1;}
| ifStatement      {$$ = $1;}
| whileStatement   {$$ = $1;}
| doWhileStatement {$$ = $1;}
| forStatement     {$$ = $1;}
| returnStatement  {$$ = $1;}
| readStatement    {$$ = $1;}
| printStatement   {$$ = $1;}
;

exprStatement : expr ';' { $$ = $1; }
| ';'               { $$ = NULL; }
| error ';'         { $$ = NULL; }
;

ifStatement : IF '(' expr ')' statement {
  ast_node t = create_ast_node(IF_STMT, lineNumber);
  t->left_child = $3;
  t->left_child->right_sibling = $5;
  $$ = t; }
| IF '(' expr ')' statement ELSE statement {
  ast_node t = create_ast_node(IF_ELSE_STMT, lineNumber);
  t->left_child = $3;
  t->left_child->right_sibling = $5;
  t->left_child->right_sibling->right_sibling = $7;
  $$ = t; }
| IF '(' error ')' statement { $$ = NULL; }
| IF '(' error ')' statement ELSE statement { $$ = NULL; }
;

whileStatement : WHILE '(' expr ')' statement {
  ast_node t = create_ast_node(WHILE_STMT, lineNumber);
  t->left_child = $3;
  t->left_child->right_sibling = $5;
  $$ = t;
 }
| WHILE '(' error ')' statement { $$ = NULL; }
;

doWhileStatement : DO statement WHILE '(' expr ')' {
  ast_node t = create_ast_node(DO_WHILE_STMT, lineNumber);
  t->left_child = $2;
  ast_node rightmost = t->left_child;
  while (rightmost->right_sibling != NULL)
    rightmost= rightmost->right_sibling;
  rightmost->right_sibling = $5;
  $$ = t;
 }
| DO statement WHILE '(' error ')' { $$ = NULL;}
;

forStatement : FOR '(' forExpr ';' forExpr ';' forExpr ')' statement {
  ast_node t = create_ast_node(FOR_STMT, lineNumber);
  /*ast_node leftmost = $9;
  ast_node temp;
  if ($7 != NULL){
    leftmost = $7;
    leftmost->right_sibling = $9;
  }
  
  if ($5 != NULL){
    temp = leftmost;
    leftmost = $5;
    leftmost->right_sibling = temp;
  }
  
  if ($3 != NULL){
    temp = leftmost;
    leftmost = $3;
    leftmost->right_sibling = temp;
  }
  
  t->left_child = leftmost;
  */
  ast_node start = create_ast_node(FOR_STRT, lineNumber);
  ast_node cond  = create_ast_node(FOR_COND, lineNumber);
  ast_node update= create_ast_node(FOR_UPDT, lineNumber);
  
  start->left_child  = $3;
  cond->left_child   = $5;
  update->left_child = $7;
  
  t->left_child = start;
  t->left_child->right_sibling = cond;
  t->left_child->right_sibling->right_sibling = update;
  t->left_child->right_sibling->right_sibling->right_sibling = $9;
  
  $$ = t;
 }
| FOR '(' error ';' forExpr ';' forExpr ')' statement { $$ = NULL;}
| FOR '(' forExpr ';' error ';' forExpr ')' statement { $$ = NULL;}
| FOR '(' forExpr ';' forExpr ';' error ')' statement { $$ = NULL;}
| FOR '(' error ';' forExpr ';' error ')' statement { $$ = NULL;}
| FOR '(' error ';' error ';' forExpr ')' statement { $$ = NULL;}
| FOR '(' forExpr ';' error ';' error ')' statement { $$ = NULL;}
| FOR '(' error ';' error ';' error ')' statement { $$ = NULL;}

;

forExpr : expr {$$ = $1;}
| /* empty */ {$$ = NULL;}
;

returnStatement : RETURN ';' {$$ = create_ast_node(RETURN_STMT, lineNumber);}
| RETURN expr ';' {
  $$ = create_ast_node(RETURN_STMT, lineNumber);
  $$->left_child = $2;
 }

| RETURN error ';' { $$ = NULL; }
;

readStatement : READ var { 
  $$ = create_ast_node(READ_STMT, lineNumber);
  $$->left_child = $2;
 }
;

printStatement : PRINT expr ';'{ 
  $$ = create_ast_node(PRINT_STMT, lineNumber);
  $$->left_child = $2;
 }
| PRINT STRING ';'{
  $$ = create_ast_node(PRINT_STMT, lineNumber);
  ast_node t = create_ast_node(STRING_LIT, lineNumber);
  t->value.string = strdup(savedLiteralText);
  $$->left_child = t;
 }
| PRINT error ';' {$$ = NULL;}
;

expr : var'='expr{
  ast_node t = create_ast_node(OP_ASSIGN, lineNumber);
  t->left_child = $1;
  t->left_child->right_sibling = $3;
  $$ = t;}
| rValue {$$ = $1;}
;

var : id { $$ = $1;  }
| id '[' expr ']' {
  ast_node t = create_ast_node(ARRAY, lineNumber);
  t->left_child = $1;
  t->left_child->right_sibling = $3;
  $$ = t;
}
| id '[' error ']' { $$ = NULL;}
;

rValue : expr '+' expr {
  ast_node t = create_ast_node(OP_PLUS, lineNumber);
  t->left_child = $1;
  t->left_child->right_sibling = $3;
  $$ = t;
 }
| expr '-' expr {
  ast_node t = create_ast_node(OP_MINUS, lineNumber);
  t->left_child = $1;
  t->left_child->right_sibling = $3;
  $$ = t;
  }
| expr '*' expr {
  ast_node t = create_ast_node(OP_TIMES, lineNumber);
  t->left_child = $1;
  t->left_child->right_sibling = $3;
  $$ = t;
  }
| expr '/' expr {
  ast_node t = create_ast_node(OP_DIVIDE, lineNumber);
  t->left_child = $1;
  t->left_child->right_sibling = $3;
  $$ = t;
  }
| expr '%' expr {
  ast_node t = create_ast_node(OP_MOD, lineNumber);
  t->left_child = $1;
  t->left_child->right_sibling = $3;
  $$ = t;
  }
| expr '<' expr {
  ast_node t = create_ast_node(OP_LT, lineNumber);
  t->left_child = $1;
  t->left_child->right_sibling = $3;
  t->type = Int;
  $$ = t;
  }
| expr LEQ expr {
  ast_node t = create_ast_node(OP_LEQ, lineNumber);
  t->left_child = $1;
  t->left_child->right_sibling = $3;
  t->type = Int;
  $$ = t;
  }
| expr '>' expr {
  ast_node t = create_ast_node(OP_GT, lineNumber);
  t->left_child = $1;
  t->left_child->right_sibling = $3;
  t->type = Int;
  $$ = t;
  }
| expr GEQ expr {
  ast_node t = create_ast_node(OP_GEQ, lineNumber);
  t->left_child = $1;
  t->left_child->right_sibling = $3;
  t->type = Int;
  $$ = t;
  }
| expr ISEQUAL expr {
  ast_node t = create_ast_node(OP_EQUALS, lineNumber);
  t->left_child = $1;
  t->type = Int;
  t->left_child->right_sibling = $3;
  $$ = t;
  }
| expr NOTEQUAL expr {
  ast_node t = create_ast_node(OP_NEQUALS, lineNumber);
  t->left_child = $1;
  t->left_child->right_sibling = $3;
  t->type = Int;
  $$ = t;
  }
| expr AND expr {
  ast_node t = create_ast_node(OP_AND, lineNumber);
  t->left_child = $1;
  t->left_child->right_sibling = $3;
  t->type = Int;
  $$ = t;
  }
| expr OR expr {
  ast_node t = create_ast_node(OP_OR, lineNumber);
  t->left_child = $1;
  t->left_child->right_sibling = $3;
  t->type = Int;
  $$ = t;
  }
| '!' expr {
  ast_node t = create_ast_node(OP_NOT, lineNumber);
  t->left_child = $2;
  t->type = Int;
  $$ = t;
  }
| '-' expr %prec UMINUS {
  ast_node t = create_ast_node(OP_NEG, lineNumber);
  t->left_child = $2;
  $$ = t;
  }
| var { $$ = $1;}
| INCREMENT var {
  ast_node t = create_ast_node(OP_INC, lineNumber);
  t->left_child = $2;
  $$ = t;
  }
| DECREMENT var {
  ast_node t = create_ast_node(OP_DEC, lineNumber);
  t->left_child = $2;
  $$ = t;
  }
| '(' expr ')' {$$ = $2;}
| '(' error ')' { $$ = NULL;}
| call {$$ = $1;}
| NUM {
  ast_node t = create_ast_node(INT_LITERAL, lineNumber);
  t->value.int_value = atoi(yytext);
  t->type = Int;
  $$ = t;
  }
| FNUM {
  ast_node t = create_ast_node(DOUBLE_LITERAL, lineNumber);
  t->value.double_value = atof(yytext);
  t->type = Double;
  $$ = t;
  }
;

call : id '(' args ')' {
  ast_node t = create_ast_node(CALL, lineNumber);
  t->left_child = $1;
  t->left_child->right_sibling = $3;
  $$ = t;
 }

args : argList { 
	ast_node a = create_ast_node(ARGS, lineNumber);
	a->left_child = $1;
	$$ = a;
	}
| /*empty */ { $$ = create_ast_node(ARGS, lineNumber) ; }
;

argList : argList ',' expr {
  ast_node t = $1;
  if (t != NULL) {
    while (t->right_sibling != NULL)
      t = t->right_sibling;
    t->right_sibling = $3;
    $$ = $1;
  }
  else
    $$ = NULL;
  
 }
| expr { $$ = $1; }
/*| error { $$ = NULL; } */
;

id : ID { 
  ast_node t = create_ast_node(IDENT, lineNumber);
  char* buffer;
  buffer = lookup(symbol_table, yytext);
  if (buffer != NULL)
    t->value.string = buffer;
  else 
    t->value.string =  add_id(symbol_table, yytext); 
  $$ = t;
 }
;
%%

int yyerror(char *s){
  parseError = 1; 
  fprintf(stderr, "%s at line %d\n", s, lineNumber); 
  return 0; 
}  

