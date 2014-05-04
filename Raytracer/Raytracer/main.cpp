
//
// Disclamer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// In order to load the resources like cute_image.png, you have to set up
// your target scheme :
//
// - Select "Edit Scheme…" in the "Product" menu;
// - Check the box "use custom working directory";
// - Fill the text field with the folder path containing your resources;
//        (e.g. your project folder)
// - Click OK.
//

#include <SFML/Graphics.hpp>
#include <unistd.h>
#include <thread>

#include "MeshObject.h"
#include "InstanceObject.h"
#include "Camera.h"
#include "PointLight.h"
#include "DirectLight.h"
#include "Scene.h"
#include "Renderer.h"
#define GLM_SWIZZLE
#include "glm/glm.hpp"
#include "glm/gtx/transform.hpp"
#include "PlaneObject.h"
#include "SphereObject.h"
#include "AreaLight.h"
#include "BoxTreeObject.h"
#include "FresnelMetalMaterial.h"
#include "DielectricMaterial.h"
#include "PlasticMaterial.h"

#define WIDTH 800.0f
#define HEIGHT 600.0f
#define GLM_SWIZZLE

float RangeRand(float min,float max) {
    return min+(max-min)*float(rand()) / float(RAND_MAX);
}

void spheres() {
    // Create scene
    Scene scn;
    scn.setSkyColor(Color(0.8f, 0.8f, 1.0f));
    
    // Create ground plane
    PlaneObject ground;
    scn.addObject(ground);
    
    // Create spheres
    for(int i=0;i<20;i++) {
        SphereObject *sphere = new SphereObject();
        float rad=RangeRand(0.25f,0.5f);
        glm::vec3 pos(RangeRand(-5.0f,5.0f),rad,RangeRand(-5.0f,5.0f));
        sphere->setRadius(rad);
        sphere->setOrigin(pos);
        scn.addObject(*sphere);
    }
    
    // Create lights
    DirectLight sunlgt(glm::vec3(2.0f, -3.0f, -2.0f));
    sunlgt.setBaseColor(Color(1.0f, 1.0f, 0.9f));
    sunlgt.setIntensity(1.0f);
    scn.addLight(sunlgt);
    
    // Create camera
    Camera cam;
    cam.lookAt(glm::vec3(-0.75f,0.25f,5.0f),glm::vec3(0.0f,0.5f,0.0f), glm::vec3(0.0, 1.0, 0.0));
    cam.setFOV(40.0f);
    cam.setAspect(1.33f);
    
    // Render image
    Renderer::getInstance().render(scn, cam);
}

void project1() {
	// Create scene
	Scene scn;
	scn.setSkyColor(Color(0.8f, 0.9f, 1.0f));
    
	// Create boxes
	MeshObject box1;
	box1.makeBox(5.0f,0.1f,5.0f);
	scn.addObject(box1);
    
	MeshObject box2;
	box2.makeBox(1.0f,1.0f,1.0f);
    
	InstanceObject inst1(&box2);
    glm::mat4 mtx;
    
	//mtx.MakeRotateX(0.5f);
    mtx = glm::rotate(mtx, 0.5f * 180.0f / PI, glm::vec3(1.0, 0.0, 0.0));
	mtx[3].y = 1.0f;
	inst1.setMatrix(mtx);
	scn.addObject(inst1);
    
	InstanceObject inst2(&box2);
	//mtx.MakeRotateY(1.0f);
    mtx = glm::mat4();
    mtx = glm::rotate(mtx, 1.0f * 180.0f / PI, glm::vec3(0.0, 1.0, 0.0));
	mtx[3] = glm::vec4(-1.0f,0.0f,1.0f, 1.0f);
	inst2.setMatrix(mtx);
	scn.addObject(inst2);
    
	// Create lights
	DirectLight sunlgt(glm::vec3(-0.5f, -1.0f, -0.5f));
	sunlgt.setBaseColor(Color(1.0f, 1.0f, 0.9f));
	sunlgt.setIntensity(0.5f);
	scn.addLight(sunlgt);
    
	PointLight redlgt(glm::vec3(2.0f, 2.0f, 0.0f));
	redlgt.setBaseColor(Color(1.0f, 0.2f, 0.2f));
	redlgt.setIntensity(2.0f);
	scn.addLight(redlgt);
    
	// Create camera
	Camera cam;
	cam.lookAt(glm::vec3(2.0f,2.0f,5.0f),glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0, 1.0, 0.0));
    //cam.lookAt(Vector3(0.0f,0.0f,0.0f),Vector3(0.0f,0.0f,-1.0f), Vector3(0.0, 1.0, 0.0));
	cam.setFOV(40.0f);
	cam.setAspect(1.33);
    
	// Render image
    Renderer::getInstance().render(scn, cam);
}

