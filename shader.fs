//#version 330

//in vec4 Color;

//out vec4 FragColor;

//void main()
//{
//    FragColor = Color;
//}

#version 330

in vec2 TexCoord0;

out vec4 FragColor;

uniform sampler2D gSampler;

void main()
{
    FragColor = texture2D(gSampler, TexCoord0.st);
};
