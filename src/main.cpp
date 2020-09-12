#include <stdlib.h>
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "classes/glwindow.h"
#include "helicopter.h"
#include "util.h"
#include "keyaction.h"
#include "player.h"
#include "camera.h"
#include "skybox.h"
#include "scenery.h"
#include "texturemanager.h"

class RenderWindow: public GLWindowBase
{
private:
	SkyBox * skybox;
	Scenery * scenery;
	Helicopter * helicopter;
	Camera * camera;
	TextureManager * texman;
	char str[255];
protected:
	bool onInit(int argc, char** argv)
	{
		// qualidade do anti serrilhado
#ifdef WIN32
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 8);
#endif
		return GLWindowBase::onInit(argc, argv);
	}

	virtual void getWindowInfo(int& width, int& height, int& bpp, bool& fullscreen, bool& resizable)
	{
		GLWindowBase::getWindowInfo(width, height, bpp, fullscreen, resizable);
	}

	virtual void onResize(int newWidth, int newHeight)
	{
		onCreate();
	}

	void setup3DScene()
	{
		int width = getWidth(), height = getHeight();
		if (height == 0)									// Prevent A Divide By Zero
			height = 1;
		glViewport(0, 0, width, height);					// Set The Current Viewport
		glMatrixMode( GL_PROJECTION );						// Select The Projection Matrix
		glLoadIdentity();									// Reset The Projection Matrix
		gluPerspective(45.0f, (GLfloat)width / height, 0.01f, 200.0f);
		// Calculate The Aspect Ratio Of The Window
		glMatrixMode( GL_MODELVIEW );						// Select The Modelview Matrix
		glLoadIdentity();									// Reset The Modelview Matrix
	}

	virtual void onCreate()
	{
		GLfloat col[] = {1.0f, 1.0f, 1.0f, 1.0f};
		GLfloat pos[] = { -1.0f, 1.0f, -2.0f, 1.0f};

		if(camera == NULL)
		{
			camera = new Camera();
		}
		if(skybox == NULL)
		{
			skybox = new SkyBox();
			skybox->load();
		}
		if(scenery == NULL)
		{
			scenery = new Scenery();
			scenery->load();
		}
		if(helicopter == NULL)
		{
			helicopter = new Helicopter(100, texman);
			helicopter->setConstantVelocity(false);
			helicopter->setBreakingAcceleration(0.002f);
			helicopter->getXAction().setKeys('s', 'w');
			helicopter->getZAction().setKeys('a', 'd');
			helicopter->getUpDownAction().setKeys(SDLK_DOWN, SDLK_UP);
		}
		setup3DScene();
		glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
		// Habilita teste de profundidade
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glClearDepth(1.0f);
		glDepthFunc(GL_LEQUAL);
		// Habilita luz
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, col);
		glLightfv(GL_LIGHT0, GL_POSITION, pos);
		glShadeModel(GL_SMOOTH);
		// Habilita cor nor objetos
		glEnable(GL_COLOR_MATERIAL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST );
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST );
		camera->setXYZ(1.5f, -0.08f, 0.07f);
		showMouse(false);
		lockMouse(true);
	}

	virtual void onMouseDown(int x, int y, int button, int state)
	{
		if(button == SDL_BUTTON_LEFT && state == 0)
			helicopter->startShootGun();
		else if(button == SDL_BUTTON_LEFT && state == LeftShift)
			helicopter->shootMissileLeft();
		else if(button == SDL_BUTTON_RIGHT && state == LeftShift)
			helicopter->shootMissileRight();
	}

	virtual void onMouseUp(int x, int y, int button, int state)
	{
		if(button == SDL_BUTTON_LEFT && state == 0)
			helicopter->stopShootGun();
	}

	/**
	 * trata os eventos do teclado
	 */
	virtual void onKeyDown(int key, int state)
	{
		helicopter->update(key, true);
		switch(key)
		{
		case SDLK_0:
		case SDLK_KP0:
			camera->setXYZ(1.5f, -0.08f, 0.07f);
			camera->setZAngle(0.0f);
			camera->setYAngle(0.0f);
			break;
		case SDLK_1:
		case SDLK_KP1:
			camera->setXYZ(0.7f, 0.05f, -0.27f);
			camera->setZAngle(0.0f);
			camera->setYAngle(80.0f);
			break;
		case SDLK_2:
		case SDLK_KP2:
			camera->setXYZ(2.5f, -0.1f, 0.07f);
			camera->setZAngle(-20.0f);
			camera->setYAngle(0.0f);
			break;
		default:
			break;
		}
		GLWindowBase::onKeyDown(key, state);
	}

	/**
	 * trata os eventos do teclado
	 */
	virtual void onKeyUp(int key, int state)
	{
		helicopter->update(key, false);
		GLWindowBase::onKeyUp(key, state);
	}

	virtual void render()
	{
		// limpa o buffer
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		glPushMatrix();

		glRotatef(helicopter->getYAngle() + 90, 0.0f, 1.0f, 0.0f);
		camera->move();
		camera->look();

		glTranslatef(0.0f, -helicopter->getYDist(), 0.0f);
		glPushMatrix();
		skybox->render();
		helicopter->move();
		scenery->render();
		glPopMatrix();

		// renderiza o helicoptero
		glPushMatrix();
		glTranslatef(-camera->getX(), -camera->getY(), -camera->getZ());
		glRotatef(-helicopter->getYAngle(), 0.0f, 1.0f, 0.0f);
		glTranslatef(camera->getX(), camera->getY(), camera->getZ());
		helicopter->render();
		glPopMatrix();

		glPopMatrix();
		// mostra os desenhos
		swapBuffers();
		// atualiza os movimentos
		updateAction();
		sprintf(str, "FPS: %.2f", getFPS());
		setTitle(str);
	}

	/**
	 * Atualiza os ângulos
	 */
	inline void updateAction()
	{

	}

public:
	RenderWindow()
	{
		texman = new TextureManager();
		helicopter = NULL;
		skybox = NULL;
		scenery = NULL;
		camera = NULL;
	}
	~RenderWindow()
	{
		if(camera != NULL)
			delete camera;
		if(scenery != NULL)
			delete scenery;
		if(skybox != NULL)
			delete skybox;
		if(helicopter != NULL)
			delete helicopter;
		delete texman;
	}
};

int main(int argc, char *argv[])
{
	RenderWindow lp;

	lp.setTitle("Helicopter");
	return lp.start(argc, argv);
}

