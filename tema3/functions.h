#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp_header.h"

#define minc(x, y) ((x) <= (y) ? (x) : (y))
#define maxc(x, y) ((x) <= (y) ? (y) : (x))

void bmp_read(FILE *input, image *crt_image, pixels ***bitmap) {
    fread(&crt_image->fileheader, sizeof(crt_image->fileheader), 1, input);
    fread(&crt_image->fileinfo, sizeof(crt_image->fileinfo), 1, input);
    *bitmap = (pixels **)calloc(crt_image->fileinfo.height, sizeof(pixels *));
    if (*bitmap == NULL) {
        free(bitmap);
        exit(0);
    }
    for (int i = 0; i < crt_image->fileinfo.height; i++) {
        (*bitmap)[i] = (pixels *)calloc(crt_image->fileinfo.width, sizeof(pixels));
        if ((*bitmap)[i] == NULL) {
            for (int k = 0 ; k < i ; k++)
            free((*bitmap)[k]);
            free(*bitmap);
            exit(0);
        }
        for (int j = 0; j < crt_image->fileinfo.width; j++) {
            fread(&(*bitmap)[i][j], sizeof(pixels), 1, input);
        }
        if (((sizeof(pixels) * crt_image->fileinfo.width) % 4) != 0) {
            fseek(input, (long)(4 - ((sizeof(pixels) * crt_image->fileinfo.width) % 4)), SEEK_CUR);
        }
    }
}
void bmp_write(FILE *output, image crt_image, pixels ***bitmap) {
    fwrite(&crt_image.fileheader, 1, sizeof(crt_image.fileheader), output);
    fwrite(&crt_image.fileinfo, sizeof(crt_image.fileinfo), 1, output);
    char zero = 0;
    for (int i = 0; i < crt_image.fileinfo.height; i++) {
        for (int j = 0; j < crt_image.fileinfo.width; j++) {
            fwrite(&(*bitmap)[i][j], 1, sizeof(pixels), output);
        }
        if (((3 * crt_image.fileinfo.width) % 4) != 0) {
            for (int i = 0; i < 4 - (sizeof(pixels) * crt_image.fileinfo.width) % 4; i++)
                fwrite(&zero, 1, 1, output);
        }
    }
}
void bmp_insert(FILE *insert, signed int y, signed int x, pixels ***bitmap, image crt_img) {
    image img_insert;
    fread(&img_insert.fileheader, sizeof(img_insert.fileheader), 1, insert);
    fread(&img_insert.fileinfo, sizeof(img_insert.fileinfo), 1, insert);
    signed int min_height = 0, min_width = 0;
    if (img_insert.fileinfo.height + x < crt_img.fileinfo.height)
        min_height = img_insert.fileinfo.height + x;
    else
        min_height = crt_img.fileinfo.height;
    if (img_insert.fileinfo.width + y < crt_img.fileinfo.width)
        min_width = img_insert.fileinfo.width + y;
    else
        min_width = crt_img.fileinfo.width;
    for (int i = x ; i < min_height ; i++) {
        for (int j = y ; j < min_width ; j++) {
            fread(&(*bitmap)[i][j], sizeof(pixels), 1, insert);
        }
        if (min_width == crt_img.fileinfo.width) {
            if (((3 * img_insert.fileinfo.width % 4)) != 0) {
                int outside_border = (y + img_insert.fileinfo.width - crt_img.fileinfo.width) * 3;
                fseek(insert, (long)(4 - (sizeof(pixels) * img_insert.fileinfo.width % 4)) + outside_border, SEEK_CUR);
            } else {
                fseek(insert, (y + img_insert.fileinfo.width - crt_img.fileinfo.width) * 3, SEEK_CUR);
            }
        } else {
            if (((3 * img_insert.fileinfo.width % 4)) != 0)
            fseek(insert, (long)(4 - (sizeof(pixels) * img_insert.fileinfo.width % 4)), SEEK_CUR);
        }
    }
}
void fill_width_x(int x_line, int crt_y, image crt_image, int x_width, pixels draw_color, pixels ***bitmap) {
    int x_start = maxc(0, x_line - x_width / 2);
    int x_final = minc(crt_image.fileinfo.height, x_line + x_width / 2 + 1);
    int y_start = maxc(0, crt_y - x_width/2);
    int y_final = minc(crt_image.fileinfo.width, crt_y + x_width / 2 + 1);
    for (int j = x_start ; j < x_final ; j++) {
        for (int k = y_start ; k < y_final ; k++) {
            (*bitmap)[j][k].B = draw_color.B;
            (*bitmap)[j][k].G = draw_color.G;
            (*bitmap)[j][k].R = draw_color.R;
        }
    }
}
void fill_width_y(int y_line, int crt_x, image crt_image, int x_width, pixels draw_color, pixels ***bitmap) {
    int x_start = maxc(0, crt_x - x_width / 2);
    int x_final = minc(crt_image.fileinfo.height, crt_x + x_width / 2 + 1);
    int y_start = maxc(0, y_line - x_width/ 2);
    int y_final = minc(crt_image.fileinfo.width, y_line + x_width / 2 + 1);
    for (int j = x_start ; j < x_final ; j++) {
        for (int k = y_start; k < y_final; k++) {
            (*bitmap)[j][k].B = draw_color.B;
            (*bitmap)[j][k].G = draw_color.G;
            (*bitmap)[j][k].R = draw_color.R;
        }
    }
}
void bmp_line(int y1, int x1, int y2, int x2, pixels draw_color, pixels ***bitmap, int x_width, image crt_image) {
    int abs_x = maxc(x1, x2) - minc(x1, x2);
    int abs_y = maxc(y1, y2) - minc(y1, y2);
    if (abs_x < abs_y) {
        int first = minc(y1, y2);
        int second = maxc(y1, y2);
        for (int i = maxc(first, 0); i <= minc(second, crt_image.fileinfo.width); i++) {
            int x_line = ((i - y1) * (x2 - x1) + x1 * (y2 - y1)) / (y2 - y1);
            if (x_line >= 0 && x_line < crt_image.fileinfo.height)
            fill_width_x(x_line, i, crt_image, x_width, draw_color, bitmap);
        }
        } else {
        int first = minc(x1, x2);
        int second = maxc(x1, x2);
        for (int i = maxc(first, 0); i <= minc(second, crt_image.fileinfo.height); i++) {
            int y_line = ((i - x1) * (y2 - y1) + y1 * (x2 - x1)) / (x2 - x1);
            if (y_line >=0 && y_line < crt_image.fileinfo.width)
            fill_width_y(y_line, i, crt_image, x_width, draw_color, bitmap);
        }
    }
}

