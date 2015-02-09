#ifndef __SPACE_H__
#define __SPACE_H__

#include <library.h>

#define PI										3.14159265

typedef struct
{
	float q0;
	float q1;
	float q2;
	float q3;
} tQuaternion;

typedef struct
{
	float roll;
	float pitch;
	float yaw;
} tEulerAngle;

typedef struct
{
	float vx;
	float vy;
	float vz;
} tVector;

tEulerAngle geoEulerAngleFromQuaternion(tQuaternion quaternion);
tVector geoMagVectorInertialFrame(tVector vMagBody, tEulerAngle eMag);
tVector geoMagVectorInertialFrameZRotationIgnored(tVector vMagBody, tEulerAngle eMag);
float geoMagYawInertialFrame(tVector vMagInertial);
tEulerAngle geoEulerAngleCorrected(tEulerAngle eMagBody, tVector vMagBody);

#endif
