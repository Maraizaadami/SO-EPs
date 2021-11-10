
/* 
 * File:   Secao_critica.c
 * Author: Hector Neira Llado e Maraiza Adami Pereira
 * Created on 22 de Outubro de 2020, 5:17
 */


/*implementação multithreaded ( uma thread para P0 e outra para P1)*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> /*bibliotecas de threads*/
#include <errno.h> /*macros para identificar e relatar erros */
#include <unistd.h>/*função sleep*/
#include <stdint.h> /*type intptr_t*/

#define MAX_THREADS 1 
#define N 5 

int count = 0;  /*Contador*/ 
int vez ,meu_id, outro_id;

pthread_t thread_id[MAX_THREADS];  //estrutura de controle do thread, do tipo pthread_t. um valor que permite identificar o thread;

void secao_critica(int c){
	printf("entrando na seção crítica \n");

	count = c;	

	if (vez == 0){ 
		count = count + 1; /*incrementa 1 item no contador*/
		printf(" P0 na seção crítica, contador:   %d.\n", count);
		vez = 1;
    sleep(2);
	}

	if (vez == 1){
		count = count + 1; /* incrementa 1*/
		//printf("O contador foi decrementado e vale: %d \n", count);
		printf("P1 na seção crítica, contador: :  %d \n", count);
		vez = 0;
    sleep(2);
	}
}

void secao_nao_critica(int id){
  int meu_id = id; 
	printf ("Seção não crítica ");
	printf ("Mensagem: Hello world , thread id : %u - Processo id %d !\n", (intptr_t)pthread_self(), (intptr_t)meu_id);
}

void P0(void) {
	int meu_id = 0;
	int outro_id = 1;
	vez = meu_id;
        
	while (vez == 0 ){
		if (count == N) break; /* se o buffer está cheio entra na função sleep*/
		secao_critica(count);
		vez = outro_id;
		secao_nao_critica(meu_id);
	}
}

void P1(void){
	int meu_id = 1;
	int outro_id= 0; 
	vez = meu_id;
        
	while ( vez == 1){
		if (count == 0) {/* se buffer vazio, chama a função sleep */
			vez = outro_id;
			sleep(15);
		} 
	secao_critica(count);
  	vez = outro_id;
	secao_nao_critica(meu_id);
	}
		
	

} 

void * rotina (void *id){
	
	int thread_id = (intptr_t)id; //recebe o argumento da função e guarda no tipo intptr_t -tipo inteiro para armazenar um ponteiro

	printf ("Thread id:  %u executando...\n",(intptr_t)pthread_self() );//id da thread em execução
	//printf ("contador:%d \n",count);

	if (vez == 0) P0();


	if (vez == 1) P1();

   	//pthread_exit(NULL);//encerra a thread e retorna nulo
}

int main(void) {
  int status; 

  int t_p0= 0;
 	status = pthread_create(&thread_id[0], NULL, rotina, (void*)(intptr_t)t_p0); 


	/*verificar se ocorreu algum erro na chamada de pthread_create*/

	if(status) {
		printf("Erro ao criar o thread  %d \n", status);
		exit(1);
 	} else {
    		printf("Thread %d criado com sucesso!\n", t_p0);// imprime o id da thread que está rodando
    
  	}
	
   int t_p1= 1;
 	status = pthread_create(&thread_id[1], NULL, rotina, (void*)(intptr_t)t_p1);

	
	if(status) {
		printf("Erro ao criar o thread  %d \n", status);
		exit(1);
 	} else {
    		printf("Thread %d criado com sucesso!\n", t_p1);// imprime o id da thread que está rodando
  	}
        
  pthread_join(thread_id[0], NULL);

  pthread_exit(NULL);//finaliza a thread

  return 0;
}
