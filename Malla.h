#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include "PV3D.h"
#include "Cara.h"

class Malla {

protected:
	int numVertices;
	PV3D** vertice;
	int numeroNormales;
	PV3D** normal;
	int numCaras;
	Cara** cara;
	PV3D* calculoVectorNormalPorNewell(Cara C);

public:
	Malla();
	void dibuja();
};