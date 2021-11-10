/* 
 * File:   main_t.c
 * Author: Hector Neira Llado e Maraiza Adami Pereira
 * Created on 10 de Outubro de 2020, 19:00
 */

/*Criação de um processo, criação de várias POSIX threads*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h> //bibliotecas de threads
#include <errno.h> // macros para identificar e relatar erros 
#include <unistd.h>// função sleep
#include <stdint.h> //type intptr_t

#define MAX_THREADS 5

pthread_t thread_id[MAX_THREADS];  //estrutura de controle do thread, do tipo pthread_t. um valor que permite identificar o thread;

/*Rotina que será executada pelos threads*/

void * rotina (void *id){
	
	int thread_id = (intptr_t)id; //recebe o argumento da função e guarda no tipo intptr_t -tipo inteiro para armazenar um ponteiro

	printf ("Thread id:  %u executando...\n",(intptr_t)pthread_self() );//id da thread em execução
	printf ("Mensagem: Hello world , thread id : %u - Eu fui criada na iteração %d !\n", (intptr_t)pthread_self(), (intptr_t)thread_id);
	printf ( "Finalizando thread id : %u .\n" , (intptr_t)pthread_self());
   	pthread_exit(NULL);//encerra a thread e retorna nulo
}


int main () {

    int status, i;

   /*tenta iniciar o thread,usando a função phtread_create( indicando o endereço , atributo,a função rotina e passando como argumento um inteiro */

    for(i = 0; i <= MAX_THREADS; i++) {
	
        status = pthread_create(&thread_id[i], NULL, rotina, (void*)(intptr_t)i); 

	/*verificar se ocorreu algum erro na chamada de pthread_create*/

	 if(status) {
             printf("Erro ao criar o thread  %d \n", status);
             exit(1);
        }
        printf("Thread %d criado com sucesso!\n", i);// imprime o id da thread que está rodando
        
	sleep(1); //Pausa de 1 segundo
    }
	

    pthread_exit(NULL);//finaliza a thread
}





