#pragma once

#include <optional>
#include "Config.h"
#include "SampleConversion.h"
#include "ImageGeneration.h"
#include "ImageConcat.h"

typedef struct Arg{
    int id;
    AudioBuffer samples;
    int num_channels;
    int num_samples;
    double width;
    double length_in_seconds;
    cv::Mat *images;
} Arg;

/**
 * Parallelized compress samples and convert to suitable data structure, then generate the images
 *
 * @param arg thread arguments
 */
void *async_ConvGen(void *arg);