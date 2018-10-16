// gcc 426.c -o pthread -lpthread

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *fibonacci(void *args) {

  int value = *(int *) args;

  int *fibo;

  fibo = (int *) malloc(value*sizeof (int));

  if (fibo == NULL)  {
    printf("Alocacao falhou. Finalizado.\n");
    exit(1);
  }

  *(fibo + 0) = 0;
  *(fibo + 1) = 1;

  for (int i = 2; i < value; i++) {
    *(fibo + i) = *(fibo + (i-2)) + *(fibo + (i-1));
  }

  pthread_exit(fibo);
}

int main () {

  pthread_t thread_id;
  void *thread_result;

  int value;
  int *vector_result;

  printf("SEQUENCIA DE FIBONACCI\n");
  printf("Digite o valor que determinará quantos números da sequencia serão impressos\n");

  scanf("%d", &value);

  int flag = pthread_create(&thread_id, NULL, fibonacci, &value);

  if(flag != 0) {
    printf("Erro na criação da nova thread.\n");
    exit(EXIT_FAILURE);
  }

  int status = pthread_join(thread_id, &thread_result);

  if(status != 0) {
    printf ("Erro ao aguardar finalização do thread.\n");
    exit(EXIT_FAILURE);
  }

  vector_result = (int *) thread_result;

  for (int i = 0; i < value; i++) {
    printf("FIBONACCI [%d]: %d\n", i, *(vector_result + i));
  }

  free(thread_result);

  return 0;
}
