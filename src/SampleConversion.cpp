#include "Config.h"
#include "SampleConversion.h"
#include <algorithm>
#include <numeric>

AudioType SAMPLE_MIN;
AudioType SAMPLE_MAX;

std::vector<AudioType> sample_conversion(const AudioBuffer &samples, int num_channels, int num_samples, double length_in_seconds) {

    std::vector<AudioType> result;

    int width = static_cast<double>(num_samples) / FPS / length_in_seconds;

    SAMPLE_MIN = std::numeric_limits<AudioType>::max();
    SAMPLE_MAX = std::numeric_limits<AudioType>::min();

    for(int i = 0; i < num_samples; i += width) {

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

        result.push_back(avg);

    }

    return result;

}
