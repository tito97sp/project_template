file(REMOVE_RECURSE
  "nsh_romfsimg.c"
  "romfs.img"
  "romfs.txt"
  "romfs_pruned.stamp"
  "romfs_copy.stamp"
  "romfs_extras.stamp"
  "romfs_extract.stamp"
  "../etc/init.d/rc.board_defaults"
  "rc.board_defaults.stamp"
  "../romfs_files.tar"
  "CMakeFiles/romfs.dir/nsh_romfsimg.c.obj"
  "libromfs.pdb"
  "libromfs.a"
)

# Per-language clean rules from dependency scanning.
foreach(lang C)
  include(CMakeFiles/romfs.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
