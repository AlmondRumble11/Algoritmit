#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define KOKO 9
struct Node {
	int arvo;
	int korkeus;
	int tila;
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
	ptr->tila = 0;
	ptr->korkeus = 1; //asetetaan korkeus
	ptr->pVasen = NULL;
	ptr->pOikea = NULL;
	
	return ptr;

}
int maksimi(int vasenpuoli, int oikeapuoli){
	int temp;
	if (vasenpuoli > oikeapuoli){
		temp = vasenpuoli;
		vasenpuoli = oikeapuoli;
		oikeapuoli = temp;
	
	}
	return oikeapuoli;

	

}
void tulostaPuu(Solmu*pA, int vali) { 
    if (pA != NULL) {
	//väli on väli joka tulee kun tehdään puuta
	    vali += 10; 
	    tulostaPuu(pA->pOikea, vali); 
	    printf("\n"); 
	    for (int i = 10; i < vali; i++) 
		printf(" "); 
	    printf("%d(%d)(%d)\n", pA->arvo,pA->korkeus,pA->tila); 
	    tulostaPuu(pA->pVasen, vali); 
    }
} 
//saadaan solmun ero arvo
int solmunKorkeus(Solmu *pA){
	int korkeus = 0;
	if (pA != NULL){
		korkeus = pA->korkeus;
	}
	return korkeus;
}
//solmusta vasemman ja oikean puoleisen puun korkeus ero
int korkeusEro(Solmu *pA){

	int korkeusEro = 0;
	
	if(pA != NULL){
		korkeusEro = solmunKorkeus(pA->pVasen) - solmunKorkeus(pA->pOikea);
	}

	return korkeusEro;
}


Solmu *kierrosOikealle(Solmu *juuri){
	Solmu *lapsi = juuri->pVasen; //uusi juuri
	Solmu *lapsenlapsi = lapsi->pOikea;

	
	//kierros
	lapsi->pOikea = juuri;
	juuri->pVasen = lapsenlapsi;
	
	
	//korkeuden päivitys
	//solmunkorkeus eroon käytetty aliohjelmaa sen takia koska  solmulla ei ole oikea tai vasenta lasta niin sen tarkastus onnistuu helpoiten aliohjelmassa
	juuri->korkeus = maksimi(solmunKorkeus(juuri->pVasen), solmunKorkeus(juuri->pOikea)) +1;
	lapsi->korkeus = maksimi(solmunKorkeus(lapsi->pVasen), solmunKorkeus(lapsi->pOikea)) +1;
		juuri->tila = korkeusEro(juuri);
	lapsi->tila = korkeusEro(lapsi);
	//palautetaan uusi juurisolmu
	return lapsi;

}