void cornellBox() {
    // Create scene
	Scene scn;
	scn.setSkyColor(Color(0.8f, 0.9f, 1.0f));
    
    for (MeshObject* objs : MeshObject::loadFromFile("models/cornell-box/CornellBox-Glossy.obj"))
    {
        BoxTreeObject* box = new BoxTreeObject();
        box->construct(*objs);
        //scn.addObject(*objs);
        scn.addObject(*box);
    }
    
	PointLight redlgt(glm::vec3(0.0f,2.0f,2.0f));
	redlgt.setBaseColor(Color(1.0f, 0.5f, 0.5f));
	redlgt.setIntensity(1.0f);
	scn.addLight(redlgt);
    
    PointLight wlgt(glm::vec3(0.0f,1.0f,1.0f));
    wlgt.setBaseColor(Color(0.9f, 0.9f, 0.9f));
    wlgt.setIntensity(1.0f);
    scn.addLight(wlgt);
    
	Camera cam;
	cam.lookAt(glm::vec3(0.0f,0.75f,3.0f),glm::vec3(0.0f,0.75f,0.0f), glm::vec3(0.0, 1.0, 0.0));
	cam.setFOV(40.0f);
	cam.setAspect(WIDTH / HEIGHT);
    
    Renderer::getInstance().render(scn, cam);
}

void teapot() {
    // Create scene
    
	Scene scn;
	scn.setSkyColor(Color(0.8f, 0.9f, 1.0f));
    
    PlaneObject ground;
    scn.addObject(ground);
    
    for (MeshObject* objs : MeshObject::loadFromFile("models/teapot/teapot.obj")) {
        objs->setMaterial(new FresnelMetalMaterial(Color(1.0f, 215.0f/255.0f, 0), 0.37, 2.82));
        BoxTreeObject* box = new BoxTreeObject();
        box->construct(*objs);
        //scn.addObject(*objs);
        scn.addObject(*box);
    }
    
    DirectLight sunlgt(glm::vec3(1.0f, -1.0f, -0.5f));
	sunlgt.setBaseColor(Color(0.9f, 0.9f, 0.9f));
	sunlgt.setIntensity(0.5f);
	scn.addLight(sunlgt);
    
    DirectLight sunlgt2(glm::vec3(-1.f, -1.0f, -0.5f));
	sunlgt2.setBaseColor(Color(0.9f, 0.9f, 0.9f));
	sunlgt2.setIntensity(0.5f);
	scn.addLight(sunlgt2);
    
	Camera cam;
	cam.lookAt(glm::vec3(0.f,50.f,200.0f),glm::vec3(0.0f,50.0f,0.0f), glm::vec3(0.0, 1.0, 0.0));
	cam.setFOV(40.0f);
	cam.setAspect(WIDTH / HEIGHT);
    
    Renderer::getInstance().render(scn, cam);
}

void bedroom() {
    // Create scene
	Scene scn;
	scn.setSkyColor(Color(0.8f, 0.9f, 1.0f));
    
    for (MeshObject* objs : MeshObject::loadFromFile("models/bedroom/Bedroom.obj"))
        scn.addObject(*objs);
    
    
    PointLight wlgt(glm::vec3(-53.545274, 43.698658, 195.204880));
    wlgt.setBaseColor(Color(0.9f, 0.9f, 0.9f));
    wlgt.setIntensity(100.8f);
    scn.addLight(wlgt);
    
	Camera cam;
	//cam.lookAt(glm::vec3(50.0f,154.0f,-94.0f),glm::vec3(11.0f,133.0f,-31.0f), glm::vec3(0.0, 1.0, 0.0));
    cam.lookAt(glm::vec3(-53.545274, 43.698658, 195.204880),glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
	cam.setFOV(40.0f);
	cam.setAspect(WIDTH / HEIGHT);
    
    Renderer::getInstance().render(scn, cam);
}

void head() {
    // Create scene
	Scene scn;
	scn.setSkyColor(Color(0.8f, 0.9f, 1.0f));
    
    for (MeshObject* objs : MeshObject::loadFromFile("models/head/head.OBJ"))
        scn.addObject(*objs);
    
	DirectLight sunlgt(glm::vec3(-0.5f, -1.0f, -0.5f));
	sunlgt.setBaseColor(Color(1.0f, 1.0f, 0.9f));
	sunlgt.setIntensity(0.5f);
	scn.addLight(sunlgt);
    
	Camera cam;
	cam.lookAt(glm::vec3(1.0f,0.0f,0.0f),glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0, 1.0, 0.0));
	cam.setFOV(40.0f);
	cam.setAspect(WIDTH / HEIGHT);
    
    Renderer::getInstance().render(scn, cam);
}

