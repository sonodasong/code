#include <math.h>
#include "geometry.h"

tEulerAngle geoEulerAngleFromQuaternion(tQuaternion quaternion)
{
	tEulerAngle eulerAngle;
	float q0, q1, q2, q3;

	q0 = quaternion.q0;
	q1 = quaternion.q1;
	q2 = quaternion.q2;
	q3 = quaternion.q3;
	eulerAngle.roll = atan2(2 * (q0 * q1 + q2 * q3), 1 - 2 * (q1 * q1 + q2 * q2));
	eulerAngle.pitch = asin(2 * (q0 * q2 - q3 * q1));
	eulerAngle.yaw = atan2(2 * (q0 * q3 + q1 * q2), 1 - 2 * (q2 * q2 + q3 * q3));
	return eulerAngle;
}

tVector geoMagVectorInertialFrame(tVector vMagBody, tEulerAngle eMag)
{
	tVector vMagInertial;
	float c1, c2, c3;
	float s1, s2, s3;

	c1 = cos(eMag.yaw);
	c2 = cos(eMag.pitch);
	c3 = cos(eMag.roll);
	s1 = sin(eMag.yaw);
	s2 = sin(eMag.pitch);
	s3 = sin(eMag.roll);
	vMagInertial.vx = c1 * c2 * vMagBody.vx;
	vMagInertial.vx += (c1 * s2 * s3 - c3 * s1) * vMagBody.vy;
	vMagInertial.vx += (s1 * s3 + c1 * c3 * s2) * vMagBody.vz;
	vMagInertial.vy = c2 * s1 * vMagBody.vx;
	vMagInertial.vy += (c1 * c3 + s1 * s2 * s3) * vMagBody.vy;
	vMagInertial.vy += (c3 * s1 * s2 - c1 * s3) * vMagBody.vz;
	vMagInertial.vz = -s2 * vMagBody.vx;
	vMagInertial.vz += c2 * s3 * vMagBody.vy;
	vMagInertial.vz += c2 * c3 * vMagBody.vz;
	return vMagInertial;
}

tVector geoMagVectorInertialFrameZRotationIgnored(tVector vMagBody, tEulerAngle eMag)
{
	tVector vMagInertial;
	float c2, c3;
	float s2, s3;

	c2 = cos(eMag.pitch);
	c3 = cos(eMag.roll);
	s2 = sin(eMag.pitch);
	s3 = sin(eMag.roll);
	vMagInertial.vx = c2 * vMagBody.vx;
	vMagInertial.vx += s2 * s3 * vMagBody.vy;
	vMagInertial.vx += c3 * s2 * vMagBody.vz;
	vMagInertial.vy = 0.0;
	vMagInertial.vy += c3 * vMagBody.vy;
	vMagInertial.vy += s3 * vMagBody.vz;
	vMagInertial.vz = -s2 * vMagBody.vx;
	vMagInertial.vz += c2 * s3 * vMagBody.vy;
	vMagInertial.vz += c2 * c3 * vMagBody.vz;
	return vMagInertial;
}

float geoMagYawInertialFrame(tVector vMagInertial)
{
	float magYaw;

	magYaw = atan2(vMagInertial.vx, vMagInertial.vy);
	return magYaw;
}

tEulerAngle geoEulerAngleCorrected(tEulerAngle eMagBody, tVector vMagBody)
{
	tVector vMagInertial;

	vMagInertial = geoMagVectorInertialFrameZRotationIgnored(vMagBody, eMagBody);
	eMagBody.yaw = geoMagYawInertialFrame(vMagInertial);
	return eMagBody;
}
