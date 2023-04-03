#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CMD 12
#define MC 50

typedef enum{//definizione di tipo enumeration per la creazione del menu'
    input_tastiera, input_file, ric_codice, elimina_codice, elimina_data, output, r_fine
}comando_e;

typedef struct{
    char cod[6];
    char nome[MC];
    char cogn[MC];
    char data[11];
    char via[MC];
    char citta[MC];
    int  cap;
}item;

typedef struct node {
    item val;
    struct node *next;
}node_t, *link;

//Prototipi delle funzioni base operanti su liste
link newNode(item val, link next);
link SortListIns(link h, item val);
void listTravR(link h);
item listSearch(link h, char *c);
item ItemSetVoid();
item listExtrKeyCod(link *h , char *c);
void listExtrdate(link *h, char idate[][11]);
item listExtrdatasingola(link *h, char idate [][11]);
void freelist(link h);

comando_e leggicomando(char cmd[]);
void intast(link *h);
void infile(link *h);
int Keygreater(char *a,char *b);


int main() {
    char cmd[CMD];
    int comando;
    int f=1;
    item x;
    char c[6];
    char idate[2][11];//gg/mm/aaaa
    link h = NULL;

    //menu
    while(f){
        fflush(stdin);
        comando=leggicomando(cmd);
        switch (comando) {
            case input_tastiera:
                intast(&h);
                break;

            case input_file:
                infile(&h);
                break;

            case ric_codice:
                printf("\n inserisci codice cittadino");
                scanf("%s", c);
                x=listSearch(h, c);
                if(strcmp(x.cod,"none")!=0){
                    printf("\n%s ", x.cod);
                    printf("%s ", x.nome);
                    printf("%s ", x.cogn);
                    printf("%s ", x.data);
                    printf("%s ", x.via);
                    printf("%s ", x.citta);
                    printf("%d ", x.cap);
                }
                else printf("\n Cittadino non trovato");

                break;

            case elimina_codice:
                printf("\n inserisci codice cittadino");
                scanf("%s", c);
                x=listExtrKeyCod(&h, c);
                if(strcmp(x.cod,"none")!=0){
                    printf("\n%s ", x.cod);
                    printf("%s ", x.nome);
                    printf("%s ", x.cogn);
                    printf("%s ", x.data);
                    printf("%s ", x.via);
                    printf("%s ", x.citta);
                    printf("%d ", x.cap);
                }
                else printf("\n Cittadino non trovato");

                break;

            case elimina_data:
                printf("\nInserisci le due date nel formato gg/mm/aaaa : ");
                scanf("%s", idate[0]);
                scanf("%s", idate[1]);
                listExtrdate(&h, idate);
                break;

            case output:
                listTravR(h);
                break;

            case r_fine: f=0; break;
            default: printf("Comando errato\n");
                //non funziona il comando errato:
                //in caso di input del comando errato il programma termina
        }
    }
    freelist(h);
    return 0;
}

comando_e leggicomando(char cmd[]){
    comando_e c; // funzione leggi comando per la gestione del menu' col tipo dato comando_e: enumeration
    char cmdp[CMD];//stringa che serve a contenere parola per il comando
    char tab[r_fine+1][CMD] = {
            "in_ta", "in_fi", "ric", "c_cod", "c_data", "stampa", "fine"
    };
    printf("\n\n-------------------------------------MENU'----------------------------------------\n");
    printf("| Digitare                                                                       |\n");
    printf("| in_ta       : per inserire da tastiera i dati di un nuovo cittadino            |\n");
    printf("| in_fi       : per inserire da file i dati di un nuovi cittadino                |\n");
    printf("| ric         : per ricercare un cittadino inserendone il codice                 |\n");
    printf("| c_cod       : per cancellare i dati di un cittadino inserendone il codice      |\n");
    printf("| c_data      : per cancellare i dati dei cittadini nati tra due date            |\n");
    printf("| stampa      : per stampare tutto il database delle anagrafe                    |\n");
    printf("| fine        : per terminare il programma                                       |\n");
    printf("----------------------------------------------------------------------------------\n");

    gets(cmd);
    sscanf(cmd, "%s", &cmdp);

    strlwr(cmdp);
    c=input_tastiera;
    while(c<r_fine && strcmp(cmdp, tab[c])!=0) c++;
    return c;
}

void intast(link*h){
    item new;//item appoggio per il nuovo input
    char c[5];

    //da rivedere la generazione del codice
    strcpy(new.cod,"A");
    itoa(rand()%1000,c,5);
    strcat(new.cod,c);

    printf("\nInserire il nome : ");
    scanf("%s", new.nome);
    printf("\nIl cognome : ");
    scanf("%s", new.cogn);
    printf("\nData di nascita nel formato gg/mm/aaaa : ");
    scanf("%s", new.data);
    printf("\nLa via : ");
    scanf("%s", new.via);
    printf("\nLa citta' di residenza : ");
    scanf("%s", new.citta);
    printf("\nIl cap : ");
    scanf("%di", &new.cap);
    *h= SortListIns(*h,new);
}

