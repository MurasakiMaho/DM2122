#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"
#include "Assignment2.h"

#define Boundaries 51
#define RoadBoundaries 10
#define newBoundaries 51

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

	inAnotherWorld = false;
	speed = 20.f;
}

void Camera3::updateInAnotherWorld(bool newVal)
{
	inAnotherWorld = newVal;
}

void Camera3::updateSpeed(float newVal)
{
	speed = newVal;
}

void Camera3::Update(double dt)
{
	static const float CAMERA_SPEED = 90.f;
	float ZOOM_SPEED = speed;

	

	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	
	// a and d lil buggy
	if (!inAnotherWorld)
	{
		if (Application::IsKeyPressed('A'))
		{
			if ((position.x + 1) >= Boundaries || (position.x - 1) <= -Boundaries || (position.z + 1) >= Boundaries || (position.z - 1) <= RoadBoundaries)
			{
				//position += right * ZOOM_SPEED * static_cast<float>(dt);
				position += right * ZOOM_SPEED * static_cast<float>(dt);
				target = position + view;
			}
			else
			{
				position -= right * ZOOM_SPEED * static_cast<float>(dt);
				target = position + view;
			}
		}
		if (Application::IsKeyPressed('D'))
		{
			if ((position.x + 1) >= Boundaries || (position.x - 1) <= -Boundaries || (position.z + 1) >= Boundaries || (position.z - 1) <= RoadBoundaries)
			{
				//position -= right * ZOOM_SPEED * static_cast<float>(dt);
				position -= right * ZOOM_SPEED * static_cast<float>(dt);
				target = position + view;
			}
			else
			{
				position += right * ZOOM_SPEED * static_cast<float>(dt);
				target = position + view;
			}
		}
		if (Application::IsKeyPressed('W'))
		{
			if ((position.x + 1) >= Boundaries || (position.x - 1) <= -Boundaries || (position.z + 1) >= Boundaries || (position.z - 1) <= RoadBoundaries)
			{
				//position -= view * ZOOM_SPEED * static_cast<float>(dt);
			}
			else
			{
				position += view * ZOOM_SPEED * static_cast<float>(dt);
				target = position + view;
			}
			if (position.y != 0)
			{
				position.y = defaultPosition.y;
				target.y = position.y + view.y;
			}

		}
		if (Application::IsKeyPressed('S'))
		{
			if ((position.x + 0.1) >= Boundaries || (position.x - 0.1) <= -Boundaries || (position.z + 0.1) >= Boundaries || (position.z - 0.1) <= RoadBoundaries)
			{
				//position += view * ZOOM_SPEED * static_cast<float>(dt);
			}
			else
			{
				position -= view * ZOOM_SPEED * static_cast<float>(dt);
				target = position + view;
			}
			if (position.y != 0)
			{
				position.y = defaultPosition.y;
				target.y = position.y + view.y;
			}
		}
	}
	else
	{
		if (Application::IsKeyPressed('A'))
		{
			if ((position.x + 1) >= newBoundaries || (position.x - 1) <= -newBoundaries || (position.z + 1) >= newBoundaries || (position.z - 1) <= -newBoundaries)
			{
				//position += right * ZOOM_SPEED * static_cast<float>(dt);
				position += right * ZOOM_SPEED * static_cast<float>(dt);
				target = position + view;
			}
			else
			{
				position -= right * ZOOM_SPEED * static_cast<float>(dt);
				target = position + view;
			}
		}
		if (Application::IsKeyPressed('D'))
		{
			if ((position.x + 1) >= newBoundaries || (position.x - 1) <= -newBoundaries || (position.z + 1) >= newBoundaries || (position.z - 1) <= -newBoundaries)
			{
				//position -= right * ZOOM_SPEED * static_cast<float>(dt);
				position -= right * ZOOM_SPEED * static_cast<float>(dt);
				target = position + view;
			}
			else
			{
				position += right * ZOOM_SPEED * static_cast<float>(dt);
				target = position + view;
			}
		}
		if (Application::IsKeyPressed('W'))
		{
			if ((position.x + 1) >= newBoundaries || (position.x - 1) <= -newBoundaries || (position.z + 1) >= newBoundaries || (position.z - 1) <= -newBoundaries)
			{
				//position -= view * ZOOM_SPEED * static_cast<float>(dt);
			}
			else
			{
				position += view * ZOOM_SPEED * static_cast<float>(dt);
				target = position + view;
			}
			if (position.y != 0)
			{
				position.y = defaultPosition.y;
				target.y = position.y + view.y;
			}

		}
		if (Application::IsKeyPressed('S'))
		{
			if ((position.x + 0.1) >= newBoundaries || (position.x - 0.1) <= -newBoundaries || (position.z + 0.1) >= newBoundaries || (position.z - 0.1) <= -newBoundaries)
			{
				//position += view * ZOOM_SPEED * static_cast<float>(dt);
			}
			else
			{
				position -= view * ZOOM_SPEED * static_cast<float>(dt);
				target = position + view;
			}
			if (position.y != 0)
			{
				position.y = defaultPosition.y;
				target.y = position.y + view.y;
			}
		}
	}
	

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
