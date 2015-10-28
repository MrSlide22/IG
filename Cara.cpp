#include "Cara.h"

Cara::Cara(VerticeNormal** aVN, int numV, float red, float green, float blue) {
	arrayVN = aVN;
	numVertices = numV;
	color[0] = red;
	color[1] = green;
	color[2] = blue;
}

Cara::Cara(VerticeNormal** aVN, int numV) {
	arrayVN = aVN;
	numVertices = numV;
	color[0] = 0.1f;
	color[1] = 0.1f;
	color[2] = 1;
}


int Cara::getNumeroVertices() {
	return numVertices;
}
int Cara::getIndiceNormal(int j) {
	return arrayVN[j]->getIndNorm();
}
int Cara::getIndiceVertice(int j) {
	return arrayVN[j]->getIndVert();
}

float Cara::getRed(){
	return color[0];
}

float Cara::getGreen(){
	return color[1];
}

float Cara::getBlue(){
	return color[2];
}