#include "utils.h"

void caesar(char sir[1000], int nr) {
    for (unsigned int i = 0 ; i < strlen(sir) ; i++) {
    if (sir[i] >= 'a' && sir[i] <= 'z') {
        sir[i] = ((sir[i] - 'a') + 26 - nr % 26) % 26 + 'a';
    }
    if (sir[i] >= 'A' && sir[i] <= 'Z') {
        sir[i] = ((sir[i] - 'A') + 26 - nr % 26) % 26 + 'A';
    }
    if (sir[i] >= '0' && sir[i] <= '9') {
        sir[i] = ((sir[i] - '0') + 10 - nr % 10) % 10 + '0';
    }
    }
}
void SolveTask2() {
    char cypertype[1000];
    scanf("%s", cypertype);

    // rezolvare caesar

    if (strcmp(cypertype, "caesar") == 0) {
        int nr;
        char cuvant[1000];
        char a;
        scanf("%d\n", &nr);
        scanf("%s", cuvant);
        cuvant[strlen(cuvant)] = '\0';
        caesar(cuvant, nr);
        printf("%s\n", cuvant);
    }

    // rezolvare viginere

    if (strcmp(cypertype, "vigenere") == 0) {
        char key[10];
        char code[1000];
        scanf("%s", key);
        key[strlen(key)] = '\0';
        scanf("%s", code);
        code[strlen(code)] = '\0';
        unsigned int contor = 0;

        // formare cod

        for (unsigned int i = 0; i < strlen(code); i++) {
            int nr = key[contor] - 'A';
            if (code[i] >= 'a' && code[i] <= 'z') {
                code[i] = ((code[i] - 'a') + 26 - nr) % 26 + 'a';
                contor++;
            }
            if (code[i] >= 'A' && code[i] <= 'Z') {
                code[i] = ((code[i] - 'A') + 26 - nr) % 26 + 'A';
                contor++;
            }
            if (code[i] >= '0' && code[i] <= '9') {
                code[i] = ((code[i] - '0') + 10 - nr % 10) % 10 + '0';
                contor++;
            }
            if (contor == strlen(key))
                contor = 0;
        }
        code[strlen(code)] = '\0';
        printf("%s\n", code);
    }

    // adunare

    if (strcmp(cypertype, "addition") == 0) {
        int nr;
        char a;
        scanf("%d", &nr);
        char add1[1000], add2[1000];
        scanf("%s", add1);
        add1[strlen(add1)] = '\0';
        scanf("%s", add2);
        add2[strlen(add2)] = '\0';
        caesar(add1, nr);
        caesar(add2, nr);
        char finaladd[1000];
        int carry = 0;
        int max;
        if (strlen(add1) > strlen(add2))
            max = (int)strlen(add1);
        else
            max = (int)strlen(add2);
        finaladd[max + 1] = '\0';
        int i = (int)strlen(add1) - 1;
        int j = (int)strlen(add2) - 1;

        // while pt adunare

        while (max >= 0) {
            int firstvalue;
            int secondvalue;
            if (i < 0) {
                firstvalue = 0;
            } else {
                firstvalue = add1[i] - '0';
            }
            if (j < 0) {
                secondvalue = 0;
            } else {
                secondvalue = add2[j] - '0';
            }
        int addition = firstvalue + secondvalue + carry;
            if (addition >= 10)
                carry = 1;
            else
                carry = 0;
            finaladd[max] = addition % 10 + '0';
            max--;
            j--;
            i--;
        }
        int ok = 0;

        // scoatere zerourilor

        for (unsigned int i = 0; i < strlen(finaladd) && ok == 0; i++) {
            if (finaladd[i] != '0') {
                ok = 1;
                memmove(finaladd, finaladd + i, strlen(finaladd) - i + 2);
            }
        }
        if (ok == 0)
            printf("0");
        else
            printf("%s\n", finaladd);
    }
}
