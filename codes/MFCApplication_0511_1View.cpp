
// MFCApplication_0511_1View.cpp: CMFCApplication05111View 클래스의 구현
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCApplication_0511_1.h"
#endif

#include "MFCApplication_0511_1Doc.h"
#include "MFCApplication_0511_1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication05111View

IMPLEMENT_DYNCREATE(CMFCApplication05111View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication05111View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCApplication05111View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_DOWN_SAMPLING, &CMFCApplication05111View::OnDownSampling)
	ON_COMMAND(ID_Up_Sampling, &CMFCApplication05111View::OnUpSampling)
	ON_COMMAND(ID_QUANTIZATION, &CMFCApplication05111View::OnQuantization)
//	ON_COMMAND(ID_SUM_CONSTANT, &CMFCApplication05111View::OnSumConstant)
ON_COMMAND(ID_SUM_CONSTANT, &CMFCApplication05111View::OnSumConstant)
ON_COMMAND(ID_SUB_CONSTANT, &CMFCApplication05111View::OnSubConstant)
ON_COMMAND(ID_MUL_CONSTANT, &CMFCApplication05111View::OnMulConstant)
ON_COMMAND(ID_DIV_CONSTANT, &CMFCApplication05111View::OnDivConstant)
ON_COMMAND(ID_AND_OPERATE, &CMFCApplication05111View::OnAndOperate)
ON_COMMAND(ID_OR_OPERATE, &CMFCApplication05111View::OnOrOperate)
ON_COMMAND(ID_XOR_OPERATE, &CMFCApplication05111View::OnXorOperate)
ON_COMMAND(ID_NEGA_TRANSFORM, &CMFCApplication05111View::OnNegaTransform)
ON_COMMAND(ID_GAMMA_CORRECTION, &CMFCApplication05111View::OnGammaCorrection)
ON_COMMAND(ID_BINARIZATION, &CMFCApplication05111View::OnBinarization)
ON_COMMAND(ID_STRESS_TRANSFORM, &CMFCApplication05111View::OnStressTransform)
ON_COMMAND(ID_HISTO_STRETCH, &CMFCApplication05111View::OnHistoStretch)
ON_COMMAND(ID_END_IN_SEARCH, &CMFCApplication05111View::OnEndInSearch)
ON_COMMAND(ID_HISTOGRAM, &CMFCApplication05111View::OnHistogram)
ON_COMMAND(ID_HISTO_EQUAL, &CMFCApplication05111View::OnHistoEqual)
ON_COMMAND(ID_HISTO_SPEC, &CMFCApplication05111View::OnHistoSpec)
ON_COMMAND(ID_EMBOSSING, &CMFCApplication05111View::OnEmbossing)
ON_COMMAND(ID_BLURR, &CMFCApplication05111View::OnBlurr)
ON_COMMAND(ID_GAUSSIAN_FILTER, &CMFCApplication05111View::OnGaussianFilter)
ON_COMMAND(ID_SHARPNING, &CMFCApplication05111View::OnSharpning)
ON_COMMAND(ID_HPR_SHARP, &CMFCApplication05111View::OnHprSharp)
ON_COMMAND(ID_LPF_SHARP, &CMFCApplication05111View::OnLpfSharp)
ON_COMMAND(ID_CONVOL_SUM, &CMFCApplication05111View::OnConvolSum)
ON_COMMAND(ID_TRANSLATION, &CMFCApplication05111View::OnTranslation)
ON_COMMAND(ID_MIRROR_HOR, &CMFCApplication05111View::OnMirrorHor)
ON_COMMAND(ID_MIRROR_VER, &CMFCApplication05111View::OnMirrorVer)
ON_COMMAND(ID_TRANSLATION2, &CMFCApplication05111View::OnTranslation2)
ON_COMMAND(ID_FRAME_AND, &CMFCApplication05111View::OnFrameAnd)
ON_COMMAND(ID_FRAME_CONB, &CMFCApplication05111View::OnFrameConb)
ON_COMMAND(ID_FRAME_DIV, &CMFCApplication05111View::OnFrameDiv)
ON_COMMAND(ID_FRAME_MUL, &CMFCApplication05111View::OnFrameMul)
ON_COMMAND(ID_FRAME_OR, &CMFCApplication05111View::OnFrameOr)
ON_COMMAND(ID_FRAME_SUB, &CMFCApplication05111View::OnFrameSub)
ON_COMMAND(ID_FRAME_SUM, &CMFCApplication05111View::OnFrameSum)
ON_COMMAND(ID_BINARY_DILATION, &CMFCApplication05111View::OnBinaryDilation)
ON_COMMAND(ID_BINARY_EROSION, &CMFCApplication05111View::OnBinaryErosion)
ON_COMMAND(ID_GRAY_DILATION, &CMFCApplication05111View::OnGrayDilation)
ON_COMMAND(ID_GRAY_EROSION, &CMFCApplication05111View::OnGrayErosion)
ON_COMMAND(ID_LOW_PASS_FILTER, &CMFCApplication05111View::OnLowPassFilter)
ON_COMMAND(ID_HIGH_PASS_FILTER, &CMFCApplication05111View::OnHighPassFilter)
ON_COMMAND(ID_MEAN_FILTER, &CMFCApplication05111View::OnMeanFilter)
ON_COMMAND(ID_MEDIAN_FILTER, &CMFCApplication05111View::OnMedianFilter)
ON_COMMAND(ID_MAX_FILTER, &CMFCApplication05111View::OnMaxFilter)
ON_COMMAND(ID_MIN_FILTER, &CMFCApplication05111View::OnMinFilter)
ON_COMMAND(ID_FFT_2D, &CMFCApplication05111View::OnFft2d)
ON_COMMAND(ID_DIFF_OPERATOR_HOR, &CMFCApplication05111View::OnDiffOperatorHor)
ON_COMMAND(ID_HOMOGEN_OPERATOR, &CMFCApplication05111View::OnHomogenOperator)
ON_COMMAND(ID_LAPLACIAN, &CMFCApplication05111View::OnLaplacian)
ON_COMMAND(ID_NEAREST, &CMFCApplication05111View::OnNearest)
ON_COMMAND(ID_BILINEAR, &CMFCApplication05111View::OnBilinear)
ON_COMMAND(ID_MEDIAN_SUB, &CMFCApplication05111View::OnMedianSub)
ON_COMMAND(ID_MEAN_SUB, &CMFCApplication05111View::OnMeanSub)
END_MESSAGE_MAP()

