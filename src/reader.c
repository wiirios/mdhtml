#include "reader.h"

int fatal(const char *msg) {
    perror(msg);

    exit(EXIT_FAILURE);
}

void free_files(FILE *md, FILE *html) {
    fclose(md);
    fclose(html);
}

void read_file(FILE *md, int c) {
    int first_line = 1;
    
    while (fgets(buffer, MAX_LINE, md) != NULL) {
        if (!isspace((unsigned char) buffer[0])) {
            while (1) {
                int states[] = {Q1, Q2, Q3, Q4};
                int sigma[] = {0, 1};
                int delta[4][2];

                delta[Q1][0] = Q2;
                delta[Q1][1] = Q1;
                delta[Q2][0] = Q3;
                delta[Q2][1] = Q4;
                delta[Q3][0] = Q3;
                delta[Q3][1] = Q3;
                delta[Q4][0] = Q4;
                delta[Q4][1] = Q4;

                state start = Q1;
                state final = Q4;

                int final_state = afd(states, sigma, delta, start, final, &buffer[0]);

                convert(&buffer[0], final_state);
                memset(buffer, 0, sizeof(buffer));
                memset(buffer_without_symbols, 0, sizeof(buffer_without_symbols));
                break;
            }

        }

    }
}

int afd(int states[], int sigma[], int (*delta)[2], state start, state final, char *chain) {
    state current = start;
 
    for (int i = 0; chain[i] != '\0'; i++) {
        int symbol = 0;

        if (chain[i] == '*') symbol = 0;
        else symbol = 1;

        current = delta[current][symbol];
    }

    return (current == final);
}

void convert(char *buffer, int state) {
    if (state == 0 || state == 1) remove_symbols('*', &buffer[0]);
    
    if (state == 0) {
        strcat(html_buff, "<strong>");
        strcat(html_buff, buffer_without_symbols);
        strcat(html_buff, "</strong>");
    } else if (state == 1) {
        strcat(html_buff, "<em>");
        strcat(html_buff, buffer_without_symbols);
        strcat(html_buff, "</em>");
    }
}

void print_out(FILE *html_file) {
    fprintf(html_file, html_buff);
}

void remove_symbols(const char symbol, char *buffer) {
    int i = 0;
    int j = 0;
    int length = 0;

    for (; buffer[i] != '\0'; i++) {
        if (buffer[i] != symbol) {
            buffer_without_symbols[j] = buffer[i];
            j++;
        }

        length++;
    }

    //strchr(buffer_without_symbols, '\n');
}
