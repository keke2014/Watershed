
/*
* 分水岭算法主函数
*/

#include <string>
#include "WaterShedAlgorithm.h"

int main( int argc, char* argv[] )
{
	std::string imgName;
	if (argc > 1) imgName = argv[1];
	else { printf("usage: ws image_name \n"); return -1; }

	WatershedAlgorithm myWatershed;	// 创建分水岭算法实例
	IplImage* pSrc = cvLoadImage(imgName.c_str(), CV_LOAD_IMAGE_UNCHANGED);
	if (pSrc == NULL) {
		printf("Can't open image: %s \n", imgName.c_str());
		return -1;
	}
	myWatershed.run(pSrc, imgName);	// 运行分水岭算法

	cvShowImage(imgName.c_str(), pSrc);
	std::string inTmp;
	if (pSrc->nChannels == 3) {
		inTmp = imgName + "_Gray.jpg";
		IplImage* pGray = cvLoadImage(inTmp.c_str(), CV_LOAD_IMAGE_UNCHANGED);
		cvShowImage(inTmp.c_str(), pGray);
	}
	inTmp = imgName + "_BW.jpg";
	IplImage* pBW = cvLoadImage(inTmp.c_str(), CV_LOAD_IMAGE_UNCHANGED);
	cvShowImage(inTmp.c_str(), pBW);
	inTmp = imgName + "_WS.jpg";
	IplImage* pWS = cvLoadImage(inTmp.c_str(), CV_LOAD_IMAGE_UNCHANGED);
	cvShowImage(inTmp.c_str(), pWS);
	inTmp = imgName + "_Gray_WS.jpg";
	IplImage* pGWS = cvLoadImage(inTmp.c_str(), CV_LOAD_IMAGE_UNCHANGED);
	cvShowImage(inTmp.c_str(), pGWS);
	cvWaitKey();

	cvReleaseImage(&pSrc);
	return 0;
}
