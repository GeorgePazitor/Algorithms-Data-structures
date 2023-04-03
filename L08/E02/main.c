#include <stdio.h>
#include <string.h>
#include "graph.h"

#define MAXC 31
/*
 Si facciano anche le seguenti assunzioni:
 i nomi dei singoli nodi sono univoci all'interno del grafo
 non sono ammessi cappi
 tra due nodi c'è al massimo un arco (non è un multigrafo)
 le sotto-reti sono sotto-grafi non necessariamente connessi.
 */


int main(int argc,char **argv) {
    int f=1, f1, f2=0;
    FILE *fp;
    Graph g;
    char a[MAXC]="", b[MAXC]="", c[MAXC]="";

    fp=fopen(argv[1], "r");
    g=GRAPHload(fp);
    fclose(fp);

    while(f){
        fflush(stdin);
        printf("\n-----------------------------------------------------------------------------");
        printf("\nInserisci:"
               "\n1 Per stampare vertici e vertici a loro connessi in ordine alfabetico"
               "\n2 Per verificare se 3 vertici formano un grafo connesso con matrice di adiacenze"
               "\n3 Per verificare se 3 vertici formano un grafo connesso con lista di adiacenze"
               "\n4 Per generare la lista delle adiacenze a partire dalla matrice delle adiacenze"
               "\n0 Per terminare");
        printf("\n-----------------------------------------------------------------------------\n");
        scanf("%d", &f);
       switch(f){
           case 1:
               GRAPHdisplayAlpha(g);
               break;
           case 2:
               fflush(stdin);
               while(strcmp(a,b)==0 || strcmp(b,c)==0){
                   printf("\nInserire nome vertice 1 (massimo 30 caratteri):\n");
                   scanf("%s", a);
                   printf("\nInserire nome vertice 2 (massimo 30 caratteri):\n");
                   scanf("%s", b);
                   printf("\nInserire nome vertice 3 (massimo 30 caratteri):\n");
                   scanf("%s", c);
               }

               f1=GRAPH3complete(g, a, b, c);
               if(f1==1)printf("\nI tre vertici formano un grafo connesso");
               else {
                   if(f1==0) printf("I tre vertici non formano un grafo connesso");
                   else printf("Uno o piu' vertici non esiste");
               }
               break;
           case 3:
               if(f2!=0){
               fflush(stdin);
               while(strcmp(a,b)==0 || strcmp(b,c)==0){
                   printf("\nInserire nome vertice 1 (massimo 30 caratteri):\n");
                   scanf("%s", a);
                   printf("\nInserire nome vertice 2 (massimo 30 caratteri):\n");
                   scanf("%s", b);
                   printf("\nInserire nome vertice 3 (massimo 30 caratteri):\n");
                   scanf("%s", c);
               }

               f1=GRAPH3completeLadj(g, a, b, c);
               if(f1==1)printf("\nI tre vertici formano un grafo connesso");
               else {
                   if(f1==0) printf("I tre vertici non formano un grafo connesso");
                   else printf("Uno o piu' vertici non esiste");
               }
               }else printf("\nlista delle adiacenze non ancora generata");
               break;
           case 4:
               GRAPHladj(g);
               f2=1;
               break;
           case 0:
               f=0;
               break;
           default:
               printf("Input non valido");
       }
   }
    GRAPHfree(g);


    return 0;
}
