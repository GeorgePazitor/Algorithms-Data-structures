#include "qBST.h"

typedef struct BSTnode* link;
struct BSTnode { quot item; link l; link r; int N;} ;
struct binarysearchtree { link root; link z; };


static link NEW(quot item, link l, link r, int N) {
    link x = malloc(sizeof *x);
    x->item = item; x->l = l; x->r = r; x->N=N;
    return x;
}
BST BSTinit( ) {
    BST bst = malloc(sizeof *bst) ;
    bst->root= ( bst->z = NEW(Qsetvoid(), NULL, NULL, 0));
    return bst;
}

static void treeFree(link h, link z){
    if(h==z)
        return;
    treeFree(h->l, z);
    treeFree(h->r, z);
    free(h);

}
void BSTfree(BST bst){
    if(bst==NULL)
        return;

    treeFree(bst->root, bst->z);
    free(bst->z);
    free(bst);
}


static link insertR(link h, quot x, link z) {//inserimento in foglia
    if (h == z)
        return NEW(x, z, z, 1);
    if (DTcmpData(x.dd, (h->item).dd)==-1)
        h->l = insertR(h->l, x, z);
    else
        h->r = insertR(h->r, x, z);
    (h->N)++;
    return h;
}
void BSTinsert_leafR(BST bst, quot x) {
    bst->root = insertR(bst->root, x, bst->z);
}

quot searchR(link h, data k, link z) {
    int cmp;
    if (h == z)
        return Qsetvoid();
    cmp = DTcmpData(k, (h->item).dd);
    if (cmp == 0)
        return h->item;
    if (cmp == -1)
        return searchR(h->l, k, z);
    return searchR(h->r, k, z);
}
quot BSTsearch(BST bst, data k) {
    return searchR(bst->root, k, bst->z);
}

int modifyR(link h, data k, ora o, int v, int n, link z) {
    int cmp;
    if (h == z)
        return 0;
    cmp = DTcmpData(k, (h->item).dd);
    if (cmp == 0){
        Qcalc(&(h->item), v, n);
        h->item.oo=o;//ora dell'ultima modifica
        return 1;
    }
    if (cmp == -1)
        return modifyR(h->l, k, o, v, n, z);
    return modifyR(h->l, k, o, v, n, z);
}
int BSTmodify(BST bst, data k, ora o, int v, int n) {
    return modifyR(bst->root, k, o, v , n, bst->z);
}


void inOrderDT(link h, link z, data d1, data d2, float *min, float *max){
    float v;
    if (h == z)
        return;
    inOrderDT(h->l, z, d1, d2, min, max);
    if(DTcmpData(d1, h->item.dd)<=0 && DTcmpData(h->item.dd, d2 )<=0){
        v= Qretq(h->item);
        if(v>*max) *max=v;
        if(v<*min) *min=v;
    }
    inOrderDT(h->r, z, d1, d2, min, max);
}
void inOrderDTRic(BST bst,data d1, data d2){
    float min=FLT_MAX;
    float max=-FLT_MAX;
    inOrderDT(bst->root, bst->z, d1, d2, &min, &max);
    printf("La massima quotazione e' di %.2f e' la minima di %.2f", max, min);
}

float farestLeaf(link root, link z) {
    float u, v;
    if (root == z)
        return -1;
    u = farestLeaf(root->l,z);
    v = farestLeaf(root->r,z);
    if (u>v)
        return u+1;
    return v+1;
}

float closestLeaf(link root, link z) {
    float u, v;
    if (root == z)
        return -1;
    u = closestLeaf(root->l,z);
    v = closestLeaf(root->r,z);
    if (u<v)
        return u+1;
    return v+1;
}

float BSTceckbalance(BST bst, float s){
    float p;
    p=farestLeaf(bst->root, bst->z)/closestLeaf(bst->root, bst->z);
    if(p>s){
        BSTbalance(bst);
        return p;
    }
    return 0;
}

//partizionamento ricorsivo (va fatto rispetto alla chiave mediana)

link rotR(link h) {
    link x = h->l;
    h->l = x->r;

    x->r = h;

    x->N = h->N;
    h->N = 1;
    h->N += (h->l) ? h->l->N : 0;
    h->N += (h->r) ? h->r->N : 0;
    return x;
}

link rotL(link h) {
    link x = h->r;//
    h->r = x->l;//

    x->l = h;//

    x->N = h->N;
    h->N = 1;
    //aggiunge ad h->N il valore  h->l->N se (h->l) è vera(>0) zero se è zero(nessuna figlio sinistro)
    h->N += (h->l) ? h->l->N : 0;
    h->N += (h->r) ? h->r->N : 0;
    return x;
}


link partR(link h, int r){
    int t=h->l->N;
    if(t>r){
        h->l=partR(h->l, r);
        h=rotR(h);
    }
    if(t<r){
        h->r=partR(h->r, r-t-1);
        h=rotL(h);
    }
    return h;
}

 static link balanceR(link h, link z) {
    int r;
    if (h == z)
        return z;
    r = (h->N+1)/2-1;
    h = partR(h, r);
    h->l = balanceR(h->l, z);
    h->r = balanceR(h->r, z);
    return h;
}
void BSTbalance(BST bst) {
    bst->root = balanceR(bst->root, bst->z);
}
