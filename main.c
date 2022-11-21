/********************************************************************************
* main.c: Demonstration av strukt i C för implementering av dynamiska vektorer
*         för lagring och utskrift av heltal.
********************************************************************************/
#include "int_vector.h"

/********************************************************************************
* main: Deklarerar och initierar två vektorer v1 och v2, varav v1 allokeras 
*       automatiskt och v2 dynamiskt. Filen numbers.txt öppnas för skrivning. 
* 
*       Vektor v1 fylls med tio heltal med startvärde 0 och stegvärde 2.
*       Vektor v2 fylls med 200 heltal med startvärde 100 och stegvärde -1.
* 
*       Det sista talet i vektor v1 tas bort med en pop-operation.
*       Vektor v2 tilldelas heltalet 1000 längst bak med en push-operation.
* 
*       Vektorernas innehåll skrivs ut både i terminalen samt till filen 
*       numbers.txt. Innan programmet avslutas frigörs allokerat minne för
*       vektorerna.
********************************************************************************/
int main(void)
{
   struct int_vector v1, *v2;
   FILE* ostream = fopen("numbers.txt", "w");

   int_vector_init(&v1);
   v2 = int_vector_new();

   int_vector_resize(&v1, 10);
   int_vector_resize(v2, 20);

   int_vector_assign(&v1, 0, 2);
   int_vector_assign(v2, 100, -1);
  
   int_vector_pop(&v1);
   int_vector_push(v2, 1000);

   int_vector_print(&v1, 0);
   int_vector_print(v2, 0);

   int_vector_print(&v1, ostream);
   int_vector_print(v2, ostream);

   int_vector_clear(&v1);
   int_vector_delete(&v2);
   return 0;
}