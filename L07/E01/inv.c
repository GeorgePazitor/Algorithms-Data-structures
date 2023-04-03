#include <stdlib.h>
#include <stdio.h>
#include "inv.h"
#define LEN 100


/* funzioni di input/output delle statistiche */
void stat_read(FILE *fp, stat_t *statp) {
    fscanf(fp, "\t%d %d %d %d %d %d", &statp->hp, &statp->mp, &statp->atk, &statp->def, &statp->mag, &statp->spr);
}

void stat_print(FILE *fp, stat_t *statp, int soglia){//stampa con la soglia minima delle statistiche,
    //se il valore è minore della soglia, assume il valore della soglia
    if(statp->hp>=soglia)fprintf(fp," %d",statp->hp);
    else fprintf(fp," %d", soglia);

    if(statp->mp>=soglia)fprintf(fp," %d",statp->mp);
    else fprintf(fp," %d", soglia);

    if(statp->atk>=soglia)fprintf(fp," %d",statp->atk);
    else fprintf(fp," %d", soglia);

    if(statp->def>=soglia)fprintf(fp," %d",statp->def);
    else fprintf(fp," %d", soglia);

    if(statp->mag>=soglia)fprintf(fp," %d",statp->mag);
    else fprintf(fp," %d", soglia);

    if(statp->spr>=soglia)fprintf(fp," %d\n",statp->spr);
    else fprintf(fp," %d\n", soglia);
}

/* funzioni di input/output di un oggetto dell'inventario */
void inv_read(FILE *fp, inv_t *invp){
    fscanf(fp, "%s %s", invp->nome, invp->tipo);
    stat_read(fp,&invp->stat);
}

void inv_print(FILE *fp, inv_t *invp){
    fprintf(fp, "%s %s", invp->nome, invp->tipo);
    stat_print(fp,&invp->stat,1);//richiama la stampa delle statistiche con la soglia minima possibile

}

/* ritorna il campo stat di un oggetto dell'inventario */
stat_t inv_getStat(inv_t *invp){
    return invp->stat;
}

/* funzioni aggiunte */
void stat_set_void(stat_t *statp){
    statp->hp=0;
    statp->mp=0;
    statp->atk=0;
    statp->def=0;
    statp->mag=0;
    statp->spr=0;
}

void stat_modify(stat_t *statp, stat_t statn, int op){//modifica le statistiche, op = 1 addiziona , 0 sottrae
    if(op){
        statp->hp+=statn.hp;
        statp->mp+=statn.mp;
        statp->atk+=statn.atk;
        statp->def+=statn.def;
        statp->mag+=statn.mag;
        statp->spr+=statn.spr;

    }
    else{
        statp->hp-=statn.hp;
        statp->mp-=statn.mp;
        statp->atk-=statn.atk;
        statp->def-=statn.def;
        statp->mag-=statn.mag;
        statp->spr-=statn.spr;

    }
}

