MODULES = pg_power
EXTENSION = pg_power
DATA = pg_power--0.0.1.sql

# for postgres build
PG_CONFIG = pg_config
PGXS := $(shell $(PG_CONFIG) --pgxs)
include $(PGXS)
