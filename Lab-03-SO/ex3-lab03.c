#include <stdio.h>
#include <unistd.h> 
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Erro ao criar processo filho");
        return 1;
    }
    if (pid == 0) { 
        printf("Prrocesso filho. PID: %d\n", getpid());
        execlp("ls", "ls", "-l", NULL);
        perror("Erro ao executar o exec");
    } else {
        wait(NULL);
        printf("Processo filho terminou. Pai PID: %d\n", getpid());
    }
    return 0;
}
