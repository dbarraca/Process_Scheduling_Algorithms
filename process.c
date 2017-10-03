#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "process.h"



Proc *randomProc(int arv, int run, int pri, int name){
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
      *(procs + procNdx) = randomProc(rand(), rand(), rand(), procNdx);
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

int changeCurrProc(Proc **procs, int numProc, int quantum, int curNdx) {
   int procNdx = 0;
   float shortRun = QUANT_MAX;
   int retNdx = curNdx;
   Proc *oldProc = *(procs + curNdx);

   if (curNdx > 0) {
      for (procNdx = 0; procNdx < numProc; procNdx++) {
         Proc *curProc = *(procs + procNdx);

         if(quantum >= curProc->arv && curProc->exp - curProc->run < shortRun &&
          oldProc->exp - oldProc->run < curProc->exp - curProc->run) {
            retNdx = procNdx;
            shortRun = curProc->exp - curProc->run;
         }
      }
   }

   return retNdx;
}

void setProcStart(Proc ** procs, int ndx, int quantum) {
   if (ndx >= 0 && (*(procs + ndx))->start < 0) {
      (*(procs + ndx))->start = quantum;
   }
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

   printf("Name: %i   arrival:%.0f   expected run:%.0f   priority:%i\n",
    proc->name, proc->arv, proc->exp, proc->pri);
}

void printProcName(Proc  **procs, int ndx) {
    if (ndx >= 0) {
       printf("%i", (*(procs + ndx))->name);
    }
}

void printProcs(Proc **procs, int numProc) {
   int procNdx;

   for (procNdx = 0; procNdx < numProc; procNdx++) {
      printProc(*(procs + procNdx));
   }
   printf("\n");
}
