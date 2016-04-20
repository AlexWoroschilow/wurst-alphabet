
/*
 *
 *	citation.h
 *  Beertime!
 * 
 *  @author Steve Hoffmann, steve@bioinf.uni-leipzig.de
 *  @company Bioinformatics, University of Leipzig 
 *  @date 07/25/2007 10:50:10 PM CEST  
 *
 */

#include <stdlib.h>
#include <time.h>

 char* cite[] = { "\"Beertime!\" (A. Torda)\0", 
                 "\"Ick fahr nur noch die janz jrossen Poette, wa!\" (Apotheker Lenz)\0",
                 "\"Nochn' schoenes Bier verhaften?\" (M. Mosisch)\0",
                 "\"Mahlzeit!\" (Ditsche, Ingo, Schildkroede)\0",
                 "\"Halt die Klappe, ich hab' Feierabend.\" (Schildkroede)\0"
                 "\"Gehen Sie vorsichtig mit dem Begriff der Unendlichkeit um!\" (Shorty)\0",
                 "\"Die Ficker!\" (Thommy)\0",
                 "\"Hab' ich gerade inner Bild gelesen!\" (Bienchen)\0",
                 "\"Tschüss, Herr Kayser!\" (Shorty)\0",
                 "\"Ich bin neu in der Hamburger Schule\" (Tocotronic)\0",
                 "\"Es wäre nicht zum aushalten, wäre er echt\" (Kettcar)\0",
                 "\"Stefan Kurtz uses suffix arrays to fix his bike.\" (A. Torda)\0",
                 "\"Ich hol' jetzt die Hilti!\" (Ein verzweifelter Bauarbeiter)\0"
                 "\"Käff'chen?\" (Lars)\0"}; 


 unsigned citenumber = 12;

 char* citerand() { 
   srand(time(NULL)); 
   return cite[((unsigned)rand()%(int)(citenumber))];
 }


