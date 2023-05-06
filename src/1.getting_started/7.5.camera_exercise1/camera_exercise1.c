// This function is found in the camera class. What we basically do is keep the y position value at 0.0f to force our
// user to stick to the ground.
// rewritten for C using the CGLM

[...]
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

    // make sure the user stays at the ground level
    Position[1] = 0.0f; // <-- this one-liner keeps the user at the ground level (xz plane)
}
[...]
