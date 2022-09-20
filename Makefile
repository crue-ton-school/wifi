PREFIX?=/usr
BIN?=$(PREFIX)/bin

CLANG := $(shell command -v clang++ 2>/dev/null)
GCC := $(shell command -v g++ 2>/dev/null)

default:
	@printf "targets:\n\tmake install\n\tmake uninstall\n\tmake purge\n"

install:
ifndef CLANG
	@printf "clang/clang++ not found!\nShould be prompted to use g++ instead...\n"
	@echo -n "Use g++ instead? [Y/n] ";read _c;if [ $${_c:-'N'} = 'y' ];then g++ wifi.cpp -o $(BIN)/wifi;fi
else
	clang++ -Wall wifi.cpp -o $(BIN)/wifi 
endif
		

uninstall:
	rm -f $(BIN)/wifi

purge:
	cd ..;rm -rf wifi
