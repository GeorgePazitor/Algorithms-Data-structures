#include <stdio.h>
#include <string.h>
#define LOG "../log.txt"
#define OUT "../out.txt"
#define MT 1000
#define MS 30
#define CMD 12

typedef enum{//definizione di tipo enumeration per la creazione del menù
    r_stampa, ord_data, ord_codice, ord_partenza, ord_arrivo, ric_partenza, r_fine
}comando_e;

//Strutture-----------------------------

typedef struct{
    char code[MS];     //<codice_tratta>
    char partenza[MS]; //<partenza>
    char arrivo[MS];   //<destinazione>
    char data_t[11];       //<data>
    char ora_p[9];         //<ora_partenza>
    char ora_a[9];         //<ora_arrivo>
    int m_rit;         //<ritardo>
}tratta;

//Prototipi-------------------------

void file_in(tratta l[], FILE *fin, int *n);
void menuparola(tratta log[], int n);
comando_e leggicomando(char cmd[]);
void bubbleSort(tratta log[], int n, int s);
void ricercaDicotomica(tratta log[], int n, char p[], int m);
void ricercaLineare(tratta log[],int n, char p[], int m);
void stampa(tratta l[], int n);

//Main------------------------------
int main() {
    tratta log[MT];// contiene tutto il file log con informazioni suddivise secondo la struct tratta
    FILE *fp;
    int n;// numero delle righe del file

    //gestione del file con funzione di inizializzazione della struttura contenente le tratte
    fp=fopen(LOG, "r");
    if(fp==NULL){printf("File Errore\n"); return -1;}

    file_in(log, fp, &n);// n passata reference
    fclose(fp);

    menuparola(log, n);
    return 0;

}
//Funzioni-----------------------------------
void file_in(tratta l[], FILE *fin, int *n){
    int i;

    fscanf(fin, "%d", n);

    for(i=0; i<*n; i++){ // acquisizione delle informazioni nel vettore di struct
        fscanf(fin, "%s %s %s ", &l[i].code, &l[i].partenza, &l[i].arrivo);
        fscanf(fin,"%s %s %s ", &l[i].data_t, &l[i].ora_p, &l[i].ora_a);
        fscanf(fin, "%d\n", &l[i].m_rit);
    }
}
void menuparola(tratta log[], int n){
    //cmd contiene la stringa ottunuta con l'input
    char cmd[CMD];
    int comando;
    int f=1;
    int partOrdinato=0; //flag di avvenuto ordinamento della struttura dati per partenze(0 no , 1 si)
    char ric_part[MS]; //stringa che contiene la partenza da ricercare
    int m; //lunghezza della stringa da ricercare

    while(f){
        fflush(stdin);
        comando=leggicomando(cmd);
        switch (comando) {
            case r_stampa:
                stampa(log, n);
                break;

            case ord_data:
                bubbleSort(log, n, 0);
                partOrdinato=0;
                break;

            case ord_codice:
                bubbleSort(log, n, 1);
                partOrdinato=0;
                break;

            case ord_partenza:
                bubbleSort(log, n, 2);
                partOrdinato=1;
                break;

            case ord_arrivo:
                bubbleSort(log, n, 3);
                partOrdinato=0;
                break;

            case ric_partenza:
                printf("Inserire la partenza sulla quale effettuare la ricerca delle corse\n");
                gets(ric_part);
                m=strlen(ric_part);
                if(partOrdinato){// se il vettore delle fartenze è ordinato di fa ricerca dicotomica
                    ricercaDicotomica(log, n, ric_part, m);
                }
                else{// altrimenti lineare
                    ricercaLineare(log, n, ric_part, m);
                }
                break;

            case r_fine: f=0; break;
            default: printf("Comando errato\n");
            //non funziona il comando errato:
            //in caso di input del comando errato il programma termina
        }
    }
}

