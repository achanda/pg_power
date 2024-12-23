#include "postgres.h"
#include "fmgr.h"
#include "executor/executor.h"

PG_MODULE_MAGIC;

static ExecutorStart_hook_type prev_ExecutorStart = NULL;
static ExecutorEnd_hook_type prev_ExecutorEnd = NULL;

static unsigned long long start = 0;

unsigned long long read_energy_uj() {
    const char* file_path = "/sys/devices/virtual/powercap/intel-rapl/intel-rapl:0/energy_uj";
    FILE* file = fopen(file_path, "r");

    if (file == NULL) {
        elog(LOG, "[ERROR] Failed to open energy file: %s\n", file_path);
        exit(EXIT_FAILURE);
    }

    unsigned long long energy_value;
    int result = fscanf(file, "%llu", &energy_value);

    if (result != 1) {
        elog(LOG, "[ERROR] Failed to read energy value from file: %s\n", file_path);
        exit(EXIT_FAILURE);
    }

    fclose(file);
    return energy_value;
}

static void custom_ExecutorStart(QueryDesc *queryDesc, int eflags)
{
    start = read_energy_uj();
    elog(LOG, "Query execution starting: %lld", start);

    if (prev_ExecutorStart)
        prev_ExecutorStart(queryDesc, eflags);
    else
        standard_ExecutorStart(queryDesc, eflags);
}

static void custom_ExecutorEnd(QueryDesc *queryDesc)
{
    unsigned long long current = read_energy_uj();
    elog(LOG, "Query execution completed: %lld", current-start);

    if (prev_ExecutorEnd)
        prev_ExecutorEnd(queryDesc);
    else
        standard_ExecutorEnd(queryDesc);
}

void _PG_init(void)
{
    prev_ExecutorStart = ExecutorStart_hook;
    ExecutorStart_hook = custom_ExecutorStart;
    prev_ExecutorEnd = ExecutorEnd_hook;
    ExecutorEnd_hook = custom_ExecutorEnd;
}

void _PG_fini(void)
{
    ExecutorStart_hook = prev_ExecutorStart;
    ExecutorEnd_hook = prev_ExecutorEnd;
}
