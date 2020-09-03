#include "Frustum.h"

Frustum::Frustum()
{

}

Frustum::~Frustum()
{

}

void Frustum::calculate_frustum(Window* w,glm::vec3 right, glm::vec3 up, glm::vec3 front, glm::vec3 pos, float fov, float near, float far)
{
	float fovy = fov;
	float nr = near;
	float fr = far;

	float hheight = tan(fovy / 2.0f);
	float hwidth = hheight * 1.0f;

	glm::vec3 farright = (hwidth * fr * right) * (float)w->GetWidth() / (float)w->GetHeigth();
	glm::vec3 fartop = (hheight * fr * up);
	glm::vec3 nearright = (hwidth * nr * right) * (float)w->GetWidth() / (float)w->GetHeigth();
	glm::vec3 neartop = (hheight * nr * up);
	glm::vec3 center = pos + fr * front;
	glm::vec3 nearcenter = pos + nr * -front;

	glm::vec3 ftl = center - farright + fartop; //far top left
	glm::vec3 fbr = center + farright - fartop; //far bottom right
	glm::vec3 ftr = center + farright + fartop; //far bottom right
	glm::vec3 fbl = center - farright - fartop; //far bottom right
	glm::vec3 ntl = nearcenter - nearright + neartop; //far top left
	glm::vec3 nbr = nearcenter + nearright - neartop; //far bottom right
	glm::vec3 ntr = nearcenter + nearright + neartop; //far bottom right
	glm::vec3 nbl = nearcenter - nearright - neartop; //far bottom right
	planes.clear();
	// FAR
	glm::vec3 v = ftr - ftl;
	glm::vec3 u = fbr - ftl;
	glm::vec3 n = glm::cross(v, u);
	float D = -glm::dot(n, ftl);
	planes.push_back(Plane{ n, D });
	// NEAR
	v = ntr - ntl;
	u = nbr - ntl;
	n = glm::cross(v, u);
	D = -glm::dot(n, ntl);
	planes.push_back(Plane{ n, D });
	// TOP
	v = ftr - ftl;
	u = ntr - ftl;
	n = glm::cross(v, u);
	D = -glm::dot(n, ftl);
	planes.push_back(Plane{ n, D });
	// BOTTOM
	v = fbr - fbl;
	u = nbr - fbl;
	n = glm::cross(v, u);
	D = -glm::dot(n, fbl) * 0.8f;
	planes.push_back(Plane{ n, D });
	// RIGHT
	v = fbr - nbr;
	u = ntr - nbr;
	n = glm::cross(v, u);
	D = -glm::dot(n, nbr);
	planes.push_back(Plane{ n, D });
	// LEFT
	v = fbl - nbl;
	u = ntl - nbl;
	n = glm::cross(v, u);
	D = -glm::dot(n, nbl);
	planes.push_back(Plane{ n, D });
}

