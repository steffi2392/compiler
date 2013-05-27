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
static void process_assignment(quad q, int *offset_from_fp); 
static quad process_funcdec(quad q); 
static void process_enter(quad q); 
static void process_leave(quad q); 
static quad process_pardec(quad q, int rtrn_val_size);
static void process_return(quad q, int rtrn_val_size); 
static void process_math(quad q, int *offset_from_fp, char * operation); 
static void process_float_math(quad q, int *offset_from_fp, char * operation); 
static void process_exitsub(quad q, int rtrn_type_size); 
static void process_push(quad q); 
static void process_call(quad q); 
static void process_get_rtrn(quad q, int offset); 
static void write(char * string); 
static void ro_instruction(char *opcode, int r, int s, int t, int override); 
static void rm_instruction(char *opcode, int r, int d, int s, int override); 
static void directive(char *type, int loc, int value); 
static void fill(int loc, int count, int val); 
static char * process_temp(char * init_temp); 
static void increment_reg(int reg, int offset); 
static int stoi(char *string); 

/* globals */ 
int memory_pointer = 0; 
int instruction_pos = 0; 
int main_loc; 
int jump_to_main; 
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

  // general setup
  
  // process all the vardecs first
  // SOME OF THESE COULD BE ASSIGNMENTS FIX ME
  while (curr->opcode == vardec){
    printf("process_global\n"); 
    process_global(curr); 
    curr = curr->next; 
  }

  // the next instruction should jump to main! record this.
  jump_to_main = instruction_pos; 
  instruction_pos++; 

  // Now process functions
  while (curr->opcode == func_dec){
    printf("process_funcdec\n"); 
    curr = process_funcdec(curr);
    if (curr->opcode = halt){
      ro_instruction("HALT", 0, 0, 0, 0); 
      return; 
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
  else{ 
    type = 1; 
  }

  // Not an array
  if (q->address3 == NULL){
    symnode node = insert_into_symboltable(symtab, q->address2, Var, type, 0);
    print_symnode(node, 0); 
    printf("inserted %s of type %d\n", q->address2, type); 
    node->offset = memory_pointer;
    //    node->

      if (type == 0){
	directive(".INT", memory_pointer, 0); 
      }
      else{
	directive(".FLOAT", memory_pointer, 0); 
      }
      rm_instruction("LDC", 0, 8, 0, 0);
      ro_instruction("ADD", 6, 6, 0, 0);
      memory_pointer += 8;
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

// Process local variable declaration
static void process_vardec(quad q, int *offset_from_fp){
  int type; 
  if (strcmp(q->address1, "int") == 0)
    type = 0;
  else
    type = 1; 

  // Not an array
  if (q->address3 == NULL){
    symnode node = insert_into_symboltable(symtab, q->address2, type, Var, 0); 
    node->offset = *offset_from_fp; 

    // store the value of 0 into memory at that slot, 
    // adjust SP and offset_from_fp appropriately.
    rm_instruction("LDC", 0, 0, 0, 0); 
    rm_instruction("ST", 0, node->offset, 5, 0); 
    if (type == 0) { // int
      rm_instruction("LDC", 0, 4, 0, 0); 
      ro_instruction("ADD", 6, 6, 0, 0); 
      *offset_from_fp += 4; 
    }
    else{ // double
      rm_instruction("LDC", 0, 8, 0, 0); 
      ro_instruction("ADD", 6, 6, 0, 0); 
      *offset_from_fp += 8; 
    } 
  }
}

// quad: (assn, arg1, arg2, null)
static void process_assignment(quad q, int *offset_from_fp){
  printf("entered process_assignment (like 162)\n");
  print_symboltable(symtab); 
 
  char * target = q->address1; 
  int level, val_lev, reg; 
  symnode node = lookup_in_symboltable(symtab, target, Var, &level); 
  if (node != NULL){ // storing into an established variable
    symnode value = lookup_in_symboltable(symtab, q->address2, 1, &val_lev);
    printf("found x\n"); 
    if (value != NULL){
      reg = (val_lev == 0) ? 4 : 5; 
      rm_instruction("LD", 0, value->offset, reg, 0); 
    }
    else {
      int constant = stoi(q->address2);
      rm_instruction("LDC", 0, constant, 0, 0); 
    }

    int reg = (level == 0) ? 4 : 5; // either global offset or FP 
    rm_instruction("ST", 0, node->offset, reg, 0); 
  }
  // Storing into a temp var 
  else {
    printf("did not find x\n"); 
    symnode value_node = lookup_in_symboltable(symtab, q->address2, Var, &level); 
    char * temp_var = process_temp(target); 
    node = insert_into_symboltable(symtab, temp_var, Var, value_node->data_type, 0); 
    node->offset = *offset_from_fp; 

    // make offset_from_fp and increment_reg point to the start of the next word
    int offset_increment = (value_node->data_type == Double) ? 8 : 4; 
    *offset_from_fp += offset_increment; 
    increment_reg(6, offset_increment); 
    
    // get the value you're storing
    if (value_node != NULL){
      reg = (val_lev == 0) ? 4 : 5; // what register am I taking offset of? 
      rm_instruction("LD", 0, value_node->offset, reg, 0); 
    }
    else { // it's a constant
      int constant = stoi(q->address2); 
      rm_instruction("LDC", 0, constant, 0, 0); 
    }

    rm_instruction("ST", 0, node->offset, 5, 0); 
  }
}

/* When we hit the function declaration, R6 is pointing to the first parameter
 * But actually, R6 probably should point to right after first param - make sure it does.
 * NEED A WAY TO REPORT RETURN TYPE AND PUT IN SYMBOL TABLE 
 */ 
static quad process_funcdec(quad q){
  int level, rtrn_type, rtrn_val_size, offset_from_fp; 

  // write the jump to main command if this is the main function
  if (strcmp(q->address2, "main") == 0){
    printf("FOUND MAIN\n"); 
    rm_instruction("LDC", 7, instruction_pos * 4, 0, jump_to_main); 
  }
  
  // figure out function return type
  if (strcmp(q->address1, "int") == 0){
    rtrn_type = 0; 
    rtrn_val_size = 4; 
  }
  else if (strcmp(q->address1, "double") == 0){
    rtrn_type = 1; 
    rtrn_val_size = 8; 
  }
  else {
    rtrn_type = 2; 
    rtrn_val_size = 0; 
  }

  symnode node = insert_into_symboltable(symtab, q->address2, Function, rtrn_type, 0); 
  node->offset = instruction_pos; 
  
  // make space for return value
  // calculate the offset, based on what type the function returns
  increment_reg(6, rtrn_val_size); 

  // store the old R5 (FP); 
  // "increment R6 by 4" 
  rm_instruction("ST", 5, 0, 6, 0); 
  increment_reg(6, 4); 

  // R5 = R6 + 4
  //rm_instruction("LDC", 0, 4, 0); 
  //ro_instruction("ADD", 5, 6, 0); 
  // ^ That's what we had before, but I think we actually want R5 = R6 (this will put
  // the frame pointer at the first empty spot in the function, which feels right).  
  rm_instruction("LDC", 0, 0, 0, 0); 
  ro_instruction("ADD", 5, 6, 0, 0); 
  offset_from_fp = 0; 

  q = q->next; 
  while (q->opcode != exit_sub){
    // HUGE CASE STATEMENT
    switch(q->opcode) {
    case vardec:
      process_vardec(q, &offset_from_fp); 
      q = q->next; 
      printf("vardec\n"); 
      break; 
    case assn: 
      process_assignment(q, &offset_from_fp); 
      q = q->next; 
      printf("assn\n"); 
      break; 
    case enter: 
      process_enter(q); 
      q = q->next; 
      printf("enter\n"); 
      break; 
    case leave: 
      process_leave(q); 
      q = q->next; 
      printf("leave\n"); 
      break; 
    case pardec: 
      process_pardec(q, rtrn_val_size); 
      q = q->next; 
      printf("pardec\n"); 
      break; 
    case rtrn: 
      // only process the return if the function is not void
      if (rtrn_type != 2){
	process_return(q, rtrn_val_size); 
	printf("rtrn\n"); 
      }
      printf("rtrn, but not value\n"); 
      q = q->next; 
      break;
    case add: 
      process_math(q, &offset_from_fp, "ADD"); 
      q = q->next;
      printf("add\n"); 
      break; 
    case sub: 
      process_math(q, &offset_from_fp, "SUB"); 
      q = q->next; 
      printf("sub\n"); 
      break;
    case mult:
      process_math(q, &offset_from_fp, "MUL"); 
      q = q->next; 
      printf("mult\n"); 
      break; 
    case divide: 
      process_math(q, &offset_from_fp, "DIV"); 
      q = q->next; 
      printf("divide\n"); 
      break;
    case mod: 
      process_math(q, &offset_from_fp, "MOD"); 
      q = q->next; 
      printf("mod\n"); 
      break; 
    case f_add: 
      process_float_math(q, &offset_from_fp, "ADDF"); 
      q = q->next; 
      printf("addf\n"); 
      break; 
    case f_sub: 
      process_float_math(q, &offset_from_fp, "SUBF"); 
      q = q->next; 
      printf("subf\n"); 
      break; 
    case f_mult: 
      process_float_math(q, &offset_from_fp, "MULF"); 
      q = q->next; 
      printf("mulf\n"); 
      break; 
    case f_divide: 
      process_float_math(q, &offset_from_fp, "DIVF"); 
      q = q->next; 
      printf("divf\n"); 
      break;
    case push: 
      process_push(q); 
      q = q->next; 
      printf("push\n"); 
      break;
    case goto_sub: 
      process_call(q); 
      q = q->next; 
      printf("goto_sub\n"); 
      break; 
    }
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
  int reg = (level == 0) ? 4 : 5; 

  if (rtrn_val_size == 8){
    rm_instruction("LDF", 0, node->offset, reg, 0); 
    rm_instruction("STF", 0, -1 * rtrn_val_size, 5, 0); 
  }
  else {
  rm_instruction("LD", 0, node->offset, reg, 0); 
  rm_instruction("ST", 0, -1 * rtrn_val_size, 5, 0); 
  }
}

/* (operation, t1, x, y)
 *  1. move R6 (by 4 or 8)
 *  2. set $t's offset off of R5
 *  3. actually perform the operation
 * This only handles ints! 
 */ 
static void process_math(quad q, int *offset_from_fp, char * operation){
  // type of t1 is the type of x and y
  int level1, level2, result_size, result_type, val; 
  symnode arg1 = lookup_in_symboltable(symtab, q->address2, Var, &level1); 
  symnode arg2 = lookup_in_symboltable(symtab, q->address3, Var, &level2);

  // If we're here, we know it's an int. 
  result_size = 4; 

  // insert temp var into symtab and set its offset
  symnode result_node = insert_into_symboltable(symtab, q->address1, Var, Int, 0); 
  result_node->offset = *offset_from_fp;
  *offset_from_fp += 4; 

  // Put the value of arg1 into R0
  if (arg1 != NULL){
    int arg1_offset_reg = (level1 == 0) ? 4 : 5; // global or local? 
    rm_instruction("LD", 0, arg1->offset, arg1_offset_reg, 0); 
  }
  else { // arg1 is a constant
    val = stoi(q->address2); 
    rm_instruction("LDC", 0, val, 0, 0); 
  }

  // Put the value of arg2 into R1
  if (arg2 != NULL){
    int arg2_offset_reg = (level2 == 0) ? 4 : 5; // global or local?
    rm_instruction("LD", 1, arg2->offset, arg2_offset_reg, 0); 
  }
  else { // arg2 is a constant
    val = stoi(q->address3); 
    rm_instruction("LDC", 1, val, 0, 0); 
  }

  // add those values into R0
  ro_instruction(operation, 0, 0, 1, 0); 

  // store that value into proper spot (at R6)
  rm_instruction("ST", 0, 0, 6, 0); 

  // increment FP
  increment_reg(6, result_size); 
}

// This one handles floats!
// There might be alignment issues!!
static void process_float_math(quad q, int *offset_from_fp, char * operation){
  int level1, level2, result_size, val; 
  symnode arg1 = lookup_in_symboltable(symtab, q->address2, Var, &level1); 
  symnode arg2 = lookup_in_symboltable(symtab, q->address3, Var, &level2); 

  // We know it's a double!
  result_size = 8; 

  // insert temp var into symtab and set its offset                                            
  symnode result_node = insert_into_symboltable(symtab, q->address1, Var, Int, 0);
  result_node->offset = *offset_from_fp;
  *offset_from_fp += 8;

  // Put the value of arg1 into R0                                                          
  if (arg1 != NULL){
    int arg1_offset_reg = (level1 == 0) ? 4 : 5; // global or local?                        
    rm_instruction("LDF", 0, arg1->offset, arg1_offset_reg, 0);
  }
  else { // arg1 is a constant                                                              
    val = stoi(q->address2);
    rm_instruction("LDFC", 0, val, 0, 0);
  }

  // Put the value of arg2 into R1                                                          
  if (arg2 != NULL){
    int arg2_offset_reg = (level2 == 0) ? 4 : 5; // global or local?                        
    rm_instruction("LDF", 1, arg2->offset, arg2_offset_reg, 0);
  }
  else { // arg2 is a constant                                                              
    val = stoi(q->address2);
    rm_instruction("LDFC", 1, val, 0, 0);
  }

  // add those values into R0                      
  ro_instruction(operation, 0, 0, 1, 0);

  // store that value into proper spot (at R6)     
  rm_instruction("STF", 0, 0, 6, 0);

  // increment FP                                  
  increment_reg(6, result_size);
}

// ALWAYS PUT A SPACE FOR RETURN VALUE EVEN IF IT'S VOID
static void process_exitsub(quad q, int rtrn_type_size){

  // 1. Make R6 point right above R5
  rm_instruction("LDA", 6, -4, 5, 0);  

  // 2. Set R5 to the contents of R6
  rm_instruction("LD", 5, 0, 6, 0); 

  // 3. Move R6 up 1 word (subtract size of return type)
  rtrn_type_size = -1 * rtrn_type_size; 
  rm_instruction("LDC", 0, rtrn_type_size, 0, 0); 
  ro_instruction("ADD", 6, 6, 0, 0); 

  // 4. put the program counter back to where it should be
  rm_instruction("LD", 7, -4, 6, 0); 

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
  
  rm_instruction("LD", 0, node->offset, reg, 0); // load param into R0
  rm_instruction("ST", 0, 0, 6, 0); 
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
  rm_instruction("LDC", 0, 3, 0, 0); // maybe this value of 3 is +/- 1?? 
  ro_instruction("ADD", 0, 0, 7, 0); 
  rm_instruction("ST", 0, 0, 6, 0); 

  // 3. put that into memory
  //LDC (7), ^that number(0); <-- found in step 1;
  rm_instruction("LDC", 7, offset, 0, 0); 
}

// RETURN IS AT R6
static void process_get_rtrn(quad q, int offset){
  // 1. put whatever R6 is looking at into R0
  // LD 0, 0(6)
  rm_instruction("LD", 0, 0, 6, 0); 

  // 2. put R6 back to where it should be: R6 = R5 + current offset
  rm_instruction("LDC", 1, offset, 0, 0); 
  ro_instruction("ADD", 6, 5, 1, 0); 
}

// writes a string to a file
static void write(char * string){
  printf("%s", string); 
}

static void ro_instruction(char *opcode, int r, int s, int t, int instruction_override){
  char buffer[MAX_BUFFER]; 
  int instruct_num = (instruction_override == 0) ? instruction_pos : instruction_override; 
  snprintf(buffer, MAX_BUFFER, "%d: %s, %d, %d, %d\n", instruct_num, opcode, r, s, t); 
  write(buffer); 

  if (instruction_override == 0)
    instruction_pos++; 
}

static void rm_instruction(char *opcode, int r, int d, int s, int instruction_override){
  char buffer[MAX_BUFFER]; 
  int instruct_num = (instruction_override == 0) ? instruction_pos : instruction_override; 
  snprintf(buffer, MAX_BUFFER, "%d: %s %d, %d(%d)\n", instruct_num, opcode, r, d, s); 
  write(buffer); 

  if (instruction_override == 0)
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
  snprintf(buffer, MAX_BUFFER,"$%s", init_temp);
  return buffer; 
}

static void increment_reg(int reg, int offset){
  rm_instruction("LDC", 0, offset, 0, 0); 
  ro_instruction("ADD", reg, reg, 0, 0); 
}

static int stoi(char * string){
  int i; 
  sscanf(string, "%d", &i);
  return i; 
}

static double stof(char * string){
  double i; 
  scanf(string, "%f", &i); 
  return i; 
}
