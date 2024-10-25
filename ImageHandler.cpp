#include "framework.h"
#include "ImageHandler.h"

static HDC gMemDC = NULL; // 메모리 DC
static HDC tempDC = NULL; // 임시 DC
static HBITMAP bmpRev = NULL; // 반전된 비트맵
static HBITMAP oldBmp = NULL; // 이전 비트맵
static HDC hdcRotated = NULL;
static HBITMAP gRotatedBitmap = NULL;
static HDC gRotatedDC = NULL;

static HBITMAP blank50 = NULL;
static HBITMAP blank100 = NULL;
static HBITMAP blank200 = NULL;

static HBITMAP rotblank50 = NULL;
static HBITMAP rotblank100 = NULL;
static HBITMAP rotblank200 = NULL;

static HBRUSH hPinkBrush = CreateSolidBrush(RGB(255, 0, 255));
static HPEN hPinkPen = CreatePen(PS_SOLID, 2, RGB(255, 0, 255));

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

    // 수정 시작
    // 원래 선택된 비트맵을 저장
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdc, origin);
    // 수정 끝

    HBITMAP hCroppedBitmap = CreateCompatibleBitmap(hdc, width, height);

    // 수정 시작
    // 새로 생성된 비트맵을 메모리 DC에 선택
    HBITMAP hOldCroppedBitmap = (HBITMAP)SelectObject(hdcMem, hCroppedBitmap);
    // 수정 끝

    BitBlt(hdcMem, 0, 0, width, height, hdc, x, y, SRCCOPY);

    // 수정 시작
    // DC에서 원래 비트맵으로 복원
    SelectObject(hdc, hOldBitmap);
    SelectObject(hdcMem, hOldCroppedBitmap);
    // 수정 끝

    // 추가 시작
    // GDI 객체 해제
    DeleteObject(hOldBitmap);
    DeleteObject(hOldCroppedBitmap);
    // 추가 끝

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

    // 수정 시작
    // 원래 선택된 비트맵을 저장
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdc, origin);
    // 수정 끝

    HBITMAP hCroppedBitmap = CreateCompatibleBitmap(hdc, imgSize.x, imgSize.y);

    // 수정 시작
    // 새로 생성된 비트맵을 메모리 DC에 선택
    HBITMAP hOldCroppedBitmap = (HBITMAP)SelectObject(hdcMem, hCroppedBitmap);
    // 수정 끝

    BitBlt(hdcMem, 0, 0, imgSize.x, imgSize.y, hdc, startPos.x, startPos.y, SRCCOPY);

    // 수정 시작
    // DC에서 원래 비트맵으로 복원
    SelectObject(hdc, hOldBitmap);
    SelectObject(hdcMem, hOldCroppedBitmap);
    // 수정 끝

    // 추가 시작
    // GDI 객체 해제
    DeleteObject(hOldBitmap);
    DeleteObject(hOldCroppedBitmap);
    // 추가 끝

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

    // DC가 없으면 생성
    if (!gMemDC)
        gMemDC = CreateCompatibleDC(_hdc);

    // 원래 선택된 비트맵을 저장
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(gMemDC, _bitMap);

    // 배경색이 하얀색이여서 하얀색을 지정하면 깨짐
    TransparentBlt(_hdc, x, y, bitmap.bmWidth, bitmap.bmHeight, gMemDC, 0, 0, bitmap.bmWidth, bitmap.bmHeight, BackColor);

    // DC에서 원래 비트맵으로 복원
    SelectObject(gMemDC, hOldBitmap);

    /*
    if (_bitMap == NULL) { return; }
    BITMAP bitmap;
    GetObject(_bitMap, sizeof(BITMAP), &bitmap);

    HDC dcMem = CreateCompatibleDC(_hdc);
    // 수정 시작
    // 원래 선택된 비트맵을 저장
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(dcMem, _bitMap);
    // 수정 끝

    // 배경색이 하얀색이여서 하얀색을 지정하면 깨짐 -> 바탕도 하얀색이여서 ==> 거의 안쓰는 색으로 배치해둠
    TransparentBlt(_hdc, x, y, bitmap.bmWidth, bitmap.bmHeight, dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, BackColor);

    // 수정 시작
    // DC에서 원래 비트맵으로 복원
    SelectObject(dcMem, hOldBitmap);
    // 수정 끝
    DeleteDC(dcMem);
    */

}
void ImageHandler::renderWithoutBack(const HBITMAP& _bitMap, HDC& _hdc, Vector2Int startPos, Vector2Int size, Vector2Int imagePos)
{
    if (_bitMap == nullptr || _bitMap == NULL) { return; }

    // DC가 없으면 생성
    if (!gMemDC)
        gMemDC = CreateCompatibleDC(_hdc);

    HBITMAP hOldBitmap = (HBITMAP)SelectObject(gMemDC, _bitMap);

    TransparentBlt(_hdc, startPos.x, startPos.y, size.x, size.y, gMemDC, imagePos.x, imagePos.y, size.x, size.y, BackColor);

    // DC에서 원래 비트맵으로 복원
    SelectObject(gMemDC, hOldBitmap);
}

