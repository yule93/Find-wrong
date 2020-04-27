#include "stdafx.h"
#ifndef SHARED_HANDLERS
#include "MFCApplication2.h"
#endif
#include "MFCApplication2Doc.h"
#include "CRightView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

IMPLEMENT_DYNCREATE(CRightView, CView)

BEGIN_MESSAGE_MAP(CRightView, CView)
END_MESSAGE_MAP()



CRightView::CRightView()
{
}


CRightView::~CRightView()
{
}

void CRightView::OnDraw(CDC* pDC)
{
	CMFCApplication2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.C:/Users/B10707/Desktop/MFCApplication2/
	CClientDC dc(this);
	
	/* CImage Image;
	Image.Load(_T("C:/Users/B10707/Desktop/MFCApplication2/test.jpg"));
	Image.BitBlt(dc.m_hDC, 0, 0); */
	
	CDC mdc;		// 비트맵을 임시 로딩할 DC
	mdc.CreateCompatibleDC(&dc);
	CBitmap bit, *oldbit;
	bit.LoadBitmapW(IDB_BITMAP_R);		// 오른쪽 뷰에 불러올 IDB_BITMAP_R 이미지 파일을 가져옴
	BITMAP bmp;
	bit.GetObject(sizeof(BITMAP), &bmp);		// 비트맵 파일을 불러오기 위한 선언
	oldbit = mdc.SelectObject(&bit);
	dc.TransparentBlt(0, 0, bmp.bmWidth, bmp.bmHeight, &mdc, 0, 0, bmp.bmWidth, bmp.bmHeight, RGB(255, 255, 255));		// 배경 투명화를 한 상태로 bmp를 얻어온다.
	mdc.SelectObject(oldbit);
	bit.DeleteObject();
	mdc.DeleteDC();			// 불러온 뒤 필요 없는 메모리 해제

	for (int num = 0; num < pDoc->m_cnt; num++)		// 클릭한 횟수만큼 DrawRight 함수를 사용
	{
		DrawRight(pDoc->m_ptData[num]);
	}

	CString msg;
	int s = pDoc->dibHi1.biHeight*pDoc->dibHi1.biWidth;
	
	/*for (int i = 0; i < s; i++) {
		msg.Format(_T("%d, %d, %d"), pDoc->answer1, pDoc->answer2, pDoc->answer3);
		pDC->TextOut(0, 0, msg);
	} */
}
void CRightView::DrawRight(CPoint point)
{
	CMFCApplication2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	CClientDC dc(this);
	CDC mdc;		// 비트맵을 임시 로딩할 DC
	mdc.CreateCompatibleDC(&dc);
	CBitmap bit, *oldbit;
	int rwsize = WIDTHBYTES(pDoc->dibHi1.biBitCount*pDoc->width);
	int OX=0;
	for (int i = 0; i < 3; i++)
	{
		//if ((point.x*rwsize + point.y) == pDoc->answer1)
		if((point.x>250 && point.y<40)
			|| (point.x>230 && point.x<260 && point.y>340 && point.y<360)
			|| (point.x>75 && point.x<95 && point.y>185 && point.y<215)
			|| (point.x>130 && point.x<140 && point.y>125 && point.y<145)
			|| (point.x>330 && point.x<350 && point.y>350 && point.y<380))
		{
			OX = 1;
			break;
		}
	}

	
	if (OX==0/*point.y<285*/)		// 정답이 아닐 경우 X 모양의 비트맵을 불러와 그림
		bit.LoadBitmapW(IDC_BITMAP_X);
	else {			// 정답이 맞을 경우 O 모양의 비트맵을 불러와 그림
		bit.LoadBitmapW(IDC_BITMAP_O);		
	}
		
	oldbit = mdc.SelectObject(&bit);		// 오브젝트 선택해서 mdc에 임시 로딩
	dc.TransparentBlt((point.x)-10, (point.y)-10, 20, 20, &mdc, 0, 0, 20, 20, RGB(255, 255, 255));		// 클릭한 point의 좌표값을 얻어와 mdc를 배경투명화한 채 뿌려준다.
	mdc.SelectObject(oldbit);
	bit.DeleteObject();
	mdc.DeleteDC();		// 한 번 뿌려준 뒤 끝냄
	
	/*dc.MoveTo(point.x - 25, point.y - 25);
	dc.LineTo(point.x + 25, point.y + 25);
	dc.MoveTo(point.x + 25, point.y - 25);
	dc.LineTo(point.x - 25, point.y + 25);*/
}

#ifdef _DEBUG
void CRightView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CRightView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
CMFCApplication2Doc* CRightView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication2Doc)));
	return (CMFCApplication2Doc*)m_pDocument;
}
#endif // _DEBUG
