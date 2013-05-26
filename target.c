/* target.c
 * Makes target code from quads
 */ 

#import <stdlib.h>
#import <stdio.h>
#import <string.h>
#import "intermediate.h"

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
      printf("HALT 0, 0, 0\n");
      program_counter++; 
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
	printf(".INT %d 0\n", memory_pointer); 
	printf("LDC 0, 4(0)\n"); 
	print("ADD 6, 6, 0\n");
	program_counter += 3; 
	memory_pointer += 4; 
      }
      else{
	printf(".FLOAT %d 0\n", memory_pointer); 
	printf("LDC 0, 8(0)\n"); 
	printf("ADD 6, 6, 0\n");
	program_counter += 3; 
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
  int level, val_lev, reg; 
  symnode node = lookup_in_symboltable(symtab, target, 1, level); 
  if (node != NULL){
    symnode value = lookup_in_symboltable(symtab, q->address2, 1, val_lev); 
    if (value != NULL){
      reg = (val_lev == 0) ? 4 : 5; 
      printf("LD 0, %d(%d)\n", value->offset, reg); 
      program_counter++; 
    }
    else {
      int constant = stoi(value); 
      printf("LDC 0, %d(0)\n", constant);
      program_counter++; 
    }

    int reg = (level == 0) ? 4 : 5; // either global offset or FP 
    printf("ST 0, %d(%d)\n", node->offset, reg);
    program_counter++; 
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
  printf("LDC 0, %d(0)\n", offset); 
  printf("ADD 6, 6, 0\n"); 
  program_counter += 2; 

  // store the old R5 (FP); 
  // "increment R6 by 4" 
  increment_reg(6, 4); 
  printf("ST 5, 0(6)\n"); 
  program_counter++; 

  // R5 = R6 + 4
  printf("LDC 0, 4(0)\n"); 
  printf("ADD 5, 6, 0\n"); 

  q = q->next; 
  while (q != NULL){
    // HUGE CASE STATEMENT
  }
}

// process enter, just enter new scope in symbol table
static void process_enter(quad q){
}

// exit the scope
static void process_leave(quad q){
}

// handle all the pardecs
static void process_pardec(quad q){
  // (pardec int x) 
  // NO CODE! just compute an offset.  
  // going in, we know that the current offset = -4 - (type of RV) -4
  // the next one gets that minus whatever the previous one was
}

// return value = -4 - return type off of R5
static void process_return(quad q){
  // LD O, t1's offset of R5
  // ST 0, -offset(5)
}

// 1. move R6 (by 4 or 8)
// 2. set $t's offset off of R5
static void process_add(quad q){
}

// ALWAYS PUT A SPACE FOR RETURN VALUE EVEN IF IT'S VOID
static void process_exitsub(quad q){
  // 1. Make R6 point right above R5
  LDA 6, -4(5); 

  // 2. Set R5 to the contents of R6
  LD 5, 0(6); 

  // 3. Move R6 up 1 word (subtract size of return type)

  // 4. put the program counter back to where it should be
  LD 7, -4(6);

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
