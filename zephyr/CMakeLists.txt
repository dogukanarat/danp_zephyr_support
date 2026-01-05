if(CONFIG_DANP_SUPPORT)
    zephyr_library()

    zephyr_interface_library_named(danp_support)

    # Add your DANP support source files
    zephyr_library_sources(
        ../src/danp_shell.c
        ../src/danp_log.c
        ../src/danp_utilities.c
        # Add any other source files from src/ here
    )

    # Include directories
    zephyr_include_directories(
        ../include
        ../src
    )

    # Link against the OSAL library
    zephyr_library_link_libraries(osal)

endif()
