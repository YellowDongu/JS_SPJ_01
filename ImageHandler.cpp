#include "framework.h"
#include "ImageHandler.h"


void ImageHandler::Render(const HBITMAP& _bitMap, HDC& _hdc, int x, int y)
{
    if (_bitMap == NULL) { return; }
    BITMAP bitmap;
    GetObject(_bitMap, sizeof(BITMAP), &bitmap);

    HDC dcMem = CreateCompatibleDC(_hdc);
    SelectObject(dcMem, _bitMap);

    BitBlt(_hdc, x, y, bitmap.bmWidth, bitmap.bmHeight, dcMem, 0, 0, SRCCOPY);

    DeleteDC(dcMem);
}


HBITMAP ImageHandler::loadImg(std::wstring filePath)
{
    return (HBITMAP)LoadImage(NULL, filePath.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

HBITMAP ImageHandler::cropImage(const HBITMAP& origin, int x, int y, int width, int height)
{
    HDC hdc = CreateCompatibleDC(NULL);
    HDC hdcMem = CreateCompatibleDC(NULL);

    // ���� ����
    // ���� ���õ� ��Ʈ���� ����
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdc, origin);
    // ���� ��

    HBITMAP hCroppedBitmap = CreateCompatibleBitmap(hdc, width, height);

    // ���� ����
    // ���� ������ ��Ʈ���� �޸� DC�� ����
    HBITMAP hOldCroppedBitmap = (HBITMAP)SelectObject(hdcMem, hCroppedBitmap);
    // ���� ��

    BitBlt(hdcMem, 0, 0, width, height, hdc, x, y, SRCCOPY);

    // ���� ����
    // DC���� ���� ��Ʈ������ ����
    SelectObject(hdc, hOldBitmap);
    SelectObject(hdcMem, hOldCroppedBitmap);
    // ���� ��

    // �߰� ����
    // GDI ��ü ����
    DeleteObject(hOldBitmap);
    DeleteObject(hOldCroppedBitmap);
    // �߰� ��

    DeleteDC(hdc);
    DeleteDC(hdcMem);

    return hCroppedBitmap;
}

HBITMAP ImageHandler::cropImage(const HBITMAP& origin, Vector2Int startPos, Vector2Int imgSize)
{
    /*
    HDC hdc = CreateCompatibleDC(NULL);
    HDC hdcMem = CreateCompatibleDC(NULL);

    SelectObject(hdc, origin);
    HBITMAP hCroppedBitmap = CreateCompatibleBitmap(hdc, imgSize.x, imgSize.y);
    SelectObject(hdcMem, hCroppedBitmap);
    BitBlt(hdcMem, 0, 0, imgSize.x, imgSize.y, hdc, startPos.x, startPos.y, SRCCOPY);

    DeleteDC(hdc);
    DeleteDC(hdcMem);

    return hCroppedBitmap;
    */
    HDC hdc = CreateCompatibleDC(NULL);
    HDC hdcMem = CreateCompatibleDC(NULL);

    // ���� ����
    // ���� ���õ� ��Ʈ���� ����
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdc, origin);
    // ���� ��

    HBITMAP hCroppedBitmap = CreateCompatibleBitmap(hdc, imgSize.x, imgSize.y);

    // ���� ����
    // ���� ������ ��Ʈ���� �޸� DC�� ����
    HBITMAP hOldCroppedBitmap = (HBITMAP)SelectObject(hdcMem, hCroppedBitmap);
    // ���� ��

    BitBlt(hdcMem, 0, 0, imgSize.x, imgSize.y, hdc, startPos.x, startPos.y, SRCCOPY);

    // ���� ����
    // DC���� ���� ��Ʈ������ ����
    SelectObject(hdc, hOldBitmap);
    SelectObject(hdcMem, hOldCroppedBitmap);
    // ���� ��

    // �߰� ����
    // GDI ��ü ����
    DeleteObject(hOldBitmap);
    DeleteObject(hOldCroppedBitmap);
    // �߰� ��

    DeleteDC(hdc);
    DeleteDC(hdcMem);

    return hCroppedBitmap;
}


