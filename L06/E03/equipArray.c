#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define EQUIP_SLOT 8

#include "invArray.h"
#include "inv.h"

/* ADT di prima classe collezione di oggetti di equipaggiamento */
typedef struct equipArray_s *equipArray_t;

struct equipArray_s{
    int inUso;
    inv_t *arrayEq;//vettore di oggetti di inventario allocato dinamicamente
};


/* creatore e disruttore */
equipArray_t equipArray_init(){
    equipArray_t eq=(equipArray_t)malloc(sizeof(struct equipArray_s));
    eq->inUso=0;
    eq->arrayEq=(inv_t*)malloc(EQUIP_SLOT*sizeof(inv_t));
    return eq;
}
void equipArray_free(equipArray_t equipArray){
    free(equipArray->arrayEq);
    free(equipArray);
}

/* quanti equipaggiamenti sono in uso */
int equipArray_inUse(equipArray_t equipArray){
    return equipArray->inUso;
}

/* scrittura su file */
void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray){
    int i;
    for(i=0;i<equipArray->inUso;i++){
        inv_print(fp, &equipArray->arrayEq[i]);
    }
    if(equipArray->inUso==0) printf("nessun equipaggiamento");
}

int equipArray_getEquipbyName(equipArray_t equipArray, char *name){//ritorna l'indice dato il nome, -1 se non trovato
    int pos=equipArray->inUso;
    int i;
    for(i=0; i<pos ;i++){
        if(strcmp(name, equipArray->arrayEq->nome)==0){
            return i;
        }
    }
    return -1;
}
/* modifica equipaggiamento scegliendo un oggetto da inventario */
inv_t* equipArray_update(equipArray_t equipArray, invArray_t invArray){
    //ritorna il puntatore a oggetto di inventario che sarà aggiunto a equipaggiamento o rimosso
    //per poter alterare le statistiche del personaggio richiamando l'apposita funzione
    inv_t *k;
    char s[100];
    int i,j;
    int op;
    int pos=equipArray->inUso;

    printf("Premi 1 per equippaggiare un oggetto dall'inventario, 0 per rimuoverlo\n");
    scanf("%d", &op);
    switch (op){
        case 1://aggiunta a equip
            if(pos<8) {
                printf("\nInserisci il nome di un oggetto da equipaggiare: ");
                scanf("%s", s);
                i = invArray_searchByName(invArray, s);
                if(i!=-1){//equipaggiamento esiste in vettore inventario
                    for (j = 0; j < pos; j++) {
                        if(strcmp(equipArray->arrayEq[j].nome,s)==0){
                            printf("\nEquipaggiamento già in uso");
                            k=NULL;
                            op=0;
                        }
                    }
                    if(op!=0){//riuso op come flag di equipaggiamento già in uso
                        //assegno il contenuto della struct che si trova all'indice i, con nome inserito pocanzi
                        equipArray->arrayEq[pos] = *invArray_getByIndex(invArray, i);
                        k=&(equipArray->arrayEq[pos]);//assegno a k l'indirizzo dell'elemento in vettore degli equip
                        equipArray->inUso++;
                    }
                }
                else{
                    printf("\nNome dell'equipaggiamento inesistente");
                    k=NULL;
                }
            }
            else{
                printf("\nSlot degli equipaggiamenti pieno");
                k=NULL;
            }
        break;

        case 0://rimozione da equip
            printf("\nInserisci il nome di un oggetto da rimuovere dall'equipaggiamento: ");
            scanf("%s", s);
            i=equipArray_getEquipbyName(equipArray, s);
            if(i==-1) {
                printf("Equipaggiamento non trovato");
                k=NULL;
            }
            else {
                k=&(equipArray->arrayEq[i]);//indirizzo dell' oggetto in equip di tipo inv_t
                for (j = i + 1; j < pos; j++) {//a partire dalla posizione dell'oggetto rimosso + 1
                    equipArray->arrayEq[j - 1] = equipArray->arrayEq[j];//scalameto delle posizioni in equip
                }
                equipArray->inUso--;
            }
        break;
        default:
            printf("\ncomando non valido\n");
            k=NULL;
            break;
    }
    return k; //NULL  se non è stato aggiunto o rimosso nulla
}
/* torna indice (nel vettore inventario) dell'oggetto in posizione index (0..EQUIP_SLOT-1) di equipArray */
int equipArray_getEquipByIndex(equipArray_t equipArray, int index);



