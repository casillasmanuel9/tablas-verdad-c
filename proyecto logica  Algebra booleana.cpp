#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<math.h>
//Juan Manuel Galindo Casillas

int cimaevalucacion(),pilavaciaevaluacion(),pilallenaevaluacion(int x);
void inicializarevaluacion(),pushevaluacion(int c,int x),popevaluacion();
int numerodevariables(char lin[30]);
int variables(char lin);
int convin(int numvar);
char desplegartablasdeverdad();
char a[30];
struct pila{
    char datos[50];
    int tope;

}p;
struct pilaevaluacion{
    int datos[50];
    int tope;
}eva;
int pilavacia(),pilallena(int x),Prioridadfuera(char opdor),PrioridadDentro(char opdor),operador(char ch);
void push(char c, int x),pop(),inicializar();
char cima();


int main(){
    char exprecion[30];
    int tam, numvar,com;

    printf("dame la expresión  booleana\n");
    printf("recuerde que la letra 'c' despues la variable significa el complemento de la variable \n");
    fflush(stdin);
    scanf ("%s", &exprecion);
    numvar=numerodevariables(exprecion);
    printf("el numero de variables es: %i\n", numvar);
    com=pow(2,numvar);
    printf("las combinaciones  posibles son 2^%i = %i ",numvar,com);
    getch();
    return 0;

}

int numerodevariables(char exprecion[30]){
    char numvar[5];
    char a[30];

    int x,i,q;
    int tam,k,z,j;
    char v,cp[10];
    k=0;
    j=0;
    x=strlen(exprecion);
    printf("El tamaño de la linea es %i\n",x);
    for (i=0;i<x;i++){
            if (variables(exprecion[i])==1){
                    fflush(stdin);

                    if (i==0){
                        a[i]=exprecion[i];
                        j=j+1;
                    }else{
                        k=0;
                        z=0;
                        while(k<j && z==0){
                            fflush(stdin);
                            if(a[k]!=exprecion[i] && exprecion[i]!=('c')){
                                z=0;
                                fflush(stdin);
                            }else{
                                z=1;
                            }
                            k++;
                        }
                        if (z!=1){
                            fflush(stdin);
                            a[j]=exprecion[i];
                            j++;
                        }
                    }

            }

    }
    fflush(stdin);

    tam=pow(2,j);
    printf("numero de variables %i \n",j);
    int tab[tam][j+1];
    i=0;
    int r=0,e=0,t;
    t=(tam);
    while(r<j){
        t=t/2;
        while (i<tam){
            while(e<t){
                    tab[i][r]=1;
                    i++;
                    e++;
            }
            e=0;
            while(e<t){
                tab[i][r]=0;
                i++;
                e++;
            }
            e=0;
        }
        i=0;
        r++;
    }



    inicializar();

    char ch;
    int apilado;
    char post[50];
    for(i=0;i<x;i++){
        if(operador(exprecion[i])==1){
            apilado=0;
            while (apilado!= 1){
                if (pilavacia()==1){
                    push(exprecion[i],x);
                    apilado=1;
                }else{
                    ch=cima();
                    if (PrioridadDentro(ch)>=Prioridadfuera(exprecion[i])){
                        post[e]=ch;
                        e++;
                        pop();
                    }else{
                        push(exprecion[i],x);
                        apilado=1;
                    }
                }
            }
        }else{
            if (exprecion[i]==(')') ){
                ch=cima();
                pop();
                while (ch!= ('(')){
                        post[e]=ch;
                        e++;
                        ch=cima();
                        pop();
                }
            }else{
                post[e]=exprecion[i];
                e++;
            }
        }
    }
    while (pilavacia()!=1){
        ch=cima();
        pop();
        post[e]=ch;
        e++;
    }

    int w,o,u;
    u=0;
    o=0;
    w=0;
    char cal[50];
    i=0;
    int koko=0;
    while (o < tam){
        i=0;
        koko=0;

            while (i<e){
                    if(post[i]!=('*') && post[i]!=('+') ){
                            if (post[i]==a[w]){
                                    v=tab[o][w];
                                    itoa(v,cp,10);
                                    if(post[i+1]==('c')){
                                        if(cp[0]=='0'){
                                            cp[0]='1';
                                        }else{
                                            cp[0]='0';
                                        }
                                    }
                                    cal[koko]=cp[0];

                                    koko++;
                                    i++;
                            }else{
                                    if(post[i]==('c')){
                                        i++;

                                    }else{
                                        if(w+1<j){
                                           w++;
                                        }else{
                                            w=0;
                                        }
                                    }
                                }
                            }else{
                                cal[koko]=post[i];
                                i++;
                                koko++;
                            }
                }
            inicializarevaluacion();
            float valor1,valor2,valor3;
            int y;
            char aux[3];
            for (y=0;y<koko;y++){
                if( variables(cal[y])!=1){
                    valor2=cimaevalucacion();
                    popevaluacion();
                    valor1=cimaevalucacion();
                    popevaluacion();
                    switch(cal[y]){
                    case ('*'):
                        valor3=valor1*valor2;
                        break;
                    case ('+'):
                        valor3=valor1+valor2;
                        if(valor3>1){
                            valor3=1;
                        }
                        break;
                    default:
                        printf("error");
                    }
                    pushevaluacion(valor3,koko);
                }else{
                    aux[0]=cal[y];
                    valor3=atoi(aux);
                    pushevaluacion(valor3,koko);
                }
            }
            valor1=cimaevalucacion();
            popevaluacion();
            tab[o][j]=valor1;
            o++;

            i=0;
            while (i<koko){
                cal[i]='\0';
                i++;
            }
    }

    printf("tabla de verdad\n");
    q=0;
    for (q=0;q<j;q++){
        printf("%c      ",a[q]);
    }

    printf("%s \n",exprecion);
    for (i=0;i<x;i++){
        printf("_______");
    }
    printf("\n");
    for (r=0;r<tam;r++){
            for (i=0;i<j+1;i++){
                printf("%i      ",tab[r][i]);
            }
            printf("\n");
    }
    for (i=0;i<x;i++){
        printf("_______");
    }
    printf("\n");


    return j;

}

