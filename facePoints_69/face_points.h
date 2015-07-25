#ifndef _FACE_POINTS_H_
#define _FACE_POINTS_H_

#include "header.h"
#include "LBF.h"
#include "LBFRegressor.h"

class KeyPoints
{
public:
	KeyPoints(std::string modelName, std::string cascadeName)
	{
		this->modelName = modelName;
		this->cascadeName = cascadeName;


		faces = new std::vector < cv::Rect > ;

		initParam(modelName);

		regressor = new LBFRegressor;
		regressor->Load(modelName);

		cascade = new cv::CascadeClassifier;
		if (!cascade->load(cascadeName)){
			std::cerr << "ERROR: Could not load classifier cascade" << std::endl;
		}
	}
	~KeyPoints()
	{
		delete regressor;
		//delete cascade;
	}

	bool initParam(std::string param_file);
	void initParam();
	void runKeypointsDetection(cv::Mat inputImage);
	void getFacePosition(int* pos);

	/*<  返回的是一个vector，里面存放了输入图片
	     所有人脸的关键点，其中每68个点为一个人脸*/
	std::vector<CvPoint> getFaceKeypoints();

	/*<  keypoints中存放的为所有关键点的横纵坐标，
	     每两个位一个点，每68个点为一个人脸*/
	void getFaceKeypoints(int* keypoints);

	void drawFace();
	void drawKeypoints();

private:
	Params _params;
	int _pos[4];
	std::string modelName;
	std::string cascadeName;

	std::vector<cv::Rect> *faces;

	std::vector<CvPoint>points;

	LBFRegressor* regressor;
	cv::CascadeClassifier* cascade;
	cv::Mat_<double> current_shape;   /*< curret_shape是一个多行两列的矩阵,用来存放检测到的关键点*/
	std::vector<cv::Mat_<double>>shapes;


	void ReadGlobalParamFromFile(std::string );
	void InitializeGlobalParam();
	void detectFace(cv::Mat image);

};

#endif