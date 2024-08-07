#include "postgres.h"

#include <math.h>
#include <sys/stat.h>
#include <unistd.h>

#include "rapl.h"
#include "access/parallel.h"
#include "catalog/pg_authid.h"
#include "common/hashfn.h"
#include "common/int.h"
#include "executor/instrument.h"
#include "funcapi.h"
#include "jit/jit.h"
#include "mb/pg_wchar.h"
#include "miscadmin.h"
#include "nodes/queryjumble.h"
#include "optimizer/planner.h"
#include "parser/analyze.h"
#include "parser/parsetree.h"
#include "parser/scanner.h"
#include "parser/scansup.h"
#include "pgstat.h"
#include "storage/fd.h"
#include "storage/ipc.h"
#include "storage/lwlock.h"
#include "storage/shmem.h"
#include "storage/spin.h"
#include "tcop/utility.h"
#include "utils/acl.h"
#include "utils/builtins.h"
#include "utils/memutils.h"
#include "utils/timestamp.h"

PG_MODULE_MAGIC;

static int core = 0;

static ExecutorStart_hook_type prev_ExecutorStart = NULL;
static ExecutorEnd_hook_type prev_ExecutorEnd = NULL;

static void pg_power_ExecutorStart(QueryDesc *queryDesc, int eflags);
static void pg_power_ExecutorEnd(QueryDesc *queryDesc);

void _PG_init(void) {
	EnableQueryId();

	rapl_init(core);

	prev_ExecutorStart = ExecutorStart_hook;
	ExecutorStart_hook = pg_power_ExecutorStart;

	prev_ExecutorEnd = ExecutorEnd_hook;
	ExecutorEnd_hook = pg_power_ExecutorEnd;
}

static void pg_power_ExecutorStart(QueryDesc *queryDesc, int eflags) {
	if (prev_ExecutorStart)
		prev_ExecutorStart(queryDesc, eflags);
	else
		standard_ExecutorStart(queryDesc, eflags);
}

static void pg_power_ExecutorEnd(QueryDesc *queryDesc) {
}
