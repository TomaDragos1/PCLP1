#include <stdio.h>
#define nrshift 29
#define nrshiftdr 3
#define shiftop 2
#define nrshiftop 30
#define shiftdim 28
#define dimvec 8
#define bitishort 16


int main() {
    unsigned int nr = 0, cpynr = 0, n = 0;
    unsigned v_opr[dimvec] = {0};
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

    int k = -1;
    int sum = 0;
     for (unsigned int j = 0; j < nrdecitire; j++) {
        unsigned short nr_citit = 0;
        scanf("%hd", &nr_citit);
        for (unsigned int i = 0; i < bitishort / dim && k != (int)n; i++) {
            unsigned short cpy = nr_citit;
            cpy = (cpy << (i * dim));
            cpy = (cpy >> (bitishort - dim)); {
                if (k == -1)
                    sum = cpy;
                if (v_opr[k] == 0 && k != -1)
                    sum = sum + cpy;
                if (v_opr[k] == 1 && k != -1)
                    sum = sum - cpy;
                if (v_opr[k] == 2 && k != -1)
                    sum = sum * cpy;
                if (v_opr[k] == 3 && k != -1)
                    sum = sum / cpy;
            }
            k++;
        }
    }
    printf("%d\n", sum);
    return 0;
}
