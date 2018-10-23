/*gittest
** simple error demonstration to demonstrate power of valgrind
** Julian M. Kunkel - 17.04.2008
*/

#include <stdio.h>
#include <stdlib.h>

int *
mistake1 ()
{
  //buf war lokale variable und somit nach beendigung der fkt geloescht
  int *buf = calloc (2, sizeof(int));
  buf[1] = 1;
  return buf;
}

int *
mistake2 ()
{
  //im array von int* wird auf buf[1] und nicht buf[2] zugegriffen
  int *buf = malloc (sizeof (int) * 2);
  buf[1] = 2;
  return buf;
}

int *
mistake3 ()
{
  /* In dieser Funktion darf kein Speicher direkt allokiert werden. */
  //fehler im funktionsaufruf fuer buf allokation
  int *buf = (int *) mistake2 ();
  buf[0] = 3;
  return buf;
}

int *
mistake4 ()
{
  //free hat buf vor return freigegeben
  int *buf = malloc (sizeof (char) * 4);
  buf[0] = 4;
  return buf;
}

int
main (void)
{
  /* Modifizieren Sie die folgende Zeile nicht */
  int *p[4] = { &mistake1 ()[1], &mistake2 ()[1], mistake3 (), mistake4 () };

  printf ("1 %d\n", *p[0]);
  printf ("2 %d\n", *p[1]);
  printf ("3 %d\n", *p[2]);
  printf ("4 %d\n", *p[3]);

  /* mhh muss hier noch etwas gefreed werden? */
  /* Fügen sie hier die korrekten aufrufe von free() ein */
  free (p[2]);
  free (p[3]);
  //p[0]-1, da der pointer auf den array kopf gefreed werden muss
  free (p[0]-1);
  free (p[1]-1);			/* welcher Pointer war das doch gleich?, TODO: Fixme... :-) */

  return 0;
}
