double ar1[3];
double ar2[3];

void swap(double a[], double b[], int x){
  double temp;
  temp = a[x];
  a[x] = b[x];
  b[x] = temp;
  return;
}

int main(){
  int index = 2;
  
  /*read index;*/
  ar1[0] = 0.0;
  ar1[1] = 2.0;
  ar1[2] = 4.0;
  
  ar2[0] = 1.0;
  ar2[1] = 3.0;
  ar2[2] = 5.0;


  swap(ar1, ar2, index);
  print ar1[index];
  print ar2[index];

  return 0;
}
