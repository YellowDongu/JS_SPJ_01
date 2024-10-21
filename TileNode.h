#pragma once
class TileNode
{
public:
	TileNode() : gridPos(Vector2Int::zero()), worldPos(Vector2::zero()), size(0) {}
	~TileNode() {}

	virtual void init() abstract;
	virtual void update() abstract;
	virtual void render(HDC _hdc, cameraManager _cam) abstract;
	virtual void release() abstract;


	Vector2Int gridPosition() const { return gridPos; }
	Vector2 position() const { return worldPos; }
	int tileSize() const { return size; }

	void resizeTile(Vector2 newWorldPos, int newSize)
	{
        worldPos = newWorldPos;
		size = newSize;
	}


private:
	Vector2Int gridPos;
	Vector2 worldPos;
	int size;

	BITMAP tileImg;
};


bool colorMatch(COLORREF objectColor, COLORREF targetColor, int tolerance)
{
    return (abs(GetRValue(objectColor) - GetRValue(targetColor)) <= tolerance &&
            abs(GetGValue(objectColor) - GetGValue(targetColor)) <= tolerance &&
            abs(GetBValue(objectColor) - GetBValue(targetColor)) <= tolerance);
}

HBITMAP outline(const HBITMAP& hBitmap, COLORREF outlineColor, COLORREF targetColor, int tolerance,
      bool left = true, bool top = true, bool right = true, bool bottom = true)
{
    BITMAP bitmap;
    GetObject(hBitmap, sizeof(BITMAP), &bitmap);

    // ���ο� ��Ʈ�� ����
    HBITMAP hNewBitmap = CreateBitmap(bitmap.bmWidth, bitmap.bmHeight, bitmap.bmPlanes, bitmap.bmBitsPixel, NULL);

    HDC hdcMem = CreateCompatibleDC(NULL);
    HDC hdcOrigin = CreateCompatibleDC(NULL);

    SelectObject(hdcMem, hNewBitmap);

    // �ܰ��� �׸� �귯�� ����
    HPEN hPen = CreatePen(PS_SOLID, 1, outlineColor);
    HGDIOBJ oldPen = SelectObject(hdcMem, hPen);

    SelectObject(hdcOrigin, hBitmap);

    // ��Ʈ���� ���������� ��ĵ�ϸ鼭 �ܰ��� Ȯ��
    for (int y = 1; y < bitmap.bmHeight - 1; ++y)
    {
        for (int x = 1; x < bitmap.bmWidth - 1; ++x)
        {
            COLORREF currentPixel = GetPixel(hdcOrigin, x, y);
            // ������ �ƴ� �� �˻�
            if (!colorMatch(currentPixel, targetColor, tolerance)) continue;

            // �ֺ� �ȼ� ��������
            COLORREF leftPixel = GetPixel(hdcOrigin, x - 1, y);
            COLORREF rightPixel = GetPixel(hdcOrigin, x + 1, y);
            COLORREF topPixel = GetPixel(hdcOrigin, x, y - 1);
            COLORREF bottomPixel = GetPixel(hdcOrigin, x, y + 1);

            // �ܰ����� �׸��� ���� - ������ ��
            bool drawLeft = colorMatch(leftPixel, targetColor, tolerance) && !colorMatch(leftPixel, outlineColor, tolerance);
            bool drawRight = colorMatch(rightPixel, targetColor, tolerance) && !colorMatch(leftPixel, outlineColor, tolerance);
            bool drawTop = colorMatch(topPixel, targetColor, tolerance) && !colorMatch(leftPixel, outlineColor, tolerance);
            bool drawBottom = colorMatch(bottomPixel, targetColor, tolerance) && !colorMatch(leftPixel, outlineColor, tolerance);

            if (drawLeft && left) SetPixel(hdcMem, x - 1, y, outlineColor);
            if (drawRight && right) SetPixel(hdcMem, x + 1, y, outlineColor);
            if (drawTop && top) SetPixel(hdcMem, x, y - 1, outlineColor);
            if (drawBottom && bottom) SetPixel(hdcMem, x, y + 1, outlineColor);
        }
    }

    SelectObject(hdcMem, oldPen);
    DeleteObject(hPen);

    DeleteDC(hdcMem);
    DeleteDC(hdcOrigin);

    return hNewBitmap;
}