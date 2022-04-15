
#include "Main.h"

GLFWwindow* InitWindow()
{
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        getchar();
        return nullptr;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Open a window and create its OpenGL context
    GLFWwindow* window = glfwCreateWindow(width, height, "TexterRenderer", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        getchar();
        glfwTerminate();
        return nullptr;

    }
    glfwMakeContextCurrent(window);

    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return nullptr;
    }

    std::cout << "Using GL Version: " << glGetString(GL_VERSION) << std::endl;

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    return window;
}







int main( void )
{
    GLFWwindow* window = InitWindow();



    if (!window)
        return -1;

    float positions[] = {

		//vert position on screen       //uv coords
        -QuadStripSize, -QuadStripSize, 0.0f, 0.0f, // 0
		 QuadStripSize, -QuadStripSize, 1.0f, 0.0f, // 1
		 QuadStripSize,  QuadStripSize, 1.0f, 1.0f, // 2
        -QuadStripSize,  QuadStripSize, 0.0f, 1.0f  // 3
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    GLCall( glEnable(GL_BLEND) );
    GLCall( glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA) );

    {
        VertexArray VertexArray;
        VertexBuffer VertexBuffer(positions, 4 * 4 * sizeof(float));
        IndexBuffer IndexBuffer(indices, 6);

        VertexBufferLayout VertexBufferLayout;
		VertexBufferLayout.AddFloat(2);
		VertexBufferLayout.AddFloat(2);

		VertexArray.AddBuffer(VertexBuffer, VertexBufferLayout);
	
		ShaderBase shader("res/shaders/MainShader.shader");
        shader.SelectForRendering();


		TextureHelpers Tex("res/textures/MaskTestImage.png");
		Tex.Bind();
        shader.SetUniform1i("u_Texture", 0);

        Renderer renderer;



		ThreadedTimeUpdate();
		
        do {
            renderer.Clear();
            renderer.Draw(VertexArray, IndexBuffer, shader);


			std::string n = "u_Params";
			shader.SetUniform4f(n, Time, width, height, 1.0);
			//std::cout << Time << std::endl;

			
            // Swap chain here
            glfwSwapBuffers(window);
            glfwPollEvents();
        } // Check if the ESC key was pressed or the window was closed
        while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
                glfwWindowShouldClose(window) == 0 );
    }

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    return 0;
}

