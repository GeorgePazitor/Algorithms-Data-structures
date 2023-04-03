#include <stdlib.h>
#include <stdio.h>

#include "pgList.h"
#include "invArray.h"
#include "pg.h"

#define N_SCELTE 7
#define DBG 0

enum { falso, vero };
typedef int bool;

void stampaMenu(char *scelte[], int *selezione){
  int i;
  printf("\nMENU'\n");
  for(i=0;i<N_SCELTE;i++)
    printf("%2d > %s\n",i,scelte[i]);
  scanf(" %d",selezione);
}

int main(int argc, char **argv) {
  char *scelte[] = {
    "Uscita",
    "Stampa personaggi",
    "Stampa inventario",
    "Cerca personaggio",
    "Aggiungi personaggio",
    "Elimina personaggio",
    "Modifica equip"
  };

  char codiceRicerca[LEN];
  int selezione;
  FILE *fin;
  bool fineProgramma;

  pgList_t pgList = pgList_init(); //inizializzazione lista personaggi
  invArray_t invArray = invArray_init(); //inizializzazione array inventario
  pg_t *pgp, pg;
  fin = fopen("../pg.txt","r");
  pgList_read(fin, pgList); //lettura da file dei personaggi da mettere in lista
  fclose(fin);
#if DBG
  pgList_print(stdout, pgList);
#endif /* DBG */

  fin = fopen("../inventario.txt","r");
  invArray_read(fin, invArray); //lettura da file degli equipaggiamenti da mettere nell'inventario
  fclose(fin);
#if DBG
  invArray_print(stdout, invArray);
#endif /* DBG */

  fineProgramma = falso;

  do {
      fflush(stdin);
    stampaMenu(scelte, &selezione);
    switch(selezione){

    case 0: {
      fineProgramma = vero;
    } break;

    case 1: {//stampa personaggi
      pgList_print(stdout, pgList, invArray);
    } break;

    case 2: {//stampa inventario
      invArray_print(stdout, invArray);
    } break;

    case 3: {//ricerca per codice del personaggio
      printf("Inserire codice personaggio: ");
      scanf("%s", codiceRicerca);
      pgp = pgList_searchByCode(pgList, codiceRicerca);
      if (pgp!=NULL) {
        pg_print(stdout, pgp, invArray);
      }
    } break;

    case 4: {//aggiunta personaggio
        printf("Cod Nome Classe HP MP ATK DEF MAG SPR: ");
      if (pg_read(stdin, &pg) != 0) {
        pgList_insert(pgList, pg);
      }
    } break;

    case 5: {//elimina personaggio
      printf("Inserire codice personaggio: ");
      scanf("%s", codiceRicerca);
      pgList_remove(pgList, codiceRicerca);
    } break;

    case 6: {//modifica equipaggiamento
      printf("Inserire codice personaggio: ");
      scanf("%s", codiceRicerca);
      pgp = pgList_searchByCode(pgList, codiceRicerca);

      if (pgp!=NULL) {
        pg_updateEquip(pgp, invArray);
      }
    } break;

    default:{
      printf("Scelta non valida\n");
    } break;
    }
  } while(!fineProgramma);

  pgList_free(pgList);
  invArray_free(invArray);

  return 0;
}
