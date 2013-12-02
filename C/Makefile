CC=clang
CFLAGS=-Wall -std=gnu99 -Wextra -pedantic -g
EXENAME=BogoSort
CFILES=main.c BogoSortAnalysis.c BogoSort.c
COBJFILES=$(CFILES:c=o)
EXECUTABLES=$(EXENAME)

all: $(EXENAME)

$(EXENAME): $(COBJFILES)

install:
	cp $(EXECUTABLES) /usr/local/bin/

clean:
	rm -rf $(COBJFILES)

realclean purge: clean
	rm -rf $(EXECUTABLES)
