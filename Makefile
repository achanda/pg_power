EXTENSION = pg_power
MODULE_big = pg_power
DATA = pg_power--0.0.1.sql
OBJS = pg_power.o rapl.o 
PG_CONFIG = /usr/local/pgsql/bin/pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
