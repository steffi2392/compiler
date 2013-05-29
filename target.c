/* target.c
 * Makes target code from quads
 */ 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "intermediate.h"/* target.c
 * Makes target code from quads
 */ 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "intermediate.h"
#include "symtab.h"

#define MAX_BUFFER 200 

/* prototypes */
static quad process_read(quad q, int *offset_from_fp); 
static quad process_print(quad q, int *offset_from_fp); 
static quad process_global(quad q);
static quad process_vardec(quad q, int *offset_from_fp);  
static quad process_assignment(quad q, int *offset_from_fp); 
static quad process_funcdec(quad q);
static quad process_pardec(quad q, int rtrn_val_size, int *num_params); 
static quad process_return(quad q, int rtrn_val_type); 
static quad process_math(quad q, int *offset_from_fp, char * operation); 
static quad process_float_math(quad q, int *offset_from_fp, char * operation); 
static quad process_exitsub(quad q); 
static quad process_push(quad q); 
static quad process_call(quad q); 
static quad process_get_rtrn(quad q, int *offset_from_fp, int rtrn_type); 
static quad process_whileloop(quad q, int *offset_from_fp, int rtrn_type); 
static quad process_dowhileloop(quad q, int *offset_from_fp, int rtrn_type); 
static quad process_for(quad q, int *offset_from_fp, int rtrn_type); 
static quad process_if(quad q, int *offset_from_fp, int rtrn_type); 
static quad process_ifelse(quad q, int *offset_from_fp, int rtrn_type); 
static quad process_and(quad q, int *offset_from_fp, int rtrn_type); 
static quad process_or(quad q, int *offset_from_fp, int rtrn_type); 
static quad process_not(quad q, int *offset_from_fp); 
static quad process_lkup(quad q, int *offset_from_fp); 
static quad process_array_assn(quad q); 
static void load_arg(char * name, int reg); 
static void load_float_arg(char * name, int reg); 
static quad process_logic(quad q, int *offset_from_fp); 
static void write(char * string); 
static quad process_quad(quad q, int * offset_from_fp, int rtrn_type, int *num_params); 
static void ro_instruction(char *opcode, int r, int s, int t, int override); 
static void rm_instruction(char *opcode, int r, int d, int s, int override); 
static void rm_float_instruction(char *opcode, int r, float d,int s, int instruction_override); 
static void directive(char *type, int loc, int value); 
static void fill(int loc, int count, int val); 
static char * process_temp(char * init_temp); 
static void increment_reg(int reg, int offset); 
static int stoi(char *string); 
static float stof(char * string); 

/* globals */ 
int memory_pointer = 0; 
int instruction_pos = 0; 
int main_loc; 
int jump_to_main;
int current_parnum; 
symboltable symtab; 

FILE *file; 

/* Makes target code from a list of quads */  
void generate_target(quad_list code){
  file = fopen("output.txt", "w"); 

  quad curr; 
  symtab = create_symboltable(); 
 
  // process each quad
  curr = code->first; 
  if (curr == NULL){
    printf("first quad is null\n"); 
    return; 
  }

  // general setup
  
  // process all the vardecs first
  // SOME OF THESE COULD BE ASSIGNMENTS FIX ME
  //  while (curr->opcode == vardec){
  while (curr->opcode != func_dec){ 
    printf("process_vardec\n"); 
    curr = process_global(curr); 
    //curr = curr->next; 
  }

  // the next instruction should jump to main! record this.
  jump_to_main = instruction_pos; 
  instruction_pos++; 

  // Now process functions
  while (curr->opcode == func_dec){
    printf("process_funcdec\n"); 
    curr = process_funcdec(curr);
    if (curr->opcode == halt || curr->opcode == rtrn){
      ro_instruction("HALT", 0, 0, 0, 0); 
      return; 
    }
  }
  fclose(file); 
}

// this could probably be recycled to handle normal vardecs as well: just pass in the offset
// for vardecs: initial offset is 0!
// Check level to figure out if you're offsetting from R4 or R5 
static quad process_global(quad q){
  int type; 
  
  if (q->opcode != vardec){
	int filler;
	q = process_quad(q, &memory_pointer, 0, &filler);
	return q;
}
  if (strcmp(q->address1, "int") == 0){
    type = 0; 
  }
  else{ 
    type = 1; 
  }

  // Not an array
  if (q->address3 == NULL){
    symnode node = insert_into_symboltable(symtab, q->address2, Var, type, 0);
    printf("inserted %s of type %d\n", q->address2, type); 
    node->offset = memory_pointer;

    if (type == 0){
      directive(".INT", memory_pointer, 0); 
    }
    else{
      directive(".FLOAT", memory_pointer, 0); 
    }
    rm_instruction("LDC", 0, 8, 0, -1);
    ro_instruction("ADD", 6, 6, 0, 0);
    memory_pointer += 8;
  }
  // dealing with an array
   else{
    // if size is just a quad, it's easy! 
    int level, size; 
    symnode ar = insert_into_symboltable(symtab, q->address2, Array, type, 0); 
    ar->offset = memory_pointer;
	size = stoi(q->address3);
	while (size > 0){
		if (type == 0){
			directive(".INT", memory_pointer, 0); 
		}
		else{
			directive(".FLOAT", memory_pointer, 0); 
		}
		rm_instruction("LDC", 0, 8, 0, -1);
		ro_instruction("ADD", 6, 6, 0, 0);
		memory_pointer += 8;


		size--;
	}
   }

  return q->next; 
}

// Process local variable declaration
static quad process_vardec(quad q, int *offset_from_fp){
  int type; 
  if (strcmp(q->address1, "int") == 0)
    type = 0;
  else
    type = 1; 

  // Not an array
  if (q->address3 == NULL){
    symnode node = insert_into_symboltable(symtab, q->address2, Var, type, 0); 
    printf("inserted %s of type %d\n", q->address2, type);
    node->offset = *offset_from_fp; 

    // store the value of 0 into memory at that slot, 
    // adjust SP and offset_from_fp appropriately.
    rm_instruction("LDC", 0, 0, 0, -1); 
    rm_instruction("ST", 0, node->offset, 5, -1); 

    // Don't care what type it was! Everything offset 8. 
    rm_instruction("LDC", 0, 8, 0, -1); 
    ro_instruction("ADD", 6, 6, 0, 0); 
    *offset_from_fp += 8; 
    memory_pointer += 8; 
  }
  // dealing with an array
   else{
    // if size is just a quad, it's easy! 
    int level, size; 
    symnode ar = insert_into_symboltable(symtab, q->address2, Array, type, 0); 
    ar->offset = *offset_from_fp;
	size = stoi(q->address3);
	while (size > 0){
		rm_instruction("LDC", 0, 0, 0, -1); 
		rm_instruction("ST", 0, *offset_from_fp, 5, -1); 


		rm_instruction("LDC", 0, 8, 0, -1);
		ro_instruction("ADD", 6, 6, 0, 0);
		*offset_from_fp+= 8;
		memory_pointer += 8; 

		size--;
	}
   } 
  
  return q->next; 
}

