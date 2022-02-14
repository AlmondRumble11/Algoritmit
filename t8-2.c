#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct puusolmu_t {
  int luku;
  short tila; /* tasapainoilmaisin */
  struct puusolmu_t *vasen, *oikea;
} puusolmu, *puuosoitin;

void lisaa_solmu(puuosoitin *, int, int *, puusolmu *);
void oikea_kierto(puuosoitin *, int *,puusolmu *);
void tulosta_puu(puuosoitin);
void vasen_kierto(puuosoitin *, int *,puusolmu *);


//tyhjennetään linkitetty lista
void tyhjennys(puusolmu *pA){
	if(pA!=NULL){
		tyhjennys(pA->vasen);
		tyhjennys(pA->oikea);
		printf("Poistetaan %d\n",pA->luku);
		free(pA);
	}

}

void tulostaPuu(puusolmu *pA, int vali) { 
    if (pA != NULL) {
	//väli on väli joka tulee kun tehdään puuta
	    vali += 10; 
	    tulostaPuu(pA->oikea, vali); 
	    printf("\n"); 
	    for (int i = 10; i < vali; i++) 
		printf(" "); 
	    printf("%d(%d)\n", pA->luku,pA->tila); 
	    tulostaPuu(pA->vasen, vali); 
    }
} 
int main()
	{
	int etp = 0, i, luvut[] = {9,10,11,3,2,6,4,7,5,0};
	puuosoitin puu = NULL;
	puusolmu *pA = NULL;
	
	for(i = 0; luvut[i] != 0; i++)
	{
		printf("Lisätään luku %d puuhun\n",luvut[i]);
		pA = puu;
		lisaa_solmu(&puu, luvut[i], &etp, pA);
		printf("Puu lisätyn luvun jälkeen");
		tulostaPuu(puu,0);
		printf("\n");
		printf("############################\n");
	}
	tulosta_puu(puu);
	printf("\n");
	int luku; 
	while(1){
	
		printf("Anna luku joka lisätään puuhun, 0 lopettaa: ");
		scanf("%d",&luku);
		if(luku==0){
			break;
		}else{
			lisaa_solmu(&puu,luku,&etp,pA);
			tulostaPuu(puu,0);
			printf("\n");
			printf("############################\n");
		}
	
	}
	tyhjennys(puu);
	puu = NULL;
	int luvut2[10] =  {65,85,25,50,100,10,150,75,125,15};
	int etp2 = 0;
	for(int j = 0; j < 10; j++){
		printf("Lisätään luku %d puuhun\n",luvut2[j]);
		pA = puu;
		lisaa_solmu(&puu, luvut2[j], &etp2, pA);
		printf("Puu lisätyn luvun jälkeen");
		tulostaPuu(puu,0);
		printf("\n");
		printf("############################\n");
	
	}
	tyhjennys(puu);
 	return 0;
}

void lisaa_solmu(puuosoitin *emo, int luku, int *etp, puusolmu *pA)
{
	//jos osoitin solmuun on null eli ei ole solmua niin luodaan uusi solmu
	if(!(*emo)){
	    *etp = 1; // asetetaan tasapainottomuuden ilmaisin 
	    	if(!(*emo = (puuosoitin)malloc(sizeof(puusolmu)))){
			perror("malloc");
			exit(1);
		}
		(*emo)->vasen = (*emo)->oikea = NULL;
		(*emo)->tila = 0;
		(*emo)->luku = luku;
	//jos annettu luku on emo solmua pienempi niin lisätään se sen vasemmalle puolelle
  	} else if(luku < (*emo)->luku){	
    		lisaa_solmu(&(*emo)->vasen, luku, etp, pA);
		
		//tehdään toimenpiteitä riippuen mikä tasapainotila emo solmussa on ennen lisäystä 
		if(*etp){
			switch((*emo)->tila){
				//oikella 1 enemmän kuin vasemmalle ennen lisäystä vasemmalle--> nyt on tasapainossa
				case -1:
					(*emo)->tila = 0;
					*etp = 0;
					break;
				// tasapainossa --> nyt vasemmalle yksi ennemmän
				case 0:
					(*emo)->tila = 1;
					break;
				//vasemmalle valmiiksi 1 enemmän --> vasen kierto eli kierretään oikealle puuta
				case 1:
					
					vasen_kierto(emo, etp, pA);
					
      			}
    		}
	//jos luku on suurempi kuin emo luku niin lisätään se sen oikealle puolelle
  	} else if(luku > (*emo)->luku){
    		lisaa_solmu(&(*emo)->oikea, luku, etp,pA);
    		//tehdään toimenpiteitä riippuen mikä tasapaino tila oli emo solmussa ennen lisäystä
		if(*etp){
      			switch((*emo)->tila){
      				//jos vasemmalla 1 enemmän kuin oikealla--> emo solmu tasapainossa
				case 1:
				  	(*emo)->tila = 0;
				  	*etp = 0;
				  	break;
			  	//jos emo solmu oli tasapainossa--> nyt se on oikealle yhden enemmän
				case 0:
				  	(*emo)->tila = -1;
				   	break;
			   	//jos se oli valmiiksi oikealle yhden enemmän --> oikea kierto eli kierretään vasemmalle
				case -1:
					
					oikea_kierto(emo, etp, pA);
				
			}
    		}
	//jos on sama luku kuin jos valmiiksi puussa
  	} else{
		*etp = 0;
		printf("Luku %d on jo puussa\n", luku);
  	}

}

