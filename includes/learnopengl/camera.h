#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <cglm/cglm.h>

// Default camera values
#define YAW          -90.0f
#define PITCH          0.0f
#define SPEED          2.5f
#define SENSITIVITY    0.1f
#define ZOOM          45.0f

// Defines several possible options for camera movement. Used as abstraction to stay away from window-system specific input methods
typedef enum
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
} Camera_Movement;

// camera Attributes
struct CAMERA
{
    vec3 Position;
    vec3 Front;
    vec3 Up;
    vec3 Right;
    vec3 WorldUp;

    // euler Angles
    float Yaw;
    float Pitch;

    // camera options
    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;
};

struct CAMERA* Camera;

// calculates the front vector from the Camera's (updated) Euler Angles
void updateCameraVectors()
{
	// calculate the new Front vector
	vec3 vfront = {0, 0, 0};
	vfront[0] = cos(glm_rad(Camera->Yaw)) * cos(glm_rad(Camera->Pitch));
	vfront[1] = sin(glm_rad(Camera->Pitch));
	vfront[2] = sin(glm_rad(Camera->Yaw)) * cos(glm_rad(Camera->Pitch));
	glm_normalize_to(vfront, Camera->Front);
	// also re-calculate the Right and Up vector
    // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    vec3 tempVec = {0, 0, 0};
    glm_cross(Camera->Front, Camera->WorldUp, tempVec);
	glm_normalize_to(tempVec, Camera->Right);
	glm_cross(Camera->Right, Camera->Front, tempVec);
	glm_normalize_to(tempVec, Camera->Up);
}

// constructor with vectors
void CreateCameraVector(vec3 position)
{
    Camera = (struct CAMERA*)malloc(sizeof(struct CAMERA));
    Camera->Front[0] = 0.0f;
    Camera->Front[1] = 0.0f;
    Camera->Front[2] = -1.0f;
    Camera->MovementSpeed = SPEED;
    Camera->MouseSensitivity = SENSITIVITY;
    Camera->Zoom = ZOOM;
	Camera->Position[0] = position[0];
	Camera->Position[1] = position[1];
	Camera->Position[2] = position[2];
	Camera->WorldUp[0] = 0.0f;
	Camera->WorldUp[1] = 1.0f;
	Camera->WorldUp[2] = 0.0f;
	Camera->Yaw = YAW;
	Camera->Pitch = PITCH;
	updateCameraVectors();
}

// constructor with scalar values
void CreateCameraScalar(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
{
    Camera->Front[0] = 0.0f;
    Camera->Front[1] = 0.0f;
    Camera->Front[2] = -1.0f;
    Camera->MovementSpeed = SPEED;
    Camera->MouseSensitivity = SENSITIVITY;
    Camera->Zoom = ZOOM;
	Camera->Position[0] = posX;
	Camera->Position[1] = posY;
	Camera->Position[2] = posZ;
	Camera->WorldUp[0]  = upX;
	Camera->WorldUp[1]  = upY;
	Camera->WorldUp[2]  = upZ;
	Camera->Yaw = yaw;
	Camera->Pitch = pitch;
	updateCameraVectors();
}

// returns the view matrix calculated using Euler Angles and the LookAt Matrix
void Camera_GetViewMatrix(mat4 mat)
{
    vec3 tempVec = {0, 0, 0};
    glm_vec3_add(Camera->Position, Camera->Front, tempVec);
	glm_lookat(Camera->Position, tempVec, Camera->Up, mat);
}

// processes input received from any keyboard-like input system.
// Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera_ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
	float velocity = Camera->MovementSpeed * deltaTime;
	if (direction == FORWARD)
    {
        vec3 tempVec = {0, 0, 0};
        glm_vec3_muladds(Camera->Front, velocity, tempVec);
        glm_vec3_add(Camera->Position, tempVec, Camera->Position);
    }

	if (direction == BACKWARD)
    {
        vec3 tempVec = {0, 0, 0};
        glm_vec3_muladds(Camera->Front, velocity, tempVec);
        glm_vec3_sub(Camera->Position, tempVec, Camera->Position);
    }

	if (direction == LEFT)
    {
        vec3 tempVec = {0, 0, 0};
        glm_vec3_muladds(Camera->Right, velocity, tempVec);
        glm_vec3_sub(Camera->Position, tempVec, Camera->Position);
    }

	if (direction == RIGHT)
    {
        vec3 tempVec = {0, 0, 0};
        glm_vec3_muladds(Camera->Right, velocity, tempVec);
        glm_vec3_add(Camera->Position, tempVec, Camera->Position);
    }
}

// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera_ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
	xoffset *= Camera->MouseSensitivity;
	yoffset *= Camera->MouseSensitivity;

	Camera->Yaw   += xoffset;
	Camera->Pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if(constrainPitch)
	{
		if (Camera->Pitch > 89.0f)
			Camera->Pitch = 89.0f;

		if (Camera->Pitch < -89.0f)
			Camera->Pitch = -89.0f;
	}

	// update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();
}

// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera_ProcessMouseScroll(float yoffset)
{
	Camera->Zoom -= (float)yoffset;
	if (Camera->Zoom < 1.0f)
		Camera->Zoom = 1.0f;

	if (Camera->Zoom > 45.0f)
		Camera->Zoom = 45.0f;
}

void Camera_CleanUp()
{
    free(Camera);
}

#endif
