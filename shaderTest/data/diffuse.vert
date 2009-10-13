
//varying vec3 normal;
//  varying vec2  TexCoord;
  void main(void)
  {
          gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
          gl_Position = ftransform();   
  }

