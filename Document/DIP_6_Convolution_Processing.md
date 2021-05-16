## DIP_Convolution_Processing
* 화소의 원값이나 위치를 바탕으로 화소 값을 변경하는 화소의 점 처리과 달리 해당 입력 화소뿐만 아니라 그 주위의 화소 값도 함께 고려하는 공간 영역 연산
* 회선 기법(또는 컨벌루션 기법, Convolution Technique)으로 수행하므로, 화소의 영역 처리를 회선 처리(Convolution Processing) 또는 컨벌루션 처리라고 함.
* 원시 화소와 이웃한 각 화소에 가중치를 곱한 합을 출력 화소로 생성


### 엠보싱 처리
* 입력 영상을 양각 형태로 보이게 하는 기술
* 원하는 비트를 선택적으로 0으로 만드는 기능이 있어 마스크(mask) 연산이라고도 함
* 실행하기
  - 메뉴 추가
  - 클래스 마법사를 통해 View와 Doc에 OnEmbossing 함수 생성.
  - Doc 클래스에 OnMaskProcess, OnScale, Image2DMem 함수 추가. double** m_tempImage 변수 선언
  - Doc OnEmbossing() 작성
  ```c
  void CMFCApplication05111Doc::OnEmbossing()
  {
  	int i, j;
  	//double EmboMask[3][3] = { {-1., 0., 0.}, {0., 0., 0.}, {0., 0., 1.} };
  	//마스크 선택
  	double EmboMask[3][3] = {{0., 0., 0.}, {0., 1., 0.}, {0., 0., 0.}};
  	 //double EmboMask[3][3] = {{1., 1., 1.}, {1., -8.,1.}, {1., 1., 1.}};

  	m_Re_height = m_height;
  	m_Re_width = m_width;
  	m_Re_size = m_Re_height * m_Re_width;
  	m_OutputImage = new unsigned char[m_Re_size];
  	m_tempImage = OnMaskProcess(m_InputImage, EmboMask);

  	for (i = 0; i < m_Re_height; i++) {
  		for (j = 0; j < m_Re_width; j++) {
  			if (m_tempImage[i][j] > 255.)
  				m_tempImage[i][j] = 255.;
  			if (m_tempImage[i][j] < 0.)
  				m_tempImage[i][j] = 0.;
  		}
  	}

  	// m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);
  	//정규화 함수 사용할 때.

  	for (i = 0; i < m_Re_height; i++) {
  		for (j = 0; j < m_Re_width; j++) {
  			m_OutputImage[i*m_Re_width + j]
  				= (unsigned char)m_tempImage[i][j];
  		}
  	}
  	// TODO: 여기에 구현 코드 추가.
  }
  ```
  - Doc OnMaskProcess() 작성
  ```c
  double** CMFCApplication05111Doc::OnMaskProcess(unsigned char *Target, double Mask[3][3])
  {
  	int i, j, n, m;
  	double **tempInputImage, **tempOutputImage, S = 0.0;

  	tempInputImage = Image2DMem(m_height + 2, m_width + 2);

  	tempOutputImage = Image2DMem(m_height, m_width);

  	for (i = 0; i < m_height; i++) {
  		for (j = 0; j < m_width; j++) {
  			tempInputImage[i + 1][j + 1]
  				= (double)Target[i * m_width + j];
  		}
  	}

  	for (i = 0; i < m_height; i++) {
  		for (j = 0; j < m_width; j++) {
  			for (n = 0; n < 3; n++) {
  				for (m = 0; m < 3; m++) {
  					S += Mask[n][m] * tempInputImage[i + n][j + m];
  				}
  			}
  			tempOutputImage[i][j] = S;
  			S = 0.0;
  		}
  	}

  	// TODO: 여기에 구현 코드 추가.
  	return tempOutputImage;
  }
  ```
  - Doc OnScale() 작성
  ```c
  double** CMFCApplication05111Doc::OnScale(double **Target, int height, int width)
  {
  	int i, j;
  	double min, max;

  	min = max = Target[0][0];

  	for (i = 0; i < height; i++) {
  		for (j = 0; j < width; j++) {
  			if (Target[i][j] <= min)
  				min = Target[i][j];
  		}
  	}

  	for (i = 0; i < height; i++) {
  		for (j = 0; j < width; j++) {
  			if (Target[i][j] >= max)
  				max = Target[i][j];
  		}
  	}

  	max = max - min;

  	for (i = 0; i < height; i++) {
  		for (j = 0; j < width; j++) {
  			Target[i][j] = (Target[i][j] - min) * (255. / max);
  		}
  	}

  	// TODO: 여기에 구현 코드 추가.
  	return Target;
  }
  ```
  - Doc Image2DMem() 작성
  ```c
  double** CMFCApplication05111Doc::Image2DMem(int height, int width)
  {
  	double** temp;
  	int i, j;
  	temp = new double *[height];
  	for (i = 0; i < height; i++) {
  		temp[i] = new double[width];
  	}

  	for (i = 0; i < height; i++) {
  		for (j = 0; j < width; j++) {
  			temp[i][j] = 0.0;
  		}
  	}
  	return temp;

  	// TODO: 여기에 구현 코드 추가.
  }
  ```
  - View OnEmbossing() 작성
  - 실행화면(이미지링크)


