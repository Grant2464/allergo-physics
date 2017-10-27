GLuint pid;


//Display settings
al_set_new_display_flags(ALLEGRO_OPENGL);
al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST); // Whether to use multisampling (1) or not (0).
al_set_new_display_option(ALLEGRO_SAMPLES, 4, ALLEGRO_SUGGEST); // If the above is 1, the number of samples to use per pixel. Else 0.

//Allegro init stuff
ALLEGRO_DISPLAY *d;
assert(!al_init());
d = al_create_display(WINDOW_W, WINDOW_H);
assert(!d);

// al_get_display_option(d, ALLEGRO_SAMPLE_BUFFERS); //NOT NEEDED?

//al_get_opengl_extension_list(): Returns the list of OpenGL extensions supported by Allegro, for the given display.
//The extension will be set to true if available for the given display and false otherwise
if (al_get_opengl_extension_list()->ALLEGRO_GL_ARB_multisample) {  //Checking Multisampling stuff
		glEnable(GL_MULTISAMPLE_ARB); //Multisampling enabling stuff
}

if (!al_get_opengl_extension_list()->ALLEGRO_GL_ARB_vertex_program) { //Checking Multisampling stuff
		assert(1);
}

//OpenGl Init Stuff
glEnable(GL_DEPTH_TEST); //Helps give depth
glShadeModel(GL_SMOOTH); //Sets shading to smooth
glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); //Indicates the quality of color and texture coordinate interpolation
glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //Lines not fill
glDisable(GL_CULL_FACE); //Don't show back part?

//  Setup projection and modelview matrices
glMatrixMode(GL_PROJECTION);
glLoadIdentity();  //Standard init stuff
gluPerspective(45.0, WINDOW_W/(float)WINDOW_H, 0.1, 100.0); //Standard init stuff

glMatrixMode(GL_MODELVIEW);
glLoadIdentity();

//  Position the camera to look at our mesh from a distance
gluLookAt(0.0f, 20.0f, -45.0f, 0.0f, 0.0f, 0.0f, 0, 1, 0);

create_mesh();

//  Define the vertex program
glEnable(GL_VERTEX_PROGRAM_ARB);
glGenProgramsARB(1, &pid);
glBindProgramARB(GL_VERTEX_PROGRAM_ARB, pid);
glGetError();

if (al_get_opengl_extension_list()->ALLEGRO_GL_NV_vertex_program2_option) {
		glProgramStringARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_FORMAT_ASCII_ARB,
		                   strlen(program_nv), program_nv);
}
else {
		glProgramStringARB(GL_VERTEX_PROGRAM_ARB, GL_PROGRAM_FORMAT_ASCII_ARB,
		                   strlen(program), program);
}

//  Check for errors
if (glGetError()) {
		const char *pgm = al_get_opengl_extension_list()->ALLEGRO_GL_NV_vertex_program2_option
		                  ? program_nv : program;
		GLint error_pos;
		const GLubyte *error_str = glGetString(GL_PROGRAM_ERROR_STRING_ARB);
		glGetIntegerv(GL_PROGRAM_ERROR_POSITION_ARB, &error_pos);

		assert(1);

}
