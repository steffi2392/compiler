#include <stdio.h> 
#include <stdlib.h>
#include "ast.h"
#include "symtab.h"
struct token_lookup {
  char *token;
  ast_node_type node_type;
};

static struct token_lookup token_table[] = {
  { "ROOT", ROOT },
  { "=", OP_ASSIGN },
  { "+", OP_PLUS },
  { "-", OP_MINUS },
  { "-", OP_NEG },
  { "*", OP_TIMES },
  { "/", OP_DIVIDE },
  { "==", OP_EQUALS },
  {"!=",OP_NEQUALS },
  {"%", OP_MOD},
  {"<", OP_LT},
  {"<=", OP_LEQ},
  {">",OP_GT},
  {">=", OP_GEQ},
  {"&&", OP_AND},
  {"||", OP_OR},
  {"!", OP_NOT},
  {"++", OP_INC},
  {"--", OP_DEC},
  { "IF", IF_STMT },
  {"IFELSE", IF_ELSE_STMT },
  {"WHILE", WHILE_STMT},
  {"DOWHILE",DO_WHILE_STMT},
  {"FOR",FOR_STMT},
  {"READ",READ_STMT},
  {"PRINT",PRINT_STMT},
  {"RETURN",RETURN_STMT},
  {"ID", IDENT },
  {"CALL", CALL},
  {"INT", INT_TYPE},
  {"DOUBLE", DOUBLE_TYPE},
  {"VOID", VOID_TYPE},
  {"FUNC DEC", FUNCDEC},
  {"CMPD", CMPD},
  {"ARRAY", ARRAY},
  {"INTLIT", INT_LITERAL },
  {"DOUBLELIT", DOUBLE_LITERAL },
  {"PARAMETERS", PARAMS},
  {"STRING",STRING_LIT },
  {"START", FOR_STRT},
  {"CONDITION", FOR_COND},
  {"UPDATE", FOR_UPDT},
  { NULL, 0 }
};
void scopecheck(ast_node parent, symboltable symtab){
	printf("begin checking node scope %s\n",  token_table[parent->node_type].token);

	// binary operations
	if (parent->node_type == OP_EQUALS || parent->node_type == OP_NEQUALS || parent->node_type == OP_LT || parent->node_type == OP_LEQ || parent->node_type == OP_GT ||
	parent->node_type == OP_GEQ, parent->node_type == OP_AND || 
	parent->node_type == OP_OR || parent->node_type == OP_PLUS  || parent->node_type == OP_MINUS || parent->node_type == OP_TIMES || parent->node_type == OP_DIVIDE || parent->node_type == OP_ASSIGN ){
		scopecheck(parent->left_child, symtab);
		scopecheck(parent->left_child->right_sibling, symtab);
	}
	// Unary operations
	if (parent->node_type == OP_NEG || parent->node_type == OP_INC || parent->node_type == OP_DEC || parent->node_type == OP_NOT || parent->node_type == READ_STMT)
		scopecheck(parent->left_child, symtab);
	
	if(parent->node_type == ARRAY){
		// check if the child of parent is in the scope
		int level;
		symnode orig = lookup_in_symboltable(symtab, parent->left_child->value.string, Array,&level);
		if (orig == NULL){
			fprintf(stderr, "Undeclared variable %s on line %d", parent->left_child->value.string, parent->line_number);
			exit(1);
			}
		scopecheck(parent->left_child->right_sibling, symtab);
	}
	
	if (parent->node_type == IDENT) {
		int level;
		symnode orig = lookup_in_symboltable(symtab, parent->value.string, Var,&level);
		if (orig == NULL){
			fprintf(stderr, "Undeclared variable %s on line %d", parent->value.string, parent->line_number);
			exit(1);
		}
	}
	if (parent->node_type == FUNCDEC){
		int level;
		symnode orig = lookup_in_symboltable(symtab, parent->left_child->value.string, Function,&level);
		if (orig == NULL){
			fprintf(stderr, "Undeclared function %s on line %d", parent->value.string, parent->line_number);
			exit(1);
		}
		ast_node args = parent->left_child->right_sibling->left_child;
		while (args != NULL){
			scopecheck(args, symtab);
			args = args->right_sibling;
		}
	}
}

