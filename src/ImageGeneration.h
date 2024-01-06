#pragma once

#include <opencv2/core/mat.hpp>
#include "Config.h"

/**
 * Generate video frames from compressed samples
 *
 * @param samples compressed samples
 * @param num_channels begin index
 * @param num_samples end index
 */
cv::Mat image_generation(vector<AudioType> samples, int begin, int end);
