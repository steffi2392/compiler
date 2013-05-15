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
  ast_node t = create_ast_node(ROOT);
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
  $$ = t;
 }
;

varSpec : INT {$$ = create_ast_node(INT_TYPE);}
| DOUBLE {$$ = create_ast_node(DOUBLE_TYPE);}
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
  $$ = create_ast_node(OP_ASSIGN);
  $$->left_child = $1;
  $$->left_child->right_sibling = $3;
  }
| id '[' expr ']'{
  $$ = create_ast_node(ARRAY);
  $$->left_child = $1;
  $$->left_child->right_sibling = $3;
  }
;

funcDeclaration : varSpec id '(' formalParams ')' compound {
  ast_node t = create_ast_node(FUNCDEC);
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
  ast_node t = create_ast_node(FUNCDEC); 
  ast_node current = create_ast_node(VOID_TYPE); 
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

formalParams : formalList {$$ = $1;}
| VOID {$$ = NULL;}
|/* empty, since these are null, we skip over formal params in funcDeclaration*/  {$$ = NULL;}
;

formalList : formalParam { $$ = $1; }
| formalList ',' formalParam {
  ast_node params = create_ast_node(PARAMS);
  
  ast_node t = $1;
  if (t != NULL) {
    while (t->right_sibling != NULL)
      t = t->right_sibling;
    t->right_sibling = $3;
    params->left_child = t;
    $$ = params;
  }
 }
/*| error ',' formalParam {$$ = NULL;}*/
;

formalParam : varSpec id {
  /*  ast_node t = create_ast_node(PARAM);*/
  $$ = $1;
  $$->left_child = $2;
  /*$$ = t;*/
 }
| varSpec id '[' ']' { 
  ast_node t = $1;
  ast_node array = create_ast_node(ARRAY);
  t->left_child = array;
  t->left_child->left_child = $2;
  //t->left_child->right_sibling->left_child = $2;
  $$ = t;
 }
;

compound : '{' localDec statementList '}' {
  ast_node t = create_ast_node(CMPD);
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
  ast_node t = create_ast_node(IF_STMT);
  t->left_child = $3;
  t->left_child->right_sibling = $5;
  $$ = t; }
| IF '(' expr ')' statement ELSE statement {
  ast_node t = create_ast_node(IF_ELSE_STMT);
  t->left_child = $3;
  t->left_child->right_sibling = $5;
  t->left_child->right_sibling->right_sibling = $7;
  $$ = t; }
| IF '(' error ')' statement { $$ = NULL; }
| IF '(' error ')' statement ELSE statement { $$ = NULL; }
;

whileStatement : WHILE '(' expr ')' statement {
  ast_node t = create_ast_node(WHILE_STMT);
  t->left_child = $3;
  t->left_child->right_sibling = $5;
  $$ = t;
 }
| WHILE '(' error ')' statement { $$ = NULL; }
;

doWhileStatement : DO statement WHILE '(' expr ')' {
  ast_node t = create_ast_node(DO_WHILE_STMT);
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
  ast_node t = create_ast_node(FOR_STMT);
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
  ast_node start = create_ast_node(FOR_STRT);
  ast_node cond  = create_ast_node(FOR_COND);
  ast_node update= create_ast_node(FOR_UPDT);
  
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

returnStatement : RETURN ';' {$$ = create_ast_node(RETURN_STMT);}
| RETURN expr ';' {
  $$ = create_ast_node(RETURN_STMT);
  $$->left_child = $2;
 }

| RETURN error ';' { $$ = NULL; }
;

readStatement : READ var { 
  $$ = create_ast_node(READ_STMT);
  $$->left_child = $2;
 }
;

printStatement : PRINT expr ';'{ 
  $$ = create_ast_node(PRINT_STMT);
  $$->left_child = $2;
 }
| PRINT STRING ';'{
  $$ = create_ast_node(PRINT_STMT);
  ast_node t = create_ast_node(STRING_LIT);
  t->value.string = strdup(savedLiteralText);
  $$->left_child = t;
 }
| PRINT error ';' {$$ = NULL;}
;

expr : var'='expr{
  ast_node t = create_ast_node(OP_ASSIGN);
  t->left_child = $1;
  t->left_child->right_sibling = $3;
  $$ = t;}
| rValue {$$ = $1;}
;

var : id { $$ = $1;  }
| id '[' expr ']' {
  ast_node t = create_ast_node(ARRAY);
  t->left_child = $1;
  t->left_child->right_sibling = $3;
  $$ = t;
}
| id '[' error ']' { $$ = NULL;}
;

rValue : expr '+' expr {
  ast_node t = create_ast_node(OP_PLUS);
  t->left_child = $1;
  t->left_child->right_sibling = $3;
  $$ = t;
 }
| expr '-' expr {
  ast_node t = create_ast_node(OP_MINUS);
  t->left_child = $1;
  t->left_child->right_sibling = $3;
  $$ = t;
  }
| expr '*' expr {
  ast_node t = create_ast_node(OP_TIMES);
  t->left_child = $1;
  t->left_child->right_sibling = $3;
  $$ = t;
  }
| expr '/' expr {
  ast_node t = create_ast_node(OP_DIVIDE);
  t->left_child = $1;
  t->left_child->right_sibling = $3;
  $$ = t;
  }
| expr '%' expr {
  ast_node t = create_ast_node(OP_MOD);
  t->left_child = $1;
  t->left_child->right_sibling = $3;
  $$ = t;
  }
| expr '<' expr {
  ast_node t = create_ast_node(OP_LT);
  t->left_child = $1;
  t->left_child->right_sibling = $3;
  $$ = t;
  }
| expr LEQ expr {
  ast_node t = create_ast_node(OP_LEQ);
  t->left_child = $1;
  t->left_child->right_sibling = $3;
  $$ = t;
  }
| expr '>' expr {
  ast_node t = create_ast_node(OP_GT);
  t->left_child = $1;
  t->left_child->right_sibling = $3;
  $$ = t;
  }
| expr GEQ expr {
  ast_node t = create_ast_node(OP_GEQ);
  t->left_child = $1;
  t->left_child->right_sibling = $3;
  $$ = t;
  }
| expr ISEQUAL expr {
  ast_node t = create_ast_node(OP_EQUALS);
  t->left_child = $1;
  t->left_child->right_sibling = $3;
  $$ = t;
  }
| expr NOTEQUAL expr {
  ast_node t = create_ast_node(OP_NEQUALS);
  t->left_child = $1;
  t->left_child->right_sibling = $3;
  $$ = t;
  }
| expr AND expr {
  ast_node t = create_ast_node(OP_AND);
  t->left_child = $1;
  t->left_child->right_sibling = $3;
  $$ = t;
  }
| expr OR expr {
  ast_node t = create_ast_node(OP_OR);
  t->left_child = $1;
  t->left_child->right_sibling = $3;
  $$ = t;
  }
| '!' expr {
  ast_node t = create_ast_node(OP_NOT);
  t->left_child = $2;
  $$ = t;
  }
| '-' expr %prec UMINUS {
  ast_node t = create_ast_node(OP_NEG);
  t->left_child = $2;
  $$ = t;
  }
| var { $$ = $1;}
| INCREMENT var {
  ast_node t = create_ast_node(OP_INC);
  t->left_child = $2;
  $$ = t;
  }
| DECREMENT var {
  ast_node t = create_ast_node(OP_DEC);
  t->left_child = $2;
  $$ = t;
  }
| '(' expr ')' {$$ = $2;}
| '(' error ')' { $$ = NULL;}
| call {$$ = $1;}
| NUM {
  ast_node t = create_ast_node(INT_LITERAL);
  t->value.int_value = atoi(yytext);
  $$ = t;
  }
| FNUM {
  ast_node t = create_ast_node(DOUBLE_LITERAL);
  t->value.double_value = atof(yytext);
  $$ = t;
  }
;

call : id '(' args ')' {
  ast_node t = create_ast_node(CALL);
  t->left_child = $1;
  t->left_child->right_sibling = $3;
  $$ = t;
 }

args : argList { $$ = $1; }
| /*empty */ { $$ = NULL; }
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
  ast_node t = create_ast_node(IDENT);
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

