int majority(int *a, int N){
    int n1;//numero di elementi primo sottovettore
    int n2;//numero di elementi secondo sottovettore
    int i,x,y;
    //x :risultato della chiamata ricorsiva sul primo sottovettore
    //y :risultato della chiamata ricorsiva sul secondo sottovettore

    int rx=0, ry=0;//ricorrenze dei vavoriti dei sottovettori, all'interno del vettore di partenza

    if(N==1){//condizione di terminazione, vettore di un solo elemento
        return a[0];
    }
    //calcolo del numero di elementi di ciascun vettore e del punto di partenza di ogniuno
    n1=N/2;
    n2=N-(N/2);
    //chiamate ricorsive per ciascuna delle metà del vettore di partenza
    x=majority(a,n1);
    y=majority(&a[n1],n2) ;

    if(x==y) return x;//stesso favorito o entrambe -1

    for(i=0;i<N;i++){//conteggio delle occorrenze nel vettore di partenza
        if(a[i]==x) rx++;
        if(a[i]==y) ry++;
    }
        if(rx>N/2)
            return x;
        if(ry>N/2)
            return y;
        if(ry<=N/2 || rx<=N/2)
            return -1;
}


