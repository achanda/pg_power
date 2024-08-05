use pgrx::prelude::*;

pgrx::pg_module_magic!();

use pgrx::hooks::ExecutorHooks;
use pgrx::pg_sys;

#[pg_guard]
pub extern "C" fn _PG_init() {
    ExecutorHooks::register(CustomExecutorHooks {})
}

struct CustomExecutorHooks;

impl ExecutorHooks for CustomExecutorHooks {
    fn standard_executor_run(
        &self,
        query_desc: *mut pg_sys::QueryDesc,
        direction: pg_sys::ScanDirection,
        count: u64,
        execute_once: bool,
    ) {
        // Print the query before running
        unsafe {
            if let Some(query_string) = (*query_desc).sourceText.as_ref() {
                pgrx::log!("Executing query: {}", query_string);
            }
        }

        // Call the real standard_executorRun
        unsafe {
            pg_sys::standard_ExecutorRun(query_desc, direction, count, execute_once);
        }
    }
}

#[cfg(any(test, feature = "pg_test"))]
#[pg_schema]
mod tests {
    use pgrx::prelude::*;

    #[pg_test]
    fn test_hello_pg_power() {
        assert_eq!("Hello, pg_power", crate::hello_pg_power());
    }

}

/// This module is required by `cargo pgrx test` invocations.
/// It must be visible at the root of your extension crate.
#[cfg(test)]
pub mod pg_test {
    pub fn setup(_options: Vec<&str>) {
        // perform one-off initialization when the pg_test framework starts
    }

    pub fn postgresql_conf_options() -> Vec<&'static str> {
        // return any postgresql.conf settings that are required for your tests
        vec![]
    }
}
