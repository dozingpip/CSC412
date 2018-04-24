#include <stdio.h>
#include <stdlib.h>

void fib(int f1, int f2, int n){
printf("%d terms of the Fibonacci series with F1=%d and F2=%d:\nF1=%d ", n, f1, f2, f1);
int last = f1;
int current = f2;
for(int i = 1; i< n; i++){
printf("F%d=%d ", n, current);
int temp = current;
current = last + current;
last = temp;
}
printf("\n");
}

int main(int argc, const char* argv[]){
fib(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));

return 0;
}
