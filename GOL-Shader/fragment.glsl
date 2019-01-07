#version 110
out vec4 FragColor;


uniform sampler2D aTexture;
uniform float windowSize;

float neighbors = 0.0;

float offset = 1.0/windowSize;

void main()
{

	neighbors += texture2D(aTexture, vec2(gl_TexCoord[0].x - offset, gl_TexCoord[0].y)).r; //left
	neighbors += texture2D(aTexture, vec2(gl_TexCoord[0].x + offset, gl_TexCoord[0].y)).r; //right
	neighbors += texture2D(aTexture, vec2(gl_TexCoord[0].x, gl_TexCoord[0].y - offset)).r; //up
	neighbors += texture2D(aTexture, vec2(gl_TexCoord[0].x, gl_TexCoord[0].y + offset)).r; //down
	neighbors += texture2D(aTexture, vec2(gl_TexCoord[0].x - offset, gl_TexCoord[0].y - offset)).r; //left up
	neighbors += texture2D(aTexture, vec2(gl_TexCoord[0].x + offset, gl_TexCoord[0].y - offset)).r; //right up
	neighbors += texture2D(aTexture, vec2(gl_TexCoord[0].x - offset, gl_TexCoord[0].y + offset)).r; //left down
	neighbors += texture2D(aTexture, vec2(gl_TexCoord[0].x + offset, gl_TexCoord[0].y + offset)).r; //left up


	if(texture2D(aTexture, vec2(gl_TexCoord[0].x, gl_TexCoord[0].y)).r == 1.0){ //currently alive
		if(neighbors < 2.0 || neighbors > 3.0){ //dies
			gl_FragColor = vec4(0.0,0.172,0.172,1.0);
		}
		else{ //lives
			gl_FragColor = vec4(1.0,1.0,1.0,1.0);
		}
	}else{
		if(neighbors == 3.0){
			gl_FragColor = vec4(1.0,1.0,1.0,1.0);
		}
		else{
			gl_FragColor = vec4(0.0,0.172,0.172,1.0);
		}
	}
} 