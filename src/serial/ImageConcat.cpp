#include "ImageConcat.h"
#include "Config.h"

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

    cv::VideoWriter video_writer(OUTPUT_FILENAME, EX, FPS, FRAME_SIZE, false);

    if(!video_writer.isOpened()) {
        std::cerr << "Error: Could not open the video file for writing." << std::endl;
        return;
    }

    for(int col = 0; col <= mat.cols - WIDTH; col += step) {
        cv::Mat frame = mat(cv::Rect(col, 0, WIDTH, HEIGHT));
        video_writer.write(frame);

        if(col * 100 / (mat.cols - WIDTH) > progress) {
            progress = col * 100 / (mat.cols - WIDTH);
            if(progress % 5 == 0) {
                std::cout << "Processing: " << progress << "%\n";
            }
        }
    }

    std::cout << "Processing: 100%\n";

    video_writer.release();

    std::cout << "Video created successfully: " << OUTPUT_FILENAME << std::endl;
}
