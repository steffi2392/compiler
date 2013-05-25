/* assembly.c
 * generates TM57 assembly code from intermediate code
 */ 

#import <stdlib.h>
#import <stdio.h>
#import <string.h>
#import "intermediate.h"

int instruction_num = 0; 
int data_loc = 0; 

static int new_instruction(){
  int num = instruction_num; 
  instruction_num++; 
  return num; 
}

/* Generates (and prints) target code from intermediate code, 
 * given in the form of a quad list.  Ooooboy, let's do this.
 */ 
void generate_target(quad_list intermediate){
  quad curr = intermediate->first; // current quad

  while (curr->opcode != funcdec){
    // process globals
    process_global(curr); 
  }

  // when you get here, you're either at main, or main doesn't exist. 
  if (strcmp(curr->address2, "main") == 0){
    
  }
  else{
    // No main function. Process functions.
    while (curr->copcode != halt){
      // process the function
    }
  }

  // halt. BOOM DONE. 
}

static void process_global(quad q){
  while (q->opcode != vardec)
}

static void process_math(quad a){
  // put a->address1 into the symbol table
}
