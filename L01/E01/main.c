char *cercaRegexp(char *src, char *regexp){
    char *p;
    char mcar[]="[]^\\.";       //stringa contenente tutti i caratteri aggiuntivi
    int l=strlen(mcar);     //lunghezza stringa contenente tutti i caratteri aggiuntivi
    int m=strlen(regexp);   //lunghezza della regexp
    int i,j,k,v,w,f=0;

    //i : dopo i controlli scorre i caratteri di src[]
    //j: dopo i controlli scorre i caratteri di regexp[]
    //k: valore precedente di j, se i due sono uguali la parola non è nell'insieme delle regexp
    //v: scorre i caratteri nelle parentesi quadre della regexp
    //w: flag che controlla se il carattere i-esimo di src rispetta le parentesi quadre della regexp
    //f: flag che deve rimanere 0 se i controlli sono andati bene, nella seconda parte è condizione di terminazione
    //controlli delle stringhe in input

    for(i=0; f==0 && regexp[i]!='\0' ;i++){
        if(!isalpha(regexp[i])){
            f=1; // deve azzerarsi altrimenti ci sono caratteri indesiderati
            for(j=0; j<l; j++)
            {
                if(regexp[i]==mcar[j]) {
                    f=0;
                }
            }
        }

    }

    for(i=0;f==0 && src[i]!='\0' ;i++){
        if(!isalpha(src[i])){
            if(src[i]!=' '){ f=1; }
        }
    }

    i=0;
    j=0;

    while(f==0 && src[i]!='\0'){
        k=j;
        if(src[i]!=' '){
            if(j==0){p=&src[i];}
            switch (regexp[j])
            {
                case '\\':
                    if (regexp[j + 1] == 'a' && islower(src[i])) {
                        j=j+2;//per saltare backslash ed 'a'
                    }
                    if (regexp[j + 1] == 'A' && isupper(src[i])) {
                        j=j+2;//per saltare backslash ed 'A'
                    }

                    break;

                case '.':
                    j++;

                    break;

                case '[':
                    if(regexp[j+1]!='^'){
                        w=0;
                        for(v=0; regexp[j+1+v]!=']';v++){
                            if(regexp[j+1+v]==src[i]) w=1; //se il carattere è presente alza flag
                        }
                        if(w) j=j+2+v; // se flag alzato scorre le due parentesi e i v caratteri tra le due
                    }
                    else{
                        w=0;
                        for(v=0; regexp[j+2+v]!=']';v++){
                            if(regexp[j+2+v]==src[i]) w=1; //se il carattere è presente alza flag
                        }
                        if(!w) j=j+3+v;// se flag non e' alzato scorre le due parentesi, la cuspide e i v caratteri
                    }

                    break;
                default://per altro carattere
                    if(src[i]==regexp[j]){
                        j++;
                    }
            }
        }
        else{ j=0; }
        if(j==k){ j=0; }// se j e k sono uguali la parola non è nell' insieme delle regexp
        //se si è arrivati alla fine della regexp e della parola senza problemi->cond. di terminazione
        if(j==m && (src[i+1]==' ' || src[i+1]=='\0')){ f=1;}
        i++;
    }
    if(f==0) p=NULL;
    return p;
}
