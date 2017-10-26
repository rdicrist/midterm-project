//
//  Bullets.h
//  ASTEROIDS
//
//  Created by Ricki DiCristoforo on 10/24/17.
//

#ifndef Bullets_h
#define Bullets_h
#include "common.h"


class Bullets {
public:
    class Bullet {
    public:
        vec2 loc;
        vec2 vel;
        vec3 color;
        Bullet(vec2 loca, vec2 point);
    };
    
    std::vector < Bullet * > bullets;
    
    Bullets();
    ~Bullets();
    
    GLuint vao;
    GLuint program;
    GLuint buffer;
    GLuint vertex_shader, fragment_shader;
    GLint vpos_location, vcolor_location;
    GLint PM_location;
    
    void init();
    void update();
    void step(float width, float height);
    void draw(mat4 proj);
    void update_state();
    
};




#endif /* Bullets_h */
