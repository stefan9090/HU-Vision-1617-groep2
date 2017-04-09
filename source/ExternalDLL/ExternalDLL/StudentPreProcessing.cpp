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

//unused code
/*
IntensityImage * mix_picture(const IntensityImage *image1, const IntensityImage *image2) {
	if (!(image1->getHeight() == image2->getHeight()) && (image1->getWidth() == image2->getWidth())) {
		return nullptr;
	}
	IntensityImage * end_picture = ImageFactory::newIntensityImage(*image1);
	for (int x = 1; x < image1->getWidth() - 1; x++) {
		for (int y = 0; y < image1->getHeight(); y++) {

			unsigned char image1_pixel = image1->getPixel(x, y);
			unsigned char image2_pixel = image2->getPixel(x, y);

			if (image1_pixel >= image2_pixel) {
				end_picture->setPixel(x, y, image2_pixel);
			}
			else {
				end_picture->setPixel(x, y, image1_pixel);
			}
		}
	}
	return end_picture;
}
*/

IntensityImage * StudentPreProcessing::stepToIntensityImage(const RGBImage &image) const {
	return nullptr;
}

IntensityImage * StudentPreProcessing::stepScaleImage(const IntensityImage &image) const {
	return nullptr;
}

//unused code
/*
IntensityImage * laplacian(const IntensityImage &image) {
	IntensityImage * end_picture = ImageFactory::newIntensityImage(image);
	for (int x = 1; x < image.getWidth() - 1; x++) {
		for (int y = 1; y < image.getHeight() - 1; y++) {
			
			unsigned char pixel_base = image.getPixel(x, y);

			unsigned char pixel_first = image.getPixel(x - 1, y);
			unsigned char pixel_second = image.getPixel(x + 1, y);

			int horizontal_pixel = pixel_first + pixel_second - 2 * pixel_base;

			pixel_first = image.getPixel(x, y - 1);
			pixel_second = image.getPixel(x, y + 1);

			int vertical_pixel = -pixel_first + pixel_second - 2 * pixel_base;

			int new_pixel = std::sqrt(std::pow(vertical_pixel, 2) + std::pow(horizontal_pixel, 2));

			
			//new_pixel += 127;

			if (new_pixel > 255) {
				new_pixel = 255;
			}
			else if (new_pixel < 0) {
				new_pixel = 0;
			}

			end_picture->setPixel(x, y, new_pixel);
		}
	}
	return end_picture;
}

IntensityImage * edge_detection_1d(const IntensityImage &image, int kernel[3]) {
	IntensityImage * end_picture = ImageFactory::newIntensityImage(image);
	int hor_sum = 0;
	int ver_sum = 0;
	for (int x = 1; x < image.getWidth() - 1; x++) {
		for (int y = 1; y < image.getHeight()-1; y++) {
			hor_sum = 0;
			ver_sum = 0;
			for (int kernelX = -1; kernelX <= 1;kernelX++) {
				hor_sum += kernel[kernelX + 1] * image.getPixel(x - kernelX, y);
				ver_sum += kernel[kernelX + 1] * image.getPixel(x, y - kernelX);
			}
			
			int new_pixel = std::sqrt(std::pow(hor_sum, 2) + std::pow(ver_sum, 2));

			if (new_pixel < 0) {
				new_pixel = 0;
			}
			else if (new_pixel > 255) {
				new_pixel = 255;
			}
			
			end_picture->setPixel(x, y, new_pixel);
			
		}
	}
	return end_picture;
}

IntensityImage * edge_detection_2d1(const IntensityImage &image, int kernel[3][3]) {
	IntensityImage * end_picture = ImageFactory::newIntensityImage(image);
	int sum = 0;
	for (int x = 1; x < image.getWidth() - 1; x++) {
		for (int y = 1; y < image.getHeight() - 1; y++) {
			sum = 0;
			for (int kernelX = -1; kernelX <= 1; kernelX++) {
				for (int kernelY = -1; kernelY <= 1; kernelY++) {
					sum += kernel[kernelY + 1][kernelX + 1] * image.getPixel(x - kernelX, y - kernelY);
				}
			}			
			if (sum < 0) {
				sum = 0;
			}
			end_picture->setPixel(x, y, sum);
		}
	}
	return end_picture;
}

IntensityImage * edge_detection_2d2(const IntensityImage &image, int kernel[3][3]) {
	IntensityImage * end_picture = ImageFactory::newIntensityImage(image);
	int sum_hor = 0;
	int sum_ver = 0;
	for (int x = 1; x < image.getWidth() - 1; x++) {
		for (int y = 1; y < image.getHeight() - 1; y++) {
			sum_hor = 0;
			sum_ver = 0;
			for (int kernelX = -1; kernelX <= 1; kernelX++) {
				for (int kernelY = -1; kernelY <= 1; kernelY++) {
					sum_hor += kernel[kernelY + 1][kernelX + 1] * image.getPixel(x - kernelX, y - kernelY);
					sum_ver += kernel[kernelX + 1][kernelY + 1] * image.getPixel(x - kernelX, y - kernelY);
				}
			}
			int new_pixel = std::sqrt(std::pow(sum_hor, 2)+std::pow(sum_ver, 2));
			//int new_pixel = sum_hor + sum_ver;
			if (new_pixel < 0) {
				new_pixel = 0;
			}else if (new_pixel > 255) {
				new_pixel = 255;
			}
			end_picture->setPixel(x, y, new_pixel);
		}
	}
	return end_picture;
}

IntensityImage * BGD(const IntensityImage &image) {
	IntensityImage * end_picture = ImageFactory::newIntensityImage(image);
	for (int x = 1; x < image.getWidth() - 1; x++) {
		for (int y = 1; y < image.getHeight() - 1; y++) {

			unsigned char pixel_first = image.getPixel(x - 1, y);
			unsigned char pixel_second = image.getPixel(x, y);
			
			int horizontal_pixel = -pixel_first + pixel_second;
			

			pixel_first = image.getPixel(x, y - 1);
			pixel_second = image.getPixel(x, y);

			int vertical_pixel = -pixel_first + pixel_second;

			int new_pixel = std::sqrt(std::pow(vertical_pixel, 2) + std::pow(horizontal_pixel, 2));

			if (new_pixel > 255) {
				new_pixel = 255;
			}
			else if (new_pixel < 0) {
				new_pixel  = 0;
			}

			end_picture->setPixel(x, y, new_pixel);
		}
	}
	return end_picture;
}
*/
					  

