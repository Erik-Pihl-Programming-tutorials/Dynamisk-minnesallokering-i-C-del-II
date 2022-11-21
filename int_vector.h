/********************************************************************************
* int_vector.h: Inneh�ller funktionalitet f�r lagring samt utskrift av 
*               dynamiska arrayer inneh�llande heltal via strukten int_vector
*               samt associerade funktioner.
********************************************************************************/
#ifndef INT_VECTOR_H_
#define INT_VECTOR_H_

/* Inkluderingsdirektiv: */
#include <stdio.h>  /* Inneh�ller printf, FILE* med mera. */
#include <stdlib.h> /* Inneh�ller malloc, realloc och free. */

/********************************************************************************
* int_vector: Strukt f�r dynamiska arrayer (vektorer) inneh�llande heltal.
********************************************************************************/
struct int_vector
{
   int* data;   /* Pekare till det dynamiska f�ltet (arrayen). */
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
* int_vector_clear: T�mmer angiven dynamisk vektor.
*
*                   - self: Pekare till den vektor som ska t�mmas.
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
* int_vector_delete: Raderar angiven dynamiskt allokerad vektor och s�tter
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
* int_vector_begin: Returnerar adressen till f�rsta elementet i angiven vektor.
*                   Om vektorn �r tom returneras null.
* 
*                   - self: Pekare till vektorn.
********************************************************************************/
static inline int* int_vector_begin(const struct int_vector* self)
{
   return self->data;
}

/********************************************************************************
* int_vector_end: Returnerar adressen efter sista elementet i angiven vektor.
*                 Om vektorn �r tom returneras null.
*
*                 - self: Pekare till vektorn.
********************************************************************************/
static inline int* int_vector_end(const struct int_vector* self)
{
   return self->data + self->size;
}

/********************************************************************************
* int_vector_last: Returnerar adressen till sista elementet i angiven vektor.
*                  Om vektorn �r tom returneras null.
*
*                  - self: Pekare till vektorn.
********************************************************************************/
static inline int* int_vector_last(const struct int_vector* self)
{
   return self->size > 0 ? int_vector_end(self) - 1 : 0;
}

/********************************************************************************
* int_vector_resize: �ndrar storleken p� angiven dynamisk vektor. Vid lyckad
*                    minnesallokering returneras 0, annars returneras felkod 1.
*
*                    - self: Pekare till den vektor vars storlek ska �ndras.
*                    - size: Vektorns storlek efter omallokeringen.
********************************************************************************/
int int_vector_resize(struct int_vector* self,
                      const size_t size);

/********************************************************************************
* int_vector_push: L�gger till ett nytt heltal l�ngst bak i angiven vektor.
*                  Om minnesallokeringen lyckas s� returneras 0, annars felkod 1.
*
*                  - self: Pekare till vektorn som ska tilldelas det nya talet.
*                  - num : Det nya tal som ska l�ggas till.
********************************************************************************/
int int_vector_push(struct int_vector* self,
                    const int num);

/********************************************************************************
* int_vector_pop: Tar bort sista heltalet i angiven vektor. Om minnesallokeringen 
*                 lyckas s� returneras 0, annars felkod 1.
*
*                 - self: Pekare till vektorn vars sista heltal ska tas bort.
********************************************************************************/
int int_vector_pop(struct int_vector* self);

/********************************************************************************
* int_vector_assign: Tilldelar heltal till angiven vektor med godtyckligt 
*                    start- och stegv�rde.
*
*                    - self     : Pekare till vektorn som ska tilldelas.
*                    - start_val: Startv�rde f�r tilldelningen.
*                    - step_val : Stegv�rde, dvs. differensen mellan varje tal.
********************************************************************************/
void int_vector_assign(struct int_vector* self,
                       const int start_val,
                       const int step_val);

/********************************************************************************
* int_vector_print: Skriver ut heltal lagrade i angiven vektor via godtycklig
*                   utstr�m, d�r standardutenheten stdout anv�nds som default
*                   f�r utskrift i terminalen.
*
*                   - self   : Pekare till vektorn som ska tilldelas.
*                   - ostream: Pekare till godtycklig utstr�m (default = stdout).
********************************************************************************/
void int_vector_print(const struct int_vector* self,
                      FILE* ostream);

#endif /* INT_VECTOR_H_ */