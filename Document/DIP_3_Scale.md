## DIP_Scale

### MFC메뉴버튼 만들기
* 리소스 뷰에서 [프로젝트]-[메뉴]-[IDR_프로젝트이름TYPE] 더블클릭.
* 빈칸 위치에 클릭. 속성에서 Caption을 수정해 원해는 문자표현 가능
* 해당 메뉴 아래에도 같은 방법으로 바로가기 매뉴 만들기.(ID, Caption 설정)

### MFC 메뉴와 뷰 커맨드 연결
* 클래스 마법사 열기. 뷰클래스 선택.
* ID에서 생성한 바로가기메뉴ID 선택, 메세지 유형 COMMAND 선택하여 처리기 추가.

### MFC 다이얼로그 생성
* 리소스 뷰에서 [프로젝트]-[다이얼로그] 폴더 선택. 우클릭해서 새 다이얼로그 추가.
* 도구 상자를 통해 대화상자에 숫자를 입력 받을 수 있도록 대화상자 편집.
* 각각의 ID, Caption을 설정 해주어야 함.
* 추가된 대화상자를 추가하기위해 클래스위자드에서 클래스추가 옆 화살표를 눌러 MFC클래스 생성. 생성시 클래스 이름앞에 'C'를 반드시 붙여줘야 함. base class= CDialog 설정. Dialog ID는 적용할 대화상자 ID.
* 만들어진 대화상자 클래스를 클래스마법사를 통해 멤버변수를 Control ID를 EDIT ID로 설정하여 생성.
* 추가된 대화상자를 사용하기 위해 프로젝트Doc.cpp 파일의 윗부분에 해당 대화상자 헤더 선언.




#### DownSampling  이미지 축소
* 디지털 영상을 축소하기.
* 원 영상의 값을 일정한 좌표 단위로 버리는 것.
* 실행하기
	- 다운샘플링 메뉴 추가
	- 프로젝트뷰에 해당 메뉴 커멘드 처리기 추가.(클래스 마법사)
	- 샘플링 비율을 위한 대화상자 추가. 대화상자 클래스 추가. 대화상자 클래스 변수 설정.
	- 프로젝트Doc 우클릭해서 OnDownSampling 함수 추가. 결과영상 관련 변수 추(포인터, 가로, 세로, 전체 사이즈)
	- OnDownSampling 작성
	```c
	void CMFCApplication05111Doc::OnDownSampling()
	{
		int i, j;
		CDownSampleDlg2 dlg;

		if (dlg.DoModal() == IDOK) // 대화상자의 활성화 여부
		{
			m_Re_height = m_height / dlg.m_DownSampleRate;
			m_Re_width = m_width / dlg.m_DownSampleRate;
			m_Re_size = m_Re_height * m_Re_width;

			m_OutputImage = new unsigned char[m_Re_size];

			for (i = 0; i < m_Re_height; i++) {
				for (j = 0; j < m_Re_width; j++) {
					m_OutputImage[i*m_Re_width + j]
						= m_InputImage[(i*dlg.m_DownSampleRate*m_width) + dlg.m_DownSampleRate*j];
				}
			}
		}
		// TODO: 여기에 구현 코드 추가.
	}
	```
	- View OnDownSampling 작성
	```c
	MFCApplication05111Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnDownSampling();

	Invalidate(TRUE);
	```
	- 실행화면(이미지링크)



