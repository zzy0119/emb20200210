#ifndef __TBF_H
#define __TBF_H

#define MAXTBF	1024

int tbfInit(int cps, int burst);

int tbfFetchToken(int td, int token);

int tbfReturnToken(int td, int token);

void tbfDestroy(int td);

#endif

