out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D aTexture;

void main()
{
	gl_FragColor = texture2D(aTexture,gl_TexCoord[0].xy) * vec4(1.0,0.5,0.5,1.0);
} 