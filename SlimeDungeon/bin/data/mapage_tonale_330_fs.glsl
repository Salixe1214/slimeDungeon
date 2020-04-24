// IFT3100H19 ~ image_tint_330_fs.glsl

#version 330

// attributs uniformes
uniform sampler2D image;

// attribut en entrée
in vec2 surface_texcoord;

// attribut en sortie
out vec4 fragment_color;

void main()
{
  vec3 x =  texture(image, vec2(surface_texcoord.x, surface_texcoord.y)).xyz;

  x = x / (x + vec3(1.0));
  fragment_color = vec4(1.0) - exp(-x.xyzz * 2.0);
  fragment_color.w = texture(image, vec2(surface_texcoord.x, surface_texcoord.y)).w;
}