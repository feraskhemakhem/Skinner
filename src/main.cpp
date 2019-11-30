#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <memory>
#include <cstdlib>
#include <algorithm>

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>


#include "GLSL.h"
#include "Program.h"
#include "Camera.h"
#include "MatrixStack.h"
#include "ShapeSkin.h"

using namespace std;
using namespace glm;

GLFWwindow *window; // Main application window
string RESOURCE_DIR = ""; // Where the resources are loaded from
int NUM_BONES = 2; // 2 bones by default
int NUM_VERTICES_HORIZ = 4;
int NUM_VERTICES_VERT = 2;
int RECT_LENGTH = 10;
int RECT_WIDTH = 20;
float DEFORM_FACTOR = 0.5; // coefficient for the weight between LBS and DQS
bool keyToggles[256] = {false};
double t = 0.0;

shared_ptr<Camera> camera = NULL;
shared_ptr<ShapeSkin> shape = NULL;
shared_ptr<Program> progSimple = NULL;
shared_ptr<Program> progSkin = NULL;
shared_ptr<Program> progBonus = NULL;
shared_ptr<Skinner> walker = NULL;


static void error_callback(int error, const char *description)
{
	cerr << description << endl;
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	else if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) { // GLFW_KEY_RIGHT
		DEFORM_FACTOR = std::min(DEFORM_FACTOR+0.1f, 1.0f);
		cout << "deform factor: " << DEFORM_FACTOR << endl;
	}
	else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) { // GLFW_KEY_LEFT 
		DEFORM_FACTOR = std::max(DEFORM_FACTOR-0.1f, 0.0f);
		cout << "deform factor: " << DEFORM_FACTOR << endl;
	}
}

static void char_callback(GLFWwindow *window, unsigned int key)
{
	keyToggles[key] = !keyToggles[key];
	if (key == 'd') {
		t += 0.3;
	}
	else if (key == 'a') {
		t -= 0.3;
	}
}

static void cursor_position_callback(GLFWwindow* window, double xmouse, double ymouse)
{
	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if(state == GLFW_PRESS) {
		camera->mouseMoved(xmouse, ymouse);
	}
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	// Get the current mouse position.
	double xmouse, ymouse;
	glfwGetCursorPos(window, &xmouse, &ymouse);
	// Get current window size.
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	if(action == GLFW_PRESS) {
		bool shift = mods & GLFW_MOD_SHIFT;
		bool ctrl  = mods & GLFW_MOD_CONTROL;
		bool alt   = mods & GLFW_MOD_ALT;
		camera->mouseClicked(xmouse, ymouse, shift, ctrl, alt);
	}
}

// void loadScene(const string &meshFile, const string &attachmentFile, const string &skeletonFile)
// {
// 	keyToggles[(unsigned)'c'] = true;
	
// 	camera = make_shared<Camera>();
	
// 	// Single shape for all the animations.
// 	shape = make_shared<ShapeSkin>();
// 	shape->loadMesh(meshFile);

//     shape->loadAttachment(attachmentFile, walker);
//     // This function now loads the attachments and saves bind pose to bindPose, along with the other animations to boneAnimations
// 	shape->loadSkeleton(skeletonFile, walker);

// 	// For drawing the grid, etc.
// 	progSimple = make_shared<Program>();
// 	progSimple->setShaderNames(RESOURCE_DIR + "simple_vert.glsl", RESOURCE_DIR + "simple_frag.glsl");
// 	progSimple->setVerbose(true);
	
// 	// For skinned shape, CPU/GPU
// 	progSkin = make_shared<Program>();
// 	progSkin->setShaderNames(RESOURCE_DIR + "skin_vert.glsl", RESOURCE_DIR + "skin_frag.glsl");
// 	progSkin->setVerbose(true);
    
//     progBonus = make_shared<Program>();
//     progBonus->setShaderNames(RESOURCE_DIR + "bonus_vert.glsl", RESOURCE_DIR + "bonus_frag.glsl");
//     progBonus->setVerbose(true);
// }

void loadScene()
{
	keyToggles[(unsigned)'c'] = true;
	
	camera = make_shared<Camera>();
	
	// Single shape for all the animations.
	shape = make_shared<ShapeSkin>();
	shape->loadMesh(NUM_VERTICES_HORIZ, NUM_VERTICES_VERT, RECT_LENGTH, RECT_WIDTH);

	shape->loadAttachment(NUM_BONES, RECT_WIDTH);
	// This function now loads the attachments and saves bind pose to bindPose, along with the other animations to boneAnimations
	shape->loadSkeleton(walker);

	// For drawing the grid, etc.
	progSimple = make_shared<Program>();
	progSimple->setShaderNames(RESOURCE_DIR + "simple_vert.glsl", RESOURCE_DIR + "simple_frag.glsl");
	progSimple->setVerbose(true);
	
	// For skinned shape, CPU/GPU
	progSkin = make_shared<Program>();
	progSkin->setShaderNames(RESOURCE_DIR + "skin_vert.glsl", RESOURCE_DIR + "skin_frag.glsl");
	progSkin->setVerbose(true);
    
	progBonus = make_shared<Program>();
	progBonus->setShaderNames(RESOURCE_DIR + "bonus_vert.glsl", RESOURCE_DIR + "bonus_frag.glsl");
	progBonus->setVerbose(true);
}

