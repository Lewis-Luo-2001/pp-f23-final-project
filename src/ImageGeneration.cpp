#include "ImageGeneration.h" 

Mat ImageGeneration(vector<AudioType> samples, int begin, int end){
    int bar_width = (WIDTH) / BAR_IN_A_FRAME;
    Mat res = new Mat((bar_width) * (end-begin), HEIGHT, CV_8UC1, Scalar(255));

    for(int i = begin; i < end; i++) {
        int high = round(samples[i]);
        for(int h = 0; h < high / 2; h++) {
            for(int w = i * bar_width; w < (i + 1) * bar_width; w++) {
                res.at<uchar>(HEIGHT / 2 + h, w) = 0;
            }
        }
    }

    return res;
}
