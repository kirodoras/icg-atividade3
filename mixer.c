//------------------------
// Universidade Federal de Sergipe
// Departamento de Matemática - Prof Evilson Vieira
// Biblioteta simples para o curso de Introdução à Computação Gráfica
// Mistura duas imagens ppm
// Compilar: gcc mixer.c -o mixer -lm
// Sintaxe: ./mixer gatobranco.ppm gatopreto.ppm
// Aluno Mateus Figueiredo Pereira
// Aracaju-SE 17/12/2023
//------------------------
#include <stdio.h>
#include <stdlib.h>

void main(int argc, char **argv)
{
    int i, j, l, h, n;
    unsigned char type, cmax, caractere;
    FILE *file;
    FILE *file1;

    file = fopen(argv[1], "r");
    while ((caractere = getc(file)) == '#')
        while ((caractere = getc(file)) != '\n')
            ;
    ungetc(caractere, file);

    fscanf(file, "P%hhu\n", &type);
    while ((caractere = getc(file)) == '#')
        while ((caractere = getc(file)) != '\n')
            ;
    ungetc(caractere, file);

    fscanf(file, "%u %u\n%hhu\n", &l, &h, &cmax);

    file1 = fopen(argv[2], "r");
    while ((caractere = getc(file1)) == '#')
        while ((caractere = getc(file1)) != '\n')
            ;
    ungetc(caractere, file1);

    fscanf(file1, "P%hhu\n", &type);
    while ((caractere = getc(file1)) == '#')
        while ((caractere = getc(file1)) != '\n')
            ;
    ungetc(caractere, file1);

    fscanf(file1, "%u %u\n%hhu\n", &l, &h, &cmax);

    unsigned char(**imagem)[3];

    n = l * sizeof(char *);
    imagem = malloc(n);

    n = h * 3;
    for (i = 0; i < l; i++)
        imagem[i] = malloc(n);

    unsigned char p[l][h][3];
    unsigned char q[l][h][3];

    if (type == 3)
    {
        for (j = 0; j < h; j++)
            for (i = 0; i < l; i++)
            {
                fscanf(file, "%hhu %hhu %hhu", &p[i][j][0], &p[i][j][1], &p[i][j][2]);
                fscanf(file1, "%hhu %hhu %hhu", &q[i][j][0], &q[i][j][1], &q[i][j][2]);
            }
        fclose(file);
        fclose(file1);
    }
    else if (type == 6)
    {
        for (j = 0; j < h; j++)
            for (i = 0; i < l; i++)
            {
                fscanf(file, "%c%c%c", &p[i][j][0], &p[i][j][1], &p[i][j][2]);
                fscanf(file1, "%c%c%c", &q[i][j][0], &q[i][j][1], &q[i][j][2]);
            }
        fclose(file);
        fclose(file1);
    }
    else
    {
        printf("Formato inválido!");
        fclose(file);
        fclose(file1);
        exit(0);
    }

    float fx = 0;
    float fx1 = 0;
    for (j = 0; j < h; j++)
        for (i = 0; i < l; i++)
        {
            if (i < l / 3)
            {
                imagem[i][j][0] = q[i][j][0];
                imagem[i][j][1] = q[i][j][1];
                imagem[i][j][2] = q[i][j][2];
            }
            else if (i <= (2 * l / 3))
            {
                fx = ((float)3 / l) * i - 1.0;
                fx1 = ((float)-3 / l) * i + 2.0;
                imagem[i][j][0] = fx * p[i][j][0] + fx1 * q[i][j][0];
                imagem[i][j][1] = fx * p[i][j][1] + fx1 * q[i][j][1];
                imagem[i][j][2] = fx * p[i][j][2] + fx1 * q[i][j][2];
            }
            else
            {
                imagem[i][j][0] = p[i][j][0];
                imagem[i][j][1] = p[i][j][1];
                imagem[i][j][2] = p[i][j][2];
            }
        }

    file = fopen("mixer.ppm", "w");
    fprintf(file, "P6\n");
    fprintf(file, "%u %u\n255\n", l, h);
    for (j = 0; j < h; j++)
        for (i = 0; i < l; i++)
            fprintf(file, "%c%c%c", imagem[i][j][0], imagem[i][j][1], imagem[i][j][2]);
    fclose(file);
    for (i = 0; i < l; i++)
        free(imagem[i]);
    free(imagem);
}
