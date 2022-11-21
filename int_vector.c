/********************************************************************************
* int_vector.h: Innehåller definitioner av associerade externa funktioner för
*               strukten int_vector.
********************************************************************************/
#include "int_vector.h"

/********************************************************************************
* int_vector_resize: Ändrar storleken på angiven dynamisk vektor. Vid lyckad
*                    minnesallokering returneras 0, annars returneras felkod 1.
*
*                    - self: Pekare till den vektor vars storlek ska ändras.
*                    - size: Vektorns storlek efter omallokeringen.
********************************************************************************/
int int_vector_resize(struct int_vector* self,
                      const size_t size)
{
   if (size == 0)
   {
      int_vector_clear(self);
      return 0;
   }
   else
   {
      int* copy = (int*)realloc(self->data, sizeof(int) * size);
      if (!copy) return 1;
      self->data = copy;
      self->size = size;
      return 0;
   }
}

/********************************************************************************
* int_vector_push: Lägger till ett nytt heltal längst bak i angiven vektor.
*                  Om minnesallokeringen lyckas så returneras 0, annars felkod 1.
*
*                  - self: Pekare till vektorn som ska tilldelas det nya talet.
*                  - num : Det nya tal som ska läggas till.
********************************************************************************/
int int_vector_push(struct int_vector* self,
                    const int num)
{
   int* copy = (int*)realloc(self->data, sizeof(int) * (self->size + 1));
   if (!copy) return 1;
   copy[self->size++] = num;
   self->data = copy;
   return 0;
}

/********************************************************************************
* int_vector_pop: Tar bort sista heltalet i angiven vektor. Om minnesallokeringen
*                 lyckas så returneras 0, annars felkod 1.
*
*                 - self: Pekare till vektorn vars sista heltal ska tas bort.
********************************************************************************/
int int_vector_pop(struct int_vector* self)
{
   if (self->size <= 1)
   {
      int_vector_clear(self);
      return 0;
   }
   else
   {
      int* copy = (int*)realloc(self->data, sizeof(int) * (self->size - 1));
      if (!copy) return 1;
      self->data = copy;
      self->size--;
      return 0;
   }
}

/********************************************************************************
* int_vector_assign: Tilldelar heltal till angiven vektor med godtyckligt
*                    start- och stegvärde.
*
*                    - self     : Pekare till vektorn som ska tilldelas.
*                    - start_val: Startvärde för tilldelningen.
*                    - step_val : Stegvärde, dvs. differensen mellan varje tal.
********************************************************************************/
void int_vector_assign(struct int_vector* self,
                       const int start_val,
                       const int step_val)
{
   int num = start_val;

   for (int* i = int_vector_begin(self); i < int_vector_end(self); ++i)
   {
      *i = num;
      num += step_val;
   }

   return;
}

/********************************************************************************
* int_vector_print: Skriver ut heltal lagrade i angiven vektor via godtycklig
*                   utström, där standardutenheten stdout används som default
*                   för utskrift i terminalen.
*
*                   - self   : Pekare till vektorn som ska tilldelas.
*                   - ostream: Pekare till godtycklig utström (default = stdout).
********************************************************************************/
void int_vector_print(const struct int_vector* self,
                      FILE* ostream)
{
   if (self->size == 0) return;
   if (!ostream) ostream = stdout;

   fprintf(ostream, "--------------------------------------------------------------------------------\n");

   for (const int* i = int_vector_begin(self); i < int_vector_end(self); ++i)
   {
      fprintf(ostream, "%d\n", *i);
   }

   fprintf(ostream, "--------------------------------------------------------------------------------\n\n");
   return;
}