#### UpSampling  이미지 확대
* 디지털 영상을 확대하기.
* 단순한 업 샘플링을 사용하면 영상 품질이 떨어지기 때문에 원본 영상을 이용하여 보간(Interpolation)해야함.
* 실행하기
	- 업샘플링 메뉴 추가
	- 프로젝트뷰에 해당 메뉴 커멘드 처리기 추가.(클래스 마법사)
	- 프로젝트Doc 우클릭해서 OnUpSampling 함수 추가.
	- OnUpSampling 작성
		```c
	void CMFCApplication05111Doc::OnUpSampling()
	{
	int i, j;
	CUpSampleDlg dlg;

	if (dlg.DoModal() == IDOK) {
		m_Re_height = m_height * dlg.m_UpSampleRate;
		m_Re_width = m_width * dlg.m_UpSampleRate;
		m_Re_size = m_Re_height * m_Re_width;
		m_OutputImage = new unsigned char[m_Re_size];

		for (i = 0; i < m_Re_size; i++)
			m_OutputImage[i] = 0;

		for (i = 0; i < m_height; i++) {
			for (j = 0; j < m_width; j++) {
				m_OutputImage[i*dlg.m_UpSampleRate*m_Re_width +
					dlg.m_UpSampleRate*j] = m_InputImage[i*m_width + j];
			}
		}

		for (i = 0; i < m_height; i++) {
			for (j = 0; j < m_width; j++) {
				m_OutputImage[i*dlg.m_UpSampleRate * m_Re_width + dlg.m_UpSampleRate * j] //i * 2 * 512 + 2* j
					= m_InputImage[i * m_width + j]; // i * 256 +j
				//원본 이미지 샘플레이트만큼 거리두고 넣기

				if (j == 511) {
					m_OutputImage[i * dlg.m_UpSampleRate * m_Re_width +
						dlg.m_UpSampleRate * j] = m_InputImage[i * m_width + j];
					for (int x = 1; x < dlg.m_UpSampleRate; x++) {
						m_OutputImage[i * dlg.m_UpSampleRate * m_Re_width +
							dlg.m_UpSampleRate * j + x] = m_InputImage[i * m_width + j];
						m_OutputImage[i * dlg.m_UpSampleRate * m_Re_width +
							dlg.m_UpSampleRate * j + x * m_Re_width] = m_InputImage[i * m_width + j];
						for (int y = 1; y < dlg.m_UpSampleRate; y++) {
							m_OutputImage[i * dlg.m_UpSampleRate * m_Re_width +
								dlg.m_UpSampleRate * j + x * m_Re_width + y] = m_InputImage[i * m_width + j];
						}
					}
				}
				else {
					for (int x = 1; x < dlg.m_UpSampleRate; x++) { //x는 샘플레이트 반영을 위함
						m_OutputImage[i * dlg.m_UpSampleRate * m_Re_width + dlg.m_UpSampleRate * j + x] // i*2*512 + 2*j+x
							= (m_InputImage[i * m_width + j] + m_InputImage[i * m_width + j + 1]) / 2;
						m_OutputImage[i * dlg.m_UpSampleRate * m_Re_width + dlg.m_UpSampleRate * j + x * m_Re_width]  // i*2*512+ 2*j+x*512
							= (m_InputImage[i * m_width + j] + m_InputImage[i * m_width + j + 1]) / 2;
						for (int y = 1; y < dlg.m_UpSampleRate; y++) { //사이값 채우기, y는 샘플레이트 반영
							m_OutputImage[i * dlg.m_UpSampleRate * m_Re_width + dlg.m_UpSampleRate * j + x * m_Re_width + y] //i * 2 * 512 + 2* j + x*512+y
								= (m_InputImage[i * m_width + j] + m_InputImage[i * m_width + j + 1]) / 2;
						}
					}
				}

			}
		}
	}
}
		```
	- View OnUpSampling 작성
	- 실행화면(이미지링크)




#### Quantization  양자화
* 표본화된 화소의 밝기나 색상을 정해진 몇단계의 값으로 근사화하는 과정.
* 양자화 비트로 색상이나 밝기가 몇 단계로 표현되는 지 결정됨.
* 원 영상의 값을 일정한 좌표 단위로 버리는 것.
* 실행하기
	- 양자화 메뉴 추가
	- 프로젝트뷰에 해당 메뉴 커멘드 처리기 추가.(클래스 마법사)
	- 샘플링 비율을 위한 대화상자 추가. 대화상자 클래스 추가. 대화상자 클래스 변수 설정.
	- 프로젝트Doc 우클릭해서 OnQuantization 함수 추가.  
	- OnQuantization 작성(math.h 헤더선언)
```c
void CMFCApplication05111Doc::OnQuantization()
{
	CQuantizationDlg dlg;
	if (dlg.DoModal() == IDOK)
	{
		int i, j, value, LEVEL;
		double HIGH, *TEMP;

		m_Re_height = m_height;
		m_Re_width = m_width;
		m_Re_size = m_Re_height * m_Re_width;

		m_OutputImage = new unsigned char[m_Re_size];

		TEMP = new double[m_size];

		LEVEL = 256;
		HIGH = 256.;

		value = (int)pow(2, dlg.m_QuantBit);

		for (i = 0; i < m_size; i++) {
			for (j = 0; j < value; j++) {
				if (m_InputImage[i] >= (LEVEL / value)*j &&
					m_InputImage[i] < (LEVEL / value)*(j + 1)) {
					TEMP[i] = (double)(HIGH / value)*j;
				}
			}
		}
		for (i = 0; i < m_size; i++) {
			m_OutputImage[i] = (unsigned char)TEMP[i];
		}

	}
	// TODO: 여기에 구현 코드 추가.
}
```
	- View OnQuantization 작성
	- 실행화면(이미지링크)
