#pragma once
static int currentFontSize = 0;
static HFONT currentFont = nullptr;

class ImageHandler
{
public:
    // �ܼ��� �ٰ����� ȸ����Ű�� ������
    static void renderRotatedPolygon(HDC _hdc, Vector2 center, std::vector<Vector2Int> points, float angle);
    // �ܼ��� �簢���� ȸ����Ű�� ������
    static void renderRotatedRectangle(HDC hdc, Vector2 center, int width, int height, float angle);

    // .bmp�� �ҷ��ͼ� HBITMAP���� ��ȯ
    static HBITMAP loadImg(std::wstring filePath);
    // �̹����� �߾� ���� ȸ��
    static HBITMAP RotateImage(HBITMAP hBitmap, float angle);
    // �̹����� ������ ũ�⸸ŭ �ڸ��� ��ȯ
    static HBITMAP cropImage(const HBITMAP& hOriginalBitmap, int x, int y, int width, int height);
    // �̹����� ������ ũ�⸸ŭ �ڸ��� ��ȯ(vector2 ����)
    static HBITMAP cropImage(const HBITMAP& origin, Vector2Int startPos, Vector2Int imgSize);
    // �̹����� �����ؼ� ���� �ٿ����Ƽ� ũ�� ������ְ� ��ȯ
    static HBITMAP duplicateImage(const HBITMAP& origin);
    // �̹����� �����ؼ� ���� ������ �ٿ����� ũ�⸸ŭ �ڸ� �� ��ȯ(tessellation)
    static HBITMAP resizeImage(const HBITMAP& origin, int width, int height);
    // �̹��� ������ �� �� ��ȯ, �ػ� ��ȭ�� ����
    static HBITMAP zoomImage(const HBITMAP& origin, float magnification);
    // �̹��� ȸ��
    static HBITMAP RotateBitmap(HBITMAP hBitmap, float angle);
    // �̹��� ����
    static void Render(const HBITMAP& _bitMap, HDC& _hdc, int x, int y);
    // �̹��� ���� - �� ����� �����ϰ� ����(���� : RGB(255,0,255))
    static void renderWithoutBack(const HBITMAP& _bitMap, HDC& _hdc, int x, int y);
    static void renderWithoutBack(const HBITMAP& _bitMap, HDC& _hdc, Vector2Int startPos, Vector2Int size, Vector2Int imagePos);
    static void renderWithoutBack(const HBITMAP& _bitMap, HDC& _hdc, Vector2Int startPos, Vector2Int size, Vector2Int imagePos, bool reverse);

    // �̹��� ���� - �̹��� ��ü�� alpha��(0~255, ���� �������� ����)��ŭ �����ϰ� ����
    static void TransparentRender(const HBITMAP& hBitmap, HDC& _hdc, int x, int y, BYTE alpha);
    // �̹��� ���� - �̹����� �߾����� ������ �װ��� �߽����� ȸ���ϰ� �� ������ �����ϰ� ����
    static void renderRotateWithoutBack(const HBITMAP& hBitmap, HDC& _hdc, Vector2Int pos, float angle, bool reverse);
    static void renderRotateWithoutBack(const HBITMAP& hBitmap, HDC& _hdc, Vector2Int pos, Vector2Int center, float angle, bool reverse, Vector2& imgSize);
    // �̹��� ���� - �̹��� ��ü�� alpha��(0~255, ���� �������� ����)��ŭ �����ϰ� ����
    static void renderTransparentWithoutBack(const HBITMAP& hBitmap, HDC& _hdc, int x, int y, BYTE alpha);
    // �̹��� ���� - �̹����� ������ �� �� ��������
    static void zoomRender(const HBITMAP& _hBitmap, HDC _hdc, int x, int y, float magnification);

    static HBITMAP shadowImage(const HBITMAP& _bitMap, int percent);
    static void DrawOutlinedText(HDC hdc, const wchar_t* text, int x, int y);
    static void DrawOutlinedText(HDC hdc, const wchar_t* text, int x, int y, COLORREF innerColor);
    static void textResize(int size, HDC _hdc)
    {
        // ��Ʈ ũ�Ⱑ ������ ������ ��Ʈ�� ������ �ʿ䰡 ����
        if (size == currentFontSize)
        {
            SelectObject(_hdc, currentFont);
            return;  // ���� ����
        }

        // ���� ��Ʈ�� ������ ����
        if (currentFont)
        {
            DeleteObject(currentFont);
        }

        // ���ο� ��Ʈ�� ����
        currentFont = CreateFont(
            size, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
            OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_DONTCARE, TEXT("Andy"));

        // ���ο� ��Ʈ�� DC�� ����
        SelectObject(_hdc, currentFont);

        // ���� ��Ʈ ũ�⸦ ����
        currentFontSize = size;
        /**/
        /*
        HFONT hOldFont = (HFONT)GetCurrentObject(_hdc, OBJ_FONT);
        if (hOldFont)
        {
            LOGFONT logFont;
            // ���� ��Ʈ ���� ��������
            if (GetObject(hOldFont, sizeof(LOGFONT), &logFont))
            {
                // ��Ʈ ũ�� ����
                logFont.lfHeight = size;

                // ���ο� ��Ʈ ����
                HFONT hNewFont = CreateFontIndirect(&logFont);
                if (hNewFont)
                {
                    // �� ��Ʈ�� DC�� �����ϰ� ���� ��Ʈ ��ȯ
                    HFONT hPrevFont = (HFONT)SelectObject(_hdc, hNewFont);

                    // ���õ� ��Ʈ�� �ٽ� ���� ��Ʈ�� ����
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

    // �̹��� ȸ���� �ٰ��� ȸ���� ���� �Լ�
    static void RotatePoint(Vector2Int& point, const Vector2& center, float angle);
};

#define BackColor RGB(255, 0, 255)