#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FIN "../elementi.txt"
#define DP 35 //valore massimo di difficoltà del progrmma
#define DD 10 //valore massimo di difficolà per diagonale
#define DMAX 5 //massima lunghezza di una diagonale
#define NDIAG 3 //numero di diagonali in un programma
# define BONUS 1.5 //bonus elemento difficile in ultima diagonale

//test case 1 3


typedef struct elemento{
    char nome[100];
    int tipo;// l'elemento può essere un elemento acrobatico avanti [2], acrobatico indietro [1] o ditransizione [0]
    int dirin;// il ginnasta può entrare in un elemento frontalmente [1] o di spalle [0]
    int dirout;// il ginnasta può uscire da un elemento frontalmente [1] o di spalle [0]
    int prec;// l'elemento può essere eseguito come primo di una sequenza [0] o deve essere preceduto da almeno un altro elemento [1]
    int fin;// l'elemento non può essere seguito da altri elementi [1] o meno [0]
    float val;// il punteggio ottenuto dall'atleta per la corretta esecuzione di un elemento (reale)
    int diff;// la difficoltà di esecuzione dell'elemento (intero).
}elem;


//disp ripetute per gli elementi in una diagonale diagonali
int disp_rip(int pos,elem *val,elem *sol,int n,int k,int cnt, elem ***mDiag, int *nDiag, int totDiag, int diagDD, int **dDiag);

//combinazioni con ripetizione per le diagonali in un set di 3 diag
void comb_rip(int pos,elem **val, elem **sol, elem ***mprog, int n, int k, int start, float *valBest, int *dDiag);// con n=totDiag e k=3

int realloc_mDiag(elem ***mDiag, int *nDiag, int **dDiag);

int copyDiag(elem ***mDiag,int *dDiag, int n, elem *sol, int k);

int not_pruning_diag(int pos, int i, int k, elem *val, elem *sol, int diagDD);

void best(elem **sol, elem ***mProg, int k, float *valBest);

int main() {//disp ripetute e comb ripetute

    int i,j;
    int nel;        //nuemero elementi acquisito da file
    int nDiag=50;   //numero di diagonali che puo memorizzare mDiag appena inizializzata
    int totDiag=0;  //numero di diagonali trovate con disp_rip

    int *dDiag;     //vettore di difficoltà delle digonali inizializzato nelle disp_ripe e usato
                    // nelle comb_ripetute per il pruning

    elem *arrel;    // array degli elementi (val in disp_rip)
    elem *diag;     // array della diagonale corrente (sol in disp_rip)
    elem **mDiag;   //matrice delle diagonali
    elem **prog;    // matrice del programma corrente trovato
    elem **mProg;   //matrice del programma ottimo corrente


    FILE *fp;
    fp = fopen(FIN, "r");
    fscanf(fp, "%d", &nel);


    arrel=(elem*)malloc(nel*sizeof(elem));
    diag=(elem*)malloc(DMAX*sizeof(elem));
    mDiag=(elem**)malloc(nDiag*sizeof(elem*));

    dDiag=(int*)calloc(nDiag, sizeof(int));

    for(i=0; i<nel; i++){
        fscanf(fp,"%s %d %d %d %d %d %f %d\n",
               arrel[i].nome,
               &arrel[i].tipo,
               &arrel[i].dirin,
               &arrel[i].dirout,
               &arrel[i].prec,
               &arrel[i].fin,
               &arrel[i].val,
               &arrel[i].diff);
    }

    for(i=1; i<=DMAX; i++){
        totDiag += disp_rip(0, arrel, diag, nel, i, 0, &mDiag, &nDiag, totDiag, 0, &dDiag);
    }

    printf("Diagonali trovate: %d \n", totDiag);

    prog=(elem**)malloc(NDIAG*sizeof(elem*));
    mProg=(elem**)malloc(NDIAG*sizeof(elem*));
    for(i=0;i<NDIAG;i++){
        prog[i]=(elem*)malloc(DMAX*sizeof(elem));
        mProg[i]=(elem*)calloc(DMAX, sizeof(elem));
    }
    float valBest=0;

    comb_rip(0, mDiag, prog, &mProg, totDiag, NDIAG , 0, &valBest, dDiag);


    printf("TOT %f :\n", valBest);
    for(i=0;i<NDIAG;i++) {
        for (j = 0; j < DMAX; j++) {
            printf("%s %f ||", mProg[i][j].nome, mProg[i][j].val);
        }
        printf("\n");
    }


    free(arrel);
    free(diag);
    for(i=0;i<totDiag;i++){
        free(mDiag[i]);
    }
    free(mDiag);

    for(i=0;i<NDIAG;i++){
        //free(prog[i]); non riesco a deallocare le singole diagonali del vettore di diagonali usato per la soluzione
        free(mProg[i]);
    }
    free(prog);
    free(mProg);

    return 0;
}

