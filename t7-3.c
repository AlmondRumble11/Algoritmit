#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
	if(luku < (*pA)->arvo){
		lisaaArvo(&(*pA)->pVasen,luku);
	//jos luku on suurempi tai yhtä suuri kuin tarkasteltava solmu niin mennään puussa solmusta oikealle
	}else{
		lisaaArvo(&(*pA)->pOikea,luku);
	}

}
//tulostetaan solmut järestyksessä:vasen, juuri, oikea
void tulostus(Solmu *pA){
	if(pA != NULL){
		tulostus(pA->pVasen);
		printf("%d\n",pA->arvo);
		tulostus(pA->pOikea);
	}
	
}
void printPostorder(Solmu* node) 
{ 
     if (node == NULL) 
        return; 
  
     // first recur on left subtree 
     printPostorder(node->pVasen); 
  
     // then recur on right subtree 
     printPostorder(node->pOikea); 
  
     // now deal with the node 
     printf("%d ", node->arvo); 
} 
void printInorder( Solmu* node) 
{ 
     if (node == NULL) 
          return; 
  
     /* first recur on left child */
     printInorder(node->pVasen); 
  
     /* then print the data of node */
     printf("%d ", node->arvo);   
  
     /* now recur on right child */
     printInorder(node->pOikea); 
} 
void printPreorder(Solmu* node) 
{ 
     if (node == NULL) 
          return; 
  
     /* first print data of node */
     printf("%d ", node->arvo);   
  
     /* then recur on left sutree */
     printPreorder(node->pVasen);   
  
     /* now recur on right subtree */
     printPreorder(node->pOikea); 
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

int main (void){

	int luvut[7] = {25, 23, 28, 16, 44, 24, 27};
	
	Solmu *pA=NULL;
	for(int i = 0; i<7;i++){
		lisaaArvo(&pA,luvut[i]);
	}
	
	tulostus(pA);
	tulostaPuu(pA,0);
	tyhjennys(pA);
	pA=NULL;
	//int luvut2[7] = {44, 28, 27, 23, 16, 24, 25};
	int luvut2[9] = {10, 5, 4, 15, 13, 14, 20, 19, 30};
	for(int i = 0; i<9;i++){
		lisaaArvo(&pA,luvut2[i]);
	}
	tulostus(pA);
	tulostaPuu(pA,0);
	printf("\njälki\n");
	printPostorder(pA);
	printf("\nsisä\n");
	printInorder(pA);
	printf("\nesi\n");
	printPreorder(pA);
	tyhjennys(pA);
	pA = NULL;

	return 0;
}
















