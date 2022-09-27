PREFIX?=/usr
BIN?=$(PREFIX)/bin

PROGRAM_DIR := $(shell dirname $(realpath $(firstword $(MAKEFILE_LIST))))

CLANG := $(shell command -v clang++ 2>/dev/null)
GCC := $(shell command -v g++ 2>/dev/null)

default:
	@printf "targets:\n\tmake install\n\tmake uninstall\n\tmake purge\n"

install:
	cp src/config.def.h src/config.h
ifndef CLANG
	@printf "clang/clang++ not found!\nShould be prompted to use g++ instead...\n"
	@echo -n "Use g++ instead? [Y/n] "; \
	read _c; \
	if [ $${_c:-'N'} = 'y' ];then \
		g++ src/wifi.cpp -o src/wifi; \
	fi
else
	clang++ -Wall src/wifi.cpp -o src/wifi 
endif

	if [ -f $(BIN)/wifi ];then rm -f $(BIN)/wifi;fi
	ln -s $(PROGRAM_DIR)/src/wifi $(BIN)/wifi

uninstall:
	rm -f src/wifi
	rm -f $(BIN)/wifi

purge:
	rm -f $(BIN)/wifi
	cd ..;rm -rf wifi
