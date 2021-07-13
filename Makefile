# Help
# --------------------------------------------------------------------
# Don't be afraid of this makefile, it is just passing
# arguments to cmake to allow us to keep the wiki pages etc.
# that describe how to build the px4 firmware
# the same even when using cmake instead of make.
#
# Example usage:
#
# make _fmu-v2_default 			(builds)
# make _fmu-v2_default upload 	(builds and uploads)
# make _fmu-v2_default test 		(builds and tests)
#
# This tells cmake to build the nuttx px4_fmu-v2 default config in the
# directory build/px4_fmu-v2_default and then call make
# in that directory with the target upload.

# explicity set default build target
all: nucleo_h743zi #px4_sitl_default

# define a space character to be able to explicitly find it in strings
space := $(subst ,, )

define make_list
     $(shell cat .github/workflows/compile_${1}.yml | sed -E 's|[[:space:]]+(.*),|check_\1|g' | grep check_${2})
endef

# Parsing
# --------------------------------------------------------------------
# assume 1st argument passed is the main target, the
# rest are arguments to pass to the makefile generated
# by cmake in the subdirectory
FIRST_ARG := $(firstword $(MAKECMDGOALS))
ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))

# Get -j or --jobs argument as suggested in:
# https://stackoverflow.com/a/33616144/8548472
MAKE_PID := $(shell echo $$PPID)
j := $(shell ps T | sed -n 's|.*$(MAKE_PID).*$(MAKE).* \(-j\|--jobs\) *\([0-9][0-9]*\).*|\2|p')

# Default j for clang-tidy
j_clang_tidy := $(or $(j),4)

NINJA_BIN := ninja
ifndef NO_NINJA_BUILD
	NINJA_BUILD := $(shell $(NINJA_BIN) --version 2>/dev/null)

	ifndef NINJA_BUILD
		NINJA_BIN := ninja-build
		NINJA_BUILD := $(shell $(NINJA_BIN) --version 2>/dev/null)
	endif
endif

ifdef NINJA_BUILD
	QPRO_CMAKE_GENERATOR := Ninja
	QPRO_MAKE := $(NINJA_BIN)

	ifdef VERBOSE
		QPRO_MAKE_ARGS := -v
	else
		QPRO_MAKE_ARGS :=
	endif

	# Only override ninja default if -j is set.
	ifneq ($(j),)
		QPRO_MAKE_ARGS := $(QPRO_MAKE_ARGS) -j$(j)
	endif
else
	ifdef SYSTEMROOT
		# Windows
		QPRO_CMAKE_GENERATOR := "MSYS\ Makefiles"
	else
		QPRO_CMAKE_GENERATOR := "Unix\ Makefiles"
	endif

	# For non-ninja builds we default to -j4
	j := $(or $(j),4)
	QPRO_MAKE = $(MAKE)
	QPRO_MAKE_ARGS = -j$(j) --no-print-directory
endif

SRC_DIR := $(shell dirname "$(realpath $(lastword $(MAKEFILE_LIST)))")

# check if replay env variable is set & set build dir accordingly
ifdef replay
	BUILD_DIR_SUFFIX := _replay
else
	BUILD_DIR_SUFFIX :=
endif

# additional config parameters passed to cmake
ifdef EXTERNAL_MODULES_LOCATION
	CMAKE_ARGS += -DEXTERNAL_MODULES_LOCATION:STRING=$(EXTERNAL_MODULES_LOCATION)
endif

ifdef QPRO_CMAKE_BUILD_TYPE
	CMAKE_ARGS += -DCMAKE_BUILD_TYPE=${QPRO_CMAKE_BUILD_TYPE}
else

	# Address Sanitizer
	ifdef QPRO_ASAN
		CMAKE_ARGS += -DCMAKE_BUILD_TYPE=AddressSanitizer
	endif

	# Memory Sanitizer
	ifdef QPRO_MSAN
		CMAKE_ARGS += -DCMAKE_BUILD_TYPE=MemorySanitizer
	endif

	# Thread Sanitizer
	ifdef QPRO_TSAN
		CMAKE_ARGS += -DCMAKE_BUILD_TYPE=ThreadSanitizer
	endif

	# Undefined Behavior Sanitizer
	ifdef QPRO_UBSAN
		CMAKE_ARGS += -DCMAKE_BUILD_TYPE=UndefinedBehaviorSanitizer
	endif

