#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "process.h"
#include "timeSchedAlgs.h"
#include "roundRobin.h"

#define TRUE 1
#define FALSE 0

int main() {
/*   printf("First Come First Serve\n");
   multipleRuns(TOT_PROCS, FALSE, NUM_RUNS, earlyArv);

   printf("\nShortest Job Time\n");
   multipleRuns(TOT_PROCS, FALSE, NUM_RUNS, shortExp);

   printf("\nShortest Remaining Time\n");
   multipleRuns(TOT_PROCS, TRUE, NUM_RUNS, shortRemain);
*/

   printf("Round Robin\n\n");
   roundRobinRuns(TOT_PROCS);

   return 0;
}
