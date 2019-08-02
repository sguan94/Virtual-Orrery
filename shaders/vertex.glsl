// ==========================================================================
// Vertex program for barebones GLFW boilerplate
//
// Author:  Sonny Chan, University of Calgary
// Date:    December 2015
// ==========================================================================
#version 410

// location indices for these attributes correspond to those specified in the
// InitializeGeometry() function of the main program
layout(location = 0) in vec3 VertexPosition;
//layout(location = 1) in vec3 VertexColour;
layout(location = 1) in vec2 VertexUV;
layout(location = 2) in vec3 NormalVec;

uniform mat4 spinMatrix;
uniform mat4 revolutionMatrix;
uniform mat4 Projection;
uniform mat4 View;
uniform vec3 cameraPos;

// output to be interpolated between vertices and passed to the fragment stage
//out vec3 Colour;
//out float z;
out vec2 uv;
out float dotNL;
out float dotNHP;

void main()
{
    // assign vertex position without modification
	mat4 Model = mat4(	1, 0, 0, 0, 
						0, 1, 0, 0,
						0, 0, 1, 0,
						0, 0, 0, 1);
	Model = Model * revolutionMatrix * spinMatrix;
    gl_Position =  Projection * View * Model * vec4(VertexPosition, 1.0);

	vec3 n = (spinMatrix * vec4(NormalVec, 0.0f)).xyz;
    vec3 l = normalize(vec3(0,0,0) - (Model * vec4(VertexPosition, 1.0)).xyz);
    //vec3 v = normalize(cameraPos - (Model * vec4(VertexPosition, 1.0)).xyz);
    //vec3 h = normalize(v + l);

	dotNL = max(0, dot(n, l));
    //dotNHP = pow(max(0, dot(h, n)), 4);

    // assign output colour to be interpolated
    //Colour = VertexColour;
	//z = VertexPosition[1];
	uv = VertexUV;
}
