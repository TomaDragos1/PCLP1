#include <stdio.h>
#define nrshift 29
#define nrshiftdr 3
#define shiftop 2
#define nrshiftop 30
#define shiftdim 28

void afisare_op(unsigned int a) {
    if (a == 0)
        printf("+ ");
    if (a == 1)
        printf("- ");
    if (a == 2)
        printf("* ");
    if (a == 3)
        printf("/ ");
}

int main() {
    unsigned int nr = 0, cpynr = 0, n = 0;
    scanf("%d", &nr);
    cpynr = nr;
    cpynr = (cpynr >> nrshift);
    n = cpynr + 1;
    cpynr = nr;
    cpynr = (cpynr << nrshiftdr);
    printf("%d ", n);
    for (unsigned int i = 0; i < (n * 2); i = i + 2) {
        unsigned int cpynr2 = cpynr;
        cpynr2 = (cpynr2 >> nrshiftop);
        afisare_op(cpynr2);
        cpynr = (cpynr << shiftop);
    }
    cpynr = (cpynr >> shiftdim) + 1;
    printf("%d\n", cpynr);

    return 0;
}
