
// ImageCompositionDoc.cpp: CImageCompositionDoc 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageComposition.h"
#endif

#include "ImageCompositionDoc.h"

#include <propkey.h>

#include "CImgComposition.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CImageCompositionDoc

IMPLEMENT_DYNCREATE(CImageCompositionDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageCompositionDoc, CDocument)
END_MESSAGE_MAP()


// CImageCompositionDoc 생성/소멸

CImageCompositionDoc::CImageCompositionDoc() noexcept
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CImageCompositionDoc::~CImageCompositionDoc()
{
}

BOOL CImageCompositionDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CImageCompositionDoc serialization

void CImageCompositionDoc::Serialize(CArchive& ar)
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
void CImageCompositionDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
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
void CImageCompositionDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageCompositionDoc::SetSearchContent(const CString& value)
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

// CImageCompositionDoc 진단

#ifdef _DEBUG
void CImageCompositionDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageCompositionDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG



// CImageCompositionDoc 명령
BOOL CImageCompositionDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.

	//CFile에서 처리

	CFile hFile;        //파일을 읽어들이면 이 클래스 형식으로 저장.
	m_height;        //이미지의 높이를 저장할 변수
	m_width;        //이미지의 가로길이를 저장할 변수

	hFile.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);    //파일 열기
	hFile.Read(&dibHf, sizeof(BITMAPFILEHEADER));                          //dibHf에 파일헤더를 읽어들인다.

	//이 파일이 BMP파일인지 검사 

	if (dibHf.bfType != 0x4D42)
	{
		AfxMessageBox(L"Not BMP file!!");                                        //프로젝트 생성시 유니코드를 사용하게 할 경우
		return FALSE;                                                                      //L을 붙여준다
	}

	hFile.Read(&dibHi, sizeof(BITMAPINFOHEADER));                             //영상정보의 header를 읽기

	if (dibHi.biBitCount != 8 && dibHi.biBitCount != 24)                                //8,24비트가 아닐경우
	{
		AfxMessageBox(L"Gray/True Color Possible!!");
		return FALSE;
	}

	if (dibHi.biBitCount == 8)
		//8비트의 경우 팔레트를 생성해 주어야 한다. 총 256가지 색이므로 그 길이만큼 읽어들인다
		hFile.Read(palRGB, sizeof(RGBQUAD) * 256);

	//메모리 할당
	int ImgSize;

	if (dibHi.biBitCount == 8)
	{
		ImgSize = hFile.GetLength() - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER) - 256 * sizeof(RGBQUAD);    //이미지의 크기는 파일 총 길이에서, 두 헤드와 팔레트의 사이즈를 
	}                                                                       //제외한다.
	else if (dibHi.biBitCount == 24) //컬러영상
	{
		ImgSize = hFile.GetLength() - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER);
	}

	//이미지를 저장, 출력할 배열생성.
	m_InImg = new unsigned char[ImgSize];
	m_OutputImage = new unsigned char[ImgSize];
	hFile.Read(m_InImg, ImgSize);
	//m_OutputImage = m_InImg;
	hFile.Close();

	//이미지의 길이정보
	m_height = dibHi.biHeight;
	m_width = dibHi.biWidth;
	m_Out_height = dibHi.biHeight;
	m_Out_width = dibHi.biWidth;

	return TRUE;
}


BOOL CImageCompositionDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	//3장
	CFile hFile;

	if (!hFile.Open(lpszPathName, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary))

		return FALSE;

	//정보저장
	hFile.Write(&dibHf, sizeof(BITMAPFILEHEADER));
	hFile.Write(&dibHi, sizeof(BITMAPINFOHEADER));

	if (dibHi.biBitCount == 8)
		hFile.Write(palRGB, sizeof(RGBQUAD) * 256);

	hFile.Write(m_OutputImage, dibHi.biSizeImage);
	hFile.Close();

	return TRUE;
}




void CImageCompositionDoc::OnImgComp()
{
	// 프레임AND 참고
	CFile tFile;
	CFileDialog OpenDlg(TRUE);
	CImgComposition ic;
	int bitcount=0;

	if (OpenDlg.DoModal() == IDOK) {
		tFile.Open(OpenDlg.GetPathName(), CFile::modeRead | CFile::typeBinary);    //파일 열기
		tFile.Read(&dibHf, sizeof(BITMAPFILEHEADER));

		//이 파일이 BMP파일인지 검사 
		if (dibHf.bfType != 0x4D42)
		{
			AfxMessageBox(L"Not BMP file!!");                                        //프로젝트 생성시 유니코드를 사용하게 할 경우                                                                     //L을 붙여준다
		}

		tFile.Read(&dibHi, sizeof(BITMAPINFOHEADER));                             //영상정보의 header를 읽기

		if (dibHi.biBitCount != 8 && dibHi.biBitCount != 24)                                //8,24비트가 아닐경우
		{
			AfxMessageBox(L"Gray/True Color Possible!!");
		}

		if (dibHi.biBitCount == 8)
			//8비트의 경우 팔레트를 생성해 주어야 한다. 총 256가지 색이므로 그 길이만큼 읽어들인다
			tFile.Read(palRGB, sizeof(RGBQUAD) * 256);


		//메모리 할당
		int ImgSize;

		if (dibHi.biBitCount == 8)
		{
			ImgSize = tFile.GetLength() - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER) - 256 * sizeof(RGBQUAD);    //이미지의 크기는 파일 총 길이에서, 두 헤드와 팔레트의 사이즈를 
		}
		else if (dibHi.biBitCount == 24) //컬러영상
		{
			ImgSize = tFile.GetLength() - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER);
		}

		//int i;
		unsigned char* background = new unsigned char[ImgSize];
		tFile.Read(background, ImgSize);
		tFile.Close();

		bitcount = dibHi.biBitCount;
		//AfxMessageBox(bitcount);
		m_Out_height = dibHi.biHeight;
		m_Out_width = dibHi.biWidth;
		m_Out_size = m_Out_height * m_Out_width;

		m_OutputImage = new unsigned char[m_Out_size];
		m_OutputImage = background;

		m_OutputImage = ic.ImageComposition(m_Out_size, m_InImg, background, m_OutputImage, bitcount);
	}

	

	/*
	if (OpenDlg.DoModal() == IDOK) {
		tFile.Open(OpenDlg.GetPathName(), CFile::modeRead); //파일 열기창
		if (tFile.GetLength() == (unsigned)m_width * m_height) {
			background = new unsigned char[m_size];
			tFile.Read(background, m_size); //파일에서 데이터 가지고 오기.
			tFile.Close();


			m_OutputImage = ic.ImageComposition(m_size, m_InputImage, background, m_OutputImage);

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
	*/
}
