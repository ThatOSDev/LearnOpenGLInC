int main()
{
    [...]
    // render loop
    while(!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        float currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        processInput(window);

        // clear the colorbuffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // change the light's position values over time (can be done anywhere in the render loop actually, but try to do it at least before using the light source positions)
        lightPos[0] = 1.0f + sin((float)glfwGetTime()) * 2.0f;
        lightPos[1] = sin((float)glfwGetTime() / 2.0f) * 1.0f;

        // set uniforms, draw objects
        [...]

        // glfw: swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
