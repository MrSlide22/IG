#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#pragma once
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
	PV3D* getCentroDeCara(Cara c);
	int displayModel = 1;
	float rotateAngleX = 0;
	float rotateAngleY = 0;
	float rotateAngleZ = 0;
	bool showN = false;

public:
	Malla();
	void dibuja();
	void setDisplayModel(int model);
	void rotate(float x, float y, float z);
	float getRotateAngleX();
	void setRotateAngleX(float angle);
	float getRotateAngleY();
	void setRotateAngleY(float angle);
	float getRotateAngleZ();
	void setRotateAngleZ(float angle);
	void showNormals(bool show);
};