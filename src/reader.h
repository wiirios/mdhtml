#ifndef READER_H
#define READER_H

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_CHAR 1000
#define MAX_LINE 256

typedef enum {
    Q1 = 0,
    Q2 = 1,
    Q3 = 2,
    Q4 = 3
} state;

char buffer[MAX_LINE];
char buffer_without_symbols[MAX_LINE];
char html_buff[MAX_CHAR];

int fatal(const char *msg);
int afd(int states[], int sigma[], int (*delta)[2], state start, state final, char *chain);

void free_files(FILE *md, FILE *html);
void read_file(FILE *md, int c);
void convert(char *buffer, int state);
void print_out(FILE *html_file);
void remove_symbols(const char symbol, char *buffer);

#endif