int disp_rip(int pos,elem *val,elem *sol,int n,int k,int cnt, elem ***mDiag, int *nDiag, int totDiag, int diagDD, int **dDiag){
    int i;
    if (pos >= k) {
        if(cnt+totDiag>=*nDiag) realloc_mDiag(mDiag, nDiag, dDiag);
        if(copyDiag(mDiag, *dDiag, cnt+totDiag, sol, k)) return cnt+1;
        return cnt;
    }
    for (i = 0; i < n; i++) {
        sol[pos] = val[i];
        if(not_pruning_diag(pos, i, k, val, sol, diagDD))
            cnt = disp_rip(pos+1, val, sol, n, k, cnt, mDiag, nDiag, totDiag, diagDD+sol[pos].diff, dDiag);
    }
    return cnt;
}

int realloc_mDiag(elem ***mDiag, int *nDiag, int **dDiag){

    *nDiag=2*(*nDiag);
    (*mDiag) = (elem**)realloc(*mDiag, (*nDiag) * sizeof (elem*));
    (*dDiag) = (int*)realloc(*dDiag, (*nDiag) * sizeof (int));
    return 0;
}

int copyDiag(elem ***mDiag, int *dDiag, int n, elem *sol, int k){
    int i;
    int acrob=0;
    elem *c=(elem*) calloc(DMAX, sizeof(elem));//inizializza la diagonale a 0
    if(c==NULL) return 0;//fallita l'allocazione
    dDiag[n]=0;
    for (i=0; i<k; i++) {
        c[i]=sol[i];
        dDiag[n]+=sol[i].diff;
        if(c[i].tipo==1 || c[i].tipo==2) acrob++;
        }
    if(acrob==0){
        free(c);
        return 0;//diagonale senza alcun elemento acrobatico
    }
    (*mDiag)[n]=c;
    return 1;
}

int not_pruning_diag(int pos, int i, int k, elem *val, elem *sol, int diagDD){
    if(pos==0 && val[i].dirin!=1) return 0; //se l'elem è il primo ma non inizia frontalmente(una diag deve iniziare frontalmente)
    if(pos==0 && val[i].prec==1) return 0;
    if(pos!=k-1 && val[i].fin==1) return 0; //se l'elem non è l'ultimo della diag ma è finale

    if(pos!=0 && sol[pos-1].dirout != val[i].dirin) return 0; //direzione di uscita e di ingresso devono coincidere
    if(diagDD+val[i].diff>DD) return 0;

    return 1;
}

void comb_rip(int pos, elem **val, elem **sol, elem ***mProg, int n, int k, int start, float *valBest, int *dDiag) {
    int i;
    int diffProg=0;

    if (pos >= k) {
        best(sol, mProg, k, valBest);
        return;
    }

    for (i=start; i<n; i++) {
        if(diffProg+dDiag[i] <= DP){//pruning preventivo sulla difficoltà della diagonale
            sol[pos] = val[i];
            comb_rip(pos+1, val, sol, mProg, n, k, start, valBest, dDiag);
        }
        start++;
    }
}

void best(elem **sol, elem ***mProg, int k, float *valBest){
    int i,j;
    float valSol=0;
    float valDiag[3]={0,0,0}; //vettore di valore delle diagonali
    int diffSol=0;
    int avanti=0;
    int dietro=0;
    int seqacrob=0;
    int mult=0; //moltlipicatore 1.5 x (elemento di diff >=8 nell'ultima diagonale)
    int mult_best=-1;
    int not_best=0;

    elem tmp[DMAX];


    for(i=0;i<k;i++) {
        for (j = 0; j < DMAX; j++) { 
            if(strcmp(sol[i][j].nome,"")!=0) {
                valDiag[i] += sol[i][j].val;

                diffSol += sol[i][j].diff;
                if (j > 0)
                    if ((sol[i][j-1].tipo == 1 || sol[i][j-1].tipo == 2) &&
                        (sol[i][j].tipo == 1 || sol[i][j].tipo == 2))
                        seqacrob = 1;
                if (sol[i][j].tipo == 1) avanti++;
                if (sol[i][j].tipo == 2) dietro++;
                if (((j<DMAX-1 && strcmp(sol[i][j+1].nome,"")==0) || j==DMAX-1) && sol[i][j].diff >= 8) {
                    if (mult > 0 && valDiag[mult_best]<valDiag[i]){
                        mult_best=i;
                    }
                    else {
                        if(mult==0){
                            mult=1;
                            mult_best=i;
                        }
                    }
                }
            }
        }
        valSol+=valDiag[i];
    }
    if(mult==1) {
        valSol -=valDiag[mult_best];
        valSol +=(valDiag[mult_best]*BONUS);
    }

    if(avanti==0 || dietro==0) not_best=1;
    if(!seqacrob) not_best=1;
    if(diffSol>DP) not_best=1;

    if(not_best==0 && valSol>*valBest) {
        *valBest=valSol;
        for(i=0;i<k;i++) {
            for (j = 0; j < DMAX; j++) {
                (*mProg)[i][j] = sol[i][j];
                if(i==mult_best){
                    tmp[j]=sol[i][j];
                }
            }
        }
        if(mult_best>=0){
            for(i=mult_best;i<k-1;i++){
                for (j = 0; j < DMAX; j++) {
                    (*mProg)[i][j] = sol[i+1][j];
                }
            }
            for (j = 0; j < DMAX; j++) {
                (*mProg)[k-1][j] = tmp[j];//metto la diagonale moltiplicata della soluzione nell'ultima posizione
            }
        }
    }
}


