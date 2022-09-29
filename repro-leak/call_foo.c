#include <stddef.h>
#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct ProcStatus
{
	int pid;
	char comm[32];
	char state;
	int ppid;
	int pgrp;
	int session;
	int tty_nr;
	int tpgid;
	unsigned int flags;
	unsigned long minflt;
	unsigned long cminflt;
	unsigned long majflt;
	unsigned long cmajflt;
	unsigned long utime;
	unsigned long stime;
	unsigned long cutime;
	unsigned long cstime;
	unsigned long priority;
	unsigned long nice;
	unsigned long num_threads;
	unsigned long itrealvalue;
	unsigned long long starttime;
	unsigned long vsize;
	unsigned long rss;
	unsigned long rsslim;
	unsigned long startcode;
	unsigned long endcode;
	unsigned long startstack;
	unsigned long kstkesp;
	unsigned long kstkeip;
	unsigned long signal;
	unsigned long blocked;
	unsigned long sigignore;
	unsigned long sigcatch;
	unsigned long wchan;
	unsigned long nswap;
	unsigned long cnswap;
	int exit_signal;
	int processor;
	unsigned int rt_priority;
	unsigned int policy;
	unsigned long long delayacct_blkio_ticks;
	unsigned long guest_time;
	unsigned int cguest_time; // marked as unsigned int in docs
	unsigned long start_data;
	unsigned long end_data;
	unsigned long start_brk;
	unsigned long arg_start;
	unsigned long arg_end;
	unsigned long env_start;
	unsigned long env_end;
	int exit_code;
} ProcStatus;

static char StatusLine[] =
	"%d %s %c %d %d %d %d %u %lu %lu %lu %lu %lu %ld %ld %ld %ld %ld %ld "
	"%llu %lu %ld %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %lu %d %d %u "
	"%u %llu %lu %ld %lu %lu %lu %lu %lu %lu %d";

void proc_read(ProcStatus *procstat)
{
	FILE *ststream = fopen("/proc/self/stat", "r");
	if (!ststream)
	{
		printf("error \n");
		exit(1);
	}

	if (0 > fscanf(ststream, StatusLine, &procstat->pid, &procstat->comm,
				   &procstat->state, &procstat->ppid, &procstat->pgrp,
				   &procstat->session, &procstat->tty_nr, &procstat->tpgid,
				   &procstat->flags, &procstat->minflt, &procstat->cminflt,
				   &procstat->majflt, &procstat->cmajflt, &procstat->utime,
				   &procstat->stime, &procstat->cutime, &procstat->cstime,
				   &procstat->priority, &procstat->nice, &procstat->num_threads,
				   &procstat->itrealvalue, &procstat->starttime, &procstat->vsize,
				   &procstat->rss, &procstat->rsslim, &procstat->startcode,
				   &procstat->endcode, &procstat->startstack, &procstat->kstkesp,
				   &procstat->kstkeip, &procstat->signal, &procstat->blocked,
				   &procstat->sigignore, &procstat->sigcatch, &procstat->wchan,
				   &procstat->nswap, &procstat->cnswap, &procstat->exit_signal,
				   &procstat->processor, &procstat->rt_priority,
				   &procstat->policy, &procstat->delayacct_blkio_ticks,
				   &procstat->guest_time, &procstat->cguest_time,
				   &procstat->start_data, &procstat->end_data,
				   &procstat->start_brk, &procstat->arg_start, &procstat->arg_end,
				   &procstat->env_start, &procstat->env_end))
	{
		printf("error \n");
		exit(1);
	}
	fclose(ststream);
	return;
}

// symbol coming from Go
extern void foo(void);

static void *call_foo(void *p)
{
	foo();
	return NULL;
}

void bar(void)
{
	pthread_t t;
	ProcStatus procstatus;
	pthread_create(&t, NULL, call_foo, NULL);
	proc_read(&procstatus);
	printf("Hello from C : %s", __FUNCTION__);
	printf("procstat->rss %lu\n", procstatus.rss);
	sleep(1);
	pthread_join(t, NULL);
}
