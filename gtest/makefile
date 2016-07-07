CC = g++
CCFLAG = -lgtest -lpthread -lgtest_main -std=c++11
INC = -I ../include
SRCDIR = ../src
BUILDDIR = build
TESTSRCDIR = src
BINDIR = bin

DateTest: dir $(BUILDDIR)/Date.o
	$(CC) $(BUILDDIR)/Date.o $(TESTSRCDIR)/DateTest.cpp $(CCFLAG) -o $(BINDIR)/DateTest
$(BUILDDIR)/Date.o: $(SRCDIR)/Date.cpp
	$(CC) $(SRCDIR)/Date.cpp $(INC) -std=c++11 -c -o $(BUILDDIR)/Date.o
dir:
	mkdir -p $(BINDIR)
	mkdir -p $(BUILDDIR)
clean:
	rm *~ $(BUILDDIR)/*
