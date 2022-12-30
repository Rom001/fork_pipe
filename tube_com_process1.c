#include <unistd.h>
#include <stdio.h>

char message_envoyer[25] = "0123456789\n";
char message_recu[25];

void main(){

    int p[2];
    ///int pipe();

    if (pipe(p) == -1 ){
        fprintf(stderr, "impossoble ouvrir tube\n");
        exit(1);
    }

    write(p[1], message_envoyer, 24);
    close(p[1]);

    read(p[0],message_recu, 24);
    close(p[0]);

    printf("%s", message_recu);
}