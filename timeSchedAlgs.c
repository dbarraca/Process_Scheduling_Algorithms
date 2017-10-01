#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "process.h"
#include "timeSchedAlgs.h"

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
   int retNdx = -1;

   for (procNdx = 0; procNdx < numProc; procNdx++) {
      Proc *curProc = *(procs + procNdx);

      if(quantum >= curProc->arv && curProc->exp < shortExp) {
         retNdx = procNdx;
         shortExp = curProc->exp;
      }
   }

   return retNdx;
}

int shortRemain(Proc **procs, int numProc, int quantum) {
   int procNdx = 0;
   float shortRun = QUANT_MAX;
   int retNdx = -1;

   for (procNdx = 0; procNdx < numProc; procNdx++) {
      Proc *curProc = *(procs + procNdx);

      if(quantum >= curProc->arv && curProc->exp - curProc->run < shortRun) {
         retNdx = procNdx;
         shortRun = curProc->exp - curProc->run;
      }
   }

   return retNdx;
}

void runAlg(Proc **procs, int numProcs, int preemp,
 int (*nextProc)(Proc **procs, int numProc, int quantum)) {
   int quantum, curNdx = -1;

   for (quantum = 0; quantum < QUANT_MAX || curNdx >= 0; quantum++) { //count quanta
      printf("%i ", quantum);
      if (curNdx >= 0) { //check for running process
         (*(procs + curNdx))->run++; //increase running process run time

         if ((*(procs + curNdx))->run >= (*(procs + curNdx))->exp) { //check run time

            (*(procs + curNdx))->end = quantum; //mark end of process run
            procs = removeProc(procs, numProcs, curNdx); //remove done process
            numProcs--;
            if (quantum < QUANT_MAX)
               curNdx = (*nextProc)(procs, numProcs, quantum); //run new process
            else
               curNdx = -1;
         }
         else if (preemp == TRUE)  //check if preemptive
            curNdx = changeCurrProc(procs, numProcs - 1, quantum, curNdx); //change running process
      }
      else {
         curNdx = (*nextProc)(procs, numProcs, quantum); //new running process
      }

      setProcStart(procs, curNdx, quantum); //mark start of process run
      printProcName(procs, curNdx); //print processes name for time chart
      printf("\n");
   }
}

void multipleRuns(int numProcs, int preemp, int numRuns,
 int (*nextProc)(Proc **procs, int numProc, int quantum)) {

   int seed = 1, run;
   Proc **procs = NULL,
    **allProcs = malloc(sizeof(Proc *) * numRuns * numProcs);

   srand(seed);
   for (run = 0; run < numRuns; run++) {
      procs = generateProcs(TOT_PROCS);  //generate processes
//      printProcs(procs, TOT_PROCS);  //print all generated processes
      printf("RUN #%i ", run + 1);

      runAlg(procs, TOT_PROCS, preemp, nextProc);
      printf("\n");
      printProcs(procs, TOT_PROCS);  //print all generated processes
      memcpy(allProcs + run * numProcs, procs, sizeof(Proc *) * numProcs);
      free(procs);
   }

   algStats(allProcs, NUM_RUNS * TOT_PROCS);
   freeProcs(allProcs, NUM_RUNS * TOT_PROCS);
}

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
