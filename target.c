 /* target.c
 * Makes target code from quads
 */ 

#import <stdlib.h>
#import <stdio.h>
#import <string.h>
#import "intermediate.h"
#import "symtab.h"

#define MAX_BUFFER 200 

/* prototypes */
static void process_global(quad q); 
static void process_assignment(quad q); 
static quad process_funcdec(quad q); 
static void process_enter(quad q); 
static void process_leave(quad q); 
static quad process_pardec(quad q, int rtrn_val_size);
static void process_return(quad q, int rtrn_val_size); 
static void process_add(quad q); 
static void process_exitsub(quad q, int rtrn_type_size); 
static void process_push(quad q); 
static void process_call(quad q); 
static void process_get_rtrn(quad q, int offset); 
static void write(char * string); 
static void ro_instruction(char *opcode, int r, int s, int t); 
static void rm_instruction(char *opcode, int r, int d, int s); 
static void directive(char *type, int loc, int value); 
static void fill(int loc, int count, int val); 
static char * process_temp(char * init_temp); 
static void increment_reg(int reg, int offset); 
static int stoi(char *string); 

/* globals */ 
int memory_pointer = 0; 
int program_counter = 0; 
int main_loc; 
symboltable symtab; 

/* Makes target code from a list of quads */  
void generate_target(quad_list code){
  //printf("LDC 4, 4(0)\n"); // initial mem[] location
  quad curr; 
  symtab = create_symboltable(); 
 
  // process each quad
  curr = code->first; 
  if (curr == NULL){
    printf("first quad is null\n"); 
    return; 
  }
  
  do {
    switch (curr->opcode){
    case vardec:
      process_global(curr);
      curr = curr->next; 
      break; 
    case func_dec: 
      process_funcdec(curr); 
      break; 
    case halt: 
      ro_instruction("HALT", 0, 0, 0); 
      break; 
    } }while (curr != code->first); 
  
}

// this could probably be recycled to handle normal vardecs as well: just pass in the offset
// for vardecs: initial offset is 0!
// Check level to figure out if you're offsetting from R4 or R5 
static void process_global(quad q){
  int type; 
  if (strcmp(q->address1, "int") == 0){
    type = 0; 
  }
  else{ 
    type = 1; 
  }

  // Not an array
  if (q->address3 == NULL){
    symnode node = insert_into_symboltable(symtab, q->address2, type, 1, 0);
    node->offset = memory_pointer;
    //    node->

      if (type == 0){
	directive(".INT", memory_pointer, 0); 
	rm_instruction("LDC", 0, 4, 0); 
	ro_instruction("ADD", 6, 6, 0); 
     	memory_pointer += 4; 
      }
      else{
	directive(".INT", memory_pointer, 0); 
	rm_instruction("LDC", 0, 8, 0); 
	ro_instruction("ADD", 6, 6, 0); 
	memory_pointer += 8; 
      }
  }
  // dealing with an array
  /*  else{
    // if size is just a quad, it's easy! 
    int level, size; 
    symtab node = lookup_in_symboltable(symtab, q-address3, 1, &level); 
    if (node != NULL){
      size = 
	print("");
    }
    else {// it's a number
      size = 
	printf("LDC 0, %d(O)\n", size); 
    }

    // do the loop thing
    }*/ 
}

