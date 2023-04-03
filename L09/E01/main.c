#include <stdio.h>

#include "graph.h"

#define FN "../grafo2.txt"
int main() {
    FILE *fp;
    Graph g;

    fp=fopen(FN, "r");
    g=GRAPHload(fp);
    fclose(fp);

    if(GRAPHdDfs(g, 0)) {//dDfs modificata per riportare l'esistenza di archi back (return 1)
        printf("Il grafo non e' un DAG\n");
        minBackcardset(g);
    }
    else{
        printf("Il grafo e' gia un DAG\n");
        DAGmaxdist(g);
    }
    GRAPHfree(g);
    return 0;
}
