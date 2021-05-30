<<<<<<< HEAD
﻿
// MFCApplication_0511_1Doc.cpp: CMFCApplication05111Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCApplication_0511_1.h"
#endif

#include "MFCApplication_0511_1Doc.h"


#include <propkey.h>

#include "CDownSampleDlg2.h"
#include "CUpSampleDlg.h"
#include "CQuantizationDlg.h"
#include "math.h"
#include "CConstantDlg.h"
#include "CStressTransformDlg.h"


#include "CImgComposition.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCApplication05111Doc

IMPLEMENT_DYNCREATE(CMFCApplication05111Doc, CDocument)

BEGIN_MESSAGE_MAP(CMFCApplication05111Doc, CDocument)
//	ON_COMMAND(ID_SUM_CONSTANT, &CMFCApplication05111Doc::OnSumConstant)
END_MESSAGE_MAP()


// CMFCApplication05111Doc 생성/소멸

CMFCApplication05111Doc::CMFCApplication05111Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CMFCApplication05111Doc::~CMFCApplication05111Doc()
{
}

BOOL CMFCApplication05111Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CMFCApplication05111Doc serialization

void CMFCApplication05111Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CMFCApplication05111Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CMFCApplication05111Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCApplication05111Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCApplication05111Doc 진단

#ifdef _DEBUG
void CMFCApplication05111Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCApplication05111Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

#define DIB_HEADER_MARKER ((WORD) ('M' << 8) | 'B')



// CMFCApplication05111Doc 명령
BOOL CMFCApplication05111Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	CFile File; //파일 객체 선언

	File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);
	// 파일 열기 대화상자에서 선택한 파일을 지정하고 읽기 모드 선택

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
	File.Read(m_InputImage, m_size);
	File.Close();



	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return TRUE;
}


BOOL CMFCApplication05111Doc::OnSaveDocument(LPCTSTR lpszPathName)
{
	CFile File; // 
	CFileDialog SaveDlg(FALSE, _T("raw"), NULL, OFN_HIDEREADONLY);

	if (SaveDlg.DoModal() == IDOK) {
		File.Open(SaveDlg.GetPathName(), CFile::modeCreate | CFile::modeWrite);
		File.Write(m_OutputImage, m_size);
		File.Close();
	}




	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return TRUE;//CDocument::OnSaveDocument(lpszPathName);
}






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

		
		

		CString str[10000];
		
		str[200].Format(L"%d", dlg.m_UpSampleRate);
		AfxMessageBox(str[200]);
		str[201].Format(L"%d", m_Re_width);
		AfxMessageBox(str[201]);
		str[202].Format(L"%d", m_width);
		AfxMessageBox(str[202]);
		str[203].Format(L"%d", m_height);
		AfxMessageBox(str[203]);

		str[0].Format(L"%d", m_OutputImage[0]);
		AfxMessageBox(str[0]);
		str[1].Format(L"%d", m_OutputImage[1]);
		AfxMessageBox(str[1]);
		str[2].Format(L"%d", m_OutputImage[2]);
		AfxMessageBox(str[2]);
	}


	// TODO: 여기에 구현 코드 추가.
}


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





void CMFCApplication05111Doc::OnStressTransform()
{
	CStressTransformDlg dlg;
	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] >= dlg.m_StartPoint &&
				m_InputImage[i] <= dlg.m_EndPoint)
				m_OutputImage[i] = 255;
			else
				m_OutputImage[i] = m_InputImage[i];
		}
	}
	// TODO: 여기에 구현 코드 추가.
}


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

double m_HIST[256];
double m_Sum_Of_HIST[256];
unsigned char m_Scale_HIST[256];


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


void CMFCApplication05111Doc::OnConvolSum()
{
	// TODO: 여기에 구현 코드 추가.
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

	int  j;
	//unsigned char LOW, HIGH;
	double MAX, MIN, DIF;

	m_Re_height = 60000;
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
	
	for (i = 0; i < m_size; i++) {
		value = (int)m_Sum_Of_HIST[i];
		m_HIST[i]= value;
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
}


void CMFCApplication05111Doc::OnTranslation()
{
	int i, j;
	int h_pos = 30, w_pos = 130;
	double **tempArray;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];


	m_tempImage = Image2DMem(m_height, m_width);
	tempArray = Image2DMem(m_Re_height, m_Re_width);

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_tempImage[i][j] = (double)m_InputImage[i*m_width + j];
		}
	}

	for (i = 0; i < m_height - h_pos; i++) {
		for (j = 0; j < m_width - w_pos; j++) {
			tempArray[i + h_pos][j + w_pos] = m_tempImage[i][j];
		}
	}

	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i* m_Re_width + j]
				= (unsigned char)tempArray[i][j];
		}
	}
	delete[] m_tempImage;
	delete[] tempArray;



	// TODO: 여기에 구현 코드 추가.
}


void CMFCApplication05111Doc::OnMirrorHor()
{
	int i, j;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_OutputImage[i*m_width + m_width - j - 1] =
				m_InputImage[i*m_width + j];
		}
	}

	// TODO: 여기에 구현 코드 추가.
}


void CMFCApplication05111Doc::OnMirrorVer()
{
	int i, j;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_OutputImage[(m_height - i - 1)*m_width + j]
				= m_InputImage[i*m_width + j];
		}
	}
	// TODO: 여기에 구현 코드 추가.
}


void CMFCApplication05111Doc::OnTranslation2()
{
	int i, j, CenterH, CenterW, newH, newW, degree = 45;
	double Radian, PI, **tempArray, Value;


	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];
	PI = 3.14159265358979;

	Radian = (double)degree*PI / 180.0;
	CenterH = m_height / 2;
	CenterW = m_width / 2;

	m_tempImage = Image2DMem(m_height, m_width);
	tempArray = Image2DMem(m_Re_height, m_Re_width);

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_tempImage[i][j] = (double)m_InputImage[i*m_width + j];
		}
	}

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			newH = (int)((i - CenterH)*cos(Radian)
				- (j - CenterW)*sin(Radian) + CenterH);
			newW = (int)((i - CenterH)*sin(Radian)
				+ (j - CenterW)*sin(Radian) + CenterW);

			if (newH < 0 || newH >= m_height) {
				Value = 0;
			}
			else if (newW < 0 || newW >= m_width) {
				Value = 0;
			}
			else {
				Value = m_tempImage[newH][newW];
			}
			tempArray[i][j] = Value;
		}
	}

	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i* m_Re_width + j]
				= (unsigned char)tempArray[i][j];
		}
	}

	delete[] m_tempImage;
	delete[] tempArray;

	// TODO: 여기에 구현 코드 추가.
}


void CMFCApplication05111Doc::OnFrameAnd()
{
	// TODO: 여기에 구현 코드 추가.
	CFile File;
	CFileDialog OpenDlg(TRUE);

	int i;
	unsigned char *temp =nullptr;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (OpenDlg.DoModal() == IDOK) {
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);
		if (File.GetLength() == (unsigned)m_width * m_height) {
			temp = new unsigned char[m_size];
			File.Read(temp, m_size);
			File.Close();

			for (i = 0; i < m_size; i++) {
				m_OutputImage[i]
					= (unsigned char)(m_InputImage[i] & temp[i]);
			}
		}
		else {
			AfxMessageBox(L"Image size not matched");
			return;
		}
	}

}