### 블러링  처리
* 영상의 세밀한 부분을 제거하여 영상을 흐리게 하거나 부드럽게 하는 기술
* 영상의 세밀한 부분은 주파수 축에서 보면 고주파 성분인데, 블러링은 이 고주파 성분을 제거해 줌.
* 사용하는 가중치의 회선 마스크는 저역통과 필터(Low Pass Filter)가 됨
* 블러링 회선 마스크는 모든 계수가 양수로 전체 합은 1
* 실행하기
  - 메뉴 추가
  - 클래스 마법사를 통해 View와 Doc에 OnBlurr 함수 생성.
  - Doc OnBlurr() 작성
  ```c
  void CMFCApplication05111Doc::OnBlurr()
  {
  	int i, j;
  	double BlurrMask[3][3] = { {1. / 9., 1. / 9., 1. / 9.},
  		{1. / 9., 1. / 9., 1. / 9.}, {1. / 9., 1. / 9., 1. / 9.} };

  	m_Re_height = m_height;
  	m_Re_width = m_width;
  	m_Re_size = m_Re_height * m_Re_width;

  	m_OutputImage = new unsigned char[m_Re_size];
  	m_tempImage = OnMaskProcess(m_InputImage, BlurrMask);

  	for (i = 0; i < m_Re_height; i++) {
  		for (j = 0; j < m_Re_width; j++) {
  			if (m_tempImage[i][j] > 255.)
  				m_tempImage[i][j] = 255.;
  			if (m_tempImage[i][j] < 0.)
  				m_tempImage[i][j] = 0.;
  		}
  	}

  	for (i = 0; i < m_Re_height; i++) {
  		for (j = 0; j < m_Re_width; j++) {
  			m_OutputImage[i*m_Re_width + j]
  				= (unsigned char)m_tempImage[i][j];
  		}
  	}
  	// TODO: 여기에 구현 코드 추가.
  }
  ```
  - View OnBlurr() 작성
  - 실행화면(이미지링크)



