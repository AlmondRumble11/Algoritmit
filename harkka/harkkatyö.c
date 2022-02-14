/*
NIMI: Jesse Mustonen
Opiskelia nro: 0541805
lähteinä hyödynnetty:
https://www.tutorialspoint.com/print-binary-tree-in-2-dimensions-in-cplusplus puu rakenteen tulostukseen
https://www.tutorialspoint.com/data_structures_algorithms/avl_tree_algorithm.htm hahmotaa miten kierrokset toimivat
https://www.programiz.com/dsa/avl-tree poistamiseen ja korkeuden päivitys

*/
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

Solmu *uusiSolmu(int luku);
Solmu *vasenKierros(Solmu *juuri);
Solmu *oikeaKierros(Solmu *juuri);
Solmu *oikeaVasenKierros(Solmu *juuri,Solmu*paa);
Solmu *vasenOikeaKierros(Solmu *juuri,Solmu*paa);
Solmu *uusiSolmu(int luku);
Solmu *lisaaArvo(Solmu *pA,int luku,Solmu*paa);
Solmu *tyhjennys(Solmu *pA);
Solmu *lukeminen(Solmu *pA, char nimi[]);
void tulostaPuu(Solmu*pA, int vali);
void korkeusEro(Solmu *pA);
void suurempiPuoli(Solmu *solmu);
void kirjota(Solmu *pA, char nimi[]);
void kirjotaPuu(Solmu *pA, FILE *tiedosto,int vali); 
int etsiArvo(Solmu *pA,int arvo);
int valikko();
int tiedostonValinta();