void CMFCApplication05111Doc::OnFrameConb()
{
	// TODO: 여기에 구현 코드 추가.
	CFile File;
	CFileDialog OpenDlg(TRUE);
	int i;
	unsigned char *temp = nullptr;
	unsigned char *masktemp = nullptr;
	unsigned char maskvalue;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	AfxMessageBox(L"합성할 영상 선택");

	if (OpenDlg.DoModal() == IDOK) {
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);
		temp = new unsigned char[m_size];
		File.Read(temp, m_size);

		if ((unsigned)m_width * m_height != File.GetLength()) {
			AfxMessageBox(L"Image size not matched");
			return;
		}
		File.Close();
	}
	AfxMessageBox(L"입력할영상");
	if (OpenDlg.DoModal() == IDOK) {
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);
		masktemp = new unsigned char[m_size];	
		File.Read(masktemp, m_size);
		File.Close();
	}

	for (i = 0; i < m_size; i++) {
		maskvalue = 255 - masktemp[i];
		m_OutputImage[i]
			= (m_InputImage[i] & masktemp[i]) | (temp[i] & maskvalue);
	}


}


void CMFCApplication05111Doc::OnFrameDiv()
{
	// TODO: 여기에 구현 코드 추가.
	CFile File;
	CFileDialog OpenDlg(TRUE);

	int i;
	unsigned char *temp;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (OpenDlg.DoModal() == IDOK) {
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);

		if (File.GetLength() == (unsigned)m_width * m_height) {
			temp = new unsigned char[m_size];

			File.Read(temp, m_size);
			File.Close();

			for (i = 0; i < m_size; i++) {
				if (m_InputImage[i] == 0)
					m_OutputImage[i] = 0;
				else if (temp[i] == 0)
					m_OutputImage[i] = 255;
				else
					m_OutputImage[i]
					= (unsigned char)(m_InputImage[i] / temp[i]);
			}
		}
		else {
			AfxMessageBox(L"Image size not matched");
			return;
		}
	}



}


void CMFCApplication05111Doc::OnFrameMul()
{
	// TODO: 여기에 구현 코드 추가.
	CFile File;
	CFileDialog OpenDlg(TRUE);

	int i;
	unsigned char *temp;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (OpenDlg.DoModal() == IDOK) {
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);
		if (File.GetLength() == (unsigned)m_width * m_height) {
			temp = new unsigned char[m_size];
			File.Read(temp, m_size);
			File.Close();

			for (i = 0; i < m_size; i++) {
				if (m_InputImage[i] * temp[i] > 255)
					m_OutputImage[i] = 255;
				else
					m_OutputImage[i] = m_InputImage[i] * temp[i];
			}
		}
		else {
			AfxMessageBox(L"Image size not matched");
			return;
		}
	}
}


void CMFCApplication05111Doc::OnFrameOr()
{
	// TODO: 여기에 구현 코드 추가.
	CFile File;
	CFileDialog OpenDlg(TRUE);

	int i;
	unsigned char *temp;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (OpenDlg.DoModal() == IDOK) {
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);
		if (File.GetLength() == (unsigned)m_width * m_height) {
			temp = new unsigned char[m_size];

			File.Read(temp, m_size);
			File.Close();

			for (i = 0; i < m_size; i++) {
				m_OutputImage[i]
					= (unsigned char)(m_InputImage[i] | temp[i]);
			}
		}

	}
	else {
		AfxMessageBox(L"Image size not matched");
		return;
	}



}


void CMFCApplication05111Doc::OnFrameSub()
{
	// TODO: 여기에 구현 코드 추가.
	CFile File;
	CFileDialog OpenDlg(TRUE);

	int i;
	unsigned char *temp;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (OpenDlg.DoModal() == IDOK) {
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);
		if (File.GetLength() == (unsigned)m_width * m_height) {
			temp = new unsigned char[m_size];

			File.Read(temp, m_size);
			File.Close();

			for (i = 0; i < m_size; i++) {
				if (m_InputImage[i] - temp[i] < 0)
					m_OutputImage[i] = 0;
				else
					m_OutputImage[i] = m_InputImage[i] - temp[i];
			}
		}
		else {
			AfxMessageBox(L"Image size not matched");
			return;
		}
	}
}


void CMFCApplication05111Doc::OnFrameSum()
{
	// TODO: 여기에 구현 코드 추가.
	CFile File;
	CFileDialog OpenDlg(TRUE);

	int i;
	unsigned char *temp;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	
	m_OutputImage = new unsigned char[m_Re_size];

	if (OpenDlg.DoModal() == IDOK) {
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);
		if (File.GetLength() == (unsigned)m_width * m_height) {
			temp = new unsigned char[m_size];

			File.Read(temp, m_size);
			File.Close();

			for (i = 0; i < m_size; i++) {
				if (m_InputImage[i] + temp[i] > 255)
					m_OutputImage[i] = 255;
				else
					m_OutputImage[i] = m_InputImage[i] + temp[i];
			}
		}
		else {
			AfxMessageBox(L"Image size not matched");
			return;
		}
	}


}


void CMFCApplication05111Doc::OnBinaryDilation()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j, n, m;
	double Mask[3][3] = { {255.,255.,255.}, {255.,255.,255.}, {255.,255.,255.} };
	double **tempInput, S = 0.0;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	tempInput = Image2DMem(m_height + 2, m_width + 2);

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			tempInput[i + 1][j + 1]
				= (double)m_InputImage[i * m_width + j];
		}
	}

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					if (Mask[n][m] == tempInput[i + n][j + m]) {
						S += 1.0;
					}
				}
			}
			if (S == 9.0)
				m_OutputImage[i * m_Re_width + j] = (unsigned char)255.0;
			else
				m_OutputImage[i * m_Re_width + j] = (unsigned char)0.0;
			S = 0.0; // reset;
		}
	}
	delete[] tempInput;


}


void CMFCApplication05111Doc::OnBinaryErosion()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j, n, m;
	double Mask[3][3] = { {0., 0., 0.},{0., 0., 0.},{0., 0., 0.} };
	double **tempInput, S = 0.0;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	tempInput = Image2DMem(m_height + 2, m_width + 2);

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			tempInput[i + 1][j + 1]
				= (double)m_InputImage[i * m_width + j];
		}
	}

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					if (Mask[n][m] == tempInput[i + n][j + m]) {
						S += 1.0;
					}
				}
			}
			if (S == 9.0)
				m_OutputImage[i * m_Re_width + j]
				= (unsigned char)0.0;
			else
				m_OutputImage[i * m_Re_width + j]
				= (unsigned char)255.0;
			S = 0.0;
		}
	}
	delete[] tempInput;

}


void CMFCApplication05111Doc::OnGrayDilation()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j, n, m, h;
	double Mask[9], MAX = 0.0;
	double **tempInput, S = 0.0;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	tempInput = Image2DMem(m_height + 2, m_width + 2);

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			tempInput[i + 1][j + 1]
				= (double)m_InputImage[i * m_width + j];
		}
	}

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			MAX = 0.0;
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					Mask[n * 3 + m] = tempInput[i + n][j + m];
				}
			}
			for (h = 0; h < 9; h++) {
				if (Mask[h] > MAX)
					MAX = Mask[h];
			}
			m_OutputImage[i * m_Re_width + j]
				= (unsigned char)MAX;
		}
	}


}


void CMFCApplication05111Doc::OnGrayErosion()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j, n, m, h;
	double Mask[9], MIN = 10000.0;
	double **tempInput, S = 0.0;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	tempInput = Image2DMem(m_height + 2, m_width + 2);

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			tempInput[i + 1][j + 1]
				= (double)m_InputImage[i * m_width + j];
		}
	}

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			MIN = 10000.0;
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					Mask[n * 3 + m] = tempInput[i + n][j + m];
				}
			}
			for (h = 0; h < 9; h++) {
				if (Mask[h] < MIN)
					MIN = Mask[h];
			}
			m_OutputImage[i * m_Re_width + j]
				= (unsigned char)MIN;
		}
	}

}