// INCOMPLETE FINISH MEEEEEE
// ADD $t1 to symbol table - not just t1!!!
static void process_assignment(quad q){
  char * target = q->address1; 
  int level, val_lev, reg; 
  symnode node = lookup_in_symboltable(symtab, target, Var, &level); 
  if (node != NULL){
    symnode value = lookup_in_symboltable(symtab, q->address2, 1, &val_lev); 
    if (value != NULL){
      reg = (val_lev == 0) ? 4 : 5; 
      rm_instruction("LD", 0, value->offset, reg); 
    }
    else {
      int constant = stoi(q->address2);
      rm_instruction("LDC", 0, constant, 0); 
    }

    int reg = (level == 0) ? 4 : 5; // either global offset or FP 
    rm_instruction("ST", 0, node->offset, reg); 
  }
  // Storing into a temp var THIS IS WRONG FIX ME
  else {
    symnode value_node = lookup_in_symboltable(symtab, q->address2, Var, &level); 
    char * temp_var = process_temp(target); 
    node = insert_into_symboltable(symtab, temp_var, Var, value_node->data_type, 0); 
    
    int offset_increment = (value_node->data_type == Int) ? 4 : 8; 
    increment_reg(6, offset_increment); 
    
    // get the value you're storing
    symnode value = lookup_in_symboltable(symtab, q->address2, Var, &val_lev); 
    if (value != NULL){
      reg = (val_lev == 0) ? 4 : 5; // what register am I taking offset of? 
      rm_instruction("LD", 0, value->offset, reg); 
    }
    else { // it's a constant
      int constant = stoi(q->address2); 
      rm_instruction("LDC", 0, constant, 0); 
    }

    rm_instruction("ST", 0, node->offset, 5); 
  }
}

/* When we hit the function declaration, R6 is pointing to the first parameter
 * NEED A WAY TO REPORT RETURN TYPE AND PUT IN SYMBOL TABLE 
 */ 
static quad process_funcdec(quad q){
  int level; 
  symnode node = insert_into_symboltable(symtab, q->address2, 0, 0, 0); 
  node->offset = program_counter; 
  
  // make space for return value
  // calculate the offset, based on what type the function returns
  //rm_instruction("LDC", 0, offset, 0); 
  //ro_instruction("ADD" 6, 6, 0); 
  increment_reg(6, node->offset); 

  // store the old R5 (FP); 
  // "increment R6 by 4" 
  increment_reg(6, 4); 
  rm_instruction("ST", 5, 0, 6); 
  
  // R5 = R6 + 4
  rm_instruction("LDC", 0, 4, 0); 
  ro_instruction("ADD", 5, 6, 0); 

  q = q->next; 
  while (q->opcode != exit_sub){
    // HUGE CASE STATEMENT
  }
  return q->next; 
}

// process enter, just enter new scope in symbol table
static void process_enter(quad q){
  enter_scope(symtab); 
}

// exit the scope
static void process_leave(quad q){
  leave_scope(symtab); 
}

/* Handle all the pardecs: (pardec, int, x, NULL)
 * Upon entry, we know that the offset of the first param should be
 * -4 - (type of RV) - 4.
 * Any future ones that the offset of the previous one minus the size 
 * of the previous one. 
 * No code generated. 
 */ 
static quad process_pardec(quad q, int rtrn_val_size){
  int offset = -8 - rtrn_val_size; 
  
  // go through all the pardecs
  for (q; q->opcode == pardec; q = q->next){
    int data_type = (strcmp(q->address1, "int") == 0) ? 0 : 1; 
    symnode node = insert_into_symboltable(symtab, q->address2, Var, data_type, 0); 
    node->offset = offset; 

    int increment = (data_type == 0) ? -4 : -8; 
    offset += increment; 
  }
  return q; 
}

// return value = -4 - return type off of R5
static void process_return(quad q, int rtrn_val_size){

  // LD O, t1's offset of R5
  int level; 
  symnode node = lookup_in_symboltable(symtab, q->address1, Var, &level); 
  rm_instruction("LD", 0, node->offset, 5); 

  // ST 0, -offset(5)
  rm_instruction("ST", 0, rtrn_val_size, 5); 
}

/* (add, t1, x, y)
 *  1. move R6 (by 4 or 8)
 *  2. set $t's offset off of R5
 */ 
static void process_add(quad q){
  // type of t1 is the type of x and y
  int level; 
  symnode node = lookup_in_symboltable(symtab, q->address2, Var, &level); 
  int offset = (node->data_type == Int) ? 4 : 8; 

  // load the constant of the offset into a register
  rm_instruction("LDC", 0, offset, 0); 

  // increment R6 by that constant
  ro_instruction("ADD", 6, 6, 0); 

  // insert temp var into symtab and set its offset
  symnode new_node = insert_into_symboltable(symtab, q->address1, Var, node->data_type, 0); 
  new_node->offset = offset; 
}

