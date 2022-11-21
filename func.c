/********************************************************************************
* func.c: Demonstration av dynamisk minnesallokering i C, vilket innebär minne
*         som kan allokeras och deallokeras (frigöras) från en pool med minne
*         kallad heapen (eller DRAM, dynamic RAM memory). 
*
*         Dynamisk minnesallokering genomförs i C primärt via de tre funktionerna
*         malloc (för ny minnesallokering), realloc (för omallokering av
*         befintligt minne) samt free (för deallokering/frigörande av minne).
*         Dessa funktioner är deklarerade i standardbiblioteket stdlib.h, som
*         därmed måste inkluderas.
* 
*      1. Funktionen malloc används för att allokera minne och returnera
*         en pekare till detta minne enligt nedan:
* 
*         <datatyp>* pekare = (datatyp*)malloc(<mängden minne i byte>);
*          
*         Som exempel, för att allokera ett fält (en array) som rymmer 20 heltal
*         av datatypen int (4 byte per int, alltså totalt 4 x 20 = 80 byte) och
*         låta en pekare döpt data peka på detta fält, så kan följande 
*         instruktion användas:
* 
*         int* data = (int*)malloc(80);
* 
*         För att slippa räkna antalet byte manuellt så används normalt
*         sizeof-operatorn, som i detta fall används för att returnera storleken
*         på en int. Vi allokerar därmed storleken av en int x 20, vilket medför
*         att minne allokeras för 20 variabler av datatypen int:
* 
*         int* data = (int*)malloc(sizeof(int) * 20);
* 
*         Funktionen malloc returnerar en voidpekare, vilket innebär en
*         generell pekare. Detta har gjort så att funktionen malloc kan användas
*         för att returnera en pekare av godtycklig datatyp. Se till att 
*         typomvandla detta returvärde till önskad datatyp, i detta fall en
*         intpekare, via en explicit typomvandling (int*). Det fungerar att
*         inte göra detta i C (även om det är dålig kutym), men vid programmering
*         i C++ erhålls då ett kompilatorfel (implicit typomvandling från void*
*         till int*).
* 
*         När funktionen malloc anropas så sker ett försök att allokera önskad
*         mängd minne. Detta lyckas om det finns en tillräcklig mängd konsekutivt
*         minne på heapen. Annars returneras en nullpekare. Kontrollera alltid
*         returvärdet från funktionen malloc. Om null retureras så får ni 
*         hantera detta utefter vad ni finner lämpligt. I detta program avslutas
*         programmet om detta sker enligt nedan:
* 
*         if (!data) return 1;
* 
*         Det går också att skriva if (data == 0) eller if (data == NULL).
* 
*      2. Funktionen realloc används för att omallokera ett befintligt fält
*         enligt nedan:
* 
*         <datatyp>* pekare = (datatyp*)realloc(
*            <pekare till minnet som ska omallokeras>, <mängden minne i byte>);
* 
*         Som exempel, för att omallokera det fält som pekaren data ovan pekar
*         på så att det rymmer 40 heltal och låta en kopiapekare peka på det
*         omallokerade fältet kan följande instruktion användas:
* 
*         int* copy = (int*)realloc(data, sizeof(int) * 40);
*          
*         Vid lyckad omallokering frigörs det gamla minnet om detta ligger
*         på en annan adress, vilket därmed inte behöver göras manuellt.
*         Vid misslyckad minnesallokering returneras null, precis som för
*         funktionen malloc. För att undvika att skriva över adressen till
*         det gamla fältet med null så bör en kopiapekare ta emot returvärdet
*         från realloc (adressen till det nya fältet). Endast vid lyckad
*         omallokering (returvärdet är inte lika med null) bör pekaren till
*         det ursprungliga fältet sättas till att peka på adressen till det
*         nya fältet (den adress kopiapekaren pekar på). Annars ifall
*         minnesallokeringen misslyckas så bibehålls adressen till det gamla 
*         fältet, då kopiapekaren tog emot null från funktionen realloc.
*         Se i programmet nedan hur en pekare döpt copy används för att 
*         omallokera ett fält som pekas på av en pekare döpt data:
* 
*      3. Funktionen free används för att frigöra/deallokera dynamiskt 
*         allokerat minne enligt nedan:
* 
*         free(<pekare till minnet som ska frigöras>);
* 
*         Som exempel, för att frigöra det minne som pekas på av pekaren data
*         ovan kan följande instruktion användas:
* 
*         free(data);
* 
*         Viktigt är att alltid sätta pekaren till minnet till null efter
*         deallokeringen. Annars fortsätter pekaren att pekar på den adress
*         där minnet tidigare låg. Detta kan bjuda in misstag, exempelvis
*         att vi råkar genomförs tilldelning till denna adress, vilket kan
*         medföra att programmet kraschar. En sådan pekare kallas dangling 
*         pointer och bör alltså undvikas. 
*
*         Pekaren data ovan kan sättas till null genom att tilldela denna adressen 0:
* 
*         data = 0;
* 
*         Alternativt kan makrot NULL användas:
* 
*         data = NULL;        
********************************************************************************/
#include <stdio.h>  /*Innehåller printf, FILE* med mera. */
#include <stdlib.h> /* Innehåller malloc, realloc, free med mera. */

