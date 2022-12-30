#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NB_FORK 2

char message_envoyer[25] = "0123456789\n";
char message_recu[25];

void waitForAll() {
	int status;
	pid_t pid;
	int n = 0;
	while (n < NB_FORK) {
		pid = wait(&status);
		n++;
	}
}

int main(){

    int p[2];

    if (pipe(p) == -1 ){
        fprintf(stderr, "impossoble ouvrir tube\n");
        exit(1);
    }

    pid_t pid = fork();
    if (pid == -1) {
		// Il y a une erreur
		perror("fork");
  		return EXIT_FAILURE;

	} else if (pid == 0) {
	    // On est dans le fils
		read(p[0],message_recu, 24);
        close(p[0]);

        printf("%s", message_recu);

	} else {
		// On est dans le père
        write(p[1], message_envoyer, 24);
        close(p[1]);
	}

    waitForAll();
    return EXIT_SUCCESS;
}