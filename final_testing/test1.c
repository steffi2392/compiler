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
	  if (_toggle1 == 0){
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
  int glob = 3; 
  if (x == 0 || x == 1){
    return x; 
  }
  else {
    return fib(x-1) + fib(x - 2); 
  }
}

void double_math(double num1, double num2){
  double a; 
  a = num2 / 3.0; 
  print a; 
}

int glob; 

int main(){
  int x,y;
  glob = 3;
  x = 8; 
  y = 5; 
  pretty_print(x, 1);    
  print fib(y); 
  double_math(1.0, 6.0); 
}
