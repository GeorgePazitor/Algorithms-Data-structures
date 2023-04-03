#ifndef LAB9_1_ST_H
#define LAB9_1_ST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXC 30

typedef struct symbtab *ST;
ST STinit(int maxN);
void STfree(ST st);
void STinsert(ST st, char k[MAXC]);
int STsearch(ST st, char k[MAXC]);

char *STsearchByIndex(ST st,int v);
#endif
