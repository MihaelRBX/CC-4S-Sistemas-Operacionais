# Projeto-1-SO
Projeto 1 de Sistemas Operacionais. Aluno: Mihael Rommel B. Xavier / RA:10239617
O objetivo do projeto é implementar um sistema de controle de depósitos e saques em uma conta bancária que seja acessado por várias threads, identificando e resolvendo problemas de concorrência.

# Solucão
O código apresentava um problema onde várias threads tentavam acessar o saldo bancário ao mesmo tempo, causando inconsistências no saldo final. O problema foi resolvido com a adição de mutex para garantir que apenas uma thread por vez pudesse acessar e modificar o saldo.

# Implementacão
- Mutex (`pthread_mutex`): Adicionado para sincronizar o acesso ao saldo bancário, garantindo que uma única thread acesse o recurso compartilhado por vez, evitando concorrência.
- Threads (`pthread`): Threads responsáveis por realizar depósitos e saques em uma conta bancária. Cada thread realiza múltiplas operações de forma sincronizada.

# Arquivos
- `threads.c`: O código-fonte do projeto.
- `README.md`: Este arquivo de documentação.

# Compilar o código
Para compilar o programa em sistemas baseados em Unix/Linux, use o seguinte comando:
```bash
gcc threads.c -o threads -lpthread
