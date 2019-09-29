#version 120
// cheb
attribute vec4 aPos;
attribute vec3 aNor;

uniform vec3 lightPos;
uniform mat4 P;
uniform mat4 MV;

varying vec3 lightInCamera; // light wrt camera
varying vec3 vNor; // in camera space
varying vec4 position; // in camera space


void main()
{
	gl_Position = P * (MV * aPos);
    position = MV * aPos;
    vNor = (MV * vec4(aNor, 0.0)).xyz;
    lightInCamera = (MV * vec4(lightPos,1)).xyz;
}
