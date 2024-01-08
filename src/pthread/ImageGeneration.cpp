#include "ImageGeneration.h"
#include <algorithm>

cv::Mat image_generation(std::vector<AudioType> samples, int begin, int end, AudioType SAMPLE_MIN, AudioType SAMPLE_MAX){
    int bar_width = (WIDTH) / BAR_IN_A_FRAME;
    cv::Mat res = cv::Mat(HEIGHT, (bar_width) * (end-begin), CV_8UC1, cv::Scalar(255));
    int mx = std::max(abs(SAMPLE_MAX), abs(SAMPLE_MIN));
    int adjust = STANDARD_HEIGHT / 2;

    for(int i = 0; i < adjust; i++) {
        for(int w = 0; w < end - begin; w++) {
            res.at<uchar>(HEIGHT / 2 + i, w) = 0;
            res.at<uchar>(HEIGHT / 2 - i, w) = 0;
        }
    }

    double percentage_unit = (HEIGHT - STANDARD_HEIGHT) / 2. / mx;
    for(int i = begin; i < end; i++) {
        int high = round(abs(samples[i]) * percentage_unit);
        //high = round((float) high / (SAMPLE_MAX - SAMPLE_MIN) * HEIGHT);
        for(int h = 0; h < high; h++) {
            int up = HEIGHT / 2 + adjust + h;
            int down = HEIGHT / 2 - adjust - h;
            //if(up > HEIGHT || down < 0) break;

            for(int w = i * bar_width; w < (i + 1) * bar_width; w++) {
                res.at<uchar>(up, w) = 0;
                res.at<uchar>(down, w) = 0;
            }
        }
    }

    return res;
}
