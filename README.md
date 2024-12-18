To run this, make sure the postgres binary can read the RAPL file

```
sudo setcap cap_dac_read_search=+ep /usr/lib/postgresql/14/bin/postgres
```
