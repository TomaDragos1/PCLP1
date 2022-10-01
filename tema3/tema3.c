#include "functions.h"

int main() {
    FILE *file_input = NULL, *file_move = NULL, *file_insert = NULL;
    image img;
    pixels **bitmap = NULL;
    pixels draw_color;
    int x_width = 1;
    while (1) {
        char *sir = NULL;
        int i = 0;
        int dim = 1;
        sir = malloc(dim * sizeof(char));
        if (sir == NULL) {
            free(sir);
            return -1;
        }
        char letter = 0;
        while (1) {
            if (i >= dim) {
                dim = dim * 2;
                char *temp = NULL;
                temp = realloc(sir, dim * sizeof(char));
                if (temp == NULL) {
                    free(temp);
                    free(sir);
                    return -1;
                } else {
                sir = temp;
                }
            }
            scanf("%c", &letter);
            if (letter == '\n') {
                sir[i] = '\0';
                break;
            } else {
            sir[i] = letter;
            }
            i++;
        }
        char *word = strtok(sir, " ");
        if (strcmp(word, "edit") == 0) {
            word = strtok(NULL, " ");
            char *path = NULL;
            path = (char *)calloc(strlen(word) + 1, sizeof(char));
            if (path == NULL) {
                free(path);
                return -1;
            }
            strncpy(path, word, strlen(word) + 1);
            file_input = fopen(path, "rb");
            bmp_read(file_input, &img, &bitmap);
            fclose(file_input);
            free(path);
            }
        if (strcmp(word, "save") == 0) {
            word = strtok(NULL, " ");
            char *path = NULL;
            path = (char *)calloc(strlen(word) + 1, sizeof(char));
            if (path == NULL) {
                free(path);
                return -1;
            }
            strncpy(path, word, strlen(word) + 1);
            file_move = fopen(path, "wab");
            bmp_write(file_move, img, &bitmap);
            fclose(file_move);
            free(path);
            }
        if (strcmp(word, "insert") == 0) {
            word = strtok(NULL, " ");
            char *path = NULL;
            path = (char *)calloc(strlen(word) + 1, sizeof(char));
            if (path == NULL) {
                free(path);
                return -1;
             }
            strncpy(path, word, strlen(word) + 1);
            file_insert = fopen(path, "rb");
            word = strtok(NULL, " ");
            signed int y_insert = atoi(word);
            word = strtok(NULL, " ");
            signed int x_insert = atoi(word);
            bmp_insert(file_insert, y_insert, x_insert, &bitmap, img);
            fclose(file_insert);
            free(path);
            }
        if (strcmp(word, "set") == 0) {
            word = strtok(NULL, " ");
            if (strcmp(word, "draw_color") == 0) {
                word = strtok(NULL, " ");
                draw_color.R = atoi(word);
                word = strtok(NULL, " ");
                draw_color.G = atoi(word);
                word = strtok(NULL, " ");
                draw_color.B = atoi(word);
                }
            if (strcmp(word, "line_width") == 0) {
                    word = strtok(NULL, " ");
                    if (word == NULL)
                    x_width = 1;
                    else
                    x_width = atoi(word);
                }
            }
            if (strcmp(word, "draw") == 0) {
                word = strtok(NULL, " ");
                if (strcmp(word, "line") == 0) {
                    word = strtok(NULL, " ");
                    int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
                    y1 = atoi(word);
                    word = strtok(NULL, " ");
                    x1 = atoi(word);
                    word = strtok(NULL, " ");
                    y2 = atoi(word);
                    word = strtok(NULL, " ");
                    x2 = atoi(word);
                    bmp_line(y1, x1, y2, x2, draw_color, &bitmap, x_width, img);
                }
            if (strcmp(word, "rectangle") == 0) {
                int y1 = 0, x1 = 0, rectangle_height = 0, rectangle_width = 0;
                word = strtok(NULL, " ");
                y1 = atoi(word);
                word = strtok(NULL, " ");
                x1 = atoi(word);
                word = strtok(NULL, " ");
                rectangle_width = atoi(word);
                word = strtok(NULL, " ");
                rectangle_height = atoi(word);
                draw_rectangle(y1, x1, rectangle_height, rectangle_width,
                img, &bitmap, x_width, draw_color);
                }
            if (strcmp(word, "triangle") == 0) {
                int y1 = 0, x1 = 0, y2 = 0, x2 = 0, y3 = 0, x3 = 0;
                word = strtok(NULL, " ");
                y1 = atoi(word);
                word = strtok(NULL, " ");
                x1 = atoi(word);
                word = strtok(NULL, " ");
                y2 = atoi(word);
                word = strtok(NULL, " ");
                x2 = atoi(word);
                word = strtok(NULL, " ");
                y3 = atoi(word);
                word = strtok(NULL, " ");
                x3 = atoi(word);
                draw_triangle(y1, x1, y2, x2, y3, x3, img, &bitmap, x_width, draw_color);
                }
            }
        if (strcmp(word, "fill") == 0) {
            int x_fill = 0, y_fill = 0;
            word = strtok(NULL, " ");
            y_fill = atoi(word);
            word = strtok(NULL, " ");
            x_fill = atoi(word);
            pixels curent_pixel_colour;
            curent_pixel_colour.B = bitmap[x_fill][y_fill].B;
            curent_pixel_colour.G = bitmap[x_fill][y_fill].G;
            curent_pixel_colour.R = bitmap[x_fill][y_fill].R;
            fill_colour(x_fill, y_fill, curent_pixel_colour, draw_color, &bitmap, &img);
            }
        if (strcmp(sir, "quit") == 0) {
                for (int i = 0 ; i < img.fileinfo.height; i++)
                    free(bitmap[i]);
                free(bitmap);
                free(sir);
                break;
            }
        free(sir);
    }
}
