#version 450 compatibility

out vec4 FragColor;
  
in vec2 TexCoord;

uniform sampler2D ourTexture;


void main()
{   
    vec4 tex_col = texture(ourTexture, TexCoord);

    FragColor.rgba = tex_col.rgba;
}