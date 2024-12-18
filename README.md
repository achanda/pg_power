To run this, make sure the postgres binary can read the RAPL file

```
sudo setcap cap_dac_read_search=+ep /usr/lib/postgresql/14/bin/postgres
```

Sample output from the postgres server

```
abhishek@guest:~$ /usr/lib/postgresql/14/bin/postgres --config-file=$(pwd)/pgdata/postgresql.conf -D $(pwd)/pgdata -k $(pwd)/pgdata
2024-12-18 03:13:00.490 GMT [1751699] LOG:  starting PostgreSQL 14.13 (Ubuntu 14.13-0ubuntu0.22.04.1) on x86_64-pc-linux-gnu, compiled by gcc (Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0, 64-bit
2024-12-18 03:13:00.490 GMT [1751699] LOG:  listening on IPv6 address "::1", port 5432
2024-12-18 03:13:00.490 GMT [1751699] LOG:  listening on IPv4 address "127.0.0.1", port 5432
2024-12-18 03:13:00.492 GMT [1751699] LOG:  listening on Unix socket "/home/abhishek/pgdata/.s.PGSQL.5432"
2024-12-18 03:13:00.494 GMT [1751700] LOG:  database system was shut down at 2024-12-18 03:12:28 GMT
2024-12-18 03:13:00.498 GMT [1751699] LOG:  database system is ready to accept connections
2024-12-18 03:13:09.611 GMT [1751715] LOG:  Query execution starting: 69877598944
2024-12-18 03:13:09.611 GMT [1751715] STATEMENT:  select 1+1;
2024-12-18 03:13:09.611 GMT [1751715] LOG:  Query execution completed: 3785
2024-12-18 03:13:09.611 GMT [1751715] STATEMENT:  select 1+1;
^C2024-12-18 03:13:21.466 GMT [1751699] LOG:  received fast shutdown request
2024-12-18 03:13:21.469 GMT [1751699] LOG:  aborting any active transactions
2024-12-18 03:13:21.469 GMT [1751715] FATAL:  terminating connection due to administrator command
2024-12-18 03:13:21.471 GMT [1751699] LOG:  background worker "logical replication launcher" (PID 1751706) exited with exit code 1
2024-12-18 03:13:21.472 GMT [1751701] LOG:  shutting down
2024-12-18 03:13:21.481 GMT [1751699] LOG:  database system is shut down
```