void ImageHandler::renderWithoutBack(const HBITMAP& _bitMap, HDC& _hdc, Vector2Int startPos, Vector2Int size, Vector2Int imagePos, bool reverse)
{
    if (!reverse)
    {
        renderWithoutBack(_bitMap, _hdc, startPos, size, imagePos);
        return;
    }
    if (_bitMap == NULL) { return; }

    // DC 생성
    if (!gMemDC)
        gMemDC = CreateCompatibleDC(_hdc);

    if (!tempDC)
        tempDC = CreateCompatibleDC(_hdc);

    int blank = 0;

    HBITMAP oldimg = (HBITMAP)SelectObject(tempDC, _bitMap);

    HBITMAP hOldBitmap;
    // 반전된 비트맵 생성
    if (size.x > 100 || size.y > 100)
    {
        if (blank200 == NULL)
            blank200 = loadImg(L"Blank200.bmp");
        blank = 200;
        // 비트맵 선택
        hOldBitmap = (HBITMAP)SelectObject(gMemDC, blank200);
    }
    else if (size.x > 50 || size.y > 50)
    {
        if (blank100 == NULL)
            blank100 = loadImg(L"Blank100.bmp");
        blank = 100;
        // 비트맵 선택
        hOldBitmap = (HBITMAP)SelectObject(gMemDC, blank100);

    }
    else
    {
        if (blank50 == NULL)
            blank50 = loadImg(L"Blank50.bmp");
        blank = 50;
        // 비트맵 선택
        hOldBitmap = (HBITMAP)SelectObject(gMemDC, blank50);

    }

    StretchBlt(gMemDC, size.x - 1, 0, -size.x, size.y, tempDC, imagePos.x, imagePos.y, size.x, size.y, SRCCOPY);
    TransparentBlt(_hdc, startPos.x, startPos.y, size.x, size.y, gMemDC, 0, 0, size.x, size.y, BackColor);

    HBRUSH oldBrush = (HBRUSH)SelectObject(gMemDC, hPinkBrush);
    HPEN oldPen = (HPEN)SelectObject(gMemDC, hPinkPen);
    Rectangle(gMemDC, 0, 0, blank, blank);
    SelectObject(gMemDC, oldBrush);
    SelectObject(gMemDC, oldPen);

    SelectObject(tempDC, oldBmp);
    SelectObject(gMemDC, hOldBitmap);



}

