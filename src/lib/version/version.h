/****************************************************************************
 *
 *   Copyright (c) 2013-2019 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name PX4 nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/**
 * @file version.h
 *
 * Tools for system version detection.
 *
 * @author Anton Babushkin <anton.babushkin@me.com>
 * @author Beat Küng <beat-kueng@gmx.net>
 */

#pragma once

#include <stdint.h>

__BEGIN_DECLS

/**
 * get the board name as string (including the version if there are multiple)
 */
static inline const char *board_name(void)
{
	return BOARD_NAME;
}

/**
 * get the board sub type
 */
static inline const char *board_sub_type(void)
{
	return board_get_hw_type_name();
}

/**
 * get the board HW version
 */
static inline int board_hw_version(void)
{
	return board_get_hw_version();
}

/**
 * get the board HW revision
 */
static inline int board_hw_revision(void)
{
	return board_get_hw_revision();
}

/**
 * get the build URI (used for crash logging)
 */
const char *build_uri(void);

/**
 * Convert a version tag string to a number
 * @param tag version tag in one of the following forms:
 *            - vendor: v1.4.0-0.2.0
 *            - dev: v1.4.0-rc3-7-g7e282f57
 *            - rc: v1.4.0-rc4
 *            - beta: v1.4.0-beta1
 *            - release: v1.4.0
 *            - linux: 7.9.3
 * @return version in the form 0xAABBCCTT (AA: Major, BB: Minor, CC: Patch, TT Type @see FIRMWARE_TYPE)
 */
__EXPORT uint32_t version_tag_to_number(const char *tag);

/**
 * get the PX4 Firmware version
 * @return version in the form 0xAABBCCTT (AA: Major, BB: Minor, CC: Patch, TT Type @see FIRMWARE_TYPE)
 */
__EXPORT uint32_t firmware_version(void);

/**
 * Convert a version tag string to a vendor version number
 * @param tag version tag in one of the following forms:
 *            - vendor: v1.4.0-0.2.0
 *            - dev: v1.4.0-rc3-7-g7e282f57
 *            - rc: v1.4.0-rc4
 *            - beta: v1.4.0-beta1
 *            - release: v1.4.0
 *            - linux: 7.9.3
 * @return version in the form 0xAABBCCTT (AA: Major, BB: Minor, CC: Patch, TT Type @see FIRMWARE_TYPE)
 */
__EXPORT uint32_t version_tag_to_vendor_version_number(const char *tag);

/**
 * get the PX4 Firmware vendor version
 * @return version in the form 0xAABBCCTT (AA: Major, BB: Minor, CC: Patch, TT Type @see FIRMWARE_TYPE)
 */
__EXPORT uint32_t firmware_vendor_version(void);

/**
 * get the board version (last 8 bytes should be silicon ID, if any)
 */
__EXPORT uint32_t board_version(void);

/**
 * operating system version
 * @return version in the form 0xAABBCCTT (AA: Major, BB: Minor, CC: Patch, TT Type @see FIRMWARE_TYPE)
 */
__EXPORT uint32_t os_version(void);

/**
 * Operating system version as human readable string (git tag)
 * @return string or NULL if not defined
 */
__EXPORT const char *os_version_string(void);

/**
 * name of the operating system
 * @return human readable string
 */
__EXPORT const char *os_name(void);

/**
 * Toolchain name used to compile PX4
 */
__EXPORT const char *toolchain_name(void);

/**
 * Toolchain version used to compile PX4 (no particular format)
 */
__EXPORT const char *toolchain_version(void);

/**
 * Firmware version as human readable string (git tag)
 */
__EXPORT const char *firmware_version_string(void);

/**
 * get the git branch name (can be empty, for example if HEAD points to a tag)
 */
__EXPORT const char *firmware_git_branch(void);

/**
 * Firmware version in binary form (first part of the git tag)
 */
__EXPORT uint64_t firmware_version_binary(void);

/**
 * ECL lib version as human readable string (git tag)
 */
__EXPORT const char *ecl_lib_version_string(void);

/**
 * MAVLink lib version in binary form (first part of the git tag)
 */
__EXPORT uint64_t mavlink_lib_version_binary(void);

/**
 * Operating system version in binary form (first part of the git tag)
 * @return this is not available on all OSes and can return 0
 */
__EXPORT uint64_t os_version_binary(void);

__END_DECLS

