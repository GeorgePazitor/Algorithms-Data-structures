#ifndef LAB8_2_GRAPH_H
#define LAB8_2_GRAPH_H
#include<stdio.h>
#include<stdlib.h>
#define MAXC 31
typedef struct edge { int v; int w; int wt; } Edge;
typedef struct graph *Graph;
Graph GRAPHinit(int V);

Graph GRAPHload(FILE *fin);
void GRAPHladj(Graph G);
void GRAPHinsertE(Graph G, int id1, int id2, int wt);
void GRAPHinsertEinLadj(Graph G, int id1, int id2, int wt);
void GRAPHfree(Graph G);

int GRAPH3complete(Graph G, char a[MAXC], char b[MAXC], char c[MAXC]);
int GRAPH3completeLadj(Graph G, char a[MAXC], char b[MAXC], char c[MAXC]);
void GRAPHdisplayAlpha(Graph G);

#endif //LAB8_2_GRAPH_H