void init()
{
    
	// my skinner things
	walker = make_shared<Skinner>(NUM_BONES);

	// Non-OpenGL things
	// loadScene(MESH_FILE, ATTACHMENT_FILE, SKELETON_FILE);
	loadScene();

	// Set background color
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	// Enable z-buffer test
	glEnable(GL_DEPTH_TEST);
	// Enable alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	shape->init();

	progSimple->init();
	progSimple->addUniform("P");
	progSimple->addUniform("MV");
	
	progSkin->init();
    progSkin->addUniform("P");
    progSkin->addUniform("MV");
    progSkin->addAttribute("aPos");
    progSkin->addAttribute("aNor");
    progSkin->addUniform("lightPos");
    progSkin->addUniform("ka");
    progSkin->addUniform("kd");
    progSkin->addUniform("ks");
    progSkin->addUniform("s");
    progSkin->setVerbose(false);
    
    progBonus->init();
    progBonus->addUniform("P");
    progBonus->addUniform("MV");
    progBonus->addUniform("anime");
    progBonus->addUniform("bind");
    progBonus->addAttribute("aPos");
    progBonus->addAttribute("aNor");
    progBonus->addAttribute("weights0");
    progBonus->addAttribute("weights1");
    progBonus->addAttribute("weights2");
    progBonus->addAttribute("weights3");
    progBonus->addAttribute("bones0");
    progBonus->addAttribute("bones1");
    progBonus->addAttribute("bones2");
    progBonus->addAttribute("bones3");
    progBonus->addAttribute("numInfl");
    progBonus->addUniform("lightPos");
    progBonus->addUniform("ka");
    progBonus->addUniform("kd");
    progBonus->addUniform("ks");
    progBonus->addUniform("s");
    progBonus->setVerbose(false);
	
	// Initialize time.
	glfwSetTime(0.0);
	
	GLSL::checkError(GET_FILE_LINE);
}

