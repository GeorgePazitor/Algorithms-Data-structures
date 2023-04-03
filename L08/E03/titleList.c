#include "titleList.h"

typedef struct node *link;

struct node {title val; link next;  };
struct list { link head; int N; };

link SortListIns(link h, title val);
title SortListSearch(link h, char k[MAXC]);
link newNode(title val, link next);

Ltit Listinit(){
    Ltit l=(Ltit) malloc(sizeof (Ltit));
    l->head=NULL;
    l->N=0;
    return l;
}

void ListInsR(Ltit l, title val){
    l->head=SortListIns(l->head,val);
    l->N++;
}

title ListSearchR(Ltit l, char k[MAXC]){
    return SortListSearch(l->head, k);
}


link newNode(title val, link next) {
    link x = malloc(sizeof *x);
    if (x==NULL)
        return NULL;
    else {
        x->val = val;
        x->next = next;
    }
    return x;
}

link SortListIns(link h, title val) {
    link x, p;
    char k[MAXC];
    strcpy(k,TITgetname(val));
    if (h==NULL || strcmp(TITgetname(h->val),k)>0)
        return newNode(val, h);
    for (x=h->next, p=h;
         x!=NULL && strcmp(k,TITgetname(x->val))>0;
         p=x, x=x->next);
    p->next = newNode(val, x);
    return h;
}

title SortListSearch(link h, char k[MAXC]) {
    link x;
    for (x=h;x!=NULL;x=x->next) {
        if (strcmp(TITgetname(x->val), k) == 0)
            return x->val;
    }
    return NULL;
}

void Listdisp(Ltit l){
    link n;
    char k[MAXC];

    for(n=l->head; n!=NULL; n=n->next){
        strcpy(k,TITgetname(n->val));
        printf("\n%s", k);
    }
}
void Listfree(Ltit l){
    link n, tmp;
    for(n=l->head; n!=NULL; n=n->next){
        tmp=n;
        n=n->next;
        TITfree(tmp->val);
        free(tmp);
    }
    free(l);
}