### 가우시안 필터 처리
* 영상의 세세한 부분을 제거하여 부드럽게 하므로 스무딩(Smoothing) 처리라고도 함
* 스무딩 처리에 사용되는 대표적인 저역통과 필터로 가우시안 필터(Gaussian Filter)가 있음
* σ 값이 클을 수록 * 은 저주파 성분만 통과시킴.
* 실행하기
  - 상수값 입력 대화상자 생성.
  - 메뉴 추가
  - 클래스 마법사를 통해 View와 Doc에 OnGaussianFilter 함수 생성.
  - Doc OnGaussianFilter() 작성
  ```c
  void CMFCApplication05111Doc::OnGaussianFilter()
  {
  	int i, j;
  	double GaussianMask[3][3] = { {1. / 16., 1. / 8., 1. / 16.},
  		{1. / 8., 1. / 4., 1. / 8.}, {1. / 16., 1. / 8., 1. / 16.} };

  	m_Re_height = m_height;
  	m_Re_width = m_width;
  	m_Re_size = m_Re_height * m_Re_width;

  	m_OutputImage = new unsigned char[m_Re_size];

  	m_tempImage = OnMaskProcess(m_InputImage, GaussianMask);

  	for (i = 0; i < m_Re_height; i++) {
  		for (j = 0; j < m_Re_width; j++) {
  			if (m_tempImage[i][j] > 255.)
  				m_tempImage[i][j] = 255.;
  			if (m_tempImage[i][j] < 0.)
  				m_tempImage[i][j] = 0.;
  		}
  	}

  	for (i = 0; i < m_Re_height; i++) {
  		for (j = 0; j < m_Re_width; j++) {
  			m_OutputImage[i*m_Re_width + j]
  				= (unsigned char)m_tempImage[i][j];
  		}
  	}

  	// TODO: 여기에 구현 코드 추가.
  }
  ```
  - View OnGaussianFilter() 작성
  - 실행화면(이미지링크)


### 샤프닝 처리  
* 블러링과는 반대로 디지털 영상에서 상세한 부분을 더욱 강조하여 표현
* 영상의 상세한 부분은 고주파 성분이므로 영상에서 저주파 성분만 제거하면 샤프닝 효과를 얻을 수 있음
* 사용되는 가중치의 회선 마스크는 고역통과 필터(High Pass Filter)가 됨
* 흐린 영상을 개선하여 선명한 영상을 생성하는 데 주로 사용됨.
* 실행하기
  - 메뉴 추가
  - 클래스 마법사를 통해 View와 Doc에 OnSharpening 함수 생성.
  - Doc OnSharpening() 작성
  ```c
  void CMFCApplication05111Doc::OnSharpning()
  {
  	int i, j;
  	//double SharpeningMask[3][3] = {{-1., -1., -1.}, {-1., 9., -1.}, {-1., -1., -1.}};
  	double SharpeningMask[3][3] = { {0., -1., 0.}, {-1., 5.,
  		-1.}, {0., -1., 0.} };

  	m_Re_height = m_height;
  	m_Re_width = m_width;
  	m_Re_size = m_Re_height * m_Re_width;

  	m_OutputImage = new unsigned char[m_Re_size];

  	m_tempImage = OnMaskProcess(m_InputImage, SharpeningMask);
  	// m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);

  	for (i = 0; i < m_Re_height; i++) {
  		for (j = 0; j < m_Re_width; j++) {
  			if (m_tempImage[i][j] > 255.)
  				m_tempImage[i][j] = 255.;
  			if (m_tempImage[i][j] < 0.)
  				m_tempImage[i][j] = 0.;
  		}
  	}

  	for (i = 0; i < m_Re_height; i++) {
  		for (j = 0; j < m_Re_width; j++) {
  			m_OutputImage[i*m_Re_width + j]
  				= (unsigned char)m_tempImage[i][j];
  		}
  	}
  	// TODO: 여기에 구현 코드 추가.
  }
  ```
  - View OnSharpening() 작성
  - 실행화면(이미지링크)

