
// MFCApplication2View.h: CMFCApplication2View 클래스의 인터페이스
//

#pragma once
#include "MFCApplication2Doc.h"


class CMFCApplication2View : public CView
{
protected: // serialization에서만 만들어집니다.
	CMFCApplication2View();
	DECLARE_DYNCREATE(CMFCApplication2View)

// 특성입니다.
public:
	CMFCApplication2Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// 구현입니다.
public:
	virtual ~CMFCApplication2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);

public:
	BITMAPINFO * BmInfo;
	int height;
	int width;
	int rwsize;
#define WIDTHBYTES(bits) (((bits)+31)/32*4)
public:
	CPoint m_point;
};

#ifndef _DEBUG  // MFCApplication2View.cpp의 디버그 버전
inline CMFCApplication2Doc* CMFCApplication2View::GetDocument() const
   { return reinterpret_cast<CMFCApplication2Doc*>(m_pDocument); }
#endif

