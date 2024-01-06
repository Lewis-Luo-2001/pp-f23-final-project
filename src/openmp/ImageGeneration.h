#pragma once

#include <opencv2/core/mat.hpp>
#include "Config.h"
#include <vector>

/**
 * Generate video frames from compressed samples
 *
 * @param samples compressed samples
 * @param num_channels begin index
 * @param num_samples end index
 */
void image_generation(cv::Mat &res, const std::vector<AudioType> &samples, int begin, int end);
