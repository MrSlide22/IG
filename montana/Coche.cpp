#include <math.h>
#include <iostream>
#include "Coche.h"

Coche::Coche(){

	this->height = 1;
	this->width = 2.5;
	this->length = 5;
	this->wheelRadius = 0.4;

	this->construirCoche();
}

Coche::Coche(float height, float width, float length, float wheelRadius){

	this->height = height;
	this->width = width;
	this->length = length;
	this->wheelRadius = 0.4;

	this->construirCoche();
}

void Coche::construirCoche(){

	this->numVertices = 22;
	this->numCaras = 14;
	this->numeroNormales = this->numCaras;

	this->vertice = new PV3D*[this->numVertices];
	this->cara = new Cara*[this->numCaras];
	this->normal = new PV3D*[this->numeroNormales];

	this->vertice[0] = new PV3D(width, 0, length, 1);
	this->vertice[1] = new PV3D(width, 0, 0, 1);
	this->vertice[2] = new PV3D(0, 0, 0, 1);
	this->vertice[3] = new PV3D(0, 0, length, 1);

	this->vertice[4] = new PV3D(width, height, length, 1);
	this->vertice[5] = new PV3D(width, height, 0, 1);
	this->vertice[6] = new PV3D(0, height, 0, 1);
	this->vertice[7] = new PV3D(0, height, length, 1);

	this->vertice[8] = new PV3D(width, height, length/1.5, 1);
	this->vertice[9] = new PV3D(width, height, length / 5, 1);
	this->vertice[10] = new PV3D(0, height, length / 5, 1);
	this->vertice[11] = new PV3D(0, height, length / 1.5, 1);

	this->vertice[12] = new PV3D(width, height * 2, length / 2, 1);
	this->vertice[13] = new PV3D(width, height * 2, length / 4, 1);
	this->vertice[14] = new PV3D(0, height * 2, length / 4, 1);
	this->vertice[15] = new PV3D(0, height * 2, length / 2, 1);

	//Faro delanteros Derecho
	this->vertice[16] = new PV3D(width/4, height, length, 1);
	this->vertice[17] = new PV3D(width / 4, height - height / 4, length, 1);
	this->vertice[18] = new PV3D(0, height - height/4, length, 1);

	this->vertice[19] = new PV3D(width - width / 4, height, length, 1);
	this->vertice[20] = new PV3D(width - width / 4, height - height / 4, length, 1);
	this->vertice[21] = new PV3D(width, height - height / 4, length, 1);
	
	VerticeNormal** vn[14];

	vn[0] = new VerticeNormal*[4];
	vn[0][0] = new VerticeNormal(0, 0);
	vn[0][1] = new VerticeNormal(3, 0);
	vn[0][2] = new VerticeNormal(2, 0);
	vn[0][3] = new VerticeNormal(1, 0);
	this->cara[0] = new Cara(vn[0], 4);
	this->normal[0] = this->calculoVectorNormalPorNewell(*cara[0]);

	vn[1] = new VerticeNormal*[4];
	vn[1][0] = new VerticeNormal(4, 1);
	vn[1][1] = new VerticeNormal(0, 1);
	vn[1][2] = new VerticeNormal(1, 1);
	vn[1][3] = new VerticeNormal(5, 1);
	this->cara[1] = new Cara(vn[1], 4);
	this->normal[1] = this->calculoVectorNormalPorNewell(*cara[1]);

	vn[2] = new VerticeNormal*[4];
	vn[2][0] = new VerticeNormal(5, 2);
	vn[2][1] = new VerticeNormal(1, 2);
	vn[2][2] = new VerticeNormal(2, 2);
	vn[2][3] = new VerticeNormal(6, 2);
	this->cara[2] = new Cara(vn[2], 4);
	this->normal[2] = this->calculoVectorNormalPorNewell(*cara[2]);

	vn[3] = new VerticeNormal*[4];
	vn[3][0] = new VerticeNormal(6, 3);
	vn[3][1] = new VerticeNormal(2, 3);
	vn[3][2] = new VerticeNormal(3, 3);
	vn[3][3] = new VerticeNormal(7, 3);
	this->cara[3] = new Cara(vn[3], 4);
	this->normal[3] = this->calculoVectorNormalPorNewell(*cara[3]);

	vn[4] = new VerticeNormal*[8];
	vn[4][0] = new VerticeNormal(16, 4);
	vn[4][1] = new VerticeNormal(17, 4);
	vn[4][2] = new VerticeNormal(18, 4);
	vn[4][3] = new VerticeNormal(3, 4);
	vn[4][4] = new VerticeNormal(0, 4);
	vn[4][5] = new VerticeNormal(21, 4);
	vn[4][6] = new VerticeNormal(20, 4);
	vn[4][7] = new VerticeNormal(19, 4);
	this->cara[4] = new Cara(vn[4], 8);
	this->normal[4] = this->calculoVectorNormalPorNewell(*cara[4]);

	vn[5] = new VerticeNormal*[4];
	vn[5][0] = new VerticeNormal(7, 5);
	vn[5][1] = new VerticeNormal(4, 5);
	vn[5][2] = new VerticeNormal(8, 5);
	vn[5][3] = new VerticeNormal(11, 5);
	this->cara[5] = new Cara(vn[5], 4);
	this->normal[5] = this->calculoVectorNormalPorNewell(*cara[5]);

	vn[6] = new VerticeNormal*[4];
	vn[6][0] = new VerticeNormal(10, 6);
	vn[6][1] = new VerticeNormal(9, 6);
	vn[6][2] = new VerticeNormal(5, 6);
	vn[6][3] = new VerticeNormal(6, 6);
	this->cara[6] = new Cara(vn[6], 4);
	this->normal[6] = this->calculoVectorNormalPorNewell(*cara[6]);

	vn[7] = new VerticeNormal*[4];
	vn[7][0] = new VerticeNormal(12, 7);
	vn[7][1] = new VerticeNormal(8, 7);
	vn[7][2] = new VerticeNormal(9, 7);
	vn[7][3] = new VerticeNormal(13, 7);
	this->cara[7] = new Cara(vn[7], 4);
	this->normal[7] = this->calculoVectorNormalPorNewell(*cara[7]);

	vn[8] = new VerticeNormal*[4];
	vn[8][0] = new VerticeNormal(13, 8);
	vn[8][1] = new VerticeNormal(9, 8);
	vn[8][2] = new VerticeNormal(10, 8);
	vn[8][3] = new VerticeNormal(14, 8);
	this->cara[8] = new Cara(vn[8], 4);
	this->normal[8] = this->calculoVectorNormalPorNewell(*cara[8]);

	vn[9] = new VerticeNormal*[4];
	vn[9][0] = new VerticeNormal(14, 9);
	vn[9][1] = new VerticeNormal(10, 9);
	vn[9][2] = new VerticeNormal(11, 9);
	vn[9][3] = new VerticeNormal(15, 9);
	this->cara[9] = new Cara(vn[9], 4);
	this->normal[9] = this->calculoVectorNormalPorNewell(*cara[9]);

	vn[10] = new VerticeNormal*[4];
	vn[10][0] = new VerticeNormal(15, 10);
	vn[10][1] = new VerticeNormal(11, 10);
	vn[10][2] = new VerticeNormal(8, 10);
	vn[10][3] = new VerticeNormal(12, 10);
	this->cara[10] = new Cara(vn[10], 4);
	this->normal[10] = this->calculoVectorNormalPorNewell(*cara[10]);

	vn[11] = new VerticeNormal*[4];
	vn[11][0] = new VerticeNormal(15, 11);
	vn[11][1] = new VerticeNormal(12, 11);
	vn[11][2] = new VerticeNormal(13, 11);
	vn[11][3] = new VerticeNormal(14, 11);
	this->cara[11] = new Cara(vn[11], 4);
	this->normal[11] = this->calculoVectorNormalPorNewell(*cara[11]);

	//Faro delantero izquierdo
	vn[12] = new VerticeNormal*[4];
	vn[12][0] = new VerticeNormal(7, 12);
	vn[12][1] = new VerticeNormal(18, 12);
	vn[12][2] = new VerticeNormal(17, 12);
	vn[12][3] = new VerticeNormal(16, 12);
	this->cara[12] = new Cara(vn[12], 4, 1, 1, 0);
	this->normal[12] = this->calculoVectorNormalPorNewell(*cara[12]);

	//Faro delantero derecho
	vn[13] = new VerticeNormal*[4];
	vn[13][0] = new VerticeNormal(19, 13);
	vn[13][1] = new VerticeNormal(20, 13);
	vn[13][2] = new VerticeNormal(21, 13);
	vn[13][3] = new VerticeNormal(4, 13);
	this->cara[13] = new Cara(vn[13], 4, 1, 1, 0);
	this->normal[13] = this->calculoVectorNormalPorNewell(*cara[13]);
}

