# Decide about the main compiler
CC := g++

# Set the directories
BUILDDIR := build
SRCDIR := src
INCDIR := include
TARGET := bin/plot

# Set flags
CFLAGS := -I./$(INCDIR) `root-config --cflags`
LIBS := `root-config --libs`
MISCFLAGS := -fdiagnostics-color=always
DEBUGFLAGS := -O0 -g2

SOURCES := $(shell find $(SRCDIR) -type f -name *.cxx)
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.cxx=.o))

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "   Linking..."
	@mkdir -p bin
	@echo "   $(CC) $^ -o $(TARGET) $(LIBS)"; $(CC) $^ -o $(TARGET) $(LIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.cxx
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(BUILDDIR)/Studies
	@echo "   $(CC) $(CFLAGS) -c -o $@ $<"; $(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo "   Cleaning...";
	@echo "   rm $(TARGET)"; rm $(TARGET)
	@echo "   rm $(BUILDDIR)/*.o"; rm $(BUILDDIR)/*.o
	@echo "   rm $(BUILDDIR)/Studies/*.o"; rm $(BUILDDIR)/Studies/*.o