//alpha에 0~255 정수 넣기(값 낮을수록 투명)
void ImageHandler::TransparentRender(const HBITMAP& hBitmap, HDC& _hdc, int x, int y, BYTE alpha)
{
    HDC hdcMem = CreateCompatibleDC(_hdc);
    // 원래 선택된 비트맵을 저장
    HBITMAP hOldBitmap = (HBITMAP)SelectObject(hdcMem, hBitmap);

    BITMAP bitmap;
    GetObject(hBitmap, sizeof(BITMAP), &bitmap);

    // 기본 합성 방식/플래그/알파 값 설정/소스 비트맵의 알파 채널 사용
    BLENDFUNCTION blendFunc{ AC_SRC_OVER, 0, alpha, AC_SRC_ALPHA };

    // BOOL result = AlphaBlend(대상 DC, X 위치, Y 위치, 비트맵 너비, 비트맵 높이, 원본 DC, 원본 비트맵 X 좌표, 원본 비트맵 Y 좌표, 원본 비트맵 너비, 원본 비트맵 높이, BLENDFUNCTION 구조체);
    AlphaBlend(_hdc, x, y, bitmap.bmWidth, bitmap.bmHeight, hdcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, blendFunc);

    // DC에서 원래 비트맵으로 복원
    SelectObject(hdcMem, hOldBitmap);
    DeleteDC(hdcMem);
}


HBITMAP ImageHandler::RotateImage(HBITMAP hBitmap, float angle)
{
    BITMAP bmp;
    GetObject(hBitmap, sizeof(bmp), &bmp);

    // 회전 각도를 라디안으로 변환
    float radians = angle * (3.14159f / 180.0f);
    float cosTheta = cos(radians);
    float sinTheta = sin(radians);

    // 회전 후 새 이미지 크기 계산
    int newWidth = (int)(abs(bmp.bmWidth * cosTheta) + abs(bmp.bmHeight * sinTheta));
    int newHeight = (int)(abs(bmp.bmHeight * cosTheta) + abs(bmp.bmWidth * sinTheta));

    // 새 비트맵 생성
    HBITMAP hRotatedBitmap = CreateCompatibleBitmap(GetDC(NULL), newWidth, newHeight);

    if(!gMemDC)
        gMemDC = CreateCompatibleDC(NULL);

    HDC hdcRotated = CreateCompatibleDC(NULL);

    // 비트맵 선택
    HBITMAP oldTemp = (HBITMAP)SelectObject(gMemDC, hBitmap);
    SelectObject(hdcRotated, hRotatedBitmap);

    HBRUSH oldBrush = (HBRUSH)SelectObject(hdcRotated, hPinkBrush);
    HPEN oldPen = (HPEN)SelectObject(hdcRotated, hPinkPen);
    Rectangle(hdcRotated, 0, 0, newWidth, newHeight);
    SelectObject(hdcRotated, oldBrush); 
    SelectObject(hdcRotated, oldPen);

    // 회전 변환 행렬 설정
    SetGraphicsMode(hdcRotated, GM_ADVANCED);
    XFORM xform;
    xform.eM11 = cosTheta;
    xform.eM12 = sinTheta;
    xform.eM21 = -sinTheta;
    xform.eM22 = cosTheta;
    xform.eDx = (float)newWidth / 2;
    xform.eDy = (float)newHeight / 2;

    SetWorldTransform(hdcRotated, &xform);

    // 비트맵을 새 비트맵으로 복사
    BitBlt(hdcRotated, -bmp.bmWidth / 2, -bmp.bmHeight / 2, bmp.bmWidth, bmp.bmHeight, gMemDC, 0, 0, SRCCOPY);

    // DC 정리
    SelectObject(gMemDC, oldTemp);
    DeleteDC(hdcRotated);

    return hRotatedBitmap;
}



