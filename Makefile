# Decide about the main compiler
CC := g++

# Set the directories
COREDIR := core
STUDIESDIR := studies
TARGET := bin/plot

# Set flags
CFLAGS := -I./ `root-config --cflags`
LIBS := `root-config --libs`
MISCFLAGS := -fdiagnostics-color=always
DEBUGFLAGS := -O0 -g2

CORESRC := $(shell find $(COREDIR) -type f -name *.cc)
COREOBJ := $(CORESRC:.cc=.o)

STUDIESSRC := $(shell find $(STUDIESDIR) -type f -name *.cc)
STUDIESOBJ := $(STUDIESSRC:.cc=.o)

all: $(TARGET)

$(TARGET): $(COREOBJ) $(STUDIESOBJ)
	@echo "   Linking..."
	@mkdir -p bin
	@echo "   $(CC) $^ -o $(TARGET) $(LIBS)"; $(CC) $^ -o $(TARGET) $(LIBS)

$(COREDIR)/%.o: $(COREDIR)/%.cc
	@echo "   $(CC) $(CFLAGS) -c -o $@ $<"; $(CC) $(CFLAGS) -c -o $@ $<

$(STUDIESDIR)/%.o: $(STUDIESDIR)/%.cc
	@echo "   $(CC) $(CFLAGS) -c -o $@ $<"; $(CC) $(CFLAGS) -c -o $@ $<

clean:
	@echo "   Cleaning...";
	@echo "   find $(COREDIR) -type f -name "*.o" -exec rm {} \;"; find $(COREDIR) -type f -name "*.o" -exec rm {} \;
	@echo "   find $(STUDIESDIR) -type f -name "*.o" -exec rm {} \;"; find $(STUDIESDIR) -type f -name "*.o" -exec rm {} \;
	@echo "   rm $(TARGET)"; rm $(TARGET)
