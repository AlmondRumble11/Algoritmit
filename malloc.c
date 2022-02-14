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

int main (void){
	Solmu *ptrA = NULL;
	printf("Lisätään luvut listaan\n");
	ptrA = lisays(ptrA);
	tulostus(ptrA);
	return 0;
}