void ImageHandler::renderRotateWithoutBack(const HBITMAP& hBitmap, HDC& _hdc, Vector2Int pos, float angle, bool reverse)
{
    BITMAP bmp;
    GetObject(hBitmap, sizeof(bmp), &bmp);

    // 회전 각도를 라디안으로 변환
    float radians = angle * (3.14159f / 180.0f);
    float cosTheta = cos(radians);
    float sinTheta = sin(radians);

    // 회전 후 새 이미지 크기 계산
    int newWidth = (int)(abs(bmp.bmWidth * cosTheta) + abs(bmp.bmHeight * sinTheta));
    int newHeight = (int)(abs(bmp.bmHeight * cosTheta) + abs(bmp.bmWidth * sinTheta));

    if(!gMemDC)
        gMemDC = CreateCompatibleDC(NULL);
    if(!hdcRotated)
        hdcRotated = CreateCompatibleDC(NULL);



    int blank = 0;

    HBITMAP oldTemp = (HBITMAP)SelectObject(gMemDC, hBitmap);
    HBITMAP hOldBitmap;
    // 반전된 비트맵 생성
    if (newWidth > 100 || newHeight > 100)
    {
        if (blank200 == NULL)
            blank200 = loadImg(L"Blank200.bmp");
        blank = 200;
        // 비트맵 선택
        hOldBitmap = (HBITMAP)SelectObject(hdcRotated, blank200);
    }
    else if (newWidth > 50 || newHeight > 50)
    {
        if (blank100 == NULL)
            blank100 = loadImg(L"Blank100.bmp");
        blank = 100;
        // 비트맵 선택
        hOldBitmap = (HBITMAP)SelectObject(hdcRotated, blank100);

    }
    else
    {
        if (blank50 == NULL)
            blank50 = loadImg(L"Blank50.bmp");
        blank = 50;
        // 비트맵 선택
        hOldBitmap = (HBITMAP)SelectObject(hdcRotated, blank50);

    }


    // 회전 변환 행렬 설정
    SetGraphicsMode(hdcRotated, GM_ADVANCED);
    XFORM xform;
    xform.eM11 = cosTheta;
    xform.eM12 = sinTheta;
    xform.eM21 = -sinTheta;
    xform.eM22 = cosTheta;
    xform.eDx = (float)newWidth / 2;
    xform.eDy = (float)newHeight / 2;

    SetWorldTransform(hdcRotated, &xform);

    BitBlt(hdcRotated, -bmp.bmWidth / 2, -bmp.bmHeight / 2, bmp.bmWidth, bmp.bmHeight, gMemDC, 0, 0, SRCCOPY);
    
    TransparentBlt(_hdc, pos.x, pos.y, (int)bmp.bmWidth, (int)bmp.bmHeight, hdcRotated, 0, 0, (int)bmp.bmWidth, (int)bmp.bmHeight, BackColor);

    HBRUSH oldBrush = (HBRUSH)SelectObject(hdcRotated, hPinkBrush);
    HPEN oldPen = (HPEN)SelectObject(hdcRotated, hPinkPen);
    Rectangle(hdcRotated, 0, 0, blank, blank);
    SelectObject(hdcRotated, oldBrush);
    SelectObject(hdcRotated, oldPen);


    SelectObject(gMemDC, hOldBitmap);
    SelectObject(gMemDC, oldTemp);
}

