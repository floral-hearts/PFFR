#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if(argc != 3) {
        fputs("error: no input file path", stderr);
        exit(0);
    }
    if(strcmp(argv[1], "-pdf") == 0)
        execl("cnvt/-pdf.exe", "cnvt/-pdf.exe", argv[2], argv[3], NULL);
    else if(strcmp(argv[1], "pdf-") == 0)
        execl("cnvt/pdf-.exe", "cnvt/pdf-.exe", argv[2], argv[3], NULL);
}
