//
//  Bullets.h
//  ASTEROIDS
//
//  Created by Ricki DiCristoforo on 10/16/17.
//
//

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "common/Angel.h"
#include "shader.h"

#include <stdlib.h>
#include <stdio.h>
#include <vector>

#ifndef Bullets_h
#define Bullets_h

#include "common.h"

class Bullets {
    
    
    GLuint vao;
    GLuint program;
    GLuint buffer;
    GLuint vertex_shader, fragment_shader;
    GLint vpos_location, vcolor_location;
    GLint PM_location;
    
public:
    Bullets(vec2 location, vec2 velocity);
    
    void init();
    
    
    
};


#endif /* Bullets_h */
