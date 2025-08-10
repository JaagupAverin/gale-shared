message("Gale shared module included.")

add_subdirectory_ifdef(CONFIG_GALE_IPC ipc)
