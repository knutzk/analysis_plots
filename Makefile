# Decide about the main compiler
CC=g++

# Set all flags
CFLAGS=-I./include -I/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/root/6.04.14-x86_64-slc6-gcc49-opt/include
LDFLAGS=-L/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/root/6.04.14-x86_64-slc6-gcc49-opt/lib
LIBS=-lCore -lRIO -lNet -lHist -lGraf -lGraf3d -lGpad -lTree -lRint -lPostscript -lMatrix -lPhysics -lMathCore -lThread -pthread -lm -ldl -rdynamic
MISCFLAGS=-pthread -std=c++11 -Wno-deprecated-declarations -m64 -O0 -g2 -fdiagnostics-color=always



all: plot

plot: main.o
	$(CC) $(MISCFLAGS) $(LDFLAGS) $(LIBS) -o plot \
	main.o \
	AtlasLabel.o \
	AtlasStyle.o \
	FileContainer.o \
	HistHolder.o \
	HistHolderContainer.o \
	HistPlotter.o \
	MatrixHolder.o \
	MatrixHolderContainer.o \
	MatrixPlotter.o \
	RatioPlotter.o \
	Studies_Jets.o \
	Studies_Likelihood.o \
	Studies_MatchBtagPerf.o \
	Studies_MatchEfficiencies.o \
	Studies_MatchJetMatrices.o \
	Studies_MatchLONLO.o \

main.o: main.cxx AtlasLabel.o AtlasStyle.o FileContainer.o HistHolder.o \
	HistHolderContainer.o HistPlotter.o MatrixHolder.o \
	MatrixHolderContainer.o MatrixPlotter.o RatioPlotter.o \
	Studies_Jets.o Studies_Likelihood.o Studies_MatchBtagPerf.o \
	Studies_MatchEfficiencies.o Studies_MatchJetMatrices.o \
	Studies_MatchLONLO.o
	$(CC) $(MISCFLAGS) $(CFLAGS) -c main.cxx

AtlasLabel.o: src/AtlasLabel.cxx
	$(CC) $(MISCFLAGS) $(CFLAGS) -c src/AtlasLabel.cxx

AtlasStyle.o: src/AtlasStyle.cxx
	$(CC) $(MISCFLAGS) $(CFLAGS) -c src/AtlasStyle.cxx

FileContainer.o: src/FileContainer.cxx
	$(CC) $(MISCFLAGS) $(CFLAGS) -c src/FileContainer.cxx

HistHolder.o: src/HistHolder.cxx
	$(CC) $(MISCFLAGS) $(CFLAGS) -c src/HistHolder.cxx

HistHolderContainer.o: src/HistHolderContainer.cxx HistHolder.o FileContainer.o
	$(CC) $(MISCFLAGS) $(CFLAGS) -c src/HistHolderContainer.cxx

HistPlotter.o: src/HistPlotter.cxx HistHolder.o AtlasLabel.o
	$(CC) $(MISCFLAGS) $(CFLAGS) -c src/HistPlotter.cxx

MatrixHolder.o: src/MatrixHolder.cxx
	$(CC) $(MISCFLAGS) $(CFLAGS) -c src/MatrixHolder.cxx

MatrixHolderContainer.o: src/MatrixHolderContainer.cxx MatrixHolder.o FileContainer.o
	$(CC) $(MISCFLAGS) $(CFLAGS) -c src/MatrixHolderContainer.cxx

MatrixPlotter.o: src/MatrixPlotter.cxx HistPlotter.o
	$(CC) $(MISCFLAGS) $(CFLAGS) -c src/MatrixPlotter.cxx

RatioPlotter.o: src/RatioPlotter.cxx HistPlotter.o
	$(CC) $(MISCFLAGS) $(CFLAGS) -c src/RatioPlotter.cxx

Studies_Jets.o: src/Studies/Jets.cxx
	$(CC) $(MISCFLAGS) $(CFLAGS) -c src/Studies/Jets.cxx -o Studies_Jets.o

Studies_Likelihood.o: src/Studies/Likelihood.cxx
	$(CC) $(MISCFLAGS) $(CFLAGS) -c src/Studies/Likelihood.cxx -o Studies_Likelihood.o

Studies_MatchEfficiencies.o: src/Studies/MatchEfficiencies.cxx
	$(CC) $(MISCFLAGS) $(CFLAGS) -c src/Studies/MatchEfficiencies.cxx -o Studies_MatchEfficiencies.o

Studies_MatchBtagPerf.o: src/Studies/MatchBtagPerf.cxx
	$(CC) $(MISCFLAGS) $(CFLAGS) -c src/Studies/MatchBtagPerf.cxx -o Studies_MatchBtagPerf.o

Studies_MatchJetMatrices.o: src/Studies/MatchJetMatrices.cxx
	$(CC) $(MISCFLAGS) $(CFLAGS) -c src/Studies/MatchJetMatrices.cxx -o Studies_MatchJetMatrices.o

Studies_MatchLONLO.o: src/Studies/MatchLONLO.cxx
	$(CC) $(MISCFLAGS) $(CFLAGS) -c src/Studies/MatchLONLO.cxx -o Studies_MatchLONLO.o


clean:
	rm -rf *.o plot
