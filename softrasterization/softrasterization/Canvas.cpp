#include "Canvas.h"
#include "VecAndMatrix.h"

void Canvas::DrawPoint(Point p) {
	if (p.x < 0 || p.x >= m_Width || p.y < 0 || p.y >= m_Height) {
		return;
	}
	m_ColorBuffer[m_Width * (int)p.y + (int)p.x] = p.color;
}

void Canvas::DrawLine(Point p1, Point p2) {
	Point curp(p1);
	int delta_x = fabs(p1.x - p2.x);
	int delta_y = fabs(p1.y - p2.y);
	bool use_y = true;
	int step = delta_x;
	if (delta_y > delta_x) {
		step = delta_y;
		delta_y ^= delta_x;
		delta_x ^= delta_y;
		delta_y ^= delta_x;
		use_y = false;
	}
	int rise1;
	int rise2;
	if (use_y) {
		if (p1.y < p2.y)
			rise1 = 1;
		else
			rise1 = -1;
		if (p1.x < p2.x)
			rise2 = 1;
		else
			rise2 = -1;
	}
	else {
		if (p1.x < p2.x)
			rise1 = 1;
		else
			rise1 = -1;
		if (p1.y < p2.y)
			rise2 = 1;
		else
			rise2 = -1;
	}
	int delta_p = 2 * delta_y - delta_x;
	for (int i = 0; i <= step; ++i) {
		DrawPoint(curp);
		if (delta_p > 0) {
			if (use_y)
				curp.y += rise1;
			else
				curp.x += rise1;
			delta_p -= 2 * delta_x;
		}
		if (use_y)
			curp.x += rise2;
		else
			curp.y += rise2;
		delta_p += 2 * delta_y;
	}
}
//P=(1-u-v)A+uB+vC;
vec3 barycentric(const Point& A, const Point& B, const Point& C, const Point& P) {
	vec3 AB = vec3(B.x - A.x, B.y - A.y, 1);
	vec3 AC = vec3(C.x - A.x, C.y - A.y, 1);
	vec3 PA = vec3(A.x - P.x, A.y - P.y, 1);
	vec3 bct = cross(vec3(AB.x, AC.x, PA.x), vec3(AB.y, AC.y, PA.y));
	if (fabs(bct.z) < 1e-4)
		return vec3(-1, 1, 1);
	return vec3(1 - (bct.x + bct.y) / bct.z, bct.x / bct.z, bct.y / bct.z);
}

void Canvas::DrawTriangle(Point p1,Point p2,Point p3){
	int lower_x = std::min(p1.x, std::min(p2.x, p3.x));
	int lower_y = std::min(p1.y, std::min(p2.y, p3.y));
	int upper_x = std::max(p1.x, std::max(p2.x, p3.x));
	int upper_y = std::max(p1.y, std::max(p2.y, p3.y));

	for (int i = lower_x; i <= upper_x; ++i) {
		for (int j = lower_y; j <= upper_y; ++j) {
			auto bct = barycentric(p1, p2, p3, Point(i,j));
			if (bct.x > 0 && bct.y > 0 && bct.z > 0) {
				double deep = p1.deep*bct.x+
				DrawPoint(Point(i, j));
			}
		}
	}
}
