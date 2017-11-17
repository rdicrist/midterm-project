//
//  Asteroids.cpp
//  asteroids
//
//  Created by Ricki DiCristoforo on 10/25/17.
//

#include "common.h"



Asteroids::Asteroid::Asteroid(){

    int ran = rand()%4;
    if (ran == 0){
        loc = vec2(20, rand()%20);
    }
    else if (ran == 1){
        loc = vec2(-20, rand()%20);
    }
    else if (ran == 2){
        loc = vec2(rand()%20, 20);
    }
    else if (ran == 3){
        loc = vec2(rand()%20, -20);
    }
    
    //loc = vec2(rand()%40-20, rand()%40-20);
    //color = vec3(1,1,1);
    vel = vec2(rand()/(float)RAND_MAX * (.1 - -.1) + (-.1), rand()/(float)RAND_MAX * (.1 - -.1) + (-.1));
    //vel = vec2(1,1);
    scale = 1; 
}

Asteroids::Asteroid::Asteroid(vec2 loca, vec2 velo){
    loc = loca;
    //color = vec3(1,1,1);
    vel = velo;
}



void Asteroids::Asteroid::init2(){
    
    std::string vshader = shader_path + "vshader_Ship.glsl";
    std::string fshader = shader_path + "fshader_Ship.glsl";
    
    GLchar* vertex_shader_source = readShaderSource(vshader.c_str());
    GLchar* fragment_shader_source = readShaderSource(fshader.c_str());
    
    vertex_shader2 = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader2, 1, (const GLchar**) &vertex_shader_source, NULL);
    glCompileShader(vertex_shader2);
    check_shader_compilation(vshader, vertex_shader2);
    
    fragment_shader2 = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader2, 1, (const GLchar**) &fragment_shader_source, NULL);
    glCompileShader(fragment_shader2);
    check_shader_compilation(fshader, fragment_shader2);
    
    program2 = glCreateProgram();
    glAttachShader(program2, vertex_shader2);
    glAttachShader(program2, fragment_shader2);
    
    glLinkProgram(program2);
    check_program_link(program2);
    
    glBindFragDataLocation(program2, 0, "fragColor");
    
    vpos_location2   = glGetAttribLocation(program2, "vPos");
    vcolor_location2 = glGetAttribLocation(program2, "vColor" );
    PM_location2 = glGetUniformLocation(program2, "M" );
    
    // Create a vertex array object
    glGenVertexArrays( 1, &vao2 );
    //Set GL state to use vertex array object
    glBindVertexArray( vao2 );
    
    //Generate buffer to hold our vertex data
    glGenBuffers( 1, &buffer2 );
    //Set GL state to use this buffer
    glBindBuffer( GL_ARRAY_BUFFER, buffer2 );
    
    //Create GPU buffer to hold vertices and color
    glBufferData( GL_ARRAY_BUFFER, sizeof(ast_vert) + sizeof(ast_color), NULL, GL_STATIC_DRAW );
    //First part of array holds vertices
    glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(ast_vert), ast_vert );
    //Second part of array hold colors (offset by sizeof(triangle))
    glBufferSubData( GL_ARRAY_BUFFER, sizeof(ast_vert), sizeof(ast_color), ast_color );
    
    glEnableVertexAttribArray(vpos_location2);
    glEnableVertexAttribArray(vcolor_location2 );
    
    glVertexAttribPointer( vpos_location2, 2, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0) );
    glVertexAttribPointer( vcolor_location2, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(sizeof(ast_vert)) );
    
    glBindVertexArray(0);

    
};

void Asteroids::Asteroid::drawOne(mat4 proj){
    
    glUseProgram( program2 );
    glBindVertexArray( vao2 );
    mat4 mvv = Angel::Scale(scale,scale, 0);
    //mat4 scale = Angel::Scale(scale, scale, 0);
    mat4 mv = Angel::Translate(loc.x, loc.y, 0.0);
    
    glUniformMatrix4fv( PM_location2, 1, GL_TRUE, proj * mv * mvv );
    glDrawArrays(GL_TRIANGLE_FAN, 0, 12);
    glBindVertexArray(0);
    glUseProgram(0);
    /*
     //for the point
     glPointSize(50);
     
     glUseProgram(program);
     glBindVertexArray(vao);
     update();
     glUniformMatrix4fv( PM_location, 1, GL_TRUE, proj);
     glDrawArrays(GL_POINTS, 0, asteroids.size());
     */
    
}

void Asteroids::Asteroid::update_state2(){
    loc += vel;
    
    if(loc.x < -20 || loc.x > 20){
        loc.x = -loc.x;
        //asteroids[i]-> loc.x*(-1);
    }
    if(loc.y < -20 ||loc.y > 20){
        loc.y = -loc.y;
        //asteroids[i]-> loc.y*(-1);
    }
    
    
}

Asteroids::Asteroids(){};
Asteroids::~Asteroids(){
    for(unsigned int i=0; i < asteroids.size(); i++)
        delete asteroids[i];
    asteroids.clear();
}

void Asteroids::init(){
    for(int i = 0;i<asteroids.size();i++){
        asteroids[i]->init2();
    }
}

void Asteroids::draw(mat4 proj){
    for(int i = 0;i<asteroids.size();i++){
        asteroids[i]->drawOne(proj);
    }
}


