#include "ST.h"
typedef struct name{char n[MAXC];}n;

struct symbtab {n *a; int maxN; int size;};

ST STinit(int maxN) {
    ST st; int i; char s[MAXC];
    st = malloc(sizeof(*st));
    st->a = malloc(maxN * sizeof(n));

    for (i = 0; i < maxN; i++){
        strcpy(st->a[i].n,"\0");
    }
    st->maxN = maxN;
    st->size = 0;
    return st;
}

void STfree(ST st) {
    free(st->a);
    free(st);
}

void STinsert(ST st, char k[MAXC]) {
    int i = st->size;
    if (st->size >= st->maxN) {
        st->a=realloc(st->a,(2*st->maxN)*sizeof(n));
        if (st->a == NULL) return;
        st->maxN = 2*st->maxN;
    }
    strcpy(st->a[i].n , k); st->size++;
}
int STsearch(ST st, char k[MAXC]) {
    int i;
    if (st->size == 0) return -1;
    for (i = 0; i < st->size; i++)
        if (strcmp(st->a[i].n, k)==0) return i;
    return 0;
}

char *STsearchByIndex(ST st,int v){
    return st->a[v].n;
}
