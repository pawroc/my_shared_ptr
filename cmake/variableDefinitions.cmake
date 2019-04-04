set(PROJECT_ROOT "..")
set(PREFIX_ROOT "prefix_root")
set(ENV{HUNTER_ROOT} "${PROJECT_ROOT}/${PREFIX_ROOT}")

execute_process (
    COMMAND bash -c "mkdir -p $ENV{HUNTER_ROOT}"
)