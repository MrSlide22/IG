#pragma once
#include "Ficha.h"
#include <iostream>

Ficha::Ficha(int nQuesitos, float z, float x){

	this->nQuesitos = nQuesitos;
	this->z = z;
	this->x = x;

	this->n = 6; //numero de caras que forman la revolucion (360/nQuesitos => uno por grado que tenga la revolucion)
	float colores[6][3] = { { 0, 0, 1 },
							{ 0, 1, 0 },
							{ 0, 1, 1 },
							{ 1, 0, 0 },
							{ 1, 0, 1 },
							{ 1, 1, 0 } };

	int m = 2; //numero de vertices que componen el perfil de la parte curva del quesito

	this->numVertices = (n*m + m)*nQuesitos + 2; //primero ponemos solo los vertices que componen la revolucion (luego añadimos más)
	this->numCaras = (n*(m - 1) + 3)*nQuesitos; //las caras de la revolucion mas 3 del quesito
	this->numeroNormales = numCaras;
	this->vertice = new PV3D*[numVertices]; //El tamano sera el numero de vertices de la revolucion mas los dos vertices del centro del quesito
	this->normal = new PV3D*[numeroNormales];
	this->cara = new Cara*[numCaras];

	//Creamos todos los vertices de la revolucion de la ficha
	for (int i = 0; i < nQuesitos; i++){
		this->verticesRevolucion(m, i);
	}

	//Creamos los vertices del centro
	this->vertice[numVertices - 2] = new PV3D(0, 0, 0, 1); // vertice del centro del quesito (abajo)
	this->vertice[numVertices - 1] = new PV3D(0, this->x, 0, 1); // vertice del centro del quesito (arriba)

	for (int i = 0; i < nQuesitos; i++){
		this->carasQuesitos(i, m, colores[i%this->nQuesitos]);
	}
}

void Ficha::carasQuesitos(int indiceQuesito, int m, float color[3]){

	int indiceCara = (this->n*(m-1)+3)*indiceQuesito;
	int verticeInicial = (this->n*m + m)*indiceQuesito;
	VerticeNormal** vn[3];

	//Definimos los vertices que compondran las caras laterales y la tapa
	//Cara lateral 1 (derecha)
	vn[0] = new VerticeNormal*[4];
	vn[0][0] = new VerticeNormal(this->n*m + m - 1 + verticeInicial, indiceCara);
	vn[0][1] = new VerticeNormal(this->n*m + m - 2 + verticeInicial, indiceCara);
	vn[0][2] = new VerticeNormal(this->numVertices - 2, indiceCara); //vertice del centro-abajo
	vn[0][3] = new VerticeNormal(this->numVertices - 1, indiceCara); //vertice del centro-arriba
	this->cara[indiceCara] = new Cara(vn[0], 4, color[0], color[1], color[2]);

	PV3D* v1 = calculoVectorNormalPorNewell(*cara[indiceCara]);
	this->normal[indiceCara] = v1;

	//Cara lateral 2 (izquierda)
	vn[1] = new VerticeNormal*[4];
	vn[1][0] = new VerticeNormal(this->numVertices - 1, indiceCara + 1); // vertice del centro-arriba
	vn[1][1] = new VerticeNormal(this->numVertices - 2, indiceCara + 1); // vertice del centro-abajo
	vn[1][2] = new VerticeNormal(verticeInicial, indiceCara + 1);
	vn[1][3] = new VerticeNormal(verticeInicial + 1, indiceCara + 1);
	this->cara[indiceCara + 1] = new Cara(vn[1], 4, color[0], color[1], color[2]);

	PV3D* v2 = calculoVectorNormalPorNewell(*cara[indiceCara + 1]);
	this->normal[indiceCara + 1] = v2;

	//Tapa (arriba)
	vn[2] = new VerticeNormal*[this->n + 2];
	for (int i = 0; i <= this->n; i++){ //empezamos por lo vertices de la tapa que forman parte de la parte curva
		vn[2][i] = new VerticeNormal(i*m + 1 + verticeInicial, indiceCara + 2); //i*m+1 para coger solo los de arriba de la parte curva
	}
	vn[2][this->n + 1] = new VerticeNormal(this->numVertices - 1, indiceCara + 2); //anadimos el vertice del centro (arriba)
	this->cara[indiceCara + 2] = new Cara(vn[2], this->n + 2, color[0], color[1], color[2]);

	PV3D* v3 = calculoVectorNormalPorNewell(*cara[indiceCara + 2]);
	this->normal[indiceCara + 2] = v3;

	indiceCara += 3;
	//Construcción de las caras de la revolucion
	for (int i = 0; i < this->n; i++){
		for (int j = 0; j < m - 1; j++) { //esquina inferior-izquierda de una cara
			//indiceCara = i*(m-1) + j;
			int indice = i*m + j + verticeInicial;
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

void Ficha::verticesRevolucion(int m, int indiceQuesito){
	PV3D** perfil = new PV3D*[m];
	int verticeInicial = (this->n*m+m)*indiceQuesito;

	//Calculamos donde debe empezar el perfil en funcion de indiceQuesito (la posicion que ocupa el quesito en el circulo de trivial
	double theta = (indiceQuesito * 360 / nQuesitos) * atan(1) * 4 / 180; //atan(1) * 4 = PI || 6 es el numero de quesitos que queremos en la ficha
	double c = cos(theta);
	double s = sin(theta);
	double x = s*this->z;
	double z = c*this->z;

	//Definimos los vertices del perfil de la cara curva
	perfil[0] = new PV3D(x, 0, z, 1);
	perfil[1] = new PV3D(x, this->x, z, 1);

	//Metemos los vertices del perfil en el array de vertices
	for (int j = 0; j < m; j++){
		this->vertice[verticeInicial + j] = perfil[j]->clona();
	}

	//Definimos el resto de vertices de la revolucion
	for (int i = 1; i < this->n + 1; i++){ //nQ+2 para generar el numero de caras de la revolucion mas el ultimo perfil

		double theta = (i * (360 / nQuesitos - 5) / (double)this->n) * atan(1) * 4 / 180; //atan(1) * 4 = PI
		double c = cos(theta);
		double s = sin(theta);

		for (int j = 0; j < m; j++){
			int indice = i*m + j + verticeInicial;
			double x = c*perfil[j]->getX() + s*perfil[j]->getZ();
			double z = -s*perfil[j]->getX() + c*perfil[j]->getZ();
			PV3D* p = new PV3D(x, perfil[j]->getY(), z, 1);
			vertice[indice] = p;
		}
	}
}