void CMFCApplication05111Doc::OnLowPassFilter()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;
	double LPF[3][3] = { {1. / 9., 1. / 9., 1. / 9.}, {1. / 9., 1. / 9., 1. / 9.}, {1. / 9., 1. / 9., 1. / 9.} };
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	m_tempImage = OnMaskProcess(m_InputImage, LPF);

	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			if (m_tempImage[i][j] > 255)
				m_OutputImage[i*   m_Re_width + j] = 255;
			else if (m_tempImage[i][j] < 0)
				m_OutputImage[i*   m_Re_width + j] = 0;
			else
				m_OutputImage[i* m_Re_width + j]
				= (unsigned char)m_tempImage[i][j];
		}
	}

}


void CMFCApplication05111Doc::OnHighPassFilter()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;
	double HPF[3][3] = { {-1. / 9., -1. / 9., -1. / 9.}, {-1. / 9., 8 / 9., -1. / 9.}, {-1. / 9., -1. / 9., -1. / 9.} };

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = OnMaskProcess(m_InputImage, HPF);

	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			if (m_tempImage[i][j] > 255)
				m_OutputImage[i*   m_Re_width + j] = 255;
			else if (m_tempImage[i][j] < 0)
				m_OutputImage[i*   m_Re_width + j] = 0;
			else
				m_OutputImage[i*   m_Re_width + j]
				= (unsigned char)m_tempImage[i][j];
		}
	}
}


void CMFCApplication05111Doc::OnMeanFilter()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j, n, m;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	double **tempInputImage, **tempOutputImage, S = 0.0;

	tempInputImage = Image2DMem(m_height + 2, m_width + 2);
	tempOutputImage = Image2DMem(m_height, m_width);

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			tempInputImage[i + 1][j + 1]
				= (double)m_InputImage[i * m_width + j];
		}
	}

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					S += tempInputImage[i + n][j + m];
				}
			}
			m_OutputImage[i*   m_Re_width + j]
				= (unsigned char)(S / 9.);
			S = 0.0; // reset​
		}
	}


}


void CMFCApplication05111Doc::OnMedianFilter()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j, n, m, index = 0;
	double **tempInputImage, Mask[9];

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	tempInputImage = Image2DMem(m_height + 2, m_width + 2);

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			tempInputImage[i + 1][j + 1]
				= (double)m_InputImage[i * m_width + j];
		}
	}

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					Mask[n * 3 + m] = tempInputImage[i + n][j + m];
				}
			}
			//OnBubleSort(Mask, 9);
			m_OutputImage[index] = (unsigned char)Mask[4];
			index++;
		}
	}
}


void CMFCApplication05111Doc::OnMaxFilter()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j, n, m, index = 0;
	double **tempInputImage, Mask[9];

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	tempInputImage = Image2DMem(m_height + 2, m_width + 2);

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			tempInputImage[i + 1][j + 1]
				= (double)m_InputImage[i * m_width + j];
		}
	}

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					Mask[n * 3 + m] = tempInputImage[i + n][j + m];
				}
			}
			//OnBubleSort(Mask, 9);
			m_OutputImage[index] = (unsigned char)Mask[8];
			index++;
		}
	}
}


void CMFCApplication05111Doc::OnMinFilter()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j, n, m, index = 0;
	double **tempInputImage, Mask[9];

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	tempInputImage = Image2DMem(m_height + 2, m_width + 2);

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			tempInputImage[i + 1][j + 1]
				= (double)m_InputImage[i * m_width + j];
		}
	}

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					Mask[n * 3 + m] = tempInputImage[i + n][j + m];
				}
			}
			//OnBubleSort(Mask, 9);
			m_OutputImage[index] = (unsigned char)Mask[0];
			index++;
		}
	}

}


void CMFCApplication05111Doc::OnBubbleSort(double * A, int MAX)
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;
	for (i = 0; i < MAX; i++) {
		for (j = 0; j < MAX - 1; j++) {
			if (A[j] > A[j + 1]) {
				OnSwap(&A[j], &A[j + 1]);
			}
		}
	}
}


void CMFCApplication05111Doc::OnSwap(double* a, double* b)
{
	// TODO: 여기에 구현 코드 추가.
	double temp;
	temp = *a;
	*a = *b;
	*b = temp;

}


void CMFCApplication05111Doc::OnFft2d()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j, row, col, Log2N, Num;
	Complex *Data;

	unsigned char **temp;
	double Value, Absol;

	Num = m_width;
	Log2N = 0;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	while (Num >= 2) // 영상의 너비 계산
	{
		Num >>= 1;
		Log2N++;
	}

	m_tempImage = Image2DMem(m_height, m_width); // 기억 장소 할당
	Data = new Complex[m_width];

	m_FFT = new Complex *[m_height];
	// 주파수 영역 변환 영상을 저장하기 위한 배열
	temp = new unsigned char *[m_height];

	for (i = 0; i < m_height; i++) {
		m_FFT[i] = new Complex[m_width];
		temp[i] = new unsigned char[m_width];
	}
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			Data[j].Re = (double)m_InputImage[i*m_width + j];
			// 입력의 한 행을 복사, 실수 성분 값은 영상의 값
			Data[j].Im = 0.0; // 복소 성분 값은 0
		}
		OnFtt1d(Data, m_width, Log2N); // 1차원 FFT
		for (j = 0; j < m_width; j++) { // 결과 저장
			m_FFT[i][j].Re = Data[j].Re;
			m_FFT[i][j].Im = Data[j].Im;
		}
	}

	Num = m_height;
	Log2N = 0;

	while (Num >= 2) // 영상의 높이 계산
	{
		Num >>= 1;
		Log2N++;
	}

	Data = new Complex[m_height];

	for (i = 0; i < m_width; i++) {
		for (j = 0; j < m_height; j++) {
			Data[j].Re = m_FFT[j][i].Re; // 영상의 한 열을 복사
			Data[j].Im = m_FFT[j][i].Im;
		}

		OnFtt1d(Data, m_height, Log2N); // 1차원 FFT

		for (j = 0; j < m_height; j++) { // 결과 저장
			m_FFT[j][i].Re = Data[j].Re;
			m_FFT[j][i].Im = Data[j].Im;
		}
	}
	// FFT 실행 결과를 영상으로 출력하기 위한 연산
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			Value = sqrt((m_FFT[i][j].Re * m_FFT[i][j].Re) +
				(m_FFT[i][j].Im * m_FFT[i][j].Im));
			Absol = 20 * log(Value);

			if (Absol > 255.0)
				Absol = 255.0;
			if (Absol < 0.0)
				Absol = 0.0;
			m_tempImage[i][j] = Absol;
		}
	}

	// 셔플링 과정 : 영상을 4등분하고 분할된 영상을 상하 대칭 및 좌우 대칭
	for (i = 0; i < m_height; i += m_height / 2) {
		for (int j = 0; j < m_width; j += m_width / 2) {
			for (row = 0; row < m_height / 2; row++) {
				for (col = 0; col < m_width / 2; col++) {
					temp[(m_height / 2 - 1) - row + i][(m_width / 2 - 1) - col + j]
						= (unsigned char)m_tempImage[i + row][j + col];
				}
			}
		}
	}
	
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_OutputImage[i*m_width + j] = temp[i][j];
		}
	}

	delete[] Data, **temp;

}


void CMFCApplication05111Doc::OnFtt1d(Complex * X, int N, int Log2N)
{
	// TODO: 여기에 구현 코드 추가.
	// 1차원 fft를 위한 함수
	OnShuffle(X, N, Log2N); // 함수 호출
	OnButterfly(X, N, Log2N, 1); // 함수 호출
}


