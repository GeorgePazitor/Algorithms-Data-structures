#include <stdio.h>
#include <stdlib.h>
#define F1 "../tiles.txt"
#define F2 "../board.txt"

typedef struct{
    int r;//numero di righe
    int c;//numero di colonne
    int n;//caselle
    int k;//caselle non inizializzate
}scacchi;

typedef struct{
    char o;//colore T1 orizzontale
    char v;//colore T2 verticale
    int po;//valore T1 orizzontale
    int pv;//valore T2 verticale
}tes;//definizione delle tessere

typedef struct{
    int ntes;//posizione della tessera in questa casella nel vettore delle tessere
    int ru;//0 non tuotata, 1 ruotata
}cas;//definizione di una casella

typedef struct{
    int r;
    int c;
}index;

int disp(int pos,cas **sc,cas **sol,tes *tiles, int *mark, scacchi s, int cnt, index *w);
//fnzione che calcola il punteggio totalizzato dalla soluzione valutata
int calcolaPunteggio(cas **sol, tes *tiles, scacchi s);

//funzione che crea e inizializza le strutture dati
void init(tes **tiles,cas ***sc,cas ***sol,int  **mark,index **empty,scacchi *s);
//funzione che libera la memoria occupata dalle strutture dati usate
void freeall(cas **sol, cas **sc, tes *tiles,int *mark, scacchi s);


int main() {
    int i,j;
    tes *tiles=NULL;     //contiene le tessere nell'ordine col quale sono contenute nel file tiles.txt
    cas **sc=NULL, **sol=NULL;// sc conterrà la soluzione finale, sol le diverse possibili soluzioni finali
    int *mark=NULL;      //la i-esima posizione nel vettore è relativa all'i-esima posizione nel vettore tiles
    index *empty=NULL;   //vettore di elementi che contengono la riga e la colonna di una casella vuota in scacchiera
    scacchi s;      //struttura dati con informazioni della scacchiera
    int psc;        //punteggio della soluzione ottima

    init(&tiles, &sc, &sol, &mark, &empty,&s);

    psc=disp(0, sc, sol, tiles, mark,s, 0, empty);
    printf("\nLa soluzione e' %d punti:\n", psc);
    for (i=0;i<s.r;i++){
        for(j=0;j<s.c;j++){
            printf("%d/%d ", sc[i][j].ntes, sc[i][j].ru);
        }
        printf("\n");
    }

    //deallocazione
    freeall(sol, sc, tiles, mark, s);

    return 0;
}
void init(tes **tiles,cas ***sc,cas ***sol,int  **mark, index **empty,scacchi *s){
    int i,j;
    FILE *fp;
    fp= fopen(F1,"r");
    fscanf(fp,"%d\n", &s->n);


    (*tiles)=(tes*) malloc(s->n*sizeof(tes));
    (*mark)=(int*) calloc(s->n, sizeof (int));
    (*empty)=(index*) malloc(s->n*sizeof (index));

    for(i=0;i<s->n;i++){//inizializzo il vettore di tessere
        fscanf(fp,"%c %d %c %d\n", &(*tiles)[i].o,  &(*tiles)[i].po,  &(*tiles)[i].v,  &(*tiles)[i].pv);
    }
    fclose(fp);

    //input da file dell'inizializzazione della scacchiera
    fp= fopen(F2, "r");
    fscanf(fp,"%d %d\n", &s->r, &s->c);

    (*sc)=(cas**)malloc(s->r*sizeof (cas*));
    (*sol)=(cas**)malloc(s->r*sizeof (cas*));
    s->k=0;
    for(i=0;i<s->r;i++){

        (*sc)[i]=(cas*)malloc(s->c*sizeof (cas));
        (*sol)[i]=(cas*)malloc(s->r*sizeof (cas));

        for(j=0;j<s->c;j++){
            fscanf(fp,"%d/%d ",&(*sc)[i][j].ntes , &(*sc)[i][j].ru);
            (*sol)[i][j]=(*sc)[i][j];
            if((*sol)[i][j].ntes!=-1) {
                (*mark)[(*sol)[i][j].ntes]=1;//segno le posizioni da non considerare(già occupate da tessere)
            }
            else{//segno la riga e la colonna delle posizioni vuote
                (*empty)[s->k].r=i;
                (*empty)[s->k].c=j;
                s->k=s->k+1;//incremento il numero delle posizioni vuote
            }

        }
    }
    fclose(fp);
}
void freeall(cas **sol, cas **sc, tes *tiles,int *mark, scacchi s){
    int i;
    for(i=0;i<s.r;i++) {
        free(sc[i]);
        free(sol[i]);
    }
    free(sc);
    free(sol);
    free(tiles);
    free(mark);
}

