CXXFLAGS += -std=gnu++17
LINK.o := $(LINK.cc)

ko-term: ko.o unicode.o

ko.o: ko.hh
unicode.o: unicode.hh
ko-term.o: ko.hh unicode.hh

clean:
	rm -f *.o ko-term
.PHONY: clean