//quad: (array_lkup, temp, array, index)
static quad process_lkup(quad q, int *offset_from_fp){
	int level, ind_lev, reg;
	
	symnode array = lookup_in_symboltable(symtab, q->address2, Array, &level);
	symnode result_node = insert_into_symboltable(symtab, q->address1, Var, array->data_type, 0); 
	result_node->offset = *offset_from_fp;
	*offset_from_fp += 8; 
	symnode index = lookup_in_symboltable(symtab, q->address2, Var, &ind_lev);

    if (index != NULL){
      reg = (ind_lev == 0) ? 4 : 5; 
      rm_instruction("LD", 0, index->offset, reg, -1); 
    }
    else {
      int constant = stoi(q->address3);
      rm_instruction("LDC", 0, constant, 0, -1); 
    }
	
	rm_instruction("LDC", 1, 8, 0, -1);
	ro_instruction("MUL", 0, 1, 0, 0 );
	
	if (array->dereference == 0){
	  //Store the offset of the start of the array
	  rm_instruction("LDC", 1, array->offset, 0, -1);
	  
	  // Add up the offset of the start with the offset of the index
	  ro_instruction("ADD", 0, 0 , 1, 0);
	  
	  reg = (level == 0) ? 4 : 5; // either global offset or FP 
	  rm_instruction("LDA", 2, array->offset, reg, -1);
	  ro_instruction("ADD", 2, 2, 0, 0);
	  rm_instruction("LD", 2, 0, 2, -1);
	}
	else {
	  reg = (level == 0) ? 4 : 5; // either global offset or FP
	  rm_instruction("LD", 1, array->offset, reg, -1);
	  ro_instruction("ADD", 0,0,1,0);
	    
	  rm_instruction("LD", 2, 0, 0, -1);
	}
	
	// store that value into proper spot (at R6)
	rm_instruction("ST", 2, 0, 6, -1); 

	// increment FP
	increment_reg(6, 8); 

	return q->next; 
}

//quad: (array_assn, array, index, arg)
static quad process_array_assignment(quad q){
	
	int level, ind_lev, val_lev, reg, constant;
	symnode node = lookup_in_symboltable(symtab, q->address1, Array, &level);
	symnode index = lookup_in_symboltable(symtab, q->address2, Var, &ind_lev);
	
    if (index != NULL){
      reg = (ind_lev == 0) ? 4 : 5; 
      rm_instruction("LD", 0, index->offset, reg, -1); 
    }
    else {
		printf("index is null");

      constant = stoi(q->address2);
      rm_instruction("LDC", 0, constant, 0, -1); 
    }
	
	rm_instruction("LDC", 1, 8, 0, -1);
	ro_instruction("MUL", 0, 1, 0, 0 );
	
	symnode value = lookup_in_symboltable(symtab, q->address3, Var, &val_lev);
	
    if (value != NULL){
      reg = (val_lev == 0) ? 4 : 5; 
      rm_instruction("LD", 1, value->offset, reg, -1); 
    }
    else {
		printf(" And so is arg, address 3 is %s\n", q->address3);
      constant = stoi(q->address3);
      printf("stoid'");
	  rm_instruction("LDC", 1, constant, 0, -1); 
		printf("got here");
	}
	
    if (node->dereference == 0) {
      rm_instruction("LDC", 2, node->offset, 0, -1);
      ro_instruction("ADD", 0, 0 , 2, 0);

      reg = (level == 0) ? 4 : 5; // either global offset or FP 
      rm_instruction("LDA", 2, 0, reg, -1);
      ro_instruction("ADD", 2, 2, 0, 0);
    }
    else {
      reg = (level == 0) ? 4 : 5; // either global offset or FP
      rm_instruction("LD", 2, node->offset, reg, -1);
      ro_instruction("ADD", 0, 0, 2, 0);
      
      
    }
    rm_instruction("ST", 1, 0, 2, -1); 

	return q->next; 
}

// quad: (assn, arg1, arg2, null)
static quad process_assignment(quad q, int *offset_from_fp){
 
  char * target = q->address1; 
  int level, val_lev, reg; 
  symnode node = lookup_in_symboltable(symtab, target, Var, &level);
  
  if (node != NULL){ // storing into an established variable
    symnode value = lookup_in_symboltable(symtab, q->address2, 1, &val_lev);
    printf("LOOK AT ME %s , %d, %d \n", q->address2, value->data_type, Int);
    if (value != NULL){
      reg = (val_lev == 0) ? 4 : 5;
      if (value->data_type == Int) {
	printf("LOOK AT ME %s , %d, %d \n", q->address2, value->data_type, Int);
	rm_instruction("LD", 0, value->offset, reg, -1); 
      }
	else
	rm_instruction("LDF", 0, value->offset, reg, -1);
      
      if(value->data_type == Int && node->data_type == Double){
	ro_instruction("CVTIF", 0, 0, 0, 0);
      }
      
    }
    else {
      // what type is it? 
      if (node->data_type == Int){
	int constant = stoi(q->address2);
	rm_instruction("LDC", 0, constant, 0, -1); 
      }
      else {
	double constant = stof(q->address2); 
	rm_float_instruction("LDFC", 0, constant, 0, -1);
      } 
    }
    
    
    int reg = (level == 0) ? 4 : 5; // either global offset or FP 
    
    if (node->data_type == Int)
      rm_instruction("ST", 0, node->offset, reg, -1); 
    else
      rm_instruction("STF", 0, node->offset, reg, -1);
  }
  // Storing into a temp var 
  else {
    printf("did not find %s\n", target); 
    symnode value_node = lookup_in_symboltable(symtab, q->address2, Var, &level); 
    //char * temp_var = process_temp(target); 
    node = insert_into_symboltable(symtab, target, Var, Int, 0); 
    node->offset = *offset_from_fp; 

    // make offset_from_fp and increment_reg point to the start of the next word
    *offset_from_fp += 8; 
    increment_reg(6, 8); 
    
    // get the value you're storing
    if (value_node != NULL){
      reg = (val_lev == 0) ? 4 : 5; // what register am I taking offset of? 
      node->data_type = value_node->data_type;

      if (value_node->data_type == Int)
        rm_instruction("LD", 0, value_node->offset, reg, -1);
      else
        rm_instruction("LDF", 0, value_node->offset, reg, -1);
    }
    else { // it's a constant
      char* test = strchr(q->address1, '.');
      if (test == NULL){ // int - no decimal point
	rm_instruction("LDC", 0, stoi(q->address1),0,-1);
        rm_instruction("ST", 0, node->offset, 5, -1);
      }
      else{
	node->data_type = Double;
        rm_instruction("LDFC", 0, stof(q->address1),0,-1);
        rm_instruction("STF", 0, node->offset, 5, -1);
      }

	/*
      if (node->data_type == Int){ 
	int constant = stoi(q->address2); 
	rm_instruction("LDC", 0, constant, 0, -1);
      }
      else{
	double constant = stof(q->address2); 
	rm_float_instruction("LDFC", 0, constant, 0, -1); 
      }
	   */
    }
  }

    //rm_instruction("ST", 0, node->offset, 5, -1); 
  
  return q->next; 
}

