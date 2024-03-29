#pragma once

#include <opencv2/videoio.hpp>
#include <string>

using AudioType = int;
using AudioBuffer = std::vector<std::vector<AudioType>>;

extern std::string OUTPUT_FILENAME;

extern AudioType sample_min;
extern AudioType sample_max;

const long NUM_THREAD = 4;

const int FPS = 60;

const int EX = cv::VideoWriter::fourcc('m', 'p', '4', 'v');

const int WIDTH = 1920;

const int HEIGHT = 1080;

const cv::Size FRAME_SIZE = cv::Size(WIDTH, HEIGHT);

const int BAR_IN_A_FRAME = 75;

const int STANDARD_HEIGHT = 5;
