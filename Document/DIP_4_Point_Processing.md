## DIP_Point_Processing

### 화소점 처리
* 원 화소의 값이나 위치를 바탕으로 단일 화소 값을 변경하는 기술
* 다른 화소의 영향을 받지 않고 단순히 화소 점의 값만 변경.
* 산술연산, 논리연산, 반전, 광도 보정, 히스토그램 평활화, 명암 대비 스트레칭 등 기법이 있다.



### 덧셈연산
* 화소의 밝기 값에 특정한 상수 값을 더해 화소의 밝기 값을 증가시켜 영상을 밝게 하는 처리 기술
* 화소의 최대값 넘을 수 있기 때문에 예외처리 해야함.
* 실행하기
  - 상수값 입력 대화상자 생성.
  - 메뉴 추가
  - 클래스 마법사를 통해 View와 Doc에 OnSumConstant 함수 생성.
  - Doc OnSumConstant() 작성
  ```c
void CMFCApplication05111Doc::OnSumConstant()
{
	CConstantDlg dlg;

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] + dlg.m_Constant >= 255)
				m_OutputImage[i] = 255;
			else
				m_OutputImage[i] = (unsigned char)(m_InputImage[i] + dlg.m_Constant);
		}
	}
	// TODO: 여기에 구현 코드 추가.
}
  ```
  - View OnSumConstant() 작성
  - 실행화면(이미지링크)



### 뺄셈연산
* 화소의 밝기 값에 특정한 상수 값을 빼 화소의 밝기 값을 감소시켜 영상의 밝기를 어둡게 하는 처리 기술
* 화소의 최소값을 넘을 수 있기 때문에 예외 처리 해야 함.
* 실행하기
  - 상수값 입력 대화상자 생성.
  - 메뉴 추가
  - 클래스 마법사를 통해 View와 Doc에 OnSubConstant 함수 생성.
  - Doc OnSubConstant() 작성
  ```c
  void CMFCApplication05111Doc::OnSubConstant()
  {
  	CConstantDlg dlg;

  	int i;

  	m_Re_height = m_height;
  	m_Re_width = m_width;
  	m_Re_size = m_Re_height * m_Re_width;

  	m_OutputImage = new unsigned char[m_Re_size];

  	if (dlg.DoModal() == IDOK) {
  		for (i = 0; i < m_size; i++) {
  			if (m_InputImage[i] - dlg.m_Constant < 0)
  				m_OutputImage[i] = 0;
  			else
  				m_OutputImage[i]
  				= (unsigned char)(m_InputImage[i] - dlg.m_Constant);
  		}
  	}

  	// TODO: 여기에 구현 코드 추가.
  }
  ```
  - View OnSubConstant() 작성
  - 실행화면(이미지링크)


### 곱셈연산
* 화소의 밝기 값에 특정 상수 값을 곱해 전체적으로 화소의 밝기 값이 증가해 더 밝아짐.
* 밝은 부분은 더욱 밝아지고, 어두운 부분은 약간 밝아져 영상 내의 밝기에 커다란 차이가 생기는 것
* 밝기의 차이가 커지므로 영상의 선명도 증가함.
* 실행하기
  - 상수값 입력 대화상자 생성.
  - 메뉴 추가
  - 클래스 마법사를 통해 View와 Doc에 OnMulConstant 함수 생성.
  - Doc OnMulConstant() 작성
  ```c
  void CMFCApplication05111Doc::OnMulConstant()
  {
  	CConstantDlg dlg;

  	int i;

  	m_Re_height = m_height;
  	m_Re_width = m_width;
  	m_Re_size = m_Re_height * m_Re_width;

  	m_OutputImage = new unsigned char[m_Re_size];

  	if (dlg.DoModal() == IDOK) {
  		for (i = 0; i < m_size; i++) {
  			if (m_InputImage[i] * dlg.m_Constant > 255)
  				m_OutputImage[i] = 255;
  			else if (m_InputImage[i] * dlg.m_Constant < 0)
  				m_OutputImage[i] = 0;
  			else
  				m_OutputImage[i]
  				= (unsigned char)(m_InputImage[i] * dlg.m_Constant);
  		}
  	}
  	// TODO: 여기에 구현 코드 추가.
  }
  ```
  - View OnMulConstant() 작성
  - 실행화면(이미지링크)



