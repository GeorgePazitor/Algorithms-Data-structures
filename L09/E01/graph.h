#ifndef LAB9_1_GRAPH_H
#define LAB9_1_GRAPH_H
#include <stdio.h>
#include <stdlib.h>

#include "ST.h"
#define MAXC 30
typedef struct edge { int v; int w; int wt; } Edge;
typedef struct graph *Graph;
Graph GRAPHinit(int V);
void GRAPHfree(Graph G);
Graph GRAPHload(FILE *fin);

void GRAPHinsertE(Graph G, int id1, int id2, int wt );
void GRAPHremoveE(Graph G, int id1, int id2);
void GRAPHedges(Graph G, Edge *a);
void minBackcardset(Graph G);
void DAGmaxdist(Graph D);
int GRAPHdDfs(Graph G, int id);
#endif //LAB9_1_GRAPH_H
