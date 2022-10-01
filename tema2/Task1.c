#include "utils.h"

int palindrom(char *word) {
    int size = strlen(word) / 2;
    for (int i = 0; i < size; i++) {
        if (word[i] != word[strlen(word) - 1 - i])
            return 0;
    }
    return 1;
}
int nrprim(char *word) {
    int nrcrt = (word[0] - '0') * 10 + word[1] - '0';
    for (int i = 2; i < nrcrt / 2; i++) {
        if (nrcrt % i == 0)
            return 0;
    }
    return 1;
}
void SolveTask1() {
    int n, m, contor = 1;
    int crtcolumn = 0, crtline = 0;
    scanf("%d %d\n", &n, &m);
    int **traseu;
    traseu = (int **)calloc(n, sizeof(int *));

    // alocare dinamica matrice si sir

    if (traseu == NULL) {
        free(traseu);
        return;
    }
    for (int i = 0; i < n; i++) {
        traseu[i] = (int *)calloc(m, sizeof(int));
        if (traseu[i] == NULL) {
            for (int j = 0; j < i; j++)
                free(traseu[j]);
            free(traseu);
        }
    }
    traseu[0][0] = contor;
    char* code;
    char letter;
    int dim = 1;
    int cont2 = 0;
    code = (char*)calloc(dim, sizeof(char));
    while (scanf("%c", &letter) != EOF) {
        code[cont2] = letter;
        if (cont2 >= dim) {
            dim = dim * 2;
            char* temp;
            temp = realloc(code, dim);
            if (temp == NULL) {
                free(temp);
                free(code);
                return;
            } else {
                code = temp;
            }
        }
        cont2++;
    }
    code[strlen(code)] = '\0';
    char *word;
    word = strtok(code, " ");

    // primul caz

    while (word != NULL) {
        if (word[0] == 'a') {
            char *crtword;
            char max;
            crtword = strdup(word + 1);
            if (crtword == NULL) {
                free(crtword);
                return;
            }
            max = crtword[0];
            int indicemax = 0;
            for (unsigned int i = 0; i < strlen(crtword); i++) {
                if (max < crtword[i]) {
                    max = crtword[i];
                    indicemax = i;
                }
            }
            indicemax = indicemax + 1;
            if (indicemax == 1) {
                contor++;
                crtcolumn = crtcolumn + 1;
                traseu[crtline][crtcolumn] = contor;
            }
            if (indicemax == 2) {
                contor++;
                crtline = crtline - 1;
                traseu[crtline][crtcolumn] = contor;
            }
            if (indicemax == 3) {
                contor++;
                crtcolumn = crtcolumn - 1;
                traseu[crtline][crtcolumn] = contor;
            }
            if (indicemax == 4) {
                contor++;
                crtline = crtline + 1;
                traseu[crtline][crtcolumn] = contor;
            }
            free(crtword);
        }

        // al doilea caz

        if (word[0] == 'b') {
            char *crtword;
            crtword = strdup(word + 1);
            if (crtword == NULL) {
                free(crtword);
                return;
            }
            char *prim;
            prim = strdup(word + strlen(word) - 2);
            if (prim == NULL) {
                free(prim);
                return;
            }
            if (nrprim(prim) == 0 && palindrom(crtword) == 0) {
                contor++;
                crtline = crtline + 1;
                traseu[crtline][crtcolumn] = contor;
            }
            if (nrprim(prim) == 1 && palindrom(crtword) == 1) {
                contor++;
                crtcolumn = crtcolumn - 1;
                traseu[crtline][crtcolumn] = contor;
            }
            if (nrprim(prim) == 0 && palindrom(crtword) == 1) {
                contor++;
                crtcolumn = crtcolumn + 1;
                traseu[crtline][crtcolumn] = contor;
            }
            if (nrprim(prim) == 1 && palindrom(crtword) == 0) {
                contor++;
                crtline = crtline - 1;
                traseu[crtline][crtcolumn] = contor;
            }
            free(crtword);
            free(prim);
        }

        // al treilea caz

        if (word[0] == 'c') {
            int n = word[1] - '0';
            int k = word[2] - '0';
            int dim = 0;
            int sum = 0;
            char *nrcrt;
            nrcrt = strdup(word + 3);
            if (nrcrt == NULL) {
                free(nrcrt);
                return;
            }

            // formula pt numerele date

            for (int i = 0; i < k; i++) {
                sum += (nrcrt[dim] - '0');
                dim = (dim + k) % n;
            }
            if (sum % 4 == 0) {
                contor++;
                crtcolumn = crtcolumn - 1;
                traseu[crtline][crtcolumn] = contor;
            }
            if (sum % 4 == 1) {
                contor++;
                crtline = crtline - 1;
                traseu[crtline][crtcolumn] = contor;
            }
            if (sum % 4 == 2) {
                contor++;
                crtcolumn = crtcolumn + 1;
                traseu[crtline][crtcolumn] = contor;
            }
            if (sum % 4 == 3) {
                contor++;
                crtline = crtline + 1;
                traseu[crtline][crtcolumn] = contor;
            }
            free(nrcrt);
        }
        word = strtok(NULL, " ");
    }
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < m; j++)
            printf("%d ", traseu[i][j]);

        printf("\n");
    }
    for (unsigned int i = 0; i < n; i++)
        free(traseu[i]);
    free(traseu);
}
