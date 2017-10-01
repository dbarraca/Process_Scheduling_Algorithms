#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "process.h"

/**
 * Find the index of the next process with arrival time past the given quantum.
 * If the last processes is reached,start checking first process.
 * If the original process is checked. end checking and return no ready process found, -1.
 */
int nextReadyProc(Proc **procs, int numProcs, int startNdx, int quantum) {
   int nextReadyNdx = startNdx + 1, numChecked = 0;

   if (nextReadyNdx >= numProcs) {
      nextReadyNdx = 0;
   }

   while ((*(procs + nextReadyNdx))->arv > quantum && numChecked < numProcs) {
       numChecked++;
       nextReadyNdx++;
       if (nextReadyNdx >= numProcs) {
          nextReadyNdx = 0;
       }
    }

    if (numChecked >= numProcs)
       nextReadyNdx = -1;

    return nextReadyNdx;
}

void roundRobin(Proc **procs, int numProcs) {
   int quantum, sliceQuanta = 0, curNdx = 0;

   for (quantum = 0; quantum < QUANT_MAX; quantum++) {

      sliceQuanta++;
      if (sliceQuanta >= TIME_SLICE) {
         sliceQuanta = 0;
         curNdx = curNdx < numProcs ? curNdx : 0;
         curNdx = nextReadyProc(procs, numProcs, curNdx, quantum);
      }

      printf("%i ",quantum);
      if (curNdx >= 0 && (*(procs + curNdx))->arv <= quantum) {
         printf("%c", (*(procs + curNdx))->name);
         (*(procs + curNdx))->run++;

         if ((*(procs + curNdx))->run >= (*(procs + curNdx))->exp) {
            procs = removeProc(procs, numProcs, curNdx);
            numProcs--;
         }
      }
      printf("\n");
   }
}

void roundRobinRuns(int numProcs) {
   int seed = 1;
   Proc **procs = NULL;

   srand(seed);
   procs = generateProcs(TOT_PROCS); //generate processes
   printProcs(procs, TOT_PROCS); //print all generated processes

   roundRobin(procs, TOT_PROCS);
}
