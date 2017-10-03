#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "process.h"
#include "timeSchedAlgs.h"

int earlyArv(Proc **procs, int numProc, int quantum) {
   int procNdx = 0;
   float earlyArv = QUANT_MAX;
   int retNdx = -1;

   for (procNdx = 0; procNdx < numProc; procNdx++) { //loop through processes
      Proc *curProc = *(procs + procNdx); //get current process

      //check if process is ready and if it is earliest
      if(quantum >= curProc->arv && curProc->arv < earlyArv) {
         retNdx = procNdx; //change return index
         earlyArv = curProc->arv; //get process arrival time
      }
   }

   return retNdx; //return index of earliest process
}

int shortExp(Proc **procs, int numProc, int quantum) {
   int procNdx = 0;
   float shortExp = QUANT_MAX;
   int retNdx = -1;

   for (procNdx = 0; procNdx < numProc; procNdx++) { //loop through processes
      Proc *curProc = *(procs + procNdx); //get current process

      //check if process is ready and if it is has shortest expected run time
      if(quantum >= curProc->arv && curProc->exp < shortExp) {
         retNdx = procNdx; //change return index
         shortExp = curProc->exp;//get process expected run time time
      }
   }

   return retNdx; //return index of process with shortest expected run time
}

int shortRemain(Proc **procs, int numProc, int quantum) {
   int procNdx = 0;
   float shortRun = QUANT_MAX;
   int retNdx = -1;

   for (procNdx = 0; procNdx < numProc; procNdx++) { //loop through processes
      Proc *curProc = *(procs + procNdx); //get current process

      //check if process is ready and if it is has shortest expected run time
      if(quantum >= curProc->arv && curProc->exp - curProc->run < shortRun) {
         retNdx = procNdx; //change return index
         shortRun = curProc->exp - curProc->run;;//get process remaining time
      }
   }

   return retNdx;//return index of process with shortest remaining run time
}

void runAlg(Proc **procs, int numProcs, int preemp,
 int (*nextProc)(Proc **procs, int numProc, int quantum)) {
   int quantum, curNdx = -1, numStarted = 0;

   for (quantum = 0; (quantum < QUANT_MAX || curNdx >= 0)  && numProcs > 0; quantum++) { //count quanta
//      printf("%i ", quantum);
      if (curNdx >= 0) { //check for running process
         (*(procs + curNdx))->run++; //increase running process run time

         if ((*(procs + curNdx))->run >= (*(procs + curNdx))->exp) { //check run time
            numStarted--;
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
         if(curNdx >= 0)
            (*(procs + curNdx))->run++; //increase running process run time
      }
      if(curNdx > 0 && (*(procs + curNdx))->start < 0)
         numStarted++;
      setProcStart(procs, curNdx, quantum); //mark start of process run
      printProcName(procs, curNdx); //print processes name for time chart
      printf(",");
//      printf("\n");
   }
}

void multipleRuns(int numProcs, int preemp, int numRuns,
 int (*nextProc)(Proc **procs, int numProc, int quantum)) {
   int seed = 1, run;
   Proc **procs = NULL,
    **allProcs = malloc(sizeof(Proc *) * numRuns * numProcs);

   srand(seed);
   for (run = 0; run < numRuns; run++) { //loop through runs
      printf("RUN %i\n", run + 1); //print run number
      procs = generateProcs(TOT_PROCS);  //generate processes
//      printProcs(procs, TOT_PROCS);  //print all generated processes
      runAlg(procs, TOT_PROCS, preemp, nextProc);
      algStats(procs, TOT_PROCS);
      printf("\n");
    //  printProcs(procs, TOT_PROCS);  //print all generated processes
      memcpy(allProcs + run * numProcs, procs, sizeof(Proc *) * numProcs);
      free(procs); // free pointer to process
   }

   algStats(allProcs, NUM_RUNS * TOT_PROCS); // print statistics on algorithm
   freeProcs(allProcs, NUM_RUNS * TOT_PROCS); // fre al process
}

Proc **orderProcs(Proc **procs, int numProc, int (*schedAlg)(Proc **, int, int)) {
   Proc **orderedProcs = malloc(sizeof(Proc *) * numProc);
   Proc **unorderedProcs = malloc(sizeof(Proc *) * numProc);
   int numUnordered = numProc, retNumProc = 0, procNdx;

   memcpy(unorderedProcs, procs, sizeof(Proc *) * numProc); // copy processes

   for(procNdx = 0; procNdx < numProc; procNdx++) { //loop through process
      //set next ordered process
      *(orderedProcs + retNumProc) =
       *(unorderedProcs + (*schedAlg)(unorderedProcs, numUnordered, QUANT_MAX));
      retNumProc++;

      //remove process from unordered processes
      unorderedProcs = removeProc(unorderedProcs, numUnordered,
       (*schedAlg)(unorderedProcs, numUnordered, QUANT_MAX));
      numUnordered--; //decrement number of unordered processes
   }

   free(unorderedProcs); // free pointer

   return orderedProcs; // return ordered processes
}
