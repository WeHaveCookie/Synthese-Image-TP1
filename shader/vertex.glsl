// Version d'OpenGL
#version 120

// fonction appelee pour chaque sommet
void main()
{
  // Affectation de la position du sommet
  gl_Position = ftransform();
}
