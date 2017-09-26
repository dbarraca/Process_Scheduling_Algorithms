#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "process.h"
#include "schedAlgs.h"
#include "roundRobin.h"
#include "algStats.h"

#define TRUE 1
#define FALSE 0
#define NUM_RUNS 1

void runAlg(Proc **procs, int numProcs, int preemp,
 int (*nextProc)(Proc **procs, int numProc, int quantum)) {
   int quantum, curNdx = -1;

   //count quanta
   for (quantum = 0; quantum < QUANT_MAX || curNdx >= 0; quantum++) {
//      printf(" %i", quantum);

      //check for running process
      if (curNdx >= 0 && *(procs + curNdx) != NULL) {
         //increment running process's run time
         ((Proc *) *(procs + curNdx))->run++;

         //check if running process reached end of run time
         if (((Proc *) *(procs + curNdx))->run >= ((Proc *)
          *(procs + curNdx))->exp) {

            (*(procs + curNdx))->end = quantum;
            //remove finished process
            procs = removeProc(procs, numProcs, curNdx);
            numProcs--;

            //set a new running process
            curNdx = (*nextProc)(procs, numProcs, quantum);
         }
         else if (curNdx >= 0 && preemp == TRUE &&
          possibleNextProc(procs, numProcs - 1, quantum, *(procs + curNdx)) > 0) {
            //if pre-emptive and there is a process that is better fit,
            //replace current process
            curNdx = possibleNextProc(procs, numProcs - 1, quantum, *(procs + curNdx));
         }
      }
      else {
         //replace proc if there is one available
         curNdx = (*nextProc)(procs, numProcs, quantum);
      }

      if (curNdx >= 0 && (*(procs + curNdx))->start < 0) {
         (*(procs + curNdx))->start = quantum;
      }


      //print name of current process if there is one
      if (curNdx >= 0) {
         printf("%c", ((Proc *) *(procs + curNdx))->name);
      }
   }

   printf("\n\n");
}

void multipleRuns(int numProcs, int preemp, int numRuns,
 int (*nextProc)(Proc **procs, int numProc, int quantum)) {

   int seed = 1, run;
   Proc **procs = NULL,
    **allProcs = malloc(sizeof(Proc *) * numRuns * numProcs);

   srand(seed);
   for (run = 0; run < numRuns; run++) {
      printf("RUN #%i   ", run + 1);
      procs = generateProcs(TOT_PROCS);  //generate processes
      //printProcs(procs, TOT_PROCS);  //print all generated processes

      runAlg(procs, TOT_PROCS, preemp, nextProc);
      memcpy(allProcs + run * numProcs, procs, sizeof(Proc *) * numProcs);
      free(procs);
   }

   algStats(allProcs, NUM_RUNS * TOT_PROCS);
   freeProcs(allProcs, NUM_RUNS * TOT_PROCS);
}

int main() {
   printf("\nFirst Come First Serve\n");
   multipleRuns(TOT_PROCS, FALSE, NUM_RUNS, earlyArv);

   printf("\nShortest Job Time\n");
   multipleRuns(TOT_PROCS, FALSE, NUM_RUNS, shortExp);
   printf("\nShortest Remaining Time\n");
   multipleRuns(TOT_PROCS, TRUE, NUM_RUNS, shortRemain);

/*
   printf("Round Robin\n\n");
   roundRobin(TOT_PROCS);
   printf("Finished Round Robin\n\n");
*/
   return 0;
}