void ImageHandler::renderRotateWithoutBack(const HBITMAP& hBitmap, HDC& _hdc, Vector2Int startPos, Vector2Int size, Vector2Int imagePos, float angle, bool reverse)
{
    if (hBitmap == nullptr || hBitmap == NULL) { return; }

    // DC가 없으면 생성
    if (!tempDC)
        tempDC = CreateCompatibleDC(NULL);
    if (!gMemDC)
        gMemDC = CreateCompatibleDC(NULL);
    if (!hdcRotated)
        hdcRotated = CreateCompatibleDC(NULL);

    HBITMAP hOldBitmap = (HBITMAP)SelectObject(tempDC, hBitmap);
    HBITMAP hOldBitmapTwo = NULL;
    int blank = 0;
    // 반전된 비트맵 생성
    if (size.x > 100 || size.y > 100)
    {
        if (blank200 == NULL)
            blank200 = loadImg(L"Blank200.bmp");
        blank = 200;
        // 비트맵 선택
        hOldBitmapTwo = (HBITMAP)SelectObject(gMemDC, blank200);
    }
    else if (size.x > 50 || size.y > 50)
    {
        if (blank100 == NULL)
            blank100 = loadImg(L"Blank100.bmp");
        blank = 100;
        // 비트맵 선택
        hOldBitmapTwo = (HBITMAP)SelectObject(gMemDC, blank100);

    }
    else
    {
        if (blank50 == NULL)
            blank50 = loadImg(L"Blank50.bmp");
        blank = 50;
        // 비트맵 선택
        hOldBitmapTwo = (HBITMAP)SelectObject(gMemDC, blank50);

    }

    BitBlt(gMemDC, 0, 0, size.x, size.y, tempDC, imagePos.x, imagePos.y, SRCCOPY);



    // 회전 각도를 라디안으로 변환
    float radians = angle * (3.14159f / 180.0f);
    float cosTheta = cos(radians);
    float sinTheta = sin(radians);
    
    // 회전 후 새 이미지 크기 계산
    int newWidth = (int)(abs(size.x * cosTheta) + abs(size.y * sinTheta));
    int newHeight = (int)(abs(size.y * cosTheta) + abs(size.x * sinTheta));

    
    HBITMAP hOldBitmapThree = NULL;
    int blankTwo = 0;
    if (newWidth > 100 || newHeight > 100)
    {
        if (rotblank200 == NULL)
            rotblank200 = loadImg(L"Blank200.bmp");
        blankTwo = 200;
        hOldBitmapThree = (HBITMAP)SelectObject(hdcRotated, rotblank200);
    }
    else if (newWidth > 50 || newHeight > 50)
    {
        if (rotblank100 == NULL)
            rotblank100 = loadImg(L"Blank100.bmp");
        blankTwo = 100;
        hOldBitmapThree = (HBITMAP)SelectObject(hdcRotated, rotblank100);
    
    }
    else
    {
        if (rotblank50 == NULL)
            rotblank50 = loadImg(L"Blank50.bmp");
        blankTwo = 50;
        hOldBitmapThree = (HBITMAP)SelectObject(hdcRotated, rotblank50);
    }

    // 회전된 사각형의 꼭지점 좌표 계산
    POINT points[3];

    // 이미지의 중앙 계산
    float centerX = (float)size.x / 2;
    float centerY = (float)size.y / 2;
    float offsetX = (blankTwo - (float)size.x) / 2;
    float offsetY = (blankTwo - (float)size.y) / 2;

    // 각 꼭지점의 위치를 회전 중심을 기준으로 계산
    points[0].x = static_cast<LONG>(centerX - ((float)size.x / 2) * cosTheta - ((float)size.y / 2) * sinTheta + offsetX); // 왼쪽 위
    points[0].y = static_cast<LONG>(centerY - ((float)size.x / 2) * sinTheta + ((float)size.y / 2) * cosTheta + offsetY);

    points[1].x = static_cast<LONG>(centerX + ((float)size.x / 2) * cosTheta - ((float)size.y / 2) * sinTheta + offsetX); // 오른쪽 위
    points[1].y = static_cast<LONG>(centerY + ((float)size.x / 2) * sinTheta + ((float)size.y / 2) * cosTheta + offsetY);

    points[2].x = static_cast<LONG>(centerX - ((float)size.x / 2) * cosTheta + ((float)size.y / 2) * sinTheta + offsetX); // 왼쪽 아래
    points[2].y = static_cast<LONG>(centerY - ((float)size.x / 2) * sinTheta - ((float)size.y / 2) * cosTheta + offsetY);


    PlgBlt(hdcRotated, points, gMemDC, 0, 0, size.x, size.y, NULL, 0, 0);

    TransparentBlt(_hdc, startPos.x - (int)offsetX, startPos.y - (int)offsetY, blankTwo, blankTwo, hdcRotated, 0, 0, blankTwo, blankTwo, BackColor);

    HBRUSH oldBrush = (HBRUSH)SelectObject(hdcRotated, hPinkBrush);
    HPEN oldPen = (HPEN)SelectObject(hdcRotated, hPinkPen);
    Rectangle(hdcRotated, 0, 0, blankTwo, blankTwo);
    SelectObject(hdcRotated, oldBrush);
    SelectObject(hdcRotated, oldPen);

    oldBrush = (HBRUSH)SelectObject(gMemDC, hPinkBrush);
    oldPen = (HPEN)SelectObject(gMemDC, hPinkPen);
    Rectangle(gMemDC, 0, 0, blank, blank);
    SelectObject(gMemDC, oldBrush);
    SelectObject(gMemDC, oldPen);


    SelectObject(tempDC, hOldBitmap);
    SelectObject(gMemDC, hOldBitmapTwo);
    SelectObject(hdcRotated, hOldBitmapThree);
}

