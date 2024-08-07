/* First we have to remove them from the extension */
ALTER EXTENSION pg_power DROP VIEW pg_stat_power;
ALTER EXTENSION pg_power DROP FUNCTION pg_stat_power();

/* Then we can drop them */
DROP VIEW pg_stat_power;
DROP FUNCTION pg_stat_power();

/* Now redefine */
CREATE FUNCTION pg_stat_power(
    OUT userid oid,
    OUT dbid oid,
    OUT query text,
    OUT power int8,
)
RETURNS SETOF record
AS 'MODULE_PATHNAME'
LANGUAGE C;

CREATE VIEW pg_stat_power AS
  SELECT * FROM pg_stat_power();

GRANT SELECT ON pg_stat_power TO PUBLIC;
