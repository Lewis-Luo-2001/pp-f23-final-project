CC = g++
LIBS = `pkg-config --cflags --libs opencv4`
CXXFLAGS = -O3 -std=c++17 -funroll-loops -fopenmp -I../../AudioFile
DBGFLAGS = -g -fsanitize=address -fsanitize=undefined

.PHONY: all debug clean

all: Imagetrans

debug: CXXFLAGS += $(DBGFLAGS)
debug: all

Imagetrans: main.o SampleConversion.o ImageGeneration.o ImageConcat.o
	$(CC) -o $@ $^ $(LIBS) $(CXXFLAGS)

main.o: main.cpp Config.h
	$(CC) -c -o $@ $< $(LIBS) $(CXXFLAGS)

SampleConversion.o: SampleConversion.cpp SampleConversion.h Config.h
	$(CC) -c -o $@ $< $(LIBS) $(CXXFLAGS)

ImageGeneration.o: ImageGeneration.cpp ImageGeneration.h Config.h
	$(CC) -c -o $@ $< $(LIBS) $(CXXFLAGS)

ImageConcat.o: ImageConcat.cpp ImageConcat.h Config.h
	$(CC) -c -o $@ $< $(LIBS) $(CXXFLAGS)

clean:
	rm -rf Imagetrans *.o
