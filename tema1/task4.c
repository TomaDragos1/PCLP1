#include <stdio.h>
#define nrshift 29
#define nrshiftdr 3
#define shiftop 2
#define nrshiftop 30
#define shiftdim 28
#define dimvec 8
#define bitishort 16
#define MAXBITI 128
#define NUMARNR 9

void transf_bin(unsigned short x, int size,unsigned int v[], int indice) {
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
    unsigned int v_dim[NUMARNR] = {0};
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

    for (unsigned int i = 0; i < bitishort * nrdecitire && cont != (int)n; i++)
        if ((i + 1) % dim == 0) {
            nr_cautat = numar_bin(v, k, k + dim);
            cont++;
            v_dim[cont] = nr_cautat;
            k = k + dim;
        }

    sum = 0;

    for (unsigned int i = 0; i < n; i++) {
        if (v_opr[i] == 2 || v_opr[i] == 3) {
            unsigned int produs = v_dim[i];
            int ok = 0;
            for (int j = i; j <= cont && ok == 0; j++) {
                if (v_opr[j] == 2)
                    produs = produs * v_dim[j + 1];
                if (v_opr[j] == 3)
                    produs = produs / v_dim[j + 1];
                v_dim[j] = 0;
                if (v_opr[j + 1] == 0 || v_opr[j + 1] == 1) {
                    ok = 1;
                    v_dim[j + 1] = 0;
                }
            }
            if (i == 0)
                sum += produs;
            else {
                if (v_opr[i - 1] == 0)
                    sum += produs;
                if (v_opr[i - 1] == 1)
                    sum -= produs;
            }
        }
    }

    if (v_dim[0] != 0)
        sum += v_dim[0];

    for (int i = 1; i <= cont; i++) {
        if (v_dim != 0) {
            if (v_opr[i - 1] == 0)
                sum += v_dim[i];
            if (v_opr[i - 1] == 1)
                sum -= v_dim[i];
        }
    }

    printf("%d\n", sum);

    return 0;
}