void ImageHandler::renderRotateWithoutBack(const HBITMAP& hBitmap, HDC& _hdc, Vector2Int pos, Vector2Int center, float angle, bool reverse, Vector2& outPut)
{
    // 이미지를 회전시키기
    HBITMAP img = RotateImage(hBitmap, angle);

    BITMAP bmp;
    GetObject(img, sizeof(bmp), &bmp); // 회전된 이미지의 정보 가져오기
    int width = bmp.bmWidth;
    int height = bmp.bmHeight;

    // 회전 각도를 라디안으로 변환
    float radians = angle * (3.1415926535f / 180.0f);

    // 이미지 중심 계산 (회전의 중심)
    Vector2 imgCenter = { width / 2.0f, height / 2.0f };

    // 회전된 이미지의 중심 좌표 계산
    Vector2 rotated = Vector2::zero();
    rotated.x = imgCenter.x + (center.x - imgCenter.x) * cos(radians) - (center.y - imgCenter.y) * sin(radians);
    rotated.y = imgCenter.y + (center.x - imgCenter.x) * sin(radians) + (center.y - imgCenter.y) * cos(radians);

    if (reverse)
    {
        rotated.x = -rotated.x + width; // X축 반전
    }

    // 회전된 이미지를 그릴 위치 계산
    Vector2Int drawPos = pos - Vector2Int(static_cast<int>(rotated.x), static_cast<int>(rotated.y));

    // 회전된 이미지를 지정된 위치에 렌더링
    renderWithoutBack(img, _hdc, drawPos, { width, height }, { 0, 0 }, reverse);

    // 회전된 비트맵 메모리 해제
    DeleteObject(img);
    outPut = drawPos;
}

void ImageHandler::renderTransparentWithoutBack(const HBITMAP& hBitmap, HDC& _hdc, int x, int y, BYTE alpha)
{
    // 메모리 DC 생성
    HDC hdcMemOne = CreateCompatibleDC(_hdc);
    SelectObject(hdcMemOne, hBitmap);

    // 비트맵 정보 가져오기
    BITMAP bitmap;
    GetObject(hBitmap, sizeof(BITMAP), &bitmap);

    LONG width = bitmap.bmWidth;
    LONG height = bitmap.bmHeight;

    // 배경색 제거 (TransparentBlt 사용)
    HDC hdcMemTwo = CreateCompatibleDC(_hdc);
    HBITMAP hTempBitmap = CreateCompatibleBitmap(_hdc, width, height);
    SelectObject(hdcMemTwo, hTempBitmap);

    // 메모리 DC에 투명한 배경을 먼저 처리
    TransparentBlt(hdcMemTwo, 0, 0, width, height, hdcMemOne, 0, 0, width, height, BackColor);

    // 투명도 처리 (AlphaBlend 사용)
    BLENDFUNCTION blendFunc;
    blendFunc.BlendOp = AC_SRC_OVER;
    blendFunc.BlendFlags = 0;
    blendFunc.SourceConstantAlpha = alpha;
    blendFunc.AlphaFormat = 0;

    // 화면에 출력
    AlphaBlend(_hdc, x, y, width, height, hdcMemTwo, 0, 0, width, height, blendFunc);

    // 리소스 해제
    DeleteDC(hdcMemTwo);
    DeleteDC(hdcMemOne);
    DeleteObject(hTempBitmap);
}

//줌인 줌아웃 다 된다
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


//줌인 줌아웃 다 된다
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
    // 각도를 라디안으로 변환
    float radians = angle * 3.14159265358979f / 180.0f;

    Vector2 normalizePoint = point - center;

    // 회전 행렬 적용
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
        {(int)center.x - width / 2, (int)center.y - height / 2}, // 좌상단
        {(int)center.x + width / 2, (int)center.y - height / 2}, // 우상단
        {(int)center.x + width / 2, (int)center.y + height / 2}, // 우하단
        {(int)center.x - width / 2, (int)center.y + height / 2}  // 좌하단
    };

    renderRotatedPolygon(hdc, center, points, angle);
}



