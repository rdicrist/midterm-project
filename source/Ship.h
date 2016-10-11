//
//  Ship.h
//  Asteroids
//
//  Created by Brian Summa on 6/5/15.
//
//

#ifndef __Asteroids__Ship__
#define __Asteroids__Ship__

#include "common.h"

#define _MAX_SPEED 10
#define _DAMPING 0.98
#define _ACC 3
#define _ROT 15

class Ship{

  vec2 ship_vert[6];
  vec3 ship_color[6];
  
  float width, height;
  
  
  //Ship State
  struct {
    vec2 cur_location;
    vec2 pointing;
    vec2 move;
    bool thruster_on;
    float angle;
  } state;
  
  //OpenGL vars
  struct {
    GLuint vao;
    GLuint program;
    GLuint buffer;
    GLuint vertex_shader, fragment_shader;
    GLint vpos_location, vcolor_location;
    GLint M_location;
  } GLvars;
  
  
  mat2 RotateZ2D( const GLfloat theta ){
    GLfloat angle = DegreesToRadians * theta;
    mat2 c;
    c[0][0] = c[1][1] = cos(angle);
    c[1][0] = sin(angle);
    c[0][1] = -c[1][0];
    return c;
  }
  
public:
  

  Ship();
  
  inline void start_thruster(){ state.thruster_on= true;}
  inline void stop_thruster() { state.thruster_on= false;}

  inline void rotateLeft() {  state.angle-=_ROT;   state.pointing =  RotateZ2D(state.angle) * vec2(0.0,-1.0);}
  inline void rotateRight(){  state.angle+=_ROT;   state.pointing =  RotateZ2D(state.angle) * vec2(0.0,-1.0);}
    
  void update_state();
  
  void gl_init();  
  
  void draw(mat4 proj);
  
  void set_extents(int w, int h){
    width  = w/2;
    height = h/2;
  }
};


#endif /* defined(__Asteroids__Ship__) */
