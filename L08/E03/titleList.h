#ifndef LAB8_3_TITLELIST_H
#define LAB8_3_TITLELIST_H
#include <stdio.h>
#include <string.h>
#include<stdlib.h>

#include "title.h"
#define MAXC 20

typedef struct list *Ltit;


Ltit Listinit();
void ListInsR(Ltit l, title val);
title ListSearchR(Ltit l, char k[MAXC]);
void Listdisp(Ltit l);
void Listfree(Ltit l);

#endif