HBITMAP ImageHandler::duplicateImage(const HBITMAP& origin)
{
    BITMAP bitmap;
    GetObject(origin, sizeof(BITMAP), &bitmap);
    int width = bitmap.bmWidth;
    int height = bitmap.bmHeight;

    HDC hdc = CreateCompatibleDC(NULL);
    HDC hdcMem = CreateCompatibleDC(NULL);

    SelectObject(hdc, origin);
    HBITMAP newBitMap = CreateCompatibleBitmap(hdc, width * 2, height * 2);

    SelectObject(hdcMem, newBitMap);
    BitBlt(hdcMem, 0, 0, width, height, hdc, 0, 0, SRCCOPY);
    BitBlt(hdcMem, width, 0, width, height, hdc, 0, 0, SRCCOPY);
    BitBlt(hdcMem, 0, height, width, height, hdc, 0, 0, SRCCOPY);
    BitBlt(hdcMem, width, height, width, height, hdc, 0, 0, SRCCOPY);

    DeleteDC(hdc);
    DeleteDC(hdcMem);

    return newBitMap;
}

HBITMAP ImageHandler::resizeImage(const HBITMAP& origin, int width, int height)
{
    BITMAP bitmap;
    GetObject(origin, sizeof(BITMAP), &bitmap);
    int imgWidth = bitmap.bmWidth;
    int imgHeight = bitmap.bmHeight;

    if (width < imgWidth && height < imgHeight)
    {
        return cropImage(origin, 0, 0, width, height);
    }
    if (width == imgWidth && height == imgHeight) { return origin; }

    HBITMAP resizedImg = origin;
    BITMAP resizedBitmap;

    while (true)
    {
        GetObject(resizedImg, sizeof(BITMAP), &resizedBitmap);
        int resizedWidth = bitmap.bmWidth;
        int resizedHeight = bitmap.bmHeight;

        if (imgWidth == width && resizedHeight == height)
        {
            return resizedImg;
        }

        if (imgWidth > width && resizedHeight > height)
        {
            break;
        }
        resizedImg = duplicateImage(resizedImg);
    }

    return cropImage(resizedImg, 0, 0, width, height);
}

void ImageHandler::renderWithoutBack(const HBITMAP& _bitMap, HDC& _hdc, int x, int y)
{
    if (_bitMap == NULL) { return; }
    BITMAP bitmap;
    GetObject(_bitMap, sizeof(BITMAP), &bitmap);

    HDC dcMem = CreateCompatibleDC(_hdc);
    // ���� ����
    // ���� ���õ� ��Ʈ���� ����
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(dcMem, _bitMap);
    // ���� ��

    // ������ �Ͼ���̿��� �Ͼ���� �����ϸ� ���� -> ������ �Ͼ���̿��� ==> ���� �Ⱦ��� ������ ��ġ�ص�
    TransparentBlt(_hdc, x, y, bitmap.bmWidth, bitmap.bmHeight, dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, BackColor);

    // ���� ����
    // DC���� ���� ��Ʈ������ ����
    SelectObject(dcMem, hOldBitmap);
    // ���� ��
    DeleteDC(dcMem);

}
void ImageHandler::renderWithoutBack(const HBITMAP& _bitMap, HDC& _hdc, Vector2Int startPos, Vector2Int size, Vector2Int imagePos)
{
    if (_bitMap == NULL) { return; }

    HDC dcMem = CreateCompatibleDC(_hdc);
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(dcMem, _bitMap);

    TransparentBlt(_hdc, startPos.x, startPos.y, size.x, size.y, dcMem, imagePos.x, imagePos.y, size.x, size.y, BackColor);

    SelectObject(dcMem, hOldBitmap);
    DeleteDC(dcMem);
}

void ImageHandler::renderWithoutBack(const HBITMAP& _bitMap, HDC& _hdc, Vector2Int startPos, Vector2Int size, Vector2Int imagePos, bool reverse)
{
    if (_bitMap == NULL) { return; }

    HDC dcMem = CreateCompatibleDC(_hdc);
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(dcMem, _bitMap);

    if (reverse) // �¿� ����: �ʺ� ������ �����Ͽ� �̹����� �����Ͽ� ���
    {
        TransparentBlt(_hdc, startPos.x + size.x, startPos.y, -size.x, size.y, dcMem, imagePos.x, imagePos.y, size.x, size.y, BackColor);
    }
    else // �Ϲ� ���
    {
        TransparentBlt(_hdc, startPos.x, startPos.y, size.x, size.y, dcMem, imagePos.x, imagePos.y, size.x, size.y, BackColor);
    }

    SelectObject(dcMem, hOldBitmap);
    DeleteDC(dcMem);
}

