#ifndef __SPACE_H__
#define __SPACE_H__

#include <library.h>

#define PI										3.14159265

#define FRAME_SIZE_SONAR						2280.0
#define FRAME_SIZE_METER						790.0

#define GEO_DISPLAY_WIDTH_METER					800.0
#define GEO_DISPLAY_HEIGHT_METER				600.0

#define GEO_DISPLAY_RESOLUTION_HORIZONTAL		1024.0
#define GEO_DISPLAY_RESOLUTION_VERTICAL			768.0

#define GEO_LAY_OUT								2
#define GEO_NEW_FRAME_X_COORDINATE_METER		0.0
#define GEO_NEW_FRAME_Y_COORDINATE_METER		0.0
#define GEO_NEW_FRAME_Z_COORDINATE_METER		0.0

typedef struct
{
	float px;
	float py;
	float pz;
} tPoint;

typedef struct
{
	float vx;
	float vy;
	float vz;
} tVector;

typedef struct
{
	float roll;
	float pitch;
	float yaw;
} tEulerAngle;

typedef struct
{
	float d0;
	float d1;
	float d2;
} tSonarDistance;

typedef struct {
	float ax;
	float az;
} tServoAngle;

tPoint geoCoordinateFromDistance(tSonarDistance sonarDistance, float a);
tServoAngle geoServoAngle(tPoint fromPoint, tPoint toPoint);
tVector geoVectorFromEulerAngle(tEulerAngle eulerAngle);
tPoint geoNewFramePoint(tPoint pOld);
tEulerAngle geoNewFrameEulerAngle(tEulerAngle eOld);
tPoint geoLaserPoint(tPoint pLaser, tVector vLaser);

#endif
