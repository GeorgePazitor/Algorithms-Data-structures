#ifndef LAB8_3_QUOT_H
#define LAB8_3_QUOT_H

#include "time.h"

typedef struct quotazione{ //si memorizza numeratore e denominatore della media ponderata in modo tale da poterla modificare dopo
    int num; //numeratore della media ponderata
    int den; //denominatore della media ponderata
    data dd; //data sulla quale è calcolarta la quotazione
    ora oo;//ora ultimo inserimento per la quotazione relativa alla data dd
}quot;

quot Qsetvoid();
void Qcalc(quot *q, int v, int n);
void QsetDTeORA(quot *q,data d, ora o);
int Qisvoid(quot q);
void Qdisp(quot q);
float Qretq(quot q);
#endif //LAB8_3_QUOT_H

