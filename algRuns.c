#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

#include "process.h"
#include "schedAlgs.h"

#define TOT_PROCS 10

void freeProcs(Proc **procs, int numProc) {
	int procIndex;

	for (procIndex = 0; procIndex < numProc; procIndex++) {
        free(*(procs + procIndex));
	}
}

int main() {
    Proc **procs = generateProcs(TOT_PROCS);
    printProcs(arrivalOrder(procs, TOT_PROCS), TOT_PROCS);

    free(procs);
    freeProcs(procs, TOT_PROCS);
}
