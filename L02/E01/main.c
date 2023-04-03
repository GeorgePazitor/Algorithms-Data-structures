int gcd(int a,int b){
    int c;
    if(a<b){//per ipotesi bisogna avere che A sia maggiore di B, se non lo sono si scambiali
        c=a;
        a=b;
        b=c;
    }
    if(a==b){return a;}
    if(b==0){return a;}

    if(a%2==0 && b%2==0){ //A pari B pari
        c=2*gcd(a/2,b/2);
        return c;

    }
    if(a%2==1 && b%2==0){ //A dispari B pari
        c=gcd(a,b/2);
        return c;

    }
    if(a%2==0 && b%2==1){//A pari B dispari
        c=gcd(a/2,b);
        return c;
    }
    if(a%2==1 && b%2==1){//A dispari B dispari
        c=gcd((a-b)/2,b);
        return c;
    }
}