void cornellBoxArea() {
    // Create scene
	Scene scn;
	scn.setSkyColor(Color(0.8f, 0.9f, 1.0f));
    
    std::vector<MeshObject*> objects = MeshObject::loadFromFile("models/cornell-box/CornellBox-Glossy.obj");
    for (MeshObject* obj : objects) {
        BoxTreeObject* box = new BoxTreeObject();
        box->construct(*obj);
        //scn.addObject(*obj);
        scn.addObject(*box);
    }
    
    objects[7]->setMaterial(new LambertMaterial(Color(0, 0, 1)));
    for (int idx = 0; idx < objects[7]->_numTriangles; ++idx) {
        AreaLight *light = new AreaLight(&objects[7]->_triangles[idx]);
        light->setIntensity(0.2);
        light->setSampling(10);
        scn.addLight(*light);
        objects[7]->_triangles[idx].setLight(light);
    }
    
    /*PointLight wlgt(glm::vec3(0.0f,1.0f,1.0f));
     wlgt.setBaseColor(Color(0.9f, 0.9f, 0.9f));
     wlgt.setIntensity(2.0f);
     scn.addLight(wlgt);*/
    
	Camera cam;
	cam.lookAt(glm::vec3(0.0f,0.75f,3.0f),glm::vec3(0.0f,0.75f,0.0f), glm::vec3(0.0, 1.0, 0.0));
	cam.setFOV(40.0f);
	cam.setAspect(WIDTH / HEIGHT);
    
    Renderer::getInstance().render(scn, cam);
}

void project2() {
    // Create scene
    Scene scn;
    scn.setSkyColor(Color(0.8f, 0.8f, 1.0f));
    
    // Create ground
    MeshObject ground;
    ground.makeBox(5.0f,0.1f,5.0f);
    ground.setMaterial(new LambertMaterial(Color(1.0, 1.0, 1.0)));
    scn.addObject(ground);
    
    std::vector<MeshObject*> objects = MeshObject::loadFromFile("models/dragon.ply");
    objects[0]->setMaterial(new LambertMaterial(Color(1.0, 1.0, 1.0)));
    //objects[0]->setMaterial(new PlasticMaterial(Color(0.0, 0.0, 0.0), 2));
    //objects[0]->setMaterial(new DielectricMaterial(1.33));
    
    BoxTreeObject* tree = new BoxTreeObject();
    tree->construct(*(objects[0]));
    scn.addObject(*tree);
    
    // Create instance
    InstanceObject inst(tree);
    glm::mat4 mtx = glm::mat4();
    mtx = glm::rotate(mtx, 180.0f, glm::vec3(0.0, 1.0, 0.0));
	mtx[3] = glm::vec4(-0.05f,0.0f,-0.1f,1.0f);
    inst.setMatrix(mtx);
    scn.addObject(inst);
    
    // Create lights
    DirectLight sunlgt(glm::vec3(2.0f, -3.0f, -2.0f));
    sunlgt.setBaseColor(Color(1.0f, 1.0f, 0.9f));
    sunlgt.setIntensity(1.0f);
    scn.addLight(sunlgt);
    
    PointLight redlgt(glm::vec3(-0.2f, 0.2f, 0.2f));
    redlgt.setBaseColor(Color(1.0f, 0.2f, 0.2f));
    redlgt.setIntensity(0.02f);
    scn.addLight(redlgt);
    
    PointLight bluelgt(glm::vec3(0.1f, 0.1f, 0.3f));
    bluelgt.setBaseColor(Color(0.2f, 0.2f, 1.0f));
    bluelgt.setIntensity(0.02f);
    scn.addLight(bluelgt);
    
    // Create camera
    Camera cam;
    cam.lookAt(glm::vec3(-0.1f,0.1f,0.2f),glm::vec3(-0.05f,0.12f,0.0f), glm::vec3(0.0, 1.0, 0.0));
    cam.setFOV(40.0f);
    cam.setAspect(WIDTH / HEIGHT);
    
    Renderer::getInstance().render(scn, cam);
}

