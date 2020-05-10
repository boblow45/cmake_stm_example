.PHONY: clean cmake-output
.DEFAULT_GOAL := help
SERVER_LOC = 'https://artifactory.analog.com/artifactory/api/pypi/cspt-knowledgebase-pypi/simple'

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
	@python -c "$$PRINT_HELP_PYSCRIPT" < $(MAKEFILE_LIST)

clean:	## remove all generated file
	rm -rf build

cmake-output: 	## run cmake with the requrired parameters
	cmake -S. -Bbuild
	$(MAKE) build

flash:
	cp ./build/stm_drone.bin ./stm_drone.bin
	JLink -device STM32F767ZI -if SWD -speed 4000 -autoconnect 1 -CommanderScript ./j-link/flash.jlink