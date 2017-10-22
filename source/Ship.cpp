 //
//  Ship.cpp
//  Asteroids
//
//  Created by Brian Summa on 6/5/15.
//
//

#include "common.h"
#include "Bullets.cpp"

Ship::Ship(){
  //!!!!!!!!Your initial state might be different depending on how you
  //pick your world coordinates
  state.cur_location = vec2(0.0,0.0);
  state.pointing = vec2(0.0,1.0); //same as angle
  state.move = vec2(0.0,0.0);
  state.thruster_on = false;
  state.angle = 0.0; //same as pointing
};


void Ship::update_state(){
  if(state.thruster_on){
    //!!!!!!!!Accelerate if the thruster is on
    //!!!!!!!!Clamp acceleration at some maximum value
      state.move += 0.3*state.pointing;
      
      if(length(state.move) > 2.0) {
          state.move = normalize(state.move);
          state.move *= 2.0;
      }
  }
  
  //!!!!!!!!Dampen the velocity at every timestep to lessen intertia
  //!!!!!!!!Move the ship location
    
    state.move*=0.8;
    state.cur_location+=state.move;
    
  //Wrap the ship position when at the boundary
  //!!!!!!!!This will change depending on the world coordinates you are using
  if(state.cur_location.x < -width || state.cur_location.x > width){
    state.cur_location.x = -state.cur_location.x;
  }
  if(state.cur_location.y < -height ||state.cur_location.y > height){
    state.cur_location.y = -state.cur_location.y;
  }

}


void Ship::gl_init(){
  //Ship
  //!!!!!!!!Populate ship_vert and ship_color
    
    ship_vert[0] = vec2(0,1);
    ship_vert[1] = vec2(-.5, -1);
    ship_vert[2] = vec2(0,-.5);
    ship_vert[3] = vec2(.5,-1);
    ship_vert[4] = vec2(0,1);
    
    ship_color[0] = vec3(1,1,1);
    ship_color[1] = vec3(1,1,1);
    ship_color[2] = vec3(1,1,1);
    ship_color[3] = vec3(1,1,1);
    ship_color[4] = vec3(1,1,1);
    
    //for thruster, draw flame
    ship_vert[5] = vec2(0, -.5);
    ship_vert[6] = vec2(-.2, -1);
    ship_vert[7] = vec2(.2, -1);
    ship_vert[8] = vec2(0, -.5);
    
    ship_color[5] = vec3(1,0,0);
    ship_color[6] = vec3(1,0,0);
    ship_color[7] = vec3(1,0,0);
    ship_color[8] = vec3(1,0,0);
    
    
    
  
  std::string vshader = shader_path + "vshader_Ship.glsl";
  std::string fshader = shader_path + "fshader_Ship.glsl";
  
  GLchar* vertex_shader_source = readShaderSource(vshader.c_str());
  GLchar* fragment_shader_source = readShaderSource(fshader.c_str());
  
  GLvars.vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(GLvars.vertex_shader, 1, (const GLchar**) &vertex_shader_source, NULL);
  glCompileShader(GLvars.vertex_shader);
  check_shader_compilation(vshader, GLvars.vertex_shader);
  
  GLvars.fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(GLvars.fragment_shader, 1, (const GLchar**) &fragment_shader_source, NULL);
  glCompileShader(GLvars.fragment_shader);
  check_shader_compilation(fshader, GLvars.fragment_shader);
  
  GLvars.program = glCreateProgram();
  glAttachShader(GLvars.program, GLvars.vertex_shader);
  glAttachShader(GLvars.program, GLvars.fragment_shader);
  
  glLinkProgram(GLvars.program);
  check_program_link(GLvars.program);
  
  glBindFragDataLocation(GLvars.program, 0, "fragColor");
  
  GLvars.vpos_location   = glGetAttribLocation(GLvars.program, "vPos");
  GLvars.vcolor_location = glGetAttribLocation(GLvars.program, "vColor" );
  GLvars.M_location = glGetUniformLocation(GLvars.program, "M" );
  
  // Create a vertex array object
  glGenVertexArrays( 1, &GLvars.vao );
  //Set GL state to use vertex array object
  glBindVertexArray( GLvars.vao );
  
  //Generate buffer to hold our vertex data
  glGenBuffers( 1, &GLvars.buffer );
  //Set GL state to use this buffer
  glBindBuffer( GL_ARRAY_BUFFER, GLvars.buffer );
  
  //Create GPU buffer to hold vertices and color
  glBufferData( GL_ARRAY_BUFFER, sizeof(ship_vert) + sizeof(ship_color), NULL, GL_STATIC_DRAW );
  //First part of array holds vertices
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(ship_vert), ship_vert );
  //Second part of array hold colors (offset by sizeof(triangle))
  glBufferSubData( GL_ARRAY_BUFFER, sizeof(ship_vert), sizeof(ship_color), ship_color );
  
  glEnableVertexAttribArray(GLvars.vpos_location);
  glEnableVertexAttribArray(GLvars.vcolor_location );
  
  glVertexAttribPointer( GLvars.vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
  glVertexAttribPointer( GLvars.vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(ship_vert)) );
  
  glBindVertexArray(0);

}

void Ship::draw(mat4 proj){
  
  glUseProgram( GLvars.program );
  glBindVertexArray( GLvars.vao );
    
    mat4 mv = Angel::Translate(state.cur_location.x, state.cur_location.y, 0.0) * Angel::RotateZ(state.angle);
  
  //!!!!!!!!Create a modelview matrix and pass it
  glUniformMatrix4fv( GLvars.M_location, 1, GL_TRUE, proj *mv );
    
    
    
    
    //draws it RICKI DID
    glDrawArrays(GL_LINE_LOOP, 0, 5);
  
  //!!!!!!!!Draw something
  
  if(state.thruster_on){
    //!!!!!!!!Maybe draw something different if the thruster is on
      //where it starts (5), the length of the points(4)
      glDrawArrays(GL_TRIANGLE_STRIP, 5, 4);
  }
  
  glBindVertexArray(0);
  glUseProgram(0);

}

/*Bullets Ship::fire(){
    //create a bullet here
    Bullets bullet = *new Bullets (state.cur_location, state.move);
    return bullet;
}*/

