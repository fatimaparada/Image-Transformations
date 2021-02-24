// Write your own transformation function(rotate, scale, and translate) and then apply the assigned transformations to the given image.
//	NOTE: You are NOT allowed to use the default cv.warpAffine or cv.warpPerspective functions.
//	1. Write separate function for Rotate, Scale, and Translate transformation.Your function should
//	have an imageand a transformation matrix as the input, and have a new image as the output.
//	2. For the given image in this assignment, please apply the following transformationsand save all
//	the output results(save the output images) :
//	a.Scale the image up by double the width and height.
//	b.Rotate the image 45 degrees. (output image should have same dimension of the original
//		image)
//	c.Translate the image by(100, 50)
//	d.Translate the image first by(100, 50) then rotate 45 degrees
//	e.Rotate the image 45 degrees first, and then translate the image by(100, 50)


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <cmath>
#include <iostream>

using namespace cv;
using namespace std;

// Scaling function
Mat myScale(Mat lenna, int transMat [][3]) {

	//Empty matrix twice as large
	Mat scaledImage = Mat::zeros(lenna.rows * 2, lenna.cols * 2, CV_8UC3);

	//Going through every pixel
	for (int x = 0; x < lenna.cols; x++) {
		for (int y = 0; y < lenna.rows; y++) {

			Vec3b color = lenna.at<Vec3b>(x, y);

			//cross product
			int newx = x * transMat[0][0] + y * transMat[1][0] + transMat[2][0];
			int newy = x * transMat[0][1] + y * transMat[1][1] + transMat[2][1];

			scaledImage.at<Vec3b>(newx, newy) = color;
		}
	}
	return scaledImage;
}

// Translation function
Mat myTranslate(Mat img, int translationTrans[][3]) {
	//Empty Matrix for translated image
	Mat translImage = Mat::zeros(img.rows, img.cols , CV_8UC3);

	//Going through every pixel
	for (int x = 0; x < img.cols; x++) {
		for (int y = 0; y < img.rows; y++) {

			Vec3b color = img.at<Vec3b>(x, y);

			//cross product
			int newx = x + translationTrans[0][2];
			int newy = y + translationTrans[1][2];

			
			if (newy >= 0 && newy <= img.rows - 1 && newx >= 0 && newx <= img.cols - 1) {

				translImage.at<Vec3b>(newx, newy) = color;
			}
		}
	}

	return translImage;
}

// Rotate Function
Mat myRotate(Mat lenna, double transMat[][3]) {

	//Empty Matrix large enough for rotated image
	Mat rotatedImage = Mat::zeros(lenna.rows , lenna.cols, CV_8UC3);

	//Going through every pixel
	for (int x = 0; x < lenna.cols; x++) {
		for (int y = 0; y < lenna.rows; y++) {

			Vec3b color = lenna.at<Vec3b>(x, y);

			//cross product
			int newx = (int)((x * transMat[0][0]) + (y * transMat[0][1]));
			int newy = (int)((x * transMat[1][0]) + (y * transMat[1][1]));

			if (newy >= 0 && newy <= lenna.rows - 1 && newx >= 0 && newx <= lenna.cols - 1) {

				rotatedImage.at<Vec3b>(newx, newy) = color;
			}
		}
	}
	return rotatedImage;
}

// Main function
int main() {
	float pi = 3.1415926;
	Mat lenna = imread("lenna.jpg");

	//Check if the image is found
	if (lenna.empty()) {
		cout << "No image found or unable to open" << endl;
	}
	else {
		imshow("Original Image: ", lenna);
	}

	//Scaling transformation matrix
	int scaleTrans[3][3] = {
	{ 2, 0, 0 },
	{ 0, 2, 0 },
	{ 0, 0, 1 }};

	//Translation transformation matric
	int x = 50;
	int y = 100;

	int translationTrans[3][3] = {
	{ 1, 0, x},
	{ 0, 1, y },
	{ 0, 0, 1 } };

	//Rotate 45 degress transformation matrix
	double angle = 45.00;

	double rotateTrans[3][3] = {
	{ cos((angle/180) * pi), sin((angle/180) * pi), 0 },
	{ -sin((angle/180) * pi), cos((angle/180) * pi), 0 },
	{ 0, 0, 1 } };

	//1. Scale the image up by double the widthand height.
	Mat scaledImg = myScale(lenna, scaleTrans);
	imshow("Scaled image: ", scaledImg);
	imwrite("scaledImg.jpg", scaledImg);

	//2. Rotate the image 45 degrees
	Mat rotatedImg = myRotate(lenna, rotateTrans);
	imshow("Rotated image:", rotatedImg);
	imwrite("rotatedImg.jpg", rotatedImg);

	//3. Translate the image by(100, 50)
	Mat translatedImg = myTranslate(lenna, translationTrans);
	imshow("Translated image: ", translatedImg);
	imwrite("translatedImg.jpg", translatedImg);

	//4. Translate the image first by(100, 50) then rotate 45 degrees
	Mat transRotaImg = myRotate(translatedImg, rotateTrans);
	imshow("Translated then rotated image:", transRotaImg);
	imwrite("TranslatedRotatedImg.jpg", transRotaImg);

	//5. Rotate the image 45 degrees first, and then translate the image by(100, 50)
	Mat rotatTransImg = myTranslate(rotatedImg, translationTrans);
	imshow("Rotated then translated image:", rotatTransImg);
	imwrite("RotatedTranslatedImg.jpg", rotatTransImg);

	waitKey(0);
	return 0;
}