HBITMAP ImageHandler::RotateBitmap(HBITMAP hBitmap, float angle)
{
    BITMAP bitmap;
    GetObject(hBitmap, sizeof(BITMAP), &bitmap);

    int width = bitmap.bmWidth;
    int height = bitmap.bmHeight;

    // 이미지의 대각선 길이 계산
    int canvasSize = static_cast<int>(sqrt(width * width + height * height)) + 1;

    // 새로운 비트맵 크기를 대각선 길이로 설정
    HDC hdc = CreateCompatibleDC(NULL);
    HBITMAP hNewBitmap = CreateCompatibleBitmap(hdc, canvasSize, canvasSize);
    HDC hdcMem = CreateCompatibleDC(NULL);
    SelectObject(hdcMem, hBitmap);

    HDC hdcRotated = CreateCompatibleDC(NULL);
    SelectObject(hdcRotated, hNewBitmap);

    // 배경색
    HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 255));
    RECT rect = { 0, 0, canvasSize, canvasSize };
    FillRect(hdcRotated, &rect, hBrush);
    DeleteObject(hBrush);

    Vector2Int newCenter{ canvasSize / 2, canvasSize / 2 };
    Vector2Int center{ width / 2, height / 2 };
    Vector2Int diff{ newCenter - center };

    // 회전된 이미지 그리기
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

    // 리소스 해제
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

            // 32비트 BMP인 경우 알파 채널을 무시하고 RGB만 조정
            if (color == RGB(255, 0, 255))
            {
                SetPixel(hdcMem, x, y, RGB(255, 0, 255));
                continue; // 특정 색상은 무시
            }

            int r = (int)(GetRValue(color) * percent);
            int g = (int)(GetGValue(color) * percent);
            int b = (int)(GetBValue(color) * percent);

            SetPixel(hdcMem, x, y, RGB(r, g, b));
        }
    }

    // hbitmap으로 불러와서
    // byte로 변환해 임시 저장
    // 버퍼를 만들어서 버퍼에 hbitmap에 없으면 
    // 버퍼일정 크기 이상이 되면 제일 앞에 있는걸 지움
    // 아니면 영역 지정해서 사용하는
    // 쪼개지 않고 bitmap에 저장하는 방법을 쓰면 되지 않을까

    DeleteDC(hdc);
    DeleteDC(hdcMem);

    return newBitMap;

}

void ImageHandler::DrawOutlinedText(HDC hdc, const wchar_t* text, int x, int y)
{
    // 외곽선 색상 설정
    SetTextColor(hdc, RGB(0,0,0));
    SetBkMode(hdc, TRANSPARENT); // 배경 모드를 투명으로 설정

    // 외곽선 그리기 (Offset을 통해 위치를 이동)
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dx != 0 || dy != 0) // 원본 위치는 제외
            {
                TextOut(hdc, x + dx, y + dy, text, wcslen(text)); // 외곽선 텍스트 출력
            }
        }
    }

    // 글씨 색상 설정
    SetTextColor(hdc, RGB(255, 255, 255));

    // 본문 텍스트 그리기
    TextOut(hdc, x, y, text, wcslen(text));
}

void ImageHandler::DrawOutlinedText(HDC hdc, const wchar_t* text, int x, int y, COLORREF innerColor)
{
    // 외곽선 색상 설정
    SetTextColor(hdc, RGB(0, 0, 0));
    SetBkMode(hdc, TRANSPARENT); // 배경 모드를 투명으로 설정

    // 외곽선 그리기 (Offset을 통해 위치를 이동)
    for (int dx = -1; dx <= 1; dx++)
    {
        for (int dy = -1; dy <= 1; dy++)
        {
            if (dx != 0 || dy != 0) // 원본 위치는 제외
            {
                TextOut(hdc, x + dx, y + dy, text, wcslen(text)); // 외곽선 텍스트 출력
            }
        }
    }

    // 글씨 색상 설정
    SetTextColor(hdc, innerColor);

    // 본문 텍스트 그리기
    TextOut(hdc, x, y, text, wcslen(text));
}
