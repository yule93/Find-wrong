
// MFCApplication2Doc.cpp: CMFCApplication2Doc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCApplication2.h"
#endif

#include "MFCApplication2Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCApplication2Doc

IMPLEMENT_DYNCREATE(CMFCApplication2Doc, CDocument)

BEGIN_MESSAGE_MAP(CMFCApplication2Doc, CDocument)
END_MESSAGE_MAP()


// CMFCApplication2Doc 생성/소멸

CMFCApplication2Doc::CMFCApplication2Doc():m_cnt(0), answer1(0)
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
	m_LImg = NULL;
	m_RImg = NULL;
	for (int i = 0; i < 256; i++)		// 컬러 영상 이미지를 불러오기 위한 행렬
	{
		palRGB1[i].rgbBlue = palRGB1[i].rgbGreen = palRGB1[i].rgbRed = i;
		palRGB1[i].rgbReserved = 0;
	}
	//ImageToArray();
}

CMFCApplication2Doc::~CMFCApplication2Doc()
{
	if (m_LImg) delete[] m_LImg;
	if (m_RImg) delete[] m_RImg;		// 이미지를 쓸모 없어지면 메모리 할당을 해제
}

BOOL CMFCApplication2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CMFCApplication2Doc serialization

void CMFCApplication2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CMFCApplication2Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CMFCApplication2Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCApplication2Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCApplication2Doc 진단

#ifdef _DEBUG
void CMFCApplication2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCApplication2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCApplication2Doc 명령


int CMFCApplication2Doc::ImageToArray()
{
	// TODO: 여기에 구현 코드 추가.
	CFile LFile, RFile;
	LFile.Open(_T("res\\left.bmp"), CFile::modeRead | CFile::typeBinary);		// 왼쪽 뷰에 붙일 이미지1을 가져옴
	LFile.Read(&dibHf1, sizeof(BITMAPFILEHEADER));		// 가져온 이미지1의 파일 헤더를 읽음
	RFile.Open(_T("res\\right.bmp"), CFile::modeRead | CFile::typeBinary);		// 오른쪽 뷰에 붙일 이미지2를 가져옴
	RFile.Read(&dibHf2, sizeof(BITMAPFILEHEADER));		// 가져온 이미지2의 파일 헤더를 읽음
	if (dibHf1.bfType != 0x4D42 || dibHf2.bfType != 0x4D42)
	{
		AfxMessageBox(L"Not BMP File!!");
		return FALSE;
	}

	LFile.Read(&dibHi1, sizeof(BITMAPINFOHEADER));
	RFile.Read(&dibHi2, sizeof(BITMAPINFOHEADER));
	if (dibHi1.biBitCount != 8 && dibHi1.biBitCount != 24)
	{
		AfxMessageBox(L"Gray/True Color Possible!!");
		return FALSE;
	}
	if (dibHi2.biBitCount != 8 && dibHi2.biBitCount != 24)
	{
		AfxMessageBox(L"Gray/True Color Possible!!");
		return FALSE;
	}
	if (dibHi1.biBitCount == 8)		// 8비트 비트맵일 경우 RGB로 읽어오기
		LFile.Read(palRGB1, sizeof(RGBQUAD) * 256);		// 256색 생성
	if (dibHi2.biBitCount == 8)		// 8비트 비트맵일 경우 RGB로 읽어오기
		RFile.Read(palRGB2, sizeof(RGBQUAD) * 256);

	int ImgSize;
	if (dibHi1.biBitCount == 8)
	{
		ImgSize = LFile.GetLength() - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER) - 256 * sizeof(RGBQUAD);
	}
	else if (dibHi1.biBitCount == 24)
	{
		ImgSize = LFile.GetLength() - sizeof(BITMAPFILEHEADER) - sizeof(BITMAPINFOHEADER);
	}

	m_LImg = new unsigned char[ImgSize];		// 왼쪽 이미지1을 저장할 배열 선언
	m_RImg = new unsigned char[ImgSize];		// 오른쪽 이미지2를 저장할 배열 선언
	LFile.Read(m_LImg, ImgSize);
	RFile.Read(m_RImg, ImgSize);
	LFile.Close();
	RFile.Close();		// 읽어온 후 파일 닫기
	height = dibHi1.biHeight; width = dibHi1.biWidth;
	
	//if (dibHi1.biBitCount == 24)
	//	return TRUE;
	//if (dibHi2.biBitCount == 24)
	//	return TRUE;
	
	int i, j, index;
	int rwsize = WIDTHBYTES(dibHi1.biBitCount*width);
	
	for (i = 0; i < height; i++)
	{
		index = i * rwsize;
		for (j = 0; j < width; j++)		// 읽어온 이미지 파일 1, 2를 각각 배열에 저장
		{
			m_LImg[index + j] = (unsigned char)palRGB1[(int)m_LImg[index + j]].rgbBlue;
			m_RImg[index + j] = (unsigned char)palRGB2[(int)m_RImg[index + j]].rgbBlue;
		}
	}
	

	int count = 0;
	for (i = 0; i < height; i++)		// 정답을 미리 구해놓는 부분. 이미지에 따라 카운트 횟수 더 늘어날 수 있음.
	{
		index = i * rwsize;
		for (j = 0; j < width; j++)
		{
			int tempVal = (abs)(m_LImg[index + j] - m_RImg[index + j]);		// 두 이미지의 차 계산
			if (tempVal != 0)
			{
				if (count == 0)		// 첫 번째 정답
					answer1 = index + j;		// answer1에 해당 정답 저장
				if(count==1)		// 두 번째 정답
					answer2 = index + j;		// answer2에 해당 정답 저장
				if(count==2)		// 세 번째 정답
					answer3 = index + j;		// answer3에 해당 정답 저장
					
				count++;		// 카운트 ++
				if (count > 2)
					return TRUE;		// 정답을 다 찾으면 정지
			}
		}
	}
	return TRUE;
}
