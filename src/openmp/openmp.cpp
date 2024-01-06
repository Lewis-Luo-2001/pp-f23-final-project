#include "AudioFile.h"
#include "opencv2/core.hpp"
#include "Config.h"
#include "SampleConversion.h"
#include "ImageGeneration.h"
#include "ImageConcat.h"
#include "omp.h"
#include <iostream>

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

    std::vector<AudioType> samples = sample_conversion(audio_file.samples, num_channels, num_samples, length_in_seconds);

    cv::Mat images = cv::Mat(HEIGHT, WIDTH / BAR_IN_A_FRAME * samples.size(), CV_8UC1, cv::Scalar(255));

    image_generation(images, samples, 0, samples.size());

    concat_images(images);  // Output included

    std::cout << "Done\n";

}
