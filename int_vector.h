/********************************************************************************
* int_vector.h: Innehåller funktionalitet för lagring samt utskrift av 
*               dynamiska arrayer innehållande heltal via strukten int_vector
*               samt associerade funktioner.
********************************************************************************/
#ifndef INT_VECTOR_H_
#define INT_VECTOR_H_

/* Inkluderingsdirektiv: */
#include <stdio.h>  /* Innehåller printf, FILE* med mera. */
#include <stdlib.h> /* Innehåller malloc, realloc och free. */

/********************************************************************************
* int_vector: Strukt för dynamiska arrayer (vektorer) innehållande heltal.
********************************************************************************/
struct int_vector
{
   int* data;   /* Pekare till det dynamiska fältet (arrayen). */
   size_t size; /* Vektorns storlek, dvs. antalet heltal den rymmer. */
};

/********************************************************************************
* int_vector_init: Initierar ny tom dynamisk vektor.
* 
*                  - self: Pekare till den vektor som ska initieras.
********************************************************************************/
static inline void int_vector_init(struct int_vector* self)
{
   self->data = 0;
   self->size = 0;
   return;
}

/********************************************************************************
* int_vector_clear: Tömmer angiven dynamisk vektor.
*
*                   - self: Pekare till den vektor som ska tömmas.
********************************************************************************/
static inline void int_vector_clear(struct int_vector* self)
{
   free(self->data);
   int_vector_init(self);
   return;
}

/********************************************************************************
* int_vector_new: Returnerar en pekare till en ny dynamiskt allokerad vektor,
*                 som initieras till tom vid start. Om minnesallokeringen
*                 misslyckas returneras null.
********************************************************************************/
static inline struct int_vector* int_vector_new(void)
{
   struct int_vector* self = (struct int_vector*)malloc(sizeof(struct int_vector));
   if (!self) return 0;
   int_vector_init(self);
   return self;
}

/********************************************************************************
* int_vector_delete: Raderar angiven dynamiskt allokerad vektor och sätter
*                    vektorpekaren till null.
* 
*                    - self: Adressen till vektorpekaren.
********************************************************************************/
static inline void int_vector_delete(struct int_vector** self)
{
   int_vector_clear(*self);
   free(*self);
   *self = 0;
   return;
}

/********************************************************************************
* int_vector_begin: Returnerar adressen till första elementet i angiven vektor.
*                   Om vektorn är tom returneras null.
* 
*                   - self: Pekare till vektorn.
********************************************************************************/
static inline int* int_vector_begin(const struct int_vector* self)
{
   return self->data;
}

/********************************************************************************
* int_vector_end: Returnerar adressen efter sista elementet i angiven vektor.
*                 Om vektorn är tom returneras null.
*
*                 - self: Pekare till vektorn.
********************************************************************************/
static inline int* int_vector_end(const struct int_vector* self)
{
   return self->data + self->size;
}

/********************************************************************************
* int_vector_last: Returnerar adressen till sista elementet i angiven vektor.
*                  Om vektorn är tom returneras null.
*
*                  - self: Pekare till vektorn.
********************************************************************************/
static inline int* int_vector_last(const struct int_vector* self)
{
   return self->size > 0 ? int_vector_end(self) - 1 : 0;
}

/********************************************************************************
* int_vector_resize: Ändrar storleken på angiven dynamisk vektor. Vid lyckad
*                    minnesallokering returneras 0, annars returneras felkod 1.
*
*                    - self: Pekare till den vektor vars storlek ska ändras.
*                    - size: Vektorns storlek efter omallokeringen.
********************************************************************************/
int int_vector_resize(struct int_vector* self,
                      const size_t size);

/********************************************************************************
* int_vector_push: Lägger till ett nytt heltal längst bak i angiven vektor.
*                  Om minnesallokeringen lyckas så returneras 0, annars felkod 1.
*
*                  - self: Pekare till vektorn som ska tilldelas det nya talet.
*                  - num : Det nya tal som ska läggas till.
********************************************************************************/
int int_vector_push(struct int_vector* self,
                    const int num);

/********************************************************************************
* int_vector_pop: Tar bort sista heltalet i angiven vektor. Om minnesallokeringen 
*                 lyckas så returneras 0, annars felkod 1.
*
*                 - self: Pekare till vektorn vars sista heltal ska tas bort.
********************************************************************************/
int int_vector_pop(struct int_vector* self);

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
                       const int step_val);

/********************************************************************************
* int_vector_print: Skriver ut heltal lagrade i angiven vektor via godtycklig
*                   utström, där standardutenheten stdout används som default
*                   för utskrift i terminalen.
*
*                   - self   : Pekare till vektorn som ska tilldelas.
*                   - ostream: Pekare till godtycklig utström (default = stdout).
********************************************************************************/
void int_vector_print(const struct int_vector* self,
                      FILE* ostream);

#endif /* INT_VECTOR_H_ */