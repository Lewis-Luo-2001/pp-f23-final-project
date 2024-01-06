#include "AudioFile.h"

void usage(){
    cerr << "Usage: ./imagetrans <inputfile> [outputfile]\n";
}

int main(int argc, char *argv[]){

    if(argc < 2){
        usage();
        return 1;
    }

    if(argc == 3){
        OUTPUT_FILENAME = argv[2];
    }

    AudioFile<AudioType> audio_file;
    bool load_success = audio_file.load(argv[1]);
    if(!load_success){
        cerr << "Audiofile load error\n";
        return 1;
    }

    int num_channels = audio_file.getNumChannels();
    int num_samples = audio_file.getNumSamplesPerChannel();
    double length_in_seconds = audio_file.getLengthInSeconds();

    vector<AudioType> samples = sample_conversion(audio_file.samples, num_channels, num_samples, length_in_seconds);

    cv::Mat images = image_generation(samplesi, 0, samples.size());

    concat_images(images);  // Output included

    cout << "Done\n";

}
