# Decide about the main compiler
CC=g++

# Set all flags
CFLAGS=-I./ -I/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/root/6.04.14-x86_64-slc6-gcc49-opt/include
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

AtlasLabel.o: Root/AtlasLabel.cxx
	$(CC) $(MISCFLAGS) $(CFLAGS) -c Root/AtlasLabel.cxx

AtlasStyle.o: Root/AtlasStyle.cxx
	$(CC) $(MISCFLAGS) $(CFLAGS) -c Root/AtlasStyle.cxx

FileContainer.o: Root/FileContainer.cxx
	$(CC) $(MISCFLAGS) $(CFLAGS) -c Root/FileContainer.cxx

HistHolder.o: Root/HistHolder.cxx
	$(CC) $(MISCFLAGS) $(CFLAGS) -c Root/HistHolder.cxx

HistHolderContainer.o: Root/HistHolderContainer.cxx HistHolder.o FileContainer.o
	$(CC) $(MISCFLAGS) $(CFLAGS) -c Root/HistHolderContainer.cxx

HistPlotter.o: Root/HistPlotter.cxx HistHolder.o AtlasLabel.o
	$(CC) $(MISCFLAGS) $(CFLAGS) -c Root/HistPlotter.cxx

MatrixHolder.o: Root/MatrixHolder.cxx
	$(CC) $(MISCFLAGS) $(CFLAGS) -c Root/MatrixHolder.cxx

MatrixHolderContainer.o: Root/MatrixHolderContainer.cxx MatrixHolder.o FileContainer.o
	$(CC) $(MISCFLAGS) $(CFLAGS) -c Root/MatrixHolderContainer.cxx

MatrixPlotter.o: Root/MatrixPlotter.cxx HistPlotter.o
	$(CC) $(MISCFLAGS) $(CFLAGS) -c Root/MatrixPlotter.cxx

RatioPlotter.o: Root/RatioPlotter.cxx HistPlotter.o
	$(CC) $(MISCFLAGS) $(CFLAGS) -c Root/RatioPlotter.cxx

Studies_Jets.o: Root/Studies/Jets.cxx
	$(CC) $(MISCFLAGS) $(CFLAGS) -c Root/Studies/Jets.cxx -o Studies_Jets.o

Studies_Likelihood.o: Root/Studies/Likelihood.cxx
	$(CC) $(MISCFLAGS) $(CFLAGS) -c Root/Studies/Likelihood.cxx -o Studies_Likelihood.o

Studies_MatchEfficiencies.o: Root/Studies/MatchEfficiencies.cxx
	$(CC) $(MISCFLAGS) $(CFLAGS) -c Root/Studies/MatchEfficiencies.cxx -o Studies_MatchEfficiencies.o

Studies_MatchBtagPerf.o: Root/Studies/MatchBtagPerf.cxx
	$(CC) $(MISCFLAGS) $(CFLAGS) -c Root/Studies/MatchBtagPerf.cxx -o Studies_MatchBtagPerf.o

Studies_MatchJetMatrices.o: Root/Studies/MatchJetMatrices.cxx
	$(CC) $(MISCFLAGS) $(CFLAGS) -c Root/Studies/MatchJetMatrices.cxx -o Studies_MatchJetMatrices.o

Studies_MatchLONLO.o: Root/Studies/MatchLONLO.cxx
	$(CC) $(MISCFLAGS) $(CFLAGS) -c Root/Studies/MatchLONLO.cxx -o Studies_MatchLONLO.o


clean:
	rm -rf *.o plot
