#include <stdio.h>
#include <stdlib.h>
int powerset(int pos,int *val,int *sol,int n,int start,int cnt, int **e, int ne);
int ceck(int *sol, int **e, int ne, int nn);
int main() {
    int i;
    int n;//numero di vertici
    int ne;//numero di archi
    int c=0;

    int *v;//vettore dei nodi
    int **e;//vettore degli archi: (vertice 1, vertice 2)
    int *sol;//vettore delle soluzioni
    FILE *fp;

    fp= fopen("../grafo.txt","r");
    fscanf(fp,"%d%d", &n,&ne);

    //allocazioni
    e=(int**)malloc(ne*sizeof(int*));
    sol=(int*)malloc(n*sizeof(int));
    v=(int*)malloc(n*sizeof(int));

    for(i=0;i<n;i++){ //generazione del vettore dei nodi
        v[i]=i;
    }

    for(i=0;i<ne;i++){
        e[i]=(int*)malloc(2*sizeof(int));
        fscanf(fp,"%d%d\n",&e[i][0], &e[i][1]);
    }
    c=powerset(0,v,sol,n,0,c, e, ne);

    printf("\nIl numero di vertex cover e': %d", c);

    //deallocazioni
    for(i=0;i<ne;i++){
        free(e[i]);
    }
    free(e);
    free(v);

    return 0;
}
int powerset(int pos,int *val,int *sol,int n,int start,int cnt,int **e, int ne) {
    int i,out;
    if (start >= n) {
        out=ceck(sol, e, ne, pos);
        if(out){
            printf("(");
            for (i = 0; i < pos; i++){
                if(i!=0) printf(",");
                printf("%d", sol[i]);
            }
            printf(")");
            printf("  ");
            return cnt+1;
        }
        else return cnt;
    }
    for (i = start; i < n; i++) {
        sol[pos] = val[i];
        cnt = powerset(pos+1, val, sol, n, i+1, cnt,e, ne);
    }
    cnt = powerset(pos, val, sol, n, n, cnt,e, ne);
    return cnt;
}

int ceck(int *sol, int **e, int ne, int nn){
    int i,j,cc,pp=0;
    //ne = numero di archi
    //nn = pos numero di elementi in possibile soluzione
    //cc = 1 se l'arco i-esimo che incide su almeno uno dei nodi in possibile soluzione
    //pp = numero degli archi che incidono su almeno uno dei nodi in possibile soluzione

    for(i=0;i<ne;i++){
        cc=0;
        for(j=0;j<nn; j++){
            //vera se l'arco incide sul nodo j-esimo della possibile soluzione
            if((sol[j]==e[i][0] || sol[j]==e[i][1])) cc=1;
        }
        if(cc) pp++; //l'i-esimo arco rispetta la condizione di accettazione
    }
    if(pp==ne) return 1;//soluzione è vertex cover = tutti gli archi incidono su almeno uno dei nodi in soluzione
    return 0;
}