void CMFCApplication05111Doc::OnShuffle(Complex * X, int N, int Log2N)
{
	// TODO: 여기에 구현 코드 추가.
	// 입력 데이터의 순서를 바구기 위한 함수
	int i;
	Complex *temp;

	temp = new Complex[N];

	for (i = 0; i < N; i++) {
		temp[i].Re = X[OnReverseBitOrder(i, Log2N)].Re;
		temp[i].Im = X[OnReverseBitOrder(i, Log2N)].Im;
	}

	for (i = 0; i < N; i++) {
		X[i].Re = temp[i].Re;
		X[i].Im = temp[i].Im;
	}
	delete[] temp;
}


void CMFCApplication05111Doc::OnButterfly(Complex * X, int N, int Log2N, int mode)
{
	// TODO: 여기에 구현 코드 추가.
	 // 나비(Butterfly) 구조를 위한 함수
	int i, j, k, m;

	int start;
	double Value;
	double PI = 3.14159265358979;

	Complex *Y, temp;

	Y = new Complex[N / 2];

	for (i = 0; i < Log2N; i++) {
		Value = pow(2, i + 1);

		if (mode == 1) {
			for (j = 0; j < (int)(Value / 2); j++) {
				Y[j].Re = cos(j*2.0*PI / Value);
				Y[j].Im = -sin(j*2.0*PI / Value);
			}
		}
		if (mode == 2) {
			for (j = 0; j < (int)(Value / 2); j++) {
				Y[j].Re = cos(j*2.0*PI / Value);
				Y[j].Im = sin(j*2.0*PI / Value);
			}
		}

		start = 0;

		for (k = 0; k < N / (int)Value; k++) {
			for (j = start; j < start + (int)(Value / 2); j++) {
				m = j + (int)(Value / 2);
				temp.Re = Y[j - start].Re * X[m].Re
					- Y[j - start].Im * X[m].Im;
				temp.Im = Y[j - start].Im * X[m].Re
					+ Y[j - start].Re * X[m].Im;

				X[m].Re = X[j].Re - temp.Re;
				X[m].Im = X[j].Im - temp.Im;

				X[j].Re = X[j].Re + temp.Re;
				X[j].Im = X[j].Im + temp.Im;
			}
			start = start + (int)Value;
		}
	}
	if (mode == 2) {
		for (i = 0; i < N; i++) {
			X[i].Re = X[i].Re / N;
			X[i].Im = X[i].Im / N;
		}
	}

	delete[] Y;
}


int CMFCApplication05111Doc::OnReverseBitOrder(int index, int Log2N)
{
	// TODO: 여기에 구현 코드 추가.
	int i, X, Y;

	Y = 0;

	for (i = 0; i < Log2N; i++) {
		X = (index & (1 << i)) >> i;
		Y = (Y << 1) | X;
	}

	return Y;
}


void CMFCApplication05111Doc::OnImgCompo()
{
	// 프레임AND 참고
	CFile File;
	CFileDialog OpenDlg(TRUE);
	CImgComposition ic;

	int i;
	unsigned char *background = nullptr;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (OpenDlg.DoModal() == IDOK) {
		File.Open(OpenDlg.GetPathName(), CFile::modeRead); //파일 열기창
		if (File.GetLength() == (unsigned)m_width * m_height) {
			background = new unsigned char[m_size];
			File.Read(background, m_size); //파일에서 데이터 가지고 오기.
			File.Close();


			m_OutputImage=ic.ImageComposition(m_size, m_InputImage, background, m_OutputImage);

			//for (i = 0; i < m_size; i++) {
			//	m_OutputImage[i]
			//		= (unsigned char)(m_InputImage[i] & background[i]);
			//}
		}
		else {
			AfxMessageBox(L"Image size not matched");
			return;
		}
	}
}


void CMFCApplication05111Doc::OnIfft2d()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j, Num, Log2N;
	Complex *Data;

	Num = m_width;
	Log2N = 0;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	while (Num >= 2) // 주파수 변환된 영상의 너비 계산
	{
		Num >>= 1;
		Log2N++;
	}

	Data = new Complex[m_height];
	m_IFFT = new Complex *[m_height]; // 역변환된 영상을 위한 배열

	for (i = 0; i < m_height; i++) {
		m_IFFT[i] = new Complex[m_width];
	}
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) { // 한 행을 복사
			Data[j].Re = m_FFT[i][j].Re;
			Data[j].Im = m_FFT[i][j].Im;
		}

		OnIfft1d(Data, m_width, Log2N); // 1차원 IFFT
		for (j = 0; j < m_width; j++) {
			m_IFFT[i][j].Re = Data[j].Re; // 결과 저장
			m_IFFT[i][j].Im = Data[j].Im;
		}
	}

	Num = m_height;
	Log2N = 0;
	while (Num >= 2) // 주파수 변환된 영상의 높이 계산
	{
		Num >>= 1;
		Log2N++;
	}

	Data = new Complex[m_height];

	for (i = 0; i < m_width; i++) {
		for (j = 0; j < m_height; j++) {
			Data[j].Re = m_IFFT[j][i].Re; // 한 열을 복사
			Data[j].Im = m_IFFT[j][i].Im;
		}

		OnIfft1d(Data, m_height, Log2N); // 1차원 IFFT

		for (j = 0; j < m_height; j++) {
			m_IFFT[j][i].Re = Data[j].Re; // 결과 저장
			m_IFFT[j][i].Im = Data[j].Im;
		}
	}

	for (i = 0; i < m_width; i++) {
		for (j = 0; j < m_height; j++) {
			m_OutputImage[i*m_width + j]
				= (unsigned char)m_IFFT[i][j].Re;
			// 결과 출력
		}
	}
	delete[] Data;
}


void CMFCApplication05111Doc::OnIfft1d(Complex* X, int N, int Log2N)
{
	// TODO: 여기에 구현 코드 추가.
	OnShuffle(X, N, Log2N);
	OnButterfly(X, N, Log2N, 2);
}


void CMFCApplication05111Doc::OnLpfFrequency()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j, x, y;
	double temp, D, N;
	D = 32.0;
	N = 4.0;

	OnFft2d(); // 주파수 변환

	// 주파수 변환된 값에서 고주파 성분 제거
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			x = i;
			y = j;
			if (x > m_height / 2)
				x = x - m_height;
			if (y > m_width / 2)
				y = y - m_width;

			temp = 1.0 / (1.0 + pow(sqrt((double)
				(x * x + y * y)) / D, 2 * N));

			m_FFT[i][j].Re = m_FFT[i][j].Re * temp;
			m_FFT[i][j].Im = m_FFT[i][j].Im * temp;
		}
	}

	OnIfft2d(); // 주파수 역변환
}


void CMFCApplication05111Doc::OnHpfFrequency()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j, x, y;
	double temp, D, N;
	D = 128.0;
	N = 4.0;

	OnFft2d(); // 주파수 변환
	// 주파수 변환된 값에서 저주파 성분 제거
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			x = i;
			y = j;

			if (x > m_height / 2)
				x = x - m_height;
			if (y > m_width / 2)
				y = y - m_width;

			temp = 1.0 / (1.0 + pow(D / sqrt((double)
				(x * x + y * y)), 2 * N));

			m_FFT[i][j].Re = m_FFT[i][j].Re * temp;
			m_FFT[i][j].Im = m_FFT[i][j].Im * temp;
		}
	}
	OnIfft2d(); // 주파수 역변환
}
=======
﻿
// MFCApplication_0511_1Doc.cpp: CMFCApplication05111Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCApplication_0511_1.h"
#endif

#include "MFCApplication_0511_1Doc.h"


#include <propkey.h>

#include "CDownSampleDlg2.h"
#include "CUpSampleDlg.h"
#include "CQuantizationDlg.h"
#include "math.h"
#include "CConstantDlg.h"
#include "CStressTransformDlg.h"


#include "CImgComposition.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCApplication05111Doc

