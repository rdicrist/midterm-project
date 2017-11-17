#include "common.h"

using namespace Angel;

Ship ship;

Bullets *bullets;
Asteroids *asteroids;

//Asteroids::Asteroid a;

static void error_callback(int error, const char* description)
{
  fprintf(stderr, "Error: %s\n", description);
}

static Asteroids::Asteroid * createNew(){
    Asteroids::Asteroid *a = new Asteroids::Asteroid();
    a->init2();
    return a ;
}

static void checkCollidBulletAsteroid(){
    for(unsigned int j=0; j < bullets->bullets.size(); j++){
        if(asteroids->split(bullets->bullets[j]->loc)){
            bullets->bullets[j]->hit = true;
        }
    }
    bullets->clean_bullets();
}


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    glfwSetWindowShouldClose(window, GLFW_TRUE);
  if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
    ship.rotateLeft();
  if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
    ship.rotateRight();
  if (key == GLFW_KEY_SPACE){
    if(action == GLFW_PRESS){
      ship.start_thruster();
    }
    if(action == GLFW_RELEASE){
      ship.stop_thruster();
    }
  }
  if (key == GLFW_KEY_UP && action == GLFW_PRESS){
    //!!!!!!!!Fire bullet
      bullets->bullets.push_back(ship.fire());
  }

}

void init(){
  
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glHint (GL_LINE_SMOOTH_HINT, GL_NICEST);
  glHint (GL_POINT_SMOOTH_HINT, GL_NICEST);
  ship.gl_init();
    bullets = new Bullets();
    bullets->init();
    
    //a.init2();
    asteroids->init();
}

void animate(double width, double height){
  if(glfwGetTime() > 0.033){
    glfwSetTime(0.0);
    ship.update_state();
      
      //a.update_state2();
      bullets->update_state();
      asteroids->update_state();
  }
}

int main(void)
{
  GLFWwindow* window;
  
  glfwSetErrorCallback(error_callback);
  
  if (!glfwInit())
    exit(EXIT_FAILURE);
  
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  
  glfwWindowHint(GLFW_SAMPLES, 10);
  
  
  window = glfwCreateWindow(1024, 768, "Asteroids!", NULL, NULL);
  if (!window){
    glfwTerminate();
    exit(EXIT_FAILURE);
  }
  
  glfwSetKeyCallback(window, key_callback);
  
  glfwMakeContextCurrent(window);
  gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
  glfwSwapInterval(1);
  
    
  asteroids = new Asteroids();
    for (int i = 0; i<8; i++){
      asteroids->asteroids.push_back(createNew());
    }
    //asteroids->asteroids.push_back(createNew());
  
  init();

  while (!glfwWindowShouldClose(window)){
    
      int width, height;

      
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    
    //!!!!!!!!Pick a projection that makes the most sense to you
    ship.set_extents(40, 40);
      
      
    mat4 proj = Ortho2D(-20, 20, 20, -20);
      
    
    animate(width, height);
    
    glClear(GL_COLOR_BUFFER_BIT);
    
    ship.draw(proj);
      //a.drawOne(proj);
      
      asteroids->draw(proj);

      
      //a.drawOne(proj);
      //creates asteroids
     //asteroids->asteroids.push_back(new Asteroids::Asteroid());
      
      
      
      bullets->draw(proj);
      
      checkCollidBulletAsteroid();
      
      //asteroids->checkCollideShip(&ship);
    
    glfwSwapBuffers(window);
    glfwPollEvents();
    
  }
  
  glfwDestroyWindow(window);
  
  glfwTerminate();
  exit(EXIT_SUCCESS);
}
