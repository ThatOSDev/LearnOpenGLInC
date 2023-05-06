
// NOTE : This code has enough info in it for you to fix it on your own. Some of these pointlights
//        were not finished converting from x y and z to using [0] [1] [2]. CGLM requires this conversion.

// == ==============================================================================================
//       DESERT
// == ==============================================================================================
glClearColor(0.75f, 0.52f, 0.3f, 1.0f);
[...]
vec3 pointLightColors[] = {
    {1.0f, 0.6f, 0.0f},
    {1.0f, 0.0f, 0.0f},
    {1.0f, 1.0, 0.0},
    {0.2f, 0.2f, 1.0f}
};
[...]
// Directional light
glUniform3f(glGetUniformLocation(lightingShaderID, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
glUniform3f(glGetUniformLocation(lightingShaderID, "dirLight.ambient"), 0.3f, 0.24f, 0.14f);
glUniform3f(glGetUniformLocation(lightingShaderID, "dirLight.diffuse"), 0.7f, 0.42f, 0.26f);
glUniform3f(glGetUniformLocation(lightingShaderID, "dirLight.specular"), 0.5f, 0.5f, 0.5f);
// Point light 1
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[0].position"), pointLightPositions[0][0], pointLightPositions[0][1], pointLightPositions[0][2]);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[0].ambient"), pointLightColors[0][0] * 0.1,  pointLightColors[0][1] * 0.1,  pointLightColors[0][2] * 0.1);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[0].diffuse"), pointLightColors[0][0],  pointLightColors[0][1],  pointLightColors[0][2]);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[0].specular"), pointLightColors[0][0],  pointLightColors[0][1],  pointLightColors[0][2]);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[0].constant"), 1.0f);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[0].linear"), 0.09);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[0].quadratic"), 0.032);
// Point light 2
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[1].position"), pointLightPositions[1][0], pointLightPositions[1][1], pointLightPositions[1][2]);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[1].ambient"), pointLightColors[1][0] * 0.1,  pointLightColors[1][1] * 0.1,  pointLightColors[1][2] * 0.1);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[1].diffuse"), pointLightColors[1][0],  pointLightColors[1][1],  pointLightColors[1][2]);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[1].specular"), pointLightColors[1][0],  pointLightColors[1][1],  pointLightColors[1][2]);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[1].constant"), 1.0f);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[1].linear"), 0.09);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[1].quadratic"), 0.032);
// Point light 3
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[2].position"), pointLightPositions[2][0], pointLightPositions[2][1], pointLightPositions[2][2]);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[2].ambient"), pointLightColors[2][0] * 0.1,  pointLightColors[2][1] * 0.1,  pointLightColors[2][2] * 0.1);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[2].diffuse"), pointLightColors[2][0],  pointLightColors[2][1],  pointLightColors[2][2]);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[2].specular") ,pointLightColors[2][0],  pointLightColors[2][1],  pointLightColors[2][2]);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[2].constant"), 1.0f);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[2].linear"), 0.09);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[2].quadratic"), 0.032);
// Point light 4
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[3].position"), pointLightPositions[3][0], pointLightPositions[3][1], pointLightPositions[3][2]);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[3].ambient"), pointLightColors[3][0] * 0.1,  pointLightColors[3][1] * 0.1,  pointLightColors[3][2] * 0.1);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[3].diffuse"), pointLightColors[3][0],  pointLightColors[3][1],  pointLightColors[3][2]);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[3].specular"), pointLightColors[3][0],  pointLightColors[3][1],  pointLightColors[3][2]);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[3].constant"), 1.0f);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[3].linear"), 0.09);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[3].quadratic"), 0.032);
// SpotLight
glUniform3f(glGetUniformLocation(lightingShaderID, "spotLight.position"), Camera->Position[0], Camera->Position[1], Camera->Position[2]);
glUniform3f(glGetUniformLocation(lightingShaderID, "spotLight.direction"), Camera->Front[0], Camera->Front[1], Camera->Front[2]);
glUniform3f(glGetUniformLocation(lightingShaderID, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
glUniform3f(glGetUniformLocation(lightingShaderID, "spotLight.diffuse"), 0.8f, 0.8f, 0.0f);
glUniform3f(glGetUniformLocation(lightingShaderID, "spotLight.specular"), 0.8f, 0.8f, 0.0f);
glUniform1f(glGetUniformLocation(lightingShaderID, "spotLight.constant"), 1.0f);
glUniform1f(glGetUniformLocation(lightingShaderID, "spotLight.linear"), 0.09);
glUniform1f(glGetUniformLocation(lightingShaderID, "spotLight.quadratic"), 0.032);
glUniform1f(glGetUniformLocation(lightingShaderID, "spotLight.cutOff"), cos(glm_rad(12.5f)));
glUniform1f(glGetUniformLocation(lightingShaderID, "spotLight.outerCutOff"), cos(glm_rad(13.0f)));
// == ==============================================================================================
//       FACTORY
// == ==============================================================================================
glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
[...]
vec3 pointLightColors[] = {
    {0.2f, 0.2f, 0.6f},
    {0.3f, 0.3f, 0.7f},
    {0.0f, 0.0f, 0.3f},
    {0.4f, 0.4f, 0.4f}
};
[...]
// Directional light
glUniform3f(glGetUniformLocation(lightingShaderID, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
glUniform3f(glGetUniformLocation(lightingShaderID, "dirLight.ambient"), 0.05f, 0.05f, 0.1f);
glUniform3f(glGetUniformLocation(lightingShaderID, "dirLight.diffuse"), 0.2f, 0.2f, 0.7);
glUniform3f(glGetUniformLocation(lightingShaderID, "dirLight.specular"), 0.7f, 0.7f, 0.7f);
// Point light 1
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[0].ambient"), pointLightColors[0].x * 0.1,  pointLightColors[0].y * 0.1,  pointLightColors[0].z * 0.1);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[0].diffuse"), pointLightColors[0].x,  pointLightColors[0].y,  pointLightColors[0].z);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[0].specular"), pointLightColors[0].x,  pointLightColors[0].y,  pointLightColors[0].z);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[0].constant"), 1.0f);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[0].linear"), 0.09);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[0].quadratic"), 0.032);
// Point light 2
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[1].ambient"), pointLightColors[1].x * 0.1,  pointLightColors[1].y * 0.1,  pointLightColors[1].z * 0.1);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[1].diffuse"), pointLightColors[1].x,  pointLightColors[1].y,  pointLightColors[1].z);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[1].specular"), pointLightColors[1].x,  pointLightColors[1].y,  pointLightColors[1].z);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[1].constant"), 1.0f);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[1].linear"), 0.09);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[1].quadratic"), 0.032);
// Point light 3
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[2].ambient"), pointLightColors[2].x * 0.1,  pointLightColors[2].y * 0.1,  pointLightColors[2].z * 0.1);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[2].diffuse"), pointLightColors[2].x,  pointLightColors[2].y,  pointLightColors[2].z);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[2].specular") ,pointLightColors[2].x,  pointLightColors[2].y,  pointLightColors[2].z);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[2].constant"), 1.0f);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[2].linear"), 0.09);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[2].quadratic"), 0.032);
// Point light 4
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[3].ambient"), pointLightColors[3].x * 0.1,  pointLightColors[3].y * 0.1,  pointLightColors[3].z * 0.1);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[3].diffuse"), pointLightColors[3].x,  pointLightColors[3].y,  pointLightColors[3].z);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[3].specular"), pointLightColors[3].x,  pointLightColors[3].y,  pointLightColors[3].z);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[3].constant"), 1.0f);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[3].linear"), 0.09);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[3].quadratic"), 0.032);
// SpotLight
glUniform3f(glGetUniformLocation(lightingShaderID, "spotLight.position"), Camera->Position[0], Camera->Position[1], Camera->Position[2]);
glUniform3f(glGetUniformLocation(lightingShaderID, "spotLight.direction"), Camera->Front[0], Camera->Front[1], Camera->Front[2]);
glUniform3f(glGetUniformLocation(lightingShaderID, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
glUniform3f(glGetUniformLocation(lightingShaderID, "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
glUniform3f(glGetUniformLocation(lightingShaderID, "spotLight.specular"), 1.0f, 1.0f, 1.0f);
glUniform1f(glGetUniformLocation(lightingShaderID, "spotLight.constant"), 1.0f);
glUniform1f(glGetUniformLocation(lightingShaderID, "spotLight.linear"), 0.009);
glUniform1f(glGetUniformLocation(lightingShaderID, "spotLight.quadratic"), 0.0032);
glUniform1f(glGetUniformLocation(lightingShaderID, "spotLight.cutOff"), cos(glm_rad(10.0f)));
glUniform1f(glGetUniformLocation(lightingShaderID, "spotLight.outerCutOff"), cos(glm_rad(12.5f)));
// == ==============================================================================================
//       HORROR
// == ==============================================================================================
glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
[...]
vec3 pointLightColors[] = {
    {0.1f, 0.1f, 0.1f},
    {0.1f, 0.1f, 0.1f},
    {0.1f, 0.1f, 0.1f},
    {0.3f, 0.1f, 0.1f}
};
[...]
// Directional light
glUniform3f(glGetUniformLocation(lightingShaderID, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
glUniform3f(glGetUniformLocation(lightingShaderID, "dirLight.ambient"), 0.0f, 0.0f, 0.0f);
glUniform3f(glGetUniformLocation(lightingShaderID, "dirLight.diffuse"), 0.05f, 0.05f, 0.05);
glUniform3f(glGetUniformLocation(lightingShaderID, "dirLight.specular"), 0.2f, 0.2f, 0.2f);
// Point light 1
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[0].ambient"), pointLightColors[0].x * 0.1,  pointLightColors[0].y * 0.1,  pointLightColors[0].z * 0.1);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[0].diffuse"), pointLightColors[0].x,  pointLightColors[0].y,  pointLightColors[0].z);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[0].specular"), pointLightColors[0].x,  pointLightColors[0].y,  pointLightColors[0].z);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[0].constant"), 1.0f);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[0].linear"), 0.14);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[0].quadratic"), 0.07);
// Point light 2
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[1].ambient"), pointLightColors[1].x * 0.1,  pointLightColors[1].y * 0.1,  pointLightColors[1].z * 0.1);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[1].diffuse"), pointLightColors[1].x,  pointLightColors[1].y,  pointLightColors[1].z);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[1].specular"), pointLightColors[1].x,  pointLightColors[1].y,  pointLightColors[1].z);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[1].constant"), 1.0f);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[1].linear"), 0.14);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[1].quadratic"), 0.07);
// Point light 3
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[2].ambient"), pointLightColors[2].x * 0.1,  pointLightColors[2].y * 0.1,  pointLightColors[2].z * 0.1);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[2].diffuse"), pointLightColors[2].x,  pointLightColors[2].y,  pointLightColors[2].z);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[2].specular") ,pointLightColors[2].x,  pointLightColors[2].y,  pointLightColors[2].z);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[2].constant"), 1.0f);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[2].linear"), 0.22);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[2].quadratic"), 0.20);
// Point light 4
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[3].ambient"), pointLightColors[3].x * 0.1,  pointLightColors[3].y * 0.1,  pointLightColors[3].z * 0.1);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[3].diffuse"), pointLightColors[3].x,  pointLightColors[3].y,  pointLightColors[3].z);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[3].specular"), pointLightColors[3].x,  pointLightColors[3].y,  pointLightColors[3].z);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[3].constant"), 1.0f);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[3].linear"), 0.14);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[3].quadratic"), 0.07);
// SpotLight
glUniform3f(glGetUniformLocation(lightingShaderID, "spotLight.position"), Camera->Position[0], Camera->Position[1], Camera->Position[2]);
glUniform3f(glGetUniformLocation(lightingShaderID, "spotLight.direction"), Camera->Front[0], Camera->Front[1], Camera->Front[2]);
glUniform3f(glGetUniformLocation(lightingShaderID, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
glUniform3f(glGetUniformLocation(lightingShaderID, "spotLight.diffuse"), 1.0f, 1.0f, 1.0f);
glUniform3f(glGetUniformLocation(lightingShaderID, "spotLight.specular"), 1.0f, 1.0f, 1.0f);
glUniform1f(glGetUniformLocation(lightingShaderID, "spotLight.constant"), 1.0f);
glUniform1f(glGetUniformLocation(lightingShaderID, "spotLight.linear"), 0.09);
glUniform1f(glGetUniformLocation(lightingShaderID, "spotLight.quadratic"), 0.032);
glUniform1f(glGetUniformLocation(lightingShaderID, "spotLight.cutOff"), cos(glm_rad(10.0f)));
glUniform1f(glGetUniformLocation(lightingShaderID, "spotLight.outerCutOff"), cos(glm_rad(15.0f)));
// == ==============================================================================================
//       BIOCHEMICAL LAB
// == ==============================================================================================
glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
[...]
vec3 pointLightColors[] = {
    {0.4f, 0.7f, 0.1f},
    {0.4f, 0.7f, 0.1f},
    {0.4f, 0.7f, 0.1f},
    {0.4f, 0.7f, 0.1f}
};
[...]
// Directional light
glUniform3f(glGetUniformLocation(lightingShaderID, "dirLight.direction"), -0.2f, -1.0f, -0.3f);
glUniform3f(glGetUniformLocation(lightingShaderID, "dirLight.ambient"), 0.5f, 0.5f, 0.5f);
glUniform3f(glGetUniformLocation(lightingShaderID, "dirLight.diffuse"), 1.0f, 1.0f, 1.0f);
glUniform3f(glGetUniformLocation(lightingShaderID, "dirLight.specular"), 1.0f, 1.0f, 1.0f);
// Point light 1
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[0].position"), pointLightPositions[0].x, pointLightPositions[0].y, pointLightPositions[0].z);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[0].ambient"), pointLightColors[0].x * 0.1,  pointLightColors[0].y * 0.1,  pointLightColors[0].z * 0.1);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[0].diffuse"), pointLightColors[0].x,  pointLightColors[0].y,  pointLightColors[0].z);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[0].specular"), pointLightColors[0].x,  pointLightColors[0].y,  pointLightColors[0].z);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[0].constant"), 1.0f);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[0].linear"), 0.07);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[0].quadratic"), 0.017);
// Point light 2
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[1].position"), pointLightPositions[1].x, pointLightPositions[1].y, pointLightPositions[1].z);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[1].ambient"), pointLightColors[1].x * 0.1,  pointLightColors[1].y * 0.1,  pointLightColors[1].z * 0.1);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[1].diffuse"), pointLightColors[1].x,  pointLightColors[1].y,  pointLightColors[1].z);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[1].specular"), pointLightColors[1].x,  pointLightColors[1].y,  pointLightColors[1].z);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[1].constant"), 1.0f);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[1].linear"), 0.07);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[1].quadratic"), 0.017);
// Point light 3
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[2].position"), pointLightPositions[2].x, pointLightPositions[2].y, pointLightPositions[2].z);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[2].ambient"), pointLightColors[2].x * 0.1,  pointLightColors[2].y * 0.1,  pointLightColors[2].z * 0.1);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[2].diffuse"), pointLightColors[2].x,  pointLightColors[2].y,  pointLightColors[2].z);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[2].specular") ,pointLightColors[2].x,  pointLightColors[2].y,  pointLightColors[2].z);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[2].constant"), 1.0f);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[2].linear"), 0.07);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[2].quadratic"), 0.017);
// Point light 4
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[3].position"), pointLightPositions[3].x, pointLightPositions[3].y, pointLightPositions[3].z);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[3].ambient"), pointLightColors[3].x * 0.1,  pointLightColors[3].y * 0.1,  pointLightColors[3].z * 0.1);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[3].diffuse"), pointLightColors[3].x,  pointLightColors[3].y,  pointLightColors[3].z);
glUniform3f(glGetUniformLocation(lightingShaderID, "pointLights[3].specular"), pointLightColors[3].x,  pointLightColors[3].y,  pointLightColors[3].z);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[3].constant"), 1.0f);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[3].linear"), 0.07);
glUniform1f(glGetUniformLocation(lightingShaderID, "pointLights[3].quadratic"), 0.017);
// SpotLight
glUniform3f(glGetUniformLocation(lightingShaderID, "spotLight.position"), Camera->Position[0], Camera->Position[1], Camera->Position[2]);
glUniform3f(glGetUniformLocation(lightingShaderID, "spotLight.direction"), Camera->Front[0], Camera->Front[1], Camera->Front[2]);
glUniform3f(glGetUniformLocation(lightingShaderID, "spotLight.ambient"), 0.0f, 0.0f, 0.0f);
glUniform3f(glGetUniformLocation(lightingShaderID, "spotLight.diffuse"), 0.0f, 1.0f, 0.0f);
glUniform3f(glGetUniformLocation(lightingShaderID, "spotLight.specular"), 0.0f, 1.0f, 0.0f);
glUniform1f(glGetUniformLocation(lightingShaderID, "spotLight.constant"), 1.0f);
glUniform1f(glGetUniformLocation(lightingShaderID, "spotLight.linear"), 0.07);
glUniform1f(glGetUniformLocation(lightingShaderID, "spotLight.quadratic"), 0.017);
glUniform1f(glGetUniformLocation(lightingShaderID, "spotLight.cutOff"), cos(glm_rad(7.0f)));
glUniform1f(glGetUniformLocation(lightingShaderID, "spotLight.outerCutOff"), cos(glm_rad(10.0f)));
