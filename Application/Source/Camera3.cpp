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
	jumptimer = 0;
	canJump = true;
	temp = false;
}

void Camera3::Update(double dt)
{
	static const float CAMERA_SPEED = 45.f;
	static const float ZOOM_SPEED = 20.f;

	

	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);

	//position.y = 1;
	

	if(Application::IsKeyPressed('A'))
	{
		if (position.x > 50 || position.x < -50 || position.z > 50 || position.z < -50)
		{
			position += right * ZOOM_SPEED * static_cast<float>(dt);
		}
		else
		{
			position -= right * ZOOM_SPEED * static_cast<float>(dt);
			target = position + view;
		}
	}
	if(Application::IsKeyPressed('D'))
	{
		if (position.x > 50 || position.x < -50 || position.z > 50 || position.z < -50)
		{
			position -= right * ZOOM_SPEED * static_cast<float>(dt);
		}
		else
		{
			position += right * ZOOM_SPEED * static_cast<float>(dt);
			target = position + view;
		}
	}
	if(Application::IsKeyPressed('W'))
	{
		if (position.x > 50 || position.x < -50 || position.z > 50 || position.z < -50)
		{
			position -= view * ZOOM_SPEED * static_cast<float>(dt);
		}
		else
		{
			position += view * ZOOM_SPEED * static_cast<float>(dt);
			target = position + view;
		}
		
	}
	if(Application::IsKeyPressed('S'))
	{
		if (position.x > 50 || position.x < -50 || position.z > 50 || position.z < -50)
		{
			position += view * ZOOM_SPEED * static_cast<float>(dt);
		}
		else
		{
			position -= view * ZOOM_SPEED * static_cast<float>(dt);
			target = position + view;
		}
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
	if (Application::IsKeyPressed(VK_LEFT))
	{
		float yaw = -CAMERA_SPEED * static_cast<float>(dt);
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, -1, 0);
		view = rotation * view;
		up = rotation * up;
		target = position + view;
	}
	if (Application::IsKeyPressed(VK_UP))
	{
		float pitch = CAMERA_SPEED * static_cast<float>(dt);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotation * view;
		target = position + view;
	}
	if (Application::IsKeyPressed(VK_RIGHT))
	{
		float yaw = -CAMERA_SPEED * static_cast<float>(dt);
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		up = rotation * up;
		target = position + view;
	}
	if (Application::IsKeyPressed(VK_DOWN))
	{
		float pitch = -CAMERA_SPEED * static_cast<float>(dt);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotation * view;
		target = position + view;
	}
	//if (canJump || jumptimer > 0)
	//{
	//	if (Application::IsKeyPressed(VK_SPACE))
	//	{
	//		canJump = false;
	//	}
	//	if (temp)
	//	{
	//		position.y -= 1;
	//		if (position.y <= 0)
	//		{
	//			position.y = 0;
	//			jumptimer = 0;
	//			canJump = true;
	//		}
	//	}
	//	else if (position.y > 10 && canJump == false)
	//	{
	//		//canJump = true;
	//		temp = true;
	//	}
	//	else if (canJump == false)
	//	{
	//		jumptimer += 0.016667;
	//		position.y += 1;
	//	}
	//	
	//	
	//}
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