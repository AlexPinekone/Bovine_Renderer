#include <iostream>
#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include "Vertice.h"
#include "Cara.h"
#include "Modelo.h"
#include "LectorArchivo.h"
#include <cmath>
#include <random>
#include <math.h>

using namespace std;

//El valor de pi para los angulos
double pi = 2 * acos(0.0);
//Prototipos
void iniciaMatriz(float**);
void imprimeMatriz(float**);
float** multMatriz(float**, float**);
Modelo multTodoModelo(Modelo mod, float **);
Vertice multPuntMat(Vertice v, float **);
float** crearMatriz();
Vertice calcPuntoMedio(Modelo m);
Vertice normaliza(Vertice v);
float productoPunto(Vertice v1, Vertice v2);
float calculaLuz(float p1x, float p1y, float p1z, float p2x, float p2y, float p2z, float p3x, float p3y, float p3z);
Vertice vectorRes(Vertice v1, Vertice v2);
void inicializaTodo();

//Arreglo donde estan los dos modelos
Modelo model[5];
//La variable t(tiempo) que ayuda con las animaciones
float t=0,g=0;
//Los puntos medios de los dos modelos
Vertice pm1, pm2;

//La vaca viene volando vengativa viendo vuestra cerca vertical
void anima1() {
	float nx, ny, nz;
	float zcI = -5;
	float zc1 = -2;
	float zc2 = 2;
	float zcF = 2;
	float ycI = 0;
	float yc1 = -6;
	float yc2 = 6;
	float ycF = 0;

	//Para la z
	nz = (pow(1 - t, 3) * zcI) +
		(3 * t * (pow(1 - t, 2)) * zc1) +
		(3 * (pow(t, 2)) * (1 - t) * zc2) +
		(pow(t, 3) * zcF);
	//Para la y
	ny = (pow(1 - t, 3) * ycI) +
		(3 * t * (pow(1 - t, 2)) * yc1) +
		(3 * (pow(t, 2)) * (1 - t) * yc2) +
		(pow(t, 3) * ycF);

	//Crea la matriz para hacer las modificaciones
	float** mT = crearMatriz();
	iniciaMatriz(mT);
	//modifica las partes de la matriz que se van a mover(restandole la posicion actual, que si no se suma esa posicion cada vez)
	//mT[0][3] = ny - model[0].vertices[0].x;
	mT[1][3] = ny - model[0].vertices[0].y; // 0 o ny
	mT[2][3] = nz - model[0].vertices[0].z;
	//Modifica el modelo(ya con su posicion)
	model[0] = multTodoModelo(model[0], mT);
	//cout << endl << model[0].vertices[0].z << endl;
}
//La vaca le hace una llave secreta a la cerca 
int p36=0;
bool bane=true;
void anima2() {
	p36 += 1;
	if (p36 < 720) {
		//Matriz traslada al origen
		float** mT = crearMatriz();
		iniciaMatriz(mT);
		mT[2][3] = -2 - pm1.z;;
		//Matriz regresa a posicion original
		float** mPo = crearMatriz();
		iniciaMatriz(mPo);
		mPo[2][3] = 2 + pm1.z;
		//Matriz de rotacion
		float** mR = crearMatriz();
		iniciaMatriz(mR);
		mR[0][0] = cos(0.5 * (pi / 180));//*( pi/180)
		mR[2][0] = -sin(0.5*(pi / 180));
		mR[0][2] = sin(0.5* (pi / 180));
		mR[2][2] = cos(0.5 * (pi / 180));
		if (bane) {
			cout << "Ayudame que tengo" << endl;
			imprimeMatriz(mPo);
			imprimeMatriz(mT);
			imprimeMatriz(mR);
			bane = false;
		}
		float** mFinal;
		mFinal = multMatriz(mPo, mR);
		mFinal = multMatriz(mFinal, mT);

		model[0] = multTodoModelo(model[0], mFinal);
	}
}
//La cerca se cae
int p90=0;
void anima3() {
	p90+=1;
	if (p90 < 900) {
		//Matriz traslada al origen
		float** mT = crearMatriz();
		iniciaMatriz(mT);
		mT[2][3] = -6-pm1.z;
		//Matriz regresa a posicion original
		float** mPo = crearMatriz();
		iniciaMatriz(mPo);
		mPo[2][3] = 6+pm1.z;
		//Matriz de rotacion
		float** mR = crearMatriz();
		iniciaMatriz(mR);
		mR[1][1] = cos(0.1 * (pi / 180));
		mR[1][2] = -sin(0.1 * (pi / 180));
		mR[2][1] = sin(0.1 * (pi / 180));
		mR[2][2] = cos(0.1 * (pi / 180));

		float** mFinal;
		mFinal = multMatriz(mPo, mR);
		mFinal = multMatriz(mFinal, mT);

		model[1] = multTodoModelo(model[1], mFinal);
	}
	else {
		t = 1.5;
	}
}
//La vaca salta
void anima4() {
	float nx, ny, nz;
	float zcI = 2;
	float zc1 = 2;
	float zc2 = 2;
	float zcF = 2;
	float ycI = 0;
	float yc1 = 2;
	float yc2 = 2;
	float ycF = 0;

	//Para la z
	nz = (pow(1 - t, 3) * zcI) +
		(3 * t * (pow(1 - t, 2)) * zc1) +
		(3 * (pow(t, 2)) * (1 - t) * zc2) +
		(pow(t, 3) * zcF);
	//Para la y
	ny = (pow(1 - t, 3) * ycI) +
		(3 * t * (pow(1 - t, 2)) * yc1) +
		(3 * (pow(t, 2)) * (1 - t) * yc2) +
		(pow(t, 3) * ycF);

	//Crea la matriz para hacer las modificaciones
	float** mT = crearMatriz();
	iniciaMatriz(mT);
	//modifica las partes de la matriz que se van a mover(restandole la posicion actual, que si no se suma esa posicion cada vez)
	mT[1][3] = ny - model[0].vertices[0].y;
	mT[2][3] = nz - model[0].vertices[0].z;
	//Modifica el modelo(ya con su posicion)
	model[0] = multTodoModelo(model[0], mT);
	//cout << endl << model[0].vertices[0].y << endl;
}
//La vaca es feliz por primera vez en su vida
void anima5() {
	//Matriz traslada al origen
	float** mT = crearMatriz();
	iniciaMatriz(mT);

	mT[2][3] = -1.5 - pm1.z;

	//Matriz regresa a posicion original
	float** mPo = crearMatriz();
	iniciaMatriz(mPo);
	mPo[2][3] = 1.5 + pm1.z;
	//Matriz de rotacion
	float** mR = crearMatriz();
	iniciaMatriz(mR);
	mR[0][0] = cos(0.5 * (pi / 180));
	mR[2][0] = -sin(0.5 * (pi / 180));
	mR[0][2] = sin(0.5 * (pi / 180));
	mR[2][2] = cos(0.5 * (pi / 180));
	if (bane) {
		cout << "Ayudame que tengo" << endl;
		imprimeMatriz(mPo);
		imprimeMatriz(mT);
		imprimeMatriz(mR);
		bane = false;
	}
	float** mFinal;
	mFinal = multMatriz(mPo, mR);
	mFinal = multMatriz(mFinal, mT);

	model[0] = multTodoModelo(model[0], mFinal);
}

