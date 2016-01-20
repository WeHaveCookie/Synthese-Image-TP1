// Version d'OpenGL
#version 120

// Donnees d'entree
attribute vec3 vertex_position;

// fonction appelee pour chaque sommet
void main()
{
  // Affectation de la position du sommet
  gl_Position = vec4(vertex_position, 1.0);

  gl_PointSize=2.0f;

  //gl_Position.x /= 2 // Divise les x par 2
  gl_Position.x += 0.5;
  gl_Position.y -= 0.2;
}