IMPLEMENT_DYNCREATE(CMFCApplication05111Doc, CDocument)

BEGIN_MESSAGE_MAP(CMFCApplication05111Doc, CDocument)
//	ON_COMMAND(ID_SUM_CONSTANT, &CMFCApplication05111Doc::OnSumConstant)
END_MESSAGE_MAP()


// CMFCApplication05111Doc 생성/소멸

CMFCApplication05111Doc::CMFCApplication05111Doc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CMFCApplication05111Doc::~CMFCApplication05111Doc()
{
}

BOOL CMFCApplication05111Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CMFCApplication05111Doc serialization

void CMFCApplication05111Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CMFCApplication05111Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CMFCApplication05111Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCApplication05111Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCApplication05111Doc 진단

#ifdef _DEBUG
void CMFCApplication05111Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCApplication05111Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

#define DIB_HEADER_MARKER ((WORD) ('M' << 8) | 'B')



// CMFCApplication05111Doc 명령
BOOL CMFCApplication05111Doc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	CFile File; //파일 객체 선언

	File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);
	// 파일 열기 대화상자에서 선택한 파일을 지정하고 읽기 모드 선택

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
	File.Read(m_InputImage, m_size);
	File.Close();



	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	return TRUE;
}


BOOL CMFCApplication05111Doc::OnSaveDocument(LPCTSTR lpszPathName)
{
	CFile File; // 
	CFileDialog SaveDlg(FALSE, _T("raw"), NULL, OFN_HIDEREADONLY);

	if (SaveDlg.DoModal() == IDOK) {
		File.Open(SaveDlg.GetPathName(), CFile::modeCreate | CFile::modeWrite);
		File.Write(m_OutputImage, m_size);
		File.Close();
	}




	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return TRUE;//CDocument::OnSaveDocument(lpszPathName);
}






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

		
		

		CString str[10000];
		
		str[200].Format(L"%d", dlg.m_UpSampleRate);
		AfxMessageBox(str[200]);
		str[201].Format(L"%d", m_Re_width);
		AfxMessageBox(str[201]);
		str[202].Format(L"%d", m_width);
		AfxMessageBox(str[202]);
		str[203].Format(L"%d", m_height);
		AfxMessageBox(str[203]);

		str[0].Format(L"%d", m_OutputImage[0]);
		AfxMessageBox(str[0]);
		str[1].Format(L"%d", m_OutputImage[1]);
		AfxMessageBox(str[1]);
		str[2].Format(L"%d", m_OutputImage[2]);
		AfxMessageBox(str[2]);
	}


	// TODO: 여기에 구현 코드 추가.
}


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





void CMFCApplication05111Doc::OnStressTransform()
{
	CStressTransformDlg dlg;
	int i;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (dlg.DoModal() == IDOK) {
		for (i = 0; i < m_size; i++) {
			if (m_InputImage[i] >= dlg.m_StartPoint &&
				m_InputImage[i] <= dlg.m_EndPoint)
				m_OutputImage[i] = 255;
			else
				m_OutputImage[i] = m_InputImage[i];
		}
	}
	// TODO: 여기에 구현 코드 추가.
}


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

double m_HIST[256];
double m_Sum_Of_HIST[256];
unsigned char m_Scale_HIST[256];


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


void CMFCApplication05111Doc::OnConvolSum()
{
	// TODO: 여기에 구현 코드 추가.
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

	int  j;
	//unsigned char LOW, HIGH;
	double MAX, MIN, DIF;

	m_Re_height = 60000;
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
	
	for (i = 0; i < m_size; i++) {
		value = (int)m_Sum_Of_HIST[i];
		m_HIST[i]= value;
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
}


void CMFCApplication05111Doc::OnTranslation()
{
	int i, j;
	int h_pos = 30, w_pos = 130;
	double **tempArray;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];


	m_tempImage = Image2DMem(m_height, m_width);
	tempArray = Image2DMem(m_Re_height, m_Re_width);

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_tempImage[i][j] = (double)m_InputImage[i*m_width + j];
		}
	}

	for (i = 0; i < m_height - h_pos; i++) {
		for (j = 0; j < m_width - w_pos; j++) {
			tempArray[i + h_pos][j + w_pos] = m_tempImage[i][j];
		}
	}

	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i* m_Re_width + j]
				= (unsigned char)tempArray[i][j];
		}
	}
	delete[] m_tempImage;
	delete[] tempArray;



	// TODO: 여기에 구현 코드 추가.
}


void CMFCApplication05111Doc::OnMirrorHor()
{
	int i, j;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_OutputImage[i*m_width + m_width - j - 1] =
				m_InputImage[i*m_width + j];
		}
	}

	// TODO: 여기에 구현 코드 추가.
}


void CMFCApplication05111Doc::OnMirrorVer()
{
	int i, j;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_OutputImage[(m_height - i - 1)*m_width + j]
				= m_InputImage[i*m_width + j];
		}
	}
	// TODO: 여기에 구현 코드 추가.
}


void CMFCApplication05111Doc::OnTranslation2()
{
	int i, j, CenterH, CenterW, newH, newW, degree = 45;
	double Radian, PI, **tempArray, Value;


	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];
	PI = 3.14159265358979;

	Radian = (double)degree*PI / 180.0;
	CenterH = m_height / 2;
	CenterW = m_width / 2;

	m_tempImage = Image2DMem(m_height, m_width);
	tempArray = Image2DMem(m_Re_height, m_Re_width);

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_tempImage[i][j] = (double)m_InputImage[i*m_width + j];
		}
	}

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			newH = (int)((i - CenterH)*cos(Radian)
				- (j - CenterW)*sin(Radian) + CenterH);
			newW = (int)((i - CenterH)*sin(Radian)
				+ (j - CenterW)*sin(Radian) + CenterW);

			if (newH < 0 || newH >= m_height) {
				Value = 0;
			}
			else if (newW < 0 || newW >= m_width) {
				Value = 0;
			}
			else {
				Value = m_tempImage[newH][newW];
			}
			tempArray[i][j] = Value;
		}
	}

	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			m_OutputImage[i* m_Re_width + j]
				= (unsigned char)tempArray[i][j];
		}
	}

	delete[] m_tempImage;
	delete[] tempArray;

	// TODO: 여기에 구현 코드 추가.
}


void CMFCApplication05111Doc::OnFrameAnd()
{
	// TODO: 여기에 구현 코드 추가.
	CFile File;
	CFileDialog OpenDlg(TRUE);

	int i;
	unsigned char *temp =nullptr;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (OpenDlg.DoModal() == IDOK) {
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);
		if (File.GetLength() == (unsigned)m_width * m_height) {
			temp = new unsigned char[m_size];
			File.Read(temp, m_size);
			File.Close();

			for (i = 0; i < m_size; i++) {
				m_OutputImage[i]
					= (unsigned char)(m_InputImage[i] & temp[i]);
			}
		}
		else {
			AfxMessageBox(L"Image size not matched");
			return;
		}
	}

}


void CMFCApplication05111Doc::OnFrameConb()
{
	// TODO: 여기에 구현 코드 추가.
	CFile File;
	CFileDialog OpenDlg(TRUE);
	int i;
	unsigned char *temp = nullptr;
	unsigned char *masktemp = nullptr;
	unsigned char maskvalue;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	AfxMessageBox(L"합성할 영상 선택");

	if (OpenDlg.DoModal() == IDOK) {
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);
		temp = new unsigned char[m_size];
		File.Read(temp, m_size);

		if ((unsigned)m_width * m_height != File.GetLength()) {
			AfxMessageBox(L"Image size not matched");
			return;
		}
		File.Close();
	}
	AfxMessageBox(L"입력할영상");
	if (OpenDlg.DoModal() == IDOK) {
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);
		masktemp = new unsigned char[m_size];	
		File.Read(masktemp, m_size);
		File.Close();
	}

	for (i = 0; i < m_size; i++) {
		maskvalue = 255 - masktemp[i];
		m_OutputImage[i]
			= (m_InputImage[i] & masktemp[i]) | (temp[i] & maskvalue);
	}


}


