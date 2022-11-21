/********************************************************************************
* func.c: Demonstration av dynamisk minnesallokering i C, vilket inneb�r minne
*         som kan allokeras och deallokeras (frig�ras) fr�n en pool med minne
*         kallad heapen (eller DRAM, dynamic RAM memory). 
*
*         Dynamisk minnesallokering genomf�rs i C prim�rt via de tre funktionerna
*         malloc (f�r ny minnesallokering), realloc (f�r omallokering av
*         befintligt minne) samt free (f�r deallokering/frig�rande av minne).
*         Dessa funktioner �r deklarerade i standardbiblioteket stdlib.h, som
*         d�rmed m�ste inkluderas.
* 
*      1. Funktionen malloc anv�nds f�r att allokera minne och returnera
*         en pekare till detta minne enligt nedan:
* 
*         <datatyp>* pekare = (datatyp*)malloc(<m�ngden minne i byte>);
*          
*         Som exempel, f�r att allokera ett f�lt (en array) som rymmer 20 heltal
*         av datatypen int (4 byte per int, allts� totalt 4 x 20 = 80 byte) och
*         l�ta en pekare d�pt data peka p� detta f�lt, s� kan f�ljande 
*         instruktion anv�ndas:
* 
*         int* data = (int*)malloc(80);
* 
*         F�r att slippa r�kna antalet byte manuellt s� anv�nds normalt
*         sizeof-operatorn, som i detta fall anv�nds f�r att returnera storleken
*         p� en int. Vi allokerar d�rmed storleken av en int x 20, vilket medf�r
*         att minne allokeras f�r 20 variabler av datatypen int:
* 
*         int* data = (int*)malloc(sizeof(int) * 20);
* 
*         Funktionen malloc returnerar en voidpekare, vilket inneb�r en
*         generell pekare. Detta har gjort s� att funktionen malloc kan anv�ndas
*         f�r att returnera en pekare av godtycklig datatyp. Se till att 
*         typomvandla detta returv�rde till �nskad datatyp, i detta fall en
*         intpekare, via en explicit typomvandling (int*). Det fungerar att
*         inte g�ra detta i C (�ven om det �r d�lig kutym), men vid programmering
*         i C++ erh�lls d� ett kompilatorfel (implicit typomvandling fr�n void*
*         till int*).
* 
*         N�r funktionen malloc anropas s� sker ett f�rs�k att allokera �nskad
*         m�ngd minne. Detta lyckas om det finns en tillr�cklig m�ngd konsekutivt
*         minne p� heapen. Annars returneras en nullpekare. Kontrollera alltid
*         returv�rdet fr�n funktionen malloc. Om null retureras s� f�r ni 
*         hantera detta utefter vad ni finner l�mpligt. I detta program avslutas
*         programmet om detta sker enligt nedan:
* 
*         if (!data) return 1;
* 
*         Det g�r ocks� att skriva if (data == 0) eller if (data == NULL).
* 
*      2. Funktionen realloc anv�nds f�r att omallokera ett befintligt f�lt
*         enligt nedan:
* 
*         <datatyp>* pekare = (datatyp*)realloc(
*            <pekare till minnet som ska omallokeras>, <m�ngden minne i byte>);
* 
*         Som exempel, f�r att omallokera det f�lt som pekaren data ovan pekar
*         p� s� att det rymmer 40 heltal och l�ta en kopiapekare peka p� det
*         omallokerade f�ltet kan f�ljande instruktion anv�ndas:
* 
*         int* copy = (int*)realloc(data, sizeof(int) * 40);
*          
*         Vid lyckad omallokering frig�rs det gamla minnet om detta ligger
*         p� en annan adress, vilket d�rmed inte beh�ver g�ras manuellt.
*         Vid misslyckad minnesallokering returneras null, precis som f�r
*         funktionen malloc. F�r att undvika att skriva �ver adressen till
*         det gamla f�ltet med null s� b�r en kopiapekare ta emot returv�rdet
*         fr�n realloc (adressen till det nya f�ltet). Endast vid lyckad
*         omallokering (returv�rdet �r inte lika med null) b�r pekaren till
*         det ursprungliga f�ltet s�ttas till att peka p� adressen till det
*         nya f�ltet (den adress kopiapekaren pekar p�). Annars ifall
*         minnesallokeringen misslyckas s� bibeh�lls adressen till det gamla 
*         f�ltet, d� kopiapekaren tog emot null fr�n funktionen realloc.
*         Se i programmet nedan hur en pekare d�pt copy anv�nds f�r att 
*         omallokera ett f�lt som pekas p� av en pekare d�pt data:
* 
*      3. Funktionen free anv�nds f�r att frig�ra/deallokera dynamiskt 
*         allokerat minne enligt nedan:
* 
*         free(<pekare till minnet som ska frig�ras>);
* 
*         Som exempel, f�r att frig�ra det minne som pekas p� av pekaren data
*         ovan kan f�ljande instruktion anv�ndas:
* 
*         free(data);
* 
*         Viktigt �r att alltid s�tta pekaren till minnet till null efter
*         deallokeringen. Annars forts�tter pekaren att pekar p� den adress
*         d�r minnet tidigare l�g. Detta kan bjuda in misstag, exempelvis
*         att vi r�kar genomf�rs tilldelning till denna adress, vilket kan
*         medf�ra att programmet kraschar. En s�dan pekare kallas dangling 
*         pointer och b�r allts� undvikas. 
*
*         Pekaren data ovan kan s�ttas till null genom att tilldela denna adressen 0:
* 
*         data = 0;
* 
*         Alternativt kan makrot NULL anv�ndas:
* 
*         data = NULL;        
********************************************************************************/
#include <stdio.h>  /*Inneh�ller printf, FILE* med mera. */
#include <stdlib.h> /* Inneh�ller malloc, realloc, free med mera. */