/********************************************************************************
* int_array_new: Returnerar pekare till ett dynamiskt allokerat fält av angiven
*                storlek. Om minnesallokeringen misslyckas så returneras null.
*
*                - size: Fältets storlek, dvs. antal heltal det ska rymma.
********************************************************************************/
static inline int* int_array_new(const size_t size)
{
   return (int*)malloc(sizeof(int) * size);
}

/********************************************************************************
* int_array_delete: Frigör minne allokerat för angivet fält och sätter 
*                   motsvarande datapekare till null. För att ändra den adress
*                   som datapekaren pekar på så passeras en dubbelpekare, som
*                   pekar adressen till denna datapekare, annars kommer det 
*                   fram en kopia, vilket medför att vi inte kan ändra adressen
*                   som ordinarie pekare pekar på.
*
*                   - data: Adressen till datapekaren som pekar på fältet
*                           som ska frigöras.
********************************************************************************/
static inline void int_array_delete(int** data)
{
   free(*data);
   *data = 0;
   return;
}

/********************************************************************************
* int_array_resize: Ändrar storleken på angivet fält till ny angiven storlek.
*                   Om minnesallokeringen lyckas så uppdateras arrayens storlek
*                   och returkod 0 returneras. Vid misslyckad minnesallokering
*                   returneras felkod 1, ordinarie array kommer vara intakt.
*                   
*                   För att kunna ändra den adress som datapekaren pekar på
*                   så skickas dess adress (annars kommer det fram en kopia,
*                   vilket medför att vi inte kan ändra adressen som originalet
*                   pekar på).
*
*                   - data    : Adressen till den datapekare som pekar på fältet.
*                   - size    : Pekare till variabel som lagrar fältets storlek.
*                   - new_size: Fältets nya storlek efter omallokering.
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
* int_array_assign: Tilldelar heltal till angiven array med angivet stegvärde.
* 
*                   - data: Pekare till arrayen.
*                   - size: Arrayens storlek, dvs. antalet heltal den rymmer.
*                   - step: Stegvärdet, dvs. differensen mellan varje tal.
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
* int_array_print: Skriver ut heltal lagrade i angiven array via angiven utström,
*                  där standardutenhet stdout används som default för utskrift
*                  i terminalen.
* 
*                  - data   : Pekare till arrayen vars innehåll ska skrivas ut.
*                  - size   : Arrayens storlek, dvs. antalet heltal den rymmer.
*                  - ostream: Pekare till angiven utström (default = stdout).
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
* main: Allokerar minne för en dynamisk array som rymmer 20 heltal. Ifall
*       minnesallokeringen misslyckas så returneras felkod 1. Annars tilldelas
*       heltal med stegvärdet 2 (0, 2, 4, 6... 38), följt av utskrift i 
*       terminalen. 
* 
*       Därefter omallokeras arrayen till att rymma 40 heltal. Ifall
*       omallokeringen lyckas så tilldelas heltal med stegvärde -2 (0, -2, -4,
*       -6... -38) längst bak i arrayen utan att skriva över tidigare innehåll. 
*       Innehållet skrivs sedan ut i terminalen.
* 
*       Innan programmet avslutas frigörs det allokerade minnet.
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