/* When we hit the function declaration, R6 is pointing to the first parameter
 * But actually, R6 probably should point to right after first param - make sure it does.
 * NEED A WAY TO REPORT RETURN TYPE AND PUT IN SYMBOL TABLE 
 */ 
static quad process_funcdec(quad q){
  int level, rtrn_type, rtrn_val_size, offset_from_fp, num_params=0; 

  // write the jump to main command if this is the main function
  if (strcmp(q->address2, "main") == 0 ){
    printf("FOUND MAIN\n"); 
    rm_instruction("LDC", 7, instruction_pos, 0, jump_to_main); 
  }
  
  // figure out function return type
  if (strcmp(q->address1, "int") == 0){
    rtrn_type = 0; 
  }
  else if (strcmp(q->address1, "double") == 0){
    rtrn_type = 1; 
  }
  else {
    rtrn_type = 2; 
  }
 
  rtrn_val_size = 8; 

  symnode node = insert_into_symboltable(symtab, q->address2, Function, rtrn_type, 0); 
  node->offset = instruction_pos; 
  // make space for return value
  // calculate the offset, based on what type the function returns
  increment_reg(6, rtrn_val_size); 

  // store the old R5 (FP); 
  // increment R6 
  rm_instruction("ST", 5, 0, 6, -1); 
  increment_reg(6, 8); 

  // R5 = R6
  rm_instruction("LDC", 0, 0, 0, -1); 
  ro_instruction("ADD", 5, 6, 0, 0); 
  offset_from_fp = 0; 

  q = q->next; 
  while (q->opcode != exit_sub && q->opcode != halt){
    q = process_quad(q, &offset_from_fp, rtrn_type, &num_params); 
  }
  
  //  node->num_params = num_params;

  return q->next; 
}

// process enter, just enter new scope in symbol table
static quad process_enter(quad q){
  enter_scope(symtab); 
  return q->next; 
}

// exit the scope
static quad process_leave(quad q){
  leave_scope(symtab); 
  return q->next; 
}

/* Handle all the pardecs: (pardec, int, x, NULL)
 * Upon entry, we know that the offset of the first param should be
 * -4 - (type of RV) - 4.
 * Any future ones that the offset of the previous one minus the size 
 * of the previous one. 
 * No code generated. 
 */ 
static quad process_pardec(quad q, int rtrn_val_size, int *num_params){
  int offset = -32; // this is maybe wrong? probably right though.  
  int level;
  
  // go through all the pardecs
  for (q; q->opcode == pardec; q = q->next){
    int data_type = (strcmp(q->address1, "int") == 0) ? 0 : 1; 
    int type; 
    if (q->address3 == NULL)
      type = Var; 
    else
      type = Array; 
    
    symnode node = insert_into_symboltable(symtab, q->address2, type, data_type, 0); 
    node->offset = offset; 
    if (node->node_type == Array)
      node->dereference = 1;
    
    int increment = -8;  
    offset += increment; 
    *num_params = (*num_params) + 1; 
  }
  return q; 
}

// return value = -4 - return type off of R5
static quad process_return(quad q, int rtrn_val_type){

  if (q->address1 != NULL){
    // LD O, t1's offset of R5
    int level; 
    symnode node = lookup_in_symboltable(symtab, q->address1, Var, &level); 

    if (node != NULL){
      int reg = (level == 0) ? 4 : 5; 

      if (rtrn_val_type == Double){
	rm_instruction("LDF", 0, node->offset, reg, -1); 
	rm_instruction("STF", 0, -16, 5, -1); 
      }
      else {
	rm_instruction("LD", 0, node->offset, reg, -1); 
	rm_instruction("ST", 0, -16, 5, -1); 
      }
    }
    else {
      char* test = strchr(q->address1, '.');
      if (test == NULL){ // int - no decimal point
        rm_instruction("LDC", 0, stoi(q->address1),0,-1);
	rm_instruction("ST", 0, -16, 5, -1);
      }
      else{
	rm_instruction("LDFC", 0, stof(q->address1),0,-1);
        rm_instruction("STF", 0, -16, 5, -1);
      }
    }
 
 }

  // now pop everything off the stack. After this, R6 will be pointing to old R5
  rm_instruction("LDA", 6, -8, 5, -1);

  // LD 7, -24(5) to get old R7
  rm_instruction("LD", 7, -24, 5, -1); 

  return q->next; 
}

/* (operation, t1, x, y)
 *  1. move R6 (by 4 or 8)
 *  2. set $t's offset off of R5
 *  3. actually perform the operation
 * This only handles ints! 
 */ 
