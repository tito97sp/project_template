file(REMOVE_RECURSE
  "CMakeFiles/nuttx_builtin_list_target"
  "apps/builtin/registry/custom_hello_main.bdat"
  "apps/builtin/registry/custom_hello_main.pdat"
  "apps/builtin/registry/custom_uorb_main.bdat"
  "apps/builtin/registry/custom_uorb_main.pdat"
  "builtins_clean.stamp"
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
  include(CMakeFiles/nuttx_builtin_list_target.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
