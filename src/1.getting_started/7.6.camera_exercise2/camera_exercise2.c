// Custom implementation of the LookAt function
// NOTE : I did not test this, but it should work... theoretically. :/
// recreated for C using CGLM ( 2022 )
void calculate_lookAt_matrix(vec3 position, vec3 target, vec3 worldUp, mat4 viewMatrix)
{
    // 1. Position = known
    // 2. Calculate cameraDirection
    vec3 tempVec = {0, 0, 0};
    glm_vec3_sub(position, target, tempVec);
    vec3 zaxis = {0, 0, 0};
    glm_normalize_to(tempVec, zaxis);
    // 3. Get positive right axis vector
    glm_normalize_to(worldUp, worldUp);
    glm_cross(worldUp, zaxis, tempVec);
    vec3 xaxis = {0, 0, 0};
    glm_normalize_to(tempVec, xaxis);
    // 4. Calculate camera up vector
    vec3 yaxis = {0, 0, 0};
    glm_cross(zaxis, xaxis, yaxis);

    // Create translation and rotation matrix
    // In glm we access elements as mat[col][row] due to column-major layout
    mat4 translation = GLM_MAT4_IDENTITY_INIT; // Identity matrix by default
    translation[3][0] = -position[0]; // Third column, first row
    translation[3][1] = -position[1];
    translation[3][2] = -position[2];
    mat4 rotation = GLM_MAT4_IDENTITY_INIT;
    rotation[0][0] = xaxis[0]; // First column, first row
    rotation[1][0] = xaxis[1];
    rotation[2][0] = xaxis[2];
    rotation[0][1] = yaxis[0]; // First column, second row
    rotation[1][1] = yaxis[1];
    rotation[2][1] = yaxis[2];
    rotation[0][2] = zaxis[0]; // First column, third row
    rotation[1][2] = zaxis[1];
    rotation[2][2] = zaxis[2];

    // Return lookAt matrix as combination of translation and rotation matrix
    // Remember to read from right to left (first translation then rotation)
    glm_mat4_mul(rotation, translation, viewMatrix); // The rotation / translation might be backwards ( not tested )
}

// Example of how to use this
// Don't forget to replace glm_lookat with this version
mat4 viewMatrix = GLM_MAT4_IDENTITY_INIT;
calculate_lookAt_matrix((vec3){camX, 0.0f, camZ}, (vec3){0.0f, 0.0f, 0.0f}, (vec3){0.0f, 1.0f, 0.0f}, viewMatrix);

