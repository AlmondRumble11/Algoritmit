#include<stdio.h>
#include<string.h>
#define INF 999
#define KOKO  11
void lyhinpolku(int alkuperainen[][KOKO]){
	int matriisi[KOKO][KOKO];

	//kopiodaan matriisi
	for (int i=0;i<KOKO;i++){
		for(int j=0;j<KOKO;j++){
			matriisi[i][j] = alkuperainen[i][j];
		}
	}
	//k kertoo mikä kierros on eli se on välisolmu eli siis minkä kautta polku kulkee
	for(int k=0;k<KOKO;k++){
	
		//generoi martriisin jota päivitetään joak kierroksella
		for(int i=0;i<KOKO;i++){
			for(int j=0;j<KOKO;j++){
				/*verrataan suoraa puolkua välisolmujen kautta löydettyyn pituuteen eli kyseinen solmu on kahden muun solmun välissä 
				ensin verrataan matsiisin ensimmäiseen solmuun, sitten toiseen jne.
				
				*/
				if(matriisi[i][j] > matriisi[i][k] + matriisi[k][j]){
					matriisi[i][j] = matriisi[i][k] + matriisi[k][j];
				
				}
				
			}
		}
		for (int i = 0; i < KOKO; i++) {
	    		for (int j = 0; j < KOKO; j++) {
			      	if (matriisi[i][j] == INF){
					printf("%4s", "INF");
				}else{
					printf("%4d", matriisi[i][j]);
				}
			    }
			printf("\n");
  		}	
  		printf("\n");
	}
	//tulostetaan matriisi
	printf("Valmis matriisi\n");
	for (int i = 0; i < KOKO; i++) {
    		for (int j = 0; j < KOKO; j++) {
		      	if (matriisi[i][j] == INF){
				printf("%4s", "INF");
			}else{
				printf("%4d", matriisi[i][j]);
			}
		    }
		printf("\n");
  	}
	printf("\n");
}



int main(void){
	int matriisi[KOKO][KOKO]={
	{INF,3,INF,INF,5,INF,INF,4,INF,INF,INF},
	{3,INF,2,INF,5,7,INF,INF,INF,INF,INF},
	{INF,2,INF,3,INF,2,6,INF,INF,INF,INF},
	{INF,INF,3,INF,INF,INF,7,INF,INF,INF,2},
	{5,5,INF,INF,INF,4,INF,7,INF,INF,INF},
	{INF,7,2,INF,4,INF,4,5,4,3,INF},
	{INF,INF,6,7,INF,4,INF,INF,INF,4,6},
	{4,INF,INF,INF,7,5,INF,INF,2,INF,INF},
	{INF,INF,INF,INF,INF,4,INF,2,INF,6,INF},
	{INF,INF,INF,INF,INF,3,4,INF,6,INF,5},
	{INF,INF,INF,2,INF,INF,6,INF,INF,5,INF}
	};
	
	
	
	//strcpy(tulos,lyhinpolku(matriisi));
	printf("Alkuperäinen matriisi\n");
	for (int i = 0; i < KOKO; i++) {
    		for (int j = 0; j < KOKO; j++) {
		      	if (matriisi[i][j] == INF){
				printf("%4s", "INF");
			}else{
				printf("%4d", matriisi[i][j]);
			}
		    }
		printf("\n");
  	}
  	printf("\n");
  	
  	
	lyhinpolku(matriisi);

}
/*





procedure lyhimmät-polut(d: array [1..n;1..n] of real) returns array of real
   for i := 1 to n do
      for j := 1 to n do
         m(i,j) := d(i,j)
   for k := 1 to n do
      for i := 1 to n do
         for j := 1 to n do
            m(i,j) := min{m(i,j), m(i,k)+m(k,j)}
   return m













*/
