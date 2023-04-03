#include "title.h"

struct titolo{
    char name[MAXC];
    BST qbst;
};

title TITinit(char k[MAXC]){
    title t=(title)malloc(sizeof(title*));
    strcpy(t->name,k);
    t->qbst=BSTinit();
    return t;
}
char *TITgetname(title t){
    return t->name;
}

void TITquotins(title t, char d[11], char o[6], int v, int n){
    quot q;
    q=BSTsearch(t->qbst, DTset(d));
    if(Qisvoid(q)){
        Qcalc(&q, v, n);
        QsetDTeORA(&q, DTset(d), ORAset(o));
        BSTinsert_leafR(t->qbst, q);
    }
    else{//se la quotazione esiste gia nel BST la ricalcolo
        BSTmodify(t->qbst, DTset(d), ORAset(o), v, n);
    }
}

void TITquotdisp(title t, data d){
    quot q;
    q= BSTsearch(t->qbst, d);

    Qdisp(q);
}

void TITsearchdata(title t, char data[11]){
    TITquotdisp(t, DTset(data));
}

void TITdatainterv(title  t , char d1[11], char d2[11]){
    inOrderDTRic(t->qbst,DTset(d1), DTset(d2));
}
void TITceckbalancetree(title t, float s){
    float f;
    f=BSTceckbalance(t->qbst, s);
    if(f>0) {
        printf("l'albero e' stato bilanciato, aveva rapporto tra il cammino piu' lungo e piu' corto di: %.2f", f);
        return;
    }
    printf("L'albero ha rapporto tra il cammino piu' lungo e piu' corto minore della soglia di bilanciamento");
}
void TITfree(title v){
    printf("aaa");
    BSTfree(v->qbst);

    free(v);
}
