CC = g++
LIBS = `pkg-config --cflags --libs opencv4`
CXXFLAGS = -O3 -std=c++17 -lpthread -funroll-loops -I../../AudioFile -I/usr/local/include/opencv4 -lopencv_core -lopencv_videoio -lopencv_highgui
DBGFLAGS = -g -fsanitize=address -fsanitize=undefined

.PHONY: all debug clean

all: Imagetrans

debug: CXXFLAGS += $(DBGFLAGS)
debug: all

Imagetrans: pthread.o SampleConversion.o ImageGeneration.o ImageConcat.o async_ConvGen.o
	$(CC) -o $@ $^ $(LIBS) $(CXXFLAGS)

pthread.o: pthread.cpp Config.h
	$(CC) -c -o $@ $< $(LIBS) $(CXXFLAGS)

async_ConvGen.o: async_ConvGen.cpp Config.h SampleConversion.h ImageGeneration.h
	$(CC) -c -o $@ $< $(LIBS) $(CXXFLAGS)

SampleConversion.o: SampleConversion.cpp SampleConversion.h Config.h
	$(CC) -c -o $@ $< $(LIBS) $(CXXFLAGS)

ImageGeneration.o: ImageGeneration.cpp ImageGeneration.h Config.h
	$(CC) -c -o $@ $< $(LIBS) $(CXXFLAGS)

ImageConcat.o: ImageConcat.cpp ImageConcat.h Config.h
	$(CC) -c -o $@ $< $(LIBS) $(CXXFLAGS)

clean:
	rm -rf Imagetrans *.o