void mueve() {
	if (GetKeyState(VK_LSHIFT) & 0x8000) {

		float** m1matT = crearMatriz();
		iniciaMatriz(m1matT);
		m1matT[2][3] = 0.01;

		model[0] = multTodoModelo(model[0], m1matT);
		
	}
}

void mueveAtras() {
	if (GetKeyState(VK_RSHIFT) & 0x8000) {

		float** m1matT = crearMatriz();
		iniciaMatriz(m1matT);
		m1matT[2][3] = -0.01;

		model[0] = multTodoModelo(model[0], m1matT);

	}
}


//Las variables que hacen las animaciones seuenciales
bool a1, a2, a3, a4, a5, ban;
//Para generar numeros random
random_device rd;
mt19937 gen(rd());
uniform_real_distribution<double> distribution(0.0, 1.0);
double numeroAleatorio;
/*
Vertice light_position(2.0, 1.0, 3.0);
Vertice light_direction(-1.0, -1.0, -1.0);*/

Vertice light_position(0,4,5);
Vertice light_direction(0,1,4);

Vertice luz,luzC;
Vertice colorV(1,1,1);
Vertice colorB(0.7294,0.2901,0);
Vertice colorP(0.09803,0.43529,0.23921);

void rotaLuz() {
	float** mR = crearMatriz();
	iniciaMatriz(mR);
	mR[0][0] = cos(-0.5 * (pi / 180));
	mR[2][0] = -sin(-0.5 * (pi / 180));
	mR[0][2] = sin(-0.5 * (pi / 180));
	mR[2][2] = cos(-0.5 * (pi / 180));
	luz = multPuntMat(luz, mR);
}