/********************************************************************************
* int_array_new: Returnerar pekare till ett dynamiskt allokerat f�lt av angiven
*                storlek. Om minnesallokeringen misslyckas s� returneras null.
*
*                - size: F�ltets storlek, dvs. antal heltal det ska rymma.
********************************************************************************/
static inline int* int_array_new(const size_t size)
{
   return (int*)malloc(sizeof(int) * size);
}

/********************************************************************************
* int_array_delete: Frig�r minne allokerat f�r angivet f�lt och s�tter 
*                   motsvarande datapekare till null. F�r att �ndra den adress
*                   som datapekaren pekar p� s� passeras en dubbelpekare, som
*                   pekar adressen till denna datapekare, annars kommer det 
*                   fram en kopia, vilket medf�r att vi inte kan �ndra adressen
*                   som ordinarie pekare pekar p�.
*
*                   - data: Adressen till datapekaren som pekar p� f�ltet
*                           som ska frig�ras.
********************************************************************************/
static inline void int_array_delete(int** data)
{
   free(*data);
   *data = 0;
   return;
}

/********************************************************************************
* int_array_resize: �ndrar storleken p� angivet f�lt till ny angiven storlek.
*                   Om minnesallokeringen lyckas s� uppdateras arrayens storlek
*                   och returkod 0 returneras. Vid misslyckad minnesallokering
*                   returneras felkod 1, ordinarie array kommer vara intakt.
*                   
*                   F�r att kunna �ndra den adress som datapekaren pekar p�
*                   s� skickas dess adress (annars kommer det fram en kopia,
*                   vilket medf�r att vi inte kan �ndra adressen som originalet
*                   pekar p�).
*
*                   - data    : Adressen till den datapekare som pekar p� f�ltet.
*                   - size    : Pekare till variabel som lagrar f�ltets storlek.
*                   - new_size: F�ltets nya storlek efter omallokering.
********************************************************************************/
static int int_array_resize(int** data, 
                            size_t* size,
                            const size_t new_size)
{
   int* copy = (int*)realloc(*data, sizeof(int) * new_size);
   if (!copy) return 1;
   *data = copy;
   *size = new_size;
   return 0;
}

/********************************************************************************
* int_array_assign: Tilldelar heltal till angiven array med angivet stegv�rde.
* 
*                   - data: Pekare till arrayen.
*                   - size: Arrayens storlek, dvs. antalet heltal den rymmer.
*                   - step: Stegv�rdet, dvs. differensen mellan varje tal.
********************************************************************************/
static void int_array_assign(int* data,
                             const size_t size,
                             const int step)
{
   for (int i = 0; i < size; ++i)
   {
      data[i] = i * step;
   }

   return;
}

/********************************************************************************
* int_array_print: Skriver ut heltal lagrade i angiven array via angiven utstr�m,
*                  d�r standardutenhet stdout anv�nds som default f�r utskrift
*                  i terminalen.
* 
*                  - data   : Pekare till arrayen vars inneh�ll ska skrivas ut.
*                  - size   : Arrayens storlek, dvs. antalet heltal den rymmer.
*                  - ostream: Pekare till angiven utstr�m (default = stdout).
********************************************************************************/
static void int_array_print(const int* data,
                            const size_t size,
                            FILE* ostream)
{
   if (size == 0) return;
   if (!ostream) ostream = stdout;

   fprintf(ostream, "--------------------------------------------------------------------------------\n");

   for (size_t i = 0; i < size; ++i)
   {
      fprintf(ostream, "%d\n", data[i]);
   }

   fprintf(ostream, "--------------------------------------------------------------------------------\n\n");
   return;
}


/********************************************************************************
* main: Allokerar minne f�r en dynamisk array som rymmer 20 heltal. Ifall
*       minnesallokeringen misslyckas s� returneras felkod 1. Annars tilldelas
*       heltal med stegv�rdet 2 (0, 2, 4, 6... 38), f�ljt av utskrift i 
*       terminalen. 
* 
*       D�refter omallokeras arrayen till att rymma 40 heltal. Ifall
*       omallokeringen lyckas s� tilldelas heltal med stegv�rde -2 (0, -2, -4,
*       -6... -38) l�ngst bak i arrayen utan att skriva �ver tidigare inneh�ll. 
*       Inneh�llet skrivs sedan ut i terminalen.
* 
*       Innan programmet avslutas frig�rs det allokerade minnet.
********************************************************************************/
int main(void)
{
   int* data = int_array_new(20);
   size_t size = 20;
   if (!data) return 1;

   int_array_assign(data, 20, 2);
   int_array_print(data, 20, 0);

   FILE* ostream = fopen("numbers.txt", "w");

   if (int_array_resize(&data, &size, 40) == 0)
   {
      int_array_assign(data + 20, 20, -2);
      int_array_print(data, size, 0);
      int_array_print(data, size, ostream);
   }

   int_array_delete(&data);
   fclose(ostream);
   return 0;
}