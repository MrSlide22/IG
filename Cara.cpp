#include "Cara.h"

int Cara::getNumeroVertices() {
	return numVertices;
}
int Cara::getIndiceNormalK(int j) {
	return arrayVN[j]->getIndNorm();
}
int Cara::getIndiceVerticeK(int j) {
	return arrayVN[j]->getIndVert();
}