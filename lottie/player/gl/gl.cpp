// Shader sources
const GLchar* vertexSource =
    "attribute vec4 position;    \n"
    "void main()                  \n"
    "{                            \n"
    "   gl_Position = vec4(position.xyz, 1.0);  \n"
    "}                            \n";
const GLchar* fragmentSource =
    "precision mediump float;\n"
    "void main()                                  \n"
    "{                                            \n"
    "  gl_FragColor = vec4 (1.0, 1.0, 1.0, 1.0 );\n"
    "}                                            \n";


void glInitShaders(int refIndex) {
	GLuint tempShaderProgram;
    // Create and compile the vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexSource, NULL);
    glCompileShader(vertexShader);

    // Create and compile the fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
    glCompileShader(fragmentShader);

    // Link the vertex and fragment shader into a shader program
    tempShaderProgram = glCreateProgram();
    glAttachShader(tempShaderProgram, vertexShader);
    glAttachShader(tempShaderProgram, fragmentShader);
    // glBindFragDataLocation(shaderProgram, 0, "outColor");
    glLinkProgram(tempShaderProgram);
    glUseProgram(tempShaderProgram);
	if (refIndex == 0) {
		mainShader = tempShaderProgram;
	} else {
		*(shaderProgram + refIndex) = &tempShaderProgram;
	}
}

void glInit() {   
// SDL_Init(SDL_INIT_VIDEO);

    
   wnd = SDL_CreateWindow("test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            theAnimation->w, theAnimation->h, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetSwapInterval(0);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    glc = SDL_GL_CreateContext(wnd);

    rdr = SDL_CreateRenderer(
        wnd, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
}

void glDraw(int shaderIndex, int bufferIndex) {
	loop = [&]
	{
		/*
		SDL_Event e;
		while(SDL_PollEvent(&e))
		{
			if(e.type == SDL_QUIT) std::terminate();
		}
		*/

		// Clear the screen to black
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw a triangle from the 3 vertices
		//glDrawArrays(GL_TRIANGLES, 0, 6);
		if (bufferIndex == 0) {
			int counter = 1;
			
			while (*vao[counter] > 0) {
				if (shaderIndex == 0) {
					glUseProgram(mainShader);
				} else {
					glUseProgram(*shaderProgram[counter]);
				}
				glBindVertexArrayOES(*vao[counter]);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				glBindVertexArrayOES(0);
				counter++;
			}
		} else {
			if (shaderIndex == 0) {
				glUseProgram(mainShader);
			} else {
				glUseProgram(*shaderProgram[shaderIndex]);
			}
			glBindVertexArrayOES(*vao[bufferIndex]);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			glBindVertexArrayOES(0);
		}
		SDL_GL_SwapWindow(wnd);
	};

	#ifdef __EMSCRIPTEN__
		emscripten_set_main_loop(main_loop, 0, true);
	#else
		while(true) main_loop();
	#endif

}

