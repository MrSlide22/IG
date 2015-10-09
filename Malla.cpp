#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Malla.h"

void Malla::dibuja(){
	 for (int i = 0; i<numeroCaras; i++) {
		 glLineWidth(1.0);
		 glBegin(GL_POLYGON); //o glBegin(GL_LINE_LOOP);
		 for (int j = 0; j < cara[i]->getNumeroVertices(); j++) {
			 int iN = cara[i]->getIndiceNormalK(j);
			 int iV = cara[i]->getIndiceVerticeK(j);
			 glNormal3f(normal[iN]->getX(), normal[iN]->getY(), normal[iN]->getZ());
			 //Si hubiera coordenadas de textura, aquí se suministrarían
			 //las coordenadas de textura del vértice j con glTexCoor2f(…);
			 glVertex3f(vertice[iV]->getX(), vertice[iV]->getY(), vertice[iV]->getZ());
		 }
		 glEnd();
	 }
 }