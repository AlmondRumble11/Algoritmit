#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define KOKO 9
struct Node {
	int arvo;
	struct Node *pVasen;
	struct Node *pOikea;
};
typedef struct Node Solmu;

//luodaan uusi solmu
Solmu *uusiSolmu(int luku){
	Solmu *ptr;
	if((ptr= (Solmu*)malloc(sizeof(Solmu))) == NULL){
		perror("Muistin varaus epäonnistui");
		exit(1);
	}
	ptr->arvo = luku;
	ptr->pVasen = NULL;
	ptr->pOikea = NULL;
	return ptr;

}
/*aina lähdetään juurisolmusta liikkelle
solmuissa mennään alaspäin niin pitkään ennen kuin tullaan tyhjään solmuun ja silloin luodaan uusi solmu kyseiselle paikalle ja palataan pois aliohjelmasta	
*/
void lisaaArvo(Solmu **pA,int luku){
	//jos solmu on tyhjä niin luodaan uusi solmu
	if(*pA == NULL){
		*pA = uusiSolmu(luku);
		return;
	
	}
	//jos luku on pienemp kuin tarkasteltavan solmun arvo niin mennään puussa solmusta vasemmalle
	if(luku > (*pA)->arvo){
		lisaaArvo(&(*pA)->pVasen,luku);
	//jos luku on suurempi tai yhtä suuri kuin tarkasteltava solmu niin mennään puussa solmusta oikealle
	}else{
		lisaaArvo(&(*pA)->pOikea,luku);
	}

}
//tulostetaan solmut järestyksessä:vasen, juuri, oikea
void tulostusP(Solmu *pA){
	if(pA != NULL){
		printf("%d ",pA->arvo);
		tulostusP(pA->pVasen);
		
		tulostusP(pA->pOikea);
	}
	
}
//tulostetaan solmut järestyksessä:vasen, juuri, oikea
void tulostus(Solmu *pA){
	if(pA != NULL){
		tulostus(pA->pVasen);
		printf("%d ",pA->arvo);
		tulostus(pA->pOikea);
	}
	
}
//tyhjennetään linkitetty lista
void tyhjennys(Solmu *pA){
	if(pA!=NULL){
		tyhjennys(pA->pVasen);
		tyhjennys(pA->pOikea);
		printf("Poistetaan %d\n",pA->arvo);
		free(pA);
	}

	
}

//tulostetaan puu muodossa

void tulostaPuu(Solmu*pA, int vali) { 
    if (pA != NULL) {
	//väli on väli joka tulee kun tehdään puuta
	    vali += 10; 
	    tulostaPuu(pA->pOikea, vali); 
	    printf("\n"); 
	    for (int i = 10; i < vali; i++) 
		printf(" "); 
	    printf("%d\n", pA->arvo); 
	    tulostaPuu(pA->pVasen, vali); 
    }
} 

//etsitään arvo
int etsiArvo(Solmu *pA,int arvo){
	//jos listan arvo on sama kuin etsittävä arvo palautetaan arvo
	printf("Arvo solmussa on %d\n",pA->arvo);
	if(arvo == pA->arvo){
		return pA->arvo;
	//jos lsitan arvo on suurempi kuin etsittävä arvo niin mennään listan arvosta vasempaan solmuun
	}else if (arvo < pA->arvo){
		//jos vasemmassa solmussa on jotain niin mennään sinne
		if(pA->pVasen!=NULL){
			//etsitään arvo uudestaan nyt vasemmasta solmusta
			return etsiArvo(pA->pVasen,arvo);
		//jos ei löytynyt
		}else{
			return 0;
		}
	//jos lstsan arvo on pienempi kuin etsittävä arvo niin mennään listan arvosta oikeaan solmuun
	}else if (arvo > pA->arvo){
		//jos oikeassa solmussa on jotain niin mennään sinne
		if(pA->pOikea != NULL){
			return etsiArvo(pA->pOikea,arvo);
		//ei löynyt mitään
		}else{
			return 0;
		}
	}else{
		return 0;
	}
}
int main (void){

	int luvut[KOKO] = {8, 9, 10, 2, 1, 5, 3, 6, 4};
	
	Solmu *pA=NULL;
	for(int i = 0; i<KOKO;i++){
		lisaaArvo(&pA,luvut[i]);
	}
	
	
	
	int luku=0;
	int arvo;
	while(luku!=-1) {
		printf("Anna etsittävä luku, -1 lopettaa: ");
		
		scanf("%d",&luku);
		if(luku == -1){
			break;
		}
		arvo = etsiArvo(pA,luku);
		if (arvo == 0){
			printf("Antamaasi lukua (%d) ei löytynyt\n",luku);
		}else{
			printf("Antamasi luku (%d) löytyi\n",arvo);
		}
	
	
	}
	tulostus(pA);
	printf("\n");
	tulostusP(pA);
	printf("\n");
	tulostaPuu(pA,0);
	tyhjennys(pA);
	pA = NULL;
	return 0;
}
















