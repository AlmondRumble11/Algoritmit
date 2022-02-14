def fib(luku): 

    if (luku <= 1) :
        return luku 
    return fib(luku- 1) + fib(luku - 2) 

  
def main(): 

    fib_luku = 30
    print(fib(fib_luku))
    return 0



main()
