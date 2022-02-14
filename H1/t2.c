#include<stdio.h>
/*Jesse Mustonen, 0541805*/


//käytetään pointereita jotta saadan muutettua osoitteissa olevia numeroita eli valiarvo = b:n arvo
void swap(int *a, int *b){
	int valiarvo = *b; //hyödynnetään väliarvoa jotta uusi b:n arvo olisi ja ja a:n b(eli väliarvo)
	*b = *a;
	*a = valiarvo;
}

void lajittelu(int a[], int n ){
	int i,j;
	int temp=0;
	//käydään taulukkoa läpi yksi luku kerrallaan
	for (i=1; i<=n-1; i++){
		
		//käydään taulukkoa läpi toisin päin eli viimeisimmästä ensimmäiseen ja verrataan sen arvoa muihin lukuihin niin kauan ennen kuin se on suurus järjestyksessä pienimmästä suurimpaan
		for (j=n; j>=i+1 ;){
			j=j-1; //vähennetään j:stä yksi koska muuten indeksi on yhden liikaa, koska indeksi alkaa 0 ja numroiden määrä alkaa 1			
			
			
			//verrataan numeroita keskenään 
			if (a[j-1] > a[j]){
		
				swap(&a[j-1], &a[j]); //lähetetään numeroiden osoitteet aliohjelmaan jotta voidaan muutta niissä olevia numeroita	
				//printf("%d vaihettiin %d kanssa\n",a[j],a[j-1]);
				temp++;
			}
			temp++;
			
		
		}
	printf("#########################\n");
	printf("Taulukko välissä\n");
		//tulostaa taulukon esille jotta näkee mitä ohjelma on tehnyt vertailun aikana
		for(int p=0;p<n;p++){ 
			printf("%d\n",a[p]);
		}
	printf("#########################\n");
	
	}
	printf("%d\n",temp);

	
}


int main(void){
	int n = 10;
	//int a[10] = {94,6654,0,-34,2321,1123,1, 5, 25,-4};
	int a[10] = {10,9,8,7,6,5,4,3,2,1};
	//int a[10] = {1,2,3,4,5,6,7,8,9,10};
	//int a[100];
	
	/*printf("Anna taulukon koko: ");
	scanf("%d",&n);
	
	for(int i=0;i<n;i++){
		printf("Anna luku: ");
		scanf("%d",&a[i]);
	}*/
	printf("#########################\n");
	printf("Ennen:\n");
	for(int p=0;p<n;p++){
		printf("%d\n",a[p]);
	}
	printf("#########################\n");
	
	
	
	lajittelu(a,n);

	printf("\n");
	printf("#########################\n");
	printf("Tulokset:\n");
	for(int p=0;p<n;p++){
		printf("%d\n",a[p]);
	}
	printf("#########################\n");
	return 0;
	

}

/*
toinen tapa hoitaa tiedon siirtoa funktioiden välillä eli ei käytä pointerita ja osoitteita on palauttaa sieltä paluuarvo ja lähettää osoitteiden sijaan numerot sinne



*/
  
