#include <stdio.h>
#include <string.h>
#define LOG "../corse.txt"
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

void file_in(tratta l[], tratta *lp[], FILE *fin, int *n);
void menuparola(tratta *lp[], int n);
comando_e leggicomando(char cmd[]);
void bubbleSort(tratta *l[],tratta *logp[], int n, int s);
void ricercaDicotomica(tratta *logp[], int n, char p[], int m);
void ricercaLineare(tratta *logp[],int n, char p[], int m);
void stampa(tratta *lp[], int n);//da modifica

//Main------------------------------
int main() {
    tratta log[MT];// contiene tutto il file log con informazioni suddivise secondo la struct tratta
    tratta *logp[MT];
    FILE *fp;
    int n;// numero delle righe del file

    //gestione del file con funzione di inizializzazione della struttura contenente le tratte
    fp=fopen(LOG, "r");
    if(fp==NULL){printf("File Errore\n"); return -1;}

    file_in(log, logp, fp, &n);// n passata reference
    fclose(fp);

    menuparola(logp, n);
    return 0;

}
//Funzioni-----------------------------------
void file_in(tratta l[],tratta *lp[], FILE *fin, int *n){
    int i;

    fscanf(fin, "%d", n);

    for(i=0; i<*n; i++){ // acquisizione delle informazioni nel vettore di struct
        fscanf(fin, "%s %s %s ", &l[i].code, &l[i].partenza, &l[i].arrivo);
        fscanf(fin,"%s %s %s ", &l[i].data_t, &l[i].ora_p, &l[i].ora_a);
        fscanf(fin, "%d\n", &l[i].m_rit);
        lp[i]=&l[i];// salvataggio nel vettore di puntatori l'indirizzo della struct
    }
}
void menuparola(tratta *lp[], int n){ // si passa solo il vettore di puntatori
    //cmd contiene la stringa ottunuta con l'input
    char cmd[CMD];
    int comando;
    int f=1;
    int dataOrdinato=0; //flag di avvenuto ordinamento della struttura dati per data(0 no , 1 si)
    int codeOrdinato=0; //flag di avvenuto ordinamento della struttura dati per codice(0 no , 1 si)
    int partOrdinato=0; //flag di avvenuto ordinamento della struttura dati per partenza(0 no , 1 si)
    int arrvOrdinato=0; //flag di avvenuto ordinamento della struttura dati per arrivo(0 no , 1 si)

    char ric_part[MS]; //stringa che contiene la partenza da ricercare
    int m; //lunghezza della stringa da ricercare
    tratta *dataOrd[MT];
    tratta *codiceOrd[MT];
    tratta *partenzaOrd[MT];
    tratta *arrivoOrd[MT];

    while(f){
        fflush(stdin);
        comando=leggicomando(cmd);
        switch (comando) {
            case r_stampa:
                stampa(lp, n);
                break;

            case ord_data:
                if (dataOrdinato) {
                    printf("\nOrdinamento gia' avvenuto\n");
                }else{
                    bubbleSort(lp, dataOrd, n, 0);
                    dataOrdinato = 1;
                }
                break;

            case ord_codice:
                if (codeOrdinato) {
                    printf("\nOrdinamento gia' avvenuto\n");
                }else{
                    bubbleSort(lp, codiceOrd, n, 1);
                    codeOrdinato = 1;
                }
                break;

            case ord_partenza:
                if (partOrdinato) {
                    printf("\nOrdinamento gia' avvenuto\n");
                }else{
                    bubbleSort(lp, partenzaOrd, n, 2);
                    partOrdinato = 1;
                }
                break;

            case ord_arrivo:
                if (arrvOrdinato) {
                    printf("\nOrdinamento gia' avvenuto\n");
                }else{
                    bubbleSort(lp, arrivoOrd, n, 3);
                    arrvOrdinato = 1;
                }
                break;

            case ric_partenza:
                printf("Inserire la partenza sulla quale effettuare la ricerca delle corse\n");
                gets(ric_part);
                m=strlen(ric_part);
                if(partOrdinato){// ricerca dicotomica per vettore ordinato
                    ricercaDicotomica(partenzaOrd, n, ric_part, m);
                }else{// altrimenti ricerca lineare
                    ricercaLineare(lp, n, ric_part, m);
                }
                break;

            case r_fine: f=0; break;
            default: printf("Comando errato\n");//non funziona il comando errato
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
    printf("stampa     :visualizza o scrivi su file il contenuto di log.txt\n");
    printf("o_data     :ordina la struttura dati per data e per ora a parita' di data e stampa\n");
    printf("o_codice   :ordina la struttura dati per codice tratta e stampa\n");
    printf("o_partenza :ordina la struttura dati per stazione di partenza e stampa\n");
    printf("o_arrivo   :ordina la struttura dati per stazione di arrivo e stampa\n");
    printf("r_partenza :per ricercare una corsa in base alla stazione di arrivo e stampa\n");
    printf("fine       :per terminare il programma\n");
    printf("---------------------------------------------------------------------------\n");

    gets(cmd);
    sscanf(cmd, "%s", &cmdp);

    strlwr(cmdp);
    c=r_stampa;
    while(c<r_fine && strcmp(cmdp, tab[c])!=0) c++;
    return c;
}
void bubbleSort(tratta *log[], tratta *logp[], int n, int s){
    int i,j, l=0, r=n-1;
    tratta *temp;
    for(i=0;i<n;i++){
        logp[i]=log[i];
    }
    //funzione di bubblesort che ordina in base al parametro s per
    //0 data
    //1 codice
    //2 partenza
    //3 arrivo
    switch (s) {
        case 0:
            for (i = l; i < r; i++) {
                for (j = l; j < r - i + l; j++) {
                    if (strcmp(logp[j]->data_t, logp[j + 1]->data_t) == 1) {
                        temp = logp[j];
                        logp[j] = logp[j + 1];
                        logp[j + 1] = temp;
                    } else {
                        if (strcmp(logp[j]->data_t, logp[j + 1]->data_t) == 0) {
                            if (strcmp(logp[j]->ora_p, logp[j + 1]->ora_p) == 1) {
                                temp = logp[j];
                                logp[j] = logp[j + 1];
                                logp[j + 1] = temp;
                            }
                        }
                    }

                }
            }
            break;
        case 1:
            for (i = l; i < r; i++) {
                for (j = l; j < r - i + l; j++) {
                    if (strcmp(logp[j]->code, logp[j + 1]->code) == 1) {
                        temp = logp[j];
                        logp[j] = logp[j + 1];
                        logp[j + 1] = temp;
                    }
                }
            }
            break;
        case 2:
            for (i = l; i < r; i++) {
                for (j = l; j < r - i + l; j++) {
                    if (strcmp(logp[j]->partenza, logp[j + 1]->partenza) == 1) {
                        temp = logp[j];
                        logp[j] = logp[j + 1];
                        logp[j + 1] = temp;
                    }
                }
            }
            break;
        case 3:
            for (i = l; i < r; i++) {
                for (j = l; j < r - i + l; j++) {
                    if (strcmp(logp[j]->arrivo, logp[j + 1]->arrivo) == 1) {
                        temp = logp[j];
                        logp[j] = logp[j + 1];
                        logp[j + 1] = temp;
                    }
                }
            }
            break;
        default:
            printf("error");

    }
    stampa(logp, n);
}

void ricercaDicotomica(tratta *logp[], int n, char p[], int m){
    int l=0;
    int r=n;
    int q,i;//i serve a scorrere tutti gli elementi contigui che rispettano il criterio di ricerca
    while(l<=r){
        q=(l+r)/2;
        if(strncmp(logp[q]->partenza,p,m)==0){
            i=q;
            do{
                printf("%s %s %s ", logp[i]->code, logp[i]->partenza, logp[i]->arrivo);
                printf("%s %s %s ", logp[i]->data_t, logp[i]->ora_p, logp[i]->ora_a);
                printf("%d\n", logp[i]->m_rit);
                i++;
            }while(i<n && strncmp(logp[i]->partenza,p,m)==0);
            i=q-1;
            while(i>=0 && strncmp(logp[i]->partenza,p,m)==0){
                printf("%s %s %s ", logp[i]->code, logp[i]->partenza, logp[i]->arrivo);
                printf("%s %s %s ", logp[i]->data_t, logp[i]->ora_p, logp[i]->ora_a);
                printf("%d\n", logp[i]->m_rit);
                i--;
            }
            return;
        }
        if(strncmp(logp[q]->partenza,p,m)==1){
            r=q-1;
        }
        else{
            l=q+1;
        }
    }


}
void ricercaLineare(tratta *logp[],int n, char p[], int m){
    int i;
    for(i=0;i<n;i++){
        if(strncmp(logp[i]->partenza,p,m)==0){
            printf("%s %s %s ", logp[i]->code, logp[i]->partenza, logp[i]->arrivo);
            printf("%s %s %s ", logp[i]->data_t, logp[i]->ora_p, logp[i]->ora_a);
            printf("%d\n", logp[i]->m_rit);
        }
    }
}

void stampa(tratta *lp[], int n){
    int i;
    for(i=0; i<n; i++){ //output della struttura dati a video
            printf("%s %s %s ", lp[i]->code, lp[i]->partenza, lp[i]->arrivo);
            printf("%s %s %s ", lp[i]->data_t, lp[i]->ora_p, lp[i]->ora_a);
            printf("%d\n", lp[i]->m_rit);
        }
    printf("\n");
}