// CMFCApplication05111View 생성/소멸

CMFCApplication05111View::CMFCApplication05111View() noexcept
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CMFCApplication05111View::~CMFCApplication05111View()
{
}

BOOL CMFCApplication05111View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}






// CMFCApplication05111View 그리기
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


// CMFCApplication05111View 인쇄


void CMFCApplication05111View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCApplication05111View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CMFCApplication05111View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CMFCApplication05111View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CMFCApplication05111View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CMFCApplication05111View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCApplication05111View 진단

#ifdef _DEBUG
void CMFCApplication05111View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication05111View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication05111Doc* CMFCApplication05111View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication05111Doc)));
	return (CMFCApplication05111Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication05111View 메시지 처리기





void CMFCApplication05111View::OnDownSampling()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnDownSampling();

	Invalidate(TRUE);
}


void CMFCApplication05111View::OnUpSampling()
{

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnUpSampling();
	Invalidate(TRUE);

}


void CMFCApplication05111View::OnQuantization()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnQuantization();
	Invalidate(TRUE);

}


//void CMFCApplication05111View::OnSumConstant()
//{
//	// TODO: 여기에 명령 처리기 코드를 추가합니다.
//	CMFCApplication05111Doc* pDoc = GetDocument();
//	ASSERT_VALID(pDoc);
//
//	pDoc->OnSumConstant();
//	Invalidate(TRUE);
//
//
//}


void CMFCApplication05111View::OnSumConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSumConstant();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnSubConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSubConstant();
	Invalidate(TRUE);


}


void CMFCApplication05111View::OnMulConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMulConstant();
	Invalidate(TRUE);



}


void CMFCApplication05111View::OnDivConstant()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnDivConstant();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnAndOperate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnAndOperate();
	Invalidate(TRUE);

}


void CMFCApplication05111View::OnOrOperate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnOrOperate();
	Invalidate(TRUE);



}


void CMFCApplication05111View::OnXorOperate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnXorOperate();
	Invalidate(TRUE);

}


void CMFCApplication05111View::OnNegaTransform()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnNegaTransform();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnGammaCorrection()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnGammaCorrection();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnBinarization()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnBinarization();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnStressTransform()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnStressTransform();
	Invalidate(TRUE);

}


void CMFCApplication05111View::OnHistoStretch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnHistoStretch();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnEndInSearch()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	pDoc->OnEndInSearch();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnHistogram()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistogram();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnHistoEqual()
{	
	CMFCApplication05111Doc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoEqual();
	Invalidate(TRUE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CMFCApplication05111View::OnHistoSpec()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHistoSpec();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnEmbossing()
{
	CMFCApplication05111Doc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnEmbossing();
	Invalidate(TRUE);
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CMFCApplication05111View::OnBlurr()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBlurr();
	Invalidate(TRUE);

}


void CMFCApplication05111View::OnGaussianFilter()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnGaussianFilter();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnSharpning()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnSharpning();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnHprSharp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHprSharp();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnLpfSharp()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnLpfSharp();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnConvolSum()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnConvolSum();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnTranslation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnTranslation();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnMirrorHor()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMirrorHor();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnMirrorVer()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMirrorVer();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnTranslation2()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnTranslation2();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnFrameAnd()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnFrameAnd();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnFrameConb()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnFrameConb();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnFrameDiv()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnFrameDiv();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnFrameMul()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnFrameMul();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnFrameOr()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnFrameOr();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnFrameSub()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnFrameSub();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnFrameSum()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnFrameSum();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnBinaryDilation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBinaryDilation();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnBinaryErosion()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBinaryErosion();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnGrayDilation()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnGrayDilation();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnGrayErosion()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnGrayErosion();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnLowPassFilter()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnLowPassFilter();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnHighPassFilter()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHighPassFilter();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnMeanFilter()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMeanFilter();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnMedianFilter()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMedianFilter();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnMaxFilter()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMaxFilter();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnMinFilter()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc*pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMinFilter();
	Invalidate(TRUE);
}


void CMFCApplication05111View::OnFft2d()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CMFCApplication05111View::OnDiffOperatorHor()
{
	CMFCApplication05111Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnDiffOperatorHor();

	Invalidate(TRUE);

	// TODO: 여기에 명령 처리기 코드를 추가합니다.
}


void CMFCApplication05111View::OnHomogenOperator()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnHomogenOperator();

	Invalidate(TRUE);

}


void CMFCApplication05111View::OnLaplacian()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnLaplacian();

	Invalidate(TRUE);

}


void CMFCApplication05111View::OnNearest()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnNearest();

	Invalidate(TRUE);

}


void CMFCApplication05111View::OnBilinear()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnBilinear();

	Invalidate(TRUE);

}


void CMFCApplication05111View::OnMedianSub()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMedianSub();

	Invalidate(TRUE);

}


void CMFCApplication05111View::OnMeanSub()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	CMFCApplication05111Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	pDoc->OnMeanSub();

	Invalidate(TRUE);

}
