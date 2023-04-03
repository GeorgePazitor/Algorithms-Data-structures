#include <stdio.h>
#include <stdlib.h>
void collanamax(int *num, char *val, int f);//wrapper
void collana(int pos,char *val,char **sol,int *num,int *k, int f);
//val vettore del tipo di pietre lungo 4
//sol vettore lunghezza z+s+r+t
//num vettore disponibilità pietre
//k lunghezza soluzione possibile(locale)
int cond(char p,char s);
int main() {
    int z=5;
    int s=10;
    int r=7;
    int t=4;
    int f=z+s+r+t;
    int num[]={z,s,r,t};
    char val[]={'z','s','r','t'};

    collanamax(num, val, f);

    return 0;
}

void collanamax(int *num, char *val, int f){//wrapper
    int k=0;
    char **sol;

    sol=malloc(2*sizeof(char*));
    sol[0]=malloc(f*sizeof(char));
    sol[1]=malloc(f*sizeof(char));

    collana(0,val,sol,num,&k,f);

    free(sol[1]);
    free(sol[0]);
    free(sol);
}
void collana(int pos,char *val,char **sol,int *num,int *k, int f){
    int i;
    if (pos >= f) {
        printf("---%d--\n", pos);
        for (i=0; i<f; i++)
            printf("%c ", sol[i]);
        printf("\n");
        return ;
    }
    for (i = 0; i < 4; i++) {
        if(num[i]>0){
            if(pos>0){
                if(cond(sol[0][pos-1],val[i])){
                    sol[0][pos] = val[i];
                    num[i]--;//prendo la pietra
                    collana(pos+1, val, sol, num, k, f);
                    num[i]++;//backtrack, rendo di nuovo disponibile la pietra annullando la scelta
                }
            }
            else{
                sol[0][pos] = val[i];
                num[i]--;
                collana(pos+1, val, sol, num, k, f);
                num[i]++;

            }
        }
    }
    if(pos>*k) {
        *k=pos;
        for(i=0;i<pos;i++){
            sol[1][i]=sol[0][i];
        }
    }
    if(pos==0){
        printf("\nCollana di lunghezza massima: %d\n", *k);
        for(i=0;i<*k;i++){
            printf("%c  ", sol[1][i]);
        }
    }

}

int cond(char p, char s){
    if(p=='z' || p=='t'){
        if (s=='z' || s=='r') return 1;
    }
    if(p=='s' || p=='r'){
        if (s=='s' || s=='t') return 1;
    }
    return 0;
}