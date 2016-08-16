CC = g++
CCFLAG = -lgtest -lpthread -lgtest_main -std=c++11 -g
CCTESTFLAG = -std=c++11 -g -c
INC = -I ../include
SRCDIR = ../src
BUILDDIR = ../build
TESTSRCDIR = src
TESTBUILDDIR = build
TESTBINDIR = bin
SOURCES = $(shell find $(TESTSRCDIR) -type f -name *.cpp)
TARGET =$(notdir $(patsubst %.cpp, %, $(SOURCES)))
TESTOBJECTS = $(patsubst %.cpp, %.o, $(SOURCES))

all: dir bin/DateTest bin/UserTest bin/MeetingTest bin/StorageTest bin/AgendaServiceTest

bin/DateTest: $(TESTBUILDDIR)/DateTest.o $(BUILDDIR)/Date.o
	$(CC) $^ $(CCFLAG) -o $@
$(TESTBUILDDIR)/DateTest.o: $(TESTSRCDIR)/DateTest.cpp
	$(CC) $^ $(INC) $(CCTESTFLAG) -o $@

bin/UserTest: $(TESTBUILDDIR)/UserTest.o $(BUILDDIR)/User.o
	$(CC) $^ $(CCFLAG) -o $@
$(TESTBUILDDIR)/UserTest.o: $(TESTSRCDIR)/UserTest.cpp
	$(CC) $^ $(INC) $(CCTESTFLAG) -o $@

bin/MeetingTest: $(TESTBUILDDIR)/MeetingTest.o $(BUILDDIR)/Meeting.o $(BUILDDIR)/Date.o
	$(CC) $^ $(CCFLAG) -o $@
$(TESTBUILDDIR)/MeetingTest.o: $(TESTSRCDIR)/MeetingTest.cpp
	$(CC) $^ $(INC) $(CCTESTFLAG) -o $@

bin/StorageTest: $(TESTBUILDDIR)/StorageTest.o $(BUILDDIR)/Storage.o $(BUILDDIR)/Meeting.o $(BUILDDIR)/User.o $(BUILDDIR)/Date.o $(TESTBUILDDIR)/utility.o
	$(CC) $^ $(CCFLAG) -o $@
$(TESTBUILDDIR)/StorageTest.o: $(TESTSRCDIR)/StorageTest.cpp
	$(CC) $^ $(INC) $(CCTESTFLAG) -o $@

$(TESTBUILDDIR)/utility.o: $(TESTSRCDIR)/utility.cpp
	$(CC) $^ $(INC) $(CCTESTFLAG) -o $@

bin/AgendaServiceTest: $(TESTBUILDDIR)/AgendaServiceTest.o $(BUILDDIR)/AgendaService.o $(BUILDDIR)/Storage.o $(BUILDDIR)/Meeting.o $(BUILDDIR)/User.o $(BUILDDIR)/Date.o $(TESTBUILDDIR)/utility.o
	$(CC) $^ $(CCFLAG) -o $@
$(TESTBUILDDIR)/AgendaServiceTest.o: $(TESTSRCDIR)/AgendaServiceTest.cpp
	$(CC) $^ $(INC) $(CCTESTFLAG) -o $@

$(BUILDDIR)/%.o:
	cd ../ && make

dir:
	mkdir -p $(TESTBINDIR)
	mkdir -p $(TESTBUILDDIR)

runAll:
	@echo " Testing AgendaService "; bin/AgendaServiceTest
	@echo " Testing Date ";bin/DateTest
	@echo " Testing Meeting ";bin/MeetingTest
	@echo " Testing Storage ";bin/StorageTest
	@echo " Testing User ";bin/UserTest

clean:
	rm -rf src/*~ $(TESTBUILDDIR)/*


result: build/tinyxml2.o
	g++ test/testXML.cpp src/parseXML.cpp build/tinyxml2.o  -I src/ -std=c++11 -g -o bin/testXML
build/tinyxml2.o:src/tinyxml2.cpp src/tinyxml2.h
	g++ $< -I src/ -c -o $@
