#pragma once
class Point
{
	friend bool operator==(const Point& p1, const Point& p2);
	friend bool operator!=(const Point& p1, const Point& p2);
public:
	int m_x, m_y;
	Point();
	Point(int x,int y);
	Point(const Point& p);
	bool isOutRange();
	bool isOutRange(int min_x, int min_y, int max_x, int max_y);
};