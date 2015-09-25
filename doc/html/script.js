
var main=function() {
  var CANVAS=document.getElementById("your_canvas");
  CANVAS.width=window.innerWidth;
  CANVAS.height=window.innerHeight;

  /*========================= CAPTURE MOUSE EVENTS ========================= */

  var AMORTIZATION=0.95;
  var drag=false;
  var old_x, old_y;
  var dX=0, dY=0;

  var mouseDown=function(e) {
    drag=true;
    old_x=e.pageX, old_y=e.pageY;
    e.preventDefault();
    return false;
  };

  var mouseUp=function(e){
    drag=false;
  };

  var mouseMove=function(e) {
    if (!drag) return false;
    dX=(e.pageX-old_x)*Math.PI/CANVAS.width,
      dY=(e.pageY-old_y)*Math.PI/CANVAS.height;
    THETA+=dX;
    PHI+=dY;
    old_x=e.pageX, old_y=e.pageY;
    e.preventDefault();
  };

  CANVAS.addEventListener("mousedown", mouseDown, false);
  CANVAS.addEventListener("mouseup", mouseUp, false);
  CANVAS.addEventListener("mouseout", mouseUp, false);
  CANVAS.addEventListener("mousemove", mouseMove, false);

  /*========================= GET WEBGL CONTEXT ========================= */
  var GL;
  try {
    GL = CANVAS.getContext("experimental-webgl", {antialias: true});
  } catch (e) {
    alert("You are not webgl compatible :(") ;
    return false;
  }

  /*========================= SHADERS ========================= */
  /*jshint multistr: true */

  var shader_vertex_source="\n\
attribute vec3 position;\n\
uniform mat4 Pmatrix;\n\
uniform mat4 Vmatrix;\n\
uniform mat4 Mmatrix;\n\
attribute vec2 uv;\n\
varying vec2 vUV;\n\
void main(void) { //pre-built function\n\
gl_Position = Pmatrix*Vmatrix*Mmatrix*vec4(position, 1.);\n\
vUV=uv;\n\
}";

  var shader_fragment_source="\n\
precision highp float;\n\
uniform sampler2D sampler;\n\
uniform float time;\n\
varying vec2 vUV;\n\
#define MAX_ITER 5\n\
\n\
vec3 sunsetGrad( ) {\n\
	vec2 sp = vUV;//vec2(.4, .7);\n\
        sp -= vec2(0.5,0.5);\n\
	vec2 p = sp*10.80;\n\
	vec2 i = p;\n\
	float c = 0.16;\n\
	\n\
	float inten = 0.51;\n\
\n\
	for (int n = 0; n < MAX_ITER; n++) \n\
	{\n\
		float t = time * (1.0 - (20.0 / float(n+1)));\n\
		//float t = time;\n\
		i = p + vec2(cos(t - i.x) + sin(t + i.y), sin(t - i.y) + cos(t + i.x));\n\
		c += 1.0/length(vec2(p.x / (sin(i.x+t)/inten),p.y / (cos(i.y+t)/inten)));\n\
	}\n\
	c /= float(MAX_ITER);\n\
	c = 1.5-sqrt(c);\n\
	vec4 k = vec4(vec3(c*c*c*c), 99.0) + vec4(1.0, 0.1, 0.1, 1.0);\n\
	float kk = mix( 0.0, 1.0, k.x*.25 + 0.25 * cos(time+sin(time*2.)) );\n\
	\n\
	float r = kk*2.-.1; \n\
	float g = 1.-(1.-kk)*2.; \n\
	float b = sin( (min(kk,.5)*3.-.33) * 3.1415926);\n\
	return( vec3( r, g,b ) );\n\
}\n\
\n\
void main(void) {\n\
   vec4 sunset = vec4(sunsetGrad(),1.0);\n\
   gl_FragColor = texture2D(sampler, vUV) + sunset;\n\
}";




  var get_shader=function(source, type, typeString) {
    var shader = GL.createShader(type);
    GL.shaderSource(shader, source);
    GL.compileShader(shader);
    if (!GL.getShaderParameter(shader, GL.COMPILE_STATUS)) {
      alert("ERROR IN "+typeString+ " SHADER : " + GL.getShaderInfoLog(shader));
      return false;
    }
    return shader;
  };

  var shader_vertex=get_shader(shader_vertex_source, GL.VERTEX_SHADER, "VERTEX");
  var shader_fragment=get_shader(shader_fragment_source, GL.FRAGMENT_SHADER, "FRAGMENT");

  var SHADER_PROGRAM=GL.createProgram();
  GL.attachShader(SHADER_PROGRAM, shader_vertex);
  GL.attachShader(SHADER_PROGRAM, shader_fragment);

  GL.linkProgram(SHADER_PROGRAM);

  var _Pmatrix = GL.getUniformLocation(SHADER_PROGRAM, "Pmatrix");
  var _Vmatrix = GL.getUniformLocation(SHADER_PROGRAM, "Vmatrix");
  var _Mmatrix = GL.getUniformLocation(SHADER_PROGRAM, "Mmatrix");
  var _time = GL.getUniformLocation(SHADER_PROGRAM, "time");

  var _sampler = GL.getUniformLocation(SHADER_PROGRAM, "sampler");
  var _uv = GL.getAttribLocation(SHADER_PROGRAM, "uv");
  var _position = GL.getAttribLocation(SHADER_PROGRAM, "position");

  GL.enableVertexAttribArray(_uv);
  GL.enableVertexAttribArray(_position);

  GL.useProgram(SHADER_PROGRAM);
  GL.uniform1i(_sampler, 0);

  /*========================= THE CUBE ========================= */
  //POINTS :
  var cube_vertex=[
    -1,-1,-1,    0,0,
    1,-1,-1,     0,1,
    1, 1,-1,     1,1,
    -1, 1,-1,    1,0,

    -1,-1, 1,    0,0,
    1,-1, 1,     0,1,
    1, 1, 1,     1,1,
    -1, 1, 1,    1,0,

    -1,-1,-1,    0,0,
    -1, 1,-1,    0,1,
    -1, 1, 1,    1,1,
    -1,-1, 1,    1,0,

    1,-1,-1,     0,0,
    1, 1,-1,     0,1,
    1, 1, 1,     1,1,
    1,-1, 1,     1,0,

    -1,-1,-1,    0,0,
    -1,-1, 1,    0,1,
    1,-1, 1,     1,1,
    1,-1,-1,     1,0,

    -1, 1,-1,    0,0,
    -1, 1, 1,    0,1,
    1, 1, 1,     1,1,
    1, 1,-1,     1,0
  ];

  var CUBE_VERTEX= GL.createBuffer ();
  GL.bindBuffer(GL.ARRAY_BUFFER, CUBE_VERTEX);
  GL.bufferData(GL.ARRAY_BUFFER,
                new Float32Array(cube_vertex),
    GL.STATIC_DRAW);

  //FACES :
  var cube_faces = [
    0,1,2,
    0,2,3,

    4,5,6,
    4,6,7,

    8,9,10,
    8,10,11,

    12,13,14,
    12,14,15,

    16,17,18,
    16,18,19,

    20,21,22,
    20,22,23

  ];
  var CUBE_FACES= GL.createBuffer ();
  GL.bindBuffer(GL.ELEMENT_ARRAY_BUFFER, CUBE_FACES);
  GL.bufferData(GL.ELEMENT_ARRAY_BUFFER,
                new Uint16Array(cube_faces),
    GL.STATIC_DRAW);

  /*========================= MATRIX ========================= */

  var PROJMATRIX=LIBS.get_projection(40, CANVAS.width/CANVAS.height, 1, 100);
  var MOVEMATRIX=LIBS.get_I4();
  var VIEWMATRIX=LIBS.get_I4();

  LIBS.translateZ(VIEWMATRIX, -6);
  var THETA=0,
      PHI=0;

  /*========================= TEXTURES ========================= */
  var get_texture=function(image_URL){


    var image=new Image();

    image.src=image_URL;
    image.webglTexture=false;


    image.onload=function(e) {



      var texture=GL.createTexture();

      GL.pixelStorei(GL.UNPACK_FLIP_Y_WEBGL, true);


      GL.bindTexture(GL.TEXTURE_2D, texture);

      GL.texImage2D(GL.TEXTURE_2D, 0, GL.RGBA, GL.RGBA, GL.UNSIGNED_BYTE, image);

      GL.texParameteri(GL.TEXTURE_2D, GL.TEXTURE_MAG_FILTER, GL.LINEAR);

      GL.texParameteri(GL.TEXTURE_2D, GL.TEXTURE_MIN_FILTER, GL.LINEAR);

      GL.bindTexture(GL.TEXTURE_2D, null);

      image.webglTexture=texture;
    };

    return image;
  };

  var cube_texture=get_texture("logo.png");


  /*========================= DRAWING ========================= */
  GL.enable(GL.DEPTH_TEST);
  GL.depthFunc(GL.LEQUAL);
  GL.clearColor(0.0, 0.0, 0.0, 0.0);
  GL.clearDepth(1.0);

  var time_old=0;
  var animate=function(time) {
    var dt=time-time_old;
    if (!drag) {
      dX*=AMORTIZATION, dY*=AMORTIZATION;
      THETA+=dX, PHI+=dY;
    }
    LIBS.rotateZ(MOVEMATRIX, dt*0.0001);
    LIBS.rotateY(MOVEMATRIX, dt*0.0002);
    LIBS.rotateX(MOVEMATRIX, dt*0.0003)
    time_old=time;

    GL.viewport(0.0, 0.0, CANVAS.width, CANVAS.height);
    GL.clear(GL.COLOR_BUFFER_BIT | GL.DEPTH_BUFFER_BIT);
    GL.uniformMatrix4fv(_Pmatrix, false, PROJMATRIX);
    GL.uniformMatrix4fv(_Vmatrix, false, VIEWMATRIX);
    GL.uniformMatrix4fv(_Mmatrix, false, MOVEMATRIX);
    GL.uniform1f(_time, time/1000.0);
    if (cube_texture.webglTexture) {

      GL.activeTexture(GL.TEXTURE0);

      GL.bindTexture(GL.TEXTURE_2D, cube_texture.webglTexture);
    }
    GL.bindBuffer(GL.ARRAY_BUFFER, CUBE_VERTEX);
    GL.vertexAttribPointer(_position, 3, GL.FLOAT, false,4*(3+2),0) ;
    GL.vertexAttribPointer(_uv, 2, GL.FLOAT, false,4*(3+2),3*4) ;

    GL.bindBuffer(GL.ELEMENT_ARRAY_BUFFER, CUBE_FACES);
    GL.drawElements(GL.TRIANGLES, 6*2*3, GL.UNSIGNED_SHORT, 0);

    GL.flush();
    window.requestAnimationFrame(animate);
  };
  animate(0);
};
