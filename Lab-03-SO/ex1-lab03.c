#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("Erro ao criar processo filho");
        return 1;
    }
    if (pid == 0) {
        printf("Processo filho. PID: %d\n", getpid());
        for (int i = 0; i < 5; i++) {
            printf("Mensagem %d do filho\n", i+1);
            sleep(1);
        }
    } else {
        printf("Processo pai. PID: %d, Filho PID: %d\n", getpid(), pid);
    }
    return 0;
}
