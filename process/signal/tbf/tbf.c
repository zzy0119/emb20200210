#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include "tbf.h"

typedef struct {
	int token;
	int cps;
	int burst;	
}tbf_t;

static int inited;
static tbf_t *jobs[MAXTBF];

static int getFreePos(void)
{
	for (int i = 0; i < MAXTBF; i++)
		if (jobs[i] == NULL)
			return i;
	return -1;
}

static void alrm_handler(int s)
{
	// 管理令牌桶库
	alarm(1);

	for (int i = 0; i < MAXTBF; i++) {
		if (jobs[i] != NULL) {
			jobs[i]->token += jobs[i]->cps;
			if (jobs[i]->token >= jobs[i]->burst)
				jobs[i]->token = jobs[i]->burst;
		}
	}
}

static void moduler_load(void)
{
	signal(SIGALRM, alrm_handler);
	alarm(1);
}

int tbfInit(int cps, int burst)
{
	tbf_t *me = NULL;
	int pos;

	if (inited == 0) {
		// 管理令牌桶库的信号还未加载
		moduler_load();
		inited = 1;
	}

	me = malloc(sizeof(*me));
	if (NULL == me)
		return -1;
	me->token = 0;
	me->cps = cps;
	me->burst = burst;

	pos = getFreePos();
	if (pos == -1) {
		free(me);	
		return -1;
	}
	jobs[pos] = me;

	return pos;
}

int tbfFetchToken(int td, int token)
{
	int ret;

	if (td < 0 || token <= 0)
		return -1;
	while (jobs[td]->token <= 0)
		pause();
	if (jobs[td]->token < token) {
		ret = jobs[td]->token;
		jobs[td]->token -= ret;
		return ret;
	}
		
	jobs[td]->token -= token;

	return token;
}

int tbfReturnToken(int td, int token)
{
	if (td < 0 || token <= 0)
		return -1;
	jobs[td]->token += token;
	if (jobs[td]->token > jobs[td]->burst)
		jobs[td]->token = jobs[td]->burst;

	return 0;
}

void tbfDestroy(int td)
{
	free(jobs[td]);
	jobs[td] = NULL;
}