//alpha�� 0~255 ���� �ֱ�(�� �������� ����)
void ImageHandler::TransparentRender(const HBITMAP& hBitmap, HDC& _hdc, int x, int y, BYTE alpha)
{
    /*
    HDC hdcMem = CreateCompatibleDC(_hdc);
    SelectObject(hdcMem, hBitmap);

    BITMAP bitmap;
    GetObject(hBitmap, sizeof(BITMAP), &bitmap);

    BLENDFUNCTION blendFunc{ AC_SRC_OVER, 0, alpha, AC_SRC_ALPHA }; // �⺻ �ռ� ���/�÷���/���� �� ����/�ҽ� ��Ʈ���� ���� ä�� ���

    AlphaBlend(_hdc, x, y, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, blendFunc); //BOOL result = AlphaBlend(��� DC, X ��ġ, Y ��ġ, ��Ʈ�� �ʺ�, ��Ʈ�� ����, ���� DC, ���� ��Ʈ�� X ��ǥ, ���� ��Ʈ�� Y ��ǥ, ���� ��Ʈ�� �ʺ�, ���� ��Ʈ�� ����, BLENDFUNCTION ����ü);

    DeleteDC(hdcMem);*/
    HDC hdcMem = CreateCompatibleDC(_hdc);
    // ���� ����
    // ���� ���õ� ��Ʈ���� ����
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem, hBitmap);
    // ���� ��

    BITMAP bitmap;
    GetObject(hBitmap, sizeof(BITMAP), &bitmap);

    BLENDFUNCTION blendFunc{ AC_SRC_OVER, 0, alpha, AC_SRC_ALPHA }; // �⺻ �ռ� ���/�÷���/���� �� ����/�ҽ� ��Ʈ���� ���� ä�� ���

    AlphaBlend(_hdc, x, y, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, blendFunc); // BOOL result = AlphaBlend(��� DC, X ��ġ, Y ��ġ, ��Ʈ�� �ʺ�, ��Ʈ�� ����, ���� DC, ���� ��Ʈ�� X ��ǥ, ���� ��Ʈ�� Y ��ǥ, ���� ��Ʈ�� �ʺ�, ���� ��Ʈ�� ����, BLENDFUNCTION ����ü);

    // ���� ����
    // DC���� ���� ��Ʈ������ ����
    SelectObject(hdcMem, hOldBitmap);
    // ���� ��
    DeleteDC(hdcMem);
}

void ImageHandler::renderTransparentWithoutBack(const HBITMAP& hBitmap, HDC& _hdc, int x, int y, BYTE alpha)
{
    // �޸� DC ����
    HDC hdcMemOne = CreateCompatibleDC(_hdc);
    SelectObject(hdcMemOne, hBitmap);

    // ��Ʈ�� ���� ��������
    BITMAP bitmap;
    GetObject(hBitmap, sizeof(BITMAP), &bitmap);

    LONG width = bitmap.bmWidth;
    LONG height = bitmap.bmHeight;

    // ���� ���� (TransparentBlt ���)
    HDC hdcMemTwo = CreateCompatibleDC(_hdc);
    HBITMAP hTempBitmap = CreateCompatibleBitmap(_hdc, width, height);
    SelectObject(hdcMemTwo, hTempBitmap);

    // �޸� DC�� ������ ����� ���� ó��
    TransparentBlt(hdcMemTwo, 0, 0, width, height, hdcMemOne, 0, 0, width, height, BackColor);

    // ���� ó�� (AlphaBlend ���)
    BLENDFUNCTION blendFunc;
    blendFunc.BlendOp = AC_SRC_OVER;
    blendFunc.BlendFlags = 0;
    blendFunc.SourceConstantAlpha = alpha;
    blendFunc.AlphaFormat = 0;

    // ȭ�鿡 ���
    AlphaBlend(_hdc, x, y, width, height, hdcMemTwo, 0, 0, width, height, blendFunc);

    // ���ҽ� ����
    DeleteDC(hdcMemTwo);
    DeleteDC(hdcMemOne);
    DeleteObject(hTempBitmap);
}

