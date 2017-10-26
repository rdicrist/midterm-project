//
//  Asteroids.h
//  ASTEROIDS
//
//  Created by Ricki DiCristoforo on 10/25/17.
//

#ifndef Asteroids_h
#define Asteroids_h

#include "common.h"


class Asteroids {
    
    
    
public:
    class Asteroid {
        vec2 ast_vert[12] = {vec2(1.32,-1.18), vec2(2.50,-1.12), vec2(3.27,1.02), vec2(1.38,1.35), vec2(2.42,2.51), vec2(-0.04,3.04), vec2(-1.74,1.26), vec2(-2.70,1.35), vec2(-3.05,-0.08), vec2(-1.78,-0.83), vec2(-2.75,-2.18), vec2(-0.03,-2.43)};
        vec3 ast_color[12] = {vec3(1,1,1), vec3(1,1,1), vec3(1,1,1), vec3(1,1,1), vec3(1,1,1), vec3(1,1,1), vec3(1,1,1), vec3(1,1,1), vec3(1,1,1), vec3(1,1,1), vec3(1,1,1), vec3(1,1,1)};
    public:
        vec2 loc;
        vec2 vel;
        float scale; 
        Asteroid();
        Asteroid(vec2 loca, vec2 velo);
        
        void init2();
        void drawOne(mat4 proj);
         void update();
        void update_state2();
        //void split(mat4 proj);
        
        GLuint vao2;
        GLuint program2;
        GLuint buffer2;
        GLuint vertex_shader2, fragment_shader2;
        GLint vpos_location2, vcolor_location2;
        GLint PM_location2;
    };
    
    std::vector < Asteroid * > asteroids;
    
    Asteroids();
    ~Asteroids();
    
    GLuint vao;
    GLuint program;
    GLuint buffer;
    GLuint vertex_shader, fragment_shader;
    GLint vpos_location, vcolor_location;
    GLint PM_location;
    
    void init();
   
    void step(float width, float height);
    void draw(mat4 proj);
    void update_state();
    void split(mat4 proj);
    Asteroids::Asteroid createNew();
    
    //
    void checkIfHit(vec2 point);
    
    int getLength();
    
    
    
};

#endif /* Asteroids_h */
