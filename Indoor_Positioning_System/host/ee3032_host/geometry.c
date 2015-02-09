#include <math.h>
#include "geometry.h"

tPoint geoCoordinateFromDistance(tSonarDistance sonarDistance, float a)
{
	tPoint point;
	float d0, d1, d2;

	d0 = sonarDistance.d0;
	d1 = sonarDistance.d1;
	d2 = sonarDistance.d2;
	d0 = d0 * d0;
	d1 = d1 * d1;
	d2 = d2 * d2;
	point.px = (d1 - d2) / (4 * a);
	point.py = a + (2 * d0 - d1 - d2) / (4 * a);
	a = a * a;
	a = (2 * (d1 + d2) * (2 * a + d0) - 2 * d0 *d0 - d1 * d1 - d2 * d2) / (8 * a) - a;
	point.pz = sqrt(a);
	return point;
}

tServoAngle geoServoAngle(tPoint fromPoint, tPoint toPoint)
{
	tServoAngle servoAngle;
	float vx;
	float vy;
	float vz;

	vx = toPoint.px - fromPoint.px;
	vy = toPoint.py - fromPoint.py;
	vz = toPoint.pz - fromPoint.pz;
	if (floatEqual(vy, 0.0)) {
		servoAngle.ax = -atan(vx / vz);
		servoAngle.az = -PI / 2;
	} else {
		if (vy > 0.0) {
			servoAngle.ax = -atan(sqrt(vx * vx + vy * vy) / vz);
		} else if (vy < 0.0) {
			servoAngle.ax = atan(sqrt(vx * vx + vy * vy) / vz);
		}
		servoAngle.az = -atan(vx / vy);
	}
	/* adjustment for servo */
	servoAngle.ax = -servoAngle.ax * 180.0 / PI + 90.0;
	servoAngle.az = servoAngle.az * 180.0 / PI + 90.0;
	servoAngle.ax = constrain(servoAngle.ax, 0.0, 180.0);
	servoAngle.az = constrain(servoAngle.az, 0.0, 180.0);
	return servoAngle;
}

/* original vector is (1, 0, 0) */
tVector geoVectorFromEulerAngle(tEulerAngle eulerAngle)
{
	tVector vector;
	vector.vx = cos(eulerAngle.pitch) * cos(eulerAngle.yaw);
	vector.vy = cos(eulerAngle.pitch) * sin(eulerAngle.yaw);
	vector.vz = -sin(eulerAngle.pitch);
	return vector;
}

tPoint geoNewFramePoint(tPoint pOld)
{
	tPoint pNew;
	tVector translate;

	translate.vx = GEO_NEW_FRAME_X_COORDINATE_METER * FRAME_SIZE_SONAR / FRAME_SIZE_METER;
	translate.vy = GEO_NEW_FRAME_Y_COORDINATE_METER * FRAME_SIZE_SONAR / FRAME_SIZE_METER;
	translate.vz = GEO_NEW_FRAME_Z_COORDINATE_METER * FRAME_SIZE_SONAR / FRAME_SIZE_METER;
	pOld.px = pOld.px - translate.vx;
	pOld.py = pOld.py - translate.vy;
	pOld.pz = pOld.pz - translate.vz;
#if GEO_LAY_OUT == 1
	pNew.px = -pOld.py;
	pNew.py = pOld.px;
#elif GEO_LAY_OUT == 2
	pNew.px = pOld.px;
	pNew.py = pOld.py;
#else
	pNew.px = pOld.py;
	pNew.py = -pOld.px;
#endif
	pNew.pz = pOld.pz;
	return pNew;
}

tPoint geoLaserPoint(tPoint pLaser, tVector vLaser)
{
	tPoint pCross;
	float a;

	if (vLaser.vx > 0.0) {
		a = -pLaser.px / vLaser.vx;
		pCross.py = pLaser.py + a * vLaser.vy;
		pCross.pz = pLaser.pz + a * vLaser.vz;
	} else {
		if (vLaser.vy > 0.0) {
			pCross.py = GEO_DISPLAY_WIDTH_METER * FRAME_SIZE_SONAR / FRAME_SIZE_METER / 2;
		} else {
			pCross.py = -GEO_DISPLAY_WIDTH_METER * FRAME_SIZE_SONAR / FRAME_SIZE_METER / 2;
		}
		if (vLaser.vz > 0) {
			pCross.pz = GEO_DISPLAY_HEIGHT_METER * FRAME_SIZE_SONAR / FRAME_SIZE_METER;
		} else {
			pCross.pz = 0.0;
		}
	}
	pCross.px = 0.0;
	return pCross;
}
