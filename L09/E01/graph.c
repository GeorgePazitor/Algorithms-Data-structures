#include "graph.h"


typedef struct node *link;
struct node { int v; int wt; link next; } ;
struct graph{int V; int E; link *ladj; ST tab; link z;} ;


static link NEW(int v, int wt, link next) {
    link x = malloc(sizeof *x);
    x->v = v; x->wt = wt; x->next = next;
    return x;
}
static Edge EDGEcreate(int v, int w, int wt) {
    Edge e;
    e.v = v; e.w = w; e.wt = wt;
    return e;
}

Graph GRAPHinit(int V) {
    int v;
    Graph G = malloc(sizeof *G);
    G->V = V;
    G->E = 0;
    G->z = NEW(-1, -1, NULL);
    G->ladj = malloc(G->V*sizeof(link));
    for (v = 0; v < G->V; v++)
        G->ladj[v] = G->z;
    G->tab = STinit(V);
    return G;
}

void GRAPHedges(Graph G, Edge *a) {
    int v, E = 0;
    link t;
    for (v=0; v < G->V; v++)
        for (t=G->ladj[v]; t != G->z; t = t->next)
            a[E++] = EDGEcreate(v, t->v, t->wt);
}

static void insertE(Graph G, Edge e) {
    int v = e.v, w = e.w, wt = e.wt;
    G->ladj[v] = NEW(w, wt, G->ladj[v]);

    G->E++;
}

static void removeE(Graph G, Edge e) {
    int v = e.v, w = e.w; link x, p;
    for (x = G->ladj[v], p = NULL; x != G->z; p = x, x = x->next) {
        if (x->v == w) {
            if (x == G->ladj[v]) G->ladj[v] = x->next;
            else p->next = x->next;
            break;
        }
    }
    G->E--; free(x);
}

Graph GRAPHload(FILE *fin) {
    int V, i, id1, id2, wt;
    char label1[MAXC], label2[MAXC];
    Graph G;
    fscanf(fin, "%d", &V);
    G = GRAPHinit(V);
    for (i=0; i<V; i++) {
        fscanf(fin, "%s", label1);
        STinsert(G->tab, label1);
    }
    while(fscanf(fin,"%s %s %d", label1, label2, &wt) == 3) {
        id1 = STsearch(G->tab, label1);
        id2 = STsearch(G->tab, label2);
        if (id1 >= 0 && id2 >=0)
            GRAPHinsertE(G, id1, id2, wt);
    }
    return G;
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
    insertE(G, EDGEcreate(id1, id2, wt));
}
void GRAPHremoveE(Graph G, int id1, int id2) {
    removeE(G, EDGEcreate(id1, id2, 0));
}
void GRAPHfree(Graph G){
    int v;
    link t, next;
    for (v=0; v < G->V; v++)
        for (t=G->ladj[v]; t != G->z; t = next) {
        next = t->next;
        free(t);
    }
    STfree(G->tab);
    free(G->ladj); free(G->z); free(G);
}

void dfsR(Graph G, Edge e, int *time, int *pre, int *post, int *st, int *fB){
    link t;
    int v, w = e.w;

    st[e.w] = e.v;
    pre[w] = (*time)++;
    for (t = G->ladj[w]; t != G->z; t = t->next)
        if (pre[t->v] == -1)
            dfsR(G, EDGEcreate(w, t->v, t->wt), time, pre, post, st, fB);
        else {
            v = t->v;
            if (post[v] == -1) (*fB)++;

        }
    post[w] = (*time)++;
}

int GRAPHdDfs(Graph G, int id) {
    int v, time=0, *pre, *post, *st, fB=0;
    pre= malloc(G->V * sizeof(int));
    post= malloc(G->V * sizeof(int));
    st = malloc(G->V * sizeof(int));
    for (v=0;v<G->V;v++) {
        pre[v]=-1; post[v]=-1; st[v]=-1;}
    dfsR(G, EDGEcreate(id,id, 0), &time, pre, post, st, &fB);
    for (v=0; v < G->V; v++)
        if (pre[v]==-1)
            dfsR(G,EDGEcreate(v,v, 0),&time,pre,post,st, &fB);

    free(pre);
    free(post);
    free(st);

    if(fB>0) return 1;
    return 0;
}


