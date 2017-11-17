//
//  Bullets.cpp
//  asteroids
//
//  Created by Ricki DiCristoforo on 10/23/17.
//

#include "common.h"



Bullets::Bullet::Bullet(vec2 loca, vec2 point){
    loc = loca;
    color = vec3(1,1,1);
    vel = point*.75;
    hit =false;
}
    
    
    
Bullets::Bullets(){};
Bullets::~Bullets(){
        for(unsigned int i=0; i < bullets.size(); i++)
            delete bullets[i];
        bullets.clear();
    }
    

    
    
    
void Bullets::init(){
        std::string vshader = shader_path + "vshader_ship.glsl";
        std::string fshader = shader_path + "fshader_ship.glsl";
        
        GLchar* vertex_shader_source = readShaderSource(vshader.c_str());
        GLchar* fragment_shader_source = readShaderSource(fshader.c_str());
        
        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, (const GLchar**) &vertex_shader_source, NULL);
        glCompileShader(vertex_shader);
        check_shader_compilation(vshader, vertex_shader);
        
        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, (const GLchar**) &fragment_shader_source, NULL);
        glCompileShader(fragment_shader);
        check_shader_compilation(fshader, fragment_shader);
        
        program = glCreateProgram();
        glAttachShader(program, vertex_shader);
        glAttachShader(program, fragment_shader);
        
        glLinkProgram(program);
        check_program_link(program);
        
        glBindFragDataLocation(program, 0, "fragColor");
        
        vpos_location   = glGetAttribLocation(program, "vPos");
        vcolor_location = glGetAttribLocation( program, "vColor" );
        
        // Create a vertex array object
        glGenVertexArrays( 1, &vao );
        //Set GL state to use vertex array object
        glBindVertexArray( vao );
        
        //Generate buffer to hold our vertex data
        glGenBuffers( 1, &buffer );
        
        glEnableVertexAttribArray(vpos_location);
        glEnableVertexAttribArray( vcolor_location );
        
        glBindVertexArray(0);
        
    };
    
void Bullets::update(){
        
        vec2 *pos = new vec2[bullets.size()];
        vec3 *col = new vec3[bullets.size()];
        
        for(unsigned int i=0; i < bullets.size(); i++){
            pos[i] = bullets[i]->loc;
            col[i] = bullets[i]->color;
        }
        
        //Set GL state to use this buffer
        glBindBuffer( GL_ARRAY_BUFFER, buffer );
        
        //Create GPU buffer to hold vertices and color
        glBufferData( GL_ARRAY_BUFFER, bullets.size()*sizeof(vec2) + bullets.size() *sizeof(vec3), NULL, GL_STATIC_DRAW );
        //First part of array holds vertices
        glBufferSubData( GL_ARRAY_BUFFER, 0, bullets.size()*sizeof(vec2), pos );
        //Second part of array hold colors (offset by sizeof(triangle))
        glBufferSubData( GL_ARRAY_BUFFER, bullets.size()*sizeof(vec2), bullets.size()*sizeof(vec3), col );
        
        glVertexAttribPointer( vpos_location, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
        glVertexAttribPointer( vcolor_location, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(bullets.size()*sizeof(vec2)) );
        
        glBindBuffer( GL_ARRAY_BUFFER, 0 );
        
        delete[] pos;
        delete[] col;
    
    };
    
    
void Bullets::step(float width, float height){
        //Code changes here
        for (std::vector< Bullet * >::iterator it = bullets.begin() ; it != bullets.end(); ++it){
            (*it)->loc += (*it)->vel;
            
            //deletes if it goes off the stage
            if ((*it)->loc.y <= -height || (*it)->loc.y <= height || (*it)->loc.x <= -width || (*it)->loc.x >= width ){
                delete *it;
                it = bullets.erase(it);
                break;
            }
            
            
        }
    
    }

void Bullets::draw(mat4 proj){
        glPointSize(5);
        
        glUseProgram(program);
        glBindVertexArray(vao);
        update();
        glUniformMatrix4fv( PM_location, 1, GL_TRUE, proj);
        glDrawArrays(GL_POINTS, 0, bullets.size());
        
}

void Bullets::update_state(){
    for(int i = 0;i<bullets.size();i++){
        bullets[i]->loc+=bullets[i]->vel;
    }
}


void Bullets::clean_bullets(){
    std::vector< Bullet * > temp;
    for (int i = 0; i < bullets.size(); i++){
        if (!bullets[i]->hit){
            temp.push_back(bullets[i]);
        }
    }
    bullets = temp;
}




