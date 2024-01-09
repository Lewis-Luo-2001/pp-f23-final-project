#include "ImageConcat.h"
#include "Config.h"
#include "omp.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>

/*cv::Mat *generate_matrix(int row_num, int col_num) {
    cv::Mat *mat = new cv::Mat(row_num, col_num, CV_8UC1, cv::Scalar(255));

    return mat;
}

void randomize_matrix(int row_num, int col_num, cv::Mat* mat_ptr) {
    srand(0);
    int half_num_row = row_num / 2;
    for(int i = 0; i < col_num; i++) {
        int bar_length = rand() % (half_num_row);
        for(int j = half_num_row - bar_length; j < half_num_row + bar_length; j++) {
            (*mat_ptr).at<uchar>(j, i) = 0;
        }
    }
}*/

void concat_images(cv::Mat &mat) {
    int step = WIDTH / BAR_IN_A_FRAME;
    int progress = 0;
    int thread_cnt;
    bool error = 0;
    std::string filename_template = OUTPUT_FILENAME.substr(0, OUTPUT_FILENAME.size() - 4);

    #pragma omp parallel num_threads(8)
    {

        int thread_num = omp_get_thread_num();

        #pragma omp single
        thread_cnt = omp_get_num_threads();

        #pragma omp barrier

        cv::VideoWriter video_writer(filename_template + "_tmp" + std::to_string(thread_num) + ".mp4", EX, FPS, FRAME_SIZE, false);

        int start = (mat.cols - WIDTH + 1) * thread_num / thread_cnt;
        int end = (mat.cols - WIDTH + 1) * (thread_num + 1) / thread_cnt;

        if(!video_writer.isOpened()) {
            error = 1;
        }
        else {
            for(int col = start; col < end; col += step) {
                cv::Mat frame = mat(cv::Rect(col, 0, WIDTH, HEIGHT));
                video_writer.write(frame);
            }
        }

        video_writer.release();

    }

    if(error) {
        std::cerr << "Error: Could not open the video file for writing." << std::endl;
        return;
    }

    std::fstream file_list("file_list.txt", std::ios::out);

    for(int i = 0; i < thread_cnt; i++) {
        file_list << "file \'" << filename_template + "_tmp" + std::to_string(i) + ".mp4\'\n";
    }

    file_list.close();

    std::cerr << (std::string("ffmpeg -f concat -safe 0 -i file_list.txt -c copy ") + OUTPUT_FILENAME).c_str() << "\n";
    system((std::string("ffmpeg -f concat -safe 0 -i file_list.txt -c copy ") + OUTPUT_FILENAME).c_str());

    for(int i = 0; i < thread_cnt; i++) {
        std::remove((filename_template + "_tmp" + std::to_string(i) + ".mp4").c_str());
    }

    std::remove("file_list.txt");

    std::cout << "Video created successfully: " << OUTPUT_FILENAME << std::endl;
}