IntensityImage * StudentPreProcessing::stepEdgeDetection(const IntensityImage &image) const {
	//return laplacian(image);
	
	//return BGD(image);
	//return edge_detection_1d(image, BGD_kernel);
	//return edge_detection_1d<1, 3>(image, BGD_kernel);
	//return edge_detection_2d2(image, prewitt_kernel);
	//return edge_detection<3, 3>(image, sobel_kernel);
	//return edge_detection<9, 9>(image, school_kernel);
	return edge_detection<3, 3>(image, laplacian_kernel);
}

IntensityImage * StudentPreProcessing::stepThresholding(const IntensityImage &image) const {
	IntensityImage * picture = ImageFactory::newIntensityImage(image);
	return picture;
	long total_pixel_int = 0;
	for (int x = 1; x < image.getWidth() - 1; x++) {
		for (int y = 0; y < image.getHeight(); y++) {
			total_pixel_int += image.getPixel(x, y);
		}
	}
	unsigned char average_pixel_int = total_pixel_int / (image.getHeight()*image.getWidth());
	average_pixel_int += 30;
	for (int x = 1; x < image.getWidth() - 1; x++) {
		for (int y = 1; y < image.getHeight()-1; y++) {
			unsigned char pixel = image.getPixel(x, y);
			if (pixel < average_pixel_int) {
				picture->setPixel(x, y, 255);
			}
			else {
				picture->setPixel(x, y, 0);
			}
		}
	}

	return picture;
}