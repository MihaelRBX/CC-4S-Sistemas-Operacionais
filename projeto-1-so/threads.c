#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define INITIAL_BALANCE 1000
#define NUM_THREADS 5  //número de threads de depósito e saque
#define TRANSFER_AMOUNT 50

//estrutura da conta 
typedef struct {
    int balance;
    pthread_mutex_t mutex;
} BankAccount;

//função depósito com mutex
void deposit(BankAccount *account, int amount) {
    pthread_mutex_lock(&account->mutex);  
    account->balance += amount;
    printf("Depositado: %d, Saldo Atual: %d\n", amount, account->balance);
    pthread_mutex_unlock(&account->mutex);  
}

//função saque com mutex
void withdraw(BankAccount *account, int amount) {
    pthread_mutex_lock(&account->mutex);
    if (account->balance >= amount) {
        account->balance -= amount;
        printf("Sacado: %d, Saldo Atual: %d\n", amount, account->balance);
    } else {
        printf("Saldo Insuficiente para saque: %d\n", amount);
    }
    pthread_mutex_unlock(&account->mutex);  
}

//função executada pelas threads de depósito
void* transaction_dep(void* arg) {
    BankAccount *account = (BankAccount*)arg;
    for (int i = 0; i < 5; i++) {  //cada thread faz 5 operações de depósito
        deposit(account, TRANSFER_AMOUNT);
        sleep(1);  //simulando processamento
    }
    return NULL;
}

//função executada pelas threads de saque
void* transaction_sac(void* arg) {
    BankAccount *account = (BankAccount*)arg;
    for (int i = 0; i < 5; i++) {  //cada thread faz 5 operações de saque
        withdraw(account, TRANSFER_AMOUNT);
        sleep(1);  //simulando processamento
    }
    return NULL;
}

int main() {
    pthread_t threads_dep[NUM_THREADS];
    pthread_t threads_sac[NUM_THREADS];
    BankAccount account;
    account.balance = INITIAL_BALANCE;
    pthread_mutex_init(&account.mutex, NULL);  //inicializa o mutex

    //threads de depósito
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads_dep[i], NULL, transaction_dep, &account);
    }

    //threads de saque
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads_sac[i], NULL, transaction_sac, &account);
    }

    //threads de depósito terminarem
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads_dep[i], NULL);
        pthread_join(threads_sac[i], NULL);
    }

    //finaliza mutex
    pthread_mutex_destroy(&account.mutex);

    //exibe o saldo final da conta
    printf("Saldo Final: %d\n", account.balance);

    return 0;
}