void tulostaPuu(Solmu*pA, int vali) { 
	int i;
    if (pA != NULL) {
		/*väli on väli joka tulee kun tehdään puuta*/
	    vali += 15; 
	    tulostaPuu(pA->pOikea, vali);  /* tulostetaan ensin juuren oikea puoli sitten vasen*/
	   	printf("\n"); 
		/*tulostetaan välejä */
	    for (i = 15; i < vali; i++) {
			printf(" "); 
		}
		/*tulostetaan avain, korkeus ja tilakerroin*/
	    printf("%d(%d)(%d)\n", pA->arvo,pA->korkeus,pA->tila); 
	    tulostaPuu(pA->pVasen, vali); 
    }
} 
/*solmusta vasemman ja oikean puoleisen puun korkeus ero eli tilakerroin */
void korkeusEro(Solmu *pA){
	int korkeusEro = 0;

	/*jos on vasen/oikea solmu on tyhjä*/
	int vasenKorkeus = 0; 
	int oikeaKorkeus = 0;

	/*tulisi aina olla jotain mutta varmuuden vuoksi*/
	if(pA != NULL){
		/*onko olemassa*/
		if (pA->pVasen != NULL){
			vasenKorkeus = pA->pVasen->korkeus;
		}
		/*onko olemassa*/
		if (pA->pOikea != NULL){
			 oikeaKorkeus = pA->pOikea->korkeus;
		}
		/*lasektaan korkeus ero ja päivitetään solmun tilakerroin*/
		korkeusEro = vasenKorkeus - oikeaKorkeus;
		pA->tila = korkeusEro;		
	}
}
/*etsitään kumpi oiea vai vasen solmun puolista on korkeampi ja päivitetään solmun uusi korkeus*/
void suurempiPuoli(Solmu *solmu){
	int vasen_korkeus = 0;
	int oikea_korkeus = 0; /*oletuksena oikea puoli on suurin*/
	if (solmu != NULL){
		/*onko olemassa*/
		if(solmu->pOikea != NULL){
			oikea_korkeus = solmu->pOikea->korkeus;
		}
		/*onko olemassa*/
		if(solmu->pVasen != NULL){
			vasen_korkeus = solmu->pVasen->korkeus;
		}
		/*jos vasen suurempi */
		if(vasen_korkeus > oikea_korkeus){
			oikea_korkeus = vasen_korkeus;
		}
	}
	solmu->korkeus = oikea_korkeus + 1; /*päivitetään uusi korkeus */
}
/*tehdään vasen kierros eli kierretään oikealle kerran*/
Solmu *vasenKierros(Solmu *juuri){
	Solmu *lapsi;
	
	/*kierros*/
	lapsi = juuri->pVasen; /*uusi juuri*/
	juuri->pVasen = lapsi->pOikea;
	lapsi->pOikea = juuri;

	/*päivitetään juuren ja lapsen korkeus. Joka siis on suurempi oikeasta ja vasemmasta puolesta ja lisätään siihen 1 koska lisätiin uusi solmu*/
	suurempiPuoli(juuri);
	suurempiPuoli(lapsi);
	/*päivitetään juuren ja lapsen tila. Joka siis on erotus oikeasta ja vasemmasta puolesta */
	korkeusEro(juuri);
	korkeusEro(lapsi);

	/*uusi juuri on nyt lapsi*/
	juuri = lapsi;
	return juuri;
}
/*tehdäään oikea kieroos eli kierretään vasemmalle kerran*/
Solmu *oikeaKierros(Solmu *juuri){
	Solmu *lapsi;

	/*kierros*/
	lapsi = juuri->pOikea; /*uusi juuri*/
	juuri->pOikea = lapsi->pVasen;
	lapsi->pVasen = juuri;

	/*päivitetään juuren ja lapsen korkeus. Joka siis on suurempi oikeasta ja vasemmasta puolesta ja lisätään siihen 1 koska lisätiin uusi solmu*/
	suurempiPuoli(juuri);
	suurempiPuoli(lapsi);
	/*päivitetään juuren ja lapsen tila. Joka siis on erotus oikeasta ja vasemmasta puolesta */
	korkeusEro(juuri);
	korkeusEro(lapsi);

	/*uusi juuri on nyt lapsi*/
	juuri = lapsi;
	return juuri;
}
/*RL kierros eli tehdään  vasen kierros  solmu oikealle lapselle ja sitten sen perään oikea kierros*/
Solmu *oikeaVasenKierros(Solmu *juuri,Solmu *paa){
		/*suoritetaan juuren oikealle puolelle vasen kierros*/
		juuri->pOikea = vasenKierros(juuri->pOikea);
		printf("Puu vasemman kierron jalkeen ja ennen kiertoa oikealle:\n");
		tulostaPuu(paa,0);

		/*suoritetaan nyt juurelle oikeakierros, koska nyt puu on oikealle liika kallellaan*/
		juuri = oikeaKierros(juuri);
		printf("Puun kiertoja vaativa osa kietojen jalkeen:\n");
		tulostaPuu(juuri,0);
		printf("###########################\n");
		return juuri;
}
/*LR kierros*/
Solmu *vasenOikeaKierros(Solmu *juuri,Solmu *paa){
		/*suoritetaan juuren oikealle puolelle vasen kierros*/
		juuri->pVasen = oikeaKierros(juuri->pVasen);
		printf("Puu vasemman kierron jalkeen ja ennen kiertoa oikealle:\n");
		tulostaPuu(paa,0);

		/*suoritetaan nyt juurelle oikeakierros, koska nyt puu on vasemmalle liika kallellaan*/
		juuri = vasenKierros(juuri);
		printf("Puun kiertoja vaativa osa kietojen jalkeen:\n");
		tulostaPuu(juuri,0);
		printf("###########################\n");
		return juuri;
}
/*luodaan uusi solmu*/
Solmu *uusiSolmu(int luku){
	Solmu *ptr;
	/*varataan muistia*/
	if((ptr= (Solmu*)malloc(sizeof(Solmu))) == NULL){
		perror("Muistin varaus epäonnistui");
		exit(1);
	}
	ptr->arvo = luku;
	ptr->korkeus = 1; /*asetetaan korkeus*/
    ptr->tila = 0; /*asetetaan tila*/
	ptr->pVasen = NULL;
	ptr->pOikea = NULL;
	return ptr;
}
/*lisätään uusi arvo ja tarkastetaan puun tila*/
Solmu *lisaaArvo(Solmu *pA,int luku,Solmu *paa){
	/*jos solmu on tyhjä niin luodaan uusi solmu*/
	if(pA == NULL){
		pA = uusiSolmu(luku);
		return pA;
	}
	/*jos luku on pienemp kuin tarkasteltavan solmun arvo niin mennään puussa solmusta vasemmalle*/
	if(luku < pA->arvo){
		pA->pVasen = lisaaArvo(pA->pVasen,luku,paa);
	/*jos luku on suurempi tai yhtä suuri kuin tarkasteltava solmu niin mennään puussa solmusta oikealle*/
	}else if(luku > pA->arvo){
		pA->pOikea = lisaaArvo(pA->pOikea,luku,paa);
	/*jos luku on jo olemassa*/
	}else{
		printf("Luku on jo puussa\n");
		return pA;
	}
	/*päivitetään korkeus ja tila*/
	suurempiPuoli(pA);
	korkeusEro(pA);

	/*vasemmalla on liikkaa*/
	if(pA->tila > 1){
		/*vasen oikea tapaus eli vasemalla on liikaa mutta luku suurempi kuin vasemman arvo eli menisi sen oikealle puolelle--> käännetään vasenta puoleta kerran vasemmalle  ja sitten*/
		/* ja sitten solmua kerran oikealle*/
		if (luku > pA->pVasen->arvo){
			printf("Tehdaan LR kierto\n");
			printf("Puun kierron vaativa osa ennen  kiertoa:\n");
			tulostaPuu(paa,0);
			pA = vasenOikeaKierros(pA,paa);
			return pA;
		}else{/*vasen vasen tapaus eli vasemmalla on liikkaa ja menee vasemmalle--> lierretään kerran oikealle*/
			printf("Tehdaan LL kierto\n");
			printf("Puun kierron vaativa osa ennen kietoa:\n");
			tulostaPuu(paa,0);
			pA = vasenKierros(pA);
			
			printf("Puun kierron vaativa osa kierron jalkeen:\n");
			tulostaPuu(pA,0);
			printf("###########################\n");
			return pA;
		}
	}
	/*oikealla liikaa*/
	if(pA->tila < -1){
		/* oikea vasen tapaus eli oikealla on liikaa mutta luku pienempi kuin oikean arvo eli menisi sen vasemmalle puolelle--> käännetään oikeaa puoleta kerran oikealle */
		/* ja sitten solmua kerran vasemmalle*/
		if(luku < pA->pOikea->arvo){
			printf("Tehdaan RL kierto\n");
			printf("Puun kierron vaativa osa ennen   kiertoa:\n");
			tulostaPuu(paa,0);
			pA = oikeaVasenKierros(pA,paa);
			return pA;
		}else{/* oikea oikea tapaus eli oikealla liikaa ja menee oikealle-->kierretään kerran vasemmalle */
			printf("Tehdaan RR kierto\n");
			printf("Puun kierron vaativa osa ennen kiertoa:\n");
			tulostaPuu(paa,0);
			pA = oikeaKierros(pA);
			
			printf("Puun kierron vaativa osa kierron jalkeen:\n");
			tulostaPuu(pA,0);
			printf("###########################\n");
			return pA;
		}
	}	
	return pA;
}
/*tyhjennetään puu lista*/
Solmu *tyhjennys(Solmu *pA){
	if(pA != NULL){
		tyhjennys(pA->pVasen); /*tyhjenetään eka vasen puoli sitten oikea*/
		tyhjennys(pA->pOikea);
		printf("Poistetaan %d\n",pA->arvo);
		free(pA); 
		pA = NULL;
	}
    return pA;	
}
/*etsitään arvo*/
int etsiArvo(Solmu *pA,int arvo){
	printf("Ollaan solmussa on %d\n",pA->arvo);
	/*jos puun arvo on sama kuin etsittävä arvo palautetaan arvo*/
	if(arvo == pA->arvo){
		return pA->arvo;
	/*jos puun arvo on suurempi kuin etsittävä arvo niin mennään puun arvosta vasempaan solmuun*/
	}else if (arvo < pA->arvo){
		/*jos vasemmassa solmussa on jotain niin mennään sinne*/
		if(pA->pVasen!=NULL){
			/*etsitään arvo uudestaan nyt vasemmasta solmusta*/
			return etsiArvo(pA->pVasen,arvo);
		/*jos ei löytynyt*/
		}else{
			return 0;
		}
	/*jos puun arvo on pienempi kuin etsittävä arvo niin mennään puun arvosta oikeaan solmuun*/
	}else if (arvo > pA->arvo){
		/*jos oikeassa solmussa on jotain niin mennään sinne*/
		if(pA->pOikea != NULL){
			return etsiArvo(pA->pOikea,arvo);
		/*ei löynyt mitään*/
		}else{
			return 0;
		}
	}else{
		return 0;
	}
}
/*valikko ohjelmalle*/
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
/*luetaan tiedostosta avaimet ja lisätään ne puuhun*/
Solmu *lukeminen(Solmu *pA, char nimi[]){
    FILE *tiedosto;
    char arvo[20]; /*annoin vain jonkun koon */
    int avain;
	Solmu *paa;

	/*avataan tiedosto*/
    printf("Luetaan arvot tiedostosta %s\n",nimi);
    if ((tiedosto = fopen(nimi, "r")) == NULL){
		perror("Tiedoston lukeminen epäonnistui");
		exit(0);		
	}
	/*luetaan tiedostoa*/
    while (fgets(arvo,RIVI, tiedosto) != NULL){
		
		/*saadaan avain ja tehdään siitä kokonaisluku*/
        avain = atol(arvo); 
      
		
		/*lisätään avain*/
        printf("Lisataan luku %d\n",avain);
		paa = pA; /*tulostusta varten*/
		pA = lisaaArvo(pA, avain,paa);

		/*tulostetaan puu lisäyksen jälkeen*/
		printf("Puu lisatyn luvun (%d) jalkeen:\n",avain);
		tulostaPuu(pA,0);
		printf("###########################\n");
		
    }
	/*suljetaan tiedosto*/
    fclose(tiedosto);
    printf("Tiedosto  luettu ja avaimet tallennettu puuhun.\n");
    return pA;
}
/*valikko tiedostoille*/
int tiedostonValinta(){
	int valinta;
	printf("1) Alkuperainen tiedosto(10 avainta)\n");
    printf("2) 100 avainta\n");
    printf("3) 1000 avainta\n");
	printf("4) 10000 avainta\n");
	printf("5) 100000 avainta\n");
	printf("6) Oma esimerkki\n");
	printf("Valintasi: ");
	scanf("%d",&valinta);
	return valinta;
}
/*kirjoitetaan puu tiedostoon samaan tapaan kun se tulostettaisiin*/
void kirjotaPuu(Solmu *pA, FILE *tiedosto,int vali){
	int i;
	if (pA != NULL){
		vali += 10; 
	    kirjotaPuu(pA->pOikea, tiedosto,vali); 
	    fprintf(tiedosto,"\n"); 
	    for (i = 10; i < vali; i++) {
			fprintf(tiedosto," "); 
		}
	    fprintf(tiedosto,"%d(%d)(%d)\n", pA->arvo,pA->korkeus,pA->tila); 
	    kirjotaPuu(pA->pVasen, tiedosto,vali); 
    }
}
/*avataan tiedosto kirjoitusta varten ja lähetetäänse kirjoita puu funktioon jossa puu sitten kirjoitetaan*/
void kirjota(Solmu *pA, char nimi[]){
	FILE *tiedosto;
	/*avataan tiedoto*/
	if ((tiedosto = fopen(nimi, "w")) == NULL){
		perror("Tiedoston lukeminen epäonnistui");
		exit(0);		
	}
	kirjotaPuu(pA, tiedosto,0);
	/*suljtetaan tiedosto*/
	fclose(tiedosto);
}
int main(void){
    Solmu *pA = NULL;
	Solmu *paa;
    char tiedosto[100] = "arvot.txt";
	char puu_tiedosto[100] = "puutiedosto.txt";
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
				printf("\nMika tiedosto\n");
				tiedoston_valinta = tiedostonValinta();
				/*hard codasin nämä tiedoston nimet koska en jakssanu aina kirjoitaa niitä kun testasin ohjelmaa*/
				/*printtejen kanssa yli 100 avain tidostossa kestää erittäin pitkää kun kaikki välivaiheet printataan*/
				switch (tiedoston_valinta){
					case 1:
						strcpy(tiedosto,"arvot.txt");
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
						strcpy(tiedosto,"arvot_100000.txt"); /*aika reilu 14h printteineen VScodessa*/
						break;
					case 6:
						strcpy(tiedosto,"arvot_oma.txt");
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
				printf("Lisaa avaimia puuhun ensin\n");
			}
            break;
        case 3:
            printf("Anna lisattava avain:");
            scanf("%d",&lisattava_avain);
			paa = pA;
            pA = lisaaArvo(pA,lisattava_avain,paa);
			printf("Puu lisatyn avaimen jalkeen\n");
			tulostaPuu(pA,0);
            break;
        case 4:
			if(pA != NULL){
				printf("Tulostetaan puu");
				tulostaPuu(pA,0);
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

	return 0;
}



