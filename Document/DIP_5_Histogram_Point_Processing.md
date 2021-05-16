## DIP_Histogram_Point_Processing

### 히스토그램 스트레칭
* 명암 대비를 향상시키는 연산으로, 낮은 명암 대비를 보이는 영상의 화질을 향상시키는 방법
* 명암 대비 스트레칭이라고도 함.
* 히스토그램이 모든 범위의 화소 값을 포함하도록 히스토그램의 분포를 넓힘.
* 실행하기
 - 메뉴 추가
 - 클래스 마법사를 통해 View와 Doc에 OnHistoStretch 함수 생성.
 - Doc OnHistoStretch() 작성
 ```c
 void CMFCApplication05111Doc::OnHistoStretch()
 {
 	int i;
 	unsigned char LOW, HIGH, MAX, MIN;

 	m_Re_height = m_height;
 	m_Re_width = m_width;
 	m_Re_size = m_Re_height * m_Re_width;

 	m_OutputImage = new unsigned char[m_Re_size];

 	LOW = 0;
 	HIGH = 255;

 	MIN = m_InputImage[0];
 	MAX = m_InputImage[0];

 	for (i = 0; i < m_size; i++) {
 		if (m_InputImage[i] < MIN)
 			MIN = m_InputImage[i];
 	}

 	for (i = 0; i < m_size; i++) {
 		if (m_InputImage[i] > MAX)
 			MAX = m_InputImage[i];
 	}

 	m_OutputImage = new unsigned char[m_Re_size];

 	for (i = 0; i < m_size; i++)
 		m_OutputImage[i] = (unsigned char)((m_InputImage[i] - MIN)*HIGH / (MAX - MIN));

 	// TODO: 여기에 구현 코드 추가.
 }
 ```
 - View OnHistoStretch() 작성
 - 실행화면(이미지링크)

### 앤드-인 탐색
 * 명암 대비를 향상시키는 연산으로, 낮은 명암 대비를 보이는 영상의 화질을 향상시키는 방법
 * 앤드-인 탐색 수행 공식: 두 개의 임계 값(low, high) 사용
 * 실행하기
  - 메뉴 추가
  - 클래스 마법사를 통해 View와 Doc에 OnEndInSearch 함수 생성.
  - Doc OnEndInSearch() 작성
  ```c
  void CMFCApplication05111Doc::OnEndInSearch()
  {
  	int i;
  	unsigned char LOW, HIGH, MAX, MIN;

  	m_Re_height = m_height;
  	m_Re_width = m_width;
  	m_Re_size = m_Re_height * m_Re_width;

  	m_OutputImage = new unsigned char[m_Re_size];

  	LOW = 0;
  	HIGH = 255;

  	MIN = m_InputImage[0];
  	MAX = m_InputImage[0];

  	for (i = 0; i < m_size; i++) {
  		if (m_InputImage[i] < MIN)
  			MIN = m_InputImage[i];
  	}

  	for (i = 0; i < m_size; i++) {
  		if (m_InputImage[i] > MAX)
  			MAX = m_InputImage[i];
  	}

  	m_OutputImage = new unsigned char[m_Re_size];

  	for (i = 0; i < m_size; i++) {
  		if (m_InputImage[i] <= MIN) {
  			m_OutputImage[i] = 0;
  		}
  		else if (m_InputImage[i] >= MAX) {
  			m_OutputImage[i] = 255;
  		}
  		else
  			m_OutputImage[i] = (unsigned char)((m_InputImage[i] - MIN)*HIGH / (MAX - MIN));
  	}
  	// TODO: 여기에 구현 코드 추가.
  }
  ```
  - View OnEndInSearch() 작성
  - 실행화면(이미지링크)