static quad process_math(quad q, int *offset_from_fp, char * operation){
  // type of t1 is the type of x and y
  int level1, level2, result_size, result_type, val, level; 
  symnode arg1 = lookup_in_symboltable(symtab, q->address2, Var, &level1); 
  symnode arg2 = lookup_in_symboltable(symtab, q->address3, Var, &level2);

  // If we're here, we know it's an int. 
  // But we don't care! Everything is offset 8. 
  result_size = 8; 

  // insert temp var into symtab and set its offset
  // is temp alreay in the symbol table? 
  symnode result_node = lookup_in_symboltable(symtab, q->address1, Var, &level); 

  // only add it if it's not already in there
  if (result_node == NULL){
    result_node = insert_into_symboltable(symtab, q->address1, Var, Int, 0); 
    result_node->offset = *offset_from_fp;
    *offset_from_fp += 8;
    level = 1; 
  }

  // Put the value of arg1 into R0
  if (arg1 != NULL){
    int arg1_offset_reg = (level1 == 0) ? 4 : 5; // global or local? 
    rm_instruction("LD", 0, arg1->offset, arg1_offset_reg, -1); 
  }
  else { // arg1 is a constant
    val = stoi(q->address2); 
    rm_instruction("LDC", 0, val, 0, -1); 
  }

  // Put the value of arg2 into R1
  if (arg2 != NULL){
    int arg2_offset_reg = (level2 == 0) ? 4 : 5; // global or local?
    rm_instruction("LD", 1, arg2->offset, arg2_offset_reg, -1); 
  }
  else { // arg2 is a constant
    val = stoi(q->address3); 
    rm_instruction("LDC", 1, val, 0, -1); 
  }

  // add those values into R0
  ro_instruction(operation, 0, 0, 1, 0); 

  // store that value into proper spot (at R6)
  rm_instruction("ST", 0, 0, 6, -1); 
  //int reg = (level == 0) ? 4 : 5;
  //rm_instruction("ST", 0, result_node->offset, reg, -1); 

  // increment FP
  increment_reg(6, result_size); 

  return q->next; 
}

// This one handles floats!
// There might be alignment issues!!
static quad process_float_math(quad q, int *offset_from_fp, char * operation){
  int level1, level2, result_size, val, level; 
  float float_val; 
  symnode arg1 = lookup_in_symboltable(symtab, q->address2, Var, &level1); 
  symnode arg2 = lookup_in_symboltable(symtab, q->address3, Var, &level2); 

  // We know it's a double!
  result_size = 8; 

  symnode result_node = lookup_in_symboltable(symtab, q->address1, Var, &level); 

  // insert temp var into symtab and set its offset, if it's not already there

  if (result_node == NULL){
    result_node = insert_into_symboltable(symtab, q->address1, Var, Double, 0);
    result_node->offset = *offset_from_fp;
    *offset_from_fp += 8;
  }

  // Put the value of arg1 into R0                                                          
  if (arg1 != NULL){
    int arg1_offset_reg = (level1 == 0) ? 4 : 5; // global or local?
    if (arg1->data_type == Double)                        
      rm_instruction("LDF", 0, arg1->offset, arg1_offset_reg, -1);
    else {
      rm_instruction("LD", 0, arg1->offset, arg1_offset_reg, -1);
      ro_instruction("CVTIF", 0, 0,0,0);
    }
  }
  else { // arg1 is a constant                                                              
    float_val = stof(q->address2);
    printf("NOT FLOATING YET %s\n", q->address2);
    printf("IM FLOATING %f\n", float_val);
    rm_float_instruction("LDFC", 0, float_val, 0, -1);
  }

  // Put the value of arg2 into R1                                                          
  if (arg2 != NULL){
    int arg2_offset_reg = (level2 == 0) ? 4 : 5; // global or local?
    if (arg2->data_type == Double)
      rm_instruction("LDF", 1, arg2->offset, arg2_offset_reg, -1);
    else {
      rm_instruction("LD", 0, arg2->offset, arg2_offset_reg, -1);
      ro_instruction("CVTIF", 1, 0,0,0);
    }
  }

  else { // arg2 is a literal    
    float_val = stof(q->address2);
    rm_float_instruction("LDFC", 1, float_val, 0, -1);
  }

  // add those values into R0                      
  ro_instruction(operation, 0, 0, 1, 0);

  // store that value into proper spot (at R6)     
  rm_instruction("STF", 0, 0, 6, -1);

  // increment FP                                  
  increment_reg(6, result_size);

  return q->next; 
}

// ALWAYS PUT A SPACE FOR RETURN VALUE EVEN IF IT'S VOID
static quad process_exitsub(quad q){
  return q->next; 
}

// just do this one at a time
static quad process_push(quad q){
  if (q->address1 == NULL){
    printf("null push at quad %d\n", q->num); 
  }

  int level;
  int reg;
  symnode node = lookup_in_symboltable(symtab, q->address1, Var, &level); 
  
  // if you can't find it as a Var, look for it as an Array!!
  if (node == NULL){
    node = lookup_in_symboltable(symtab, q->address1, Array, &level); 
    if (node == NULL){
      char* test = strchr(q->address1, '.');
      if (test == NULL){
	rm_instruction("LDC", 0, stoi(q->address1),0,-1);
	rm_instruction("ST", 0, 0, 6, -1);
      }
      else{
	rm_instruction("LDFC", 0, stof(q->address1),0,-1);
	rm_instruction("STF", 0, 0, 6, -1);
      }
      increment_reg(6,8);
      current_parnum +=1;
    }
    else{  

        
      reg = (level == 0) ? 4 : 5; // local vs. global 
      int offset = node->offset;
      rm_instruction("LDA", 0, node->offset, reg, -1);
      rm_instruction("ST", 0, 0, 6 ,-1);
      increment_reg(6,8);
      current_parnum +=1;
      /*printf("Ar size is %d\n", node->size);
	int off = node->offset;
	current_parnum += size;
	while (size > 0){
	rm_instruction("LD", 0, off, reg, -1); // load param into R0
	rm_instruction("ST", 0, 0, 6, -1); 
	increment_reg(6, 8); // increment SP 
	off += 8;
	size--;
	}
      */
    }
  }
  else{
    reg = (level == 0) ? 4 : 5; // local vs. global 
    rm_instruction("LD", 0, node->offset, reg, -1); // load param into R0
    rm_instruction("ST", 0, 0, 6, -1); 
    increment_reg(6, 8); // increment SP 
    current_parnum+=1;
  }
  return q->next; 
}

// When you get here, the params have already been pushed, R6 is pointing to the last param
// or maybe it's pointing to the spot right blow the last param? Think about this!!
// HOW DO I KNOW A FUNCTION'S TYPE AT THIS POINT? Do I have to know it? 
static quad process_call(quad q){
  // 1. find the function in symbol table, find its offset
  int level; 
  symnode func_node = lookup_in_symboltable(symtab, q->address1, Function, &level);  
  int offset = func_node->offset; 
  //  current_parnum = func_node->num_params;
  // 2. where the program counter is now is where we eventually want to return to 
  // store value of R7 into R6 such that it goes the next command 
  rm_instruction("LDC", 0, 4, 0, -1);  
  ro_instruction("ADD", 0, 0, 7, 0); 
  rm_instruction("ST", 0, 0, 6, -1); 
  increment_reg(6, 8); 

  // 3. put that into memory
  //LDC (7), ^that number(0); <-- found in step 1;
  rm_instruction("LDC", 7, offset, 0, -1); 

  return q->next; 
}

