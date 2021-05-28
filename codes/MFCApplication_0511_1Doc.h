
// MFCApplication_0511_1Doc.h: CMFCApplication05111Doc 클래스의 인터페이스
//


#pragma once


class CMFCApplication05111Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CMFCApplication05111Doc() noexcept;
	DECLARE_DYNCREATE(CMFCApplication05111Doc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CMFCApplication05111Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	// 입력 영상을 위한 포인터
	unsigned char* m_InputImage;
	// 입력 영상의 가로축 크기
	int m_width;
	// 입력 영상의 세로축 크기
	int m_height;
	// 입력 영상의 전체 크기
	int m_size;
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	void OnDownSampling();
	// 입력영상을 위한 포인터
	unsigned char*m_OutputImage;
	// 입력영상 가로축 크기
	int m_Re_width;
	// 입력 영상의 세로축 크기
	int m_Re_height;
	// 입력 영상의 전체 크기
	int m_Re_size;
	void OnUpSampling();
	void OnQuantization();


	void OnSumConstant();
	void OnSubConstant();
	void OnMulConstant();
	void OnDivConstant();
	void OnAndOperate();
	void OnOrOperate();
	void OnXorOperate();
	void OnNegaTransform();
	void OnGammaCorrection();
	void OnBinarization();
	
	void OnStressTransform();
	void OnHistoStretch();
	void OnEndInSearch();
	void OnHistogram();
	void OnHistoEqual();
	void OnHistoSpec();
	void OnEmbossing();
	double** OnMaskProcess(unsigned char *Target, double Mask[3][3]);
	double** OnScale(double **Target, int height, int width);
	double** Image2DMem(int height, int width);
	double** m_tempImage;
	void OnBlurr();
	void OnGaussianFilter();
	void OnSharpning();
	void OnHprSharp();
	void OnLpfSharp();
	void OnConvolSum();
	void OnTranslation();
	void OnMirrorHor();
	void OnMirrorVer();
	void OnTranslation2();
	void OnFrameAnd();
	void OnFrameConb();
	void OnFrameDiv();
	void OnFrameMul();
	void OnFrameOr();
	void OnFrameSub();
	void OnFrameSum();
	void OnBinaryDilation();
	void OnBinaryErosion();
	void OnGrayDilation();
	void OnGrayErosion();
	void OnLowPassFilter();
	void OnHighPassFilter();
	void OnMeanFilter();
	void OnMedianFilter();
	void OnMaxFilter();
	void OnMinFilter();
	void OnBubbleSort(double * A, int MAX);
	void OnSwap(double* a, double* b);
	struct Complex {
		double Re;
		double Im;
	};
	void OnFft2d();
	void OnFtt1d(Complex * X, int N, int Log2N);
	
	void OnShuffle(Complex * X, int N, int Log2N);
	void OnButterfly(Complex * X, int N, int Log2N, int mode);
	int OnReverseBitOrder(int index, int Log2N);
	Complex** m_FFT;
	void OnImgCompo();
	void OnIfft2d();
	void OnIfft1d(Complex* X, int N, int Log2N);
	Complex** m_IFFT;
	void OnLpfFrequency();
	void OnHpfFrequency();
};
