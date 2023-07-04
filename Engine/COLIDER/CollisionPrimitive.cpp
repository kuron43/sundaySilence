#include "CollisionPrimitive.h"

void Triangle::ComputeNormal() {
	Vector3 p0_p1 = p1 - p0;
	Vector3 p0_p2 = p2 - p0;

	normal = p0_p1.cross(p0_p2);
	normal.nomalize();
}