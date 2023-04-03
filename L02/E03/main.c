#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MS 30
#define CMD 12

typedef enum{//definizione di tipo enumeration per la creazione del menù
    i_file, r_stampa, ord_data, ord_codice, ord_partenza, ord_arrivo, ric_partenza, r_fine
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

int file_in(tratta **l, tratta ***lp, int *n);
void menuparola(tratta *l, tratta **lp, int n);
comando_e leggicomando(char cmd[]);
void bubbleSort(tratta **lp,tratta ***lpo, int n, int s);
void ricercaDicotomica(tratta **lp, int n, char p[], int m);
void ricercaLineare(tratta **lp,int n, char p[], int m);
void stampa(tratta **lp, int n);


//Main------------------------------
int main() {
    tratta *log=NULL;// vettore di struct contenente il file di log in opportuna struttura dati
    tratta **logp=NULL;// vettore i puntatori a struct contenute in log
    int n;// numero delle righe del file

    //gestione del file con funzione di inizializzazione della struttura contenente le tratte

    file_in(&log, &logp,&n);// log, logp, n passata by reference

    menuparola(log, logp, n);

    return 0;

}
//Funzioni-----------------------------------
int file_in(tratta **l, tratta ***lp, int *n){
    int i;
    char filename[MS]="../";
    char name[MS];
    FILE *fp;
    tratta *t; //vettore di struct allocate in file_in per poi copiarne il primo indirizzo in l
    tratta **tp; //vettore puntatori a struct allocate in file_in per poi copiarne il primo indirizzo in lp

    printf("\nInserire nome del file\n");

    gets(name); // acquisizione del nome del file
    strcat(filename, name);

    fp=fopen(filename, "r");
    if(fp==NULL){printf("File Errore\n"); return 1;}

    fscanf(fp, "%d", n);

    t=(tratta*)malloc((*n)*(sizeof(tratta)));
    tp=(tratta**)malloc((*n)*(sizeof (tratta*)));

    for(i=0; i<*n; i++){ // acquisizione delle informazioni nel vettore di struct
        fscanf(fp, "%s %s %s ", &t[i].code, &t[i].partenza, &t[i].arrivo);
        fscanf(fp,"%s %s %s ", &t[i].data_t, &t[i].ora_p, &t[i].ora_a);
        fscanf(fp, "%d\n", &t[i].m_rit);
        tp[i]=&t[i];
    }
    fclose(fp);

    *l=t;
    *lp=tp;
    return 0;

}
void menuparola(tratta *l, tratta **lp, int n){
    //cmd contiene la stringa ottunuta con l'input
    char cmd[CMD];
    int comando;

    int f=1;// flag condizione di terminazione del menu'

    char ric_part[MS]; //stringa che contiene la partenza da ricercare
    int m; //lunghezza della stringa da ricercare

    //vettori di puntatori a strutture allocate in bubblesort
    //invece di tenere dei flag di avvenuto ordinamento inizializzo il vettore di puntatori a NULL
    //se è diverso da NULL allora vettore ordinato, altrimenti vettore non ordinato
    tratta **dataOrd=NULL;
    tratta **codiceOrd=NULL;
    tratta **partenzaOrd=NULL;
    tratta **arrivoOrd=NULL;

    while(f){
        fflush(stdin);
        comando=leggicomando(cmd);
        switch (comando) {
            case i_file:
                if(l!=NULL && lp!=NULL){
                    free(l);
                    free(lp);
                }
                if(dataOrd!=NULL) free(dataOrd);
                if(codiceOrd!=NULL) free(codiceOrd);
                if(partenzaOrd!=NULL) free(partenzaOrd);
                if(arrivoOrd!=NULL) free(arrivoOrd);


                dataOrd=NULL;
                codiceOrd=NULL;
                partenzaOrd=NULL;
                arrivoOrd=NULL;

                file_in(&l, &lp,&n);
                while(file_in(&l, &lp,&n)){
                    printf("\n Il nome del file potrebbe non essere valido, riprovare\n");
                }
                break;
            case r_stampa:
                stampa(lp, n);
                break;

            case ord_data:
                if (dataOrd!=NULL) {
                    printf("\nOrdinamento gia' avvenuto\n");
                }else{
                    bubbleSort(lp, &dataOrd, n, 0);
                }
                break;

            case ord_codice:
                if (codiceOrd!=NULL) {
                    printf("\nOrdinamento gia' avvenuto\n");
                }else{
                    bubbleSort(lp, &codiceOrd, n, 1);
                }
                break;

            case ord_partenza:
                if (partenzaOrd!=NULL) {
                    printf("\nOrdinamento gia' avvenuto\n");
                }else{
                    bubbleSort(lp, &partenzaOrd, n, 2);
                }
                break;

            case ord_arrivo:
                if (arrivoOrd!=NULL) {
                    printf("\nOrdinamento gia' avvenuto\n");
                }else{
                    bubbleSort(lp, &arrivoOrd, n, 3);
                }
                break;

            case ric_partenza:
                printf("Inserire la partenza sulla quale effettuare la ricerca delle corse\n");
                gets(ric_part);
                m=strlen(ric_part);
                if(partenzaOrd!=NULL){
                    ricercaDicotomica(partenzaOrd, n, ric_part, m);
                }else{
                    ricercaLineare(lp, n, ric_part, m);
                }
                break;

            case r_fine:
                if(l!=NULL && lp!=NULL){
                    free(l);
                    free(lp);
                }
                if(dataOrd!=NULL) free(dataOrd);
                if(codiceOrd!=NULL) free(codiceOrd);
                if(partenzaOrd!=NULL) free(partenzaOrd);
                if(arrivoOrd!=NULL) free(arrivoOrd);

                f=0;
                break;
            default: printf("Comando errato\n");//non funziona il comando errato
        }
    }
}

comando_e leggicomando(char cmd[]){
    comando_e c; // funzione leggi comando per la gestione del menù col tipo dato comando_e: enumeration
    char cmdp[CMD];//stringa che serve a contenere parola per il comando
    char tab[r_fine+1][CMD] = {
            "file_in","stampa", "o_data", "o_codice", "o_partenza", "o_arrivo", "r_partenza", "fine"
    };
    printf("Digitare\n");
    printf("file_in    :estrae dati dal file indicato\n");
    printf("stampa     :visualizza le corse disponibili\n");
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
    c=i_file;
    while(c<r_fine && strcmp(cmdp, tab[c])!=0) c++;
    return c;
}
void bubbleSort(tratta **lp, tratta ***lpo, int n, int s){
    //s è il selettore del ramo di switch, in base al suo valore si ordina per un certo criterio
    //0 data e ora
    //1 codice
    //2 partenza
    //3 arrivo
    int i,j, l=0, r=n-1;
    tratta **tpo;
    tratta *temp; //puntatore a struct per lo swap nell'ordinamento

    tpo=(tratta**)malloc(n*(sizeof (tratta*)));

    for(i=0;i<n;i++){
        tpo[i]=lp[i];
    }

    switch (s) {
        case 0:
            for (i = l; i < r; i++) {
                for (j = l; j < r - i + l; j++) {
                    if (strcmp(tpo[j]->data_t, tpo[j + 1]->data_t) == 1) {
                        temp = tpo[j];
                        tpo[j] = tpo[j + 1];
                        tpo[j + 1] = temp;
                    } else {
                        if (strcmp(tpo[j]->data_t, tpo[j + 1]->data_t) == 0) {
                            if (strcmp(tpo[j]->ora_p, tpo[j + 1]->ora_p) == 1) {
                                temp = tpo[j];
                                tpo[j] = tpo[j + 1];
                                tpo[j + 1] = temp;
                            }
                        }
                    }

                }
            }
            break;
        case 1:
            for (i = l; i < r; i++) {
                for (j = l; j < r - i + l; j++) {
                    if (strcmp(tpo[j]->code, tpo[j + 1]->code) == 1) {
                        temp = tpo[j];
                        tpo[j] = tpo[j + 1];
                        tpo[j + 1] = temp;
                    }
                }
            }
            break;
        case 2:
            for (i = l; i < r; i++) {
                for (j = l; j < r - i + l; j++) {
                    if (strcmp(tpo[j]->partenza, tpo[j + 1]->partenza) == 1) {
                        temp = tpo[j];
                        tpo[j] = tpo[j + 1];
                        tpo[j + 1] = temp;
                    }
                }
            }
            break;
        case 3:
            for (i = l; i < r; i++) {
                for (j = l; j < r - i + l; j++) {
                    if (strcmp(tpo[j]->arrivo, tpo[j + 1]->arrivo) == 1) {
                        temp = tpo[j];
                        tpo[j] = tpo[j + 1];
                        tpo[j + 1] = temp;
                    }
                }
            }
            break;
        default:
            printf("error");
    }
    *lpo=tpo;
    stampa(*lpo, n);
}

void ricercaDicotomica(tratta **lp, int n, char p[], int m){
    int l=0;
    int r=n;
    int q,i;//i serve a scorrere tutti gli elementi contigui che rispettano il criterio di ricerca
    while(l<=r){
        q=(l+r)/2;
        if(strncmp(lp[q]->partenza,p,m)==0){
            i=q;
            do{
                printf("%s %s %s ", lp[i]->code, lp[i]->partenza, lp[i]->arrivo);
                printf("%s %s %s ", lp[i]->data_t, lp[i]->ora_p, lp[i]->ora_a);
                printf("%d\n", lp[i]->m_rit);
                i++;
            }while(i<n && strncmp(lp[i]->partenza,p,m)==0);
            i=q-1;
            while(i>=0 && strncmp(lp[i]->partenza,p,m)==0){
                printf("%s %s %s ", lp[i]->code, lp[i]->partenza, lp[i]->arrivo);
                printf("%s %s %s ", lp[i]->data_t, lp[i]->ora_p, lp[i]->ora_a);
                printf("%d\n", lp[i]->m_rit);
                i--;
            }
            return;
        }
        if(strncmp(lp[q]->partenza,p,m)==1){
            r=q-1;
        }
        else{
            l=q+1;
        }
    }
}

void ricercaLineare(tratta **lp,int n, char p[], int m){
    int i;
    for(i=0;i<n;i++){
        if(strncmp(lp[i]->partenza,p,m)==0){
            printf("%s %s %s ", lp[i]->code, lp[i]->partenza, lp[i]->arrivo);
            printf("%s %s %s ", lp[i]->data_t, lp[i]->ora_p, lp[i]->ora_a);
            printf("%d\n", lp[i]->m_rit);
        }
    }
}

void stampa(tratta **lp, int n){
    int i;
    for(i=0; i<n; i++){ //output della struttura dati a video
            printf("%s %s %s ", lp[i]->code, lp[i]->partenza, lp[i]->arrivo);
            printf("%s %s %s ", lp[i]->data_t, lp[i]->ora_p, lp[i]->ora_a);
            printf("%d\n", lp[i]->m_rit);
        }
    printf("\n");
}

