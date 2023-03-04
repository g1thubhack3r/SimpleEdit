CFLAGS=--std=c++11 $(OPTFLAGS)
PREFIX?=/usr/local

all: build SimpleEdit

build:
	@mkdir -p bin

SimpleEdit:
	cc $(CFLAGS) src/SimpleEdit.cpp -o bin/SimpleEdit

install: all
	install -d $(DISTDIR)/$(PREFIX)/bin/
	install bin/SimpleEdit $(DISTDIR)/$(PREFIX)/bin/

clean:
	rm -rf bin
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`



