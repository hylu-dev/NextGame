#include "stdafx.h"
#include "Triangle.h"

void Triangle::Draw() {
	App::DrawLine(
		p0.x, p0.y,
		p1.x, p1.y
	);
	App::DrawLine(
		p1.x, p1.y,
		p2.x, p2.y
	);
	App::DrawLine(
		p2.x, p2.y,
		p0.x, p0.y
	);
}

void Triangle::ApplyMatrix(float4x4 matrix) {
	p0 = matrix * p0;
	p1 = matrix * p1;
	p2 = matrix * p2;
}

void Triangle::Normalize() {
	p0.Normalize();
	p1.Normalize();
	p2.Normalize();
}
