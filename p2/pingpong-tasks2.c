// PingPongOS - PingPong Operating System
// Prof. Carlos A. Maziero, DINF UFPR
// Versão 1.1 -- Julho de 2016

// Teste da gestão básica de tarefas
//para compilar no MacOS
#define _XOPEN_SOURCE 600

#include <stdio.h>
#include <stdlib.h>
#include "ppos.h"

#define MAXTASK 1000

task_t task[MAXTASK+1] ;

// corpo das threads
void BodyTask (void * arg)
{
   int next ;

   printf ("Iniciei  tarefa %5d\n", task_id()) ;

   // passa o controle para a proxima tarefa
   next = (task_id() < MAXTASK) ? task_id() + 1 : 1 ;
   task_switch (&task[next]);

   printf ("Encerrei tarefa %5d\n", task_id()) ;

   task_exit (0) ;
}

int main (int argc, char *argv[])
{
   int i ;

   printf ("main: inicio\n");

   ppos_init () ;

   // cria MAXTASK tarefas
   for (i=1; i<=MAXTASK; i++)
      task_create (&task[i], BodyTask, NULL) ;

   // passa o controle para cada uma delas em sequencia
   for (i=1; i<=MAXTASK; i++)
      task_switch (&task[i]) ;

   printf ("main: fim\n");

   exit (0);
}