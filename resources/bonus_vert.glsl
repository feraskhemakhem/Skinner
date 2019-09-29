#version 120
// cheb
attribute vec4 aPos;
attribute vec3 aNor;
attribute vec4 weights0;
attribute vec4 weights1;
attribute vec4 weights2;
attribute vec4 weights3;
attribute vec4 bones0;
attribute vec4 bones1;
attribute vec4 bones2;
attribute vec4 bones3;
attribute float numInfl;

uniform mat4 P;
uniform mat4 MV;
uniform mat4 anime[18];
uniform mat4 bind[18];
uniform vec3 lightPos;


varying vec3 lightInCamera; // light wrt camera
varying vec3 vNor; // in camera space
varying vec4 position; // in camera space


void main()
{
    
mat4 weights = mat4(weights0, weights1, weights2, weights3);
mat4 bones = mat4(bones0, bones1, bones2, bones3);
//     skinning equation
    vec4 sPos = vec4(0.0, 0.0, 0.0, 0.0);
    vec4 sNor = vec4(0.0, 0.0, 0.0, 0.0);
    for (int i = 0; i < int(numInfl); ++i) {
        
        int fIndex = i/4;
        int sIndex = i - fIndex;
        int index = int(bones[fIndex][sIndex]);
        
        vec4 dum1 = bind[index] * aPos;
        dum1 = anime[index] * dum1;
        dum1 = weights[fIndex][sIndex] * dum1;
        sPos = sPos + dum1;
        
        vec4 dum2 = bind[index] * vec4(aNor, 0.0f);
        dum2 = anime[index] * dum2;
        dum2 = weights[fIndex][sIndex] * dum2;
        sNor = sNor + dum2;
        
    }

	gl_Position = P * (MV * sPos);
    position = MV * sPos;
    vNor = (MV * sNor).xyz;
    lightInCamera = (MV * vec4(lightPos,1)).xyz;
}
