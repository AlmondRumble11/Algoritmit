#include<stdio.h>


int fibonacci(int luku){

	//jos luku on 0 tai 1
	if (luku == 0){
		return 0;
	}else if (luku == 1){
		return 1;
	}
	
	//taulukko jonne tallennetaan fibonanci luvut
	int fibonacci_taulukko[luku+1];
	
	//asetetaan tiedetyt fibonacci luvun arvot
	fibonacci_taulukko[0] = 0;
	fibonacci_taulukko[1] = 1;
	
	//Aloitetaan luvusta kaksi eteenpäin tallentamaan fibonnacicn lukuja taulukkoon kun fib(0) ja fib(1) on jo taulukossa. 
	//Tallennetaan lukuja taulukkoon aina halutuuun lukuun verrran
	for (int i = 2; i<=luku;i++){
		fibonacci_taulukko[i] = fibonacci_taulukko[i-1] + fibonacci_taulukko[i-2];
	}
	
	for (int j = 0;j<=luku;j++){
		printf("Fib luvulle %d on %d\n",j,fibonacci_taulukko[j]);
	
	}
	return fibonacci_taulukko[luku];
	
	
}



int main (void){
	int luku = 10;
	int fib;
	
	fib = fibonacci(luku);
	
	printf("\nFibonacci luvulle %d on %d\n", luku, fib);
	return 0;
}



