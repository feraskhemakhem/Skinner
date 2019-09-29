#version 120
// cheb
uniform vec3 ka;
uniform vec3 kd;
uniform vec3 ks;
uniform float s;

varying vec3 lightInCamera; // light wrt camera
varying vec4 position; // vector position in camera space
varying vec3 vNor;

void main()
{
    vec3 normal = normalize(vNor);
    vec3 l = normalize(lightInCamera - vec3(position.xyz)); // light vector
    vec3 cd = kd * max(0, dot(l, normal)); //
    vec3 e = normalize(0 - vec3(position.xyz)); // eye vector, from position to camera (0,0,0)
    vec3 h = normalize(l + e); // halfway vector
    vec3 cs = ks * pow( max(0, dot(h, normal)), s);
    vec3 c = cd + ka + cs;
    // Map normal in the range [-1, 1] to color in range [0, 1];
    gl_FragColor = vec4(c, 1.0);
}
