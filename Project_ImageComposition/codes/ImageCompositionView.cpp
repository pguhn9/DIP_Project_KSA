
// ImageCompositionView.cpp: CImageCompositionView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageComposition.h"
#endif

#include "ImageCompositionDoc.h"
#include "ImageCompositionView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageCompositionView

IMPLEMENT_DYNCREATE(CImageCompositionView, CView)

BEGIN_MESSAGE_MAP(CImageCompositionView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImageCompositionView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_IMG_COMP, &CImageCompositionView::OnImgComp)
	ON_COMMAND(ID_DOWNSAMPLE, &CImageCompositionView::OnDownsample)
END_MESSAGE_MAP()

// CImageCompositionView 생성/소멸

CImageCompositionView::CImageCompositionView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.
	BmInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD));

	for (int i = 0; i < 256; i++)
	{
		BmInfo->bmiColors[i].rgbRed = BmInfo->bmiColors[i].rgbGreen = BmInfo->bmiColors[i].rgbReserved = 0;
	}


}

CImageCompositionView::~CImageCompositionView()
{
	if (BmInfo) delete BmInfo;
}

BOOL CImageCompositionView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CImageCompositionView 그리기

void CImageCompositionView::OnDraw(CDC* pDC)
{
#define WIDTHBYTES(bits)	(((bits)+31)/32*4);        //이미지 가로 바이트 길이는 4바이트의 배수

	//BmInfo;
	int height;
	int width;
	int rwsize;

	CImageCompositionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	if (pDoc->m_InImg == NULL)
		return;

	//24비트 비트맵 파일의 영상출력
	if (pDoc->dibHi.biBitCount == 24) {
		height = pDoc->dibHi.biHeight;
		width = pDoc->dibHi.biWidth;
		rwsize = WIDTHBYTES(pDoc->dibHi.biBitCount*pDoc->dibHi.biWidth);
		BmInfo->bmiHeader = pDoc->dibHi;
		SetDIBitsToDevice(pDC->GetSafeHdc(), 0, 0, width, height, 0, 0, 0, height, pDoc->m_InImg, BmInfo, DIB_RGB_COLORS);
	}
	else	//8비트 흑백일 경우
	{
		int index;
		rwsize = WIDTHBYTES(pDoc->dibHi.biBitCount*pDoc->dibHi.biWidth);

		//팔레트를 읽어들이며 반복출력
		for (int i = 0; i < pDoc->dibHi.biHeight; i++)
			for (int j = 0; j < pDoc->dibHi.biWidth; j++) {
				index = pDoc->m_InImg[i*rwsize + j];
				BYTE R = pDoc->palRGB[index].rgbRed;
				BYTE G = pDoc->palRGB[index].rgbGreen;
				BYTE B = pDoc->palRGB[index].rgbBlue;

				//pDC->SetPixel(j,i,RGB(R,G,B));
				//영상 반전출력
				pDC->SetPixel(j, pDoc->dibHi.biHeight - i - 1, RGB(R, G, B));
			}
	}

	//아웃풋 출력
	if (pDoc->dibHi.biBitCount == 24) {
		//height = pDoc->dibHi.biHeight;
		height = pDoc->m_Out_height;
		pDoc->dibHi.biHeight = pDoc->m_Out_height;
		//width = pDoc->dibHi.biWidth;
		width = pDoc->m_Out_width;
		pDoc->dibHi.biWidth = pDoc->m_Out_width;

		//rwsize = WIDTHBYTES(pDoc->dibHi.biBitCount*pDoc->dibHi.biWidth);
		rwsize = WIDTHBYTES(pDoc->dibHi.biBitCount*pDoc->m_Out_width);
		BmInfo->bmiHeader = pDoc->dibHi;
		SetDIBitsToDevice(pDC->GetSafeHdc(), 512, 0, width, height, 0, 0, 0, height, pDoc->m_OutputImage, BmInfo, DIB_RGB_COLORS);
	}
	else	//8비트 컬러일 경우
	{
		int index;
		rwsize = WIDTHBYTES(pDoc->dibHi.biBitCount*pDoc->dibHi.biWidth);

		//팔레트를 읽어들이며 반복출력
		for (int i = 0; i < pDoc->dibHi.biHeight; i++)
			for (int j = 0; j < pDoc->dibHi.biWidth; j++) {
				index = pDoc->m_OutputImage[i*rwsize + j];
				BYTE R = pDoc->palRGB[index].rgbRed;
				BYTE G = pDoc->palRGB[index].rgbGreen;
				BYTE B = pDoc->palRGB[index].rgbBlue;

				//pDC->SetPixel(j,i,RGB(R,G,B));
				//영상 반전출력
				pDC->SetPixel(j+512, pDoc->dibHi.biHeight - i - 1, RGB(R, G, B));
			}
	}
	
}


// CImageCompositionView 인쇄


void CImageCompositionView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageCompositionView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImageCompositionView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImageCompositionView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CImageCompositionView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImageCompositionView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImageCompositionView 진단

#ifdef _DEBUG
void CImageCompositionView::AssertValid() const
{
	CView::AssertValid();
}

void CImageCompositionView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageCompositionDoc* CImageCompositionView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageCompositionDoc)));
	return (CImageCompositionDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageCompositionView 메시지 처리기



void CImageCompositionView::OnImgComp()
{
	CImageCompositionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnImgComp();
	Invalidate(TRUE);
}


void CImageCompositionView::OnDownsample()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CImageCompositionDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnDownsample();
	Invalidate(TRUE);
}
