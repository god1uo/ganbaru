#include "Canvas.h"

void Canvas::DrawPoint(Point p) {
	if (p.x < 0 || p.x >= m_Width || p.y < 0 || p.y >= m_Height) {
		return;
	}
	m_ColorBuffer[(int)(m_Width * p.y + p.x)] = p.color;
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
	int rise;
	if (use_y) {
		if (p1.y < p2.y)
			rise = 1;
		else
			rise = -1;
	}
	else {
		if (p1.x < p2.x)
			rise = 1;
		else
			rise = -1;
	}
	int delta_p = 2 * delta_y - delta_x;
	for (int i = 0; i <= step; ++i) {
		DrawPoint(curp);
		if (delta_p > 0) {
			if (use_y)
				curp.y += rise;
			else
				curp.x += rise;
			delta_p -= 2 * delta_x;
		}
		if (use_y)
			curp.x += rise;
		else
			curp.y += rise;
		delta_p += 2 * delta_y;
	}
}