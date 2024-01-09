#include "Config.h"
#include "SampleConversion.h"
#include <algorithm>
#include <numeric>
#include "omp.h"

AudioType SAMPLE_MIN;
AudioType SAMPLE_MAX;

std::vector<AudioType> sample_conversion(const AudioBuffer &samples, int num_channels, int num_samples, double length_in_seconds) {

    std::vector<AudioType> result;

    int width = static_cast<double>(num_samples) / FPS / length_in_seconds;

    int result_size = num_samples / width + (num_samples % width != 0);
    result.resize(result_size);

    SAMPLE_MIN = std::numeric_limits<AudioType>::max();
    SAMPLE_MAX = std::numeric_limits<AudioType>::min();

    #pragma omp parallel for num_threads(MAX_THREADS)
    for(int i = 0; i < result_size; i++) {

        AudioType avg = 0;
        int begin = i * width;
        int end = std::min(begin + width, num_samples);

        for(int j = 0; j < num_channels; j++) {
            for(int k = begin; k < end; k++) {
                avg += samples[j][k];
            }
        }

        avg /= ((end - begin) * num_channels);

        SAMPLE_MIN = std::min(SAMPLE_MIN, avg);
        SAMPLE_MAX = std::max(SAMPLE_MAX, avg);

        result[i] = avg;

    }

    return result;

}
