#pragma once

#include <iostream>
#include <cstdlib>

#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"

/**
 * Generate a new 1-channel opencv Mat with white pixels
 *
 * @param row_num row num of the matrix 
 * @param col_num col num of the matrix
 */
Mat *generate_matrix(int row_num, int col_num);

/**
 * Set random data to the opencv Mat 
 *
 * @param row_num row num of the matrix 
 * @param col_num col num of the matrix
 * @param mat_ptr pointer of the matrix
 */
void randomize_matrix(int row_num, int col_num, Mat* mat_ptr);

/**
 * Concat the images into a video
 *
 * @param row_num row num of the matrix 
 * @param col_num col num of the matrix
 * @param mat_ptr pointer of the matrix
 * @param frame_width col num of the video
 * @param frame_height row num of the video
 * @param fps frame per second of the video
 * @param video_path file path of the video
 */
void concat_images(int row_num, int col_num, Mat* mat_ptr, int frame_width, int frame_height, int fps, string video_path);
