#include "VerticeNormal.h"

class Cara {

private:
	int numVertices;
	VerticeNormal** arrayVN;
	float color[3];

public:
	Cara(VerticeNormal** aVN, int numVertices);
	Cara(VerticeNormal** aVN, int numVertices, float red, float green, float blue);
	int getNumeroVertices();
	int getIndiceNormal(int j);
	int getIndiceVertice(int j);
	int getRed();
	int getGreen();
	int getBlue();
};