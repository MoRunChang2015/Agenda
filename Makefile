#
# TODO: Compiler the whole project
#

CC := g++
# CC=clang++ --analyze

SRCDIR := src
BUILDDIR := build
TARGET := bin/Agenda

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -g -w -std=c++11
INC := -I include
STATIC_ANALYZER := oclint

$(TARGET) : $(OBJECTS)
	@echo " Linking "
	@mkdir -p bin
	@echo " $(CC) $^ -o $(TARGET) $(LIB) $(LINKER)"; $(CC) $^ -o $(TARGET)

$(BUILDDIR)/%.o : $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(BUILDDIR)
	@echo " $(CC) $(CFLAGS) $(INC) $(LIB) -c -o $@ $<"; $(CC) $(CFLAGS) $(INC) -c -o $@ $<

static-analyze:
	$(STATIC_ANALYZER) $(SOURCES) -- -c $(CFLAGS) $(INC) $(LIB)

clean:
	@echo " Cleaning... "
	@echo " rm -rf $(BUILDDIR) $(TARGET)"; rm -rf $(BUILDDIR) $(TARGET)

.PHONY: clean