//void Asteroids::step(float width, float height){
//
//    for (std::vector< Asteroid * >::iterator it = asteroids.begin() ; it != asteroids.end(); ++it){
//        (*it)->loc += (*it)->vel;
//
//        //parameters for the bounds to make it bounce
//        if ((*it)->loc.y <= -height || (*it)->loc.y <= height || (*it)->loc.x <= -width || (*it)->loc.x >= width ){
//            delete *it;
//            it = asteroids.erase(it);
//            break;
//        }
//
//
//    }
//    
//}



void Asteroids::update_state(){
    for(int i = 0;i<asteroids.size();i++){
        
        asteroids[i]->loc+=asteroids[i]->vel;
        
        
        if(asteroids[i]->loc.x < -20 || asteroids[i]->loc.x > 20){
            asteroids[i]->loc.x = -asteroids[i]->loc.x;
            //asteroids[i]-> loc.x*(-1);
        }
        if(asteroids[i]->loc.y < -20 ||asteroids[i]->loc.y > 20){
            asteroids[i]->loc.y = -asteroids[i]->loc.y;
            //asteroids[i]-> loc.y*(-1);
        }
    }
}

bool Asteroids::split( vec2 point){
    
    struct tBoundingBox
    {
        vec2       max;
        vec2       min;
    };
    
    tBoundingBox     boxArray[1];
    
    boxArray[0].min.x  = -3.05;
    boxArray[0].max.x  = 3.27;
    boxArray[0].min.y  = -2.43;
    boxArray[0].max.y  = 3.04;
    
    std::vector< Asteroid * > temp;
    bool hit = false;
    
    for (std::vector< Asteroid * >::iterator it = asteroids.begin() ; it != asteroids.end(); ++it){
        
        if (point.x >  ((*it)->scale*boxArray[0].max.x+(*it)->loc.x) ||
            point.x < ((*it)->scale*boxArray[0].min.x+(*it)->loc.x) ||
            point.y > ((*it)->scale*boxArray[0].max.y+(*it)->loc.y) ||
            point.y < ((*it)->scale*boxArray[0].min.y+(*it)->loc.y)){
            temp.push_back(*it);
        }
    
            else if ((*it)->scale <= .125 ){
                hit = true;
            }
        
            else {

                (*it)->scale *= .5;

                //mat4 mv = Angel::Scale((*it)->scale, (*it)->scale, 0);

                Asteroids::Asteroid * a = new Asteroids::Asteroid((*it)->loc, (*it)->vel*-1);
                Asteroids::Asteroid * b= new Asteroids::Asteroid((*it)->loc, (*it)->vel);

                a->scale = (*it)->scale;
                a->init2();

                //a.drawOne(proj * mv);

                b->scale = (*it)->scale;
                b->init2();

                //b.drawOne(proj * mv);

                temp.push_back(a);
                temp.push_back(b);
                hit = true;
            }
        
    }

    asteroids = temp;
    return hit;
    
    
    

    /////////////////
}
//
void Asteroids::deleteIfHit(vec2 point){
    
    //mins and max
    //y: -2.43  3.04
    //x: -3.05  3.27
    
    struct tBoundingBox
    {
        vec2       max;
        vec2       min;
    };
    
    tBoundingBox     boxArray[1];
    
    boxArray[0].min.x  = -3.05;
    boxArray[0].max.x  = 3.27;
    boxArray[0].min.y  = -2.43;
    boxArray[0].max.y  = 3.04;
    
    std::vector< Asteroid * > temp;
    
    for (std::vector< Asteroid * >::iterator it = asteroids.begin() ; it != asteroids.end(); ++it){
        
        boxArray[0].min.x  *= (*it)->scale;
        boxArray[0].max.x  *= (*it)->scale;
        boxArray[0].min.y  *= (*it)->scale;
        boxArray[0].max.y  *= (*it)->scale;
        
        if (point.x > (boxArray[0].max.x+(*it)->loc.x) || (point.x < boxArray[0].min.x+(*it)->loc.x) || (point.y > boxArray[0].max.y+(*it)->loc.y) || (point.x < boxArray[0].min.y+(*it)->loc.x)){
            temp.push_back(*it);
        }else{
            delete *it;
        }
    }
    asteroids=temp;
}

void Asteroids::checkCollideShip(Ship * s){
    struct tBoundingBox
    {
        vec2       max;
        vec2       min;
    };
    
    tBoundingBox     boxArray[1];
    
    boxArray[0].min.x  = -3.05;
    boxArray[0].max.x  = 3.27;
    boxArray[0].min.y  = -2.43;
    boxArray[0].max.y  = 3.04;
    
    for (std::vector< Asteroid * >::iterator it = asteroids.begin() ; it != asteroids.end(); ++it){
        
        boxArray[0].min.x  *= (*it)->scale;
        boxArray[0].max.x  *= (*it)->scale;
        boxArray[0].min.y  *= (*it)->scale;
        boxArray[0].max.y  *= (*it)->scale;
        
        if (s->returnCurLoc().x > (boxArray[0].max.x+(*it)->loc.x) ||
            (s->returnCurLoc().x < boxArray[0].min.x+(*it)->loc.x) ||
            (s->returnCurLoc().y > boxArray[0].max.y+(*it)->loc.y) ||
            (s->returnCurLoc().y < boxArray[0].min.y+(*it)->loc.y)){

            
            glfwTerminate();
            exit(EXIT_SUCCESS);
            break;
        }
    }
}



