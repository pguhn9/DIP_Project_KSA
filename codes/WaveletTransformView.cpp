
// WaveletTransformView.cpp: CWaveletTransformView 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "WaveletTransform.h"
#endif

#include "WaveletTransformDoc.h"
#include "WaveletTransformView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CWaveletTransformView

IMPLEMENT_DYNCREATE(CWaveletTransformView, CView)

BEGIN_MESSAGE_MAP(CWaveletTransformView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CWaveletTransformView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_WAVELET_TRANSFORM, &CWaveletTransformView::OnWaveletTransform)
END_MESSAGE_MAP()

// CWaveletTransformView 생성/소멸

CWaveletTransformView::CWaveletTransformView() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CWaveletTransformView::~CWaveletTransformView()
{
}

BOOL CWaveletTransformView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CWaveletTransformView 그리기

void CWaveletTransformView::OnDraw(CDC* pDC)
{
	CWaveletTransformDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here

	int i, j;
	int R, G, B;

	for (i = 0; i < pDoc->m_Height; i++) {
		for (j = 0; j < pDoc->m_Width; j++) {
			R = pDoc->m_InputImage[i*pDoc->m_Width + j];
			B = G = R;
			pDC->SetPixel(j + 5, i + 5, RGB(R, G, B));
			// 입력 영상을 화면에 출력
		}
	}
	for (i = 0; i < pDoc->m_Height; i++) {
		for (j = 0; j < pDoc->m_Width; j++) {
			R = pDoc->m_OutputImage[i*pDoc->m_Width + j];
			B = G = R;
			pDC->SetPixel(j + pDoc->m_Width + 10, i + 5, RGB(R, G, B));
			// 복원된 영상을 화면에 출력
		}
	}
}


// CWaveletTransformView 인쇄


void CWaveletTransformView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CWaveletTransformView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CWaveletTransformView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CWaveletTransformView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CWaveletTransformView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CWaveletTransformView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CWaveletTransformView 진단

#ifdef _DEBUG
void CWaveletTransformView::AssertValid() const
{
	CView::AssertValid();
}

void CWaveletTransformView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CWaveletTransformDoc* CWaveletTransformView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CWaveletTransformDoc)));
	return (CWaveletTransformDoc*)m_pDocument;
}
#endif //_DEBUG


// CWaveletTransformView 메시지 처리기


void CWaveletTransformView::OnWaveletTransform()
{
	CWaveletTransformDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnWaveletTransform(); // Doc 클래스에서 생성해야 할 함수 이름

	Invalidate(TRUE);
}
