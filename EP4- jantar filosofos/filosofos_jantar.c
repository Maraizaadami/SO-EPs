/******************************************************************************
*   arquivo...: filosofos_jantar.c
*   descricao.: EP4 utilizando programação paralela baseado no algoritmo de Dijkstra
*
*
*  Author: Hector Neira Llado e Maraiza Adami Pereira
* 	Created on 30 de Outubro de 2020, 13:54
*
********************************************************************************/
//---Pacotes necessários para o uso do programa --------------------------------------------------------------------

#include <pthread.h>/*bibliotecas de threads*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>/*API do sistema operacional POSIX.*/
#include <errno.h> /*macros para identificar e relatar erros */


//-- CONSTANTES UTILIZADAS -----------------------------------------------------------------
#define quantidadeFilosofos	(5)						                //quantidadeFilosofosidade de filósofos

#define filosofoESQUERDA	(id_filosofo + quantidadeFilosofos - 1) % quantidadeFilosofos	//Id do filósofo a filosofoESQUERDA do id

#define filosofoDIREITA		(id_filosofo + 1) % quantidadeFilosofos			        //Id do filósofo a filosofoDIREITA do id

#define filosofoPENSANDO	(0)								//Id para estado pensado

#define filosofoComFOME		(1)								//Id para estado de fome

#define filosofoCOMENDO		(2)								//Id para estado filosofoCOMENDO


//-- VARIAVEIS GLOBAIS ---------------------------------------------------------------------
pthread_t jantar[quantidadeFilosofos];		//Todos os filósofos

pthread_mutex_t mutex;				//Região crítica

pthread_mutex_t mux_filo [quantidadeFilosofos];	//Mutex por filósofo

int estado [quantidadeFilosofos];		//Estado dos filósofos


//-- METODOS UTILIZADOS ---------------------------------------------------------------

void comer ( int id_filosofo );

void pensar ( int id_filosofo );

void * filosofo ( void * param );

void pegarTalher ( int id_filosofo );

void devolverTalher ( int id_filosofo );

void intencaoTalher ( int id_filosofo );

//-- implementação dos métodos ----------------------------------------------------------

void comer ( int id_filosofo ){
	int r = (rand() % 10 + 1);
	
	printf("O filosofo com ID %d está comendo por %d segundos \n", id_filosofo, r);
	sleep( r );	//Gasta um tempo em segundos

}

void pegarTalher ( int id_filosofo ){
	pthread_mutex_lock( &(mutex) );					//Entra na região critica
	
	printf("Filosofo com ID %d esta com fome\n", id_filosofo);
	
	estado[ id_filosofo ] = filosofoComFOME;			//Altera o estado do filósofo
	
	intencaoTalher( id_filosofo );					//Intenção de pegar os talheres
	
	pthread_mutex_unlock( &(mutex) );				//Sai na região crítica
	
	pthread_mutex_lock( &(mux_filo[id_filosofo]) );	 		//Bloqueia os talheres
	
}

void intencaoTalher ( int id_filosofo ){

	printf("Filosofo com id %d esta com intenção de comer\n", id_filosofo);
	
	if( (estado[id_filosofo] == filosofoComFOME) &&			//Se o filósofo está come fome
	
		(estado[filosofoESQUERDA] != filosofoCOMENDO) &&	//Se o vizinho da filosofoESQUERDA não está filosofoCOMENDO
		
		(estado[filosofoDIREITA] != filosofoCOMENDO ) )		//Se o vizinho da filosofoDIREITA nсo está filosofoCOMENDO
		
	{
		printf("Filosofo com id %d está com a vez de comer\n", id_filosofo);
		
		estado[ id_filosofo ] = filosofoCOMENDO;		//Filósofo que ganhou a vez de comer
		
		pthread_mutex_unlock( &(mux_filo[id_filosofo]) );	//Libera os talheres
		
	}
}

void devolverTalher ( int id_filosofo ){
	pthread_mutex_lock ( &(mutex) );				//Entrando na região critica
	
	printf("Filosofo com ID %d esta pensando\n", id_filosofo);
	
	estado[ id_filosofo ] = filosofoPENSANDO;			//Terminou de comer
	
	intencaoTalher( filosofoESQUERDA );				//Verifica se o vizinho da esquerda do filosofo pode comer agora
	
	intencaoTalher( filosofoDIREITA );				//Verifica se o vizinho da direita do filosofo pode comer agora
	
	pthread_mutex_unlock ( &(mutex) );				//Sai da Região crítica
}

void pensar ( int id_filosofo ){
	int tempoEmSegs = (rand() % 10 + 1);				//pega um numero aleatório
	
	
	printf("O Filosofo com ID %d está pensando por %d segundos\n", id_filosofo, tempoEmSegs );
	
	
	sleep( tempoEmSegs );	//Gasta um tempo em segundos
}

void * filosofo ( void * vparam ){
	int * id = (int *) (vparam);	//Repassa o id do filósofo

	//printf("Filosofo %d foi criado com sucesso\n", *(id) );

	while ( 5 == 5 ){
		pensar( *(id) );			//Aguarda o filósofo pensar
		
		pegarTalher( *(id) );			//Filósofo pega os talheres
		
		comer( *(id) );				//Aguarda comer
		
		devolverTalher( *(id) );		//Devolver os talheres pra mesa
		
	}

	pthread_exit( (void*) 0 );			//Legado do retorno
}



int main ( void ){
	
	int contadorAux; //contador
	
	int statusThread;//auxiliar na criação da thread e código do erro	

	
	pthread_mutex_init( &(mutex), NULL);//Inicia os mutexes
	
	for( contadorAux = 0 ; contadorAux < quantidadeFilosofos ; contadorAux++ ){
		pthread_mutex_init( &(mux_filo[contadorAux]), NULL );
	}

	//Start das threads
	for( contadorAux = 0 ; contadorAux < quantidadeFilosofos ; contadorAux++ ){
		
		statusThread = pthread_create( &(jantar[contadorAux]), NULL, filosofo, (void *) &(contadorAux) );

		//checagem de erros
		if ( statusThread ){
			printf( "Erro ao criar o thread  %d , código do erro: %d\n", contadorAux, statusThread );
			return EXIT_FAILURE;
		}

	printf("Filosofo %d foi criado com sucesso\n", contadorAux );
	}

	//finalização e kill antes de sair
	pthread_mutex_destroy( &(mutex) );
	for( contadorAux = 0 ; contadorAux < quantidadeFilosofos ; contadorAux++ ){
		pthread_mutex_destroy( &(mux_filo[contadorAux]) );
	}
	pthread_exit( NULL );

	return EXIT_SUCCESS;
}
