#include <stdio.h> 
int fib(int luku) 
{ 
    if (luku <= 1) 
        return luku; 
    return fib(luku- 1) + fib(luku - 2); 
} 
  
int main() 
{ 
    int fib_luku = 40; 
    printf("%d\n", fib(fib_luku)); 
    return 0; 
}

