
/* ���� �� RightView�� ��� */

#pragma once
#include "MFCApplication2.h"
#include "MFCApplication2Doc.h"
class CRightView : public CView
{
	DECLARE_DYNCREATE(CRightView)

	// Ư���Դϴ�.
public:
	CMFCApplication2Doc * GetDocument() const;		// �ش� ������Ʈ�� ��ť��Ʈ ������
protected:
	CRightView();
	virtual ~CRightView();

public:
	virtual void OnDraw(CDC* pDC);		// Ŭ�� �� �� ���� �׸��� �׸��� ���� OnDraw �Լ� ����

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	void CRightView::DrawRight(CPoint point);		// �׸��� �Լ� ����
};

#ifndef _DEBUG  // MFCApplication2View.cpp�� ����� ����
inline CMFCApplication2Doc* CRightView::GetDocument() const
{
	return reinterpret_cast<CMFCApplication2Doc*>(m_pDocument);
}
#endif