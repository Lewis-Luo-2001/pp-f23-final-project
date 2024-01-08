#pragma once

#include "Config.h"
#include "Sample"
#include "SampleConversion.h"
#include "ImageGeneration.h"

struct Arg{
    int id;
    const AudioBuffer &samples;
    int num_channels;
    int num_samples;
    double width;
    cv::Mat *images;
};

/**
 * Parallelized compress samples and convert to suitable data structure, then generate the images
 *
 * @param arg thread arguments
 */
void *async_ConvGen(void *arg);