Solmu *kierrosVasemmalle(Solmu *juuri){
	Solmu *lapsi = juuri->pOikea; //uusi juuri
	Solmu *lapsenlapsi = lapsi->pVasen;
	

	//kierros
	lapsi->pVasen = juuri;
	juuri->pOikea = lapsenlapsi;
	
	
	//korkeuden päivitys
	//solmunkorkeus eroon käytetty aliohjelmaa sen takia koska  solmulla ei ole oikea tai vasenta lasta niin sen tarkastus onnistuu helpoiten aliohjelmassa
	juuri->korkeus = maksimi(solmunKorkeus(juuri->pVasen), solmunKorkeus(juuri->pOikea)) +1;
	lapsi->korkeus = maksimi(solmunKorkeus(lapsi->pVasen), solmunKorkeus(lapsi->pOikea)) +1;
	juuri->tila = korkeusEro(juuri);
	lapsi->tila = korkeusEro(lapsi);
	
	//palautetaan uusi juurisolmu
	return lapsi;
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
Solmu *lisaaArvo(Solmu *pA,int luku){
	//jos solmu on tyhjä niin luodaan uusi solmu
	if(pA == NULL){
		pA = uusiSolmu(luku);
		return pA;
	
	}
	//jos luku on pienemp kuin tarkasteltavan solmun arvo niin mennään puussa solmusta vasemmalle
	if(luku < pA->arvo){
		pA->pVasen = lisaaArvo(pA->pVasen,luku);
	//jos luku on suurempi tai yhtä suuri kuin tarkasteltava solmu niin mennään puussa solmusta oikealle
	}else if(luku > pA->arvo){
		pA->pOikea = lisaaArvo(pA->pOikea,luku);
	}else{
		return pA;
	}

	//päivitetään korkeus
	//korkeus kyseiselle solmulle on vasemman ja oikean puun maksimi eli siis kumman puolen ero on suuremi ja lisätään siihen 1
	pA->korkeus = maksimi(solmunKorkeus(pA->pVasen), solmunKorkeus(pA->pOikea)) +1;

	
	//tarkastetaan korkeuesero
	int korkeus;
	korkeus = korkeusEro(pA);
	pA->tila = korkeus;
	//vasen vasen tapaus eli vasemmalla on liikkaa --> lierretään kerran oikealle
	if(korkeus > 1 && luku < pA->pVasen->arvo){
		printf("Tehdään LL kierto\n");
		printf("Puu ennen:\n");
		tulostaPuu(pA,0);
		pA = kierrosOikealle(pA);
		printf("Kierron jälkeen:\n");
		tulostaPuu(pA,0);
		printf("###########################\n");
		return pA;
	}
	// oikea oikea tapaus eli oikealla liikaa -->kierretään kerran vasemmalle
	if(korkeus < -1 && luku > pA->pOikea->arvo){
		printf("Tehdään RR kierto\n");
		printf("Puu ennen:\n");
		tulostaPuu(pA,0);
		pA = kierrosVasemmalle(pA);
		printf("Kierron jälkeen:\n");
		tulostaPuu(pA,0);
		printf("###########################\n");
		
		return pA;
	}
	//vasen oikea tapaus eli vasemalla on liikaa mutta luku suurempi kuin vasemman arvo eli menisi sen oikealle puolelle--> käännetään vasenta puoleta kerran vasemmalle 
	// ja sitten solmua kerran oikealle
	if(korkeus > 1 && luku > pA->pVasen->arvo){
		printf("Tehdään LR kierto\n");
		printf("Puu ennen vasenta kiertoa:\n");
		tulostaPuu(pA,0);
		pA->pVasen = kierrosVasemmalle(pA->pVasen);
		printf("Puu vasemman kierron jälkeen ja ennen kiertoa oikealle:\n");
		tulostaPuu(pA,0);
		pA = kierrosOikealle(pA);
		printf("Puu kiertojen jälkeen:\n");
		tulostaPuu(pA,0);
		printf("###########################\n");
		return pA;
	}
	// oikea vasen tapaus eli oikealla on liikaa mutta luku pienempi kuin oikean arvo eli menisi sen vasemmalle puolelle--> käännetään oikeaa puoleta kerran oikealle 
	// ja sitten solmua kerran vasemmalle
	if(korkeus < -1 && luku < pA->pOikea->arvo){
		printf("Tehdään RL kierto\n");
		printf("Puu ennen oikea kiertoa kiertoa:\n");
		tulostaPuu(pA,0);
	
		pA->pOikea = kierrosOikealle(pA->pOikea);
		printf("Puu oikean kierron jälkeen ja ennen kiertoa vasemmalle:\n");
		tulostaPuu(pA,0);
		pA = kierrosVasemmalle(pA);
		printf("Puu kiertojen jälkeen:\n");
		tulostaPuu(pA,0);
		printf("###########################\n");
		return pA;
	}
	
	return pA;
	
		
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

int main(void){
	int luvut[KOKO] = {9,10,11,3,2,6,4,7,5};
	Solmu *pA = NULL;
	for (int i = 0; i<KOKO; i++){
		printf("Lisätään luku %d\n",luvut[i]);
		pA = lisaaArvo(pA, luvut[i]);
		printf("Puu lisätyn luvun jälkeen:\n");
		tulostaPuu(pA,0);
		printf("###########################\n");
	
		
	}
	
	tulostaPuu(pA,0);
	printf("\njälki\n");
	printPostorder(pA);
	printf("\nsisä\n");
	printInorder(pA);
	printf("\nesi\n");
	printPreorder(pA);
	tyhjennys(pA);




	return 0;
}
