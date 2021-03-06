#define _USE_MATH_DEFINES
#include <cmath> 
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include "MatrixStack.h"


Camera::Camera(GLFWwindow* w) :
	aspect(1.0f),
	// fovy((float)(45.0*M_PI/180.0)),
	fovy((float)(90/180.0*M_PI)),
	znear(0.1f),
	zfar(1000.0f),
	rotations(3.14, 3.14/2),
	translations(0.0f, 0.0f, -5.0f),
	rfactor(0.01f),
	tfactor(0.001f),
	sfactor(0.005f),
	window(w)
{
}

Camera::~Camera()
{
}

void Camera::mouseClicked(float x, float y, bool shift, bool ctrl, bool alt)
{
	mousePrev.x = x;
	mousePrev.y = y;
	if(shift) {
		state = Camera::TRANSLATE;
	} else if(ctrl) {
		state = Camera::SCALE;
	} else {
		state = Camera::ROTATE;
	}
}

void Camera::mouseMoved(float x, float y)
{
	glm::vec2 mouseCurr(x, y);
	glm::vec2 dv = mouseCurr - mousePrev;
	switch(state) {
		case Camera::ROTATE:
			rotations += rfactor * dv;
			break;
		case Camera::TRANSLATE:
			translations.x -= translations.z * tfactor * dv.x;
			translations.y += translations.z * tfactor * dv.y;
			break;
		case Camera::SCALE:
			translations.z *= (1.0f - sfactor * dv.y);
			break;
	}
	mousePrev = mouseCurr;
}

void Camera::applyProjectionMatrix(std::shared_ptr<MatrixStack> P) const
{
	// Modify provided MatrixStack
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	P->multMatrix(glm::ortho(-5.0f / 640.0f * width, 5.0f / 640.0f * width,
	 -5.0f / 640.0f * height, 5.0f / 640.0f * height, znear, zfar));
	// P->multMatrix(glm::ortho(-5.0f, 5.0f, -5.0f, 5.0f, znear, zfar));

}

void Camera::applyViewMatrix(std::shared_ptr<MatrixStack> MV) const
{
	MV->translate(translations);
	MV->rotate(rotations.y, glm::vec3(1.0f, 0.0f, 0.0f));
	MV->rotate(rotations.x, glm::vec3(0.0f, 1.0f, 0.0f));
}
