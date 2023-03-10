#include "Scene.hpp"

//---Base class---
Scene::Scene(ofVec3f dimensions): dimensions(dimensions){}

Scene::Scene
(
	ofVec3f dimensions,
	std::vector<std::shared_ptr<SceneObject>> sceneObjects,
	std::vector<std::shared_ptr<ParticleSystem>> particleSystems,
	std::vector<ofLight> lightSources
):
	dimensions(dimensions),
	sceneObjects(sceneObjects),
	particleSystems(particleSystems)
{}

void Scene::load(){
	mainCamera.panDeg(180);
	mainCamera.rollDeg(180);
}

void Scene::draw(){
	ofClear(ofColor::black);

	ofEnableDepthTest();
	mainCamera.begin();

	for(size_t i = 0; i < sceneObjects.size(); i++){
		sceneObjects[i] -> draw();
	}

	for(size_t i = 0; i < particleSystems.size(); i++){
		particleSystems[i] -> updateAndDraw();
	}

	mainCamera.end();
}
//------

//---Christmas Scene---
//private
void ChristmasScene::createSceneObjects(){
	sceneObjects = {
		//Ground
		std::make_shared<GroundPlane>(ofVec3f(0, 0, 0), ofVec2f(dimensions.x, dimensions.z)),
		//Snowman
		std::make_shared<Snowman>(ofVec3f(dimensions.x / 4.5, 0, dimensions.z / 8.f)),
		//---Trees---
		std::make_shared<Spruce>(ofVec3f(-dimensions.x / 3.f, 0, -dimensions.z / 10.f)),
		std::make_shared<Spruce>(ofVec3f(-dimensions.x / 4.f, 0, dimensions.z / 4.f)),
		std::make_shared<Spruce>(ofVec3f(-dimensions.x / 7.f, 0, -dimensions.z / 3.f)),
		std::make_shared<Spruce>(ofVec3f(-dimensions.x / 9.f, 0, dimensions.z / 20.f)), //Tree with gifts under it
		std::make_shared<Spruce>(ofVec3f(-dimensions.x / 9.f, 0, dimensions.z / 2.5)),
		std::make_shared<Spruce>(ofVec3f(dimensions.x / 9.f, 0, -dimensions.z / 6.f)),
		std::make_shared<Spruce>(ofVec3f(dimensions.x / 8.f, 0, dimensions.z / 3.f)),
		std::make_shared<Spruce>(ofVec3f(dimensions.x / 4.f, 0, -dimensions.z / 3.5)),
		std::make_shared<Spruce>(ofVec3f(dimensions.x / 3.f, 0, dimensions.z / 3.f)),
		std::make_shared<Spruce>(ofVec3f(dimensions.x / 2.5, 0, dimensions.z / 9.f)),
		//------
		//---Gifts---
		std::make_shared<Gift>(ofVec3f(-dimensions.x / 15.f, 0, dimensions.z / 19.f), -25),
		std::make_shared<Gift>(ofVec3f(-dimensions.x / 9.f, 0, 0), 15, 1.2, ofColor(212, 175, 55))
	};
}

void ChristmasScene::createParticleSystems(){
	particleSystems = {
		std::make_shared<SnowParticleSystem>(
			ofVec3f(-dimensions.x / 2, -dimensions.y, -dimensions.z / 2),
			ofVec3f(dimensions.x / 2, -dimensions.y, dimensions.z / 2),
			0
		),

		std::make_shared<FireParticleSystem>(ofVec3f(0, 0, 0), 40, 10)
	};
}

void ChristmasScene::createLightSources(){
	//---Fireplace---
	ofLight fireplaceLight;
	fireplaceLight.setPointLight();
	fireplaceLight.setPosition(ofVec3f(0, -dimensions.y / 10, 0));
	fireplaceLight.setDiffuseColor(ofColor(226, 88, 34));
	fireplaceLight.setSpecularColor(ofColor::white);

	fireplaceLight.enable();
	//------

	lightSources.push_back(fireplaceLight);
}

void ChristmasScene::load(){
	createSceneObjects();
	createParticleSystems();
	createLightSources();
	
	mainCamera.panDeg(180);
	mainCamera.rollDeg(180);

	particleSystems[0] -> addSphereColliders(
		std::dynamic_pointer_cast<Snowman>(sceneObjects[1]) -> spheres
	);
}
//------