comando_e leggicomando(char cmd[]){
    comando_e c; // funzione leggi comando per la gestione del menù col tipo dato comando_e: enumeration
    char cmdp[CMD];//stringa che serve a contenere parola per il comando
    char tab[r_fine+1][CMD] = {
            "stampa", "o_data", "o_codice", "o_partenza", "o_arrivo", "r_partenza", "fine"
    };
    printf("Digitare\n");
    printf("stampa     :visualizza o stampa sul file il contenuto di log.txt\n");
    printf("o_data     :ordina la struttura dati per data e per ora a parita' di data\n");
    printf("o_codice   :ordina la struttura dati per codice tratta\n");
    printf("o_partenza :ordina la struttura dati per stazione di partenza\n");
    printf("o_arrivo   :ordina la struttura dati per stazione di arrivo\n");
    printf("r_partenza :per ricercare una corsa in base alla stazione di arrivo\n");
    printf("fine       :per terminare il programma\n");
    printf("---------------------------------------------------------------------------\n");

    gets(cmd);
    sscanf(cmd, "%s", &cmdp);

    strlwr(cmdp);
    c=r_stampa;
    while(c<r_fine && strcmp(cmdp, tab[c])!=0) c++;
    return c;
}
void bubbleSort(tratta log[], int n, int s){
    int i,j, l=0, r=n-1;
    tratta temp;
    //funzione di bubblesort che ordina in base al parametro s per
    //0 data
    //1 codice
    //2 partenza
    //3 arrivo
    switch (s) {
        case 0:
            for (i = l; i < r; i++) {
                for (j = l; j < r - i + l; j++) {
                    if (strcmp(log[j].data_t, log[j + 1].data_t)==1) {
                        temp=log[j];
                        log[j]=log[j+1];
                        log[j+1]=temp;
                    }
                    else{
                        if(strcmp(log[j].data_t, log[j + 1].data_t)==0) {
                            if(strcmp(log[j].ora_p, log[j + 1].ora_p)==1){
                                temp=log[j];
                                log[j]=log[j+1];
                                log[j+1]=temp;
                            }
                        }
                    }

                }
            }
            break;
        case 1:
            for (i = l; i < r; i++) {
                for (j = l; j < r - i + l; j++) {
                    if (strcmp(log[j].code, log[j + 1].code)==1) {
                        temp=log[j];
                        log[j]=log[j + 1];
                        log[j + 1]=temp;
                    }
                }
            }
            break;
        case 2:
            for (i = l; i < r; i++) {
                for (j = l; j < r - i + l; j++) {
                    if (strcmp(log[j].partenza, log[j + 1].partenza)==1) {
                        temp=log[j];
                        log[j]=log[j + 1];
                        log[j + 1]=temp;
                    }
                }
            }
            break;
        case 3:
            for (i = l; i < r; i++) {
                for (j = l; j < r - i + l; j++) {
                    if (strcmp(log[j].arrivo, log[j + 1].arrivo)==1) {
                        temp=log[j];
                        log[j]=log[j + 1];
                        log[j + 1]=temp;
                    }
                }
            }
            break;
        default: printf("error");

    }
}

void ricercaDicotomica(tratta log[], int n, char p[], int m){
    int l=0;
    int r=n;
    int q,i;//i serve a scorrere tutti gli elementi contigui che rispettano il criterio di ricerca
    while(l<=r){
        q=(l+r)/2;
        if(strncmp(log[q].partenza,p,m)==0){
            i=q;
            do{
                printf("%s %s %s ", log[i].code, log[i].partenza, log[i].arrivo);
                printf("%s %s %s ", log[i].data_t, log[i].ora_p, log[i].ora_a);
                printf("%d\n", log[i].m_rit);
                i++;
            }while(i<n && strncmp(log[i].partenza,p,m)==0);//valutazione lazy delle condizioni logiche:se la prima è falsa la seconda non viene valutata
            i=q-1;
            while(i>=0 && strncmp(log[i].partenza,p,m)==0){
                printf("%s %s %s ", log[i].code, log[i].partenza, log[i].arrivo);
                printf("%s %s %s ", log[i].data_t, log[i].ora_p, log[i].ora_a);
                printf("%d\n", log[i].m_rit);
                i--;
            }
            return;
        }
        if(strncmp(log[q].partenza,p,m)==1){
            r=q-1;
        }
        else{
            l=q+1;
        }
    }


}
void ricercaLineare(tratta log[],int n, char p[], int m){
    int i;
    for(i=0;i<n;i++){
        if(strncmp(log[i].partenza,p,m)==0){
            printf("%s %s %s ", log[i].code, log[i].partenza, log[i].arrivo);
            printf("%s %s %s ", log[i].data_t, log[i].ora_p, log[i].ora_a);
            printf("%d\n", log[i].m_rit);
        }
    }
}

void stampa(tratta l[], int n){
    int i;
    int c;
    FILE *fout;

    printf("\n0 per stampare a video\n1 per stampare su file\n");

    scanf("%d",&c);

    if(c==0){
        for(i=0; i<n; i++){ //output della struttura dati a video
            printf("%s %s %s ", l[i].code, l[i].partenza, l[i].arrivo);
            printf("%s %s %s ", l[i].data_t, l[i].ora_p, l[i].ora_a);
            printf("%d\n", l[i].m_rit);
        }
        printf("\n");
    }
    else{
        if(c==1){
            fout=fopen(OUT,"w");
            fprintf(fout, "%d\n", n);
            for(i=0; i<n; i++){ //output della struttura dati su file
                fprintf(fout, "%s %s %s ", l[i].code, l[i].partenza, l[i].arrivo);
                fprintf(fout,"%s %s %s ", l[i].data_t, l[i].ora_p, l[i].ora_a);
                fprintf(fout, "%d\n", l[i].m_rit);
            }
            fclose(fout);
        }
        else{
            printf("Comando errato\n");
        }
        printf("\n");
    }
}