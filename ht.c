#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define KOKO 9
#define RIVI 10
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
	ptr->korkeus = 1; //asetetaan korkeus
    ptr->tila = 0;
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
void tulostaPuu(Solmu*pA, int vali,int taso, Solmu *alussa,int check) { 
	
    if (pA != NULL) {
	//väli on väli joka tulee kun tehdään puuta
	    vali += 10; 
	  
	    tulostaPuu(pA->pOikea, vali,taso++,alussa,check); 
	    
	       /*if(pA->pOikea!=NULL){
	   			printf("/");
	   		}
	    for (int i = 45; i < vali; i++) {
			printf(" "); 
			}
	    	 if(pA->pOikea!=NULL){
	   			printf("/");
	   		}*/
	   	
	   printf("\n"); 
	 	
	    for (int i = 10; i < vali; i++) {
			printf(" "); 
			
		}
		
	    printf("%d(%d)(%d)\n", pA->arvo,pA->korkeus,pA->tila); 
	   // printf("taso %d",taso);
	 	
	    if(pA->pVasen!=NULL){
	   
	        for (int j = 3; j < vali; j++) {
			printf("+"); 
			}
	   			printf("\\");
	   }else{
	   	
	   	for (int k = 3; k < (vali-10*taso); k++) {
			printf("¤"); 
	   	}
	   	printf("/");
	   }
	   	if(pA->arvo == alussa->arvo){
			//taso--;
			check = 1;
		}
		if(check==1){
		
		taso--;
		}
	    tulostaPuu(pA->pVasen, vali,taso--,alussa,check); 
	
	 
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
		printf("Luku on jo puussa\n");
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
		printf("Tehdaan LL kierto\n");
		printf("Puun kierron vaativa osa ennen kietoa:\n");
		//tulostaPuu(pA,0);
		pA = kierrosOikealle(pA);
		printf("Puun kierron vaativa osa kierron jalkeen:\n");
		//tulostaPuu(pA,0);
		printf("###########################\n");
		return pA;
	}
	// oikea oikea tapaus eli oikealla liikaa -->kierretään kerran vasemmalle
	if(korkeus < -1 && luku > pA->pOikea->arvo){
		printf("Tehdaan RR kierto\n");
		printf("Puun kierron vaativa osa ennen kiertoa:\n");
		//tulostaPuu(pA,0);
		pA = kierrosVasemmalle(pA);
		printf("Puun kierron vaativa osa kierron jalkeen:\n");
		//tulostaPuu(pA,0);
		printf("###########################\n");
		
		return pA;
	}
	//vasen oikea tapaus eli vasemalla on liikaa mutta luku suurempi kuin vasemman arvo eli menisi sen oikealle puolelle--> käännetään vasenta puoleta kerran vasemmalle 
	// ja sitten solmua kerran oikealle
	if(korkeus > 1 && luku > pA->pVasen->arvo){
		printf("Tehdaan LR kierto\n");
		printf("Puun kierron vaativa osa ennen vasenta kiertoa:\n");
		//tulostaPuu(pA,0);
		pA->pVasen = kierrosVasemmalle(pA->pVasen);
		printf("Puu kierron vaativa osa  vasemman kierron jalkeen ja ennen kiertoa oikealle:\n");
		//tulostaPuu(pA,0);
		pA = kierrosOikealle(pA);
		printf("Puun kierron vaativa osa kiertojen jalkeen:\n");
		//tulostaPuu(pA,0);
		printf("###########################\n");
		return pA;
	}
	// oikea vasen tapaus eli oikealla on liikaa mutta luku pienempi kuin oikean arvo eli menisi sen vasemmalle puolelle--> käännetään oikeaa puoleta kerran oikealle 
	// ja sitten solmua kerran vasemmalle
	if(korkeus < -1 && luku < pA->pOikea->arvo){
		printf("Tehdaan RL kierto\n");
		printf("Puun kierron vaativa osa ennen oikea kiertoa kiertoa:\n");
		//tulostaPuu(pA,0);
	
		pA->pOikea = kierrosOikealle(pA->pOikea);
		printf("Puu oikean kierron jalkeen ja ennen kiertoa vasemmalle:\n");
		//tulostaPuu(pA,0);
		pA = kierrosVasemmalle(pA);
		printf("Puu kiertojen jalkeen:\n");
		//tulostaPuu(pA,0);
		printf("###########################\n");
		return pA;
	}
	
	return pA;
	
		
}