// Return is right above R6
static quad process_get_rtrn(quad q, int *offset_from_fp, int rtrn_type){
	
  // restore R5
  rm_instruction("LD", 5, 0, 6, -1); 

  // 1. put whatever R6 is looking at into R0
  //  Where should we store this? in some existing variable or in a temp?

  // LD 0, 0(6)
  increment_reg(6, -8); 
  

  if (rtrn_type == Double)
    rm_instruction("LDF", 0, 0, 6, -1); 
  else
    rm_instruction("LD", 0, 0, 6, -1);
   
	printf(" PARAMS# %d", current_parnum);
  // 2. put R6 back to where it should be: R6 = R5 + num_params * 8 
  rm_instruction("LDC", 1, -8 -current_parnum * 8, 0, -1); 
  ro_instruction("ADD", 6, 6, 1, 0); 
  current_parnum = 0;
  int level, reg; 
  symnode target = lookup_in_symboltable(symtab, q->address1, Var, &level); 
  
  if (target != NULL){
	if (rtrn_type == Double){
		reg = (level == 0) ? 4 : 5; 
		rm_instruction("STF", 0, target->offset, reg, -1); 
	}
	else{
		reg = (level == 0) ? 4 : 5; 
		rm_instruction("ST", 0, target->offset, reg, -1);
	}
}  
	else{
		symnode target = insert_into_symboltable(symtab, q->address1, Var, rtrn_type, 0);
		target->offset = *offset_from_fp;
		offset_from_fp+=8;
		if (rtrn_type == Double){
			rm_instruction("STF", 0, 0, 6, -1); 
		}
		else{
			rm_instruction("ST", 0, 0, 6, -1);
		}
		increment_reg(6,8);
	}
  return q->next; 
}

/* (whileloop, null, null, null)
 * (condition, target, arg1, arg2)
 * (ifFalse, target, go here, null)
 * ... 
 * (jumpTo, start of condition, null, null)
 */ 
static quad process_whileloop(quad q, int *offset_from_fp, int rtrn_type){
  int condition_loc = instruction_pos; 
  symnode result_node; 

  q = q->next; 

  // 1. process the condition while it's not ifFalse 
  while (q->opcode != ifFalse){
    int filler = 0; // won't be used, just need params
    q =  process_quad(q, offset_from_fp, rtrn_type, &filler); 
  }

  // get the target offset
  int level; 
  symnode target = lookup_in_symboltable(symtab, q->address1, Var, &level); 
  int target_offset = target->offset; 

  // The next command will be to jump ifFalse, but we don't know where 
  // to go yet!
  int ifFalse_pos = instruction_pos; 
  instruction_pos += 3; // ifFalse takes 3 operations to execute 
  
  q = q->next; 
  // 3. process the loop
  while (q->opcode != jumpTo){
    int filler; 
    q = process_quad(q, offset_from_fp, rtrn_type, &filler); 
  }

  // 4. process the jump
  rm_instruction("LDC", 0, 0, 0, -1); 
  rm_instruction("LDC", 1, condition_loc, 0, -1); 
  rm_instruction("JEQ", 0, 0, 1, -1); 

  q = q->next; 

  // 5. Go back and write ifFalse
  rm_instruction("LD", 0, target_offset, 5, ifFalse_pos);
  rm_instruction("LDC", 1, instruction_pos, 0, ifFalse_pos + 1); 
  rm_instruction("JEQ", 0, 0, 1, ifFalse_pos + 2); 

  return q->next; 
}

/* (dowhileloop, null, null, null)
 * ... body ... 
 * (end_dowhileloop, null, null, null)
 * (logic, target, arg1, arg2)
 * (ifFalse, target, go here, null)
 * (jumpTo, here, null, null)
 */ 
static quad process_dowhileloop(quad q, int *offset_from_fp, int rtrn_type){
  q = q->next; 
  int filler; 

  // 1. process loop body
  int beginning = instruction_pos; 
  while (q->opcode != end_dowhileloop){ 
   q =  process_quad(q, offset_from_fp, rtrn_type, &filler); 
  }
  q = q->next; 

  // 2. process logic
  while (q->opcode != ifFalse){
    q = process_quad(q, offset_from_fp, rtrn_type, &filler);  
  }

  // get the target offset
  int level;
  symnode target = lookup_in_symboltable(symtab, q->address1, Var, &level);
  int target_offset = target->offset;

  // 3. process ifFalse (just jump over the next instruction)
  rm_instruction("LD", 0, target_offset, 5, -1); 
  rm_instruction("LDC", 1, instruction_pos + 5, 0, -1);
  rm_instruction("JEQ", 0, 0, 1, -1); 

  q = q->next; // now it's the jumpTo
  // 4. process unconditional jump
  rm_instruction("LDC", 0, 0, 0, -1); 
  rm_instruction("LDC", 1, beginning, 0, -1); 
  rm_instruction("JEQ", 0, 0, 1, -1); 

  return q->next; 
}

/* (if, null, null, null)
 * (logic, target, arg1, arg2)
 * (ifFalse, target, go here, null)
 * ... body ... 
 * (endif)
 */ 
static quad process_if(quad q, int *offset_from_fp, int rtrn_type){
  q = q->next; 
  int filler; 

  // 1. process the logic
  while (q->opcode != ifFalse){
    q = process_quad(q, offset_from_fp, rtrn_type, &filler); 
  }

  // get the target offset                                                                  
  int level;
  symnode target = lookup_in_symboltable(symtab, q->address1, Var, &level);
  int target_offset = target->offset;

  // 2. make space for ifFalse
  int ifFalse_pos = instruction_pos; 
  instruction_pos += 3; // ifFalse takes 3 operations to execute

  q = q->next; 
  // 3. process body of if
  while(q->opcode != end_ifstmt){
    q = process_quad(q, offset_from_fp, rtrn_type, &filler); 
  }

  // 4. go back and write ifFalse
  rm_instruction("LD", 0, target_offset, 5, ifFalse_pos); 
  rm_instruction("LDC", 1, instruction_pos + 2, 0, ifFalse_pos + 1); 
  rm_instruction("JEQ", 0, 0, 1, ifFalse_pos + 2); 

  return q->next; 
}

/* (ifelse, null, null, null)
 * ... logic calculation ... 
 * (ifFalse, target, go here, null)
 * ... body ... 
 * (end_ifstmt, null, null, null)
 * (jumpTo, here, null, null, null)
 * (elsestmt, null, null, null)
 * ... body ... 
 * (end_elsestmt, null, null, null)
 */ 