endif

# Pick up specific Python path if set
ifdef PYTHON_EXECUTABLE
	CMAKE_ARGS += -DPYTHON_EXECUTABLE=${PYTHON_EXECUTABLE}
endif

# Functions
# --------------------------------------------------------------------
# describe how to build a cmake config
define cmake-build
	@$(eval BUILD_DIR = "$(SRC_DIR)/build/$(1)")
	@# check if the desired cmake configuration matches the cache then CMAKE_CACHE_CHECK stays empty
	@$(call cmake-cache-check)
	@# make sure to start from scratch when switching from GNU Make to Ninja
	@if [ $(QPRO_CMAKE_GENERATOR) = "Ninja" ] && [ -e $(BUILD_DIR)/Makefile ]; then rm -rf $(BUILD_DIR); fi
	@# make sure to start from scratch if ninja build file is missing
	@if [ $(QPRO_CMAKE_GENERATOR) = "Ninja" ] && [ ! -f $(BUILD_DIR)/build.ninja ]; then rm -rf $(BUILD_DIR); fi
	@# only excplicitly configure the first build, if cache file already exists the makefile will rerun cmake automatically if necessary
	@if [ ! -e $(BUILD_DIR)/CMakeCache.txt ] || [ $(CMAKE_CACHE_CHECK) ]; then \
		mkdir -p $(BUILD_DIR) \
		&& cd $(BUILD_DIR) \
		&& cmake "$(SRC_DIR)" -G"$(QPRO_CMAKE_GENERATOR)" $(CMAKE_ARGS) \
		|| (rm -rf $(BUILD_DIR)); \
	fi
	@# run the build for the specified target
	@cmake --build $(BUILD_DIR) -- $(QPRO_MAKE_ARGS) $(ARGS)
endef

# check if the options we want to build with in CMAKE_ARGS match the ones which are already configured in the cache inside BUILD_DIR
define cmake-cache-check
	@# change to build folder which fails if it doesn't exist and CACHED_CMAKE_OPTIONS stays empty
	@# fetch all previously configured and cached options from the build folder and transform them into the OPTION=VALUE format without type (e.g. :BOOL)
	@$(eval CACHED_CMAKE_OPTIONS = $(shell cd $(BUILD_DIR) 2>/dev/null && cmake -L 2>/dev/null | sed -n 's|\([^[:blank:]]*\):[^[:blank:]]*\(=[^[:blank:]]*\)|\1\2|gp' ))
	@# transform the options in CMAKE_ARGS into the OPTION=VALUE format without -D
	@$(eval DESIRED_CMAKE_OPTIONS = $(shell echo $(CMAKE_ARGS) | sed -n 's|-D\([^[:blank:]]*=[^[:blank:]]*\)|\1|gp' ))
	@# find each currently desired option in the already cached ones making sure the complete configured string value is the same
	@$(eval VERIFIED_CMAKE_OPTIONS = $(foreach option,$(DESIRED_CMAKE_OPTIONS),$(strip $(findstring $(option)$(space),$(CACHED_CMAKE_OPTIONS)))))
	@# if the complete list of desired options is found in the list of verified options we don't need to reconfigure and CMAKE_CACHE_CHECK stays empty
	@$(eval CMAKE_CACHE_CHECK = $(if $(findstring $(DESIRED_CMAKE_OPTIONS),$(VERIFIED_CMAKE_OPTIONS)),,y))
endef

