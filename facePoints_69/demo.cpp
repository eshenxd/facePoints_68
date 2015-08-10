/*
   demo.cpp
   Author: Ethan
   2015-07-23


   Input:
       modelPath: LBF.model and regressor.model 的存放位置
	   cascadeName： Harr模板文件的存放位置
	   inputImage:待检测图像
	Output:
	   Keypoints.getFaceKeypoints():获取人脸关键点
*/

#include "header.h"
#include "face_points.h"
#include "video_camera.h"
#include "getFiles.h"
#include "faceWarpAndRotation.h"

using namespace std;
using namespace cv;

string _int2string_(int x)
{
	string tmp_s;
	char tmp_c[10];
	_itoa_s(x, tmp_c, 10);
	tmp_s = (string)tmp_c;
	return tmp_s;
}

int main()
{
	string modelPath = "../model/";
	string cascadeName = "../model/haarcascade_frontalface_alt.xml";
	string paramName = "../model/LBF.model";
	

	int saveCount = 0;
	string imageSavepath = "../save/";
	vector<CvPoint>save_keyPoint;

	KeyPoints keypointor(modelPath, cascadeName);
	

	Mat inputImage;
	Mat outputImage;

	string filePath = "../image";
	vector<string>filename;
	getFiles(filePath, filename);
	for (vector<string>::iterator iter = filename.begin(); iter != filename.end(); iter++)
	{
		saveCount++;
		inputImage = imread(*iter);
		keypointor.runKeypointsDetection(inputImage);
		save_keyPoint = keypointor.getFaceKeypoints();

		/*for (vector<CvPoint>::iterator iter = save_keyPoint.begin(); iter != save_keyPoint.end(); ++iter)
		{
		circle(inputImage, Point(iter->x, iter->y), 2, Scalar(255, 0, 0), 1, 8, 0);
		}

		imshow("show", inputImage);
		waitKey(0);*/

		

		/*circle(inputImage, src[0], 2, Scalar(255, 0, 0), 1, 8, 0);
		circle(inputImage, src[1], 2, Scalar(255, 0, 0), 1, 8, 0);
		circle(inputImage, src[2], 2, Scalar(255, 0, 0), 1, 8, 0);

		imshow("show", inputImage);
		waitKey(0);*/
		if (save_keyPoint.size() != 0)
		{
			Point2f src[3];
			src[0] = save_keyPoint[36];
			src[1] = save_keyPoint[45];
			src[2] = save_keyPoint[30];
			
			outputImage = faceWarpandRotation(src, inputImage);


			
			
		    string saveImageName = imageSavepath + _int2string_(saveCount) + ".jpg";
		
			imwrite(saveImageName, outputImage);

			/*imshow("src", inputImage);
			imshow("Warp", outputImage);
			waitKey(0);*/
		}
		
	}

	

	/*inputImage = imread("01.jpg");

	keypointor.runKeypointsDetection(inputImage);*/

	

	return 0;
}