//Lo que lo dibuja todo en la pantalla
void display(void)
{
	if (GetKeyState(VK_RBUTTON) & 0x8000) {

		inicializaTodo();
	}
	/*  clear all pixels  */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	/*luz.x = light_direction.x - light_position.x;
	luz.y = light_direction.y - light_position.y;
	luz.z = light_direction.z - light_position.z;
	luz = normaliza(luz);*/

	
	glColor3f(1.0, 0.0, 0.0);
	
	if (a1) {
		//La vaca se mueve
		anima1();
		if (t >= 1) {
			a2 = true;
			a1 = false;
			t = 0;
		}
	}
	if (a2) {
		//Rota en x para tirar la cerca'
		anima2();
		if (t >= 1) {
			a2 = false;
			a3 = true;
			t = 0;
		}
	}
	if (a3) {
		//Tira la cerca
		anima3();
		if (t >= 1.5) {
			a4 = true;
			a3 = false;
			t = 0;
		}
	}
	if (a4) {
		//salto
		if (t > 0.2 && ban==false) {
			ban = true;
			t = 0; 
		}
			//ecuacciones parametiricas de lineas y curvas, diferencia splines bezier diferencias transformacinoes, practica 
			//ecuacion parametrica de la linea o una transformacion
		if (ban) {
			anima4();
			if (t >= 1) {
				a4 = false;
				a5 = true;
				t = 0;
				ban = false;
			}
		}
			
	}
	if (a5) {
		mueve();
		mueveAtras();
		//anima5();
	}
	
	rotaLuz();
	
	float p1x, p1y, p1z, p2x, p2y, p2z, p3x, p3y, p3z, res;

	//Aqui se generan todos los triangulos que generan los dos modelos
	glBegin(GL_TRIANGLES);

	for (int n = 0; n < 5; n++) {
		for (int i = 0; i < model[n].caras.size(); i++)
		{
			p1x = model[n].vertices[model[n].caras[i].vertexIndices[0]].x;
			p1y = model[n].vertices[model[n].caras[i].vertexIndices[0]].y;
			p1z = model[n].vertices[model[n].caras[i].vertexIndices[0]].z;
			p2x = model[n].vertices[model[n].caras[i].vertexIndices[1]].x;
			p2y = model[n].vertices[model[n].caras[i].vertexIndices[1]].y;
			p2z = model[n].vertices[model[n].caras[i].vertexIndices[1]].z;
			p3x = model[n].vertices[model[n].caras[i].vertexIndices[2]].x;
			p3y = model[n].vertices[model[n].caras[i].vertexIndices[2]].y;
			p3z = model[n].vertices[model[n].caras[i].vertexIndices[2]].z;
			res = calculaLuz(p1x,p1y,p1z,p2x,p2y,p2z,p3x,p3y,p3z);
			luzC.x = luzC.y = luzC.z = res;
			if (n == 0) 
				luzC = vectorRes(luzC, colorV);
			
			if (n == 1 || n == 3 || n == 4)
				luzC = vectorRes(luzC, colorB);

			if (n == 2)
				luzC = vectorRes(luzC, colorP);
			
			
			glColor3f(luzC.x,luzC.y,luzC.z);

			glVertex3f(p1x,p1y,p1z);
			glVertex3f(p2x,p2y,p2z);
			glVertex3f(p3x,p3y,p3z);

		}
	}
	glEnd();
	//Aqui se aumenta la variable t
	t += 0.001;
	glutSwapBuffers();
	glFlush();
}


