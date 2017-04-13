#include "StudentPreProcessing.h"
#include "ImageIO.h"
#include <iostream>
#include "ImageFactory.h"
#include <stdint.h>
#include <math.h>



int BGD_kernel[1][3] = { { -1, 0, 1 } };

int laplacian_kernel[3][3] = {
	{ 0, 1, 0 },
	{ 1, -4, 1 },
	{ 0, 1, 0 } };

int sobel_kernel[3][3] = {
	{ 1, 0, -1 },
	{ 2, 0, -2 },
	{ 1, 0, -1 } };

int copy_kernel[3][3] = {
	{ 0, 0, 0 },
	{ 0, 1, 0 },
	{ 0, 0, 0 } };

int school_kernel[9][9] = {
	{0, 0, 0,  1,  1,  1, 0, 0, 0},
	{0, 0, 0,  1,  1,  1, 0, 0, 0},
	{0, 0, 0,  1,  1,  1, 0, 0, 0},
	{1, 1, 1, -4, -4, -4, 1, 1, 1},
	{1, 1, 1, -4, -4, -4, 1, 1, 1},
	{1, 1, 1, -4, -4, -4, 1, 1, 1},
	{0, 0, 0,  1,  1,  1, 0, 0, 0},
	{0, 0, 0,  1,  1,  1, 0, 0, 0},
	{0, 0, 0,  1,  1,  1, 0, 0, 0}
};

template<int sizeX, int sizeY>
IntensityImage * edge_detection(const IntensityImage &image, int kernel[sizeX][sizeY]) {
	IntensityImage * end_picture{ ImageFactory::newIntensityImage(image.getWidth(), image.getHeight()) };
	int offset = sizeX / 2;

	int sum = 0;
	for (int x = 0; x < end_picture->getWidth(); x++) {
		for (int y = 0; y < end_picture->getHeight(); y++) {
			sum = 0;
			for (int kernelX = -offset; kernelX < sizeX - offset; kernelX++) {
				for (int kernelY = -offset; kernelY < sizeY - offset; kernelY++) {

					int pictureX = x - kernelX;
					int pictureY = y - kernelY;

					if (pictureX > image.getWidth() - 1 || pictureX < 0 ||
						pictureY > image.getHeight() - 1 || pictureY < 0) {
						sum += 0;
					}
					else {
						sum += kernel[kernelY + offset][kernelX + offset] * image.getPixel(x - kernelX, y - kernelY);
					}
				}
			}
			sum += 127;
			if (sum < 0) {
				sum = 0;
			}
			else if (sum > 255) {
				sum = 255;
			}
			end_picture->setPixel(x, y, sum);
		}
	}
	return end_picture;
}

template<int sizeX, int sizeY>
IntensityImage * edge_detection_1d(const IntensityImage &image, int kernel[sizeX][sizeY]) {
	IntensityImage * end_picture{ ImageFactory::newIntensityImage(image.getWidth(), image.getHeight()) };
	int offset = sizeX / 2;
	int horizontal = 0;
	int vertical = 0;
	for (int x = 0; x < end_picture->getWidth(); x++) {
		for (int y = 0; y < end_picture->getHeight(); y++) {
			horizontal = 0;
			vertical = 0;
			for (int kernelX = -offset; kernelX < sizeX - offset; kernelX++) {
				for (int kernelY = -offset; kernelY < sizeY - offset; kernelY++) {

					int pictureX = x - kernelX;
					int pictureY = y - kernelY;

					if (pictureX > image.getWidth() - 1 || pictureX < 0 ||
						pictureY > image.getHeight() - 1 || pictureY < 0) {
						//sum += 0;
					}
					else {
						horizontal += kernel[kernelY + offset][kernelX + offset] * image.getPixel(x - kernelY, y - kernelX);
						vertical += kernel[kernelY + offset][kernelX + offset] * image.getPixel(x - kernelX, y - kernelY);
					}
				}
			}

			int end_pixel = std::sqrt(std::pow(horizontal, 2) + std::pow(vertical, 2));
			//end_pixel += 127;
			if (end_pixel < 0) {
				end_pixel = 0;
			}
			else if (end_pixel > 255) {
				end_pixel = 255;
			}

			end_picture->setPixel(x, y, end_pixel);
		}
	}
	return end_picture;
}

IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

		  
IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	//return laplacian(image);
	
	//return BGD(image);
	//return edge_detection_1d(image, BGD_kernel);
	//return edge_detection<1, 3>(image, BGD_kernel);
	//return edge_detection_2d2(image, prewitt_kernel);
	//return edge_detection<3, 3>(image, sobel_kernel);
	//return edge_detection<9, 9>(image, school_kernel);
	//return edge_detection<3, 3>(image, laplacian_kernel);
	return edge_detection<9, 9>(image, school_kernel);
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	IntensityImage * picture = ImageFactory::newIntensityImage(image);
	return picture;
}