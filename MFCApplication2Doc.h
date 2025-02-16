
// MFCApplication2Doc.h: CMFCApplication2Doc 클래스의 인터페이스
//


#pragma once


class CMFCApplication2Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CMFCApplication2Doc();
	DECLARE_DYNCREATE(CMFCApplication2Doc)

// 특성입니다.
public:

// 작업입니다.
public:
	CPoint m_ptData[100]; // x
	int m_cnt;  // x
// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CMFCApplication2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS

public:
	BITMAPFILEHEADER dibHf1;
	BITMAPINFOHEADER dibHi1;
	RGBQUAD palRGB1[256];
	RGBQUAD palRGB2[256];
	BITMAPFILEHEADER dibHf2;
	BITMAPINFOHEADER dibHi2;
	unsigned char *m_LImg;
	unsigned char *m_RImg;
	// 컬러 영상 이미지 두 개를 불러오기 위해 두 번씩 선언
	int height;
	int width;
	int answer1;		// 정답 저장 변수 1
	int answer2;		// 정답 저장 변수 2
	int answer3;		// 정답 저장 변수 3
	//int *answer;
	int ImageToArray();
	int OX;

#define WIDTHBYTES(bits) (((bits)+31)/32*4)			// 컬러 비트맵 영상을 불러오기 위한 변수들 선언
};
