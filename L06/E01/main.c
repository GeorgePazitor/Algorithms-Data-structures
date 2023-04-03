#include <stdio.h>
#include <stdlib.h>
# define FN  "../att.txt"
typedef struct {
    int si;//tempo d'inizio
    int fi;//tempo di fine
}att;


void attMaxd(att *v, int n);
void attPrint(att*val, int*p, int i);
void MergeSort(att A[], int N);
void MergeSortR(att A[], att B[], int l, int r);
void Merge(att A[], att B[], int l, int q, int r);
int ceck(att a, att b);


int main() {

    int i, n;
    att *v;
    FILE *fp;

    fp= fopen(FN, "r");
    fscanf(fp, "%d", &n);
    v=malloc(n*sizeof(att*));

    for(i=0;i<n;i++){
        fscanf(fp, "%d %d", &v[i].si, &v[i].fi);
    }
    MergeSort(v, n);//sorting per fine degli intervalli

    for(i=0;i<n;i++){
        printf("(%d ,%d)\n", v[i].si, v[i].fi);
    }

    fclose(fp);
    attMaxd(v,n);
    free(v);


    return 0;
}

void attMaxd(att *v, int n){
    int i, j;
    int dt=0, di;// durata della soluzione migliore
    int last =1;
    int *p;//vettore delle posizioni del precedente di un elemento in sottosoluzione
    int *d;//vettore delle durate di sottosoluzioni prefisso dell'i-esimo elemento

    p=malloc(n*sizeof(int));
    d=malloc(n*sizeof(int));

    p[0]=-1;
    d[0]=v[0].fi-v[0].si;

    if(n>1) {
        for (i = 1; i < n; i++) {
            d[i] = v[i].fi - v[i].si;
            di = v[i].fi - v[i].si;
            p[i] = -1;

            for (j = 0; j < i; j++) {
                //controlla se il l'intervallo non tocca quello di cui è prefisso e l'ottimalità di quello corrente [j]
                //valutandone l'esito del suo sottoproblema già risolto
                if ((ceck(v[j], v[i])) && d[i] < di + d[j]) {
                    d[i] = di + d[j];
                    p[i] = j;

                }
            }
            if (dt < d[i]) {//se il problema risolto è migliore dell'ottimo corrente , diventa l'ottimo corrente
                dt = d[i];
                last = i;
            }
        }
    }

    printf("\nLa a durata massima e': ");
    attPrint(v,p,last);
    printf("\nDi durata : %d", dt);

    free(d);
    free(p);
}

void attPrint(att *val, int *p, int i){//stampa ricorsiva a partire dall'elemento in fondo alla soluzione ottima
    if(p[i]==-1){//caso terminale dal quale parte la stampa in risalita
        printf("(%d, %d)", val[i].si, val[i].fi);
        return;

    }
    //ricorre fino al fondo della soluzione otima partendo dall'ultimo elemento ed arrivando al primo
    attPrint(val, p, p[i]);
    printf("(%d, %d)", val[i].si, val[i].fi);//stampa in risalita degli intervalli
}

int ceck(att a, att b){
    if(a.si<b.fi && b.si<a.fi) return 0;
    else return 1;

}
void MergeSort(att A[], int N) {
    att *B;
    int l=0, r=N-1;
    B=malloc(N*sizeof(att*));
    MergeSortR(A, B, l, r);
}
void MergeSortR(att A[], att B[], int l, int r){
    int q;
    if (l >= r)
        return;
    q = (l + r)/2;
    MergeSortR(A, B, l, q);
    MergeSortR(A, B, q+1, r);
    Merge(A, B, l, q, r);
}
void Merge(att A[], att B[], int l, int q, int r) {
    int i, j, k;
    i = l;
    j = q+1;
    for (k = l; k <= r; k++)
        if (i > q)
            B[k] = A[j++];
        else if (j > r)
            B[k] = A[i++];
        else if (A[i].fi<A[j].fi || A[i].fi==A[j].fi)
            B[k] = A[i++];
        else
            B[k] = A[j++];
    for ( k = l; k <= r; k++ )
        A[k] = B[k];
}