void CMFCApplication05111Doc::OnFrameDiv()
{
	// TODO: 여기에 구현 코드 추가.
	CFile File;
	CFileDialog OpenDlg(TRUE);

	int i;
	unsigned char *temp;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (OpenDlg.DoModal() == IDOK) {
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);

		if (File.GetLength() == (unsigned)m_width * m_height) {
			temp = new unsigned char[m_size];

			File.Read(temp, m_size);
			File.Close();

			for (i = 0; i < m_size; i++) {
				if (m_InputImage[i] == 0)
					m_OutputImage[i] = 0;
				else if (temp[i] == 0)
					m_OutputImage[i] = 255;
				else
					m_OutputImage[i]
					= (unsigned char)(m_InputImage[i] / temp[i]);
			}
		}
		else {
			AfxMessageBox(L"Image size not matched");
			return;
		}
	}



}


void CMFCApplication05111Doc::OnFrameMul()
{
	// TODO: 여기에 구현 코드 추가.
	CFile File;
	CFileDialog OpenDlg(TRUE);

	int i;
	unsigned char *temp;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (OpenDlg.DoModal() == IDOK) {
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);
		if (File.GetLength() == (unsigned)m_width * m_height) {
			temp = new unsigned char[m_size];
			File.Read(temp, m_size);
			File.Close();

			for (i = 0; i < m_size; i++) {
				if (m_InputImage[i] * temp[i] > 255)
					m_OutputImage[i] = 255;
				else
					m_OutputImage[i] = m_InputImage[i] * temp[i];
			}
		}
		else {
			AfxMessageBox(L"Image size not matched");
			return;
		}
	}
}


void CMFCApplication05111Doc::OnFrameOr()
{
	// TODO: 여기에 구현 코드 추가.
	CFile File;
	CFileDialog OpenDlg(TRUE);

	int i;
	unsigned char *temp;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (OpenDlg.DoModal() == IDOK) {
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);
		if (File.GetLength() == (unsigned)m_width * m_height) {
			temp = new unsigned char[m_size];

			File.Read(temp, m_size);
			File.Close();

			for (i = 0; i < m_size; i++) {
				m_OutputImage[i]
					= (unsigned char)(m_InputImage[i] | temp[i]);
			}
		}

	}
	else {
		AfxMessageBox(L"Image size not matched");
		return;
	}



}


void CMFCApplication05111Doc::OnFrameSub()
{
	// TODO: 여기에 구현 코드 추가.
	CFile File;
	CFileDialog OpenDlg(TRUE);

	int i;
	unsigned char *temp;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (OpenDlg.DoModal() == IDOK) {
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);
		if (File.GetLength() == (unsigned)m_width * m_height) {
			temp = new unsigned char[m_size];

			File.Read(temp, m_size);
			File.Close();

			for (i = 0; i < m_size; i++) {
				if (m_InputImage[i] - temp[i] < 0)
					m_OutputImage[i] = 0;
				else
					m_OutputImage[i] = m_InputImage[i] - temp[i];
			}
		}
		else {
			AfxMessageBox(L"Image size not matched");
			return;
		}
	}
}


void CMFCApplication05111Doc::OnFrameSum()
{
	// TODO: 여기에 구현 코드 추가.
	CFile File;
	CFileDialog OpenDlg(TRUE);

	int i;
	unsigned char *temp;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	
	m_OutputImage = new unsigned char[m_Re_size];

	if (OpenDlg.DoModal() == IDOK) {
		File.Open(OpenDlg.GetPathName(), CFile::modeRead);
		if (File.GetLength() == (unsigned)m_width * m_height) {
			temp = new unsigned char[m_size];

			File.Read(temp, m_size);
			File.Close();

			for (i = 0; i < m_size; i++) {
				if (m_InputImage[i] + temp[i] > 255)
					m_OutputImage[i] = 255;
				else
					m_OutputImage[i] = m_InputImage[i] + temp[i];
			}
		}
		else {
			AfxMessageBox(L"Image size not matched");
			return;
		}
	}


}


void CMFCApplication05111Doc::OnBinaryDilation()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j, n, m;
	double Mask[3][3] = { {255.,255.,255.}, {255.,255.,255.}, {255.,255.,255.} };
	double **tempInput, S = 0.0;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;
	m_OutputImage = new unsigned char[m_Re_size];

	tempInput = Image2DMem(m_height + 2, m_width + 2);

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			tempInput[i + 1][j + 1]
				= (double)m_InputImage[i * m_width + j];
		}
	}

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					if (Mask[n][m] == tempInput[i + n][j + m]) {
						S += 1.0;
					}
				}
			}
			if (S == 9.0)
				m_OutputImage[i * m_Re_width + j] = (unsigned char)255.0;
			else
				m_OutputImage[i * m_Re_width + j] = (unsigned char)0.0;
			S = 0.0; // reset;
		}
	}
	delete[] tempInput;


}


void CMFCApplication05111Doc::OnBinaryErosion()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j, n, m;
	double Mask[3][3] = { {0., 0., 0.},{0., 0., 0.},{0., 0., 0.} };
	double **tempInput, S = 0.0;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	tempInput = Image2DMem(m_height + 2, m_width + 2);

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			tempInput[i + 1][j + 1]
				= (double)m_InputImage[i * m_width + j];
		}
	}

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					if (Mask[n][m] == tempInput[i + n][j + m]) {
						S += 1.0;
					}
				}
			}
			if (S == 9.0)
				m_OutputImage[i * m_Re_width + j]
				= (unsigned char)0.0;
			else
				m_OutputImage[i * m_Re_width + j]
				= (unsigned char)255.0;
			S = 0.0;
		}
	}
	delete[] tempInput;

}


void CMFCApplication05111Doc::OnGrayDilation()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j, n, m, h;
	double Mask[9], MAX = 0.0;
	double **tempInput, S = 0.0;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	tempInput = Image2DMem(m_height + 2, m_width + 2);

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			tempInput[i + 1][j + 1]
				= (double)m_InputImage[i * m_width + j];
		}
	}

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			MAX = 0.0;
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					Mask[n * 3 + m] = tempInput[i + n][j + m];
				}
			}
			for (h = 0; h < 9; h++) {
				if (Mask[h] > MAX)
					MAX = Mask[h];
			}
			m_OutputImage[i * m_Re_width + j]
				= (unsigned char)MAX;
		}
	}


}


void CMFCApplication05111Doc::OnGrayErosion()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j, n, m, h;
	double Mask[9], MIN = 10000.0;
	double **tempInput, S = 0.0;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	tempInput = Image2DMem(m_height + 2, m_width + 2);

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			tempInput[i + 1][j + 1]
				= (double)m_InputImage[i * m_width + j];
		}
	}

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			MIN = 10000.0;
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					Mask[n * 3 + m] = tempInput[i + n][j + m];
				}
			}
			for (h = 0; h < 9; h++) {
				if (Mask[h] < MIN)
					MIN = Mask[h];
			}
			m_OutputImage[i * m_Re_width + j]
				= (unsigned char)MIN;
		}
	}

}


