#include "VerticeNormal.h"

class Cara {

private:
	int numVertices;
	VerticeNormal** arrayVN;

public:
	int getNumeroVertices();
	int getIndiceNormalK(int j);
	int getIndiceVerticeK(int j);
};