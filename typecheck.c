#import <stdio.h> 
#import "ast.h"
#import "symtab.h"

static void process_var(ast_node node, symboltable symtab); 
static void process_func(ast_node node, symboltable symtab); 
static void buildSymTab(ast_node parent, symboltable symtab); 
static void typecheck(ast_node node, symboltable symtab);
static void error(char* message); 

// General graph traversal function
void traverse(ast_node parent, symboltable symtab){
  int in_compound = 0; 
  
  if (parent != NULL){

    // NOTE: this is what you would do to change the scope. 
    // I'm not sure where we would do it though
    /*if (parent->node_type == CMPD){
      enter_scope(symtab);
      in_compound = 1;
      }*/

    buildSymTab(parent, symtab); // preProcessing

    ast_node curr = parent->left_child; 
    while (curr != NULL){
      curr->parent = parent; 
      traverse(curr, symtab);  
      curr = curr->right_sibling; 
    }
    typecheck(parent, symtab); // postProcessing

    // NOTE: and this is how we'd pop a scope 
    /*if (in_compound){
      leave_scope(symtab);
      in_compound = 0; 
      }*/
  }
}

// typechecking
static void typecheck(ast_node node, symboltable symtab){
  int level; 
  
  printf("typing node %d\n", node->node_type); 

  if (node->node_type == IDENT){
    symnode x = (lookup_in_symboltable(symtab, node->value.string, node->isVar, &level));
    if (x != NULL){
      // if it's an array, when used its value is just int or double
      if (strcmp(x->type, "int_array") == 0 && node->right_sibling != NULL){
	node->type = "int"; 
      }
      else if (strcmp(x->type, "double_array") == 0 && node->right_sibling != NULL){
	node->type = "double"; 
      }
      else
	node->type = x->type; 
      
      printf("lookup succeeded in typecheck, found %s of type %s\n", node->value.string, x->type); 
    }
    else
      printf("lookup failed in typecheck, did not find %s. isVar = %d\n", node->value.string, node->isVar); 
  }

  // assigns node to its child's type (or handles lits and returns appropriately)
  else if (node->node_type == INT_TYPE || node->node_type == DOUBLE_TYPE || node->node_type == ARRAY || node->node_type == FUNCDEC || node->node_type == RETURN_STMT
	   || node->node_type == INT_LITERAL || node->node_type == DOUBLE_LITERAL || node->node_type == CALL){
    if (node->left_child != NULL){
      printf("set type of a %d node to %s\n", node->node_type, node->left_child->type); 
      node->type = node->left_child->type;
    } 
    else{
      if (node->node_type == INT_TYPE || node->node_type == INT_LITERAL)
	node->type = "int"; 
      else if (node->node_type == DOUBLE_TYPE || node->node_type == DOUBLE_LITERAL)
	node->type = "double"; 
      else if (node->node_type == RETURN_STMT)
	node->type = "void"; 
    }
  }
  
  else if (node->node_type == OP_ASSIGN){
    printf("checking assignment\n"); 
    // if they're not the same, error!
    if (node->left_child->type != NULL && node->left_child->right_sibling->type != NULL){
      if (strcmp(node->left_child->type, node->left_child->right_sibling->type)){
	char message[200];
	snprintf(message, sizeof(message), "Trying to assign type %s to %s\n", node->left_child->right_sibling->type, node->left_child->type); 
	error(message);
      }
      else
	printf("successful assignment of type %s to %s\n", node->left_child->type, node->left_child->right_sibling->type); 
    }
  }
}

// Puts stuff into the symbol table
static void buildSymTab(ast_node curr, symboltable symtab){
  char* name, type; 
  int isVar; 
  int in_compound = 0; 

      // if you encounter a type, put that variable in the symbol table
      if ((curr->node_type == INT_TYPE || curr->node_type == DOUBLE_TYPE) && curr->left_child != NULL){
      	process_var(curr, symtab); 
      }
      // if you encounter a function, put it into symbol table
      else if (curr->node_type == FUNCDEC){
	process_func(curr, symtab); 
      }
      // a bit of a hack, makes sure that array useage knows it's a variable
      else if (curr->node_type == ARRAY){
	curr->left_child->isVar = 1; 
      }
      else if (curr->node_type == CALL){
	curr->left_child->isVar = 0; 
      }
      
}
  
// puts a variable into the symbol table with the correct type
static void process_var(ast_node node, symboltable symtab){
  char *name = NULL; 
  char *type = NULL; 

  // testing if it's an array declaration
  if ((node->left_child != NULL) && (node->left_child->left_child != NULL)){
        if (node->left_child->node_type == ARRAY){
      name = node->left_child->left_child->value.string;
      if (node->node_type == INT_TYPE)
	type = "int_array";
      else if(node->node_type == DOUBLE_TYPE)
	type = "double_array";

      node->left_child->left_child->isVar = 1;
      printf("setting isVar of %s to 1\n", name); 
    }
  }

  // is it an assignment? 
  if (node->left_child->node_type == OP_ASSIGN){
    if (node->left_child->left_child->node_type == IDENT){
      if (node->node_type == INT_TYPE)
	type = "int";
      else if (node->node_type == DOUBLE_TYPE)
	type = "double";

      name = node->left_child->left_child->value.string; 
      node->left_child->left_child->isVar = 1;
      printf("setting isVar of %s to 1\n", name); 
    }
  }

  // if it's not, then the child is an ID
  else if (node->left_child->node_type == IDENT){ 
    name = node->left_child->value.string;
    node->left_child->isVar = 1; 
    printf("setting isVar of %s to 1\n", name); 
    if (node->node_type == INT_TYPE)
      type = "int";
    else if (node->node_type == DOUBLE_TYPE)
      type = "double";
  }
    
  if (name && type){

    symnode x = insert_into_symboltable(symtab, name, 1, type);
    printf("var name: %s, type: %s\n", name, type);
    if (x != NULL)
      printf("variable inserted successfully.\n"); 
    else
      printf("variable not inserted.\n"); 
  }
}


// puts a function into the symbol table
static void process_func(ast_node node, symboltable symtab){
  char* name; 
  char* type; 
  
  if (node->left_child != NULL && node->left_child->right_sibling != NULL){
    ast_node func_type_node = node->left_child; 
    ast_node func_id = func_type_node->right_sibling; 

    name = func_id->value.string;
    if (func_type_node->node_type == INT_TYPE)
      type = "int"; 
    else if (func_type_node->node_type == DOUBLE_TYPE)
      type = "double"; 

    if (name != NULL && type != NULL){
      func_id->isVar = 0;
      printf("setting isVar of %s to 0\n", name); 
      insert_into_symboltable(symtab, name, 0, type);  
      printf("func name: %s, type: %s\n", name, type);
    }
  }
}

static void error(char* message){
  printf("Found an error: %s\n", message); 
}
