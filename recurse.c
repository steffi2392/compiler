int factoriel(int x){
  if (x == 0)
    return 1;
  else 
    return x * factoriel(x-1);
}

void main(){
  int test= 3;
  print factoriel(test);
   return;
}
