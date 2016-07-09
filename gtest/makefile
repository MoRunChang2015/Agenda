CC = g++
CCFLAG = -lgtest -lpthread -lgtest_main -std=c++11
INC = -I ../include
SRCDIR = ../src
BUILDDIR = ../build
TESTSRCDIR = src
TESTBUILDDIR = build
TESTBINDIR = bin
SOURCES = $(shell find $(TESTSRCDIR) -type f -name *.cpp)
TARGET =$(notdir $(patsubst %.cpp, %, $(SOURCES)))
TESTOBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))

all: bin/DateTest bin/UserTest bin/MeetingTest bin/StorageTest

bin/DateTest: $(TESTBUILDDIR)/DateTest.o $(BUILDDIR)/Date.o
	$(CC) $^ $(CCFLAG) -o $@
$(TESTBUILDDIR)/DateTest.o: $(TESTSRCDIR)/DateTest.cpp
	$(CC) $^ $(INC) -std=c++11 -c -o $@

bin/UserTest: $(TESTBUILDDIR)/UserTest.o $(BUILDDIR)/User.o
	$(CC) $^ $(CCFLAG) -o $@
$(TESTBUILDDIR)/UserTest.o: $(TESTSRCDIR)/UserTest.cpp
	$(CC) $^ $(INC) -std=c++11 -c -o $@

bin/MeetingTest: $(TESTBUILDDIR)/MeetingTest.o $(BUILDDIR)/Meeting.o $(BUILDDIR)/Date.o
	$(CC) $^ $(CCFLAG) -o $@
$(TESTBUILDDIR)/MeetingTest.o: $(TESTSRCDIR)/MeetingTest.cpp
	$(CC) $^ $(INC) -std=c++11 -c -o $@

bin/StorageTest: $(TESTBUILDDIR)/StorageTest.o $(BUILDDIR)/Storage.o $(BUILDDIR)/Meeting.o $(BUILDDIR)/User.o $(BUILDDIR)/Date.o
	$(CC) $^ $(CCFLAG) -o $@
$(TESTBUILDDIR)/StorageTest.o: $(TESTSRCDIR)/StorageTest.cpp
	$(CC) $^ $(INC) -std=c++11 -c -o $@

dir:
	mkdir -p $(TESTBINDIR)
	mkdir -p $(TESTBUILDDIR)
clean:
	rm src/*~ $(TESTBUILDDIR)/*
