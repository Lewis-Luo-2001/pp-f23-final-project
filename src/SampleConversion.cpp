#include "Config.h"
#include "SampleConversion.h"
#include <algorithm>

std::vector<AudioType> sample_conversion(const AudioBuffer &samples, int num_channels, int num_samples, double length_in_seconds) {

    std::vector<AudioType> result;

    int width = static_cast<double>(num_samples) / FPS / length_in_seconds;

    for(int i = 0; i < num_samples; i += width) {

        AudioType avg = 0;
        int end = std::min(i + width, num_samples);

        for(int j = 0; j < num_channels; j++) {
            for(int k = i; k < end; k++) {
                avg += samples[j][k];
            }
        }

        avg /= ((end - i) * num_channels);
        result.push_back(avg);

    }

    return result;

}
