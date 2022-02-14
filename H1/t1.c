#include <stdio.h> 
#include <string.h>
/*Jesse Mustonen, 0541805*/
int main(int argc, char *argv[]) 
{ 
  	char **ap = argv + 1; 
  	char **ep = argv + argc;
	
  	printf("# of args: %5d\n", argc-1);

  for ( ; ap < ep ; ap++ ) {

      	printf("%d, %s\n", strlen(*ap), *ap);
    
  } 

return 0;
} 





/*
Esimerkki ajo:   ./t1 Turing Church Aho Hanoi RSA

Ohjelma ottaa sisään käyttäjän antamia argumentteja komentoriviltä
int main(int argc, char *argv[]) jossa argc on komentorivi parametrien määrä ja argv[] on osoitintaulukko jossa on komentoriviltä saatujen parametrien osoittimet argumentteihin

Luodaan pointterin poitteri ap ja  lisätään siihen  1 alussa jottei tulisi ohjelman nimeä mukaan eli se aloittaa osoittamaan toisesta argumentista ja sen arvo on toisen argumentin osoittama muistipaikka 
char **ap = argv + 1;  --> eli siis esimerkkiajossa Turing:n muistipaikka


Luodaan poitterin pointteri ep ja jonka arvo on argv[] osoitintaulukon viimeinen osoite, koska kun argv(eli nyt ensimmäisen argumentin muistipaikka) lisätään argc(kaikkien argumenttien määrä) saadaan viimeisen  argumentin muistipaikka
char **ep = argv + argc;


Ohjelma tulostaa ensiksi kuinka monta argumenttia käyttäjä on antanut. Yksi vähennetään siksi jottei ohjelman nimeä tule mukaan 
printf("# of args: %5d\n", argc-1);

# of args:     5


For loopia suooritetaan niin pitkään(lisäämällä ap:hen 1) ennen kuin ap saavuttaa ep ja ollaan tultu taulukon loppuun. Eli siis ap<ep vertailee muistipaikkoja
ja loopissa tulostetaan annettujen parametrien pituus(strlen(*ap)) ja mitä ne ovat(*ap)
*ap saadaan osoittimen sisältämä merkkijono 
esimerkkajo:
for ( ; ap < ep ; ap++ )


6, Turing
6, Church
3, Aho
5, Hanoi
3, RSA


Tietorakenteet

Taulukko
argv[] on taulukko osoittimia jotka ovat merkkijonoja


*/
