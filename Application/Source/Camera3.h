#ifndef CAMERA_3_H
#define CAMERA_3_H

#include "Camera.h"


class Camera3 : public Camera
{
private:
	bool inAnotherWorld;
	float speed;
public:
	Vector3 position;
	Vector3 target;
	Vector3 up;

	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;

	Camera3();
	~Camera3();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	void updateInAnotherWorld(bool newVal);
	void updateSpeed(float newVal);
	virtual void Update(double dt);
	virtual void Reset();
};

#endif