int disp(int pos,cas **sc,cas **sol,tes *tiles,int *mark, scacchi s, int cnt, index *w){
    int i,p;
    if (pos >= s.k){
        p=calcolaPunteggio(sol,tiles, s);
        if(p>cnt){
            cnt=p;
            for (i=0; i<s.n; i++) {
                sc[i/s.c][i%s.c]=sol[i/s.c][i%s.c];// riga = i/c colonna = i%c

            }
        }
        return cnt;
    }
    for (i=0; i<s.n; i++){
        if (mark[i] == 0) {//uso mark per le posizioni in vettore
            mark[i] = 1;

            //prendendo la tessera nono ruotata

            sol[w[pos].r][w[pos].c].ntes=i ;
            sol[w[pos].r][w[pos].c].ru=0;
            cnt =disp(pos+1, sc, sol,tiles, mark, s, cnt, w);

            //prendendo la tessara ruotata

            sol[w[pos].r][w[pos].c].ntes=i ;
            sol[w[pos].r][w[pos].c].ru=1;
            cnt=disp(pos+1, sc, sol,tiles, mark, s,cnt, w);

            mark[i] = 0;
        }
    }
    return cnt;

}

int calcolaPunteggio(cas **sol, tes *tiles, scacchi s){
    char orizz;
    char vert;
    int po;
    int pv;
    int i,j;
    int a=0;
    int punt=0;
    int tot=0;

    for(i=0;i<s.r;i++){
        for(j=0;j<s.c;j++){
            if(sol[i][j].ru==0) {
                orizz=tiles[sol[i][j].ntes].o;
                po=tiles[sol[i][j].ntes].po;
            }else{
                orizz=tiles[sol[i][j].ntes].v;
                po=tiles[sol[i][j].ntes].pv;
            }
            if (a==0 && j > 0) {
                if(sol[i][j-1].ru==0){
                    if (tiles[sol[i][j - 1].ntes].o == orizz){punt+=po;}
                    else{a=1;punt=0;}
                }
                else{
                    if (tiles[sol[i][j - 1].ntes].v == orizz){punt+=po;}
                    else{a=1;punt=0;}
                }
            }
            else{punt=po;}
        }
        tot+=punt;
        a=0;
        punt=0;
    }

    a=0;punt=0;

    for(j=0;j<s.c;j++){
        for(i=0;i<s.r;i++){
            if(sol[i][j].ru==0) {
                vert=tiles[sol[i][j].ntes].v;
                pv=tiles[sol[i][j].ntes].pv;
            }else{
                vert=tiles[sol[i][j].ntes].o;
                pv=tiles[sol[i][j].ntes].po;
            }
            if (a==0 && i > 0) {
                if(sol[i-1][j].ru==0){
                    if (tiles[sol[i-1][j].ntes].v == vert){punt+=pv;}
                    else{a=1;punt=0;}
                }
                else{
                    if (tiles[sol[i-1][j].ntes].o == vert){punt+=pv;}
                    else{a=1;punt=0;}
                }
            }
            else{punt=pv;}
        }
        tot+=punt;
        a=0;
        punt=0;
    }
    return tot;
    }