void Coche::avanza(int d){
	this->distancia += d;
}

void Coche::retrocede(int d){
	this->distancia -= d;
}

PV3D* Coche::getC(double t){
	return new PV3D(3 * cos(t), 3 * sin(2 * t), 3 * sin(t), 1);
}

PV3D* Coche::getCPrima(double t){
	return new PV3D(-3 * sin(t), 6 * cos(2 * t), 3 * cos(t), 0);
}

PV3D* Coche::getCSegunda(double t){
	return new PV3D(-3 * cos(t), -12 * sin(2 * t), -3 * sin(t), 0);
}

PV3D* Coche::multiplicarMatrizPorPunto(GLfloat m[4][4], GLfloat pto[4]){

	GLfloat ret[4] = {};
	for (int i = 0; i < 4; i++){
		for (int j = 0; j < 4; j++){
			ret[i] += m[j][i] * pto[j];
		}
	}

	return new PV3D(ret[0], ret[1], ret[2], ret[3]);
}

void Coche::dibuja(){

	if (this->distancia != 0){

		int alpha = this->distancia;
		double theta = alpha * atan(1) * 4 / 180;

		PV3D* c = this->getC(theta);
		PV3D* cprima = this->getCPrima(theta);
		PV3D* csegunda = this->getCSegunda(theta);

		PV3D* t = cprima->normaliza();
		PV3D* b = (cprima->productoVectorial(csegunda))->normaliza();
		PV3D* n = b->productoVectorial(t);

		GLfloat m[4][4] = { { n->getX(), n->getY(), n->getZ(), 0 },
							{ b->getX(), b->getY(), b->getZ(), 0 },
							{ t->getX(), t->getY(), t->getZ(), 0 },
							{ c->getX(), c->getY(), c->getZ(), 1 } };

		GLfloat pto[] = { 0, 0, 0, 1 };
		PV3D* transPto = multiplicarMatrizPorPunto(m, pto);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glTranslated(transPto->getX(), transPto->getY(), transPto->getZ());
		glRotatef(theta, transPto->getX(), transPto->getY(), transPto->getZ());
	}

	Malla::dibuja();

	if (this->distancia != 0){
		glPopMatrix();
	}
}