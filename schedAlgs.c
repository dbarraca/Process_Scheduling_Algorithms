#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "process.h"
#include "schedAlgs.h"

int earlyArv(Proc **procs, int numProc, int quantum) {
   int procNdx = 0;
   float earlyArv = QUANT_MAX;
   int retNdx = -1;

   for (procNdx = 0; procNdx < numProc; procNdx++) {
      Proc *curProc = *(procs + procNdx);

      if(quantum >= curProc->arv && curProc->arv < earlyArv) {
         retNdx = procNdx;
         earlyArv = curProc->arv;
      }
   }

   return retNdx;
}

int shortExp(Proc **procs, int numProc, int quantum) {
   int procNdx = 0;
   float shortExp = QUANT_MAX;
   int retNdx = TOT_PROCS;

   for (procNdx = 0; procNdx < numProc; procNdx++) {
      Proc * curProc = *(procs + procNdx);

      if(quantum > curProc->arv && curProc->exp < shortExp) {
         retNdx = procNdx;
         shortExp = curProc->exp;
      }
   }

   return retNdx;
}

void FCFS(Proc **procs, int numProcs) {
   int quantum, curNdx = -1;

   for (quantum = 0; quantum < QUANT_MAX; quantum++) {
//      printf("%i\n", quantum);
      if (curNdx > -1 && *(procs + curNdx) != NULL) {
         ((Proc *) *(procs + curNdx))->run++;
         if (((Proc *) *(procs + curNdx))->run >= ((Proc *) *(procs + curNdx))->exp) {
            procs = removeProc(procs, numProcs, curNdx);
            numProcs--;

            curNdx = earlyArv(procs, numProcs, quantum);
         }
      }
      else {
         curNdx = earlyArv(procs, numProcs, quantum);
      }

      if(curNdx >= 0) {
         printf("%c", ((Proc *) *(procs + curNdx))->name);
      }
   }

}
/**
 * returns the processes in arrival time order with earliest first
 */
Proc **orderProcs(Proc **procs, int numProc, int (*schedAlg)(Proc **, int)) {
   Proc **orderedProcs = malloc(sizeof(Proc *) * numProc);
   Proc **unorderedProcs = malloc(sizeof(Proc *) * numProc);
   int numUnordered = numProc, retNumProc = 0, procNdx;

   memcpy(unorderedProcs, procs, sizeof(Proc *) * numProc);

   for(procNdx = 0; procNdx < numProc; procNdx++) {
      *(orderedProcs + retNumProc) =
       *(unorderedProcs + (*schedAlg)(unorderedProcs, numUnordered));
      retNumProc++;

      unorderedProcs = removeProc(unorderedProcs, numUnordered,
       (*schedAlg)(unorderedProcs, numUnordered));
      numUnordered--;
   }

   free(unorderedProcs);

   return orderedProcs;
}
