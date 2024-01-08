#include "AudioFile.h"
#include "opencv2/core.hpp"
#include "Config.h"
#include "async_ConvGen.h"
#include "ImageConcat.h"
#include <iostream>
#include <pthread.h>

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
    double start_time;
    pthread_t thread[NUM_THREAD];
    struct Arg arg[NUM_THREAD];
    //pthread_mutex_init(&mutexsum, NULL);

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_JOINABLE);

    //public param
    int width = static_cast<double>(num_samples) / FPS / length_in_seconds;
    std::vector<cv::Mat*> images_list(NUM_THREAD);

    for(int i=0; i<NUM_THREAD; i++){
        arg[i].id = i;
        arg[i].samples = audio_file.samples;
        arg[i].num_channels = num_channels;
        arg[i].num_samples = num_samples;
        arg[i].width = width;
        arg[i].images = images_list[i];

        if(pthread_create(&thread[i], &attr, async_ConvGen, &arg[i])!=0){
            cerr<<"create thread error"<<endl;
            return 1;
        }
    }

    pthread_attr_destroy(&attr);
    void* status;
    for(int i=0; i<NUM_THREAD; i++){
        pthread_join(thread[i], &status);
    }

    //pthread_mutex_destroy(&mutexsum);

    cv::Mat images;
    std::vector<cv::Mat> mat_vector;
    for (size_t i = 0; i < NUM_THREAD; i++) {
        mat_vector.push_back(*images_list[i]);
    }
    cv::hconcat(mat_vector, images);

    double end_time;

    //std::vector<AudioType> samples = sample_conversion(audio_file.samples, num_channels, num_samples, length_in_seconds);
    //cv::Mat images = image_generation(samples, begin, end);

    concat_images(images);  // Output included

    std::cout << "Done\n";

}
