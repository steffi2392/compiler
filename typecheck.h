/* typecheck.h
 */ 

#ifndef TYPECHECK_H
#define TYPECHECK_H

#import "ast.h"
#import "symtab.h"

 
//void buildSymTab(ast_node parent, symboltable symtab); 
void traverse(ast_node parent, symboltable symtab);
#endif
