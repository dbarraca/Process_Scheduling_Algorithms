#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "process.h"
#include "algStats.h"

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

   while (((quantum > QUANT_MAX && (*(procs + nextReadyNdx))->start < 0)
    || (*(procs + nextReadyNdx))->arv > quantum) && numChecked < numProcs) {
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

   for (quantum = 0; (quantum < QUANT_MAX || curNdx >= 0)
   && numProcs > 0; quantum++) {

      sliceQuanta++;
      if (sliceQuanta >= TIME_SLICE) {
         sliceQuanta = 0;
         curNdx = curNdx < numProcs ? curNdx : 0;
         curNdx = nextReadyProc(procs, numProcs, curNdx, quantum);
         setProcStart(procs, curNdx, quantum);
      }

      printf(" %i ",quantum);
      if (curNdx >= 0 && (*(procs + curNdx))->arv <= quantum) {

         printf("%i", (*(procs + curNdx))->name);
         (*(procs + curNdx))->run++;
         if ((*(procs + curNdx))->run >= (*(procs + curNdx))->exp) {
            (*(procs + curNdx))->end = quantum;
            procs = removeProc(procs, numProcs, curNdx);
            numProcs--;
         }
      }
      printf("\n");
   }
}

void roundRobinRuns(int numProcs) {
   int seed = 1, run;
   Proc **procs = NULL,
    **allProcs = malloc(sizeof(Proc *) * NUM_RUNS * numProcs);

   srand(seed);

   for (run = 0; run < NUM_RUNS; run++) {
      printf("RUN %i   ", run + 1);
      procs = generateProcs(TOT_PROCS); //generate processes
      printProcs(procs, TOT_PROCS); //print all generated processes
      roundRobin(procs, TOT_PROCS);
//      printProcs(procs, TOT_PROCS); //print all generated processes
      memcpy(allProcs + run * numProcs, procs, sizeof(Proc *) * numProcs);
      free(procs);
      printf("\n");
   }


   algStats(allProcs, NUM_RUNS * TOT_PROCS);
   freeProcs(allProcs, NUM_RUNS * TOT_PROCS);
}
