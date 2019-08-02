// ==========================================================================
// Vertex program for barebones GLFW boilerplate
//
// Author:  Sonny Chan, University of Calgary
// Date:    December 2015
// ==========================================================================
#version 410

// interpolated colour received from vertex stage
//in vec3 Colour;
//in float z;
in vec2 uv;
in float dotNL;
in float dotNHP;

// first output is mapped to the framebuffer's colour index by default
out vec4 FragmentColour;

uniform sampler2D imageTexture;
uniform bool shading;

void main(void)
{
    // write colour output without modification
    //FragmentColour = vec4(Colour, 0);

    vec4 ca = vec4(0.4f, 0.4f, 0.4f, 0.0f);
    vec4 cl = vec4(1, 1, 1, 0);

	FragmentColour = texture(imageTexture, uv);

	if(shading){
		FragmentColour = FragmentColour * (ca + cl * dotNL);
	}
	
	
}