### 나눗셈연산
* 화소 값을 임의의 상수 값으로 나누면 전체적으로 화소의 밝기 값은 감소하고, 최대 밝기와 최소 밝기의 차이는 작아짐.
* 밝은 부분은 많이 어두워지고, 어두운 부분은 약간 어두워짐.
* 실행하기
  - 상수값 입력 대화상자 생성.
  - 메뉴 추가
  - 클래스 마법사를 통해 View와 Doc에 OnDivConstant 함수 생성.
  - Doc OnDivConstant() 작성
  ```c
  void CMFCApplication05111Doc::OnDivConstant()
  {
  	CConstantDlg dlg;

  	int i;

  	m_Re_height = m_height;
  	m_Re_width = m_width;
  	m_Re_size = m_Re_height * m_Re_width;

  	m_OutputImage = new unsigned char[m_Re_size];

  	if (dlg.DoModal() == IDOK) {
  		for (i = 0; i < m_size; i++) {
  			if (m_InputImage[i] / dlg.m_Constant > 255)
  				m_OutputImage[i] = 255;
  			else if (m_InputImage[i] / dlg.m_Constant < 0)
  				m_OutputImage[i] = 0;
  			else
  				m_OutputImage[i]
  				= (unsigned char)(m_InputImage[i] / dlg.m_Constant);
  		}
  	}

  	// TODO: 여기에 구현 코드 추가.
  }
  ```
  - View OnDivConstant() 작성
  - 실행화면(이미지링크)


### AND 연산
* 영상의 특정 화소 비트에서 0으로 구성된 이진 데이터와 AND 연산을 수행
* 원하는 비트를 선택적으로 0으로 만드는 기능이 있어 마스크(mask) 연산이라고도 함
* 실행하기
  - 상수값 입력 대화상자 생성.
  - 메뉴 추가
  - 클래스 마법사를 통해 View와 Doc에 OnAndOperate 함수 생성.
  - Doc OnAndOperate() 작성
  ```c
  void CMFCApplication05111Doc::OnAndOperate()
{
	CConstantDlg dlg;

	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if ((m_InputImage[i] & (unsigned char)dlg.m_Constant) >= 255)
			{
				m_OutputImage[i] = 255;
			}
			else if ((m_InputImage[i] & (unsigned char)dlg.m_Constant) < 0)
			{
				m_OutputImage[i] = 0;
			}
			else {
				m_OutputImage[i] = (m_InputImage[i]
					& (unsigned char)dlg.m_Constant);
			}
		}
	}

	// TODO: 여기에 구현 코드 추가.
}
  ```
  - View OnAndOperate() 작성
  - 실행화면(이미지링크)




### OR 연산
* 화소의 특정 비트를 1로 만들려고 원하는 비트 위치가 1로 구성된 이진 데이터와 OR 연산을 수행
* 특정 비트를 선택적으로 1로 구성할 수 있어 선택적-세트(selective-set)연산이라고도 함
* 실행하기
  - 상수값 입력 대화상자 생성.
  - 메뉴 추가
  - 클래스 마법사를 통해 View와 Doc에 OnOrOperate 함수 생성.
  - Doc OnOrOperate() 작성
  ```c
  void CMFCApplication05111Doc::OnOrOperate()
  {
  	CConstantDlg dlg;
  	int i;

  	m_Re_height = m_height;
  	m_Re_width = m_width;
  	m_Re_size = m_Re_height * m_Re_width;

  	m_OutputImage = new unsigned char[m_Re_size];

  	if (dlg.DoModal() == IDOK) {
  		for (i = 0; i < m_size; i++) {
  			if ((m_InputImage[i] | (unsigned char)dlg.m_Constant) >= 255) {
  				m_OutputImage[i] = 255;
  			}
  			else if ((m_InputImage[i] | (unsigned char)dlg.m_Constant) < 0) {
  				m_OutputImage[i] = 0;
  			}
  			else {
  				m_OutputImage[i] = (m_InputImage[i] | (unsigned char)dlg.m_Constant);
  			}
  		}
  	}
  	// TODO: 여기에 구현 코드 추가.
  }
  ```
  - View OnOrOperate() 작성
  - 실행화면(이미지링크)



### XOR 연산
* 입력이 서로 다를 때만 1을 출력하는 연산으로, 두 데이터를 비교하므로 비교(compare)연산이라고도 함.
* 같은 비트에서만 0을 출력함.
* 실행하기
  - 상수값 입력 대화상자 생성.
  - 메뉴 추가
  - 클래스 마법사를 통해 View와 Doc에 OnXorOperate 함수 생성.
  - Doc OnXorOperate() 작성
  ```c
  void CMFCApplication05111Doc::OnXorOperate()
  {
  	CConstantDlg dlg;
  	int i;

  	m_Re_height = m_height;
  	m_Re_width = m_width;
  	m_Re_size = m_Re_height * m_Re_width;

  	m_OutputImage = new unsigned char[m_Re_size];

  	if (dlg.DoModal() == IDOK) {
  		for (i = 0; i < m_size; i++) {
  			if ((m_InputImage[i] ^ (unsigned char)dlg.m_Constant) >= 255) {
  				m_OutputImage[i] = 255;
  			}
  			else if ((m_InputImage[i] ^ (unsigned char)dlg.m_Constant) < 0) {
  				m_OutputImage[i] = 0;
  			}
  			else {
  				m_OutputImage[i] = (m_InputImage[i] ^ (unsigned char)dlg.m_Constant);
  			}
  		}
  	}
  	// TODO: 여기에 구현 코드 추가.
  }
    ```
  - View OnXorOperate() 작성
  - 실행화면(이미지링크)





