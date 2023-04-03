#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "equipArray.h"
#include "pg.h"

/* lettura e scrittura su file */
int pg_read(FILE *fp, pg_t *pgp){
    //mette campi di un personaggio al valore assunto come vuoto quando arriva alla fine di fp
    if(fscanf(fp, "%s %s %s",pgp->cod,pgp->nome,pgp->classe)==EOF) pg_set_void(pgp);
    stat_read(fp, &pgp->b_stat);
    pgp->eq_stat=pgp->b_stat;
    pgp->equip=equipArray_init();
}
/* non essendo struct dinamica, pulisce chiamando il distruttire di equipArray */
void pg_clean(pg_t *pgp){
    equipArray_free(pgp->equip);
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray){
    fprintf(fp,"%s %s %s\n",pgp->cod,pgp->nome,pgp->classe);

    printf("statistiche base personaggio");
    stat_print(fp,&pgp->b_stat,INT_MIN);

    printf("statistiche con equipaggiamento ");
    stat_print(fp,&pgp->eq_stat,0);

    printf("equipaggiamento: \n");
    equipArray_print(stdout, pgp->equip,invArray);
    printf("\n\n");
}
/* modifica personaggio aggiungendo/togliendo un equipaggiamento selezionato da inventario*/
void pg_updateEquip(pg_t *pgp, invArray_t invArray){

    inv_t *t;

    int pos=equipArray_inUse(pgp->equip);//numero di equipaggiamenti corrente

    t=equipArray_update(pgp->equip, invArray);//aggiunta o rimozione di equipaggiamento da pgp->equip
    //se il numero di equipaggiamenti e' aumentato devo sommare le nuove statistiche
    if(pos< equipArray_inUse(pgp->equip)) stat_modify(&pgp->eq_stat, inv_getStat(t), 1);
    //seil numero di equipaggiamenti e' diminuito devo sottrarre le vecchie statistiche
    if(pos> equipArray_inUse(pgp->equip)) stat_modify(&pgp->eq_stat, inv_getStat(t), 0);
}

void pg_set_void(pg_t *pgp){//
    strcpy(pgp->cod, "none");
    strcpy(pgp->nome, "none");
    strcpy(pgp->classe, "none");
    stat_set_void(&pgp->b_stat);
    stat_set_void(&pgp->eq_stat);
}