COLOR_BLUE = \033[0;94m
NO_COLOR   = \033[m

define colorecho
+@echo -e '${COLOR_BLUE}${1} ${NO_COLOR}'
endef

# Get a list of all config targets boards/*/*.cmake
ALL_CONFIG_TARGETS := $(shell find boards -maxdepth 3 -mindepth 3 ! -name '*common*' ! -name '*sdflight*' -name '*.cmake' -print | sed -e 's|boards\/||' | sed -e 's|\.cmake||' | sed -e 's|\/|_|g' | sort)

# ADD CONFIGS HERE
# --------------------------------------------------------------------
#  Do not put any spaces between function arguments.

# All targets.
$(ALL_CONFIG_TARGETS):
	@$(eval QPRO_CONFIG = $@)
	@$(eval CMAKE_ARGS += -DCONFIG=$(QPRO_CONFIG))
	@$(call cmake-build,$(QPRO_CONFIG)$(BUILD_DIR_SUFFIX))

# Filter for only default targets to allow omiting the "_default" postfix
CONFIG_TARGETS_DEFAULT := $(patsubst %_default,%,$(filter %_default,$(ALL_CONFIG_TARGETS)))
$(CONFIG_TARGETS_DEFAULT):
	@$(eval QPRO_CONFIG = $@_default)
	@$(eval CMAKE_ARGS += -DCONFIG=$(QPRO_CONFIG))
	@$(call cmake-build,$(QPRO_CONFIG)$(BUILD_DIR_SUFFIX))

all_config_targets: $(ALL_CONFIG_TARGETS)
all_default_targets: $(CONFIG_TARGETS_DEFAULT)

# board reorganization deprecation warnings (2018-11-22)
define deprecation_warning
	$(warning $(1) has been deprecated and will be removed, please use $(2)!)
endef

# All targets with just dependencies but no recipe must either be marked as phony (or have the special @: as recipe).
.PHONY: all all_config_targets all_default_targets

.PHONY: tests tests_coverage 

tests:
	$(eval CMAKE_ARGS += -DCONFIG=host_posix_test)
	$(eval CMAKE_ARGS += -DTESTFILTER=$(TESTFILTER))
	$(eval ARGS += test_results)
	$(eval ASAN_OPTIONS += color=always:check_initialization_order=1:detect_stack_use_after_return=1)
	$(eval UBSAN_OPTIONS += color=always)
	$(call cmake-build,host_posix_test)

tests_coverage:
	@$(MAKE) clean
	@$(MAKE) --no-print-directory tests QPRO_CMAKE_BUILD_TYPE=Coverage
	@mkdir -p coverage
	@lcov --directory build/host_posix_test --base-directory build/host_posix_test --gcov-tool gcov --capture -o coverage/lcov.info


# Cleanup
# --------------------------------------------------------------------
.PHONY: clean submodulesclean submodulesupdate distclean

clean:
	@[ ! -d "$(SRC_DIR)/build" ] || find "$(SRC_DIR)/build" -mindepth 1 -maxdepth 1 -type d -exec sh -c "echo {}; cmake --build {} -- clean || rm -rf {}" \; # use generated build system to clean, wipe build directory if it fails
	@git submodule foreach git clean -dX --force # some submodules generate build artifacts in source

submodulesclean:
	@git submodule foreach --quiet --recursive git clean -ff -x -d
	@git submodule update --quiet --init --recursive --force || true
	@git submodule sync --recursive
	@git submodule update --init --recursive --force --jobs 4

submodulesupdate:
	@git submodule update --quiet --init --recursive --jobs 4 || true
	@git submodule sync --recursive
	@git submodule update --init --recursive --jobs 4


distclean: 
	@git submodule deinit --force $(SRC_DIR)
	@rm -rf "$(SRC_DIR)/build"
	@git clean --force -X "$(SRC_DIR)/msg/" "$(SRC_DIR)/platforms/" "$(SRC_DIR)/posix-configs/" "$(SRC_DIR)/ROMFS/" "$(SRC_DIR)/src/" "$(SRC_DIR)/test/" "$(SRC_DIR)/Tools/"



# Help / Error
# --------------------------------------------------------------------

# All other targets are handled by QPRO_MAKE. Add a rule here to avoid printing an error.
%:
	$(if $(filter $(FIRST_ARG),$@), \
		$(error "Make target $@ not found. It either does not exist or $@ cannot be the first argument. Use '$(MAKE) help|list_config_targets' to get a list of all possible [configuration] targets."),@#)

# Print a list of non-config targets (based on http://stackoverflow.com/a/26339924/1487069)
# help:
# 	@echo "Usage: $(MAKE) <target>"
# 	@echo "Where <target> is one of:"
# 	@$(MAKE) -pRrq -f $(lastword $(MAKEFILE_LIST)) : 2>/dev/null 
# 	@echo
# 	@echo "Or, $(MAKE) <config_target> [<make_target(s)>]"
# 	@echo "Use '$(MAKE) list_config_targets' for a list of configuration targets."

# Print a list of all config targets.
list_config_targets:
	@for targ in $(patsubst %_default,%[_default],$(ALL_CONFIG_TARGETS)); do echo $$targ; done

