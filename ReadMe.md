/*
 *
 * 代码名称：faceKeypoints_68
 * 代码功能：根据LBF源代码修改而来，解决了代码中的一些bug，并做了封住，主要功能
 *          是根据人脸检测获取到的人脸位置，找出68个关键点的位置。
 *          Input:
               modelPath: LBF.model and regressor.model 的存放位置
	           cascadeName： Harr模板文件的存放位置
	           cv::Mat inputImage:待检测图像
	        Output:
	           Keypoints.getFaceKeypoints():获取人脸关键点
 * 代码作者：Ethan
 * 创建时间：2015/7/25
 * 更新信息：
 */