#include <stdio.h>
#include <stdlib.h>
# define FN  "../att1.txt"
typedef struct {
    int si;//tempo d'inizio
    int fi;//tempo di fine;
}att;


void attSel(int N, att *v);
void maxSubS(int pos,att *val,int **sol,int n, int start,int d, int *dt, int l);
int ceck(att a, att b);

int main() {

    int i, n=6;
    att *v;
    FILE *fp;

    fp= fopen(FN, "r");
    fscanf(fp, "%d", &n);
    v=malloc(n*sizeof(att*));

    for(i=0;i<n;i++){
        fscanf(fp, "%d %d", &v[i].si, &v[i].fi);
    }
    fclose(fp);
    attSel(n, v);
    free(v);


    return 0;
}
void attSel(int N, att *v){//funzione wrapper
    int i;
    int dt=0;// durata della soluzione migliore
    int **sol;

    sol=malloc(2*sizeof(int*));
    sol[0]=malloc(N*sizeof(int));//sol[0] contiene la soluzione da valutare
    sol[1]=malloc(N*sizeof(int));//sol[1] contiene la soluzione migliore
    maxSubS(0, v, sol, N, 0, 0, &dt, 0);


    printf("\nDurata max : %d", dt);
    for(i=0;i<N;i++){
        if(sol[1][i]!=-1)
        printf("\n(%d %d)", v[sol[1][i]].si, v[sol[1][i]].fi);
    }

    free(sol);
}

void maxSubS(int pos,att *val,int **sol,int n, int start, int d, int *dt, int l) {//comb semplici
    int i, t;
    if (pos < n) {
        for (i = start; i < n; i++) {
            if (l==i || ceck(val[l], val[i])) {

                sol[0][pos] = i;// la soluzione contiene gli indici del vettore di strutture val
                d = d + (val[i].fi - val[i].si);
                t=l;
                l=i;
                maxSubS(pos + 1, val, sol, n, i + 1, d, dt, l);

                sol[0][pos] = -1;// prendo l'elemento se valido, e poi non lo prendo per valutare la soluz migliore
                d = d - ( val[i].fi - val[i].si);
                l=t;
                maxSubS(pos + 1, val, sol, n, i + 1, d, dt, l);

            }
            else {
                sol[0][pos] = -1;
                maxSubS(pos + 1, val, sol, n, i + 1, d, dt, l);
            }
        }
    }
    else{
        if(d>*dt) {
            *dt=d;
            for (i = 0; i < n; i++) {
                sol[1][i] = sol[0][i];
            }
        }
    }
}
int ceck(att a, att b){
    if(a.si<b.fi && b.si<a.fi) return 0;
    else return 1;

}