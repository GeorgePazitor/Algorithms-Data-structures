#include "quot.h"

quot Qsetvoid(){
    quot t;
    t.num=0;
    t.den=0;
    t.dd=DTsetvoid();
    t.oo=ORAsetvoid();
    return t;
}
int Qisvoid(quot q){
    if(q.den==0) return 1;
    return 0;
}

void Qcalc(quot *q, int v, int n){
    q->num=q->num+(v*n);
    q->den=q->den+n;
}

void QsetDTeORA(quot *q,data d, ora o){
        q->dd=d;
        q->oo=o;
}

void Qdisp(quot q){
    float v;
    v=(float)q.num/(float)q.den;//casting esplicito delle singole variabili
    printf("\nQuotazione %f ,data %d/%d/%d ora modifica %d:%d ", v, q.dd.aa, q.dd.mm, q.dd.gg, q.oo.hh, q.oo.mi);
}

float Qretq(quot q){
    float v;
    v=(float)q.num/(float)q.den;//casting esplicito delle singole variabili
    return v;
}
