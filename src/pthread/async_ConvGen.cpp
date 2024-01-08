#include <pthread.h>
#include <algorithm>
#include <numeric>
#include "async_ConvGen.h"

void *async_ConvGen(void *arg) {
    /* sample conversion */
    AudioType SAMPLE_MIN;
    AudioType SAMPLE_MAX;

    Arg* data = (Arg*)arg;
    int id = data->id;
    const AudioBuffer &samples = data->samples;
    int num_channels = data->num_channels;
    int num_samples = data->num_samples;
    double length_in_seconds = data->length_in_seconds;

    std::vector<AudioType> sample_result;

    int width = static_cast<double>(num_samples) / FPS / length_in_seconds;

    SAMPLE_MIN = std::numeric_limits<AudioType>::max();
    SAMPLE_MAX = std::numeric_limits<AudioType>::min();

    int start_sample = id * (num_samples / NUM_THREAD);
    int end_sample = start_sample + (num_samples / NUM_THREAD);

    for(int i = start_sample; i < end_sample; i += width) {

        AudioType avg = 0;
        int end = std::min(i + width, num_samples);

        for(int j = 0; j < num_channels; j++) {
            for(int k = i; k < end; k++) {
                avg += samples[j][k];
            }
        }

        avg /= ((end - i) * num_channels);

        SAMPLE_MIN = std::min(SAMPLE_MIN, avg);
        SAMPLE_MAX = std::max(SAMPLE_MAX, avg);

        sample_result.push_back(avg);

    }

    /* image generation */
    cv::Mat res = image_generation(sample_result, 0, sample_result.size());

    // cv::Mat localCopy = res.clone();
    data->images = new cv::Mat(res);

    pthread_exit(NULL);

    return(NULL);
}