void dragons() {
    // Create scene
    Scene scn;
    scn.setSkyColor(Color(0.8f, 0.8f, 1.0f));
    
    // Create ground
    MeshObject ground;
    ground.makeBox(5.0f,0.1f,5.0f);
    scn.addObject(ground);
    
    std::vector<MeshObject*> objects = MeshObject::loadFromFile("models/dragon.ply");
    objects[0]->setMaterial(new LambertMaterial(Color(1.0, 1.0, 1.0)));
    BoxTreeObject* tree = new BoxTreeObject();
    tree->construct(*(objects[0]));
    
    std::vector<Object*> allDragons;
    // Create instance
    for (float x = -2; x < 2; x+=0.2) {
        for (float z = -3; z < 1; z+=0.2) {
            InstanceObject* inst = new InstanceObject(tree);
            glm::mat4 mtx = glm::mat4();
            mtx[3] = glm::vec4(-x/*0.05f*/,0.0f,z,1.0f);
            inst->setMatrix(mtx);
            allDragons.push_back(inst);
        }
    }
    
    BoxTreeObject* treeDragons = new BoxTreeObject();
    treeDragons->construct(allDragons);
    scn.addObject(*treeDragons);
    
    // Create lights
    DirectLight sunlgt(glm::vec3(2.0f, -3.0f, -2.0f));
    sunlgt.setBaseColor(Color(1.0f, 1.0f, 0.9f));
    sunlgt.setIntensity(1.0f);
    scn.addLight(sunlgt);
    
    PointLight redlgt(glm::vec3(-0.2f, 0.2f, 0.2f));
    redlgt.setBaseColor(Color(1.0f, 0.2f, 0.2f));
    redlgt.setIntensity(0.02f);
    scn.addLight(redlgt);
    
    PointLight bluelgt(glm::vec3(0.1f, 0.1f, 0.3f));
    bluelgt.setBaseColor(Color(0.2f, 0.2f, 1.0f));
    bluelgt.setIntensity(0.02f);
    scn.addLight(bluelgt);
    
    // Create camera
    Camera cam;
    cam.lookAt(glm::vec3(-0.1f,1.1f,2.f),glm::vec3(-0.05f,0.12f,0.0f), glm::vec3(0.0, 1.0, 0.0));
    cam.setFOV(40.0f);
    cam.setAspect(WIDTH / HEIGHT);
    
    Renderer::getInstance().render(scn, cam);
}