int variables(char lin){
    if (lin!= ('/') && lin!= ('*') && lin!= ('-') && lin!= ('+') && lin != ('(') && lin != (')') && lin != ('c')){
        return 1;
    }else{
        return 0;
    }
}
int PrioridadDentro( char opdor){
    switch ( opdor){
    case ('('):
        return 0;
        break;
    case ('*'):
        return 2;
        break;
    case ('+'):
        return 1;
        break;
    case ('-'):
        return 1;
        break;
    default:
        printf("error");

    }

}
int Prioridadfuera(char opdor){
   switch ( opdor){
    case ('('):
        return 5;
        break;
    case ('*'):
        return 2;
        break;
    case ('+'):
        return 1;
        break;
    case ('-'):
        return 1;
        break;
    default:
        printf("error");

    }

}

int operador(char ch){
    if (ch==('(') || ch==('+') || ch==('-') || ch==('*') ){
            return 1;
        }else{
            return 0;
        }
}

void inicializar(){
    p.tope=-1;
}

void push(char c, int x){
    if (pilallena(x)!=1){
        p.tope=p.tope+1;
        p.datos[p.tope]=c;
    }else{
        printf("pilallena");
    }
}

void pop(){
    if (pilavacia()!=1){
        p.tope=p.tope-1;
    }else{
        printf("pilavacia");
    }

}

int pilallena(int x){
    if (p.tope==(x-1)){
        return 1;
    }else{
        return 0;
    }
}

int pilavacia(){
    if (p.tope==-1){
        return 1;
    }else{
        return 0;
    }

}

char cima(){
    if (pilavacia()!=1){
        return p.datos[p.tope];
    }else{
        printf("pila vacia");
    }
}

int cimaevalucacion(){
    if (pilavaciaevaluacion()!=1){
        return eva.datos[eva.tope];
    }else{
        printf("pila vacia");
    }
}

void popevaluacion(){
    if (pilavaciaevaluacion()!=1){
        eva.tope=eva.tope-1;
    }else{
        printf("pilavacia");
    }

}
int pilavaciaevaluacion(){
    if (eva.tope==-1){
        return 1;
    }else{
        return 0;
    }

}
int pilallenaevaluacion(int x){
    if (eva.tope==(x-1)){
        return 1;
    }else{
        return 0;
    }
}
void pushevaluacion(int c, int x){
    if (pilallenaevaluacion(x)!=1){
        eva.tope=eva.tope+1;
        eva.datos[eva.tope]=c;
    }else{
        printf("pilallena en evaluacion");
    }
}
void inicializarevaluacion(){
    eva.tope=-1;
}
