#=============================================================================
# Nuttx
#

configure_file(${CMAKE_CURRENT_LIST_DIR}/CMakeLists.txt.in External/nuttx/nuttx-download/CMakeLists.txt)

execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE     result
  WORKING_DIRECTORY   ${BINARY_DIR}/External/nuttx/nuttx-download 
)
if(result)
  message(FATAL_ERROR "CMake step for nuttx failed: ${result}")
endif()

execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE     result
  WORKING_DIRECTORY   ${BINARY_DIR}/External/nuttx/nuttx-download 
)
if(result)
  message(FATAL_ERROR "Build step for nuttx failed: ${result}")
endif()



execute_process(
    COMMAND ./configure --prefix=/home/andressanchez/Escritorio/GIT/project_template/build/External/nuttx/tools-install
    WORKING_DIRECTORY   ${BINARY_DIR}/External/nuttx/tools/kconfig-frontends/
)
execute_process(
    COMMAND make  
    WORKING_DIRECTORY   ${BINARY_DIR}/External/nuttx/tools/kconfig-frontends/
)
execute_process(
    COMMAND make DESTDIR=/home/andressanchez/Escritorio/GIT/project_template/build/External/nuttx/tools-install install 
    WORKING_DIRECTORY   ${BINARY_DIR}/External/nuttx/tools/kconfig-frontends/
)
message(STATUS "ldconfig invoqued")
#execute_process(
    #COMMAND sudo -S ldconfig
    #WORKING_DIRECTORY   ${BINARY_DIR}/External/nuttx/tools/kconfig-frontends/
#)
