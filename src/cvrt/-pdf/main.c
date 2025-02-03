#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void error(void);

int main(int argc, char *argv[i]) {
    if(argc != 3)
        return -1;

    int pffrFile;
    int pdfFile;
    if((pffrFile = open(argv[1], O_RDONLY)) != 0)
        return -1;
    if((pdfFile = open(argv[2], O_WRONLY)) != 0)
        return -1;

    for(int i = 0; i < 7; i ++) {
        char c;
        if(fread(pffrFile, &c, 1) == EOF)
            error();
        if(c != "pffr\n\n\n"[i])
            error();
    }
    uint16_t cmd[4];
    cmd[3] = 0x0000;
    uint16_t c;
    while(1) {
        if(fread(pffrFile, &cmd[0], 1) == EOF)
            error();
        if(fread(pffrFile, &cmd[1], 1) == EOF)
            error();
        if(fread(pffrFile, &cmd[2], 1) == EOF)
            error();
        while(fread(pffrFile, &c, 1)) {
        }
    }
}

void error(void) {
    char msg[50] = "The file is damaged\n";
    write(STDERR_FILENO, msg, 50);
    exit(-1);
}
