/* 
 * File:   semaforo_binario.c
 * Author: Hector Neira Llado e Maraiza Adami Pereira
 * Created on 22 de Outubro de 2020, 7:08
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> /*bibliotecas de threads*/
#include <errno.h> /*macros para identificar e relatar erros */
#include <sys/types.h>
#include <sys/wait.h>
#include <semaphore.h>

#define count 50000
#define MAX_THREADS 2
long long valor = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;//macro inicializa o mutex estático, definindo seus atributos para os valores padrão.

void *rotina(void *arg) { /*rotina a ser executada pela thread*/

         int v = *(int*)arg; // variavel recebe o parametro da função

	for (int i = 0;i< count; i++){
		pthread_mutex_lock(&mutex);// bloqueio na variável mutex. Se ela mutex já estiver bloqueado por outro segmento, esta chamada bloqueará o segmento de chamada até que o mutex seja desbloqueado.
		valor += v;
		printf("Thread está inserindo o número %d na lista \n ", valor);
		pthread_mutex_unlock(&mutex);//desbloqueia
	}
pthread_exit (NULL); /*destroi a thread*/

}


int main (void) {
	pthread_t thread_id[MAX_THREADS];  //estrutura de controle do thread, do tipo pthread_t.
	int status, i; //variaveis auxiliares
	int var = 0;// 
    
   /*tenta iniciar o thread,usando a função phtread_create( indicando o endereço , 
	atributo,a funçãoda rotina a ser executada e passando como argumento um inteiro */

   	 for(i = 0; i <= MAX_THREADS; i++) {
		var = i;
		status = pthread_create(&thread_id[i], NULL, rotina, &var); 


		/*verificar se ocorreu algum erro na chamada de pthread_create*/

			 if(status) {
           			  printf("Erro ao criar o thread  %d \n", status);
           			  exit(1);
       			 }
	

	printf("Thread %d criado com sucesso!\n", i);// imprime o  a posição no laço que a thread foi criada
	printf( "Valor , %d \n" , valor);
	pthread_join(status, NULL); //executado para esperar o fim de uma thread 
    	}
	return (0);

}
