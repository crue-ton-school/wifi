PREFIX?=/usr
BIN?=$(PREFIX)/bin

default:
	@printf "targets:\n\tmake install\n\tmake uninstall\n\tmake purge\n"

install:
	clang++ -Wall wifi.cpp -o $(BIN)/wifi

uninstall:
	rm -f $(BIN)/wifi

purge:
	cd ..;rm -rf wifi
