#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect tex;
varying vec3 normal;


void main( void )
{   
vec4 baseColor = vec4(0.0, 0.0, 0.0, 1.0);
	
	float ddy = 15.0;
	float ddx = 15.0;
 
  // Horizontal blur
  baseColor += 0.015625 * texture2DRect(tex, gl_TexCoord[0].st + vec2(0.0, ddy*-3.0) );
  baseColor += 0.09375 * texture2DRect(tex, gl_TexCoord[0].st + vec2(0.0, ddy*-2.0) );
  baseColor += 0.234375 * texture2DRect(tex, gl_TexCoord[0].st + vec2(0.0, ddy*-1.0) );
  baseColor += 0.3125 * texture2DRect(tex, gl_TexCoord[0].st + vec2(0.0, 0.0) );
  baseColor += 0.234375 * texture2DRect(tex, gl_TexCoord[0].st + vec2(0.0, ddy*1.0) );
  baseColor += 0.09375 * texture2DRect(tex, gl_TexCoord[0].st + vec2(0.0, ddy*2.0) );
  baseColor += 0.015625 * texture2DRect(tex, gl_TexCoord[0].st + vec2(0.0, ddy*3.0) );
  
  // Vertical blur
  baseColor += 0.015625 * texture2DRect(tex, gl_TexCoord[0].st + vec2(ddx*-3.0, 0.0) );
  baseColor += 0.09375 * texture2DRect(tex, gl_TexCoord[0].st + vec2(ddx*-2.0, 0.0) );
  baseColor += 0.234375 * texture2DRect(tex, gl_TexCoord[0].st + vec2(ddx*-1.0, 0.0) );
  baseColor += 0.3125 * texture2DRect(tex, gl_TexCoord[0].st + vec2(0.0, 0.0) );
  baseColor += 0.234375 * texture2DRect(tex, gl_TexCoord[0].st + vec2(ddx*1.0, 0.0) );
  baseColor += 0.09375 * texture2DRect(tex, gl_TexCoord[0].st + vec2(ddx*2.0, 0.0) );
  baseColor += 0.015625 * texture2DRect(tex, gl_TexCoord[0].st + vec2(ddx*3.0, 0.0) );
  
  // Mix both
  baseColor *= 0.5;
  vec4 color = texture2DRect(tex,gl_TexCoord[0].st + vec2( 100, 109) );
 
  //baseColor.a = 1.0;
  //baseColor.r= 1; 
      
  gl_FragColor = baseColor; //color; // baseColor * 0.2; // * color; // texture2DRect( tex, gl_TexCoord[0].xy );

//    gl_FragColor= vec4(normal, 1.0); // * baseColor;
}

