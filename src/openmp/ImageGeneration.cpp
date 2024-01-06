#include "ImageGeneration.h"
#include <algorithm>

void image_generation(cv::Mat &res, const std::vector<AudioType> &samples, int begin, int end) {
    int bar_width = (WIDTH) / BAR_IN_A_FRAME;
    int mx = std::max(abs(SAMPLE_MAX), abs(SAMPLE_MIN));
    int adjust = STANDARD_HEIGHT / 2;

    for(int i = 0; i < adjust; i++) {
        #pragma omp parallel for num_threads(8)
        for(int w = begin; w < end; w++) {
            res.at<uchar>(HEIGHT / 2 + i, w) = 0;
            res.at<uchar>(HEIGHT / 2 - i, w) = 0;
        }
    }

    double percentage_unit = (HEIGHT - STANDARD_HEIGHT) / 2. / mx;
    int up_adjust = HEIGHT / 2 + adjust;
    int down_adjust = HEIGHT / 2 - adjust;
    #pragma omp parallel for num_threads(8)
    for(int i = begin; i < end; i++) {
        int high = round(abs(samples[i]) * percentage_unit);
        //high = round((float) high / (SAMPLE_MAX - SAMPLE_MIN) * HEIGHT);
        for(int h = 0; h < high; h++) {
            int up = up_adjust + h;
            int down = down_adjust - h;

            for(int w = i * bar_width; w < (i + 1) * bar_width; w++) {
                res.at<uchar>(up, w) = 0;
                res.at<uchar>(down, w) = 0;
            }
        }
    }
}
