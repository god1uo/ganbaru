#pragma once
#include <memory>

using byte = unsigned char;

struct Color {
	byte r;
	byte g;
	byte b;
	byte a;
	Color(byte v_b = 127, byte v_g = 127, byte v_r = 127, byte v_a = 255) :r(v_r), g(v_g), b(v_b), a(v_a) {}
};

struct Point {
	float x;
	float y;
	float deep;
	Color color;
	Point(float v_x, float v_y, float v_deep = 0, Color v_color = Color()) :x(v_x), y(v_y), deep(v_deep), color(v_color) {}
	Point(const Point& p) :x(p.x), y(p.y), color(p.color) {}
};

class Canvas
{
	unsigned short m_Width{};
	unsigned short m_Height{};
	Color* m_ColorBuffer{};
public:
	Canvas(int width, int height, Color* buffer) :m_Width(width), m_Height(height), m_ColorBuffer(buffer) {};
	void ClearScreenBuffer() { if(nullptr != m_ColorBuffer)memset(m_ColorBuffer, 0, m_Width * m_Height * sizeof Color); }
	void DrawPoint(Point p);
	void DrawLine(Point p1, Point p2);
	void DrawTriangle(Point p1, Point p2, Point p3);
};

