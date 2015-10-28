#pragma once
#include "Quesito.h"
#include <iostream>;
#include <cmath>


Quesito::Quesito(int nQ, float z, float x, int indiceQuesito, int nQuesitos, float color[]){

	this->nQ = nQ;
	this->z = z;
	this->x = x;

	this->indiceQuesito = indiceQuesito;

	this->color = color;

	int m = 2; //numero de vertices que componen el perfil de la parte curva del quesito

	this->numVertices = nQ*m+m; //primero ponemos solo los vertices que componen la revolucion (luego añadimos más)
	this->numCaras = nQ*(m - 1) + 3; //las caras de la revolucion mas 3 del quesito
	this->numeroNormales = numCaras;
	this->vertice = new PV3D*[numVertices + 2]; //El tamano sera el numero de vertices de la revolucion mas los dos vertices del centro del quesito
	this->normal = new PV3D*[numeroNormales];
	this->cara = new Cara*[numCaras];

	this->construiRevolucion(m, nQuesitos); //Construimos la cara curva

	this->numVertices += 2; //anadimos los dos vertices del centro

	this->vertice[nQ*m + m] = new PV3D(0, 0, 0, 1); //primer vertice del centro del quesito
	this->vertice[nQ*m + m + 1] = new PV3D(0, this->x, 0, 1); //segundo vertice

	VerticeNormal** vn[3];
	
	//Definimos los vertices que compondran las caras laterales y la tapa
	//Cara lateral 1 (derecha)
	vn[0] = new VerticeNormal*[4];
	vn[0][0] = new VerticeNormal(nQ*m + m - 1, nQ*m + 1);
	vn[0][1] = new VerticeNormal(nQ*m + m - 2, nQ*m + 1);
	vn[0][2] = new VerticeNormal(nQ*m + m, nQ*m + 1);
	vn[0][3] = new VerticeNormal(nQ*m + m + 1, nQ*m + 1);
	this->cara[nQ*(m - 1)] = new Cara(vn[0], 4, color[0], color[1], color[2]);

	//Cara lateral 2 (izquierda)
	vn[1] = new VerticeNormal*[4];
	vn[1][0] = new VerticeNormal(nQ*m + m + 1, nQ*m + 2);
	vn[1][1] = new VerticeNormal(nQ*m + m, nQ*m + 2);
	vn[1][2] = new VerticeNormal(0, nQ*m + 2);
	vn[1][3] = new VerticeNormal(1, nQ*m + 2);
	this->cara[nQ*(m - 1) + 1] = new Cara(vn[1], 4, color[0], color[1], color[2]);

	//Tapa (arriba)
	vn[2] = new VerticeNormal*[nQ + 2];
	for (int i = 0; i <= nQ; i++){ //empezamos por lo vertices de la tapa que forman parte de la parte curva
		vn[2][i] = new VerticeNormal(i*m + 1, nQ*m+3); //i*m+1 para coger solo los de arriba de la parte curva
	}
	vn[2][nQ+1] = new VerticeNormal(nQ*m + m + 1, nQ*m + 3); //anadimos el vertice del centro (arriba)
	this->cara[nQ*(m - 1) + 2] = new Cara(vn[2], nQ + 2, color[0], color[1], color[2]);
}

void Quesito::construiRevolucion(int m, int nQuesitos){
	
	PV3D** perfil = new PV3D*[m];

	//Calculamos donde debe empezar el perfil en funcion de indiceQuesito (la posicion que ocupa el quesito en el circulo de trivial
	double theta = (this->indiceQuesito * 360 / nQuesitos) * atan(1) * 4 / 180; //atan(1) * 4 = PI || 6 es el numero de quesitos que queremos en la ficha
	double c = cos(theta);
	double s = sin(theta);
	double x = s*this->z;
	double z = c*this->z;

	//Definimos los vertices del perfil de la cara curva
	perfil[0] = new PV3D(x, 0, z, 1);
	perfil[1] = new PV3D(x, this->x, z, 1);

	//Metemos los vertices del perfil en el array de vertices
	for (int j = 0; j < m; j++){
		this->vertice[j] = perfil[j]->clona();
	}

	//Definimos el resto de vertices de la revolucion
	for (int i = 1;  i < nQ + m; i++){ //nQ+2 para generar el numero de caras de la revolucion mas el ultimo perfil

		double theta = (i * (360 / nQuesitos - 5) / (double)this->nQ) * atan(1) * 4 / 180; //atan(1) * 4 = PI
		double c = cos(theta);
		double s = sin(theta);

		for (int j = 0; j < m; j++){
			int indice = i*m + j;
			double x = c*perfil[j]->getX() + s*perfil[j]->getZ();
			double z = -s*perfil[j]->getX() + c*perfil[j]->getZ();
			PV3D* p = new PV3D(x, perfil[j]->getY(), z, 1);
			vertice[indice] = p;
		}
	}

	//Construcción de las caras
	int indiceCara = 0;
	for (int i = 0; i < nQ; i++){
		for (int j = 0; j < m - 1; j++) { //esquina inferior-izquierda de una cara
			//indiceCara = i*(m-1) + j;
			int indice = i*m + j;
			VerticeNormal** vn = new VerticeNormal*[4];
			vn[0] = new VerticeNormal(indice, indiceCara);
			vn[1] = new VerticeNormal((indice + m), indiceCara);
			vn[2] = new VerticeNormal((indice + 1 + m), indiceCara);
			vn[3] = new VerticeNormal(indice + 1, indiceCara);
			cara[indiceCara] = new Cara(vn, 4, color[0], color[1], color[2]);

			PV3D* v = calculoVectorNormalPorNewell(*cara[indiceCara]); //Newell
			normal[indiceCara] = v;
			indiceCara++;
		} //for
	} //for
}