#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "process.h"

#define ARV_MAX 20
#define RUN_MAX 11
#define PRI_MAX 5

Proc *randomProc(int arv, int run, int pri, char name){
   Proc *proc = malloc(sizeof(Proc));

   proc->arv = arv % ARV_MAX;
   proc->exp = run % RUN_MAX;
   if(proc->exp == 0) {
      proc->exp += 1;
   }
   proc->pri = pri % PRI_MAX;
   if(proc->pri == 0) {
      proc->pri += 1;
   }
   proc->run = 0;
   proc->name = name;
   proc->start = -1;
   proc->end = -1;

   return proc;
}

Proc **generateProcs(int numProc) {
   int procNdx = 0;
   Proc **procs = malloc(sizeof(Proc *) * numProc);


   for (procNdx = 0; procNdx < numProc; procNdx++) {
      *(procs + procNdx) = randomProc(rand(), rand(), rand(), 'A' + procNdx);
   }

   return procs;
}

Proc **removeProc(Proc **procs, int numProc, int rmvNdx) {
   Proc **procsCopy = malloc(sizeof(Proc *) * (numProc - 1));

   memcpy(procsCopy, procs, sizeof(Proc *) * rmvNdx);
   memcpy(procsCopy + rmvNdx, procs + (rmvNdx + 1),
    sizeof(Proc *) * (numProc - rmvNdx - 1));

   return procsCopy;
}

void freeProcs(Proc **procs, int numProc) {
   int procNdx;

   for (procNdx = 0; procNdx < numProc; procNdx++) {
      free(*(procs + procNdx));
   }
   free(procs);

}

Proc **copyProcs(Proc **procs, int numProc) {
   int procNdx;
   Proc **procsCopy = malloc(sizeof(Proc *) * numProc);

   for(procNdx = 0; procNdx < numProc; procNdx++) {
     *(procsCopy + procNdx) = malloc(sizeof(Proc));
      memcpy(*(procsCopy + procNdx), *(procs + procNdx), sizeof(Proc));
   }

   return procsCopy;
}

void printProc(Proc *proc) {

   printf("%c   arv:%.0f   exp:%.0f   pri:%i start:%i end:%i run:%f\n", proc->name, proc->arv,
      proc->exp, proc->pri, proc->start, proc->end, proc->run);
/*
  printf("arrival time  = %f\n", proc->arv);
  printf("run time  = %f\n", proc->exp);
  printf("priority  = %i\n\n", proc->pri);
*/
}

void printProcs(Proc **procs, int numProc) {
   int procNdx;

   for (procNdx = 0; procNdx < numProc; procNdx++) {
      printProc(*(procs + procNdx));
   }
   printf("\n");
}
