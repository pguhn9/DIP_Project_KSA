## DIP_MFC_Start
이미지처리를 위한 MFC 프로젝트 시작 방법

### 환경설정
* IDE: Visual Studio 2017
* OS: Window10
* 언어: C++


### MFC 설치
* VS2017 Installer 실행
  - C++ 작업 환경에서 MFC 개발 도구를 설치.
  (이미지링크)

### MFC 프로젝트 생성
 * 메뉴-file-새 프로젝트-MFC 앱을 선택해 생성
 (이미지링크)
</br>
현재 프로젝트에서는 프로젝트 설정 바꾸지않고  기본 값으로 진행.


### MFC 프로젝트 창 설정
* 작성 창</br>
  솔루션 탐색기, 클래스 탐색기, 리소스 뷰, 도구 상자

* 디버그 창</br>
  코드 중단점 설정, 조사식 창, 메모리 창


### OnOpenDocument 함수
* 영상 데이터를 파일에서 읽어 오려면 OnOpenDocument 함수를 재정의 해야함.
* OnOpenDocument 함수는 실행한 MFC프로그램에서 [파일]-[열기]메뉴를 클릭하면 파일을 입력 받을 수 있는 대화상자를 실행시키는 역할 수행.
* 실행하기
  - 클래스 위자드에서 클래스를 프로젝트Doc 클래스로 설정하고 가상함수에서 OnOpenDocument()를 선택하여 함수 추가.
  - 클래스 탐색기에서 프로젝트Doc을 우클릭해 [추가]-[변수 추가]
    * 입력 영상 포인터
    * 입력 영상의 가로축 크기
    * 입력 영상의 세로축 크기
    * 입력 영상의 전체 크기
  - OnOpenDocument() 재정의
  ```c
  BOOL CMFCApplication05111Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	CFile File; //파일 객체 선언

	File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);
	// 파일 열기 대화상자에서 선택한 파일을 지정하고 읽기 모드 선택
	// 이 책에서는 영상의 크기 256*256, 512*512, 640*480만을 사용한다.

	if (File.GetLength() == 256 * 256) {
		m_height = 256;
		m_width = 256;
	}
	else if (File.GetLength() == 512 * 512) {
		m_height = 512;
		m_width = 512;
	}
	else if (File.GetLength() == 640 * 480) {
		m_height = 480;
		m_width = 640;
	}
	else {
		AfxMessageBox(L"Not Support Image Size"); //크기가 없는 경우
		return 0;
	}

	m_size = m_width * m_height; //영상 크기 계산

	m_InputImage = new unsigned char[m_size];

	for (int i = 0; i < m_size; i++)
		m_InputImage[i] = 255; //초기화
	File.Read(m_InputImage, m_size); //입력 영상 파일 읽기
	File.Close(); //파일 닫기

	return TRUE;
}
  ```
  - 열기 한 파일을 보여주기 위해 프로젝트View클래스의 OnDraw 함수 재정의
  ```c
  void CMFCApplication05111View::OnDraw(CDC* pDC)
  {
  	CMFCApplication05111Doc* pDoc = GetDocument();  //도큐먼트 클래스 참조
  	ASSERT_VALID(pDoc);
  	int i, j;
  	unsigned char R, G, B;

  	for (i = 0; i < pDoc->m_height; i++) {
  		for (j = 0; j < pDoc->m_width; j++) {
  			R = G = B = pDoc->m_InputImage[i*pDoc->m_width + j];
  			pDC->SetPixel(j + 5, i + 5, RGB(R, G, B));
  		}
  	}

  	for (i = 0; i < pDoc->m_Re_height; i++) {
  		for (j = 0; j < pDoc->m_Re_width; j++) {
  			R = pDoc->m_OutputImage[i*pDoc->m_Re_width + j];
  			G = B = R;
  			pDC->SetPixel(j + pDoc->m_width + 10, i + 5, RGB(R, G, B));
  		}
  	}
  	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
  }
  ```
  - 실행 화면(이미지링크)

  ### OnSaveDocument 함수
* 처리된 영상 데이터(배열)을 파일로 출력하기 위한 함수
* 실행하기
    - 클래스 위자드에서 클래스를 프로젝트Doc 클래스로 설정하고 가상함수에서 OnSaveDocument()를 선택하여 함수 추가.
    - OnSaveDocument() 재정의
    ```c
    BOOL CMFCApplication05111Doc::OnSaveDocument(LPCTSTR lpszPathName)
    {
    	CFile File; // 파일 객체 선언
    	CFileDialog SaveDlg(FALSE, _T("raw"), NULL, OFN_HIDEREADONLY);
    	// raw 파일을 다른 이름으로 저장하기를 위한 대화상자 객체 선언

    	if (SaveDlg.DoModal() == IDOK) {
    		// DoModal 멤버 함수에서 저장하기 수행
    		File.Open(SaveDlg.GetPathName(), CFile::modeCreate | CFile::modeWrite);
    		// 파일 열기
    		File.Write(m_OutputImage, m_size); // 파일 쓰기 (아웃풋이미지 저장)
    		File.Close();// 파일 닫기

    	}
    	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
    	return TRUE;//CDocument::OnSaveDocument(lpszPathName);
    }
    ```
    - MFC 프로그램에서 저장버튼을 눌러 [다른 이름으로 저장] 대화 상자에서 저장할 파일 이름을 입력해 프로그램 저장.
