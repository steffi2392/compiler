
int a;
double b[4];

int f(){
  b[0] = 5.2;
  a = -a; 
}

int main(){
  double x = f();
  int i; 
  for (i =0; i < 5; i = i+1){
    x = 1; 
  }
}