void CMFCApplication05111Doc::OnLowPassFilter()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;
	double LPF[3][3] = { {1. / 9., 1. / 9., 1. / 9.}, {1. / 9., 1. / 9., 1. / 9.}, {1. / 9., 1. / 9., 1. / 9.} };
	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	m_tempImage = OnMaskProcess(m_InputImage, LPF);

	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			if (m_tempImage[i][j] > 255)
				m_OutputImage[i*   m_Re_width + j] = 255;
			else if (m_tempImage[i][j] < 0)
				m_OutputImage[i*   m_Re_width + j] = 0;
			else
				m_OutputImage[i* m_Re_width + j]
				= (unsigned char)m_tempImage[i][j];
		}
	}

}


void CMFCApplication05111Doc::OnHighPassFilter()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;
	double HPF[3][3] = { {-1. / 9., -1. / 9., -1. / 9.}, {-1. / 9., 8 / 9., -1. / 9.}, {-1. / 9., -1. / 9., -1. / 9.} };

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];
	m_tempImage = OnMaskProcess(m_InputImage, HPF);

	for (i = 0; i < m_Re_height; i++) {
		for (j = 0; j < m_Re_width; j++) {
			if (m_tempImage[i][j] > 255)
				m_OutputImage[i*   m_Re_width + j] = 255;
			else if (m_tempImage[i][j] < 0)
				m_OutputImage[i*   m_Re_width + j] = 0;
			else
				m_OutputImage[i*   m_Re_width + j]
				= (unsigned char)m_tempImage[i][j];
		}
	}
}


void CMFCApplication05111Doc::OnMeanFilter()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j, n, m;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	double **tempInputImage, **tempOutputImage, S = 0.0;

	tempInputImage = Image2DMem(m_height + 2, m_width + 2);
	tempOutputImage = Image2DMem(m_height, m_width);

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			tempInputImage[i + 1][j + 1]
				= (double)m_InputImage[i * m_width + j];
		}
	}

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					S += tempInputImage[i + n][j + m];
				}
			}
			m_OutputImage[i*   m_Re_width + j]
				= (unsigned char)(S / 9.);
			S = 0.0; // reset​
		}
	}


}


void CMFCApplication05111Doc::OnMedianFilter()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j, n, m, index = 0;
	double **tempInputImage, Mask[9];

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	tempInputImage = Image2DMem(m_height + 2, m_width + 2);

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			tempInputImage[i + 1][j + 1]
				= (double)m_InputImage[i * m_width + j];
		}
	}

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					Mask[n * 3 + m] = tempInputImage[i + n][j + m];
				}
			}
			//OnBubleSort(Mask, 9);
			m_OutputImage[index] = (unsigned char)Mask[4];
			index++;
		}
	}
}


void CMFCApplication05111Doc::OnMaxFilter()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j, n, m, index = 0;
	double **tempInputImage, Mask[9];

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	tempInputImage = Image2DMem(m_height + 2, m_width + 2);

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			tempInputImage[i + 1][j + 1]
				= (double)m_InputImage[i * m_width + j];
		}
	}

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					Mask[n * 3 + m] = tempInputImage[i + n][j + m];
				}
			}
			//OnBubleSort(Mask, 9);
			m_OutputImage[index] = (unsigned char)Mask[8];
			index++;
		}
	}
}


void CMFCApplication05111Doc::OnMinFilter()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j, n, m, index = 0;
	double **tempInputImage, Mask[9];

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	tempInputImage = Image2DMem(m_height + 2, m_width + 2);

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			tempInputImage[i + 1][j + 1]
				= (double)m_InputImage[i * m_width + j];
		}
	}

	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			for (n = 0; n < 3; n++) {
				for (m = 0; m < 3; m++) {
					Mask[n * 3 + m] = tempInputImage[i + n][j + m];
				}
			}
			//OnBubleSort(Mask, 9);
			m_OutputImage[index] = (unsigned char)Mask[0];
			index++;
		}
	}

}


void CMFCApplication05111Doc::OnBubbleSort(double * A, int MAX)
{
	// TODO: 여기에 구현 코드 추가.
	int i, j;
	for (i = 0; i < MAX; i++) {
		for (j = 0; j < MAX - 1; j++) {
			if (A[j] > A[j + 1]) {
				OnSwap(&A[j], &A[j + 1]);
			}
		}
	}
}


void CMFCApplication05111Doc::OnSwap(double* a, double* b)
{
	// TODO: 여기에 구현 코드 추가.
	double temp;
	temp = *a;
	*a = *b;
	*b = temp;

}


void CMFCApplication05111Doc::OnFft2d()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j, row, col, Log2N, Num;
	Complex *Data;

	unsigned char **temp;
	double Value, Absol;

	Num = m_width;
	Log2N = 0;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	while (Num >= 2) // 영상의 너비 계산
	{
		Num >>= 1;
		Log2N++;
	}

	m_tempImage = Image2DMem(m_height, m_width); // 기억 장소 할당
	Data = new Complex[m_width];

	m_FFT = new Complex *[m_height];
	// 주파수 영역 변환 영상을 저장하기 위한 배열
	temp = new unsigned char *[m_height];

	for (i = 0; i < m_height; i++) {
		m_FFT[i] = new Complex[m_width];
		temp[i] = new unsigned char[m_width];
	}
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			Data[j].Re = (double)m_InputImage[i*m_width + j];
			// 입력의 한 행을 복사, 실수 성분 값은 영상의 값
			Data[j].Im = 0.0; // 복소 성분 값은 0
		}
		OnFtt1d(Data, m_width, Log2N); // 1차원 FFT
		for (j = 0; j < m_width; j++) { // 결과 저장
			m_FFT[i][j].Re = Data[j].Re;
			m_FFT[i][j].Im = Data[j].Im;
		}
	}

	Num = m_height;
	Log2N = 0;

	while (Num >= 2) // 영상의 높이 계산
	{
		Num >>= 1;
		Log2N++;
	}

	Data = new Complex[m_height];

	for (i = 0; i < m_width; i++) {
		for (j = 0; j < m_height; j++) {
			Data[j].Re = m_FFT[j][i].Re; // 영상의 한 열을 복사
			Data[j].Im = m_FFT[j][i].Im;
		}

		OnFtt1d(Data, m_height, Log2N); // 1차원 FFT

		for (j = 0; j < m_height; j++) { // 결과 저장
			m_FFT[j][i].Re = Data[j].Re;
			m_FFT[j][i].Im = Data[j].Im;
		}
	}
	// FFT 실행 결과를 영상으로 출력하기 위한 연산
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			Value = sqrt((m_FFT[i][j].Re * m_FFT[i][j].Re) +
				(m_FFT[i][j].Im * m_FFT[i][j].Im));
			Absol = 20 * log(Value);

			if (Absol > 255.0)
				Absol = 255.0;
			if (Absol < 0.0)
				Absol = 0.0;
			m_tempImage[i][j] = Absol;
		}
	}

	// 셔플링 과정 : 영상을 4등분하고 분할된 영상을 상하 대칭 및 좌우 대칭
	for (i = 0; i < m_height; i += m_height / 2) {
		for (int j = 0; j < m_width; j += m_width / 2) {
			for (row = 0; row < m_height / 2; row++) {
				for (col = 0; col < m_width / 2; col++) {
					temp[(m_height / 2 - 1) - row + i][(m_width / 2 - 1) - col + j]
						= (unsigned char)m_tempImage[i + row][j + col];
				}
			}
		}
	}
	
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			m_OutputImage[i*m_width + j] = temp[i][j];
		}
	}

	delete[] Data, **temp;

}


void CMFCApplication05111Doc::OnFtt1d(Complex * X, int N, int Log2N)
{
	// TODO: 여기에 구현 코드 추가.
	// 1차원 fft를 위한 함수
	OnShuffle(X, N, Log2N); // 함수 호출
	OnButterfly(X, N, Log2N, 1); // 함수 호출
}


