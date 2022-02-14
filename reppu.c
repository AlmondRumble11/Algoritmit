#include<stdio.h>
#define KOKO 1000
#define LKOKO 10

int max(int tavarat[], int n){
	int maks=-1;
	for(int i= 0;i<n;i++){
		if(maks<tavarat[i]){
			maks=tavarat[i];
		
		}
	
	
	}
	return maks;



}

int main(void){

	int reput[KOKO];
	int reppu[KOKO];
	int tavarat[LKOKO] = {1,4,2,9,7,6,5,4,3,8};
	int reppuIndeksi = 0;
	int rKoko = 10;
	int maks=0;
	int n=LKOKO;
	
	for(int i=0;i< LKOKO;i++){
	
		maks = max(tavarat,n);
		rKoko = rKoko - maks;
		if(rKoko==0){
			reput[reppuIndeksi] = reppu;
			reppu = {0};
			reppuIndeksi++;
			
		
		}
		
	
	}	
	 
	return 0;








}
