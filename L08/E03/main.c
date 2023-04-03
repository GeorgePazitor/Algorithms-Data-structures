#include <stdio.h>
#include <string.h>

#include "title.h"
#include "titleList.h"

#define MAXC 20

int main() {
    int f=1,f1=1; //flag per menu e sottomenu
    int n, q;//contatori di numero di titoli e numero di transazioni inserite da file
    int i, j;
    char name[MAXC], fn[MAXC],  filename[MAXC];
    char a[11], b[6];//stringhe per input di data e ora
    int c,d;
    float  s;
    FILE *fp;

    Ltit  L;
    title t;
    int ft;//flag di esistenza in lista del titolo

    fp= fopen("../F1.txt", "r");
    fscanf(fp,"%d", &n);
    printf("Titoli inseriti: \n");
    L=Listinit();

    for(i=0;i<n;i++){
        ft=1;//assumo che il titolo esista già
        fscanf(fp,"%s %d\n", name,&q);
        t=ListSearchR(L,name);//cerco titolo in lista, se non c'e lo creo nuovo
        if(t==NULL){
            t=TITinit(name);
            ft=0;//il titolo non esiste ancora il lista
        }
        for(j=0;j<q;j++){
            fscanf(fp,"%s %s %d %d\n", a, b, &c, &d);

            TITquotins(t, a,b,c,d);
        }
        if(ft==0) ListInsR(L,t);//se non esiste il titolo lo aggiungo
    }
    fclose(fp);
    Listdisp(L);

    while(f){
        fflush(stdin);
        printf("\n-----------------------------------------------------------------------------");
        printf("\nInserisci:"
               "\n1 Per inserire da file nuove transazioni nel sistema"
               "\n2 Per selezionare un titolo azionario per nome"
               "\n0 Per terminare");
        printf("\n-----------------------------------------------------------------------------\n");
        scanf("%d", &f);
        switch(f) {
            case 1:
                printf("\nInserire nome file: ");
                strcpy(fn,"../");
                scanf("%s", filename);
                strcat(fn,filename);
                fp= fopen(fn, "r");
                fscanf(fp,"%d", &n);
                printf("Titoli inseriti: \n");

                for(i=0;i<n;i++){
                    ft=1;//assumo che il titolo esista già
                    fscanf(fp,"%s %d\n", name,&q);
                    t=ListSearchR(L,name);//cerco titolo in lista, se non c'e lo creo nuovo
                    if(t==NULL){
                        t=TITinit(name);
                        ft=0;//il titolo non esiste ancora il lista
                    }
                    for(j=0;j<q;j++){
                        fscanf(fp,"%s %s %d %d\n", a, b, &c, &d);

                        TITquotins(t, a,b,c,d);
                    }
                    if(ft==0) ListInsR(L,t);//se non esiste il titolo lo aggiungo
                }
                fclose(fp);
                Listdisp(L);
                break;
            case 2:
                do {
                printf("\nInserisci nome titolo azionario valido:");
                scanf("%s", name);
                t = ListSearchR(L, name);
                }while(t==NULL);
                while(f1){
                    fflush(stdin);
                    printf("\n\t===========================================================");
                    printf("\n\tDel titolo selezionato mostrare:"
                           "\n\t1 Quotazione in una certa data"
                           "\n\t2 Quotazione minima e massima in un certo intervallo di date"
                           "\n\t3 Quotazione minima e massima lungo tutto il periodo registrato"
                           "\n\t4 Bilanciarne l'albero delle quotazioni"
                           "\n\t0 Per tornare al menu' principale");
                    printf("\n===========================================================\n");
                    scanf("%d", &f1);
                    fflush(stdin);
                    switch(f1){
                        case 1:
                            printf("Inserire una data nel formato aaaa/mm/gg\n");
                            scanf("%s", a);
                            TITsearchdata(t,a);
                            break;
                        case 2:
                            printf("Inserire intervallo di date delle quali stampare le quotazione\n");
                            printf("Inserire una data 1 nel formato aaaa/mm/gg\n");
                            scanf("%s", a);
                            printf("Inserire una data 2 nel formato aaaa/mm/gg\n");
                            scanf("%s", b);
                            TITdatainterv(t, a , b);
                            break;
                        case 3:
                            TITdatainterv(t, "0000/00/00", "9999/99/99");
                            break;
                        case 4:
                            printf("\nInserire una soglia di bilanciamento: ");
                            scanf("%f", &s);
                            TITceckbalancetree(t,s);

                            break;
                        case 0:
                            f1=0;
                            break;
                        default:
                            printf("Input non valido");
                    }
                }
                break;
            case 0:
                f=0;
                break;
            default:
                printf("Input non valido");
        }
    }

    Listfree(L);
    return 0;
}

