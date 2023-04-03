#ifndef LAB8_3_TIME_H
#define LAB8_3_TIME_H
#include<stdio.h>
#include<string.h>


typedef struct {//aaaa/mm/gg e hh:mm
    int aa;
    int mm;
    int gg;
}data;

typedef struct orario{//aaaa/mm/gg e hh:mm
    int hh;
    int mi;
}ora;


int DTcmpData(data t1, data t2);// >1 se la prima è piu' recente della seconda, <1 se il contrario , 0 se uguali
data DTsetvoid();
ora ORAsetvoid();
data DTset(char s[11]);
ora ORAset(char s[6]);

#endif
