#include "Cubo.h"

Cubo::Cubo(){

	numVertices = 8;
	vertice = new PV3D*[8];
	vertice[0] = new PV3D(0.0f, 0.0f, 0.0f, 1);
	vertice[1] = new PV3D(0.0f, 0.0f, 10.0f, 1);
	vertice[2] = new PV3D(10.0f, 0.0f, 10.0f, 1);
	vertice[3] = new PV3D(10.0f, 0.0f, 0.0f, 1);
	vertice[4] = new PV3D(0.0f, 10.0f, 10.0f, 1);
	vertice[5] = new PV3D(0.0f, 10.0f, 0.0f, 1);
	vertice[6] = new PV3D(10.0f, 10.0f, 10.0f, 1);
	vertice[7] = new PV3D(10.0f, 10.0f, 0.0f, 1);

	numeroNormales = 6;
	normal = new PV3D*[6];
	normal[0] = new PV3D(0, 0, 1, 0);
	normal[1] = new PV3D(1, 0, 0, 0);
	normal[2] = new PV3D(0, 1, 0, 0);
	normal[3] = new PV3D(0, 0, -1, 0);
	normal[4] = new PV3D(-1, 0, 0, 0);
	normal[5] = new PV3D(0, -1, 0, 0);

	VerticeNormal** aVN[6];
	numCaras = 6;
	cara = new Cara*[4];
	//Cara 0
	aVN[0] = new VerticeNormal*[4];
	aVN[0][0] = new VerticeNormal(3, 1);
	aVN[0][1] = new VerticeNormal(2, 1);
	aVN[0][2] = new VerticeNormal(6, 1);
	aVN[0][3] = new VerticeNormal(7, 1);
	cara[0] = new Cara(aVN[0], 4, 0, 1, 0);

	//Cara 1
	aVN[1] = new VerticeNormal*[4];
	aVN[1][0] = new VerticeNormal(0, 5);
	aVN[1][1] = new VerticeNormal(5, 5);
	aVN[1][2] = new VerticeNormal(2, 5);
	aVN[1][3] = new VerticeNormal(3, 5);
	cara[1] = new Cara(aVN[1], 4, 0, 1, 0);

	//Cara 2
	aVN[2] = new VerticeNormal*[4];
	aVN[2][0] = new VerticeNormal(0, 4);
	aVN[2][1] = new VerticeNormal(1, 4);
	aVN[2][2] = new VerticeNormal(4, 4);
	aVN[2][3] = new VerticeNormal(5, 4);
	cara[2] = new Cara(aVN[2], 4, 0, 0, 1);

	//Cara 3
	aVN[3] = new VerticeNormal*[4];
	aVN[3][0] = new VerticeNormal(1, 2);
	aVN[3][1] = new VerticeNormal(2, 2);
	aVN[3][2] = new VerticeNormal(6, 2);
	aVN[3][3] = new VerticeNormal(4, 2);
	cara[3] = new Cara(aVN[3], 4, 1, 0, 0);

	//Cara 4
	aVN[4] = new VerticeNormal*[4];
	aVN[4][0] = new VerticeNormal(0, 3);
	aVN[4][1] = new VerticeNormal(1, 3);
	aVN[4][2] = new VerticeNormal(2, 3);
	aVN[4][3] = new VerticeNormal(3, 3);
	cara[4] = new Cara(aVN[4], 4, 0, 1, 0);

	//Cara 5
	aVN[5] = new VerticeNormal*[4];
	aVN[5][0] = new VerticeNormal(5, 0);
	aVN[5][1] = new VerticeNormal(4, 0);
	aVN[5][2] = new VerticeNormal(6, 0);
	aVN[5][3] = new VerticeNormal(7, 0);
	cara[5] = new Cara(aVN[5], 4, 0, 0, 1);
}