#include "reader.h"

int main(int argc, char*argv[]) {
    FILE *md_file = fopen(argv[1], "r");
    FILE *html_file = fopen("../out/result.html", "w");

    if (md_file == NULL || html_file == NULL) {
        free_files(md_file, html_file);

        fatal("The follow error ocorred");
    }

    int c;
    read_file(md_file, c);

    print_out(html_file);
    
    free_files(md_file, html_file);

    return 0;
}