//tyhjennetään linkitetty lista
Solmu *tyhjennys(Solmu *pA){
	if(pA!=NULL){
		tyhjennys(pA->pVasen);
		tyhjennys(pA->pOikea);
		printf("Poistetaan %d\n",pA->arvo);
		free(pA);
		pA = NULL;
	}
    return pA;

	
}
//etsitään arvo
int etsiArvo(Solmu *pA,int arvo){
	//jos listan arvo on sama kuin etsittävä arvo palautetaan arvo
	printf("Ollaan solmussa on %d\n",pA->arvo);
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
int valikko(){
	int valinta;
	printf("\nValitse haluamasi toiminto alla olevasta valikosta:\n");
	printf("1) Lue avaimet tiedostosta\n");
    printf("2) Etsi avain puusta\n");
    printf("3) Lisaa avain puuhun\n");
	printf("4) Tulosta puu\n");
	printf("5) Tyhjenna puu\n");
	printf("6) Piirra puu tiedostoon\n");
	printf("0) Lopeta\n");
	printf("Valintasi: ");
	scanf("%d", &valinta);
	return valinta;
}
Solmu *lukeminen(Solmu *pA, char nimi[]){
    FILE *tiedosto;
    char arvo[100]="";
    
    int avain;
    printf("Luetaan arvot tiedostosta %s\n",nimi);
    if ((tiedosto = fopen(nimi, "r")) == NULL){
		perror("Tiedoston lukeminen epäonnistui");
		exit(0);		
	}
    while (fgets(arvo,RIVI, tiedosto) != NULL){
       
        avain = atol(arvo);
        printf("%d\n",avain);
		
        printf("Lisataan luku %d\n",avain);
		pA = lisaaArvo(pA, avain);
		printf("Puu lisatyn luvun jalkeen:\n");
		//tulostaPuu(pA,0);
		printf("###########################\n");
		


    }
    fclose(tiedosto);
    printf("Tiedosto  luettu.\n");


    return pA;
}
int tiedostonValinta(){
	int valinta;
	printf("1) Alkuperainen tiedosto(10 avainta)\n");
    printf("2) 100 avainta\n");
    printf("3) 1000 avainta\n");
	printf("4) 10000 avainta\n");
	printf("5) 100000 avainta\n");
	printf("Valintasi: ");
	scanf("%d",&valinta);
	return valinta;
}
void kirjotaPuu(Solmu *pA, FILE *tiedosto,int vali){
	if (pA != NULL){
		vali += 10; 
	    kirjotaPuu(pA->pOikea, tiedosto,vali); 
	    fprintf(tiedosto,"\n"); 
	    for (int i = 10; i < vali; i++) {
			fprintf(tiedosto," "); 
		}
	    fprintf(tiedosto,"%d(%d)(%d)\n", pA->arvo,pA->korkeus,pA->tila); 
	    kirjotaPuu(pA->pVasen, tiedosto,vali); 
    }


}
void kirjota(Solmu *pA, char nimi[]){
	FILE *tiedosto;
	if ((tiedosto = fopen(nimi, "w")) == NULL){
		perror("Tiedoston lukeminen epäonnistui");
		exit(0);		
	}
	kirjotaPuu(pA, tiedosto,0);
	fclose(tiedosto);

}
int main(void){
	//int luvut[KOKO] = {9,10,11,3,2,6,4,7,5};
    Solmu *pA = NULL;
    char tiedosto[100] = "arvot.txt";
    char puu_tiedosto[100] = "puutiedosto.txt";
    //int luvut[KOKO] = {2, 4, 6, 8, 10, 12, 14, 30, 28};
    int valinta = -1;
    int lisattava_avain;
    int etsittava_avain;
	int tiedoston_valinta;
    int arvo_loyty;
    do{
        valinta = valikko();
        switch (valinta)
        {
        case 1:

            if (pA != NULL){
                printf("Tyhjenna puu ensin\n");
            }else{
				printf("Mika tiedosto\n");
				tiedoston_valinta = tiedostonValinta();
				switch (tiedoston_valinta){
				case 1:
					break;
				case 2:
					strcpy(tiedosto,"arvot_100.txt");
					break;
				case 3:
					strcpy(tiedosto,"arvot_1000.txt");
					break;
				case 4:
					strcpy(tiedosto,"arvot_10000.txt");
					break;
				case 5:
					strcpy(tiedosto,"arvot_100000.txt");
					break;
				default:
					printf("Tuntematon valinta, yrita uudestaan.\n");
					break;
				}
                pA = lukeminen(pA, tiedosto);
            }

            break;
        case 2:
			if(pA != NULL){
				printf("Anna etsittava avain:");
				scanf("%d",&etsittava_avain);
				arvo_loyty = etsiArvo(pA,etsittava_avain);
				if (arvo_loyty == 0){
					printf("Antamaasi lukua (%d) ei loytynyt\n",etsittava_avain);
				}else{
					printf("Antamasi luku (%d) loytyi\n",etsittava_avain);
				}
			}else{
				printf("Lue tiedosto ensin\n");
			}
            break;
        case 3:
            printf("Anna lisattava avain:");
            scanf("%d",&lisattava_avain);
            pA = lisaaArvo(pA,lisattava_avain);
			printf("Puu lisatyn avaimen jalkeen\n");
			tulostaPuu(pA,0,0,pA,0);
            break;
        case 4:
			if(pA != NULL){
				printf("Tulostetaan puu");
				tulostaPuu(pA,0,0,pA,0);
			}else{
				printf("Lue tiedosto ensin\n");
			}
            break;
        case 5:
            pA = tyhjennys(pA);
            break;
		case 6:
            if (pA != NULL){
				kirjota(pA,puu_tiedosto);
			}else{
				printf("Lue tiedosto ensin\n");
			}
            break;
		case 0:
			pA = tyhjennys(pA); 
			printf("Kiitos ohjelman kaytosta.\n");
			printf("\n");
			
			break;
        default:
            printf("Tuntematon valinta, yrita uudestaan.\n");
			break;
        }

    }while (valinta!=0);
  
    

	/*for (int i = 0; i<KOKO; i++){
		printf("Lisataan luku %d\n",luvut[i]);
		pA = lisaaArvo(pA, luvut[i]);
		printf("Puu lisatyn luvun jalkeen:\n");
		tulostaPuu(pA,0);
		printf("###########################\n");
	
		
	}
	printf("\nValmis puu:");
	tulostaPuu(pA,0);
	tyhjennys(pA);*/




	return 0;
}
