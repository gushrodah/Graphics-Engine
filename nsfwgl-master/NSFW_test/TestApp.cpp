#include "TestApp.h"
#include <iostream>
using namespace std;

void TestApp::onStep()
{
	camera.Input(10.0f, nsfw::Window::instance().getDeltaTime());
	float dt = nsfw::Window::instance().getDeltaTime();
	obj.transform = glm::rotate(obj.transform, (dt * 10), vec3(0, 1, 0));

	fp.prep();
	fp.draw(camera, obj);
	fp.draw(camera, plane);
	fp.post();

	cp.prep();
	cp.draw();
	cp.post();
}

void TestApp::onPlay()
{
	//obj.transform = glm::mat4(1);
	obj.diffuse = "SoulSpearsoulspear_diffuse.tga";					// default
	obj.mesh = "SoulSpear_Low:SoulSpear_Low1";						// default
	obj.tris = "SoulSpear_Low:SoulSpear_Low1";						// default

	plane.diffuse = "White";
	plane.mesh = "Quad";
	plane.tris = "Quad";

	plane.transform = glm::rotate(plane.transform, 270.0f, vec3(1, 0, 0));

	fp.shader = "Light";
	fp.fbo = "Forward";

	cp.shader = "Post";
	cp.fbo = "ShadowMap";						// default
}

void TestApp::onInit()
{
	nsfw::Assets::instance().loadFBX("SoulSpear", "../resources/FBX/soulspear/soulspear.fbx");

	nsfw::Assets::instance().loadShader("Basic","../resources/shaders/basic.vert", "../resources/shaders/basic.frag");

	nsfw::Assets::instance().loadShader("Post", "../resources/shaders/post.vert", "../resources/shaders/post.frag");

	nsfw::Assets::instance().loadShader("Light", "../resources/shaders/light.vert", "../resources/shaders/light.frag");

	nsfw::Assets::instance().loadTexture("White", "../resources/textures/white.png");

	// foward rendering
	const char   *names[] = { "ForwardFinal", "ForwardDepth" };
	const unsigned deps[] = { GL_RGBA, GL_DEPTH_COMPONENT };
	nsfw::Assets::instance().makeFBO("Forward", 800, 600, 2, names, deps);

	// shadow map
	const char *s_names[] =		{ "PostFinal", "PostDepth" };
	const unsigned s_deps[] =	{ GL_RGBA, GL_DEPTH_COMPONENT };
	nsfw::Assets::instance().makeFBO("ShadowMap", 800, 600, 1, s_names, s_deps);

	camera.lookAt(glm::vec3(3, 3, 3),		// offset  
		glm::vec3(0, 0, 0),		// origin
		glm::vec3(0, 1, 0));	// up
}

void TestApp::onTerm()
{

}