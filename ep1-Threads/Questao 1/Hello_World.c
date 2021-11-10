/* 
 * File:   Hello_world.c
 * Author: Hector Neira Llado e Maraiza Adami Pereira
 * Created on 10 de Outubro de 2020, 14:49
 */

/*Criação de um processo pai, “hello world”, fork processo filho, “hello world”, finalização de ambos*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>


int main(){
    
    pid_t filho ; //tipo de dados padrão para representação de processo , aqui nomeamos de filho
    int i,Status, q; // cria duas váriaveis inteiras
    

    filho = fork(); // cria o processo filho através da função fork , a variavel filho vai receber o id do processo criado
   

    if (filho ==  0)
    {
        // código executado no filho
        printf("filho valor :  %d \n", filho);
       
        printf("Mensagem: Hello World\n");
        printf("Sou o processo filho.Pid número: %d\n", getpid());

	for (i =0 ; i<=5; i++){
		  printf("%d\n", i);
		sleep(2); // atraso de 2 segundos
	}
	_exit(0); //a saída imediata do processo filho
    }
    
   
    else  { 
	 //O código neste trecho será executado no processo pai
	
       q = wait(&Status); // recebe -1 se o processo filho teve erro e encerrou ou o pid do processo filho se , esse se encerrou regularmente 
	
       printf("Esperando o status do filho.\n");
         
        
       if ( WIFEXITED(Status)){//Retorna verdadeiro caso o processo filho tenha terminado normalmente 

	 printf("Processo filho encerrado.\n");

       }else{

           printf( "processo filho terminou inesperadamente");
       }

        printf("Mensagem : Hello World\n" );	 
	printf("Sou o processo Pai: pid numero %d\n", getpid());
        
        for (i =6 ; i<10; i++){
		  printf("%d\n", i);
		sleep(2); // atraso de 2 segundos
	}
    }


    //Esta regiao sera executada por ambos processos
    printf("Finalizando processo pai. \n\n");
    return 0;
}