//���� �ܾƿ� �� �ȴ�
void ImageHandler::zoomRender(const HBITMAP& _hBitmap, HDC _hdc, int x, int y, float magnification)
{
    if (magnification == 1.0f) { Render(_hBitmap, _hdc, x, y); }

    HDC hdcSrc = CreateCompatibleDC(_hdc);
    SelectObject(hdcSrc, _hBitmap);

    BITMAP bitmap;
    GetObject(_hBitmap, sizeof(BITMAP), &bitmap);
    int width = (int)((float)bitmap.bmWidth * magnification);
    int height = (int)((float)bitmap.bmHeight * magnification);

    StretchBlt(_hdc, x, y, width, height, hdcSrc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

    DeleteDC(hdcSrc);
}


//���� �ܾƿ� �� �ȴ�
HBITMAP ImageHandler::zoomImage(const HBITMAP& origin, float magnification)
{
    if (magnification == 1.0f) { return origin; }
    BITMAP bitmap;
    GetObject(origin, sizeof(BITMAP), &bitmap);
    int width = (int)((float)bitmap.bmWidth * magnification);
    int height = (int)((float)bitmap.bmHeight * magnification);

    HDC hdc = CreateCompatibleDC(NULL);
    HDC hdcMem = CreateCompatibleDC(NULL);
    SelectObject(hdc, origin);

    HBITMAP newBitMap = CreateCompatibleBitmap(hdc, width, height);
    SelectObject(hdcMem, newBitMap);

    StretchBlt(hdcMem, 0, 0, width, height, hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

    DeleteDC(hdc);
    DeleteDC(hdcMem);

    return newBitMap;
}


void ImageHandler::RotatePoint(Vector2Int& point, const Vector2& center, float angle)
{
    // ������ �������� ��ȯ
    float radians = angle * 3.14159265358979f / 180.0f;

    Vector2 normalizePoint = point - center;

    // ȸ�� ��� ����
    Vector2Int rotatedPoint{
        static_cast<int>(normalizePoint.x * cos(radians) - normalizePoint.y * sin(radians)),
        static_cast<int>(normalizePoint.x * sin(radians) + normalizePoint.y * cos(radians))
    };

    point = rotatedPoint + center;
}

void ImageHandler::renderRotatedPolygon(HDC _hdc, Vector2 center, std::vector<Vector2Int> points, float angle)
{
    for (Vector2Int& point : points)
    {
        RotatePoint(point, center, angle);
    }

    std::unique_ptr<POINT[]> polygon = std::make_unique<POINT[]>(points.size());

    for (unsigned int i = 0; i < points.size(); i++)
    {
        polygon[i] = { points[i].x, points[i].y };
    }

    Polygon(_hdc, polygon.get(), 4);
}


void ImageHandler::renderRotatedRectangle(HDC hdc, Vector2 center, int width, int height, float angle)
{
    std::vector<Vector2Int> points{
        {(int)center.x - width / 2, (int)center.y - height / 2}, // �»��
        {(int)center.x + width / 2, (int)center.y - height / 2}, // ����
        {(int)center.x + width / 2, (int)center.y + height / 2}, // ���ϴ�
        {(int)center.x - width / 2, (int)center.y + height / 2}  // ���ϴ�
    };

    renderRotatedPolygon(hdc, center, points, angle);
}



HBITMAP ImageHandler::RotateBitmap(HBITMAP hBitmap, float angle)
{
    BITMAP bitmap;
    GetObject(hBitmap, sizeof(BITMAP), &bitmap);

    int width = bitmap.bmWidth;
    int height = bitmap.bmHeight;

    // �̹����� �밢�� ���� ���
    int canvasSize = static_cast<int>(sqrt(width * width + height * height)) + 1;

    // ���ο� ��Ʈ�� ũ�⸦ �밢�� ���̷� ����
    HDC hdc = CreateCompatibleDC(NULL);
    HBITMAP hNewBitmap = CreateCompatibleBitmap(hdc, canvasSize, canvasSize);
    HDC hdcMem = CreateCompatibleDC(NULL);
    SelectObject(hdcMem, hBitmap);

    HDC hdcRotated = CreateCompatibleDC(NULL);
    SelectObject(hdcRotated, hNewBitmap);

    // ����
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
    RECT rect = { 0, 0, canvasSize, canvasSize };
    FillRect(hdcRotated, &rect, hBrush);
    DeleteObject(hBrush);

    Vector2Int newCenter{ canvasSize / 2, canvasSize / 2 };
    Vector2Int center{ width / 2, height / 2 };
    Vector2Int diff{ newCenter - center };

    // ȸ���� �̹��� �׸���
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            Vector2Int point{ x,y };
            RotatePoint(point, center, angle);
            point += diff;

            if ((point.x >= 0 && point.x < canvasSize) && (point.y >= 0 && point.y < canvasSize))
            {
                COLORREF color = GetPixel(hdcMem, x, y);
                SetPixel(hdcRotated, point.x, point.y, color);
            }
        }
    }

    // ���ҽ� ����
    DeleteDC(hdc);
    DeleteDC(hdcMem);
    DeleteDC(hdcRotated);

    return hNewBitmap;
}


