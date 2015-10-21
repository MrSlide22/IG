#include "Cara.h"

Cara::Cara(VerticeNormal** aVN, int numV, float red, float green, float blue) {
	arrayVN = aVN;
	numVertices = numV;
	color[0] = red;
	color[1] = green;
	color[2] = blue;
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

int Cara::getRed(){
	return color[0];
}

int Cara::getGreen(){
	return color[1];
}

int Cara::getBlue(){
	return color[2];
}