### 히스토그램 출력
  * 관찰한 데이터의 특징을 한눈에 알아볼 수 있도록 데이터를 막대그래프 모양으로 나타낸 것
  * 디지털 영상에 대한 많은 정보를 제공함.
  * 실행하기
    - 메뉴 추가
    - 클래스 마법사를 통해 View와 Doc에 OnHistogram 함수 생성.
    - doc 전역변수 선언(double m_HIST[256], double m_Sum_Of_HIST[256], unsigned char m_Scale_HIST[256])
    - Doc OnHistogram() 작성
    ```c
    void CMFCApplication05111Doc::OnHistogram()
    {
    	int i, j, value;
    	unsigned char LOW, HIGH;
    	double MAX, MIN, DIF;

    	m_Re_height = 256;
    	m_Re_width = 256;
    	m_Re_size = m_Re_height * m_Re_width;

    	LOW = 0;
    	HIGH = 255;

    	for (i = 0; i < 256; i++)
    		m_HIST[i] = LOW;

    	for (i = 0; i < m_size; i++) {
    		value = (int)m_InputImage[i];
    		m_HIST[value]++;
    	}

    	MIN = m_HIST[0];
    	MAX = m_HIST[0];

    	for (i = 0; i < 256; i++) {
    		if (m_HIST[i] > MAX)
    			MAX = m_HIST[i];
    	}

    	for (i = 0; i < 256; i++) {
    		if (m_HIST[i] < MIN)
    			MIN = m_HIST[i];
    	}

    	DIF = MAX - MIN;

    	for (i = 0; i < 256; i++)
    		m_Scale_HIST[i] = (unsigned char)((m_HIST[i] - MIN) * HIGH / DIF);

    	m_OutputImage = new unsigned char[m_Re_size + (256 * 20)];

    	for (i = 0; i < m_Re_size; i++)
    		m_OutputImage[i] = 255;

    	for (i = 0; i < 256; i++) {
    		for (j = 0; j < m_Scale_HIST[i]; j++) {
    			m_OutputImage[m_Re_width*(m_Re_height - j - 1) + i] = 0;
    		}
    	}

    	for (i = m_Re_height; i < m_Re_height + 5; i++) {
    		for (j = 0; j < 256; j++) {
    			m_OutputImage[m_Re_height * i + j] = 255;
    		}
    	}

    	for (i = m_Re_height + 5; i < m_Re_height + 20; i++) {
    		for (j = 0; j < 256; j++) {
    			m_OutputImage[m_Re_height * i + j] = j;
    		}
    	}

    	m_Re_height = m_Re_height + 20;
    	m_Re_size = m_Re_height * m_Re_width;

    	// TODO: 여기에 구현 코드 추가.
    }
    ```
    - View OnHistogram() 작성
    - 실행화면(이미지링크)


### 히스토그램 평활화
  * 어둡게 촬영된 영상의 히스토그램을 조절하여 명암 분포가 빈약한 영상을 균일하게 만들어 줌.
  * 영상의 밝기 분포를 재분배하여 명암 대비를 최대화
  * 명암 대비 조정을 자동으로 수행, 각 명암의 빈도는 변경하지 않음.
  * 검출 특성이 좋은 영상만 출력하지는 않지만 영상의 검출 특성을 증가시킴
  * 3단계
    - 1단계: 명암 값 j의 빈도 수 hist[j]를 계산해 입력 영상의 히스토그램 생성
    - 2단계: 각 명암 값 i에서 0~i까지의 누적 빈도 수(누적합)를 계산
    - 3단계: 2단계에서 구한 누적 빈도 수를 정규화(정규화 누적합)
  * 실행하기
    - 메뉴 추가
    - 클래스 마법사를 통해 View와 Doc에 OnHistoEqual 함수 생성.
    - Doc OnHistoEqual() 작성
    ```c
    void CMFCApplication05111Doc::OnHistoEqual()
    {
    	int i, value;
    	unsigned char LOW, HIGH, Temp;
    	double SUM = 0.0;

    	m_Re_height = m_height;
    	m_Re_width = m_width;
    	m_Re_size = m_Re_height * m_Re_width;

    	LOW = 0;
    	HIGH = 255;

    	for (i = 0; i < 256; i++)
    		m_HIST[i] = LOW;

    	for (i = 0; i < m_size; i++) {
    		value = (int)m_InputImage[i];
    		m_HIST[value]++;
    	}

    	for (i = 0; i < 256; i++) {
    		SUM += m_HIST[i];
    		m_Sum_Of_HIST[i] = SUM;  //누적합 히스토그램
    	}

    	m_OutputImage = new unsigned char[m_Re_size];

    	for (i = 0; i < m_size; i++) {
    		Temp = m_InputImage[i];
    		m_OutputImage[i] = (unsigned char)(m_Sum_Of_HIST[Temp] * HIGH / m_size);
    		//m_OutputImage[i] = m_Sum_Of_HIST[Temp];
    	}
    	// TODO: 여기에 구현 코드 추가.
    }
    ```
    - View OnHistoEqual() 작성
    - 실행화면(이미지링크)


