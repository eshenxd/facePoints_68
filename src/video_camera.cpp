#include "video_camera.h"


Camera::Camera(int index ){

	c_capture = cvCaptureFromCAM(index);

	if (!c_capture) suc_flag=false;
	
	else{
		suc_flag = true;

		cvGrabFrame(c_capture);

		c_capimg = cvQueryFrame(c_capture);

		c_image = cvCreateImage(cvGetSize(c_capimg), c_capimg->depth, c_capimg->nChannels);

	}
}

Camera::~Camera(){

	
	if(suc_flag==true)
	{
		cvReleaseCapture(&c_capture);

		c_capture = 0;
		
		cvReleaseImage(&c_image);

		c_image = 0;
	}

	
}

IplImage* Camera::read_from_camera()
{
	c_capimg = cvQueryFrame(c_capture);

	if (c_capimg->origin == 0)
		cvCopy(c_capimg, c_image);
	else
		cvFlip(c_capimg, c_image);

	return c_image;
}


Video::Video(std::string filename){

	v_capture = cvCaptureFromFile(filename.c_str());

	if (!v_capture)
	{
		fprintf(stderr, "ERROR(%s, %d): CANNOT open video file %s!\n",
			__FILE__, __LINE__, filename);
		
		suc_flag = false;
	}

	else
	{
		suc_flag = true;

		cvSetCaptureProperty(v_capture, CV_CAP_PROP_POS_FRAMES, 0);
		
		v_capimg = cvQueryFrame(v_capture);
		
		v_image = cvCreateImage(cvGetSize(v_capimg), v_capimg->depth, v_capimg->nChannels);

		frame_count = (int)cvGetCaptureProperty(v_capture, CV_CAP_PROP_FRAME_COUNT);
	}
}

Video::~Video(){

	cvReleaseCapture(&v_capture);
	
	v_capture = 0;
	
	cvReleaseImage(&v_image);
	
	v_image = 0;
}

IplImage* Video::read_from_video(int frame_no){

	if (frame_no < -1)
		return 0;

	else
	{
		cvSetCaptureProperty(v_capture, CV_CAP_PROP_POS_FRAMES, frame_no);
		v_capimg = cvQueryFrame(v_capture);
	}

	if (v_capimg->origin == 0)
		cvCopy(v_capimg, v_image);
	else
		cvFlip(v_capimg, v_image);

	return v_image;
}


//test main.cpp
//int main(){
//	
//	std::string filename = "End.avi";
//
//	Video video(filename);
//
//	if (video.suc_flag == false)return -1;
//
//	IplImage* image=NULL;
//
//	int end = video.frame_count;
//
//	int i=0;
//
//	while (i<end)
//	{
//		image = video.read_from_video(i++);
//
//		cvShowImage("test", image);
//
//		cvWaitKey(1);
//	}
//}