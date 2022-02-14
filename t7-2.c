#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Node {
	int iNumero;
	struct Node *pNext;
};
typedef struct Node Solmu;

Solmu *lisays(Solmu *ptrA){
	Solmu *ptr;
	Solmu *ptrU;
	int luvut[7] = {2,4,6,3,7,1,9};
	//lisätään luvut listaan
	for (int i = 0; i<7;i++){
		//varataan muisti
		if((ptrU = (Solmu*)malloc(sizeof(Solmu))) == NULL){
			perror("Muistin varaus epäonnistui");
			exit(1);
		}
		ptrU->iNumero=luvut[i];	
		ptrU->pNext = NULL;
		//jos listassa ei ole mitään
		if(ptrA == NULL){
			ptrA = ptrU;
		}else{
			
			ptr = ptrA; 
			//siirretään poitteria seuraavaan kohtaan
			while(ptr->pNext != NULL){
				ptr = ptr->pNext;
			}		
			ptr->pNext = ptrU;
		}	
	}
	return ptrA;
}
void tulostus(Solmu *pA){
	Solmu *ptr = pA;
	while(ptr != NULL){
		printf("%d\n",ptr->iNumero);
		ptr = ptr->pNext;
	}
}
Solmu *tyhjennys(Solmu *pA){
	Solmu *ptr = pA;
	while(ptr != NULL){
		pA=ptr->pNext;
		free(ptr);
		ptr=pA;
	}
	printf("Muisti vapautettu\n");
	return pA;
}

Solmu *poisto(Solmu *pA, int avain){
	Solmu *ptr=pA;
	Solmu *ptrAikasempi;
	while(ptr != NULL && ptr->iNumero != avain){
		ptrAikasempi = ptr;
		ptr = ptr->pNext;
	}
	if (ptr == NULL){
		printf("Avain %d ei ollut listassa\n",avain);
		return pA;	
	}else{
		ptrAikasempi->pNext = ptr->pNext;
		free(ptr);
	}
	return pA;
}
Solmu *poistaSijainti(Solmu *pA, int sijainti){
	int koko = 0;
	Solmu *ptr=pA;
	Solmu *ptrU;
	
	//esitään oikea kohta  josta halutaan poistaa
	while(ptr != NULL && koko++ < sijainti-1){
		ptrU = ptr;
		ptr = ptr->pNext;
	}
	if (ptr == NULL){
		printf("Jotain meni pieleen\n");
	}else{
		//
		ptrU->pNext = ptr->pNext;
		int temp = ptr->iNumero;
		printf("Poistettava luku %d\n",ptr->iNumero);
		free(ptr);
		printf("Luku %d on poistettu\n",temp);
	}
	return pA;
}
int pituus(Solmu *pA){
	int pituus = 0;
	Solmu *ptr = pA;
	
	while(ptr != NULL){
		pituus++;
		ptr = ptr->pNext;
	}
	return pituus;
}
int main (void){
	Solmu *ptrA = NULL;
	printf("Lisätään luvut listaan\n");
	ptrA = lisays(ptrA);
	tulostus(ptrA);
	printf("Poistetaan avain 6 listasta\n");
	int avain = 6;
	ptrA = poisto(ptrA,avain);
	tulostus(ptrA);
	printf("Poistetaan toiseksi viimeinen alkio listasta\n");
	int listan_pituus;
	listan_pituus = pituus(ptrA);
	int sijainti = listan_pituus - 1;
	if (sijainti <= 0 ){
		printf("Jotain on mennyt pieleen\n");
	
	}else{
		ptrA = poistaSijainti(ptrA, sijainti);
		tulostus(ptrA);
	}
	printf("Tyhjennetään lista ja vapautetaan muisti\n");
	ptrA = tyhjennys(ptrA);
	return 0;
}
