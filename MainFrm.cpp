
// MainFrm.cpp: CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "MFCApplication2.h"
#include "MFCApplication2Doc.h"

#include "MainFrm.h"
#include "MFCApplication2View.h"
#include "CRightView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // 상태 줄 표시기
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("상태 표시줄을 만들지 못했습니다.\n");
		return -1;      // 만들지 못했습니다.
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	cs.cx = 790;		// 메인 프레임의 x축 크기 설정
	cs.cy = 570;		// 메인 프레임의 y축 크기 설정
	cs.y = 200;			// 실행 화면이 윈도우 화면에서 나타나는 x축 위치
	cs.x = 300;			// 실행 화면이 윈도우 화면에서 나타나는 y축 위치
	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CRect rect;
	GetClientRect(rect);	// 윈도우 클라이언트 영역사에서 좌표값을 반환한다.
	m_wndSplit.CreateStatic(this, 1, 2);	// 메인 프레임을 1행 2열로 나눈다.
	m_wndSplit.CreateView(0, 0, RUNTIME_CLASS(CMFCApplication2View), CSize(rect.Width() / 2, 500), pContext);
	// (0, 0)번째 행렬 프레임에 CMFCApplication2View를 붙인다.
	m_wndSplit.CreateView(0, 1, RUNTIME_CLASS(CRightView), CSize(rect.Width() / 2, 500), pContext);	
	// (0, 1)번째 행렬 프레임에 CRightView를 붙인다.
	return TRUE;
	//return CFrameWnd::OnCreateClient(lpcs, pContext);
}