### 히스토그램 명세화
* 특정 모양의 히스토그램을 생성된 디지털 영상의 히스토그램에 포함하여 영상의 일부 영역의 명암 대비(콘트라스트)를 개선하는 영상처리 기법
* 입력 영상의 히스토그램을 원하는 히스토그램으로 변환한다고 해서 히스토그램 정합(Histogram Matching) 기법
* 특정 부분을 향상시키려고 원하는 히스토그램을 이용한 정합으로 일부 영역에서만 명암 대비를 개선
* 기본적으로 입력 영상을 원하는 히스토그램으로 평활화하고 역 히스토그램 평활화 수행 → 룩업테이블(lookup table)을 생성하고 평활화된 원 영상을 역 변환하여 원하는 히스토그램을 얻음.
* 5단계 과정
  - 1단계: 히스토그램 생성
  - 2단계: 입력 영상의 평활화
  - 3단계: 원하는 히스토그램을 평활화하여 분포가 균일한 히스토그램을 만듦.
  - 4단계: 평활화된 히스토그램을 역 평활화하는 과정. 평활화와 반대로 정규화된 누적합이 명도 값이 되고, 명도 값은 역 평활화 값이 됨. 역 평활화 값이 역함수로서 룩업테이블로 사용됨.
  - 5단계: 역변환 함수를 이용해 입력 영상을 원하는 히스토그램으로 만들어 줌.

* 실행하기
  - 메뉴 추가
  - 클래스 마법사를 통해 View와 Doc에 OnHistoSpec 함수 생성.
  - Doc OnHistoSpec() 작성
  ```c
  void CMFCApplication05111Doc::OnHistoSpec()
  {
  	int i, value, Dvalue, top, bottom, DADD;
  	unsigned char *m_DTEMP = { 0 };
  	unsigned char  m_Sum_Of_ScHIST[256], m_TABLE[256];
  	unsigned char LOW, HIGH, Temp, *m_Org_Temp;
  	double m_DHIST[256], m_Sum_Of_DHIST[256], SUM = 0.0, DSUM = 0.0;
  	double DMAX, DMIN;

  	top = 255;
  	bottom = top - 1;

  	m_Re_height = m_height;
  	m_Re_width = m_width;
  	m_Re_size = m_Re_height * m_Re_width;

  	m_OutputImage = new unsigned char[m_Re_size];
  	m_Org_Temp = new unsigned char[m_size];

  	CFile File;
  	CFileDialog OpenDlg(TRUE);

  	if (OpenDlg.DoModal() == IDOK) {
  		File.Open(OpenDlg.GetPathName(), CFile::modeRead | CFile::typeBinary);

  		if (File.GetLength() == (unsigned)m_size) {
  			m_DTEMP = new unsigned char[m_size];
  			File.Read(m_DTEMP, m_size);
  			File.Close();
  		}
  		else {
  			AfxMessageBox(L"Image size not matched");
  			return;
  		}
  	}

  	LOW = 0;
  	HIGH = 255;

  	for (i = 0; i < 256; i++) {
  		m_HIST[i] = LOW;
  		m_DHIST[i] = LOW;
  		m_TABLE[i] = LOW;
  	}

  	for (i = 0; i < m_size; i++) {
  		value = (int)m_InputImage[i];
  		m_HIST[value]++;
  		Dvalue = (int)m_DTEMP[i];
  		m_DHIST[Dvalue]++;
  	}

  	for (i = 0; i < 256; i++) {
  		SUM += m_HIST[i];
  		m_Sum_Of_HIST[i] = SUM;
  		DSUM += m_DHIST[i];
  		m_Sum_Of_DHIST[i] = DSUM;
  	}

  	for (i = 0; i < m_size; i++) {
  		Temp = m_InputImage[i];
  		m_Org_Temp[i] = (unsigned char)(m_Sum_Of_HIST[Temp] * HIGH / m_size);
  	}

  	DMIN = m_Sum_Of_DHIST[0];
  	DMAX = m_Sum_Of_DHIST[255];

  	for (i = 0; i < 256; i++) {
  		m_Sum_Of_ScHIST[i] = (unsigned char)((m_Sum_Of_DHIST[i]
  			- DMIN)*HIGH / (DMAX - DMIN));
  	}

  	for (; ; ) {
  		for (i = m_Sum_Of_ScHIST[bottom];
  			i <= m_Sum_Of_ScHIST[top]; i++) {
  			m_TABLE[i] = top;
  		}

  		top = bottom;
  		bottom = bottom - 1;

  		if (bottom < -1)
  			break;
  	}

  	for (i = 0; i < m_size; i++) {
  		DADD = (int)m_Org_Temp[i];
  		m_OutputImage[i] = m_TABLE[DADD];
  	}

  	// TODO: 여기에 구현 코드 추가.
  }
  ```
  - View OnHistoSpec() 작성
  - 실행화면(이미지링크)
