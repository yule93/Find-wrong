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
	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.C:/Users/B10707/Desktop/MFCApplication2/
	CClientDC dc(this);
	
	/* CImage Image;
	Image.Load(_T("C:/Users/B10707/Desktop/MFCApplication2/test.jpg"));
	Image.BitBlt(dc.m_hDC, 0, 0); */
	
	CDC mdc;		// ��Ʈ���� �ӽ� �ε��� DC
	mdc.CreateCompatibleDC(&dc);
	CBitmap bit, *oldbit;
	bit.LoadBitmapW(IDB_BITMAP_R);		// ������ �信 �ҷ��� IDB_BITMAP_R �̹��� ������ ������
	BITMAP bmp;
	bit.GetObject(sizeof(BITMAP), &bmp);		// ��Ʈ�� ������ �ҷ����� ���� ����
	oldbit = mdc.SelectObject(&bit);
	dc.TransparentBlt(0, 0, bmp.bmWidth, bmp.bmHeight, &mdc, 0, 0, bmp.bmWidth, bmp.bmHeight, RGB(255, 255, 255));		// ��� ����ȭ�� �� ���·� bmp�� ���´�.
	mdc.SelectObject(oldbit);
	bit.DeleteObject();
	mdc.DeleteDC();			// �ҷ��� �� �ʿ� ���� �޸� ����

	for (int num = 0; num < pDoc->m_cnt; num++)		// Ŭ���� Ƚ����ŭ DrawRight �Լ��� ���
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
	CDC mdc;		// ��Ʈ���� �ӽ� �ε��� DC
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

	
	if (OX==0/*point.y<285*/)		// ������ �ƴ� ��� X ����� ��Ʈ���� �ҷ��� �׸�
		bit.LoadBitmapW(IDC_BITMAP_X);
	else {			// ������ ���� ��� O ����� ��Ʈ���� �ҷ��� �׸�
		bit.LoadBitmapW(IDC_BITMAP_O);		
	}
		
	oldbit = mdc.SelectObject(&bit);		// ������Ʈ �����ؼ� mdc�� �ӽ� �ε�
	dc.TransparentBlt((point.x)-10, (point.y)-10, 20, 20, &mdc, 0, 0, 20, 20, RGB(255, 255, 255));		// Ŭ���� point�� ��ǥ���� ���� mdc�� �������ȭ�� ä �ѷ��ش�.
	mdc.SelectObject(oldbit);
	bit.DeleteObject();
	mdc.DeleteDC();		// �� �� �ѷ��� �� ����
	
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
CMFCApplication2Doc* CRightView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication2Doc)));
	return (CMFCApplication2Doc*)m_pDocument;
}
#endif // _DEBUG
