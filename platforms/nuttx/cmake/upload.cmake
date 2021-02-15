
find_program(OPENOCD openocd)
if(NOT OPENOCD)
    message(FATAL "OpenOCD not found.")
else()
    #check board and configure uploader.
    if(CONFIG_ARCH_CHIP_STM32H743ZI)
            set(OPENOCD_INTERFACE   "stlink-v2.cfg")
            set(OPENOCD_TARGET      "stm32h7x.cfg")
            set(OPENOCD_FLASH_ADD   "0x08000000")
    
    else()
        message(FATAL "No OpenOCD configuration for this board.")
    endif()


    if(${CMAKE_HOST_SYSTEM_NAME} STREQUAL "Linux")
        add_custom_target(${BOARD}_server
        COMMAND openocd -f interface/${OPENOCD_INTERFACE} -f target/${OPENOCD_TARGET}
        WORKING_DIRECTORY ${BINARY_DIR}
        USES_TERMINAL
        )
        
        add_custom_target(${BOARD}_upload
        COMMAND openocd -f interface/${OPENOCD_INTERFACE} -f target/${OPENOCD_TARGET} -c init -c "reset halt" -c "flash write_image erase ${BOARD}.bin ${OPENOCD_FLASH_ADD}"
        WORKING_DIRECTORY ${BINARY_DIR}
        DEPENDS 
            ${BINARY_DIR}/${BOARD}.bin
        USES_TERMINAL
        )

    endif()
endif()