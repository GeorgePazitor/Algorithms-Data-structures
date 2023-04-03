#ifndef LAB8_3_TITLE_H
#define LAB8_3_TITLE_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "qBST.h"
#define MAXC 20
typedef struct titolo *title;

title TITinit(char k[MAXC]);
char *TITgetname(title t);

void TITquotins(title t, char d[11], char o[6], int v, int n);

void TITquotdisp(title t, data d);
void TITsearchdata(title t,char data[11]);
void TITdatainterv(title  t , char d1[11], char d2[11]);
void TITceckbalancetree(title t, float s);
void TITfree(title v);
#endif //LAB8_3_TITLE_H