static quad process_ifelse(quad q, int *offset_from_fp, int rtrn_type){
  q = q->next; 
  int filler; 

  // process logic
  while (q->opcode != ifFalse){
    q = process_quad(q, offset_from_fp, rtrn_type, &filler); 
  }

  // get the target offset     
  int level;
  symnode target = lookup_in_symboltable(symtab, q->address1, Var, &level);
  int target_offset = target->offset;

  // 2. make space for ifFalse  
  int ifFalse_pos = instruction_pos;
  instruction_pos += 3; // ifFalse takes 3 operations to execute 

  q = q->next; 
  // 3. process body of the if
  while (q->opcode != end_ifstmt){
    q = process_quad(q, offset_from_fp, rtrn_type, &filler); 
  }

  q = q->next; 
  // 4. make space for the unconditional jump
  int jump_pos = instruction_pos; 
  instruction_pos +=3;  // unconditional jump takes 3 operations

  // 5. go back and fill in ifFalse     
  rm_instruction("LD", 0, target_offset, 5, ifFalse_pos);
  rm_instruction("LDC",1, instruction_pos, 0, ifFalse_pos + 1);
  rm_instruction("JEQ",0, 0, 1, ifFalse_pos + 2);

  q = q->next; 
  q = q->next; 
  // 6. process body of else
  while (q->opcode != end_elsestmt){
    q = process_quad(q, offset_from_fp, rtrn_type, &filler); 
  }

  // 7. go back and fill unconditional jump
  rm_instruction("LDC", 0, 0, 0, jump_pos); 
  rm_instruction("LDC", 1, instruction_pos, 0, jump_pos + 1); 
  rm_instruction("JEQ", 0, 0, 1, jump_pos + 2); 

  return q->next; 
}

/* (and, null, null, null)
 * ... processing ... 
 * (ifFalse, target, go here, null) 
 * ... processing ... 
 * (jumpTo, here, null, null, null)
 * ... processing ... 
 * (end_and, null, null, null)
 */ 
static quad process_and(quad q, int *offset_from_fp, int rtrn_type){
  q = q->next; 
  int filler; 

  // 1. process left side
  while (q->opcode != ifFalse){
    q = process_quad(q, offset_from_fp, rtrn_type, &filler); 
  }

  // get the short circuit target offset
  int level; 
  symnode target = lookup_in_symboltable(symtab, q->address1, Var, &level); 
  int target_offset = target->offset; 

  // 2. make space for ifFalse
  int ifFalse_pos = instruction_pos; 
  instruction_pos += 3; 

  // 3. process right side
  q = q->next; 
  while (q->opcode != jumpTo){
    q = process_quad(q, offset_from_fp, rtrn_type, &filler); 
  }

  // 4. make space for unconditional jump
  int jump = instruction_pos; 
  instruction_pos += 3; 

  // 5. backpatch ifFalse
  rm_instruction("LD", 0, target_offset, 5, ifFalse_pos); 
  rm_instruction("LDC", 1, instruction_pos, 0, ifFalse_pos + 1); 
  rm_instruction("JEQ", 0, 0, 1, ifFalse_pos + 2); 

  q = q->next; 
  // 6. process short circuit result storing
  while (q->opcode != end_and){
    q = process_quad(q, offset_from_fp, rtrn_type, &filler); 
  }

  // 7. backpatch unconditional jumpTo
  rm_instruction("LDC", 0, 0, 0, jump); 
  rm_instruction("LDC", 1, instruction_pos, 0, jump + 1); 
  rm_instruction("JEQ", 0, 0, 1, jump + 2); 

  return q->next; 
}

/* (or, null, null, null)
 * ... processing ... 
 * (ifFalse, target, go here, null)
 * (jumpTo, here, null, null)
 * ... processing ... 
 * (jumpTo, here, null, null) 
 * ... processing ... 
 * (end_or, null, null, null)
 */ 
static quad process_or(quad q, int *offset_from_fp, int rtrn_type){
  q = q->next; 
  int filler; 

  // 1. process the left side
  while (q->opcode != ifFalse){
    q = process_quad(q, offset_from_fp, rtrn_type, &filler); 
  }

  // get the short circuit target offset                                                    
  int level;
  symnode target = lookup_in_symboltable(symtab, q->address1, Var, &level);
  int target_offset = target->offset;

  // 2. make space for ifFalse                                                              
  int ifFalse_pos = instruction_pos;
  instruction_pos += 3;
  q = q->next; 

  // 3. make space for unconditional jump #1
  int jump1 = instruction_pos; 
  instruction_pos += 3; 

  // 4. backpatch ifFalse
  rm_instruction("LD", 0, target_offset, 5, ifFalse_pos); 
  rm_instruction("LDC", 1, instruction_pos, 0, ifFalse_pos + 1); 
  rm_instruction("JEQ", 0, 0, 1, ifFalse_pos + 2); 

  q = q->next; 
  // 5. process the right side
  while (q->opcode != jumpTo){
    q = process_quad(q, offset_from_fp, rtrn_type, &filler); 
  }

  // 6. make space for unconditional jump #2
  int jump2 = instruction_pos; 
  instruction_pos += 3; 
  
  // 7. backpatch jump #1
  rm_instruction("LDC", 0, 0, 0, jump1); 
  rm_instruction("LDC", 1, instruction_pos, 0, jump1 + 1); 
  rm_instruction("JEQ", 0, 0, 1, jump1 + 2); 

  q = q->next; 
  // 8. processing: assign short circuit value
  while (q->opcode != end_or){
    q = process_quad(q, offset_from_fp, rtrn_type, &filler); 
  }

  // 9. backpatch jump #2
  rm_instruction("LDC", 0, 0, 0, jump2); 
  rm_instruction("LDC", 1, instruction_pos, 0, jump2 + 1); 
  rm_instruction("JEQ", 0, 0, 1, jump2 + 2); 

  return q->next; 
}

// (not, target, arg, null)
static quad process_not(quad q, int *offset_from_fp){
  // load arg into R0
  load_arg(q->address2, 0); 

  // put target (temp) into symbol table
  symnode target = insert_into_symboltable(symtab, q->address1, Var, Int, 0); 
  target->offset = *offset_from_fp; 
  *offset_from_fp +=8; 

  // store 1 into target
  rm_instruction("LDC", 1, 1, 0, -1); 
  rm_instruction("ST", 1, target->offset, 5, -1); 

  // if R0 is 0, you're done! jump past the next 2 instructions
  rm_instruction("LDC", 2, instruction_pos + 3, 0, -1); 
  rm_instruction("JEQ", 0,  0, 2, -1); 

  // store 0 in target
  rm_instruction("LDC", 1, 0, 0, -1); 
  rm_instruction("ST", 1, target->offset, 5, -1); 

  return q->next; 
}

