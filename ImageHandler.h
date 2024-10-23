#pragma once
static int currentFontSize = 0;
static HFONT currentFont = nullptr;

class ImageHandler
{
public:
    // 단순한 다각형을 회전시키고 렌더링
    static void renderRotatedPolygon(HDC _hdc, Vector2 center, std::vector<Vector2Int> points, float angle);
    // 단순한 사각형을 회전시키고 렌더링
    static void renderRotatedRectangle(HDC hdc, Vector2 center, int width, int height, float angle);

    // .bmp을 불러와서 HBITMAP으로 변환
    static HBITMAP loadImg(std::wstring filePath);
    // 이미지를 중앙 기준 회전
    static HBITMAP RotateImage(HBITMAP hBitmap, float angle);
    // 이미지를 지정한 크기만큼 자르고 반환
    static HBITMAP cropImage(const HBITMAP& hOriginalBitmap, int x, int y, int width, int height);
    // 이미지를 지정한 크기만큼 자르고 반환(vector2 전용)
    static HBITMAP cropImage(const HBITMAP& origin, Vector2Int startPos, Vector2Int imgSize);
    // 이미지를 복사해서 옆에 붙여놓아서 크게 만들어주고 반환
    static HBITMAP duplicateImage(const HBITMAP& origin);
    // 이미지를 복사해서 옆에 여러번 붙여놓고 크기만큼 자른 뒤 반환(tessellation)
    static HBITMAP resizeImage(const HBITMAP& origin, int width, int height);
    // 이미지 디지털 줌 후 반환, 해상도 열화가 있음
    static HBITMAP zoomImage(const HBITMAP& origin, float magnification);
    // 이미지 회전
    static HBITMAP RotateBitmap(HBITMAP hBitmap, float angle);
    // 이미지 렌더
    static void Render(const HBITMAP& _bitMap, HDC& _hdc, int x, int y);
    // 이미지 렌더 - 뒷 배경을 투명하게 만듬(배경색 : RGB(255,0,255))
    static void renderWithoutBack(const HBITMAP& _bitMap, HDC& _hdc, int x, int y);
    static void renderWithoutBack(const HBITMAP& _bitMap, HDC& _hdc, Vector2Int startPos, Vector2Int size, Vector2Int imagePos);
    static void renderWithoutBack(const HBITMAP& _bitMap, HDC& _hdc, Vector2Int startPos, Vector2Int size, Vector2Int imagePos, bool reverse);

    // 이미지 렌더 - 이미지 전체를 alpha값(0~255, 값이 낮을수록 투명)만큼 투명하게 만듬
    static void TransparentRender(const HBITMAP& hBitmap, HDC& _hdc, int x, int y, BYTE alpha);
    // 이미지 렌더 - 이미지의 중앙점을 선택해 그곳을 중심으로 회전하고 뒷 배경까지 투명하게 만듬
    static void renderRotateWithoutBack(const HBITMAP& hBitmap, HDC& _hdc, Vector2Int pos, float angle, bool reverse);
    static void renderRotateWithoutBack(const HBITMAP& hBitmap, HDC& _hdc, Vector2Int pos, Vector2Int center, float angle, bool reverse, Vector2& imgSize);
    // 이미지 렌더 - 이미지 전체를 alpha값(0~255, 값이 낮을수록 투명)만큼 투명하게 만듬
    static void renderTransparentWithoutBack(const HBITMAP& hBitmap, HDC& _hdc, int x, int y, BYTE alpha);
    // 이미지 렌더 - 이미지를 디지털 줌 후 렌더해줌
    static void zoomRender(const HBITMAP& _hBitmap, HDC _hdc, int x, int y, float magnification);

    static HBITMAP shadowImage(const HBITMAP& _bitMap, int percent);
    static void DrawOutlinedText(HDC hdc, const wchar_t* text, int x, int y);
    static void DrawOutlinedText(HDC hdc, const wchar_t* text, int x, int y, COLORREF innerColor);
    static void textResize(int size, HDC _hdc)
    {
        // 폰트 크기가 이전과 같으면 폰트를 변경할 필요가 없음
        if (size == currentFontSize)
        {
            SelectObject(_hdc, currentFont);
            return;  // 변경 없음
        }

        // 이전 폰트가 있으면 삭제
        if (currentFont)
        {
            DeleteObject(currentFont);
        }

        // 새로운 폰트를 생성
        currentFont = CreateFont(
            size, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
            OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_DONTCARE, TEXT("Andy"));

        // 새로운 폰트를 DC에 선택
        SelectObject(_hdc, currentFont);

        // 현재 폰트 크기를 갱신
        currentFontSize = size;
        /**/
        /*
        HFONT hOldFont = (HFONT)GetCurrentObject(_hdc, OBJ_FONT);
        if (hOldFont)
        {
            LOGFONT logFont;
            // 기존 폰트 정보 가져오기
            if (GetObject(hOldFont, sizeof(LOGFONT), &logFont))
            {
                // 폰트 크기 변경
                logFont.lfHeight = size;

                // 새로운 폰트 생성
                HFONT hNewFont = CreateFontIndirect(&logFont);
                if (hNewFont)
                {
                    // 새 폰트를 DC에 선택하고 이전 폰트 반환
                    HFONT hPrevFont = (HFONT)SelectObject(_hdc, hNewFont);

                    // 선택된 폰트를 다시 원래 폰트로 복원
                    //SelectObject(_hdc, hPrevFont);
                    DeleteObject(hPrevFont);
                }
            }
        }
        */
        //HFONT newFont = CreateFont(
        //    size, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
        //    OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        //    DEFAULT_PITCH | FF_SWISS, L"Andy");
        //HFONT oldFont = (HFONT)SelectObject(_hdc, newFont);
        //oldFont = CreateFont(
        //    size, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
        //    OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
        //    DEFAULT_PITCH | FF_DONTCARE, TEXT("Andy"));
        //SelectObject(_hdc, oldFont);
        //DeleteObject(newFont);
        
    }
private:
    ImageHandler() {}
    ~ImageHandler() {}

    // 이미지 회전과 다각형 회전에 쓰는 함수
    static void RotatePoint(Vector2Int& point, const Vector2& center, float angle);
};

#define BackColor RGB(255, 0, 255)