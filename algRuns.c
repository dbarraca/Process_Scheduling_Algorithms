#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "process.h"
#include "schedAlgs.h"

int main() {
   Proc **procs = generateProcs(TOT_PROCS);  //generate processes

   printProcs(procs, TOT_PROCS);  //print all genrated processes

   FCFS(procs, TOT_PROCS);  //run first come firs serve scheduling

   freeProcs(procs, TOT_PROCS);  //free each individual process
   free(procs);  //free pointer to all processes

   return 0;
}
