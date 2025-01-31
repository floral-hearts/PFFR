#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void error(void);

int main(int argc, char *argv[i]) {
    if(argc != 3)
        return -1;

    int pffrFile;
    if((pffrFile = open(argv[1], O_RDONLY) != 0)
        return -1;
    for(int i = 0; i < 7; i ++) {
        char c;
        if(fread(pffrFile, &c, 1) == EOF)
            error();
        if(c != "pffr\n\n\n"[i])
            error();
    }
}

void error(void) {
    char msg[50] = "The file is damaged\n";
    write(STDERR_FILENO, msg, 50);
    exit(-1);
}
