// gcc 426.c -o pthread -lpthread
// monte carlo
// funcao para srand de -1 a 1 de pontos x e y

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

int pontos_dentro_do_circulo = 0;
int pontos_totais = 0;
pthread_mutex_t lock;
/*
int var = 1;

acquire(&var);
release(&var);

void acquire(int *mutex){

  while(!mutex);

  mutex = 0;
}

void release(int *mutex){
  mutex = 1;
}
*/

void *randomizacao_pontos(void *args) {

  int value = *(int *) args;

  double random_x = 0.0;
  double random_y = 0.0;
  double distancia = 0.0;

  srand(time(NULL));

  for(int i = 0; i < value; i++) {
    pthread_mutex_lock(&lock);
    pontos_totais++;
    pthread_mutex_unlock(&lock);
    random_x = ((double)rand() / (double)(RAND_MAX)) * 2.0 - 1.0;
    random_y = ((double)rand() / (double)(RAND_MAX)) * 2.0 - 1.0;

    distancia = sqrt(pow(random_x, 2) + pow(random_y, 2));

    if(distancia <= 1.0) {
      pthread_mutex_lock(&lock);
      pontos_dentro_do_circulo++;
      pthread_mutex_unlock(&lock);
    }
  }

  pthread_exit(NULL);

}

int main () {

  int value;

  printf("MONTE CARLO\n\n");
  printf("Digite o numero de pontos (quanto mais pontos, mais exato sera o calculo de pi)\n");
  scanf("%d", &value);

  pthread_t thread_id[10];

  if (pthread_mutex_init(&lock, NULL) != 0) {
 		fprintf(stderr, "Erro ao criar mutex.\n");
 		exit(EXIT_FAILURE);
 	}

  for (int i = 0; i < 10; i++) {
    int flag = pthread_create(&thread_id[i], NULL, randomizacao_pontos, &value);

    if(flag != 0) {
      printf("Erro na criação da nova thread.\n");
      exit(EXIT_FAILURE);
    }
  }

  for (int i = 0; i < 10; i++) {
    int status = pthread_join(thread_id[i], NULL);

    if(status != 0) {
      printf ("Erro ao aguardar finalização do thread.\n");
      exit(EXIT_FAILURE);
    }
  }

  printf("%d\n", pontos_dentro_do_circulo);
  printf("%d\n", pontos_totais);
  double pi = 4.0 * ((double)pontos_dentro_do_circulo / (double)pontos_totais);

  printf("A aproximacao para pi eh:\n%lf\n", pi);

  pthread_mutex_destroy(&lock);

  return 0;
}
