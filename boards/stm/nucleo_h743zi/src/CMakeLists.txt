# ############################################################################
# #
# #   Copyright (c) 2016 PX4 Development Team. All rights reserved.
# #
# # Redistribution and use in source and binary forms, with or without
# # modification, are permitted provided that the following conditions
# # are met:
# #
# # 1. Redistributions of source code must retain the above copyright
# #    notice, this list of conditions and the following disclaimer.
# # 2. Redistributions in binary form must reproduce the above copyright
# #    notice, this list of conditions and the following disclaimer in
# #    the documentation and/or other materials provided with the
# #    distribution.
# # 3. Neither the name PX4 nor the names of its contributors may be
# #    used to endorse or promote products derived from this software
# #    without specific prior written permission.
# #
# # THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# # "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# # LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# # FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# # COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# # INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# # BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
# # OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
# # AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# # LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# # ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# # POSSIBILITY OF SUCH DAMAGE.
# #
# ############################################################################
if("${BOARD_LABEL}" STREQUAL  "bootloader")
	add_library(drivers_board
		bootloader_main.c
		usb.c
	)
	target_link_libraries(drivers_board
		PRIVATE
			nuttx_arch # sdio
			nuttx_drivers # sdio
			bootloader
	)
	target_include_directories(drivers_board PRIVATE ${SOURCE_DIR}/platforms/nuttx/src/bootloader)

else()
	add_custom_library(drivers_board
		stm32_appinitialize.c
		stm32_boot.c
		stm32_bringup.c

		stm32_autoleds.c
		#stm32_buttons.c
		#stm32_gpio.c
		#stm32_usb.c
		#stm32_userleds.c
		#stm32_adc.c
		#stm32_lsm6dsl.c
		#stm32_lsm9ds1.c
		#stm32_lsm303agr.c
		#stm32_nrf24l01.c
		#stm32_pca9635.c
		#stm32_pwm.c
		stm32_romfs_initialize.c
		#stm32_spi.c
		#stm32_ssd1306.c
		#stm32_uid.c
		)
	
	#add_dependencies(drivers_board arch_board_hw_info)

	target_link_libraries(drivers_board
	 	PRIVATE
	# 		arch_spi
	# 		arch_board_hw_info
	# 		drivers__led # drv_led_start
	 		nuttx_arch # sdio
	 		nuttx_drivers # sdio
	# 		px4_layer
     )
    
endif()