types typecheck(ast_node parent, symboltable symtab){
	printf("begin checking node type %s\n",  token_table[parent->node_type].token);

	if (parent->node_type == INT_LITERAL)
		return Int;
	if (parent->node_type == DOUBLE_LITERAL)
		return Double;
	if (parent->node_type ==IDENT) {
		int level;
		symnode orig = lookup_in_symboltable(symtab, parent->value.string, Var,&level);
		printf("observing node %s, with node type %d and data type %d", orig->name, orig->node_type, orig->data_type);
		return orig->data_type;
	}
	
	if (parent->node_type == OP_EQUALS || parent->node_type == OP_NEQUALS || parent->node_type == OP_LT || parent->node_type == OP_LEQ || parent->node_type == OP_GT ||
	parent->node_type == OP_GEQ, parent->node_type == OP_AND || 
	parent->node_type == OP_OR || parent->node_type == OP_NOT)	return Int;
	
	
	if (parent->node_type == OP_NEG || parent->node_type == OP_INC || parent->node_type == OP_DEC) return parent->left_child->type;
		
	if (parent->node_type == OP_PLUS  || parent->node_type == OP_MINUS || parent->node_type == OP_TIMES || parent->node_type == OP_DIVIDE){
		types type1 = typecheck(parent->left_child, symtab);
		types type2 = typecheck(parent->left_child->right_sibling, symtab);
		if (type1 == Double || type2 == Double)
			return Double;
		else
			return Int;
	}
	if (parent->node_type == OP_ASSIGN){
		types type1 = typecheck(parent->left_child, symtab);
		types type2 = typecheck(parent->left_child->right_sibling, symtab);
		if (type1 != type2){
			fprintf(stderr, "Type Error on line %d, assigning %d to %d variable\n", parent->line_number, type2, type1);
			exit(1);
			}
		else return type1;
	}
	if (parent->node_type == ARRAY){
		int level;
		symnode orig = lookup_in_symboltable(symtab, parent->left_child->value.string, Array,&level);
		printf("observing node %s, with node type %d and data type %d", orig->name, orig->node_type, orig->data_type);
		types type1 = orig->data_type;
		types type2 = typecheck(parent->left_child->right_sibling, symtab);
		if(type2 != Int){
			fprintf(stderr, "Indexing Error on line %d, Use int index", parent->line_number);
			exit(1);
		}
		else return type1;
	}
	if (parent->node_type == CALL){
		int level;
		symnode orig = lookup_in_symboltable(symtab, parent->left_child->value.string, Function,&level);
		printf("function %s, with node type %d and data type %d", orig->name, orig->node_type, orig->data_type);
		ast_node params = orig->parameters;
		params = params->left_child;
		ast_node args = parent->left_child->right_sibling->left_child;
		
		printf("about to loopncheck\n");
		while(params != NULL && args != NULL ){
			if(typecheck(params, symtab) != typecheck(args, symtab)){
				fprintf(stderr, "Type mismatch while calling function %s\n", orig->name);
				exit(1);
			}
			params = params->right_sibling;
			args = args->right_sibling;
		}
		if (params != NULL){
			fprintf(stderr, "Insufficient arguments passed to function %s\n",orig->name);
			exit(1);
		}
		if (args != NULL){
			fprintf(stderr, "Too many arguments passed to function %s\n",orig->name);
			exit(1);
		}
		return orig->data_type;
	}
}

void traverse(ast_node parent, symboltable symtab){

	printf("begin traversal at node %s\n",  token_table[parent->node_type].token);
	
	if (parent->node_type== ROOT || parent->node_type == CMPD || parent->node_type == PARAMS){
		ast_node n = parent->left_child;

		/* a ROOT node has either var decs or func decs as its children, go through each*/
	//	ast_node n = parent->left_child;
		while (n!=NULL) {
			printf("recursing on new root child %s\n",  token_table[n->node_type].token);

			traverse(n, symtab);
			n = n->right_sibling;	
			}
		}
	
	else if (parent-> node_type == FUNCDEC){
		ast_node n = parent->left_child->right_sibling;
		symnode func_name = insert_into_symboltable(symtab, n->value.string, Function, n->type, n->line_number);
		enter_scope(symtab);
		ast_node params = parent->left_child;
		ast_node body = params->right_sibling;
		traverse (params, symtab);
		traverse(body, symtab);
		leave_scope(symtab);
	}
	
	// Let's consider the declaration cases:
	// upon seeing an INT or a DOUBLE, check the left child
	else if (parent-> node_type == INT_TYPE || parent->node_type == DOUBLE_TYPE){
		ast_node n = parent->left_child;
		int type;
		while (n!=NULL) {
			printf("recurse on  %s\n",  token_table[n->node_type].token);
			ast_node c=n->left_child;
			switch(n->node_type){
					// If an ID is found, the ast node has all the information needed to populate the symtable
				case IDENT:
					insert_into_symboltable(symtab, n->value.string, Var, n->type, n->line_number);
					printf("var name: %s, type: %d\n", n->value.string, n->type );

					break;
	
					// Add the left child of the assignment operation, check the right sibling for type consistency
				case OP_ASSIGN:
					insert_into_symboltable(symtab, c->value.string, Var, c->type,  n->line_number);
					scopecheck(n->left_child->right_sibling, symtab);
					typecheck(n, symtab);
					printf("var name: %s, type: %d\n", c->value.string , c->type);
					break;
	
					// Add the left child of the assignment operation, check the right sibling to make sure it's an int.

				case ARRAY:
					insert_into_symboltable(symtab, c->value.string,Array, c->type,  c->line_number);
					scopecheck(n->left_child->right_sibling, symtab);
					typecheck(n, symtab);
					printf("var name: %s, type: %d\n", c->value.string , c->type);

					break;
			}
			n = n->right_sibling;	
		}
	}
	
	else if (parent->node_type == IF_STMT || parent->node_type == WHILE_STMT){
			scopecheck(parent->left_child, symtab);
			typecheck(parent->left_child, symtab);
			traverse(parent->left_child->right_sibling, symtab);	
		}
	
	else if (parent->node_type == IF_ELSE_STMT){
			scopecheck(parent->left_child, symtab);
			typecheck(parent->left_child, symtab);
			traverse(parent->left_child->right_sibling, symtab);	
			traverse(parent->left_child->right_sibling->right_sibling, symtab);	
		}
		
	else if (parent->node_type == DO_WHILE_STMT){
			traverse(parent->left_child, symtab);	
			scopecheck(parent->left_child->right_sibling, symtab);
			typecheck(parent->left_child->right_sibling, symtab);
		}
	
	else if (parent->node_type == FOR_STMT){
		ast_node fheader = parent->left_child;
		int i;
		for (i = 0; i<3; i++){
			scopecheck(fheader, symtab);
			typecheck(fheader, symtab);
			fheader = fheader->right_sibling;
		}
		traverse(fheader, symtab);	
	}
	else {
		scopecheck(parent, symtab);
		typecheck(parent, symtab);	
		}	
}