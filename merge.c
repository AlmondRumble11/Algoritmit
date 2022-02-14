#include<stdio.h>
void yhdista(int lista[], int alku, int keskikohta, int loppu){ 
	int oikeapuoliKoko= loppu-keskikohta;	//oikeanpuolen koko on loippu - keskikohta
	int vasenpuoliKoko= keskikohta-alku+1; // vasemmanpuolen koko on keskikohta+1-alku
	int vasenpuoli[vasenpuoliKoko];
	int oikeapuoli[oikeapuoliKoko];
	
	
	//tallennetaan oikeanpuolen taulukon arvot taulukoon jossa on vain oikealla pouollla olevia numeorita
	int i;
	for(i = 0;i<oikeapuoliKoko;i++){
	
		oikeapuoli[i] = lista[keskikohta+i+1];
	
	}

	//tallennetaan vasemmanpuolen  numerot taulukoon
	int j;
	for(j=0;j<vasenpuoliKoko;j++){
	
		vasenpuoli[j]=lista[alku+j];
	}
	
	int o=0; // muistaa oikean puolen lukujen indeksin
	int v=0;//vasemman puolen lukujen indeksi
	int a=alku;  //lopputulkos taulukon indeksi
	printf("OIkeapuoli\n"); 
	for (int j = 0; j < oikeapuoliKoko; j++){
        		printf("%d ",oikeapuoli[j]);
        	} 
    		printf("\n"); 
	printf("Vasenpuoli\n");
	for (int j = 0; j < vasenpuoliKoko; j++){
        		printf("%d ",vasenpuoli[j]);
        	} 
    		printf("\n"); 
	//yhdistetään oikea ja vasen puoli siten yhdeksi siten että vasemalle jää pienin luku
   	while ((v <vasenpuoliKoko) && (o < oikeapuoliKoko)){ 
    
		if (vasenpuoli[v] <= oikeapuoli[o]){ 
		    lista[a] = vasenpuoli[v]; 
		    v++; 
		}else{ 
		    lista[a] = oikeapuoli[o]; 
		    o++; 
		} 
        	a++; 
    	}
    	//laitetaan lopu luvut eripuolilta taulukkoon
	for(;o<oikeapuoliKoko;o++){
		lista[a]=oikeapuoli[o];
		a++;
	
	}
		
	for(;v<vasenpuoliKoko;v++){
		lista[a]=vasenpuoli[v];
		a++;
	
	}
		
		printf("Koko lista\n");
  		for (int j = 0; j < 8; j++){
        		printf("%d ", lista[j]);
        	} 
    		printf("\n");
    		printf("\n");  

  
} 
  

void lajittelu(int lista[], int alku, int loppu){ 
    	
    	if(alku < loppu){
    	
		int keskikohta = (alku+loppu)/2;//etsittään keskikohta
		lajittelu(lista, alku, keskikohta); //ekan puolen lajittelu
	
		lajittelu(lista, keskikohta + 1, loppu);//tokan puolenlajittelu
		yhdista(lista, alku, keskikohta, loppu); //yhdistetään taulukot
		
    	}
} 
  

int main(void){
	int koko = 8;
	
	int alkukohta = 0;
	int loppukohta = koko -1;
    	int lista[] = { 20, 16, 24, 8, 16, 28, 6 ,3}; 
 	for (int i = 0; i < koko; i++){
        	printf("%d ", lista[i]);
        } 
    	printf("\n"); 
  
    	lajittelu(lista, alkukohta, loppukohta); 
   
   	for (int j = 0; j < koko; j++){
        	printf("%d ", lista[j]);
        } 
    	printf("\n"); 
    	return 0; 
} 
