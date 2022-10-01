#include "utils.h"

void SolveTask3() {
    char *sentence;
    char **cuvinte;
    char letter;
    int i = 0;
    int dim = 1;
    sentence = (char *)malloc(dim * sizeof(char));
    if (sentence == NULL) {
        return;
    }

    // alocare dinamica sir

    while (scanf("%c", &letter) != EOF) {
        if (i >= dim) {
            dim = dim * 2;
            char *temp;
            temp = (char *)realloc(sentence, dim);
            if (temp == NULL) {
                free(sentence);
                printf("nu e mem");
            } else {
                sentence = temp;
            }
        }
        if (letter == ',' || letter == ';' || letter == '!' || letter == '.')
            i--;
        else if (letter == '\n' && sentence[i - 1] != ' ')
            sentence[i] = ' ';
        else if (sentence[i - 1] == ' ' && letter == '\n')
            i--;
        else
            sentence[i] = letter;
        i++;
    }
    sentence[strlen(sentence)] = ' ';
    char *temp2 = (char *)realloc(sentence, strlen(sentence) + 1);
    if (temp2 == NULL) {
        free(temp2);
        free(sentence);
        return;
    } else {
        sentence = temp2;
        sentence[strlen(sentence) + 1] = '\0';
    }
    char *cpy;
    char *cpy2;
    cpy = strdup(sentence);
    if (cpy == NULL) {
        free(cpy);
        return;
    }
    cpy2 = strdup(sentence);
    if (cpy2 == NULL) {
        free(cpy2);
        return;
    }
    int nrcuv = 0;
    char *p;
    p = strtok(cpy, " ,.!;\n");
    while (p != NULL) {
        nrcuv++;
        p = strtok(NULL, " ,.!;\n");
    }
    free(cpy);
    cuvinte = (char **)malloc(sizeof(char *) * nrcuv);
    if (cuvinte == NULL) {
        free(cuvinte);
        return;
    }

    // formare matrice cuvinte dinamic

    int contor = 0;
    p = strtok(sentence, " ,.!;\n");
    while (p != NULL) {
        cuvinte[contor] = strdup(p);
        if (cuvinte[contor] == NULL) {
            for (int i = 0; i <= contor; i++) {
                free(cuvinte[contor]);
            }
            free(cuvinte);
            return;
        }
        contor++;
        p = strtok(NULL, " ,.!;\n");
    }
    free(sentence);
    int total = 0;
    char **ngrame;
    char **tempchar;
    ngrame = (char **)malloc(sizeof(char *) * (total + 1));
    if (ngrame == NULL) {
        free(ngrame);
        return;
    }

    // formare dinamic ngrame

    for (unsigned int i = 1; i < contor; i++) {
        char *crtword;
        crtword = (char *)malloc(strlen(cuvinte[i-1]) + strlen(cuvinte[i])+5);
        if (crtword == NULL) {
            free(crtword);
            return;
        }
        crtword[0] = ' ';
        int k = 1;
        for (int j = 0 ; j < strlen(cuvinte[i - 1]); j++) {
            crtword[k] = cuvinte[i - 1][j];
            k++;
        }
        crtword[k] = ' ';
        k++;
        for (int j = 0 ; j < strlen(cuvinte[i]) ; j++) {
            crtword[k] = cuvinte[i][j];
            k++;
        }
        crtword[k] = ' ';
        k++;
        crtword[k] = '\0';
        int ok = 0;
        for (int j = 0; j < total && ok == 0; j++) {
            if (strcmp(ngrame[j], crtword) == 0)
                ok = 1;
        }
        if (ok == 0) {
            tempchar = (char**)realloc(ngrame, (total + 1)* sizeof(char*));
            if (tempchar == NULL) {
                free(tempchar);
                free(ngrame);
                return;
            } else {
                ngrame = tempchar;
            }
        ngrame[total]=(char*)malloc(strlen(cuvinte[i-1])+strlen(cuvinte[i])+5);
            if (ngrame[total] == NULL) {
                for (int j = 0; j < total; j++) {
                    free(ngrame[j]);
                }
                free(ngrame);
                return;
            }
            ngrame[total] = crtword;
            total++;
        }
    }
    for (unsigned int i = 0; i < nrcuv; i++)
        free(cuvinte[i]);
    free(cuvinte);
    printf("%d\n", total);

    // cautare cu strstr si afisarea tutturor ngramelor si repetarile lor

    for (int i = 0; i < total; i++) {
        char *search;
        search = strstr(cpy2, ngrame[i]);
        int aparitii = 0;
        while (search != NULL) {
            search = strstr(search + 1, ngrame[i]);
            aparitii++;
        }
        ngrame[i][strlen(ngrame[i]) - 1] = '\0';
        memmove(ngrame[i], ngrame[i] + 1, strlen(ngrame[i]) - 1);
        ngrame[i][strlen(ngrame[i]) - 1] = '\0';
        printf("%s %d\n", ngrame[i], aparitii);
    }
    free(cpy2);
    for (unsigned int i = 0; i < total; i++) {
        free(ngrame[i]);
    }
    free(ngrame);
}