/* (logic, target, arg1, arg2) */ 
static quad process_logic(quad q, int *offset_from_fp){
  int type; 
  
  // R0 = arg1 - arg2
  if (q->opcode > 12 && q->opcode < 22){
    // it's a double!
    type = Double; 
    load_float_arg(q->address2, 0); 
    load_float_arg(q->address3, 1); 
    ro_instruction("SUBF", 2, 0, 1, 0); 
  }
  else{
    // it's an int!
    type = Int; 
    load_arg(q->address2, 0); 
    load_arg(q->address3, 1); 
    ro_instruction("SUB", 2, 0, 1, 0); 
  }

  // target = 1                                                                          
  int level;
  symnode target = lookup_in_symboltable(symtab, q->address1, Var, &level);

  if (target == NULL){
    target = insert_into_symboltable(symtab, q->address1, Var, Int, 0);
    target->offset = *offset_from_fp;
    *offset_from_fp += 8;
    level = 1; 
  }

  // store true into proper spot (at R6) then increment R6
  rm_instruction("LDC", 3, 1, 0, -1); 
  rm_instruction("ST", 3, 0, 6, -1); 
  increment_reg(6, 8); 

  //  int reg = (level == 0) ? 4 : 5;
  //rm_instruction("LD", 0, target->offset, reg, -1); 

  // At this point, target = 1.  Now change it to 0 in the appropriate
  // circumstances, depending on what logical operator it is. 
  switch (q->opcode){
  case eq:
    rm_instruction("JEQ", 2, 2, 7, -1); 
    break; 
  case neq:
    rm_instruction("JNE", 2, 2, 7, -1); 
    break; 
  case lt:
    rm_instruction("JLT", 2, 2, 7, -1); 
    break; 
  case leq:
    rm_instruction("JLE", 2, 2, 7, -1); 
    break; 
  case gt:
    rm_instruction("JGT", 2, 2, 7, -1); 
    break; 
  case geq:
    rm_instruction("JGE", 2, 2, 7, -1); 
    break; 
  case f_eq:
    rm_instruction("JFEQ", 2, 2, 7, -1); 
    break; 
  case f_neq:
    rm_instruction("JFNE", 2, 2, 7, -1); 
    break; 
  case f_lt:
    rm_instruction("JFLT", 2, 2, 7, -1); 
    break; 
  case f_leq:
    rm_instruction("JFLE", 2, 2, 7, -1); 
    break; 
  case f_gt:
    rm_instruction("JFGT", 2, 2, 7, -1); 
    break;
  case f_geq:
    rm_instruction("JFGE", 2, 2, 7, -1); 
    break; 
  }  

  // Then assign target = 0 (the previous lines will jump over this if it was true. 
  rm_instruction("LDC", 0, 0, 0, -1); 
  rm_instruction("ST", 0, target->offset, 5, -1); 

  return q->next; 
}

// writes a string to a file
static void write(char * string){
  fprintf(file, "%s", string); 
}

static quad process_quad(quad q, int * offset_from_fp, int rtrn_type, int *num_params){
  switch(q->opcode){
  case read:
    printf("read\n"); 
    q = process_read(q, offset_from_fp); 
    break; 
  case print:
    printf("print\n"); 
    q = process_print(q, offset_from_fp); 
    break; 
  case vardec:
    printf("vardec\n");
    q = process_vardec(q, offset_from_fp); 
    break;
  case assn: 
    printf("assn\n"); 
    q = process_assignment(q, offset_from_fp); 
    break;
  case enter: 
    printf("enter\n"); 
    q = process_enter(q); 
    break;
  case leave: 
    printf("leave\n"); 
    q = process_leave(q); 
    break;
  case pardec: 
    printf("pardec\n"); 
    q = process_pardec(q, rtrn_type, num_params); 
    break; 
  case rtrn: 
    printf("rtrn\n"); 
    q = process_return(q, rtrn_type); 
    break; 
  case add: 
    printf("add\n"); 
    q = process_math(q, offset_from_fp, "ADD"); 
    break;
  case sub: 
    printf("sub\n"); 
    q = process_math(q, offset_from_fp, "SUB"); 
    break; 
  case mult: 
    printf("mul\n"); 
    q = process_math(q, offset_from_fp, "MUL"); 
    break; 
  case divide: 
    printf("divide\n"); 
    q = process_math(q, offset_from_fp, "DIV"); 
    break;
  case mod: 
    printf("mod\n"); 
    q = process_math(q, offset_from_fp, "MOD"); 
    break; 
  case f_add: 
    printf("addf\n"); 
    q = process_float_math(q, offset_from_fp, "ADDF"); 
    break;
  case f_sub: 
    printf("subf\n"); 
    q = process_float_math(q, offset_from_fp, "SUBF"); 
    break;
  case f_mult: 
    printf("mulf\n"); 
    q = process_float_math(q, offset_from_fp, "MULF"); 
    break;
  case f_divide: 
    printf("divf\n"); 
    q = process_float_math(q, offset_from_fp, "DIVF"); 
    break;
  case push: 
    printf("push\n"); 
    q = process_push(q); 
    break; 
  case goto_sub: 
    printf("goto_sub\n"); 
    q = process_call(q); 
    break; 
  case get_rtrn: 
    printf("get_rtrn\n"); 
    q = process_get_rtrn(q, offset_from_fp, rtrn_type); 
    break; 
  case whileloop: 
    printf("whileloop\n"); 
    q = process_whileloop(q, offset_from_fp, rtrn_type); 
    break; 
  case dowhileloop: 
    printf("dowhileloop\n"); 
    q = process_dowhileloop(q, offset_from_fp, rtrn_type); 
    break; 
  case ifstmt: 
    printf("ifstmt\n"); 
    q = process_if(q, offset_from_fp, rtrn_type); 
    break; 
  case ifelse: 
    printf("ifelse\n"); 
    q = process_ifelse(q, offset_from_fp, rtrn_type); 
    break; 
  case and: 
    printf("and\n"); 
    q = process_and(q, offset_from_fp, rtrn_type); 
    break; 
  case or: 
    printf("or\n"); 
    q = process_or(q, offset_from_fp, rtrn_type); 
    break;
  case not: 
    printf("not\n"); 
    q = process_not(q, offset_from_fp); 
    break; 
  case array_lkup: 
    printf("array_lkup\n"); 
    q = process_lkup(q, offset_from_fp); 
    break; 
  case array_assn: 
    printf("array_assn\n"); 
    q = process_array_assignment(q); 
    break; 
  case eq: 
  case neq: 
  case lt: 
  case leq: 
  case gt: 
  case geq: 
  case f_eq: 
  case f_neq: 
  case f_lt: 
  case f_leq: 
  case f_gt: 
  case f_geq: 
    printf("logic\n"); 
    q = process_logic(q, offset_from_fp); 
  }
  return q; 
}

