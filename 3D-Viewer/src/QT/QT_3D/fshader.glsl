#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

// uniform sampler2D texture;
uniform mediump vec4 color;

//varying vec2 v_texcoord;

//! [0]
void main()
{
    // Set color
    gl_FragColor = color;
    // Set fragment color from texture
    // gl_FragColor = texture2D(texture, v_texcoord);
}
//! [0]