// ALWAYS PUT A SPACE FOR RETURN VALUE EVEN IF IT'S VOID
static void process_exitsub(quad q, int rtrn_type_size){

  // 1. Make R6 point right above R5
  rm_instruction("LDA", 6, -4, 5);  

  // 2. Set R5 to the contents of R6
  rm_instruction("LD", 5, 0, 6); 

  // 3. Move R6 up 1 word (subtract size of return type)
  rtrn_type_size = -1 * rtrn_type_size; 
  rm_instruction("LDC", 0, rtrn_type_size, 0); 
  ro_instruction("ADD", 6, 6, 0); 

  // 4. put the program counter back to where it should be
  rm_instruction("LD", 7, -4, 6); 

  // WE DID IT HOORAY!
}

// When we see main(), know where we are, and write in the commands to jump to main into 
// the commands we skipped earlier: LDC 7, %d(0), whatever program counter is when we find main.

// just do this one at a time
static void process_push(quad q){
  int level;
  symnode node = lookup_in_symboltable(symtab, q->address1, Var, &level); 
  int reg = (level == 0) ? 4 : 5; // local vs. global 
  int size = (node->data_type == Double) ? 8 : 4; 
  
  rm_instruction("LD", 0, node->offset, reg); // load param into R0
  rm_instruction("ST", 0, 0, 6); 
  increment_reg(6, size); // increment SP 
}

// When you get here, the params have already been pushed, R6 is pointing to the last param
// or maybe it's pointing to the spot right blow the last param? Think about this!!
// HOW DO I KNOW A FUNCTION'S TYPE AT THIS POINT? Do I have to know it? 
static void process_call(quad q){
  // 1. find the function in symbol table, find its offset
  int level; 
  symnode func_node = lookup_in_symboltable(symtab, q->address1, Function, &level);  
  int offset = func_node->offset; 

  // 2. where the program counter is now is where we eventually want to return to 
  // store value of R7 into R6 such that it goes the next command 
  rm_instruction("LDC", 0, 3, 0); // maybe this value of 3 is +/- 1?? 
  ro_instruction("ADD", 0, 0, 7); 
  rm_instruction("ST", 0, 0, 6); 

  // 3. put that into memory
  //LDC (7), ^that number(0); <-- found in step 1;
  rm_instruction("LDC", 7, offset, 0); 
}

// RETURN IS AT R6
static void process_get_rtrn(quad q, int offset){
  // 1. put whatever R6 is looking at into R0
  // LD 0, 0(6)
  rm_instruction("LD", 0, 0, 6); 

  // 2. put R6 back to where it should be: R6 = R5 + current offset
  rm_instruction("LDC", 1, offset, 0); 
  ro_instruction("ADD", 6, 5, 1); 
}

// writes a string to a file
static void write(char * string){
  printf("%s", string); 
  program_counter++; 
}

static void ro_instruction(char *opcode, int r, int s, int t){
  char buffer[MAX_BUFFER]; 
  snprintf(buffer, MAX_BUFFER, "%s, %d, %d, %d\n", opcode, r, s, t); 
  write(buffer); 
}

static void rm_instruction(char *opcode, int r, int d, int s){
  char buffer[MAX_BUFFER]; 
  snprintf(buffer, MAX_BUFFER, "%s %d, %d(%d)\n", opcode, r, d, s); 
  write(buffer); 
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
  snprintf(buffer, MAX_BUFFER,"$%s", init_temp);
  return buffer; 
}

static void increment_reg(int reg, int offset){
  rm_instruction("LDC", 0, offset, 0); 
  ro_instruction("ADD", reg, reg, 0); 
}

static int stoi(char * string){
  int i; 
  sscanf(string, "%d", &i);
  return i; 
}
