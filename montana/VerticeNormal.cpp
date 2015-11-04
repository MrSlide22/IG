#include "VerticeNormal.h"

VerticeNormal::VerticeNormal(int indVert, int indNorm){
	indiceVertice = indVert;
	indiceNormal = indNorm;
}

int VerticeNormal::getIndVert() {
	return indiceVertice;
}
int VerticeNormal::getIndNorm() {
	return indiceNormal;
}