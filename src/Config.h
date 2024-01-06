#pragma once

#include <opencv2/videoio.hpp>
#include <string>

using AudioType = int;
using AudioBuffer = std::vector<std::vector<AudioType>>;

extern std::string OUTPUT_FILENAME;

extern AudioType SAMPLE_MIN;
extern AudioType SAMPLE_MAX;

const int FPS = 30;

const int EX = cv::VideoWriter::fourcc('m', 'p', '4', 'v');

const int WIDTH = 1920;

const int HEIGHT = 1080;

const cv::Size FRAME_SIZE = cv::Size(WIDTH, HEIGHT);

const int BAR_IN_A_FRAME = 50;
