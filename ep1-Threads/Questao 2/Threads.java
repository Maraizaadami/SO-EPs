/* 
 * File:   TesterMultithread.java
 * Author: Hector Neira Llado e Maraiza Adami Pereira
 * Created on 11 de Outubro de 2020, 14:15
 */

/*Criação de um processo, criação de várias Java threads, "hello world" de todos, finalização*/

import java.lang.*;

public class Threads implements Runnable {

    //atributos da classe Threads
    public String nomeDaThread;
    public Thread th;

    //construtor da classe Threads
    public Threads(String nomeDaThread) {
        this.nomeDaThread = nomeDaThread;
    }

    //é atraves do metodo run (overridavel) da interface Runnable onde usamos nossas java threads
    @Override
    public void run() {
        System.out.println(nomeDaThread + " : " + "Hello World!!! :)");
        try {
         Thread.sleep(3000);
        }
        catch (InterruptedException e) {
            System.out.println(nomeDaThread + "foi interrompida...");
        }

        System.out.println(nomeDaThread + " saindo...");
     }

    //método start: instanciação de java threads
    public void start() {
        System.out.println(nomeDaThread + " : " + "foi startada.");
        if (this.th == null) {
            this.th = new Thread(this, nomeDaThread);
            th.start();
        }
    }
}