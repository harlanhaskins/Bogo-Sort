CC=clang
CFLAGS=-Wall -std=gnu99 -Wextra -pedantic -g
EXENAME=BogoSort
CFILES=main.c BogoSortAnalysis.c BogoSort.c BSArray.c
COUTPUT=BogoSortResults/
COBJFILES=$(CFILES:c=o)
CASSEMBLYFILES=$(CFILES:c=s)
EXECUTABLES=$(EXENAME)

all: $(EXENAME)

$(EXENAME): $(COBJFILES)

install:
	cp $(EXECUTABLES) /usr/local/bin/

clean:
	rm -rf $(COBJFILES)
	rm -rf $(CASSEMBLYFILES)

realclean purge: clean
	rm -rf $(EXECUTABLES)
	rm -rf $(COUTPUT)
