#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "ST.h"


typedef struct vertex{char name[MAXC]; char snet[MAXC];} Vert ;

struct symboltable {Vert *a; int maxN; int size;};

ST STinit(int maxN) {
    ST st; int i;
    st = malloc(sizeof(*st));
    st->a = malloc(maxN*sizeof(Vert));
    for (i = 0; i < maxN; i++){
        strcpy(st->a[i].name, "\0");
        strcpy(st->a[i].snet, "\0");

    }
    st->maxN = maxN;
    st->size = 0;
    return st;
}

void STfree(ST st) {
    free(st->a);
    free(st);
}

void STinsert(ST st, char val[MAXC], char val1[MAXC]) {
    int i = st->size++;
    if (st->size >= st->maxN) {
        st->a=realloc(st->a,(2*st->maxN)*sizeof(Vert));
        if (st->a == NULL)
            return;
        st->maxN = 2*st->maxN;
    }
    while((i>0)&&strcmp(val,st->a[i-1].name)==-1){
        st->a[i] = st->a[i-1];
        i--;
    }

    strcpy(st->a[i].name, val);
    strcpy(st->a[i].snet, val1);
}

char* STselect(ST st, int r) {
    return st->a[r].name;
}

int STsearch(ST st, char k[MAXC]) {
    return searchR(st, 0, st->size - 1, k);
}

int searchR(ST st, int l, int r, char k[MAXC]) {
    int m;
    m = (l + r)/2;
    if (l > r)return -1;
    if(strcmp(k,st->a[m].name)==0)
        return m;
    if (l == r)
        return -1;
    if(strcmp(k,st->a[m].name)==-1)
        return searchR(st, l, m-1, k);
    else
        return searchR(st, m+1, r, k);
}



