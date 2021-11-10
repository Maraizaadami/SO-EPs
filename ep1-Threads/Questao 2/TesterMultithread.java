/* 
 * File:   TesterMultithread.java
 * Author: Hector Neira Llado e Maraiza Adami Pereira
 * Created on 11 de Outubro de 2020, 13:44
 */

/*Criação de um processo, criação de várias Java threads, "hello world" de todos, finalização*/

import java.lang.*;

public class TesterMultithread {

    //criação de um processo main, executável
    public static void main(String[] args) {

        
        //criação de 10 Java Threads
        Threads t1 = new Threads("Thread 1");
        t1.start();
        Threads t2 = new Threads("Thread 2");
        t2.start();
        Threads t3 = new Threads("Thread 3");
        t3.start();
        Threads t4 = new Threads("Thread 4");
        t4.start();
        Threads t5 = new Threads("Thread 5");
        t5.start();
        Threads t6 = new Threads("Thread 6");
        t6.start();
        Threads t7 = new Threads("Thread 7");
        t7.start();
        Threads t8 = new Threads("Thread 8");
        t8.start();
        Threads t9 = new Threads("Thread 9");
        t9.start();
        Threads t10 = new Threads("Thread 10");
        t10.start();

    }



}