float calculaLuz(float p1x, float p1y, float p1z, float p2x, float p2y, float p2z, float p3x, float p3y, float p3z) {
	float res;
	Vertice v1, v2, normal;
	v1.x = p1x - p2x;
	v1.y = p1y - p2y;
	v1.z = p1z - p2z;
	v2.x = p1x - p3x;
	v2.y = p1y - p3y;
	v2.z = p1z - p3z;
	//Producto cruz de los vectores del mismo triangulo
	normal.x = -(v1.y * v2.z - v1.z * v2.y);
	normal.y = -(v1.z * v2.x - v1.x * v2.z);
	normal.z = -(v1.x * v2.y - v1.y * v2.x);
	normal = normaliza(normal);

	res = productoPunto(normal,luz);
	return res;
}

Vertice vectorRes(Vertice v1,Vertice v2) {
	Vertice res;
	res.x = v1.x * v2.x;
	res.y = v1.y * v2.y;
	res.z = v1.z * v2.z;
	return res;
}

Vertice normaliza(Vertice v) {
	float nor;
	nor = sqrt(pow(v.x, 2) + pow(v.y,2) + pow(v.z,2));

	v.x = v.x / nor;
	v.y = v.y / nor;
	v.z = v.z / nor;
	return v;
}

float productoPunto(Vertice v1, Vertice v2) {
	float res;

	res = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;

	return res;
}

//Hace que la matriz se vuelva una identidad
void iniciaMatriz(float** m) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (i == j)
				m[i][j] = 1;
			else
				m[i][j] = 0;
		}
	}
}
//Imprime los valores de la matriz
void imprimeMatriz(float** m) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << m[i][j]<<" ";
		}
		cout << endl;
	}
}
//Multiplica la matriz1 por la matriz2(renglores por columnas)
float** multMatriz(float** m1, float** m2) {
	float **matRes=crearMatriz();
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			matRes[i][j] = 0;
			for (int k = 0; k < 4; k++)
				matRes[i][j] += m1[i][k] * m2[k][j];
		}
	}
	return matRes;
}
//Calcula el punto central del modelo 3D
Vertice calcPuntoMedio(Modelo m) {
	Vertice vres;
	vres.x = vres.y = vres.z = 0.0f;
	float mayx=m.vertices[0].x, menx = m.vertices[0].x;

	for (Vertice v : m.vertices) {
		vres.x += v.x;
		vres.y += v.y;
		vres.z += v.z;
		//cout<<"W "<<v.x << endl;
		if (v.x > mayx)
			mayx = v.x;
		if (v.x < menx)
			menx = v.x;
	}

	vres.x = vres.x / m.vertices.size();
	vres.y = vres.y / m.vertices.size();
	vres.z = vres.z / m.vertices.size();
	cout << "PUNTOS: "<<mayx<<" Y "<<menx << endl;
	return vres;
}
//Multiplica la matriz por un punto
Vertice multPuntMat(Vertice v, float** m) {
	Vertice res;
	float rx, ry, rz, rw;
	rx = v.x;
	ry = v.y;
	rz = v.z;
	rw = v.w;

	res.x = (rx * m[0][0]) + (ry * m[0][1]) + (rz * m[0][2]) + (rw * m[0][3]);
	res.y = (rx * m[1][0]) + (ry * m[1][1]) + (rz * m[1][2]) + (rw * m[1][3]);
	res.z = (rx * m[2][0]) + (ry * m[2][1]) + (rz * m[2][2]) + (rw * m[2][3]);
	res.w = (rx * m[3][0]) + (ry * m[3][1]) + (rz * m[3][2]) + (rw * m[3][3]);
	
	return res;
}
//MUltiplica todos los vertices de un modelo por una matriz concreta
Modelo multTodoModelo(Modelo mod,float** m) {
	
	Modelo aux=mod;
	for (int i = 0; i < aux.vertices.size(); i++) {
		aux.vertices[i] = multPuntMat(aux.vertices[i],m);
	}
	return aux;
}
//Crea una matriz nueva
float** crearMatriz() {
	float** matriz = new float* [4];
	for (int i = 0; i < 4; i++) {
		matriz[i] = new float[4];
	}
	return matriz;
}

