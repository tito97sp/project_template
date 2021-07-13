## This cmakelist.txt file was generated from
## the UAV Toolbox Support Package for PX4 Autopilots

add_definitions(
-DMODEL=Subsystem -DNUMST=1 -DNCSTATES=0 -DHAVESTDIO -DMODEL_HAS_DYNAMICALLY_LOADED_SFCNS=0 -DCLASSIC_INTERFACE=0 -DALLOCATIONFCN=0 -DTID01EQ=0 -DTERMFCN=1 -DONESTEPFCN=1 -DMAT_FILE=0 -DMULTI_INSTANCE_CODE=0 -DINTEGER_CODE=0 -DMT=0 )

add_module(
   MODULE Subsystem
   MAIN Subsystem
   STACK_MAIN 2000
   SRCS
      Subsystem.cpp
      ert_main.cpp
      rt_main.cpp
      Subsystem.h
      Subsystem_private.h
      Subsystem_types.h
      ert_main.h
      rtmodel.h
      rtwtypes.h
      MW_uORB_busstruct_conversion.h
      ext_work.h
      rt_logging.h
   COMPILE_FLAGS
      -fpermissive
      -Wno-narrowing
      -Wno-float-equal
   INCLUDES
      ${PX4_SOURCE_DIR}/src/modules/mavlink
      ${PX4_SOURCE_DIR}/mavlink/include/mavlink
      /home/asanchez/GIT/project_template/src/modules/simulink_models/pil
      /home/asanchez/GIT/project_template/src/modules/simulink_models/pil/Subsystem_nuttx
      /usr/local/MATLAB/R2020a/extern/include
      /usr/local/MATLAB/R2020a/simulink/include
      /usr/local/MATLAB/R2020a/rtw/c/src
      /usr/local/MATLAB/R2020a/rtw/c/src/ext_mode/common
      /usr/local/MATLAB/R2020a/rtw/c/ert
)

#get_target_property(SL_Subsystem_COMPILE_FLAGS modules__nuttx_simulink_Subsystem COMPILE_OPTIONS)
#list(REMOVE_ITEM SL_Subsystem_COMPILE_FLAGS -Werror)
#set_target_properties(modules__nuttx_simulink_Subsystem PROPERTIES COMPILE_OPTIONS "${SL_Subsystem_COMPILE_FLAGS}")
