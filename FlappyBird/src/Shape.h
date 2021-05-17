#pragma once

struct Shape
{
	int x, y, w, h;
	Shape(int X, int Y, int W, int H)
		: x(X), y(Y), w(W), h(H) {}
	Shape() {}
};