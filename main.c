#include <Stdio.h>
#include <Stdlib.h>
#include <math.h>

int main(){

    printf("Insira o indice do ultimo elemento(ex: x0,x1,x2...,xN):\n");
    int n;
    scanf("%d", &n);
    float x[n+1], y[n+1], h[n+1], alfa[n+1];
    int i;

    printf("Insira X e Y respectivamente(X espaco Y enter)\n");
    for(i=0; i<=n; i++){
        scanf("%f", &x[i]);
        scanf("%f", &y[i]);
    }

    printf("Insira o Xestimativa\n");
    float xe,ye,deltax;
    int intervalo;
    fflush(stdin);
    scanf("%f",&xe);

    //Calculo h
    for(i=0; i<=n-1;i++){
        h[i] = x[i+1]-x[i];

        if (xe>=x[i] && xe<x[i+1])
            intervalo = i;
    }

    //Decomposição de Crout para matriz tridiagonal
    for(i=1;i<=n-1;i++){
        alfa[i] = ((3/h[i])*(y[i+1] - y[i]) - (3/h[i-1]) * (y[i]-y[i-1]));
    }

    float l[n+1], u[n+1], z[n+1];
    l[0] = 1;
    u[0] = 0;
    z[0] = 0;

    for(i = 1; i<=n-1;i++){
        l[i] = ((2*(x[i+1]-x[i-1])) - (h[i-1] * u[i-1]));
        u[i] = h[i]/l[i];
        z[i] = ((alfa[i] - (h[i-1] * z[i-1]))/l[i]);
    }

    l[n] = 1;
    z[n] = 0;
    float c[n+1], b[n+1], d[n+1];
    c[n] = 0;

    for(i = n-1; i>=0; i--){
        c[i] = z[i] - (u[i]*c[i+1]);
        b[i] = (((y[i+1]-y[i])/h[i]) - ((h[i]*(c[i+1]+2*c[i]))/3));
        d[i] = ((c[i+1] - c[i])/ (3*h[i]));
    }

    for(i = 0; i <=n-1;i++){
        printf("s[%d] = %.6f + %.6f*(x-%.2f) + %.6f*(x-%.2f)^2 + %.6f(x-%.2f)^3\n",i, y[i], b[i], x[i], c[i], x[i],d[i],x[i]);
    }
    deltax = xe-x[intervalo];
    ye = y[intervalo]+b[intervalo]*(deltax)+c[intervalo]*(float)pow(deltax,2)+d[intervalo]*(float)pow(deltax,3);
    printf("ye = %.6f",ye);
    return 0;
}
