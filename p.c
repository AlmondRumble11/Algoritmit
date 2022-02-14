#include<stdio.h>

int main (void){

	int a[7] = {0,1,2,3,4,5,4};
 
 	int lkm=0;
 	for (int i = 0; i < 7; i++){
       	for (int j = i + 1; j < 7; j++){
           		if (a[i] == a[j]){
               		printf("%d ja %d ovat samat\n",a[i],a[j]);
           		}
           		lkm++;
       	}
	}
	printf("%d",lkm);
	return 0;
}
