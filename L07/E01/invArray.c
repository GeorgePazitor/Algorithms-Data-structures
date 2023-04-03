#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "inv.h"

/* ADT di prima classe collezione di oggetti di inventario */
typedef struct invArray_s *invArray_t;

struct invArray_s{
    inv_t *array;
    int ninv;
    int maxinv;
};

/* creatore e disruttore */
invArray_t invArray_init(){
    invArray_t invArray=(invArray_t)malloc(sizeof( struct invArray_s));
    invArray->array=NULL;
    invArray->ninv=0;
    invArray->maxinv=0;
    return invArray;
}
void invArray_free(invArray_t invArray){
    free(invArray->array);
    free(invArray);
}

/* lettura e scrittura su file */
void invArray_read(FILE *fp, invArray_t invArray) {
    int i;

    fscanf(fp, "%d\n", &invArray->ninv);
    invArray->array=(inv_t*)malloc(invArray->ninv*sizeof(inv_t));

    for (i = 0; i < invArray->ninv; i++) {
        inv_read(fp, &invArray->array[i]);
    }
}
void invArray_print(FILE* fp,invArray_t invArray){
    int i;
    printf("\nINVENTARIO:\n\n");
    for(i=0;i<invArray->ninv;i++){
        inv_print(fp, &invArray->array[i]);
        printf("\n");
    }
}

/* stampa un unico oggetto selezionato da indice (nel vettore) */
void invArray_printByIndex(invArray_t invArray, int index){
    inv_print(stdout, &invArray->array[index]);
}

/* ritorna puntatore a oggetto selezionato da indice (nel vettore) */
inv_t *invArray_getByIndex(invArray_t invArray, int index){
    return &(invArray->array[index]);
}

/* ritorna indice, nel vettore inventario, a oggetto selezionato da nome */
int invArray_searchByName(invArray_t invArray, char *name){
    int i;
    for (i = 0; i < invArray->ninv; i++) {
        if (strcmp(invArray->array[i].nome, name)==0) return i;
    }
    return -1;
}
