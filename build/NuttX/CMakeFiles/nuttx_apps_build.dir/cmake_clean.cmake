file(REMOVE_RECURSE
  "CMakeFiles/nuttx_apps_build"
  "apps/libapps.a"
  "apps/builtin/registry/custom_hello_main.bdat"
  "apps/builtin/registry/custom_hello_main.pdat"
  "apps/builtin/registry/custom_uorb_main.bdat"
  "apps/builtin/registry/custom_uorb_main.pdat"
  "apps/builtin/registry/custom_template_module_main.bdat"
  "apps/builtin/registry/custom_template_module_main.pdat"
  "nuttx/include/nuttx/config.h"
  "nuttx/include/nuttx/version.h"
  "builtins_clean.stamp"
  "nuttx/.config"
  "nuttx_olddefconfig.stamp"
  "nuttx_copy_config_dir.stamp"
  "nuttx_config_kconfig.stamp"
  "nuttx_copy.stamp"
  "apps_copy.stamp"
)

# Per-language clean rules from dependency scanning.
foreach(lang )
  include(CMakeFiles/nuttx_apps_build.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
