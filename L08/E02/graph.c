#include<stdio.h>
#include<stdlib.h>


#include "graph.h"
#include "ST.h"

typedef struct node *link;

struct node {int v; int wt; link next;};

struct graph {int V; int E; link *ladj; int **madj; ST tab; link z;};

static link NEW(int v, int wt, link next) {
    link x = malloc(sizeof *x);
    x->v = v; x->wt = wt; x->next = next;
    return x;
}

static int **MATRIXint(int r, int c, int val) {
    int i, j;
    int **t = malloc(r * sizeof(int *));
    for (i=0; i < r; i++) t[i] = malloc(c * sizeof(int));
    for (i=0; i < r; i++)
        for (j=0; j < c; j++)
            t[i][j] = val;
    return t;
}

Graph GRAPHinit(int V) {
    Graph G = malloc(sizeof *G);
    G->V = V;
    G->E = 0;
    G->madj = MATRIXint(V, V, 0);

    return G;
}

Graph GRAPHload(FILE *fin) {
    int i=0, id1, id2, wt;
    char e1[2][MAXC];
    char e2[2][MAXC];

    Graph G;
    ST st;
    //preinizializzazione della tabella di simboli per ricavarsi il numero di vertici del file
    st=STinit(10);//inizializzo la tabella di simboli con un numero piccolo per vederne la riallocazione

    //prima apertura del file per sapere il numero di elementi
    while(fscanf(fin,"%s %s %s %s %d\n",e1[0], e1[1], e2[0], e2[1], &wt)!=EOF){

        if(STsearch(st, e1[0])<0){
            STinsert(st, e1[0],e1[1]); i++ ;
        }
        if(STsearch(st, e2[0])<0){
            STinsert(st, e2[0],e2[1]); i++ ;
        }
    }
    G = GRAPHinit(i);
    G->tab=st;
    //seconda apertura del file per memorizzare gli archi
    rewind(fin);

    while(fscanf(fin,"%s %s %s %s %d\n",e1[0], e1[1], e2[0], e2[1], &wt) != EOF) {
        id1 = STsearch(G->tab, e1[0]);
        id2 = STsearch(G->tab, e2[0]);


        if (id1 >= 0 && id2 >=0)
            GRAPHinsertE(G, id1, id2, wt);
    }

    return G;
}
void GRAPHladj(Graph G){
    int i, j;

    G->z = NEW(-1, -1, NULL);
    G->ladj = malloc(G->V*sizeof(link));
    for (i = 0; i < G->V; i++){
        G->ladj[i] = G->z;
        for (j = 0; j < G->V; j++){
            if(G->madj[i][j]>0){
                GRAPHinsertEinLadj(G, i, j, G->madj[i][j]);
            }
        }
    }

    link x;

    for (i = 0; i < G->V; i++) {
        printf("\nNodo corrente: %s e suoi vicini:\n", STselect(G->tab, i));
        for (x = G->ladj[i]; x != G->z; x = x->next) {
            printf("\n%s peso: %d", STselect(G->tab, x->v), x->wt);
        }
        printf("\n");
    }
}

static Edge EDGEcreate(int v,int w, int wt) {
    Edge e;
    e.v = v;
    e.w = w;
    e.wt = wt;
    return e;
}
static void insertE(Graph G, Edge e) {
    int v = e.v, w = e.w, wt =e.wt;
    if (G->madj[v][w] == 0)
        G->E++;
    G->madj[v][w] = wt;
    G->madj[w][v] = wt;
}

static void insertEinLadj(Graph G, Edge e) {//per la rappresentazione di lista delle adiacenze
    int v = e.v, w = e.w, wt = e.wt;
    G->ladj[v] = NEW(w, wt, G->ladj[v]);
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
    insertE(G, EDGEcreate(id1, id2, wt));
}

void GRAPHinsertEinLadj(Graph G, int id1, int id2, int wt) {
    insertEinLadj(G, EDGEcreate(id1, id2, wt));
}

void GRAPHfree(Graph G) {
    int i;
    link t, next;

    for (i = 0; i < G->V; i++)
        free(G->madj[i]);
    free(G->madj);

    if(G->ladj!=NULL){
        for (i=0; i < G->V; i++)
            for (t=G->ladj[i]; t != G->z; t = next) {
                next = t->next;
                free(t);
            }
        free(G->ladj);
    }

    STfree(G->tab);

    free(G->z);
    free(G);
}

void GRAPHdisplayAlpha(Graph G){
    int i, j;

    for(i=0;i<G->V;i++){
        printf("\n%s", STselect(G->tab, i));
        for(j=0;j<G->V;j++){
            //si assume che archi inesistenti hanno peso nullo
            if(G->madj[i][j]>0) printf("\n   %s", STselect(G->tab, j));
        }
    }
}

int GRAPH3complete(Graph G, char a[MAXC], char b[MAXC], char c[MAXC]){
    int id1, id2, id3;
    id1 = STsearch(G->tab, a);
    id2 = STsearch(G->tab, b);
    id3 = STsearch(G->tab, c);
    if(id1<0 || id2<0 || id3<0) return -1;
    if(G->madj[id1][id2]>0 && G->madj[id1][id3]>0 && G->madj[id2][id3]>0){
        return 1;
    }
    return 0;
}

int GRAPH3completeLadj(Graph G, char a[MAXC], char b[MAXC], char c[MAXC]){
    int id1, id2, id3, f=0;

    link t;

    id1 = STsearch(G->tab, a);
    id2 = STsearch(G->tab, b);
    id3 = STsearch(G->tab, c);
    if(id1<0 || id2<0 || id3<0) return -1;


    for (t=G->ladj[id1]; t != G->z; t = t->next) {
        if(t->v == id2 && t->wt>0) f++;
        if(t->v == id3 && t->wt>0) f++;
    }
    for (t=G->ladj[id2]; t != G->z; t = t->next) {
        if(t->v == id1 && t->wt>0) f++;
        if(t->v == id3 && t->wt>0) f++;
    }
    for (t=G->ladj[id3]; t != G->z; t = t->next) {
        if(t->v == id1 && t->wt>0) f++;
        if(t->v == id2 && t->wt>0) f++;
    }
    if(f==6) return 1;
    return 0;
}
