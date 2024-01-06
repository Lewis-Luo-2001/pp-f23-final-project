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
 * @param mat matrix
 */
void concat_images(Mat &mat);
