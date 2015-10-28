#pragma once
#include <cmath>
#include <iostream>
#include "MontanaRusa.h"

MontanaRusa::MontanaRusa(int nP, int nQ, float radio){
	this->nP = nP;
	this->nQ = nQ;
	this->radio = radio;

	this->numCaras = nP*nQ - nP;
	this->numVertices = nP*nQ - nP;
	this->numeroNormales = numCaras;

	this->cara = new Cara*[this->numCaras];
	this->vertice = new PV3D*[this->numVertices];

	this->construirMontanaRusa();
}

void MontanaRusa::construirMontanaRusa(){


	PV3D** perfil = new PV3D*[this->nP];
	double inc = 2 * atan(1) * 4/ this->nP;

	for (int i = 0; i < nP; i++){
		float x = this->radio*cos(2 * atan(1) * 4 - i*inc) + 3 * cos(0);
		float y = this->radio*sin(2 * atan(1) * 4 - i*inc) + 3 * sin(2 * 0);
		float z = 3 * sin(0);
		perfil[i] = new PV3D(x, y, z, 1);
	}

	for (int j = 0; j < nP; j++){
		this->vertice[j] = perfil[j]->clona();
	}

	//Generamos los vertices (sin el perfil)
	int t = 1;
	for (int i = 1; i < nQ; i++){

		t = (360 / nQ) * i;
		float theta = t*atan(1) * 4 / 180;

		float c[] = { 3 * cos(theta), 3 * sin(2 * theta), 3 * sin(theta) };

		float cprima[] = { -3 * sin(theta), 6 * cos(2 * theta), 3 * cos(theta) };

		float csegunda[] = { -3 * cos(theta), -12 * sin(2 * theta), -3 * sin(theta) };

		float modulocprima = sqrt(cprima[0] * cprima[0] + cprima[1] * cprima[1] + cprima[2] * cprima[2]);

		float t[] = { cprima[0] / modulocprima, cprima[1] / modulocprima, cprima[2] / modulocprima };

		float b[] = { cprima[1] * csegunda[1] - cprima[2] * csegunda[1], //producto vectorial entre c' y c''
					  cprima[0] * csegunda[2] - cprima[2] * csegunda[0],
					  cprima[0] * csegunda[1] - cprima[1] * csegunda[0] };

		float modulob = sqrt(b[0] * b[0] + b[1] * b[1] + b[2] * b[2]);

		float bnormal[] = { b[0] / modulob, b[1] / modulob, b[2] / modulob };

		float n[] = { bnormal[1] * t[1] - bnormal[2] * t[1], //producto vectorial entre bnormal y t
					  bnormal[0] * t[2] - bnormal[2] * t[0],
					  bnormal[0] * t[1] - bnormal[1] * t[0] };

		float m[4][4] = { { n[0], n[1], n[2], 0 },
						  { bnormal[0], bnormal[1], bnormal[2], 0 },
						  { t[0], t[1], t[2], 0 },
						  { c[0], c[1], c[2], 1 } };

		for (int j = 0; j < nP; j++){
			int indice = (i*nP) + j;

			float pto[] = { this->radio*cos(2 * atan(1) * 4 - j*inc), this->radio*cos(2 * atan(1) * 4 - j*inc), 0, 1 };
			this->vertice[indice] = multiplicarMatrizPorPunto(m, pto);
		}
	}

	int nCaras = 0;
	//Generamos las caras
	for (int i = 0; i < nQ; i++){
		for (int j = 0; j < nP; j++){

			VerticeNormal** vn = new VerticeNormal*[nP];
			vn[0] = new VerticeNormal((i + 1)*nP + j, i*j);

			if (((i + 1)*nP + j) / nP != ((i + 1)*nP + j + 1) / nP){
				vn[1] = new VerticeNormal((i + 1)*nP + j + 1 - 4, i*j);
				vn[2] = new VerticeNormal(i*nP + j + 1 - 4, i*j);
			}
			else{
				vn[1] = new VerticeNormal((i + 1)*nP + j + 1, i*j);
				vn[2] = new VerticeNormal(i*nP + j + 1, i*j);
			}

			vn[3] = new VerticeNormal(i*nP + j, i*j);
			cara[nCaras] = new Cara(vn, 4);
			nCaras++;
		}
	}
}

PV3D* MontanaRusa::multiplicarMatrizPorPunto(float m[4][4], float pto[4]){
	float v[4] = {};
	
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			v[i] += m[i][j] * pto[i];
		}
	}

	return new PV3D(v[0], v[1], v[2], 1);
}
