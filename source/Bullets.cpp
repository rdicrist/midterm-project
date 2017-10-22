//
//  Bullets.cpp
//  ASTEROIDS
//
//  Created by Ricki DiCristoforo on 10/17/17.
//
//

#include "common.h"

/*
class Bullets{
public:

    Bullets(vec2 location, vec2 velocity){
            
        loc = location;
        //color is white
        color = vec3(1,1,1);
        vel = velocity;
        };
    vec2 loc;
    vec2 vel;
    vec3 color;
    };



    void init()
        {
            std::string vshader = shader_path + "vshader.glsl";
            std::string fshader = shader_path + "fshader.glsl";
            
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
            PM_location = glGetUniformLocation( program, "ProjectionModelview" );
            
            // Create a vertex array object
            glGenVertexArrays( 1, &vao );
            //Set GL state to use vertex array object
            glBindVertexArray( vao );
            
            //Generate buffer to hold our vertex data
            glGenBuffers( 1, &buffer );
            
            glEnableVertexAttribArray(vpos_location);
            glEnableVertexAttribArray( vcolor_location );
            
            glBindVertexArray(0);
            
    };*/

