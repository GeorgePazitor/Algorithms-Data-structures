#ifndef LAB8_2_ST_H
#define LAB8_2_ST_H
#include <stdio.h>
#include <stdlib.h>
#define MAXC 31
typedef struct symboltable *ST;

ST STinit(int maxN);
void STfree(ST st);

void STinsert(ST st, char val[MAXC], char val1[MAXC]);
int STsearch(ST st, char k[MAXC]);
int searchR(ST st, int l, int r, char k[MAXC]);

char* STselect(ST st, int r);


#endif //LAB8_2_ST_H
