# =============================================================================
# Add network application to build:

if(SB_CONFIG_NET_APP_NAME)
  ExternalZephyrProject_Add(
    APPLICATION ${SB_CONFIG_NET_APP_NAME}
    SOURCE_DIR ${SYSBUILD_CURRENT_MODULE_DIR}/${SB_CONFIG_NET_APP_NAME}
    BOARD ${SB_CONFIG_NET_APP_BOARD}
  )
endif()

# These only affect the native_sim build, otherwise not important:
# (With native_sim both applications are built into the same final executable)
native_simulator_set_child_images(${DEFAULT_IMAGE} ${SB_CONFIG_NET_APP_NAME})
native_simulator_set_final_executable(${DEFAULT_IMAGE})

# Build the network application first:
add_dependencies(${DEFAULT_IMAGE} ${SB_CONFIG_NET_APP_NAME})

message(
"Added network application to the build:
  app: ${SB_CONFIG_NET_APP_NAME}
  board: ${SB_CONFIG_NET_APP_BOARD}
")

# =============================================================================
# Add shared overlays and .confs to the built applications:

# Usage:
#   add_shared_overlays_and_confs(APP <app_name> BOARD <board>)
#
# Board is used to determine which extra overlay and .conf files to include in the build:
#  - `app_name_EXTRA_DTC_OVERLAY_FILE` and `app_name_EXTRA_CONF_FILE` will both be set based on the board.
#  - The "app_name_" prefix is a sysbuild convention for passing the given options only to a specific app.
function(add_shared_overlays_and_confs)
  cmake_parse_arguments(ARG "" "APP;BOARD" "" ${ARGV})

  set(overlay)
  set(dotconf)

  if(ARG_BOARD STREQUAL "nrf5340bsim/nrf5340/cpuapp")
    list(APPEND overlay ${SYSBUILD_CURRENT_MODULE_DIR}/boards/nrf5340bsim_nrf5340_cpuapp.overlay)
    list(APPEND dotconf ${SYSBUILD_CURRENT_MODULE_DIR}/soc/bsim.conf)
  elseif(ARG_BOARD STREQUAL "nrf54l15bsim/nrf54l15/cpuapp")
    list(APPEND overlay ${SYSBUILD_CURRENT_MODULE_DIR}/boards/nrf54l15bsim_nrf54l15_cpuapp.overlay)
    list(APPEND dotconf ${SYSBUILD_CURRENT_MODULE_DIR}/soc/bsim.conf)
  elseif(ARG_BOARD STREQUAL "nrf5340bsim/nrf5340/cpunet")
    list(APPEND overlay ${SYSBUILD_CURRENT_MODULE_DIR}/boards/nrf5340bsim_nrf5340_cpunet.overlay)
    list(APPEND dotconf ${SYSBUILD_CURRENT_MODULE_DIR}/soc/bsim.conf)
  else()
    message(FATAL_ERROR "Unrecognized board: ${ARG_BOARD}")
  endif()

  list(APPEND dotconf ${SYSBUILD_CURRENT_MODULE_DIR}/soc/global.conf)

  set(${ARG_APP}_EXTRA_DTC_OVERLAY_FILE ${overlay} CACHE INTERNAL "")
  set(${ARG_APP}_EXTRA_CONF_FILE        ${dotconf} CACHE INTERNAL "")
  message(
  "Added shared overlays and defconfigs to the build:
    app: ${ARG_APP}
    EXTRA_DTC_OVERLAY_FILE: ${overlay}
    EXTRA_CONF_FILE: ${dotconf}
  ")
endfunction()

add_shared_overlays_and_confs(APP ${DEFAULT_IMAGE}          BOARD ${CACHED_BOARD})
add_shared_overlays_and_confs(APP ${SB_CONFIG_NET_APP_NAME} BOARD ${SB_CONFIG_NET_APP_BOARD})