void tulosta_puu(puuosoitin solmu)
{
	if(!solmu) return;
	tulosta_puu(solmu->vasen);
	printf("%d ", solmu->luku);
	tulosta_puu(solmu->oikea);
}


void vasen_kierto(puuosoitin *emo, int *etp, puusolmu *pA)
{
  puuosoitin lapsi, lapsenlapsi;
  char kierto[3];
  lapsi = (*emo)->vasen; //lapsi on nyt emon vasen solmu
  //jos emon vasen oli aiemmin yhden enemmän--> ei ole enää--> LL kierto
  if(lapsi->tila == 1) /* LL-kierto */
  {
  	printf("Puu ennen vasenta(LL) kiertoa:\n");
	tulostaPuu(pA,0);
	printf("\n");
	
	
	(*emo)->vasen = lapsi->oikea;
	lapsi->oikea = *emo;
	(*emo)->tila = 0;
	(*emo) = lapsi;
	
	
	strcpy(kierto,"LL");
  } else /* LR-kierto */
  {
  	printf("Puu ennen LR kiertoa:\n");
	tulostaPuu(pA,0);
	
	printf("########################\n");
	//oikea kierto vrt
	lapsenlapsi = lapsi->oikea; //lapsi = (*emo)->oikea; 
	lapsi->oikea = lapsenlapsi->vasen; //(*emo)->oikea = lapsi->vasen;
	lapsenlapsi->vasen = lapsi; //lapsi->vasen = *emo;



	strcpy(kierto,"LR");
	
	//vasen kierto 
	(*emo)->vasen = lapsenlapsi->oikea; //(*emo)->vasen = lapsi->oikea;
	lapsenlapsi->oikea = *emo; //lapsi->oikea = *emo;
	
	//muutetaan emon ja lapsen tilaa
	switch(lapsenlapsi->tila)
		{
		case 1:
			(*emo)->tila = -1;
			lapsi->tila = 0;
			break;                        
		case 0:
			(*emo)->tila = lapsi->tila = 0;
			break;
		case -1:
			(*emo)->tila = 0;
			lapsi->tila = 1;
			break;
	}
	*emo = lapsenlapsi;

	}
	(*emo)->tila = 0;
	*etp = 0;
	printf("Muutettu puu osuus %s kierron jälkeen:\n",kierto);
	tulostaPuu(*emo,0);
	printf("########################\n");
}
void oikea_kierto(puuosoitin *emo, int *etp, puusolmu *pA){ 
	puuosoitin lapsi, lapsenlapsi;
	lapsi = (*emo)->oikea; 
	char kierto[3];      
	//jos emon oikea solmu oli aiemmein yhden enemmän--> ei ole enää--> RR kierto            
	if(lapsi->tila == -1){//RR-kierto
	
	
		printf("Puu ennen oikeaa(RR) kiertoa:\n");
		tulostaPuu(pA,0);
		printf("\n");
		
		strcpy(kierto,"RR");	
		(*emo)->oikea = lapsi->vasen;
		lapsi->vasen = *emo;
		(*emo)->tila = 0;
		(*emo) = lapsi;
		
		
	
		
	}else { //RL-kierto
		printf("Puu ennen RL kiertoa:\n");
		tulostaPuu(pA,0);
		printf("########################\n");
		
		//vasenkierto
		printf("Emo on %d\n",(*emo)->luku);
		printf("Lapsi on %d\n", lapsi->luku);
		printf("lapsenlapsi on  lapsen vasen solmu %d\n",lapsi->vasen->luku);	
		lapsenlapsi = lapsi->vasen;
		printf("Lapsen vasen solmu on nyt lapsenlapsen oikea solmu %d\n",lapsenlapsi->oikea->luku);		
		lapsi->vasen = lapsenlapsi->oikea;
		printf("lapsenlapsen oikea solmu on nyt lapsi %d\n",lapsi->luku);
	
		lapsenlapsi->oikea = lapsi;	
	
		
		
		strcpy(kierto,"RL");		
		printf("Nyt emon oikea solmu on lapsenlapsen vasen solmu\n");
		(*emo)->oikea = lapsenlapsi->vasen;
		printf("lapsenlapsen vasen solmu on nyt emo %d\n", (*emo)->luku);
		lapsenlapsi->vasen = *emo;
		
		//muutetaan emon ja lapsen tilaa
		switch(lapsenlapsi->tila){
			case 1:
				(*emo)->tila = 0;
				lapsi->tila = -1;
				break;
			case 0:
				(*emo)->tila = 0;
				lapsi->tila = 0;
				break;
			case -1:
				(*emo)->tila = 1;
				lapsi->tila = 0;
				break;
		}
		*emo = lapsenlapsi;
	
	
	}
	(*emo)->tila = 0;
	*etp = 0;
		printf("Muutettu puu osuus %s kierron jälkeen:\n",kierto);
		tulostaPuu(*emo,0);
		printf("########################\n");
}
