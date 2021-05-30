#pragma once
class CImgComposition
{
public:
	unsigned char* ImageComposition(int imgsize, unsigned char* input, unsigned char* backgroundimg, unsigned char* output, int bitcount);
	unsigned char* MakeMask(int imgsize, unsigned char* input, int bitcount);
	unsigned char* ImgFrameAnd(int imgsize, unsigned char* first, unsigned char* second, int bitcount);
	unsigned char* ImgNot(int imgsize, unsigned char* input, unsigned char* output, int bitcount);
	unsigned char* ImgBinary(int imgsize, unsigned char* input, unsigned char* output, int bitcount);
	unsigned char* ImgFrameSum(int imgsize, unsigned char* lenaobject, unsigned char* lenaback, unsigned char* output, int bitcount);


private:
	unsigned char* maskimg;
	unsigned char* maskimgNot;
	unsigned char* imgtemp;
	unsigned char* lenaobject;
	unsigned char* lenabackground;
};

