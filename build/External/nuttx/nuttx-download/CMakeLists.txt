cmake_minimum_required(VERSION 2.8.2)

project(nuttx-download NONE)

include(ExternalProject)

ExternalProject_Add(nuttx
  GIT_REPOSITORY    https://github.com/apache/incubator-nuttx.git
  GIT_TAG           master
  SOURCE_DIR        "/home/andressanchez/Escritorio/GIT/project_template/build/External/nuttx/nuttx"
  BINARY_DIR        ""
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(nuttx_tools
  GIT_REPOSITORY    https://bitbucket.org/nuttx/tools.git
  GIT_TAG           master
  SOURCE_DIR        "/home/andressanchez/Escritorio/GIT/project_template/build/External/nuttx/tools"
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

ExternalProject_Add(nuttx-apps
  GIT_REPOSITORY    https://github.com/apache/incubator-nuttx-apps.git
  GIT_TAG           master
  SOURCE_DIR        "/home/andressanchez/Escritorio/GIT/project_template/build/External/nuttx/apps"
  BINARY_DIR        ""
  CONFIGURE_COMMAND ""
  BUILD_COMMAND     ""
  INSTALL_COMMAND   ""
  TEST_COMMAND      ""
)

