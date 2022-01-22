#include "Point.h"
bool operator==(const Point& p1, const Point& p2) {
	if (p1.m_x == p2.m_x) {
		if (p1.m_y == p2.m_y) {
			return true;
		}
	}
	return false;
}
bool operator!=(const Point& p1, const Point& p2) {
	if (p1.m_x == p2.m_x) {
		if (p1.m_y == p2.m_y) {
			return false;
		}
	}
	return true;
}
Point::Point():m_x(1),m_y(1) {}
Point::Point(int x, int y) {
		m_x = x;
		m_y = y;
}
Point::Point(const Point& p) {
	this->m_x = p.m_x;
	this->m_y = p.m_y;
}
//ÅĞ¶Ï×ø±êÊÇ·ñ³¬³öÆåÅÌ·¶Î§
bool Point::isOutRange() {
	if (m_x >= 1 && m_x <= 9 && m_y >= 1 && m_y <= 10) {
		return false;
	}
	else {
		return true;
	}
}
//ÅĞ¶Ï×ø±êÊÇ·ñÔÚÄ³¸ö·¶Î§ÄÚ£¬ÖØÔØ
bool Point::isOutRange(int min_x,int min_y,int max_x,int max_y) {
	if (m_x >= min_x && m_x <= max_x && m_y >= min_y && m_y <= max_y) {
		return false;
	}
	else {
		return true;
	}
}