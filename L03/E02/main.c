#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct{
    char **scelte; //vettore di stringhe contenente le canzoni scelte
    int n_scelte; //numero di canzoni scelte
}livello; // struct relativa al singolo amico

int princ_molt(int pos, livello *val, char **sol, int n, int cnt);


int main() {
    int i,j,c;
    FILE *fp;
    int n;
    livello *val; //contiene tutti i livelli
    char **sol; //contiene una delle possibili soluzioni

    fp=fopen("../brani.txt","r");
    fscanf(fp,"%d", &n);

    val=(livello*)malloc(n*sizeof(livello));

    for(i=0;i<n;i++){//iterazione in base al numero di amici(livelli)

        fscanf(fp,"%d", &val[i].n_scelte);//input numero di possibili scelte per ogni livello
        val[i].scelte=(char**)malloc(val[i].n_scelte * sizeof(char*));

        for(j=0;j<val[i].n_scelte;j++) {
            val[i].scelte[j]=(char*)malloc(255*(sizeof(char)));
            fscanf(fp,"%s", val[i].scelte[j]);//input della singola scelta per ogni livello
        }
    }
    fclose(fp);


    sol=(char**)malloc(n*(sizeof(char*)));
    for(i=0;i<n;i++){
        sol[i]=(char*)malloc(255*sizeof(char));
    }
    c=princ_molt(0, val, sol, n, 0); // richiamo della funzione ricorsiva

    printf("\nTutte le playlist possibili sono :%d\n", c);

    //deallocazione della memoria usata
    for(i=0;i<n;i++){
        for(j=0;j<val[i].n_scelte;j++) {
            free(val[i].scelte[j]);
        }
        free(val[i].scelte);
    }
    free(val);

    for(i=0;i<n;i++){
        free(sol[i]);
    }
    free(sol);

    return 0;
}
int princ_molt(int pos, livello *val, char **sol, int n, int cnt){
    int i;

    if(pos >=n){//caso di terminazione
        for(i=0;i<n;i++)//stampa la soluzione
            printf("%s ", sol[i]);
        printf("\n");
        return cnt+1;
    }
    for(i=0;i<val[pos].n_scelte;i++){//scorre le possibili scelte sul pos-esimo livello
        strcpy(sol[pos],val[pos].scelte[i]);
        cnt=princ_molt(pos+1, val, sol, n, cnt);//richiamo ricorsivo alla funzione
    }
    return cnt;
}