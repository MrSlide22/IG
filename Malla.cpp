#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Malla.h"
#include <iostream>

Malla::Malla() {
}

void Malla::dibuja(){
	if (this->rotateAngleX != 0 || this->rotateAngleY != 0 || this->rotateAngleZ != 0){
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glRotatef(this->rotateAngleX, 1, 0, 0);
		glRotatef(this->rotateAngleY, 0, 1, 0);
		glRotatef(this->rotateAngleZ, 0, 0, 1);
	}
	 for (int i = 0; i<numCaras; i++) {
		 glLineWidth(1.0);
		 glColor3f(cara[i]->getRed(), cara[i]->getGreen(), cara[i]->getBlue());
		 if (this->displayModel == 1){
			 glBegin(GL_POLYGON);
		 }
		 else if(this->displayModel == 0){
			 glBegin(GL_LINE_LOOP);
		 }
		 for (int j = 0; j < cara[i]->getNumeroVertices(); j++) {
			 int iN = cara[i]->getIndiceNormal(j);
			 int iV = cara[i]->getIndiceVertice(j);
			 PV3D* vN = calculoVectorNormalPorNewell(*cara[i]);
			 glNormal3f(vN->getX(), vN->getY(), vN->getZ());
			 //Si hubiera coordenadas de textura, aquí se suministrarían
			 //las coordenadas de textura del vértice j con glTexCoor2f(…);
			 glVertex3f(vertice[iV]->getX(), vertice[iV]->getY(), vertice[iV]->getZ());
		 }
		 glEnd();
	 }
	 if (this->rotateAngleX != 0 || this->rotateAngleY != 0 || this->rotateAngleZ != 0){
		 glPopMatrix();
	 }
 }

PV3D* Malla::calculoVectorNormalPorNewell(Cara C){
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

void Malla::setDisplayModel(int model){
	this->displayModel = model;
}

float Malla::getRotateAngleX(){
	return this->rotateAngleX;
}

void Malla::setRotateAngleX(float angle){
	this->rotateAngleX = angle;
}
float Malla::getRotateAngleY(){
	return this->rotateAngleY;
}

void Malla::setRotateAngleY(float angle){
	this->rotateAngleY = angle;
}
float Malla::getRotateAngleZ(){
	return this->rotateAngleZ;
}

void Malla::setRotateAngleZ(float angle){
	this->rotateAngleZ = angle;
}