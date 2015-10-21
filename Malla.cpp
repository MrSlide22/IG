#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Malla.h"

Malla::Malla() {
}

void Malla::dibuja(){
	
	 for (int i = 0; i<numCaras; i++) {
		 glLineWidth(1.0);
		 glColor3f(cara[i]->getRed(), cara[i]->getGreen(), cara[i]->getBlue());
		 glBegin(GL_POLYGON); //o glBegin(GL_LINE_LOOP);
		 for (int j = 0; j < cara[i]->getNumeroVertices(); j++) {
			 int iN = cara[i]->getIndiceNormal(j);
			 int iV = cara[i]->getIndiceVertice(j);
			 glNormal3f(normal[iN]->getX(), normal[iN]->getY(), normal[iN]->getZ());
			 //Si hubiera coordenadas de textura, aquí se suministrarían
			 //las coordenadas de textura del vértice j con glTexCoor2f(…);
			 glVertex3f(vertice[iV]->getX(), vertice[iV]->getY(), vertice[iV]->getZ());
		 }
		 glEnd();
	 }
 }

PV3D* Malla::CalculoVectorNormalPorNewell(Cara C){
	PV3D* n = new PV3D(0, 0, 0, 0);
	for (int i = 0; i < C.getNumeroVertices(); i++){
		PV3D* vertActual = vertice[C.getIndiceVertice(i)];
		PV3D* vertSiguiente = vertice[C.getIndiceVertice((i + 1) % C.getNumeroVertices())];
		n->setX(n->getX() + ((vertActual->getY() - vertSiguiente->getY())*(vertActual->getZ() + vertSiguiente->getZ())));
		n->setY(n->getY() + ((vertActual->getZ() - vertSiguiente->getZ())*(vertActual->getX() + vertSiguiente->getX()))); // Z * X
		n->setZ(n->getZ() + ((vertActual->getX() - vertSiguiente->getX())*(vertActual->getY() + vertSiguiente->getY()))); // X * Y
	}
	return n->normaliza();
}