int bestSet(Graph g, Edge *sol, int *bsWt, int k){
    int i, totwt=0, f;

    for(i=0;i<k;i++){
        GRAPHremoveE(g, sol[i].v, sol[i].w);
        totwt+=sol[i].wt;
    }
    f=GRAPHdDfs(g, 0);

    for(i=0;i<k;i++){
        GRAPHinsertE(g, sol[i].v, sol[i].w, sol[i].wt);
    }

    if(!f && (*bsWt)<totwt) {
        (*bsWt)=totwt;
        return 1;
    }
    return 0;
}

int comb(int pos, Edge *val, Edge *sol, Edge* bsSol,Graph g, int *bsWt, int n, int k, int start, int cnt) {
    int i;
    if (pos >= k && bestSet(g,sol,bsWt, k)) {
        for (i=0; i<k; i++){
            bsSol[i]=sol[i];
        }
        return cnt+1;
    }
    for (i=start; i<n; i++) {
        sol[pos] = val[i];
        cnt = comb(pos+1, val, sol,bsSol,g, bsWt, n, k, i+1, cnt);
    }
    return cnt;
}


void minBackcardset(Graph G){
    int i, bsWt=0, cnt=0;

    Edge *a, *b, *sol;

    a=(Edge*)malloc(G->E*sizeof (Edge));
    b=(Edge*)malloc(G->E*sizeof (Edge));
    sol=(Edge*)malloc(G->E*sizeof (Edge));
    GRAPHedges(G, a);

    for(i=0;i<G->E && cnt==0;i++){//uscita anticipata dal for, i-1 sarà la cardinalità dell'insieme
        cnt=comb(0, a, b,sol,G,&bsWt, G->E, i, 0, 0);
    }
    if(cnt>0) cnt=i-1;
    printf("\nInsieme di archi a peso massimo che se rimossi rendono il grafo un DAG:\n");
    for(i=0;i<cnt;i++){
        printf("(%s,  %s) wt: %d\n", STsearchByIndex(G->tab, sol[i].v), STsearchByIndex(G->tab, sol[i].w), sol[i].wt);
        GRAPHremoveE(G, sol[i].v, sol[i].w);
    }
    DAGmaxdist( G);
    free(a);
    free(b);
    free(sol);
}

void TSdfsR(Graph D, int v, int *ts, int *pre, int *time) {
    link t; pre[v] = 0;
    for (t = D->ladj[v]; t != D->z; t = t->next)
        if (pre[t->v] == -1)
            TSdfsR(D, t->v, ts, pre, time);
    ts[(*time)++] = v;
}
void DAGmaxdist(Graph D) {

    int v,i, f, time = 0, nsource=0, *pre, *ts, *source;
    link t;
    pre= malloc(D->V * sizeof(int));
    ts= malloc(D->V * sizeof(int));
    source = malloc(D->V * sizeof(int));

    //determino un ordinamento topologico inverso del DAG
    for (v=0; v < D->V; v++) { pre[v] = -1; ts[v] = -1; }
    for (v=0; v < D->V; v++){
        if (pre[v]== -1) {
            TSdfsR(D, v, ts, pre, &time);//si usa la visita in profondità per farlo
        }
    }

    for (v=0; v < D->V; v++){//scorro il vettore dei vertici che si trovano in ordine topologico inverso
        f=0;//si osseva che partendo dai vertici più lontani si arriverà certamente a un nodo sorgente
        //il nodo sorgente è trovato quando finisce il vettore dell'ordine topologico inverso(tempi di completamento)
        //oppure quando il successivo vertice a essere completato non si trova nella sua lista di adiacenza
        for (t = D->ladj[ts[v]]; v!= 0 && t != D->z; t = t->next){
            if(t->v == ts[v-1]) f=1;
        }
        if(f==0 && v!=0) {
            source[nsource]=ts[v-1];
            nsource++;
        }
        printf("\n");
    }
    source[nsource]=ts[v-1];
    nsource++;

    printf("\nI nodi sorgenete sono\n");
    for(v=0;v<nsource && v<D->V;v++){
        printf("%s ", STsearchByIndex(D->tab,source[v]));
        time=0;
        for (i=0; i < D->V; i++) { pre[i] = -1; ts[i] = -1;}
        //eseguo nuove viste in profondià sui vertici sorgente per trovare i tempi di completamento di ciascuno di essi
        TSdfsR(D, source[v], ts, pre, &time);
        printf("Di distanza massima verso ogni altro nodo: %d\n",time-1);
        }
    free(pre);
    free(ts);
    free(source);
}


