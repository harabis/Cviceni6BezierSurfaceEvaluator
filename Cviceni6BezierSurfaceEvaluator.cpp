// cviceni6BezierSurface.cpp : Tento soubor obsahuje funkci main. Provádění programu se tam zahajuje a ukončuje.
//


#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

using namespace std;

int main()
{
	int sirka = 800;
	int vyska = 600;

	float angle1 = 0, angle2 = 0, angle3 = 0;

	sf::Window Aplikace(sf::VideoMode(sirka, vyska), "Cviceni 5 - Bezier curves");

	// nastav OpenGL
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);           // barva pozadi obrazku
	glClearDepth(-5.0f);                             // implicitni hloubka ulozena v pameti hloubky
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);                           // povoleni a nastaveni testu hloubky fragmentu

													// styl vykreslovani
	glPointSize(20.0f);                              // velikost vykreslovanych ridicich bodu
	glLineWidth(2.0f);                              // sirka vykreslovanych car
	glEnable(GL_POINT_SMOOTH);                      // povoleni antialiasingu bodu
	glEnable(GL_LINE_SMOOTH);                       // povoleni antialiasingu car
	glShadeModel(GL_SMOOTH);

	glViewport(0, 0, (GLsizei)sirka, (GLsizei)vyska);       // viditelna oblast pres cele okno
	glMatrixMode(GL_PROJECTION);                    // zacatek modifikace projekcni matice
	glLoadIdentity();                               // vymazani projekcni matice (=identita)

	if (sirka <= vyska) {                                     // jestlize je okno nastaveno na vysku
		glOrtho(-5.0, 5.0, -5.0 * (GLfloat)vyska / (GLfloat)sirka, 5.0 * (GLfloat)vyska / (GLfloat)sirka, -5.0, 5.0);
	}
	else {                                          // jestlize je okno nastaveno na sirku
		glOrtho(-5.0 * (GLfloat)sirka / (GLfloat)vyska, 5.0 * (GLfloat)sirka / (GLfloat)vyska, -5.0, 5.0, -5.0, 5.0);
	}


	while (Aplikace.isOpen())
	{
		sf::Event Udalosti;

		while (Aplikace.pollEvent(Udalosti))
		{
			switch (Udalosti.type)
			{

			case sf::Event::Closed:
				Aplikace.close();
				break;

			case sf::Event::KeyPressed:
				switch (Udalosti.key.code)
				{
				case sf::Keyboard::Escape:
					Aplikace.close();
					break;

				}

			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				angle1++;
				angle2 += 1.6f;
				angle3 += 2.1f;

			}


		}

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// vykresleni plochy

		float ctrlPoints2D[4][4][3] = {
			{ {-1.5,-1.5, 4.0}, {-0.5,-1.5, 2.0}, {0.5,-1.5,-1.0}, { 1.5,-1.5, 2.0} },
			{ {-1.5,-0.5, 1.0}, {-0.5,-0.5, 3.0}, {0.5,-0.5, 0.0}, { 1.5,-0.5,-1.0} },
			{ {-1.5, 0.5, 4.0}, {-0.5, 0.5, 0.0}, {0.5, 0.5, 3.0}, { 1.5, 0.5, 4.0} },
			{ {-1.5, 1.5,-2.0}, {-0.5, 1.5,-2.0}, {0.5, 1.5, 0.0}, { 1.5, 1.5,-1.0} }
		};

		float i, j;


		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glEnable(GL_MAP2_VERTEX_3);
		glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlPoints2D[0][0][0]);


		glRotatef(angle1, 0.0, 0.0, 1.0);
		glRotatef(angle2, 0.0, 1.0, 0.0);
		glRotatef(angle3, 1.0, 0.0, 0.0);

		glBegin(GL_POINTS);
		for (int l = 0; l < 4; l++) {
			for (int k = 0; k < 4; k++) {
				glVertex3f(ctrlPoints2D[l][k][0], ctrlPoints2D[l][k][1], ctrlPoints2D[l][k][2]);
			}
		}
		glEnd();

		for (i = 0; i < 1.0f; i += 0.04f) {
			glBegin(GL_QUAD_STRIP);
			for (j = 0; j < 1.0f; j += 0.1f) {
				glColor3f(i, 0.5, j);
				glEvalCoord2f(i, j);
				glColor3f(i + 0.04f, 0.5, j);
				glEvalCoord2f(i + 0.04f, j);
			}
			glEnd();
		}


		glFlush();
		Aplikace.display();

	}
}