void render()
{
	// Update time.
	// double t = glfwGetTime();

	// Get current frame buffer size.
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	
	// Use the window size for camera.
	glfwGetWindowSize(window, &width, &height);
	camera->setAspect((float)width/(float)height);
	
	// Clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	if(!keyToggles[(unsigned)'c']) {
		glEnable(GL_CULL_FACE);
	} else {
		glDisable(GL_CULL_FACE);
	}
	if(keyToggles[(unsigned)'w']) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	} else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	
	auto P = make_shared<MatrixStack>();
	auto MV = make_shared<MatrixStack>();
	
	// Apply camera transforms
	P->pushMatrix();
	camera->applyProjectionMatrix(P);
	MV->pushMatrix();
	camera->applyViewMatrix(MV);	

	// Draw grid
	progSimple->bind();
	glUniformMatrix4fv(progSimple->getUniform("P"), 1, GL_FALSE, glm::value_ptr(P->topMatrix()));
	glUniformMatrix4fv(progSimple->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
	float gridSizeHalf = 5.0f;
	int gridNx = 11;
	int gridNz = 11;
	glLineWidth(1);
	glColor3f(0.8f, 0.8f, 0.8f);
	glBegin(GL_LINES);
	// draws lines in x direction
	for(int i = 0; i < gridNx; ++i) {
		float alpha = i / (gridNx - 1.0f);
		float x = (1.0f - alpha) * (-gridSizeHalf) + alpha * gridSizeHalf;
		glVertex3f(x, 0, -gridSizeHalf);
		glVertex3f(x, 0,  gridSizeHalf);
	}

	// draws lines in z direction
	for(int i = 0; i < gridNz; ++i) {
		float alpha = i / (gridNz - 1.0f);
		float z = (1.0f - alpha) * (-gridSizeHalf) + alpha * gridSizeHalf;
		glVertex3f(-gridSizeHalf, 0, z);
		glVertex3f( gridSizeHalf, 0, z);
	}

	glEnd();
	int timeScale;
	timeScale = (int)(t*NUM_BONES); // determines the relative speed of cheb
	if(keyToggles[(unsigned)'b']) {
		// dra	ng bones
		float boneScale = 0.25f; // determines the size of the bones
		assert(NUM_BONES > 0);
		// draw_bone(0, boneScale, timeScale, MV, P);	
		mat4 howdy = mat4(1.0);

		for (int i = 0; i < NUM_BONES; ++i) { // for NUM_BONES bones
				MV->pushMatrix();
				howdy = howdy * walker->getAnime(timeScale, i);
				// MV->multMatrix(howdy); // animation acts wrt base frame
				MV->multMatrix(walker->getAnime(timeScale, i));
				glUniformMatrix4fv(progSimple->getUniform("P"), 1, GL_FALSE, glm::value_ptr(P->topMatrix()));
				glUniformMatrix4fv(progSimple->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
				glLineWidth(2);
				glBegin(GL_LINES);
				glColor3f(1, 0, 0);
				glVertex3f(0, 0, 0);
				glVertex3f(boneScale, 0, 0);
				glColor3f(0, 1, 0);
				glVertex3f(0, 0, 0);
				glVertex3f(0, boneScale, 0);
				glColor3f(0, 0, 1);
				glVertex3f(0, 0, 0);
				glVertex3f(0, 0, boneScale);
				glEnd();
				MV->popMatrix();
				// pog *= walker->getBind(i);
			}
    }		

    progSimple->unbind();
    
		// Draw character
		MV->pushMatrix();
		progSkin->bind();
		
		glUniformMatrix4fv(progSkin->getUniform("P"), 1, GL_FALSE, glm::value_ptr(P->topMatrix()));
		glUniformMatrix4fv(progSkin->getUniform("MV"), 1, GL_FALSE, glm::value_ptr(MV->topMatrix()));
		glUniform3f(progSkin->getUniform("lightPos"), 10.0f, 10.0f, 10.0f); // in camera coordinates back left corner

		// colouring
		glUniform3f(progSkin->getUniform("kd"), 0.3f, 0.3f, 0.3f); // diffused colour
		glUniform3f(progSkin->getUniform("ks"), 0.5f, 0.5f, 0.5f); // specular colour
		glUniform1f(progSkin->getUniform("s"), 200.0f);
		glUniform3f(progSkin->getUniform("ka"), 0.4f, 0.4f, 0.4f); // ambient colour (rgb)

		// apply skin
		if (DEFORM_FACTOR == 0)
			shape->LBSskinOn(walker, timeScale);
		else
			shape->DQSskinOn(walker, timeScale);

		shape->setProgram(progSkin);
		shape->draw();
		GLSL::checkError(GET_FILE_LINE);

		progSkin->unbind();
		MV->popMatrix();
    
	// Pop matrix stacks.
	MV->popMatrix();
	P->popMatrix();
	GLSL::checkError(GET_FILE_LINE);
}

int main(int argc, char **argv)
{

	// RESOURCE_DIR = argv[1] + string("/");
	RESOURCE_DIR = "../resources/";
	NUM_BONES = argc > 1 ? atoi(argv[1]) : 2;
	NUM_VERTICES_HORIZ = argc > 2 ? atoi(argv[2]) : 4;
	NUM_VERTICES_VERT = argc > 3 ? atoi(argv[3]) : 2;
	RECT_WIDTH = argc > 4 ? atoi(argv[4]) : 20;
	RECT_LENGTH = argc > 5 ? atoi(argv[5]) : 10;
	DEFORM_FACTOR = argc > 6 ? atoi(argv[6]) : 0.5;

	// error checking: asserts to make sure valid input
	assert (NUM_BONES > 1); // more than 1 bone
	assert (NUM_VERTICES_HORIZ > 0); // at least 1 vertices each direction
	assert (NUM_VERTICES_VERT > 0);
	assert (RECT_WIDTH > 0); // positive width
	assert (RECT_LENGTH > 0); // positive length

	// Set error callback.
	glfwSetErrorCallback(error_callback);
	// Initialize the library.
	if(!glfwInit()) {
		return -1;
	}
	// Create a windowed mode window and its OpenGL context.
	window = glfwCreateWindow(640, 480, "LBS - QBS skinner", NULL, NULL);
	if(!window) {
		glfwTerminate();
		return -1;
	}
	// Make the window's context current.
	glfwMakeContextCurrent(window);
	// Initialize GLEW.
	glewExperimental = true;
	if(glewInit() != GLEW_OK) {
		cerr << "Failed to initialize GLEW" << endl;
		return -1;
	}
	glGetError(); // A bug in glewInit() causes an error that we can safely ignore.
	cout << "OpenGL version: " << glGetString(GL_VERSION) << endl;
	cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;
	// Set vsync.
	glfwSwapInterval(1);
	// Set keyboard callback.
	glfwSetKeyCallback(window, key_callback);
	// Set char callback.
	glfwSetCharCallback(window, char_callback);
	// Set cursor position callback.
	glfwSetCursorPosCallback(window, cursor_position_callback);
	// Set mouse button callback.
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	// Initialize scene.
	init();
	// Loop until the user closes the window.
	while(!glfwWindowShouldClose(window)) {
		// Render scene.
		render();
		// Swap front and back buffers.
		glfwSwapBuffers(window);
		// Poll for and process events.
		glfwPollEvents();
	}
	// Quit program.
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}