// Puts the value of name into reg 
// Determines if it's a constant or variable
static void load_arg(char * name, int reg){
  int level; 
  symnode arg = lookup_in_symboltable(symtab, name, Var, &level);

  // If variable: 
  if (arg != NULL){
    int arg_offset_reg = (level == 0) ? 4 : 5; 
    rm_instruction("LD", reg, arg->offset, arg_offset_reg, -1); 
  }
  // If it's a constant: 
  else{
    int val = stoi(name); 
    rm_instruction("LDC", reg, val, 0, -1); 
  }
}

// Puts the value of name into register; name is a float
// Determines if it's a constant or variable
static void load_float_arg(char * name, int reg){
  int level; 
  symnode arg = lookup_in_symboltable(symtab, name, Var, &level); 

  // If variable: 
  if (arg != NULL){
    int arg_offset_reg = (level == 0) ? 4 : 5; 
    rm_instruction("LDF", reg, arg->offset, arg_offset_reg, -1); 
  }
  else {
    float val = stof(name); 
    rm_float_instruction("LDFC", reg, val, 0, -1); 
  }
}

static void ro_instruction(char *opcode, int r, int s, int t, int instruction_override){
  char buffer[MAX_BUFFER]; 
  int instruct_num = (instruction_override == 0) ? instruction_pos : instruction_override; 
  snprintf(buffer, MAX_BUFFER, "%d: %s %d, %d, %d\n", instruct_num, opcode, r, s, t); 
  write(buffer); 

  if (instruction_override == 0)
    instruction_pos++; 
}

static void rm_instruction(char *opcode, int r, int d, int s, int instruction_override){
  char buffer[MAX_BUFFER]; 
  int instruct_num = (instruction_override == -1) ? instruction_pos : instruction_override; 
  snprintf(buffer, MAX_BUFFER, "%d: %s %d, %d(%d)\n", instruct_num, opcode, r, d, s); 
  write(buffer); 

  if (instruction_override == -1)
    instruction_pos++; 
}

static void rm_float_instruction(char *opcode, int r, float d, int s, int instruction_override){
  char buffer[MAX_BUFFER]; 
  int instruct_num = (instruction_override == -1) ? instruction_pos : instruction_override; 
  snprintf(buffer, MAX_BUFFER, "%d: %s %d, %f(%d)\n", instruct_num, opcode, r, d, s); 
  write(buffer); 

  if (instruction_override == -1)
    instruction_pos++; 
}

static void directive(char *type, int loc, int value){
  char buffer[MAX_BUFFER]; 
  snprintf(buffer, MAX_BUFFER, "%s %d %d\n", type, loc, value); 
  write(buffer); 
}

static void fill(int loc, int count, int val){
  char buffer[MAX_BUFFER]; 
  snprintf(buffer, MAX_BUFFER, ".FILL %d %d %d\n", loc, count, val); 
  write(buffer); 
}

static char * process_temp(char * init_temp){
  char * buffer = malloc(MAX_BUFFER);
  snprintf(buffer, MAX_BUFFER,"%s", init_temp);
  return buffer; 
}

static void increment_reg(int reg, int offset){
  rm_instruction("LDC", 0, offset, 0, -1); 
  ro_instruction("ADD", reg, reg, 0, 0); 
}

static int stoi(char * string){
  int i; 
  sscanf(string, "%d", &i);
  return i; 
}

static float stof(char * string){
  float i; 
  sscanf(string, "%f", &i); 
  printf("string is %s, float is %f \n", string, i);
  return i; 
  //return atof(string);
}

static quad process_print(quad q, int *offset_from_fp){
  int level;
  symnode output = lookup_in_symboltable(symtab, q->address1, Var, &level);
  if (output == NULL){
    //char stringBuff[MAX_BUFFER];                                                         
    //strcat(stringBuff, q->address1);                                                     
    int len = strlen(q->address1);
    int i = len;
    printf("My len is %d", len);
    while (i > 0){
      int ascii = q->address1[len-i];
      rm_instruction("LDC", 0, ascii, 0, -1);
      rm_instruction("STB", 0, *offset_from_fp, 5, -1);
      rm_instruction("LDB", 0, *offset_from_fp, 5, -1);
      ro_instruction("OUTB", 0, 0, 0,0);
      i--;
    }
  }
  else {
    if (output->data_type == Int){
      load_arg(q->address1, 0);
      ro_instruction("OUT", 0 , 0, 0,0);
    }
    else{
      load_float_arg(q->address1, 0);
      ro_instruction("OUTF", 0,0,0,0);
    }
  }
  return q->next;
}

/*static quad process_read(quad q){
  int level, reg; 
  
  symnode target = lookup_in_symboltable(symtab, q->address1, Var, &level);
  	
  if (target->data_type == Int){
    ro_instruction("IN", 0, 0, 0, 0);
    reg = (level == 0) ? 4 : 5; 
    rm_instruction("ST", 0, target->offset, reg, -1); 
  }
  else{
    ro_instruction("INF", 0, 0, 0, 0);
    reg = (level == 0) ? 4 : 5; 
    rm_instruction("STF", 0, target->offset, reg, -1); 
  }
  return q->next;
  }*/

static quad process_read(quad q, int * offset_from_fp){
  int level, reg, level2, type;

  symnode target = lookup_in_symboltable(symtab, q->address1, Var, &level);
  if (target == NULL){
    // what type should this be? look at the next quad (array) and check the type        
    symnode array = lookup_in_symboltable(symtab, q->next->address1, Array, &level2);
    if (array != NULL)
      type = array->data_type;

    target = insert_into_symboltable(symtab, q->address1, Var, type, 0);
    target->offset = *offset_from_fp;
    *offset_from_fp += 8;
    level = 1;

    increment_reg(6, 8);
  }

  if (target->data_type == Int){
    ro_instruction("IN", 0, 0, 0, 0);
    reg = (level == 0) ? 4 : 5;
    rm_instruction("ST", 0, target->offset, reg, -1);
  }
  else{
    ro_instruction("INF", 0, 0, 0, 0);
    reg = (level == 0) ? 4 : 5;
    rm_instruction("STF", 0, target->offset, reg, -1);
  }
  return q->next;
}
