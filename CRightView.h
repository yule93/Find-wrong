
/* 서브 뷰 RightView의 헤더 */

#pragma once
#include "MFCApplication2.h"
#include "MFCApplication2Doc.h"
class CRightView : public CView
{
	DECLARE_DYNCREATE(CRightView)

	// 특성입니다.
public:
	CMFCApplication2Doc * GetDocument() const;		// 해당 프로젝트의 도큐먼트 가져옴
protected:
	CRightView();
	virtual ~CRightView();

public:
	virtual void OnDraw(CDC* pDC);		// 클릭 시 뷰 위에 그림을 그리기 위한 OnDraw 함수 정의

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
	void CRightView::DrawRight(CPoint point);		// 그리기 함수 정의
};

#ifndef _DEBUG  // MFCApplication2View.cpp의 디버그 버전
inline CMFCApplication2Doc* CRightView::GetDocument() const
{
	return reinterpret_cast<CMFCApplication2Doc*>(m_pDocument);
}
#endif