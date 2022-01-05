#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"


Camera3::Camera3()
{
}

Camera3::~Camera3()
{
}

void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
}

void Camera3::Update(double dt)
{
	static const float CAMERA_SPEED = 45.f;
	static const float ZOOM_SPEED = 20.f;
	if(Application::IsKeyPressed('A'))
	{
		float yaw = -CAMERA_SPEED * static_cast<float>(dt);
		Mtx44 rotation;
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		rotation.SetToRotation(yaw, 0, 1, 0);
		position = position - right;
		target = position + view;
	}
	if(Application::IsKeyPressed('D'))
	{
		float yaw = CAMERA_SPEED * static_cast<float>(dt);
		Mtx44 rotation;
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		rotation.SetToRotation(yaw, 0, 1, 0);
		position = position + right;
		target = position + view;
	}
	if(Application::IsKeyPressed('W'))
	{
		float pitch = -CAMERA_SPEED * static_cast<float>(dt);
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		position = position + view;
		target = position + view;
	}
	if(Application::IsKeyPressed('S'))
	{
		float pitch = CAMERA_SPEED * static_cast<float>(dt);
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		position = position - view;
		target = position + view;
	}
	//if(Application::IsKeyPressed('N'))
	//{
	//	//Vector3 view = target - position;
	//	//if(view.Length() > 5) //Prevent the camera from touching the origin
	//	//{
	//	//	view.Normalize();
	//	//	position += view * ZOOM_SPEED * dt;
	//	//}
	//	position = position + up * ZOOM_SPEED * dt;
	//	
	//}
	//if(Application::IsKeyPressed('M'))
	//{
	//	//Vector3 view = (target - position).Normalized();
	//	//position -= view * ZOOM_SPEED * dt;
	//	position = position - up * ZOOM_SPEED * dt;
	//}
	if (Application::IsKeyPressed(37))//left
	{
		float yaw = -CAMERA_SPEED * static_cast<float>(dt);
		Mtx44 rotation;
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		rotation.SetToRotation(yaw, 0, -1, 0);
		view = rotation * view;
		target = position + view;
	}
	if (Application::IsKeyPressed(38))//up
	{
		float pitch = -CAMERA_SPEED * static_cast<float>(dt);
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotation * view;
		target = position + view;
	}
	if (Application::IsKeyPressed(39))//right
	{
		float yaw = -CAMERA_SPEED * static_cast<float>(dt);
		Mtx44 rotation;
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		target = position + view;
	}
	if (Application::IsKeyPressed(40))//down
	{
		float pitch = CAMERA_SPEED * static_cast<float>(dt);
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotation * view;
		target = position + view;
	}
	if(Application::IsKeyPressed('R'))
	{
		Reset();
	}
}

void Camera3::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}