void draw_rectangle(int y1, int x1, int rct_height, int rct_width, image img, pixels ***bitmap, int x_w, pixels col) {
    bmp_line(y1, x1, y1 + rct_width, x1, col, bitmap, x_w, img);
    bmp_line(y1, x1, y1, x1 + rct_height, col, bitmap, x_w, img);
    bmp_line(y1 + rct_width, x1, y1 + rct_width, x1 + rct_height, col, bitmap, x_w, img);
    bmp_line(y1 + rct_width, x1 + rct_height, y1, x1 + rct_height, col, bitmap, x_w, img);
}

void draw_triangle(int y1, int x1, int y2, int x2, int y3, int x3, image img, pixels ***bitmap, int x_w, pixels col) {
    bmp_line(y1, x1, y2, x2, col, bitmap, x_w, img);
    bmp_line(y1, x1, y3, x3, col, bitmap, x_w, img);
    bmp_line(y2, x2, y3, x3, col, bitmap, x_w, img);
}
int check_struct(pixels ***bitmap, pixels color, int x, int y) {
    if ((*bitmap)[x][y].B == color.B && (*bitmap)[x][y].G == color.G && (*bitmap)[x][y].R == color.R)
    return 1;
    return 0;
}
void fill_colour(int x, int y, pixels crt_col, pixels draw_colour, pixels ***bitmap, image *crt_img) {
    if (y - 1 >= 0 && check_struct(bitmap, crt_col, x, y - 1) == 1) {
        (*bitmap)[x][y - 1].B = draw_colour.B;
        (*bitmap)[x][y - 1].G = draw_colour.G;
        (*bitmap)[x][y - 1].R = draw_colour.R;
        fill_colour(x, y - 1, crt_col, draw_colour, bitmap, crt_img);
    }
    if (y + 1 < crt_img->fileinfo.width && check_struct(bitmap, crt_col, x, y + 1) == 1) {
        (*bitmap)[x][y + 1].B = draw_colour.B;
        (*bitmap)[x][y + 1].G = draw_colour.G;
        (*bitmap)[x][y + 1].R = draw_colour.R;
        fill_colour(x, y + 1, crt_col, draw_colour, bitmap, crt_img);
    }
    if (x - 1 >= 0 && check_struct(bitmap, crt_col, x-1, y) == 1) {
        (*bitmap)[x - 1][y].B = draw_colour.B;
        (*bitmap)[x - 1][y].G = draw_colour.G;
        (*bitmap)[x - 1][y].R = draw_colour.R;
        fill_colour(x - 1, y, crt_col, draw_colour, bitmap, crt_img);
    }
    if (x + 1 < crt_img->fileinfo.height && check_struct(bitmap, crt_col, x + 1, y) == 1) {
        (*bitmap)[x + 1][y].B = draw_colour.B;
        (*bitmap)[x + 1][y].G = draw_colour.G;
        (*bitmap)[x + 1][y].R = draw_colour.R;
        fill_colour(x + 1, y, crt_col, draw_colour, bitmap, crt_img);
    }
    return;
}
