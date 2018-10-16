// gcc 424.c -o pthread -lpthread

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *prime_numbers(void *args) {

  int value = *(int *) args;

  int compare = 0, n = 0, m = 0;

  for(compare = 1; compare <= value; compare++) {
    m = 0;
    for(n = 1; n <= compare; n++) {
      if(compare % n == 0) {
        m++;
      }
    }
    if(m == 2) {
      printf("%d\n", compare);
    }
  }
  pthread_exit(NULL);
}

int main () {

  pthread_t thread_id;

  int value;

  printf("NÚMEROS PRIMOS\n");
  printf("Insira o valor limite: \n");

  scanf("%d", &value);

  int flag = pthread_create(&thread_id, NULL, prime_numbers, &value);

  if(flag != 0) {
    printf("Erro na criação da nova thread.\n");
    exit(EXIT_FAILURE);
  }

  int status = pthread_join(thread_id, NULL);

  if(status != 0) {
    printf ("Erro ao aguardar finalização do thread.\n");
    exit(EXIT_FAILURE);
  }


  return 0;
}