void infile(link*h){
    item new;//item appoggio per il nuovo input

    char fn[20];
    char filename[24]="../";
    FILE *fp;

    printf("\n Inserire il nome del file ( max 20 caratteri ): ");
    scanf("%s", fn);
    strcat(filename,fn);
    fp=fopen(filename,"r");

    while(fscanf(fp,"%s %s %s %s %s %s %d",new.cod,  new.nome,  new.cogn,  new.data,  new.via,  new.citta, &new.cap)!=EOF){
        *h= SortListIns(*h,new);
    }
    fclose(fp);
}

link newNode(item val, link next){

    link x = malloc(sizeof *x);

    if(x==NULL)
        return NULL;
    else{
        x->val=val;
        x->next=next;
    }

    return x;
}
link SortListIns(link h, item val) { //ritorna il puntatore alla testa
    link x, p; //con p puntatore al nodo precedente
    char k[11];//contiene la data del nodo che va inserito ordinatamente


    strcpy(k,val.data);

    if( h==NULL || Keygreater(h -> val.data, k)) //caso di inserimento in testa
        return newNode (val,h);
    for (x=h->next , p=h; x!=NULL && Keygreater(k,x ->val.data); p=x, x=x->next);
    p->next = newNode(val, x);

    return h;
}

int Keygreater(char *a,char *b){
    char x[11];
    char y[11];
    char z[11];

    char t[2]="/";
    char gg[3];
    char mm[3];
    char aaaa[5];

    strcpy(x,a);
    strcpy(y,b);

    sscanf(x,"%2s/%2s/%4s", gg, mm, aaaa);

    strcpy(z,aaaa);
    strcat(z,t);
    strcat(z,mm);
    strcat(z,t);
    strcat(z,gg);

    strcpy(x,z);

    sscanf(y,"%2s/%2s/%4s", gg, mm, aaaa);
    strcpy(z,aaaa);
    strcat(z,t);
    strcat(z,mm);
    strcat(z,t);
    strcat(z,gg);

    strcpy(y,z);

    if(strcmp(x,y)==1) return 1;
    else return 0;

}

item listSearch(link h, char *c){
    link x;
    for(x=h;x!=NULL;x=x->next)
        if(strcmp(x->val.cod,c)==0)
            return x->val;
    return ItemSetVoid();
}

item ItemSetVoid(){
    item a = { .cod="none",
            .nome="none",
            .cogn="none",
            .data="none",
            .via="none",
            .citta="none",
            .cap=0};
    return a;
}

item listExtrKeyCod(link *h , char *c) {
    link *xp, t;
    item i = ItemSetVoid();
    for (xp=h; (*xp) != NULL; xp = &((*xp)->next)) {
        if(strcmp((*xp)->val.cod, c)==0){
            t=*xp;
            *xp=(*xp)->next;
            i=t->val;
            free(t);
            break;
        }
    }
    return i;
}

void listTravR(link h){ //attraversamento ricorsivo in avanti
    if(h==NULL) return;
    printf("\n%s ", h->val.cod);
    printf("%s ",h->val.nome);
    printf("%s ",h->val.cogn);
    printf("%s ",h->val.data);
    printf("%s ",h->val.via);
    printf("%s ", h->val.citta);
    printf("%d ",h->val.cap);
    listTravR(h->next);
}
void listExtrdate(link *h, char idate[][11]){
    item i;
    for(i=listExtrdatasingola(h, idate) ; strcmp(i.nome,"none")!=0 ; i=listExtrdatasingola(h, idate)){
        printf("\n%s ", i.cod);
        printf("%s ",i.nome);
        printf("%s ",i.cogn);
        printf("%s ",i.data);
        printf("%s ",i.via);
        printf("%s ",i.citta);
        printf("%d ",i.cap);
    }

}

item listExtrdatasingola(link *h, char idate [][11]){
    link *xp, t;
    item i = ItemSetVoid();
    for (xp=h; (*xp) != NULL; xp = &((*xp)->next)) {
        if(Keygreater((*xp)->val.data, idate[0]) && Keygreater(idate[1], (*xp)->val.data)){
            t=*xp;
            *xp=(*xp)->next;
            i=t->val;
            free(t);
            break;
        }
    }
    return i;
}
void freelist(link h){
    link l;
    link tmp;
    l=h;
    while(l!=NULL){
        tmp=l;
        l=l->next;
        free(tmp);
    }
}

