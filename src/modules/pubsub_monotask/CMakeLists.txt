## This cmakelist.txt file was generated from
## the UAV Toolbox Support Package for PX4 Autopilots

add_definitions(
-DMODEL=pubsub_monotask -DNUMST=3 -DNCSTATES=0 -DHAVESTDIO -DMODEL_HAS_DYNAMICALLY_LOADED_SFCNS=0 -DCLASSIC_INTERFACE=0 -DALLOCATIONFCN=0 -DTID01EQ=0 -DTERMFCN=1 -DONESTEPFCN=1 -DMAT_FILE=0 -DMULTI_INSTANCE_CODE=0 -DINTEGER_CODE=0 -DMT=1 )

add_module(
   MODULE pubsub_monotask
   MAIN pubsub_monotask
   STACK_MAIN 2000
   SRCS
      MW_uORB_Write.cpp
      MW_uORB_Read.cpp
      pubsub_monotask.cpp
      rtGetInf.cpp
      rtGetNaN.cpp
      rt_main.cpp
      rt_nonfinite.cpp
      MW_uORB_Write.h
      MW_uORB_Read.h
      rtGetInf.h
      rtGetNaN.h
      rt_nonfinite.h
      pubsub_monotask.h
      pubsub_monotask_private.h
      pubsub_monotask_types.h
      rtmodel.h
      rtwtypes.h
      MW_uORB_busstruct_conversion.h
   COMPILE_FLAGS
      -fpermissive
      -Wno-narrowing
      -Wno-float-equal
   INCLUDES
      ${PX4_SOURCE_DIR}/src/modules/mavlink
      ${PX4_SOURCE_DIR}/mavlink/include/mavlink
      /home/asanchez
      /home/asanchez/Documents/MATLAB/SupportPackages/R2020a/toolbox/target/supportpackages/nuttx/include
      /home/asanchez/pubsub_monotask_nuttx
      /usr/local/MATLAB/R2020a/extern/include
      /usr/local/MATLAB/R2020a/simulink/include
      /usr/local/MATLAB/R2020a/rtw/c/src
      /usr/local/MATLAB/R2020a/rtw/c/src/ext_mode/common
      /usr/local/MATLAB/R2020a/rtw/c/ert
)

#get_target_property(SL_pubsub_monotask_COMPILE_FLAGS modules__nuttx_simulink_pubsub_monotask COMPILE_OPTIONS)
#list(REMOVE_ITEM SL_pubsub_monotask_COMPILE_FLAGS -Werror)
#set_target_properties(modules__nuttx_simulink_pubsub_monotask PROPERTIES COMPILE_OPTIONS "${SL_pubsub_monotask_COMPILE_FLAGS}")
