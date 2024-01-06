#pragma once

#include <opencv2/videoio.hpp>
#include <string>

using AudioType = double;

std::string OUTPUT_FILENAME = "output.mp4";

int FPS = 30;

int EX = cv::VideoWriter::fourcc('M', 'P', '4', 'V');

int WIDTH = 1920;

int HEIGHT = 1080;

cv::Size FRAME_SIZE = Size(WIDTH, HEIGHT);

int BAR_IN_A_FRAME = 50;