### 고주파 필터 샤프닝 처리
* 고주파 필터는 영상 신호 성분 중 고주파 성분은 통과시키고 저주파 성분은 차단
* 필터 계수의 합은 0으로 샤프닝 회선 마스크하고는 다르나, 나머지 동작 특성은 같음.
* 가운데 큰 양수 값과 주변의 작은 음수 값으로 마스크되어 경계선을 더욱 두드러지게 함.
* 실행하기
  - 메뉴 추가
  - 클래스 마법사를 통해 View와 Doc에 OnHpfSharp 함수 생성.
  - Doc OnHpfSharp() 작성
  ```c
  void CMFCApplication05111Doc::OnHprSharp()
  {
  	int i, j;
  	double HpfSharpMask[3][3] = { {-1. / 9., -1. / 9., -1. / 9.},
  		{-1. / 9., 8. / 9., -1. / 9.}, {-1. / 9., -1. / 9., -1. / 9.} };

  	m_Re_height = m_height;
  	m_Re_width = m_width;
  	m_Re_size = m_Re_height * m_Re_width;

  	m_OutputImage = new unsigned char[m_Re_size];

  	m_tempImage = OnMaskProcess(m_InputImage, HpfSharpMask);
  	m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);

  	for (i = 0; i < m_Re_height; i++) {
  		for (j = 0; j < m_Re_width; j++) {
  			if (m_tempImage[i][j] > 255.)
  				m_tempImage[i][j] = 255.;
  			if (m_tempImage[i][j] < 0.)
  				m_tempImage[i][j] = 0.;
  		}
  	}

  	for (i = 0; i < m_Re_height; i++) {
  		for (j = 0; j < m_Re_width; j++) {
  			m_OutputImage[i*m_Re_width + j]
  				= (unsigned char)m_tempImage[i][j];
  		}
  	}

  	// TODO: 여기에 구현 코드 추가.
  }
  ```
  - View OnHpfSharp() 작성
  - 실행화면(이미지링크)


### 저주파 필터 샤프닝 처리
* 저주파 필터는 영상 신호 성분 중 저주파 성분은 통과시키고 고주파 성분은 차단
* 원본 영상에서 저주파 통과 필터를 통과한 결과 영상을 뺄셈하여 얻는데, 이를 언샤프 마스킹(Unsharp Masking) = 고주파 통과 필터 결과 영상
* 실행하기
  - 상수값 입력 대화상자 생성.
  - 메뉴 추가
  - 클래스 마법사를 통해 View와 Doc에 OnLpfSharp 함수 생성.
  - Doc OnLpfSharp() 작성
  ```c
  void CMFCApplication05111Doc::OnLpfSharp()
  {
  	CConstantDlg dlg;

  	int i, j, alpha;
  	double LpfSharpMask[3][3] = { {1. / 9., 1. / 9., 1. / 9.},
  		{1. / 9., 1. / 9., 1. / 9.}, {1. / 9., 1. / 9., 1. / 9.} };

  	m_Re_height = m_height;
  	m_Re_width = m_width;
  	m_Re_size = m_Re_height * m_Re_width;

  	m_OutputImage = new unsigned char[m_Re_size];

  	if (dlg.DoModal() == IDOK) {
  		alpha = (int)dlg.m_Constant;
  	}

  	m_tempImage = OnMaskProcess(m_InputImage, LpfSharpMask);

  	for (i = 0; i < m_height; i++) {
  		for (j = 0; j < m_width; j++) {
  			m_tempImage[i][j] = (alpha * m_InputImage
  				[i*m_width + j]) - (unsigned char)m_tempImage[i][j];
  		}
  	}
  	m_tempImage = OnScale(m_tempImage, m_Re_height, m_Re_width);
  	for (i = 0; i < m_Re_height; i++) {
  		for (j = 0; j < m_Re_width; j++) {
  			if (m_tempImage[i][j] > 255.)
  				m_tempImage[i][j] = 255.;
  			if (m_tempImage[i][j] < 0.)
  				m_tempImage[i][j] = 0.;
  		}
  	}

  	for (i = 0; i < m_Re_height; i++) {
  		for (j = 0; j < m_Re_width; j++) {
  			m_OutputImage[i*m_Re_width + j]
  				= (unsigned char)m_tempImage[i][j];
  		}
  	}
  	// TODO: 여기에 구현 코드 추가.
  }
  ```
  - View OnLpfSharp() 작성
  - 실행화면(이미지링크)
