#include "pch.h"
#include "CImgComposition.h"

unsigned char* CImgComposition::ImageComposition(int imgsize, unsigned char* input, unsigned char* backgroundimg, unsigned char* output, int bitcount)
{
	imgtemp = new unsigned char[imgsize];
	maskimg = new unsigned char[imgsize];
	maskimgNot = new unsigned char[imgsize];
	lenaobject = new unsigned char[imgsize];
	lenabackground = new unsigned char[imgsize];
	output = ImgFrameAnd(imgsize, input, backgroundimg, bitcount);
	//output = ImgFrameSum(imgsize, input, backgroundimg, output);
	//output = ImgNot(imgsize, input, output);
	//output = ImgBinary(imgsize, input, output, bitcount);

	//maskimg = ImgBinary(imgsize, input, imgtemp); //마스킹 대체.
	//maskimgNot = ImgNot(imgsize, maskimg, imgtemp);
	//lenaobject = ImgFrameAnd(imgsize, input, maskimg);
	//lenabackground = ImgFrameAnd(imgsize, backgroundimg, maskimgNot);
	//output = ImgFrameAnd(imgsize, lenaobject, lenabackground);

	return output;
}

unsigned char* CImgComposition::MakeMask(int imgsize, unsigned char* input, int bitcount)
{

	return nullptr;
}

unsigned char* CImgComposition::ImgFrameAnd(int imgsize, unsigned char* first, unsigned char* second, int bitcount)
{

	for (int i = 0; i < imgsize*3; i++) {
		imgtemp[i]
			= (unsigned char)(first[i] & second[i]);
	}
	return imgtemp;
}

unsigned char* CImgComposition::ImgNot(int imgsize, unsigned char* input, unsigned char* output, int bitcount)
{
	for (int i = 0; i < imgsize*3; i++)
		output[i] = 255 - input[i];
	return output;
}

unsigned char* CImgComposition::ImgFrameSum(int imgsize, unsigned char* lenaobject, unsigned char* lenaback, unsigned char* output, int bitcount)
{
	for (int i = 0; i < imgsize*3; i++) {
		if (lenaobject[i] + lenaback[i] > 255)
			output[i] = 255;
		else
			output[i] = lenaobject[i] + lenaback[i];
	}
	return output;
}

unsigned char* CImgComposition::ImgBinary(int imgsize, unsigned char* input, unsigned char* output, int bitcount) // 테스트 이미지용 간단 마스크 만들기.
{
	for (int i = 0; i < imgsize*3; i++) {
		if (input[i] >= 100)//임의 값임.
			output[i] = 255;
		else
			output[i] = 0;
	}

	return output;
}