void init(void)
{
	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	/* glShadeModel(GL_SMOOTH);
	
	// Configurar la luz direccional
	GLfloat light_direction[] = { 1.0, -1.0, -1.0, 0.0 };  // (x, y, z, w)
	GLfloat light_color[] = { 1.0, 1.0, 1.0, 1.0 };         // Color blanco
	GLfloat ambient_light[] = { 0.2, 0.2, 0.2, 1.0 };       // Luz ambiental
	
	glLightfv(GL_LIGHT0, GL_POSITION, light_direction);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_color);
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);*/

	/*  select clearing (background) color       */
	glClearColor(0.8392, 0.9176, 0.9725, 0.0);

	/*  initialize viewing values  */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);
	//gluOrtho2D(0.0, 1.0, 0.0, 1.0);

	gluPerspective(45.0, 800.0 / 600.0, 0.1, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

	glEnable(GL_DEPTH_TEST);

}
 // Dirección de la luz

/*
 *  Declare initial window size, position, and display mode
 *  (single buffer and RGBA).  Open window with "hello"
 *  in its title bar.  Call initialization routines.
 *  Register callback function to display graphics.
 *  Enter main loop and process events.
 */

void inicializaTodo() {
	//Cosas de la luz
	luz.x = light_direction.x - light_position.x;
	luz.y = light_direction.y - light_position.y;
	luz.z = light_direction.z - light_position.z;
	luz = normaliza(luz);

	//Lector de archivos
	LectorArchivo lec;
	//Los archivos donde estan los modelos
	string dir1 = "cow.obj";
	string dir2 = "cerca.obj";
	string dir3 = "pi.obj";
	string dir4 = "humano2.obj";
	//Se leen los dos archivos y se crean los modelos para cada uno
	model[0] = lec.lector(dir1);
	model[1] = lec.lector(dir2);
	model[2] = lec.lector(dir3);
	model[3] = lec.lector(dir2);
	model[4] = lec.lector(dir2);
	//Calcula los puntos centrales de ambos modelos 
	pm1 = calcPuntoMedio(model[0]);
	cout << "Punto medio: " << pm1.x << " , " << pm1.y << " , " << pm1.z << endl;
	pm2 = calcPuntoMedio(model[1]);

	//Modelo 1 (mueve la vaca a una posicion inicial)
	float** m1matT = crearMatriz();
	iniciaMatriz(m1matT);
	m1matT[2][3] = -2;
	m1matT[0][3] = 0.3;

	model[0] = multTodoModelo(model[0], m1matT);

	//Modelo 2 (Lo escala, rota y mueve jaja salu2)
	float** m2matR = crearMatriz();
	float** m2matT = crearMatriz();
	float** m2matE = crearMatriz();
	iniciaMatriz(m2matR);
	iniciaMatriz(m2matT);
	iniciaMatriz(m2matE);
	//Rotar
	m2matR[0][0] = cos(90 * (pi / 180));
	m2matR[0][2] = sin(90 * (pi / 180));
	m2matR[2][0] = -sin(90 * (pi / 180));
	m2matR[2][2] = cos(90) * (pi / 180);
	//Escalar
	m2matE[0][0] = 0.5;
	m2matE[1][1] = 0.5;
	m2matE[2][2] = 0.5;
	m2matE[3][3] = 0.5;
	//Trasladar
	m2matT[2][3] = 6;
	m2matT[0][3] = 2;

	float** mFinal;
	mFinal = multMatriz(m2matR, m2matE);
	mFinal = multMatriz(m2matT, mFinal);
	model[1] = multTodoModelo(model[1], mFinal);

	//Imprime la smatrices para verificar
	//cout << endl << "Escalacion" << endl;
	//imprimeMatriz(m2matE);
	//cout << endl << "Rotacion" << endl;
	//imprimeMatriz(m2matR);
	//cout << endl << "Traslacion" << endl;
	//imprimeMatriz(m2matT);
	//Multiplica todas las matrices para crear una general
	
	//cout << endl << "1erMult" << endl;
	//imprimeMatriz(mFinal);
	

	//cout << endl << "Final" << endl;
	//imprimeMatriz(mFinal);


	//Cambia los puntos de los modelos

	


	//Modelo 3
	float** m3matE = crearMatriz();
	float** m3matT = crearMatriz();
	iniciaMatriz(m3matE);
	iniciaMatriz(m3matT);
	//Escalar
	m3matE[0][0] = 25;
	m3matE[1][1] = 25;
	m3matE[2][2] = 25;
	m3matE[3][3] = 25;
	//Trasladar
	m3matT[2][3] = 0;
	m3matT[0][3] = 0;
	m3matT[1][3] = 0.5;
	
	float** mFinal2;
	mFinal2 = multMatriz(m3matE,m3matT);

	model[2] = multTodoModelo(model[2], mFinal2);

	
	//model[1] = multTodoModelo(model[1], m2matE);
	//model[1] = multTodoModelo(model[1], m2matT);

	//Varias Cercas 1
	float** c1R = crearMatriz();
	float** c1T = crearMatriz();
	float** c1E = crearMatriz();
	iniciaMatriz(c1R);
	iniciaMatriz(c1T);
	iniciaMatriz(c1E);
	//Rotar
	c1R[0][0] = cos(90 * (pi / 180));
	c1R[0][2] = sin(90 * (pi / 180));
	c1R[2][0] = -sin(90 * (pi / 180));
	c1R[2][2] = cos(90) * (pi / 180);
	//Escalar
	c1E[0][0] = 0.5;
	c1E[1][1] = 0.5;
	c1E[2][2] = 0.5;
	c1E[3][3] = 0.5;
	//Trasladar
	c1T[2][3] = 6;
	c1T[0][3] = 7;

	float** f1;
	f1 = multMatriz(c1R, c1E);
	f1 = multMatriz(c1T, f1);
	model[3] = multTodoModelo(model[3], f1);

	//Varias Cercas 2
	float** c2R = crearMatriz();
	float** c2T = crearMatriz();
	float** c2E = crearMatriz();
	iniciaMatriz(c2R);
	iniciaMatriz(c2T);
	iniciaMatriz(c2E);
	//Rotar
	c2R[0][0] = cos(90 * (pi / 180));
	c2R[0][2] = sin(90 * (pi / 180));
	c2R[2][0] = -sin(90 * (pi / 180));
	c2R[2][2] = cos(90) * (pi / 180);
	//Escalar
	c2E[0][0] = 0.5;
	c2E[1][1] = 0.5;
	c2E[2][2] = 0.5;
	c2E[3][3] = 0.5;
	//Trasladar
	c2T[2][3] = 6;
	c2T[0][3] = -3;

	float** f2;
	f2 = multMatriz(c2R, c2E);
	f2 = multMatriz(c2T, f2);
	model[4] = multTodoModelo(model[4], f2);

	//DirectionalLight 
	a1 = true;
	a2 = false; 
	a3 = false;
	a4 = false;
	a5 = false; 
	ban = false;
	bane = true;
	p90 = 0;
	t = 0;
	g = 0;
	p36 = 0;

}

int main(int argc, char** argv)
{
	inicializaTodo();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Ventana ventanosa");
	init();
	
	glutDisplayFunc(display);
	//glutPostRedisplay();
	glutIdleFunc(display);
	glutMainLoop();

	return 0;   /* ISO C requires main to return int. */
}



