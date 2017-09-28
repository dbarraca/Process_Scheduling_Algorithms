#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "process.h"


Proc **readyProcs(Proc **procs, int numProcs, Proc ** readyProcs,
 int numReady, int quantum) {
   int procNdx, readyNdx, ready = FALSE;
   Proc *curProc, *curReadyProc, **retProcs = malloc(sizeof(Proc *) * numReady);

   memcpy(retProcs, readyProcs, sizeof(Proc *) * numReady);

   for (procNdx = 0; procNdx < numProcs; procNdx++) {
   curProc = *(procs + procNdx);
      for (readyNdx = 0; readyNdx < numReady; readyNdx++) {
         curReadyProc = *(retProcs + readyNdx);
         if (curProc->name == curReadyProc->name) {
            printf("proc was ready : %c\n", curProc->name);
            ready = TRUE;
         }
      }

      if (ready == FALSE && curProc->arv >= quantum) {
          printf("proc was NOT ready : %c\n", curProc->name);

         retProcs = realloc(retProcs, sizeof(Proc *) * (numReady + 1));
         memcpy(retProcs, readyProcs, sizeof(Proc *) * numReady);
         *(retProcs + numReady) = curProc;
         printf("supposedly added proc : %c\n", ((Proc *) *(retProcs + numReady))->name);

         numReady++;
      }

      ready = FALSE;
   }

   return retProcs;
}

void roundRobin(int numProcs) {
   int seed = 1, quantum, sliceQuanta = 0, curNdx = 0;
   Proc **procs = NULL;

   srand(seed);
   procs = generateProcs(TOT_PROCS);  //generate processes
   printProcs(procs, TOT_PROCS);  //print all generated processes

   for (quantum = 0; quantum < QUANT_MAX; quantum++) {
      printf("%c", ((Proc *) *(procs + curNdx))->name);
      ((Proc *) *(procs + curNdx))->run++;

      if (((Proc *) *(procs + curNdx))->run >=
       ((Proc *) *(procs + curNdx))->exp) {
         procs = removeProc(procs, numProcs, curNdx);
         numProcs--;
      }

      sliceQuanta++;

      if (sliceQuanta >= TIME_SLICE) {
         sliceQuanta = 0;
         curNdx++;
         if (curNdx >= numProcs) {
            curNdx = 0;
         }
      }
   }
}
