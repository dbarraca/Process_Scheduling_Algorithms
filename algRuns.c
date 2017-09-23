#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "process.h"
#include "schedAlgs.h"

#define TOT_PROCS 10
#define TRUE 1
#define FALSE 0
#define NUM_RUNS 1

int possibleNextProc(Proc **procs, int numProc, int quantum, Proc *oldProc) {
   int procNdx = 0;
   float shortRun = QUANT_MAX;
   int retNdx = -1;

   for (procNdx = 0; procNdx < numProc; procNdx++) {
      Proc *curProc = *(procs + procNdx);

      if(quantum >= curProc->arv && curProc->exp - curProc->run < shortRun &&
       oldProc->exp - oldProc->run < curProc->exp - curProc->run) {
         retNdx = procNdx;
         shortRun = curProc->exp - curProc->run;
      }
   }

   return retNdx;
}

void runAlg(Proc **procs, int numProcs, int preemp,
 int (*nextProc)(Proc **procs, int numProc, int quantum)) {
   int quantum, curNdx = -1;

   for (quantum = 0; quantum < QUANT_MAX; quantum++) {
//      printf("%i\n", quantum);
      if (curNdx >= 0 && *(procs + curNdx) != NULL) {
         ((Proc *) *(procs + curNdx))->run++;
         if (((Proc *) *(procs + curNdx))->run >= ((Proc *) *(procs + curNdx))->exp) {
            procs = removeProc(procs, numProcs, curNdx);
            numProcs--;

            curNdx = (*nextProc)(procs, numProcs, quantum);
         }
         else if (curNdx > 0 && preemp == TRUE &&
          possibleNextProc(procs, numProcs - 1, quantum, *(procs + curNdx)) > 0) {
            curNdx = possibleNextProc(procs, numProcs - 1, quantum, *(procs + curNdx));
         }
      }
      else {
         curNdx = (*nextProc)(procs, numProcs, quantum);
      }

      if (curNdx >= 0) {
         printf("%c", ((Proc *) *(procs + curNdx))->name);
      }
   }

   printf("\n");
}

void multipleRuns(int numProcs, int preemp,
 int (*nextProc)(Proc **procs, int numProc, int quantum)) {

   int seed = 1, run;
   Proc **procs = NULL;

   srand(seed);
   for (run = 0; run < NUM_RUNS; run++) {
      procs = generateProcs(TOT_PROCS);  //generate processes
//      printProcs(procs, TOT_PROCS);  //print all generated processes

      runAlg(procs, TOT_PROCS, preemp, nextProc);
      freeProcs(procs, TOT_PROCS);  //free each individual process
      free(procs);
   }
}

int main() {

   printf("\nFCFS\n");
   multipleRuns(TOT_PROCS, FALSE, earlyArv);
   printf("\nSJT\n");
   multipleRuns(TOT_PROCS, FALSE, shortExp);
   printf("\nSRT\n");
   multipleRuns(TOT_PROCS, TRUE, shortRemain);

   return 0;
}
