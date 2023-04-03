#include <stdio.h>
#include <string.h>
#include "pg.h"
#include "inv.h"
#include "pgList.h"

typedef struct node{
    pg_t pers;
    struct node *link;
}pgNode;

struct pgList_s{
    pgNode *head;
    pgNode *tail;
    int npg;
};


pgNode* newnode(){
    pgNode *n=(pgNode*)malloc(sizeof(pgNode));
    if(n==NULL) {
        return NULL;
    }
    else {
        pg_set_void(&n->pers);
        n->link = NULL;
        return n;
    }
}

pgList_t pgList_init(){
    pgList_t pgList=(pgList_t)malloc(sizeof(struct pgList_s));
    pgList->head=NULL;
    pgList->tail=NULL;
    pgList->npg=0;
    return pgList;
}
void pgList_free(pgList_t pgList){
    pgNode *l;
    pgNode *tmp;
    l=pgList->head;
    while(l!=NULL){
        pg_clean(&l->pers);
        tmp=l;
        l=l->link;
        free(tmp);
    }
    free(pgList);
}

/* lettura e scrittura su file */
void pgList_read(FILE *fp, pgList_t pgList){
    pg_t p;
    pg_read(fp, &p);//legge il personaggio da file in una variabile p di appoggio
    for(pgList->npg=0; strcmp(p.cod,"none")!=0; pgList->npg++){
        //condizione di terminazione: scorsa lettura di p contiene in nome il valore per pg vuoto: in pg_read si ha EOF
        pgList_insert(pgList, p);
        pg_read(fp, &p);
    }
}

void pgList_print(FILE *fp,pgList_t pgList, invArray_t invArray){
    pgNode *l;
    printf("\nPERSONAGGI:\n\n");
    for(l=pgList->head;l!=NULL;l=l->link){//attraversamento semplice in lista
        pg_print(fp,&l->pers,invArray);
    }
}

/* inserimento di un nuovo personaggio */
void pgList_insert(pgList_t pgList, pg_t pg){
    pgNode *tmp;
    tmp=pgList->head;
    if(pgList_searchByCode(pgList, pg.cod)==NULL){//controllo di non esistenza del codice inserito
        pgList->head=newnode();
        if(tmp==NULL) pgList->tail=pgList->head;//se la lista è vuota, il primo nodo sarà head e tail
        pgList->head->link=tmp;
        pgList->head->pers=pg;
    }
    else{
        printf("Il codice personaggio e' gia in uso per un altro personaggio");
    }
}
/* cancellazione con rimozione */
void pgList_remove(pgList_t pgList, char* cod){
    pgNode *l, *p;
    if(pgList->head==NULL) return;//lista dei personaggi e' vuota
    for(l=pgList->head, p=NULL; l!=NULL; p=l, l=l->link){
        if(strcmp(l->pers.cod,cod)==0){
            if(l==pgList->head) pgList->head=l->link;
            else p->link=l->link;
            pg_clean(&l->pers);
            free(l);
            printf("Il pesonaggio e' stato eliminato con successo");
            break;//interrompe l'attraversamento, paradigma di programmazione non strutturata
        }
    }

}
/* ricerca per codice, ritornando il puntatore */
pg_t *pgList_searchByCode(pgList_t pgList, char* cod){
    pgNode *l;

    if(pgList->head==NULL) return NULL;//lista vuota
    for(l=pgList->head;l!=NULL; l=l->link){
        if(strcmp(l->pers.cod,cod)==0){
            return &(l->pers);//interrompe l'attraversamento, paradigma di programmazione non strutturata
        }
    }
    return NULL;//Personaggio non trovato
}