void sam() {
    Camera* camera = new Camera;
    camera->lookAt(glm::vec3(0.0f, 0.3f, 0.5f), glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    camera->setFOV(40.0f);
    camera->setAspect(WIDTH / HEIGHT);
    
    Scene* scene = new Scene;
    scene->setSkyColor(Color(0.8f, 0.8f, 1.0f));
    
    std::vector<MeshObject*> objects = MeshObject::loadFromFile("models/dragon.ply");
    BoxTreeObject* tree = new BoxTreeObject();
    tree->construct(*(objects[0]));
    
    std::vector<Object*> allDragons;
    
    for (float x = -3.0f; x < 3.0f; x += 0.3) {
        for (float z = 0.0f; z > -10.0f; z -= 0.3f) {
            InstanceObject* inst = new InstanceObject(tree);
            glm::mat4 mtx;
            mtx[3] = glm::vec4(x, 0.0f, z, 1.0f);
            inst->setMatrix(mtx);
            allDragons.push_back(inst);
        }
    }
    
    tree = new BoxTreeObject();
    tree->construct(allDragons);
    scene->addObject(*tree);
    
    
    PlaneObject* ground = new PlaneObject;
    ground->setOrigin(glm::vec3(0.0f, 0.05f, 0.0f));
    scene->addObject(*ground);
    
    DirectLight* sunlgt = new DirectLight(glm::vec3(2.0f, -3.0f, -2.0f));
    sunlgt->setBaseColor(Color(1.0f, 1.0f, 0.9f));
    sunlgt->setIntensity(1.0f);
    scene->addLight(*sunlgt);
    
    PointLight* redlgt = new PointLight(glm::vec3(0.0f, 0.2f, 0.2f));
    redlgt->setBaseColor(Color(1.0f, 0.2f, 0.2f));
    redlgt->setIntensity(0.02f);
    scene->addLight(*redlgt);
    
    PointLight* bluelgt = new PointLight(glm::vec3(0.1f, 0.1f, 0.3f));
    bluelgt->setBaseColor(Color(0.2f, 0.2f, 1.0f));
    bluelgt->setIntensity(0.02f);
    scene->addLight(*bluelgt);
    
    Renderer::getInstance().render(*scene, *camera);
}

void gael() {    // Create scene
    Scene* scene = new Scene();
    scene->setSkyColor(Color(0.8f, 0.9f, 1.0f));
    
    std::vector<Object*> teapot;
    for (MeshObject* objs : MeshObject::loadFromFile("models/teapot/teapot.obj")) {
        BoxTreeObject* box = new BoxTreeObject();
        box->construct(*objs);
        teapot.push_back(box);
    }
    
    BoxTreeObject* teapotTree = new BoxTreeObject();
    teapotTree->construct(teapot);
    
    std::vector<Object*> teapots;
    for (int i = 0; i < 100; ++i) {
        for (int j = 0; j < 100; ++j) {
            glm::mat4 m;
            m = glm::scale(m, glm::vec3(1.0f, 1.0f, 1.0f)*0.05f);
            m[3].x = -100.0f + i*10.0f;
            m[3].z = -(j*10.0f);
            InstanceObject* oo = new InstanceObject(teapotTree);
            oo->setMatrix(m);
            teapots.push_back(oo);
        }
    }
    
    BoxTreeObject* teapotsTree = new BoxTreeObject();
    teapotsTree->construct(teapots);
    
    scene->addObject(*teapotsTree);
    
    PlaneObject* groundShape = new PlaneObject();
    scene->addObject(*groundShape);
    
    // Create lights
    PointLight* light;
    
    light = new PointLight(glm::vec3(0.4, 0.75, 1));
    light->setBaseColor(Color(0.8f, 0.9f, 1.0f));
    light->setIntensity(1.0);
    //scene->lights.push_back(light);
    
    DirectLight* sunlgt = new DirectLight(glm::vec3(2.0f, -3.0f, -2.0f));
    sunlgt->setBaseColor(Color(1.0f, 1.0f, 0.9f));
    sunlgt->setIntensity(1.0f);
    scene->addLight(*sunlgt);
    
    // Create camera
    Camera* perspectiveCamera = new Camera();
    
    perspectiveCamera->lookAt(glm::vec3(0.0f, 10.0f, 20.0f), glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
    //perspectiveCamera->lookAt(vec3(0.0f, 0.1f, 0.2f), vec3(0, 0.12f, 0.0f));
    //perspectiveCamera->lookAt(vec3(49.155, 190.717, -107.093), vec3(22.78, 162.45, -69.4));
    
    perspectiveCamera->setFOV(40.0f);
    perspectiveCamera->setAspect(WIDTH / HEIGHT);
    
    Renderer::getInstance().render(*scene, *perspectiveCamera);
}

void cornellBoxAreaDragon() {
    // Create scene
	Scene scn;
	scn.setSkyColor(Color(0.0f, 0.0f, 0.0f));
    
    std::vector<MeshObject*> objects = MeshObject::loadFromFile("models/cornell-box/CornellBox-Empty.obj");
    for (MeshObject* obj : objects) {
        BoxTreeObject* box = new BoxTreeObject();
        box->construct(*obj);
        //scn.addObject(*obj);
        scn.addObject(*box);
    }
    
    std::vector<MeshObject*> objects2 = MeshObject::loadFromFile("models/dragon.ply");
    objects2[0]->setMaterial(new FresnelMetalMaterial(Color(212.0f/255.0f, 175.0f/255.0f, 55.0f/255), 0.37, 2.82));
    //objects2[0]->setMaterial(new FresnelMetalMaterial(Color(192.0f/255, 192.0f/255, 192.0f/255), 0.177, 3.638));
    //objects2[0]->setMaterial(new FresnelMetalMaterial(Color(184.0/255, 115.0/255, 51.0/255), 0.617, 2.63));
    //objects2[0]->setMaterial(new FresnelMetalMaterial(Color(204.0/255, 204.0/255, 204.0/255), 3.30619, 3.5293));
    objects2[0]->setMaterial(new DielectricMaterial(1.50f, 25.0f, 0.2f*25, 25.0f));
   // objects2[0]->setMaterial(new PlasticMaterial(Color(0.1, 0.1, 0.9), 2.5, 0.2, 0.3));
    //objects2[0]->setMaterial(new DielectricMaterial(1.50f));

    
    BoxTreeObject* tree = new BoxTreeObject();
    tree->construct(*(objects2[0]));
    
    InstanceObject* inst = new InstanceObject(tree);
    glm::mat4 mtx;
    mtx[3] = glm::vec4(0.0f, -0.37f, 0.0f, 1.0f);
    mtx = glm::scale(mtx, glm::vec3(1.0f, 1.0f, 1.0f)*7.0f);
    inst->setMatrix(mtx);
    scn.addObject(*inst);
    
    int lightPos = 5;
    objects[lightPos]->setMaterial(new LambertMaterial(Color(0, 0, 1)));
    for (int idx = 0; idx < objects[lightPos]->_numTriangles; ++idx) {
        AreaLight *light = new AreaLight(&objects[lightPos]->_triangles[idx]);
        light->setIntensity(0.45/4);
        light->setSampling(1);
        scn.addLight(*light);
        objects[lightPos]->_triangles[idx].setLight(light);
    }
    
	Camera cam;
	cam.lookAt(glm::vec3(0.0f,0.75f,3.0f),glm::vec3(0.0f,0.75f,0.0f), glm::vec3(0.0, 1.0, 0.0));
	cam.setFOV(40.0f);
	cam.setAspect(WIDTH / HEIGHT);
    
    Renderer::getInstance().render(scn, cam);
}

void cornellBoxFresnel() {
    // Create scene
	Scene scn;
	scn.setSkyColor(Color(0.1f, 0.9f, 0.1f));
    
    std::vector<MeshObject*> objects = MeshObject::loadFromFile("models/cornell-box/CornellBox-Sphere.obj");
    for (MeshObject* obj : objects) {
        BoxTreeObject* box = new BoxTreeObject();
        box->construct(*obj);
        scn.addObject(*box);
    }
    
    //objects[0]->setMaterial(new LambertMaterial(Color(1.0, 1.0, 1.0)));
    //objects[1]->setMaterial(new LambertMaterial(Color(1.0, 1.0, 1.0)));
    objects[1]->setMaterial(new FresnelMetalMaterial(Color(192.0f/255, 192.0f/255, 192.0f/255), 0.177, 3.638));
    objects[0]->setMaterial(new FresnelMetalMaterial(Color(1.0f, 215.0f/255.0f, 0), 0.37, 2.82));
    //objects[0]->setMaterial(new FresnelMetalMaterial(Color(1.0f, 1.0f, 1.0f), 0.37, 2.82));
    objects[1]->setMaterial(new DielectricMaterial(1.3));
    //objects[1]->setMaterial(new LambertMaterial(Color(1.0, 0.0, 0.0)));
    
    int lightPos = 7;
     objects[lightPos]->setMaterial(new LambertMaterial(Color(0, 0, 1)));
     for (int idx = 0; idx < objects[lightPos]->_numTriangles; ++idx) {
     AreaLight *light = new AreaLight(&objects[lightPos]->_triangles[idx]);
     light->setIntensity(0.2/2);
     light->setSampling(5);
     scn.addLight(*light);
     objects[lightPos]->_triangles[idx].setLight(light);
     }
    //PointLight wlgt(glm::vec3(0.0f,1.0f,1.0f));
    PointLight wlgt(glm::vec3(0.2300f, 1.4800f, 0.1600f));
    wlgt.setBaseColor(Color(0.9f, 0.9f, 0.9f));
    wlgt.setIntensity(3.0f);
    //scn.addLight(wlgt);
    
    PointLight wlgt2(glm::vec3(0.00f, 1.3800f, -0.000f));
    wlgt2.setBaseColor(Color(0.9f, 0.9f, 0.9f));
    wlgt2.setIntensity(1.92f);
    //scn.addLight(wlgt2);
    
	Camera cam;
	cam.lookAt(glm::vec3(0.0f,0.75f,3.0f),glm::vec3(0.0f,0.75f,0.0f), glm::vec3(0.0, 1.0, 0.0));
	cam.setFOV(40.0f);
	cam.setAspect(WIDTH / HEIGHT);
    
    Renderer::getInstance().render(scn, cam);
}

void reflectionRefraction() {
    // Create scene
    Scene scn;
    scn.setSkyColor(Color(0.8f, 0.8f, 1.0f));
    
    // Create ground plane
    PlaneObject ground;
    ground.setMaterial(new LambertMaterial(Color(1.0, 1.0, 1.0)));
    scn.addObject(ground);
    
    // Create spheres
    for(int i=0;i<3;i++) {
        SphereObject *sphere = new SphereObject();
        float rad=0.5f;
        glm::vec3 pos(-1.4 + 1.35*i,0.5f,0.0f);
        sphere->setRadius(rad);
        sphere->setOrigin(pos);
        if (i == 2) {
            sphere->setMaterial(new PlasticMaterial(Color(1.0, 0.0, 0.0), 2));
        } else if (i == 1) {
            sphere->setMaterial(new DielectricMaterial(1.33));
        } else
            sphere->setMaterial(new FresnelMetalMaterial(Color(204.0/255, 204.0/255, 204.0/255), 3.30619, 3.5293));
        scn.addObject(*sphere);
    }
    
    // Create lights
    DirectLight sunlgt(glm::vec3(2.0f, -3.0f, -2.0f));
    sunlgt.setBaseColor(Color(1.0f, 1.0f, 0.9f));
    sunlgt.setIntensity(0.6f);
    scn.addLight(sunlgt);
    
    // Create camera
    Camera cam;
    cam.lookAt(glm::vec3(-0.75f,0.75f,5.0f),glm::vec3(0.0f,0.5f,0.0f), glm::vec3(0.0, 1.0, 0.0));
    cam.setFOV(40.0f);
    cam.setAspect(1.33f);
    
    // Render image
    Renderer::getInstance().render(scn, cam);
}

void materials() {
    // Create scene
	Scene scn;
	scn.setSkyColor(Color(0.5f, 0.5f, 0.5f));
    
    
    std::vector<MeshObject*> objects = MeshObject::loadFromFile("models/cornell-box/CornellBox-Empty.obj");
    int idx = 0;
    for (MeshObject* obj : objects) {
        BoxTreeObject* box = new BoxTreeObject();
        box->construct(*obj);
        //scn.addObject(*obj);
        if (idx != 5 && idx != 3 && idx != 2 && idx != 4)
            scn.addObject(*box);
        ++idx;
    }
    
    std::vector<MeshObject*> objects2 = MeshObject::loadFromFile("models/dragon.ply");
    objects2[0]->setMaterial(new FresnelMetalMaterial(Color(212.0f/255.0f, 175.0f/255.0f, 55.0f/255), 0.37, 2.82));
    //objects2[0]->setMaterial(new FresnelMetalMaterial(Color(192.0f/255, 192.0f/255, 192.0f/255), 0.177, 3.638));
    //objects2[0]->setMaterial(new FresnelMetalMaterial(Color(184.0/255, 115.0/255, 51.0/255), 0.617, 2.63));
    //objects2[0]->setMaterial(new FresnelMetalMaterial(Color(204.0/255, 204.0/255, 204.0/255), 3.30619, 3.5293));
    //objects2[0]->setMaterial(new DielectricMaterial(1.33f, 25.0f, 0.2f*25, 25.0f));
    //objects2[0]->setMaterial(new PlasticMaterial(Color(0.1, 0.1, 0.9), 2.5, 0.2, 0.3));
    
    BoxTreeObject* tree = new BoxTreeObject();
    tree->construct(*(objects2[0]));
    
    
    int lightPos = 1;
    objects[lightPos]->setMaterial(new LambertMaterial(Color(0, 0, 1)));
    for (int idx = 0; idx < objects[lightPos]->_numTriangles; ++idx) {
        AreaLight *light = new AreaLight(&objects[lightPos]->_triangles[idx]);
        light->setIntensity(0.45*10);
        light->setSampling(36);
        scn.addLight(*light);
        objects[lightPos]->_triangles[idx].setLight(light);
    }
    
    for (int i = 0; i < 4; ++i)
    {
        MeshObject* box = new MeshObject();
        box->makeBox(0.3, 0.2, 0.3);
        box->setMaterial(new PlasticMaterial(Color(0.0, 0.0, 0.0), 2.0f, 0.3f));
        InstanceObject* boxInst = new InstanceObject(box);
        glm::mat4 mtx;
        mtx[3] = glm::vec4(-0.7f + i * 0.5, 0.15f, 0.3f, 1.0f);
        boxInst->setMatrix(mtx);
        scn.addObject(*boxInst);
        
        InstanceObject* inst = new InstanceObject(tree);
        glm::mat4 mtx2;
        mtx2 = glm::rotate(mtx2, 0.5f * 180.0f / PI, glm::vec3(0.0, 1.0, 0.0));
        mtx2[3] = glm::vec4(-0.7f + i * 0.5, -0.37f + 0.50f, 0.3f, 1.0f);
        mtx2 = glm::scale(mtx2, glm::vec3(1.0f, 1.0f, 1.0f)*2.0f);
        inst->setMatrix(mtx2);
        scn.addObject(*inst);
        
        SphereObject* sphere = new SphereObject();
        sphere->setOrigin(glm::vec3(-0.7f + i * 0.5 + 0.11, 0.15f + 0.13f, 0.3f + 0.11));
        sphere->setRadius(0.03f);
        sphere->setMaterial(new DielectricMaterial(1.50f));
        scn.addObject(*sphere);
        
        if (i == 2)
            sphere->setMaterial(new DielectricMaterial(1.33f, 25.0f*1.0, 0.2f*25, 25.0f));
        if (i == 1)
            inst->setMaterial(new FresnelMetalMaterial(Color(212.0f/255.0f, 175.0f/255.0f, 55.0f/255), 0.37, 2.82));
        if (i == 0)
            sphere->setMaterial(new FresnelMetalMaterial(Color(184.0/255, 115.0/255, 51.0/255), 0.617, 2.63));
        if (i == 3)
            sphere->setMaterial(new FresnelMetalMaterial(Color(192.0f/255, 192.0f/255, 192.0f/255), 0.177, 3.638));
        if (i == 0)
            inst->setMaterial(new DielectricMaterial(1.33f, 25.0f*0.2, 1.0f*25, 25.0f));
        if (i == 3)
            inst->setMaterial(new PlasticMaterial(Color(0.1, 0.9, 0.1), 2.0f));
        if (i == 2)
            inst->setMaterial(new DielectricMaterial(1.5f));
    }
    
    {
        InstanceObject* inst = new InstanceObject(tree);
        inst->setMaterial(new FresnelMetalMaterial(Color(38.0f/255, 50.0f/255, 72.0f/255), 0.177, 3.638));
        //inst->setMaterial(new FresnelMetalMaterial(Color(52.0f/255, 52.0f/255, 82.0f/255), 0.177, 3.638));
        glm::mat4 mtx;
        mtx[3] = glm::vec4(0.0f, -0.37f, -0.8f, 1.0f);
        mtx = glm::scale(mtx, glm::vec3(1.0f, 1.0f, 1.0f)*7.0f);
        inst->setMatrix(mtx);
        scn.addObject(*inst);
    }
    
	Camera cam;
	cam.lookAt(glm::vec3(-0.4f,0.7f,2.3f),glm::vec3(0.03f,0.4f,0.0f), glm::vec3(0.0, 1.0, 0.0));
	cam.setFOV(40.0f);
	cam.setAspect(WIDTH / HEIGHT);
    
    Renderer::getInstance().render(scn, cam);
}

void raytracer(sf::Image* image) {
    Renderer::getInstance().setImage(WIDTH, HEIGHT, image);
    Renderer::getInstance().enableShadows(true);
    Renderer::getInstance().setAntialiasing(1);
    Renderer::getInstance().setAntialiasingJittered(true);
    Renderer::getInstance().setPhong(false);
    //Renderer::getInstance().setAntialiasingWeighted(true);
    //project1();
    //spheres();
    //cornellBox();
    //teapot();
    //head();
    //bedroom();
    //cornellBoxArea();
    //project2();
    //dragons();
    //sam();
    //gael();
    cornellBoxAreaDragon();
    //cornellBoxFresnel();
    //reflectionRefraction();
    //materials();
}

#define PROFILEX

int main(int argc, char const** argv)
{
#ifndef PROFILE
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "CSE 168 Raytracer", sf::Style::Close);
    window.setFramerateLimit(5);
    
    sf::Image image;
    image.create(WIDTH, HEIGHT);
    sf::Texture texture;
    texture.loadFromImage(image);
    sf::Sprite sprite(texture);
    
    std::thread rt(raytracer, &image);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                
            }
        }
        
        texture.loadFromImage(image);
        window.clear();
        window.draw(sprite);
        window.display();
    }
    
    rt.detach();
#endif
    
#ifdef PROFILE
    raytracer(NULL);
#endif
    
    return EXIT_SUCCESS;
}
