// #extension GL_ARB_texture_rectangle : require
//varying vec3 normal;
//  varying vec2  TexCoord;
  void main(void)
  {
          //gl_TexCoord[0] = gl_MultiTexCoord0.st;
          gl_TexCoord[0] = gl_MultiTexCoord0;
          // gl_TexCoord[0].xy = gl_MultiTexCoord0.xy;
          gl_Position = ftransform();   
  }

