int ar1[3];
int ar2[3];

void swap(int a[], int b[], int x){
  int temp;
  temp = a[x];
  a[x] = b[x];
  b[x] = temp;
  return;
}

int main(){
  int index = 2;
  
  /*read index;*/
  ar1[0] = 0;
  ar1[1] = 2;
  ar1[2] = 4;
  
  ar2[0] = 1;
  ar2[1] = 3;
  ar2[2] = 5;


  swap(ar1, ar2, index);
  print ar1[index];
  print ar2[index];

  return 0;
}
