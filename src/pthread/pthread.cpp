#include "AudioFile.h"
#include "opencv2/core.hpp"
#include "Config.h"
#include "async_ConvGen.h"
#include "ImageConcat.h"
#include <iostream>
#include <time.h>
#include <pthread.h>
#include <string>
#include <cstdio>

//pthread_mutex_t mutexsum;

void usage() {
    std::cerr << "Usage: ./Imagetrans <inputfile> [outputfile]\n";
}

std::string OUTPUT_FILENAME = "output.mp4";

int main(int argc, char *argv[]) {

    if(HEIGHT < STANDARD_HEIGHT) {
        std::cerr << "Height cannot less than standard height\n";
        return 1;
    }

    if(argc < 2) {
        usage();
        return 1;
    }

    if(argc == 3) {
        OUTPUT_FILENAME = argv[2];
    }

    AudioFile<AudioType> audio_file;
    bool load_success = audio_file.load(argv[1]);
    if(!load_success) {
        std::cerr << "Audiofile load error\n";
        return 1;
    }

    int num_channels = audio_file.getNumChannels();
    int num_samples = audio_file.getNumSamplesPerChannel();
    double length_in_seconds = audio_file.getLengthInSeconds();

    //pthread start
    pthread_t thread[NUM_THREAD];
    Arg *arg = (Arg*)malloc(sizeof(Arg) * NUM_THREAD);


    //public param
    int width = static_cast<double>(num_samples) / FPS / length_in_seconds;

    for(int i=0; i<NUM_THREAD; i++){
        arg[i].id = i;
        arg[i].samples = audio_file.samples;
        arg[i].num_channels = num_channels;
        arg[i].num_samples = num_samples;
        arg[i].width = width;
        arg[i].images = nullptr;
        arg[i].length_in_seconds = length_in_seconds;

        if(pthread_create(&thread[i], NULL, async_ConvGen, &arg[i])!=0){
            std::cerr<<"create thread error"<<std::endl;
            return 1;
        }
    }

    void* status;
    for(int i=0; i<NUM_THREAD; i++){
        pthread_join(thread[i], &status);
    }

    cv::Mat images;
    std::vector<cv::Mat> mat_vector;
    for (size_t i = 0; i < NUM_THREAD; i++) {
        if(arg[i].images == nullptr) std::cout<<"nullptr\n";
        else mat_vector.push_back(*arg[i].images);
    }
    cv::hconcat(mat_vector, images);

    std::string filename_template = OUTPUT_FILENAME.substr(0, OUTPUT_FILENAME.size() - 4);
    std::fstream file_list("file_list.txt", std::ios::out);

    for(int i = 0; i < NUM_THREAD; i++) {
        file_list << "file \'" << filename_template + "_tmp" + std::to_string(i) + ".mp4\'\n";
    }

    file_list.close();

    std::cerr << (std::string("ffmpeg -f concat -safe 0 -i file_list.txt -c copy ") + OUTPUT_FILENAME).c_str() << "\n";
    system((std::string("ffmpeg -f concat -safe 0 -i file_list.txt -c copy ") + OUTPUT_FILENAME).c_str());

    for(int i = 0; i < NUM_THREAD; i++) {
        std::remove((filename_template + "_tmp" + std::to_string(i) + ".mp4").c_str());
    }

    std::remove("file_list.txt");

    std::cout << "Video created successfully: " << OUTPUT_FILENAME << std::endl;
}
