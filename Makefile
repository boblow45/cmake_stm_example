.PHONY: cmake_target cmake_host clean test build flash
.DEFAULT_GOAL := help
SERVER_LOC = ''

BUILD_DIR_HOST         ?= build
BUILD_DIR_TARGET       ?= build_target

define BROWSER_PYSCRIPT
import os, webbrowser, sys

try:
	from urllib import pathname2url
except:
	from urllib.request import pathname2url

webbrowser.open("file://" + pathname2url(os.path.abspath(sys.argv[1])))
endef
export BROWSER_PYSCRIPT

define PRINT_HELP_PYSCRIPT
import re, sys

for line in sys.stdin:
	match = re.match(r'^([a-zA-Z_-]+):.*?## (.*)$$', line)
	if match:
		target, help = match.groups()
		print("%-20s %s" % (target, help))
endef
export PRINT_HELP_PYSCRIPT

BROWSER := python -c "$$BROWSER_PYSCRIPT"

help:
	@python3 -c "$$PRINT_HELP_PYSCRIPT" < $(MAKEFILE_LIST)

clean: ## Remove all cmake builds 
	rm -rf $(BUILD_DIR_HOST)
	rm -rf $(BUILD_DIR_TARGET)
.PHONY: clean

cmake_target: 	## Create crosscompile build scripts
	mkdir -p $(BUILD_DIR_TARGET)
	cd $(BUILD_DIR_TARGET) && cmake .. -DCMAKE_TOOLCHAIN_FILE=./cmake_arm_none_eabi.cmake
.PHONY: cmake_target

cmake_host:	## Create build scripts for host machine
	mkdir -p $(BUILD_DIR_HOST)
	cd $(BUILD_DIR_HOST) && cmake ..
.PHONY: cmake_host

test: cmake_host
	cd $(BUILD_DIR_HOST) && make && ctest
.PHONY: test

build: cmake_target
	cd $(BUILD_DIR_TARGET) && make
.PHONY: build

flash: build
	cd $(BUILD_DIR_TARGET) && make flash
.PHONY: flash