### NOT 연산
* 화소 비트를 반전시키는 일을 함.
* 영상에서는 검정색이 흰색으로, 흰색이 검정색으로 반전됨.
* 실행하기
  - 상수값 입력 대화상자 생성.
  - 메뉴 추가
  - 클래스 마법사를 통해 View와 Doc에 OnNegaTransform 함수 생성.
  - Doc OnNegaTransform() 작성
  ```c
  void CMFCApplication05111Doc::OnNegaTransform()
  {
  	CConstantDlg dlg;
  	int i;

  	m_Re_height = m_height;
  	m_Re_width = m_width;
  	m_Re_size = m_Re_height * m_Re_width;

  	m_OutputImage = new unsigned char[m_Re_size];

  	for (i = 0; i < m_size; i++)
  		m_OutputImage[i] = 255 - m_InputImage[i];
  	// TODO: 여기에 구현 코드 추가.
  }
      ```
  - View OnNegaTransform() 작성
  - 실행화면(이미지링크)



### 감마 보정
* 입력 값을 조정하여 출력을 제대로 만드는 과정
* 함수의 감마 값에 따라 영상을 밝게 하거나 흐리게 조절할 수 있음
* 감마 값이 1보다 크면 영상이 어두워지고, 1보다 작으면 영상이 밝아짐
* 실행하기
  - 상수값 입력 대화상자 생성.
  - 메뉴 추가
  - 클래스 마법사를 통해 View와 Doc에 OnGammaCorrection 함수 생성.
  - Doc OnGammaCorrection() 작성
  ```c
  void CMFCApplication05111Doc::OnGammaCorrection()
  {
  	CConstantDlg dlg;
  	int i;
  	double temp;
    
  	m_Re_height = m_height;
  	m_Re_width = m_width;
  	m_Re_size = m_Re_height * m_Re_width;

  	m_OutputImage = new unsigned char[m_Re_size];

  	if (dlg.DoModal() == IDOK) {
  		for (i = 0; i < m_size; i++) {
  			temp = pow(m_InputImage[i], 1 / dlg.m_Constant);
  			if (temp < 0)
  				m_OutputImage[i] = 0;
  			else if (temp > 255)
  				m_OutputImage[i] = 255;
  			else
  				m_OutputImage[i] = (unsigned char)temp;
  		}
  	}

  	// TODO: 여기에 구현 코드 추가.
  }
      ```
  - View OnGammaCorrection() 작성
  - 실행화면(이미지링크)

### 영상 이진화
* 영상의 화소 값을 경계 값을 이용해 값이 두 개만 있는 영상으로 변환해 주는 것
* 실행하기
  - 상수값 입력 대화상자 생성.
  - 메뉴 추가
  - 클래스 마법사를 통해 View와 Doc에 OnBinarization 함수 생성.
  - Doc OnBinarization() 작성
  ```c
  void CMFCApplication05111Doc::OnBinarization()
{
	CConstantDlg dlg;
	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] >= dlg.m_Constant)
				m_OutputImage[i] = 255;
			else
				m_OutputImage[i] = 0;
		}
	}
	// TODO: 여기에 구현 코드 추가.
}
      ```
  - View OnBinarization() 작성
  - 실행화면(이미지링크)

### 범위 강조 변환
* 영상에서 한 부분의 화소는 원 상태를 그대로 유지한 채 일정 범위의 화소만 강조하는 변환
* 실행하기
  - 상수값 범위 입력 대화상자 생성.
  - 메뉴 추가
  - 클래스 마법사를 통해 View와 Doc에 OnStressTransform 함수 생성.
  - Doc OnStressTransform() 작성
  ```c
  void CMFCApplication05111Doc::OnStressTransform()
{
	CConstantDlg dlg;
	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] >= dlg.m_Constant)
				m_OutputImage[i] = 255;
			else
				m_OutputImage[i] = 0;
		}
	}
	// TODO: 여기에 구현 코드 추가.
}
      ```
  - View OnStressTransform() 작성
  - 실행화면(이미지링크)
