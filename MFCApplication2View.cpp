
// MFCApplication2View.cpp: CMFCApplication2View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCApplication2.h"
#endif

#include "MFCApplication2Doc.h"
#include "MFCApplication2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication2View

IMPLEMENT_DYNCREATE(CMFCApplication2View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication2View, CView)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

// CMFCApplication2View 생성/소멸

CMFCApplication2View::CMFCApplication2View()
{
	BmInfo = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + 256 * sizeof(RGBQUAD));		// 비트맵 정보
	for (int i = 0; i < 256; i++)
	{
		BmInfo->bmiColors[i].rgbRed
			= BmInfo->bmiColors[i].rgbGreen
			= BmInfo->bmiColors[i].rgbBlue
			= i;
		BmInfo->bmiColors[i].rgbReserved = 0;		// 비트맵 컬러 정보를 모두 bmiColors 배열에 저장
	}
}

CMFCApplication2View::~CMFCApplication2View()
{
	if (BmInfo) delete BmInfo;
}

BOOL CMFCApplication2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CMFCApplication2View 그리기

void CMFCApplication2View::OnDraw(CDC* pDC)
{
	CMFCApplication2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	
	CClientDC dc(this);
	
	//CImage Image;
	//Image.Load(_T("C:/Users/B10707/Desktop/MFCApplication2/test.jpg"));
	//Image.BitBlt(dc.m_hDC, 0, 0);

	CDC mdc;		// 비트맵을 임시 로딩할 DC
	mdc.CreateCompatibleDC(&dc);
	CBitmap bit, *oldbit;
	bit.LoadBitmapW(IDB_BITMAP_L);		// 왼쪽 뷰에 불러올 IDB_BITMAP_L 이미지 파일을 가져옴
	BITMAP bmp;
	bit.GetObject(sizeof(BITMAP), &bmp);		// 비트맵 파일을 불러오기 위한 선언
	oldbit = mdc.SelectObject(&bit);
	dc.TransparentBlt(0, 0, bmp.bmWidth, bmp.bmHeight, &mdc, 0, 0, bmp.bmWidth, bmp.bmHeight, RGB(255, 255, 255));		// 배경 투명화를 한 상태로 bmp를 얻어온다.
	mdc.SelectObject(oldbit);
	bit.DeleteObject();
	mdc.DeleteDC();		// 불러온 뒤 필요 없는 메모리 해제

	CString msg;
	int s = pDoc->dibHi1.biHeight*pDoc->dibHi1.biWidth;

	//for (int i = 0; i < s; i++) {
	//	msg.Format(_T("%d, %d"), m_point.x, m_point.y);
	//	pDC->TextOut(0, 0, msg);
	//}
}


// CMFCApplication2View 진단

#ifdef _DEBUG
void CMFCApplication2View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication2Doc* CMFCApplication2View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication2Doc)));
	return (CMFCApplication2Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication2View 메시지 처리기

void CMFCApplication2View::OnLButtonDown(UINT nFlags, CPoint point)		// 마우스의 왼쪽 버튼을 눌렀을 때(놓았을 때 아님) 좌표값 얻어오는 함수
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CMFCApplication2Doc* pDoc = GetDocument();
	if (pDoc->m_cnt < 100)
	{
		pDoc->m_ptData[pDoc->m_cnt] = point;		// 포인트 값 얻어옴
		pDoc->m_cnt++;
		pDoc->UpdateAllViews(NULL);		// 바뀐 변경사항을 뷰에 업데이트해서 적용
		m_point = point;
	}
	CView::OnLButtonDown(nFlags, point);
}
