#include <iostream>
#include <shader.hpp> // Help to load shaders from files
// Include GLEW : Always include it before glfw.h et gl.h :)
#include <GL/glew.h> // OpenGL Extension Wrangler Library : http://glew.sourceforge.net/
#include <GL/glfw.h> // Window, keyboard, mouse : http://www.glfw.org/
#include <glm/glm.hpp> // OpenGL Mathematics : www.http://glm.g-truc.net/0.9.5/index.html

using namespace glm;
using namespace std;

int main()
{

    cout << "Debut du programme..." << endl;

    // Initialisation de GLFW
	if( !glfwInit() )
	{
		cout << "Echec de l'initialisation de GLFW" << endl;
		exit(EXIT_FAILURE);
	}



  glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4); // Anti Aliasing
  glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 2); // OpenGL 2.1
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 1);

    // Ouverture d'une fenêtre en 1024x768
    // et creation d'un contexte OpenGL
	if( !glfwOpenWindow( 1024, 768, 0,0,0,0, 32,0, GLFW_WINDOW ) )
	{
		cout << "Echec de l'ouverture de fenetre OpenGL" << endl;
		glfwTerminate();
		exit(EXIT_FAILURE);
    }

    // Definition du titre de la fenêtre
	glfwSetWindowTitle( "Polytech RICM 4 - TP1" );

    // Autorise GLFW a recevoir les appuis de touche
	glfwEnable( GLFW_STICKY_KEYS );

    // Initialisation de  GLEW
	if (glewInit() != GLEW_OK) {
		cout << "Echec de l'initialisation de GLEW" << endl;
		exit(EXIT_FAILURE);
	}

    // Verification des donnees du contexte OpenGL
    const GLubyte* renderer = glGetString (GL_RENDERER);
    cout << "Carte Graphique : " << renderer << endl;

    const GLubyte* version = glGetString (GL_VERSION);
    cout << "Driver OpenGL : " << version << endl;



    //==================================================
    // ToDo : Initialiser
    //==================================================
    GLuint programID = LoadShaders("../shader/vertex2.glsl", "../shader/fragment.glsl");

    glEnable(GL_VERTEX_PROGRAM_POINT_SIZE);

    cout << "Initialisations..." << endl;

    // Definition de la couleur du fond
    glClearColor(20.0, 60.0, 75.3, 0.0);

    // Definition d'un vecteur
    vec3 v(-1.0f, -1.0f, 0.0f);

    // Definition d'un tableau de vecteurs
    //vec3 vertex[3] = {vec3(-0.7,-0.5,0.0),vec3(0.7,-0.5,0.0),vec3(-0.7,0.5,0.0)}; // Version Triangle
    vec3 vertex[4] = {vec3(-0.5,-0.5,0.0),vec3(-0.5,0.5,0.0),vec3(0.5,0.5,0.0),vec3(0.5,-0.5,0.0)}; // Version carré
    GLuint vertexPositionID = glGetAttribLocation(programID, "vertex_position");

    // Creation d'un VBO et recuperation de son ID
    GLuint vboID;
    glGenBuffers(1,&vboID);

    // Definition de notre VBO comme le buffer courant
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    // Copie de donnees vers le VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex), vertex, GL_STATIC_DRAW);

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);



    cout << "Debut de la boucle principale..." << endl;
    unsigned int i = 0;
    // Boucle de dessin
	do{
    glUseProgram(programID);
        // Nettoyage de la zone de dessin
		glClear( GL_COLOR_BUFFER_BIT );

        //==================================================
        // ToDo : Dessiner
        //==================================================

    // On active l'attribut vertexPositionID
    glEnableVertexAttribArray(vertexPositionID);

    // On definit notre VBO comme le VBO courant
    glBindBuffer(GL_ARRAY_BUFFER, vboID);

    // On lui indique comment lire les donnees
    glVertexAttribPointer(vertexPositionID, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    // On dit a OpenGL de dessiner le contenu du buffer courant
    //glDrawArrays(GL_TRIANGLES,0,3); // Version Triangle
    glDrawArrays(GL_QUADS,0,4); // Version Carre

    // On desactive l'attribut vertexPositionID
    glDisableVertexAttribArray(vertexPositionID);

    /* EXO 1
    glBegin(GL_TRIANGLES);
    glVertex3f(-0.5,-0.5,0.0);
    glVertex3f(0.5,-0.5,0.0);
    glVertex3f(0.0,0.5,0.0);
    glEnd();
    */



		// Echange des zones de dessin buffers
		glfwSwapBuffers();

        cout << "Compteur : " << i++ << "\r";
        cout.flush();

    } // Execution de la boucle...
    while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&  // ... jusqu'a appui sur la touche ESC
           glfwGetWindowParam( GLFW_OPENED )        );  // ... ou fermeture de la fenetre

    // On libere le buffer
    glDeleteBuffers(1, &vboID);

    cout << endl;

    // Ferme GLFW et OpenGL
	glfwTerminate();



    //==================================================
    // ToDo : Nettoyer la memoire
    //==================================================




    cout << "Fin du programme..." << endl;

	return EXIT_SUCCESS;
}
