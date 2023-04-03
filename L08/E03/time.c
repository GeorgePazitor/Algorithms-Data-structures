#include "time.h"
//oss: l'ora verrà utilizzata per indicare l'ora dell'ultimo inserimento per quel giorno
//aaaa/mm/gg e hh:mm

int DTcmpData(data t1, data t2){// >1 se la prima è piu' recente della seconda, <1 se il contrario , 0 se uguali
    char s1[11];
    char s2[11];

    sprintf(s1, "%4.d/%2.d/%2.d", t1.aa, t1.mm, t1.gg);
    sprintf(s2, "%4.d/%2.d/%2.d", t2.aa, t2.mm, t2.gg);

    return strcmp(s1, s2);

}

data DTset(char s[11]){
    data t;
    sscanf(s, "%d/%d/%d",&t.aa, &t.mm, &t.gg );
   return t;
}

ora ORAset(char s[6]){
    ora o;
    sscanf(s, "%d:%d",&o.hh, &o.mi );
    return o;
}

data DTsetvoid(){
    data t;
    t.aa=-1;
    t.mm=-1;
    t.gg=-1;
    return t;
}

ora ORAsetvoid(){
    ora t;
    t.hh=-1;
    t.mi=-1;
    return t;
}