HBITMAP ImageHandler::shadowImage(const HBITMAP& _bitMap, int value)
{
    if (value < 0) return NULL;

    float percent = 0.0f;
    if (value > 100) { percent = 1.0f; }
    else if (value < 0) { percent = 0.0f; }
    else percent = (float)(100 - value) / 100.0f;

    BITMAP bitmap;
    GetObject(_bitMap, sizeof(BITMAP), &bitmap);

    int width = bitmap.bmWidth;
    int height = bitmap.bmHeight;

    HDC hdc = CreateCompatibleDC(NULL);
    HDC hdcMem = CreateCompatibleDC(NULL);

    SelectObject(hdc, _bitMap);
    HBITMAP newBitMap = CreateCompatibleBitmap(hdc, width, height);
    SelectObject(hdcMem, newBitMap);

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            COLORREF color = GetPixel(hdc, x, y);

            // 32��Ʈ BMP�� ��� ���� ä���� �����ϰ� RGB�� ����
            if (color == RGB(255, 0, 255))
            {
                SetPixel(hdcMem, x, y, RGB(255, 0, 255));
                continue; // Ư�� ������ ����
            }

            int r = GetRValue(color) * percent;
            int g = GetGValue(color) * percent;
            int b = GetBValue(color) * percent;

            SetPixel(hdcMem, x, y, RGB(r, g, b));
        }
    }

    // hbitmap���� �ҷ��ͼ�
    // byte�� ��ȯ�� �ӽ� ����
    // ���۸� ���� ���ۿ� hbitmap�� ������ 
    // �������� ũ�� �̻��� �Ǹ� ���� �տ� �ִ°� ����
    // �ƴϸ� ���� �����ؼ� ����ϴ�
    // �ɰ��� �ʰ� bitmap�� �����ϴ� ����� ���� ���� ������

    DeleteDC(hdc);
    DeleteDC(hdcMem);

    return newBitMap;

}

void ImageHandler::DrawOutlinedText(HDC hdc, const wchar_t* text, int x, int y)
{
    // �ܰ��� ���� ����
    SetTextColor(hdc, RGB(0,0,0));
    SetBkMode(hdc, TRANSPARENT); // ��� ��带 �������� ����

    // �ܰ��� �׸��� (Offset�� ���� ��ġ�� �̵�)
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dx != 0 || dy != 0) // ���� ��ġ�� ����
            {
                TextOut(hdc, x + dx, y + dy, text, wcslen(text)); // �ܰ��� �ؽ�Ʈ ���
            }
        }
    }

    // �۾� ���� ����
    SetTextColor(hdc, RGB(255, 255, 255));

    // ���� �ؽ�Ʈ �׸���
    TextOut(hdc, x, y, text, wcslen(text));
}

void ImageHandler::DrawOutlinedText(HDC hdc, const wchar_t* text, int x, int y, COLORREF innerColor)
{
    // �ܰ��� ���� ����
    SetTextColor(hdc, RGB(0, 0, 0));
    SetBkMode(hdc, TRANSPARENT); // ��� ��带 �������� ����

    // �ܰ��� �׸��� (Offset�� ���� ��ġ�� �̵�)
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dx != 0 || dy != 0) // ���� ��ġ�� ����
            {
                TextOut(hdc, x + dx, y + dy, text, wcslen(text)); // �ܰ��� �ؽ�Ʈ ���
            }
        }
    }

    // �۾� ���� ����
    SetTextColor(hdc, innerColor);

    // ���� �ؽ�Ʈ �׸���
    TextOut(hdc, x, y, text, wcslen(text));
}
