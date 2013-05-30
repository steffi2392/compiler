void pretty_print(int x, int y){
  int _toggle1 = 0;
  
  if ( y > x || y == 0) {
    print "y must be less than x and must not equal zero";
  }
  else{
    while (y < x){
      int i; 
      for (i = 0; i < y; ++i){
	int j; 
	for (j = i; j >= 0; --j){
	  if (toggle == 0){
	    print "*"; 
	    _toggle1 = 1; 
	  }
	  else {
	    print "#"; 
	    _toggle1 = 0; 
	  }
	}
	print " "; 
      }
      y = y+1;
    }
  }
}


int fib(int x){
  if (x == 0 || x == 1){
    return x; 
  }
  else {
    return fib(x-1) + fib(x - 2); 
  }
}

void safe_divide(double x, int y){
     if (y != 0 && (x / y == 5)){
     	print "multiple of 5."
      } 
}


int main(){
  pretty_print(8, 1); 
   
  print fib(5);
  print fib(6); 
  print " "; 

  safe_divide(5.0, 0); 
}
