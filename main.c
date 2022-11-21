/********************************************************************************
* main.c: Demonstration av strukt i C f�r implementering av dynamiska vektorer
*         f�r lagring och utskrift av heltal.
********************************************************************************/
#include "int_vector.h"

/********************************************************************************
* main: Deklarerar och initierar tv� vektorer v1 och v2, varav v1 allokeras 
*       automatiskt och v2 dynamiskt. Filen numbers.txt �ppnas f�r skrivning. 
* 
*       Vektor v1 fylls med tio heltal med startv�rde 0 och stegv�rde 2.
*       Vektor v2 fylls med 200 heltal med startv�rde 100 och stegv�rde -1.
* 
*       Det sista talet i vektor v1 tas bort med en pop-operation.
*       Vektor v2 tilldelas heltalet 1000 l�ngst bak med en push-operation.
* 
*       Vektorernas inneh�ll skrivs ut b�de i terminalen samt till filen 
*       numbers.txt. Innan programmet avslutas frig�rs allokerat minne f�r
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