void CMFCApplication05111Doc::OnShuffle(Complex * X, int N, int Log2N)
{
	// TODO: 여기에 구현 코드 추가.
	// 입력 데이터의 순서를 바구기 위한 함수
	int i;
	Complex *temp;

	temp = new Complex[N];

	for (i = 0; i < N; i++) {
		temp[i].Re = X[OnReverseBitOrder(i, Log2N)].Re;
		temp[i].Im = X[OnReverseBitOrder(i, Log2N)].Im;
	}

	for (i = 0; i < N; i++) {
		X[i].Re = temp[i].Re;
		X[i].Im = temp[i].Im;
	}
	delete[] temp;
}


void CMFCApplication05111Doc::OnButterfly(Complex * X, int N, int Log2N, int mode)
{
	// TODO: 여기에 구현 코드 추가.
	 // 나비(Butterfly) 구조를 위한 함수
	int i, j, k, m;

	int start;
	double Value;
	double PI = 3.14159265358979;

	Complex *Y, temp;

	Y = new Complex[N / 2];

	for (i = 0; i < Log2N; i++) {
		Value = pow(2, i + 1);

		if (mode == 1) {
			for (j = 0; j < (int)(Value / 2); j++) {
				Y[j].Re = cos(j*2.0*PI / Value);
				Y[j].Im = -sin(j*2.0*PI / Value);
			}
		}
		if (mode == 2) {
			for (j = 0; j < (int)(Value / 2); j++) {
				Y[j].Re = cos(j*2.0*PI / Value);
				Y[j].Im = sin(j*2.0*PI / Value);
			}
		}

		start = 0;

		for (k = 0; k < N / (int)Value; k++) {
			for (j = start; j < start + (int)(Value / 2); j++) {
				m = j + (int)(Value / 2);
				temp.Re = Y[j - start].Re * X[m].Re
					- Y[j - start].Im * X[m].Im;
				temp.Im = Y[j - start].Im * X[m].Re
					+ Y[j - start].Re * X[m].Im;

				X[m].Re = X[j].Re - temp.Re;
				X[m].Im = X[j].Im - temp.Im;

				X[j].Re = X[j].Re + temp.Re;
				X[j].Im = X[j].Im + temp.Im;
			}
			start = start + (int)Value;
		}
	}
	if (mode == 2) {
		for (i = 0; i < N; i++) {
			X[i].Re = X[i].Re / N;
			X[i].Im = X[i].Im / N;
		}
	}

	delete[] Y;
}


int CMFCApplication05111Doc::OnReverseBitOrder(int index, int Log2N)
{
	// TODO: 여기에 구현 코드 추가.
	int i, X, Y;

	Y = 0;

	for (i = 0; i < Log2N; i++) {
		X = (index & (1 << i)) >> i;
		Y = (Y << 1) | X;
	}

	return Y;
}


void CMFCApplication05111Doc::OnImgCompo()
{
	// 프레임AND 참고
	CFile File;
	CFileDialog OpenDlg(TRUE);
	CImgComposition ic;

	int i;
	unsigned char *background = nullptr;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	if (OpenDlg.DoModal() == IDOK) {
		File.Open(OpenDlg.GetPathName(), CFile::modeRead); //파일 열기창
		if (File.GetLength() == (unsigned)m_width * m_height) {
			background = new unsigned char[m_size];
			File.Read(background, m_size); //파일에서 데이터 가지고 오기.
			File.Close();


			m_OutputImage=ic.ImageComposition(m_size, m_InputImage, background, m_OutputImage);

			//for (i = 0; i < m_size; i++) {
			//	m_OutputImage[i]
			//		= (unsigned char)(m_InputImage[i] & background[i]);
			//}
		}
		else {
			AfxMessageBox(L"Image size not matched");
			return;
		}
	}
}


void CMFCApplication05111Doc::OnIfft2d()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j, Num, Log2N;
	Complex *Data;

	Num = m_width;
	Log2N = 0;

	m_Re_height = m_height;
	m_Re_width = m_width;
	m_Re_size = m_Re_height * m_Re_width;

	m_OutputImage = new unsigned char[m_Re_size];

	while (Num >= 2) // 주파수 변환된 영상의 너비 계산
	{
		Num >>= 1;
		Log2N++;
	}

	Data = new Complex[m_height];
	m_IFFT = new Complex *[m_height]; // 역변환된 영상을 위한 배열

	for (i = 0; i < m_height; i++) {
		m_IFFT[i] = new Complex[m_width];
	}
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) { // 한 행을 복사
			Data[j].Re = m_FFT[i][j].Re;
			Data[j].Im = m_FFT[i][j].Im;
		}

		OnIfft1d(Data, m_width, Log2N); // 1차원 IFFT
		for (j = 0; j < m_width; j++) {
			m_IFFT[i][j].Re = Data[j].Re; // 결과 저장
			m_IFFT[i][j].Im = Data[j].Im;
		}
	}

	Num = m_height;
	Log2N = 0;
	while (Num >= 2) // 주파수 변환된 영상의 높이 계산
	{
		Num >>= 1;
		Log2N++;
	}

	Data = new Complex[m_height];

	for (i = 0; i < m_width; i++) {
		for (j = 0; j < m_height; j++) {
			Data[j].Re = m_IFFT[j][i].Re; // 한 열을 복사
			Data[j].Im = m_IFFT[j][i].Im;
		}

		OnIfft1d(Data, m_height, Log2N); // 1차원 IFFT

		for (j = 0; j < m_height; j++) {
			m_IFFT[j][i].Re = Data[j].Re; // 결과 저장
			m_IFFT[j][i].Im = Data[j].Im;
		}
	}

	for (i = 0; i < m_width; i++) {
		for (j = 0; j < m_height; j++) {
			m_OutputImage[i*m_width + j]
				= (unsigned char)m_IFFT[i][j].Re;
			// 결과 출력
		}
	}
	delete[] Data;
}


void CMFCApplication05111Doc::OnIfft1d(Complex* X, int N, int Log2N)
{
	// TODO: 여기에 구현 코드 추가.
	OnShuffle(X, N, Log2N);
	OnButterfly(X, N, Log2N, 2);
}


void CMFCApplication05111Doc::OnLpfFrequency()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j, x, y;
	double temp, D, N;
	D = 32.0;
	N = 4.0;

	OnFft2d(); // 주파수 변환

	// 주파수 변환된 값에서 고주파 성분 제거
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			x = i;
			y = j;
			if (x > m_height / 2)
				x = x - m_height;
			if (y > m_width / 2)
				y = y - m_width;

			temp = 1.0 / (1.0 + pow(sqrt((double)
				(x * x + y * y)) / D, 2 * N));

			m_FFT[i][j].Re = m_FFT[i][j].Re * temp;
			m_FFT[i][j].Im = m_FFT[i][j].Im * temp;
		}
	}

	OnIfft2d(); // 주파수 역변환
}


void CMFCApplication05111Doc::OnHpfFrequency()
{
	// TODO: 여기에 구현 코드 추가.
	int i, j, x, y;
	double temp, D, N;
	D = 128.0;
	N = 4.0;

	OnFft2d(); // 주파수 변환
	// 주파수 변환된 값에서 저주파 성분 제거
	for (i = 0; i < m_height; i++) {
		for (j = 0; j < m_width; j++) {
			x = i;
			y = j;

			if (x > m_height / 2)
				x = x - m_height;
			if (y > m_width / 2)
				y = y - m_width;

			temp = 1.0 / (1.0 + pow(D / sqrt((double)
				(x * x + y * y)), 2 * N));

			m_FFT[i][j].Re = m_FFT[i][j].Re * temp;
			m_FFT[i][j].Im = m_FFT[i][j].Im * temp;
		}
	}
	OnIfft2d(); // 주파수 역변환
}
>>>>>>> 6adb5b23adddc723618e002f44a83cc893e0192f