bool Frustum::is_in_frustum(Bounds bounds,vec3 position,string name, const bool isInFrustum)
{
	bool isEntityCurrentlyInFrustum = false;
	glm::vec3 min, max;

	min.x = bounds.minX;
	min.y = bounds.minY;
	min.z = bounds.minZ;

	max.x = bounds.maxX;
	max.y = bounds.maxY;
	max.z = bounds.maxZ;

	glm::vec3 pos = position;
	glm::vec3 boxnearbottomleft = min + pos;
	glm::vec3 boxnearbottomright = glm::vec3(-min.x, min.y, min.z) + pos;
	glm::vec3 boxneartopright = glm::vec3(-min.x, -min.y, min.z) + pos;
	glm::vec3 boxneartopleft = glm::vec3(min.x, -min.y, min.z) + pos;
	glm::vec3 boxfartopright = max + pos;
	glm::vec3 boxfartopleft = glm::vec3(-max.x, max.y, max.z) + pos;
	glm::vec3 boxfarbottomleft = glm::vec3(-max.x, -max.y, max.z) + pos;
	glm::vec3 boxfarbottomright = glm::vec3(max.x, -max.y, max.z) + pos;

	if (planes[0].n.x * boxnearbottomleft.x + planes[0].n.y * boxnearbottomleft.y + planes[0].n.z * boxnearbottomleft.z + planes[0].D > 0 && planes[0].n.x * boxnearbottomright.x + planes[0].n.y * boxnearbottomright.y + planes[0].n.z * boxnearbottomright.z + planes[0].D > 0 &&
		planes[0].n.x * boxneartopright.x + planes[0].n.y * boxneartopright.y + planes[0].n.z * boxneartopright.z + planes[0].D > 0 && planes[0].n.x * boxneartopleft.x + planes[0].n.y * boxneartopleft.y + planes[0].n.z * boxneartopleft.z + planes[0].D > 0 &&
		planes[0].n.x * boxfarbottomleft.x + planes[0].n.y * boxfarbottomleft.y + planes[0].n.z * boxfarbottomleft.z + planes[0].D > 0 && planes[0].n.x * boxfarbottomright.x + planes[0].n.y * boxfarbottomright.y + planes[0].n.z * boxfarbottomright.z + planes[0].D > 0 &&
		planes[0].n.x * boxfartopright.x + planes[0].n.y * boxfartopright.y + planes[0].n.z * boxfartopright.z + planes[0].D > 0 && planes[0].n.x * boxfartopleft.x + planes[0].n.y * boxfartopleft.y + planes[0].n.z * boxfartopleft.z + planes[0].D > 0)
	{
		isEntityCurrentlyInFrustum = false;
		if (isEntityCurrentlyInFrustum != isInFrustum)
		{
			cout << name << " is not in frustum" << endl;
		}

		return isEntityCurrentlyInFrustum;
	}
		

	// NEAR
	if (planes[1].n.x * boxnearbottomleft.x + planes[1].n.y * boxnearbottomleft.y + planes[1].n.z * boxnearbottomleft.z + planes[1].D < 0 && planes[1].n.x * boxnearbottomright.x + planes[1].n.y * boxnearbottomright.y + planes[1].n.z * boxnearbottomright.z + planes[1].D < 0 &&
		planes[1].n.x * boxneartopright.x + planes[1].n.y * boxneartopright.y + planes[1].n.z * boxneartopright.z + planes[1].D < 0 && planes[1].n.x * boxneartopleft.x + planes[1].n.y * boxneartopleft.y + planes[1].n.z * boxneartopleft.z + planes[1].D < 0 &&
		planes[1].n.x * boxfarbottomleft.x + planes[1].n.y * boxfarbottomleft.y + planes[1].n.z * boxfarbottomleft.z + planes[1].D < 0 && planes[1].n.x * boxfarbottomright.x + planes[1].n.y * boxfarbottomright.y + planes[1].n.z * boxfarbottomright.z + planes[1].D < 0 &&
		planes[1].n.x * boxfartopright.x + planes[1].n.y * boxfartopright.y + planes[1].n.z * boxfartopright.z + planes[1].D < 0 && planes[1].n.x * boxfartopleft.x + planes[1].n.y * boxfartopleft.y + planes[1].n.z * boxfartopleft.z + planes[1].D < 0)
	{
		isEntityCurrentlyInFrustum = false;
		if (isEntityCurrentlyInFrustum != isInFrustum)
		{
			cout << name << " is not in frustum" << endl;
		}

		return isEntityCurrentlyInFrustum;
	}

	// TOP
	if (planes[2].n.x * boxnearbottomleft.x + planes[2].n.y * boxnearbottomleft.y + planes[2].n.z * boxnearbottomleft.z + planes[2].D < 0 && planes[2].n.x * boxnearbottomright.x + planes[2].n.y * boxnearbottomright.y + planes[2].n.z * boxnearbottomright.z + planes[2].D < 0 &&
		planes[2].n.x * boxneartopright.x + planes[2].n.y * boxneartopright.y + planes[2].n.z * boxneartopright.z + planes[2].D < 0 && planes[2].n.x * boxneartopleft.x + planes[2].n.y * boxneartopleft.y + planes[2].n.z * boxneartopleft.z + planes[2].D < 0 &&
		planes[2].n.x * boxfarbottomleft.x + planes[2].n.y * boxfarbottomleft.y + planes[2].n.z * boxfarbottomleft.z + planes[2].D < 0 && planes[2].n.x * boxfarbottomright.x + planes[2].n.y * boxfarbottomright.y + planes[2].n.z * boxfarbottomright.z + planes[2].D < 0 &&
		planes[2].n.x * boxfartopright.x + planes[2].n.y * boxfartopright.y + planes[2].n.z * boxfartopright.z + planes[2].D < 0 && planes[2].n.x * boxfartopleft.x + planes[2].n.y * boxfartopleft.y + planes[2].n.z * boxfartopleft.z + planes[2].D < 0)
	{
		isEntityCurrentlyInFrustum = false;
		if (isEntityCurrentlyInFrustum != isInFrustum)
		{
			cout << name << " is not in frustum" << endl;
		}

		return isEntityCurrentlyInFrustum;
	}

	// BOTTOM
	if (planes[3].n.x * boxnearbottomleft.x + planes[3].n.y * boxnearbottomleft.y + planes[3].n.z * boxnearbottomleft.z + planes[3].D > 0 && planes[3].n.x * boxnearbottomright.x + planes[3].n.y * boxnearbottomright.y + planes[3].n.z * boxnearbottomright.z + planes[3].D > 0 &&
		planes[3].n.x * boxneartopright.x + planes[3].n.y * boxneartopright.y + planes[3].n.z * boxneartopright.z + planes[3].D > 0 && planes[3].n.x * boxneartopleft.x + planes[3].n.y * boxneartopleft.y + planes[3].n.z * boxneartopleft.z + planes[3].D > 0 &&
		planes[3].n.x * boxfarbottomleft.x + planes[3].n.y * boxfarbottomleft.y + planes[3].n.z * boxfarbottomleft.z + planes[3].D > 0 && planes[3].n.x * boxfarbottomright.x + planes[3].n.y * boxfarbottomright.y + planes[3].n.z * boxfarbottomright.z + planes[3].D > 0 &&
		planes[3].n.x * boxfartopright.x + planes[3].n.y * boxfartopright.y + planes[3].n.z * boxfartopright.z + planes[3].D > 0 && planes[3].n.x * boxfartopleft.x + planes[3].n.y * boxfartopleft.y + planes[3].n.z * boxfartopleft.z + planes[3].D > 0)
	{
		isEntityCurrentlyInFrustum = false;
		if (isEntityCurrentlyInFrustum != isInFrustum)
		{
			cout << name << " is not in frustum" << endl;
		}

		return isEntityCurrentlyInFrustum;
	}

	// RIGHT
	if (planes[4].n.x * boxnearbottomleft.x + planes[4].n.y * boxnearbottomleft.y + planes[4].n.z * boxnearbottomleft.z + planes[4].D > 0 && planes[4].n.x * boxnearbottomright.x + planes[4].n.y * boxnearbottomright.y + planes[4].n.z * boxnearbottomright.z + planes[4].D > 0 &&
		planes[4].n.x * boxneartopright.x + planes[4].n.y * boxneartopright.y + planes[4].n.z * boxneartopright.z + planes[4].D > 0 && planes[4].n.x * boxneartopleft.x + planes[4].n.y * boxneartopleft.y + planes[4].n.z * boxneartopleft.z + planes[4].D > 0 &&
		planes[4].n.x * boxfarbottomleft.x + planes[4].n.y * boxfarbottomleft.y + planes[4].n.z * boxfarbottomleft.z + planes[4].D > 0 && planes[4].n.x * boxfarbottomright.x + planes[4].n.y * boxfarbottomright.y + planes[4].n.z * boxfarbottomright.z + planes[4].D > 0 &&
		planes[4].n.x * boxfartopright.x + planes[4].n.y * boxfartopright.y + planes[4].n.z * boxfartopright.z + planes[4].D > 0 && planes[4].n.x * boxfartopleft.x + planes[4].n.y * boxfartopleft.y + planes[4].n.z * boxfartopleft.z + planes[4].D > 0)
	{
		isEntityCurrentlyInFrustum = false;
		if (isEntityCurrentlyInFrustum != isInFrustum)
		{
			cout << name << " is not in frustum" << endl;
		}

		return isEntityCurrentlyInFrustum;
	}

	// LEFT
	if (planes[5].n.x * boxnearbottomleft.x + planes[5].n.y * boxnearbottomleft.y + planes[5].n.z * boxnearbottomleft.z + planes[5].D < 0 && planes[5].n.x * boxnearbottomright.x + planes[5].n.y * boxnearbottomright.y + planes[5].n.z * boxnearbottomright.z + planes[5].D < 0 &&
		planes[5].n.x * boxneartopright.x + planes[5].n.y * boxneartopright.y + planes[5].n.z * boxneartopright.z + planes[5].D < 0 && planes[5].n.x * boxneartopleft.x + planes[5].n.y * boxneartopleft.y + planes[5].n.z * boxneartopleft.z + planes[5].D < 0 &&
		planes[5].n.x * boxfarbottomleft.x + planes[5].n.y * boxfarbottomleft.y + planes[5].n.z * boxfarbottomleft.z + planes[5].D < 0 && planes[5].n.x * boxfarbottomright.x + planes[5].n.y * boxfarbottomright.y + planes[5].n.z * boxfarbottomright.z + planes[5].D < 0 &&
		planes[5].n.x * boxfartopright.x + planes[5].n.y * boxfartopright.y + planes[5].n.z * boxfartopright.z + planes[5].D < 0 && planes[5].n.x * boxfartopleft.x + planes[5].n.y * boxfartopleft.y + planes[5].n.z * boxfartopleft.z + planes[5].D < 0)
	{
		isEntityCurrentlyInFrustum = false;
		if (isEntityCurrentlyInFrustum != isInFrustum)
		{
			cout << name << " is not in frustum" << endl;
		}

		return isEntityCurrentlyInFrustum;
	}

	isEntityCurrentlyInFrustum = true;
	if (isEntityCurrentlyInFrustum != isInFrustum)
	{
		cout << name << " is in frustum" << endl;
	}

	return isEntityCurrentlyInFrustum;
}