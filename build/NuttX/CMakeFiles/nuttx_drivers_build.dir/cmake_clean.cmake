file(REMOVE_RECURSE
  "CMakeFiles/nuttx_drivers_build"
  "nuttx/drivers/libdrivers.a"
  "nuttx/include/nuttx/config.h"
  "nuttx/include/nuttx/version.h"
  "nuttx/.config"
  "nuttx_olddefconfig.stamp"
  "nuttx_copy_config_dir.stamp"
  "nuttx_config_kconfig.stamp"
  "nuttx_copy.stamp"
  "apps_copy.stamp"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/nuttx_drivers_build.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
