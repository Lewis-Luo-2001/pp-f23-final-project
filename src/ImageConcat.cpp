#include "ImageConcat.h"

Mat *generate_matrix(int row_num, int col_num) {
    Mat *mat = new Mat(row_num, col_num, CV_8UC1, Scalar(255));

    return mat;
}

void randomize_matrix(int row_num, int col_num, Mat* mat_ptr) {
    srand(0);
    int half_num_row = row_num / 2;
    for(int i = 0; i < col_num; i++) {
        int bar_length = rand() % (half_num_row);
        for(int j = half_num_row - bar_length; j < half_num_row + bar_length; j++) {
            (*mat_ptr).at<uchar>(j, i) = 0;
        }
    }
}


void concat_images(int row_num, int col_num, Mat* mat_ptr, int frame_width, int frame_height, int fps, string video_path, int step) {
    VideoWriter video_writer(video_path, VideoWriter::fourcc('M', 'J', 'P', 'G'), fps, Size(frame_width, frame_height), false);

    if(!video_writer.isOpened()) {
        cerr<<"Error: Could not open the video file for writing."<<endl;
        return;
    }

    for(int col = 0; col <= image.cols - frame_width; col += step) {
        Mat frame = image(Rect(col, 0, frame_width, frame_height));
        video_writer.write(frame);
    }

    video_writer.release();

    cout<<"Video created successfully: "<<video_path<<endl;
}