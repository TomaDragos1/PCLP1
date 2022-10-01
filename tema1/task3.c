#include <stdio.h>
#define nrshift 29
#define nrshiftdr 3
#define shiftop 2
#define nrshiftop 30
#define shiftdim 28
#define dimvec 8
#define bitishort 16
#define MAXBITI 128

void transf_bin(unsigned short x, int size, unsigned int v[], int indice) {
    int i = 0, j = (indice - 1) * bitishort;
    for (i = size * dimvec - 1; i >= 0; i--) {

        int b = ((1 << i) & x) != 0;
        v[j] = b;
        j++;

    }
}

int numar_bin(unsigned int v[], int i, int dim) {
    int a = 1;
    int sum = 0;
    for (int j = dim - 1; j >= i; j--) {

        if (v[j] != 0)
            sum += a;
        a = a * 2;
    }
    return sum;
}

int main()
{
    unsigned int nr = 0, cpynr = 0, n = 0;
    unsigned int v_opr[dimvec] = {0}, v[MAXBITI] ={0};
    scanf("%d", &nr);
    cpynr = nr;
    cpynr = (cpynr >> nrshift);
    n = cpynr + 1;
    cpynr = nr;
    cpynr = (cpynr << nrshiftdr);
    unsigned int j = 0;
    for (unsigned int i = 0; i < (n * 2); i = i + 2) {
        unsigned int cpynr2 = cpynr;
        cpynr2 = (cpynr2 >> nrshiftop);
         v_opr[j] = cpynr2;
        j++;
        cpynr = (cpynr << shiftop);
    }
    cpynr = (cpynr >> shiftdim) + 1;
    unsigned int dim = cpynr;
    unsigned int nrdecitire = 0;
    if (((n + 1) * dim) % bitishort != 0)
        nrdecitire = ((n + 1) * dim) / bitishort + 1;

    else
        nrdecitire = ((n + 1) * dim) / bitishort;


    for (unsigned int j = 1; j <= nrdecitire; j++) {
        unsigned short nr_citit = 0;
        scanf("%hd", &nr_citit);
        transf_bin(nr_citit, sizeof(unsigned short), v, j);
    }

    int sum = 0;
    int nr_cautat = 0;
    int k = 0;
    int cont = -1;

    for (unsigned int i = 0; (i < bitishort * nrdecitire) && cont !=(int)n; i++)
        if ((i + 1) % dim == 0) {
            nr_cautat = numar_bin(v, k, k + dim); {
                if (cont == -1)
                    sum = nr_cautat;
                if (v_opr[cont] == 0 && cont != -1)
                    sum = sum + nr_cautat;
                if (v_opr[cont] == 1 && cont != -1)
                    sum = sum - nr_cautat;
                if (v_opr[cont] == 2 && cont != -1)
                    sum = sum * nr_cautat;
                if (v_opr[cont] == 3 && cont != -1)
                    sum = sum / nr_cautat;
                cont++;
            }
            k = k + dim;
        }
    printf("%d\n", sum);
    return 0;
}