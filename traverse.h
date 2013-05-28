/* typecheck.h
 */ 

#ifndef TYPECHECK_H
#define TYPECHECK_H

#include "ast.h"
#include "symtab.h"

 
//void buildSymTab(ast_node parent, symboltable symtab); 
void traverse(ast_node parent, symboltable symtab);
#endif
