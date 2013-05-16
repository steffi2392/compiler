
int a;
double b[4];

int f(){
  b[0] = 5.2;
  b[1] = a; 
  return b[0];
}

int main(){
  double x = f();
}
