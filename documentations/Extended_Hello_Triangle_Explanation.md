# Extended Hello Triangle: Detailed Explanation

## 1. Introduction: The Libraries
To start with OpenGL, we need a few helper libraries because OpenGL itself interacts directly with the graphics driver, but it doesn't handle "System" things like creating windows or reading keyboard input.

-   **GLFW (Graphics Library Framework)**:
    -   **Purpose**: It handles the boring OS stuff. It creates a Window, creates an OpenGL Context (a canvas to draw on), and handles user Input (Keyboard, Mouse).
    -   *In our code*: `glfwInit()`, `glfwCreateWindow()`.

-   **GLAD**:
    -   **Purpose**: OpenGL function pointers are complex and vary by graphics card driver. GLAD loads these function pointers for us so we can call functions like `glCompileShader` without crashing.
    -   *In our code*: `gladLoadGLLoader()`.

-   **GLM (OpenGL Mathematics)**:
    -   **Purpose**: OpenGL likes linear algebra (matrices and vectors). GLM is a math library designed to work exactly like GLSL (OpenGL Shading Language). We use it for rotation matrices.
    -   *In our code*: `glm::mat4`, `glm::rotate`, `glm::vec3`.

---

## 2. The Concepts

### A. The Pipeline (Vertex -> Fragment)
Everything you draw goes through a "pipeline". For our Triangle:
1.  **Vertex Shader**: Runs once for every *point* (vertex) of the triangle. Its job is to tell the GPU *where* the point is on the screen (-1.0 to 1.0 coordinates).
2.  **Fragment Shader**: Runs once for every *pixel* inside the triangle. Its job is to tell the GPU *what color* that pixel depends on.

### B. Buffers (VAO & VBO)
Sending data from CPU (your C++ code) to GPU (Graphics Card) is slow, so we send it in batches called **Buffers**.

1.  **VBO (Vertex Buffer Object)**:
    -   Examples: Coordinates `(x, y, z)`.
    -   It acts as the memory storage on the GPU card itself.
2.  **VAO (Vertex Array Object)**:
    -   Imagine the VBO is a raw bag of bytes. The VAO "describes" to OpenGL what those bytes mean.
    -   "Hey OpenGL, the first 3 numbers are position X, Y, Z. The next 3 are something else..."
    -   *In our code*: `glVertexAttribPointer(0, 3, GL_FLOAT...)` tells OpenGL that Attribute 0 is 3 floats long (X, Y, Z).

### C. Shaders & Uniforms
Shaders are small programs written in **GLSL** (OpenGL Shading Language) that run on the GPU.
-   **Compiling**: We pass the source code string to OpenGL, and it compiles it at runtime (`glCompileShader`).
-   **Uniforms**: These are "Global Variables" that we can set from C++ and read inside the Shader.
    -   *In our code*: `uniform vec4 ourColor` is how we pulse the green color. We verify the time in C++, calculate the green value, and send it to the shader every frame.

---

## 3. The Transformations (Math)

To move or rotate things, we don't change the hardcoded vertices. Instead, we use **Matrices**.

### Identity Matrix
An "Identity Matrix" is a matrix that does nothing. It's our starting point.
```cpp
glm::mat4 trans = glm::mat4(1.0f); // Identity
```

### Rotation
We apply a rotation operation to that matrix:
```cpp
trans = glm::rotate(trans, timeValue * speed, axis);
```
-   `trans`: The matrix to modify.
-   `angle`: How much to rotate (in radians).
-   `axis`: Which axis to spin around? Since we are 2D, we spin around the **Z-axis** (the needle sticking out of the screen), so `glm::vec3(0.0f, 0.0f, 1.0f)`.

### Sending to GPU
Shaders do the heavy lifting.
1.  **In C++**: We calculate the matrix `trans`.
2.  **Send**: `glUniformMatrix4fv(...)` sends it to the Uniform defined in the Vertex Shader.
3.  **In Shader**: `gl_Position = transform * vec4(aPos, 1.0);`. The shader multiplies every vertex position by our rotation matrix, causing the triangle to spin.

---

## 4. The Loop
The `while (!glfwWindowShouldClose(window))` loop is the heart of the game/app.
1.  **Input**: Check if keys are pressed.
2.  **Update**: Calculate new animation states (Time, Color, Rotation Matrix).
3.  **Render**: `glDrawArrays` - tell the GPU to execute the drawing using the current state (Matrix, Shaders, VAO).
4.  **Swap Buffers**: OpenGL draws to a hidden "Back Buffer". `glfwSwapBuffers` swaps it to the front so the user sees the new frame instantly (prevents flickering).
