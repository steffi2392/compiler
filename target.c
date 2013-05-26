/* target.c
 * Makes target code from quads
 */ 

#import <stdlib.h>
#import <stdio.h>
#import <string.h>
#import "intermediate.h"

#define MAX_BUFFER 200; 

/* prototypes */
static void write(char * string); 

/* globals */ 
int memory_pointer = 0; 
int program_counter = 0; 
int main_loc; 

/* Makes target code from a list of quads */  
void generate_target(quad_list code){
  //printf("LDC 4, 4(0)\n"); // initial mem[] location
  quad curr; 

  // process each quad
  quad curr = code->first; 
  while (curr != NULL){
    switch (curr->opcode){
    case vardec:
      process_global(curr);
      curr = curr->next; 
      break; 
    case funcdec: 
      process_funcdec(curr); 
      break; 
    case halt: 
      ro_instruction("HALT", 0, 0, 0); 
      break; 
    }
  }
}

// this could probably be recycled to handle normal vardecs as well: just pass in the offset
// for vardecs: initial offset is 0!
// Check level to figure out if you're offsetting from R4 or R5 
static void process_global(quad q){
  int type; 
  if (strcmp(q->address1, "int") == 0){
    type = 0; 
  }
  else 
    type = 1; 

  // Not an array
  if (q->address3 == NULL){
    symtab node = insert_into_symboltable(symtab, q->address2, type, 1, 0);
    node->offset = memory_pointer;
    node->

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

// ADD $t1 to symbol table - not just t1!!!
static void process_assignment(quad q){
  char * target = q->address1; 
  char buffer[MAX_LENGTH]; 
  int level, val_lev, reg; 
  symnode node = lookup_in_symboltable(symtab, target, 1, level); 
  if (node != NULL){
    symnode value = lookup_in_symboltable(symtab, q->address2, 1, val_lev); 
    if (value != NULL){
      reg = (val_lev == 0) ? 4 : 5; 
      rm_instruction("LD", 0, value->offset, reg); 
    }
    else {
      int constant = stoi(value);
      rm_instruction("LDC", 0, constant, 0); 
    }

    int reg = (level == 0) ? 4 : 5; // either global offset or FP 
    rm_instruction("ST", node->offset, reg); 
  }
}

/* When we hit the function declaration, R6 is pointing to the first parameter 
 */ 
static void process_funcdec(quad q){
  int level; 
  symtab->node = insert_into_symboltable(symtab, q->address2, 0, &level); 
  node->offset = program_counter; 
  
  // make space for return value
  // calculate the offset, based on what type the function returns
  //rm_instruction("LDC", 0, offset, 0); 
  //ro_instruction("ADD" 6, 6, 0); 
  increment_reg(6, offset); 

  // store the old R5 (FP); 
  // "increment R6 by 4" 
  increment_reg(6, 4); 
  rm_instruction("ST", 5, 0, 6); 
  
  // R5 = R6 + 4
  rm_instruction("LDC", 0, 4, 0); 
  ro_instruction("ADD", 5, 6, 0); 

  q = q->next; 
  while (q != NULL){
    // HUGE CASE STATEMENT
  }
}

// process enter, just enter new scope in symbol table
static void process_enter(quad q){
  enter_scope(symboltable symtab); 
}

// exit the scope
static void process_leave(quad q){
  leave_scope(symboltable symtab); 
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
  char buffer[MAX_BUFFER]; 

  // type of t1 is the type of x and y
  int level; 
  symnode node = lookup_in_symboltable(symtab, q->address2, Var, &level); 
  int offset = (node->data_type == Int) ? 4 : 8; 

  // load the constant of the offset into a register
  snprintf(buffer, MAX_BUFFER, "LDC 0, %d(0)\n", offset);
  write(buffer); 

  // increment R6 by that constant
  snprintf(buffer, MAX_BUFFER, "ADD 6, 6, 0\n"); 
  write(buffer); 

  // insert temp var into symtab and set its offset
  symnode new_node = insert_into_symboltable(symtab, q->address1, Var, node->data_type, 0); 
  new_node->offset = offset; 
}

// ALWAYS PUT A SPACE FOR RETURN VALUE EVEN IF IT'S VOID
static void process_exitsub(quad q, int rtrn_type_size){
  char buffer[MAX_BUFFER]; 

  // 1. Make R6 point right above R5
  write("LDA 6, -4(5)\n");  

  // 2. Set R5 to the contents of R6
  write("LD 5, 0(6)\n");  

  // 3. Move R6 up 1 word (subtract size of return type)
  rtrn_type_size = -1 * rtrn_type_size; 
  snprintf(buffer, MAX_BUFFER, "LDC 0, %d(0)\n", rtrn_type_size); 
  write(buffer); 
  write("ADD 6, 6, 0\n"); 

  // 4. put the program counter back to where it should be
  write("LD 7, -4(6)\n"); 

  // WE DID IT HOORAY!
}

// When we see main(), know where we are, and write in the commands to jump to main into 
// the commands we skipped earlier: LDC 7, %d(0), whatever program counter is when we find main.

// just do this one at a time
static void process_push(quad q){
  
}

// When you get here, the params have already been pushed, R6 is pointing to the last param
static void process_call(quad q){
  // 1. find the function in symbol table, find its offset

  // 2. where the program counter is now is where we eventually want to return to 
  // store value of R7 into R6 such that it goes the next command 
  LDC R0, 3 // but maybe this value of 3 is wrong, off by 1?
    ADD R0, 0, 7
    ST 0, 0(6)

  // 3. put that into memory
    LDC (7), ^that number(0); <-- found in step 1;
}

// RETURN IS AT R6
static void process_get_rtrn(quad q){
  // 1. put whatever R6 is looking at into R0
  // LD 0, 0(6)

  // 2. put R6 back to where it should be: R6 = R5 + current offset
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
