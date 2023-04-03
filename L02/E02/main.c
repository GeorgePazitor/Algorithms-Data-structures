#include <stdio.h>
#include <stdlib.h>
#define MAT "../mat"

void malloc2dP(int ***m, int r, int c);
void free2d(int **m, int r);
void leggif(int **m, FILE *fp, int r, int c);
void separa(int **mat, int **w, int **b, int r, int c,int *dimw,int *dimb);

int main() {

    int nr,nc,i,dimw, dimb;
    //dimw dimensione del vettore dei bianchi
    //dimb dimensione del vettore dei neri
    int **mat;
    FILE *fp;
    int *wh, *bl;; // puntatori a vettore di bianchi e di neri


    fp=fopen(MAT,"r");
    fscanf(fp,"%d %d\n", &nr, &nc);

    malloc2dP(&mat, nr, nc);//allocazione della matrice dinamica con passaggio by reference

    leggif(mat,fp, nr, nc);//input da file del contenuto della matrice

    fclose(fp);

    //i vettori vengono passati by reference(indirizzo di memoria dell'indirizzo di memoria del primo elemento del vettore)
    separa(mat,&wh, &bl, nr, nc, &dimw, &dimb);

    //seguono opportune deallocazioni di memoria ed output richiesti
    free2d(mat, nr);

    printf("\nIl vettore dei bianchi e': ");
    for(i=0;i<dimw;i++){
        printf("%d ", wh[i]);
    }
    printf("\nIl vettore dei neri e': ");
    for(i=0;i<dimb;i++){
        printf("%d ", bl[i]);
    }
    free(wh);
    free(bl);
    return 0;
}

void malloc2dP(int ***m, int r, int c){
    int **p; //alloca la matrice che conterrà gli interi del file
    int i;

    p=(int **)malloc(r*(sizeof (int)));//vettore di puntatori
    for(i=0; i<r ; i++){
        p[i]=(int *)malloc(c*sizeof (int));//ogni puntatore punta a un vettore di interi
    }
    *m=p;
}


void free2d(int **m, int r){
    int i;
    for (i=0;i<r;i++){
        free(m[i]);
    }
    free(m);
}

void leggif(int **m, FILE *fp, int r, int c){
    int i,j;

    for (i=0;i<r;i++){
        for(j=0;j<c;j++){
            fscanf(fp,"%d", &m[i][j]);
        }
    }

}

void separa(int **m, int **w, int **b, int r, int c,int *dimw,int *dimb){
    int i,j,x=0;

    //si assume che la scacchiera abbia il primo elemento bianco
    //a meno che entrambe gli indici non siano dispari gli elementi si equipartiscono in bianchi e neri
    *dimw=(r*c)/2;
    *dimb=*dimw;
    if(r%2!=0 && c%2!=0){ *dimw=*dimw+1;}//se entrambe gli indici sono dispari ci sarà un bianco in più

    //allocazione dello spazio per i vettori di interi passati by reference
    *w=(int *)malloc((*dimw)*(sizeof (int)));

    *b=(int *)malloc((*dimb)*(sizeof (int)));

    for (i=0;i<r;i++){
        for(j=0;j<c;j++){
            if((i+j)%2==0){//se la somma degli indici è pari allora inserisci in vettore di bianchi
                (*w)[x]=m[i][j];
            }
            else{//altrimenti inserisci in vettore di bianchi
                (*b)[x]=m[i][j];
                x++;
            }

        }
    }
}

