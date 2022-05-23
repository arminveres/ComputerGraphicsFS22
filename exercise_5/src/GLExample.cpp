#include "GLExample.h"
#include "Cube.h"
#include <iostream>

namespace cgCourse
{
	GLExample::GLExample(glm::uvec2 _windowSize, std::string _title): GLApp(_windowSize, _title, false)
	{
		mvpMatrix = glm::mat4(1);
		animation = 0.0;
		animationDir = Forward;
		drawTorusNormals = false; // just in case somebody wants to activate the normals
	}

	bool GLExample::init()
	{
		// Framebuffer size and window size may be different in high-DPI displays
		// setup camera with standard view (static for our case)
		cam.create(getFramebufferSize(),
			glm::vec3(3, 3, -3),
			glm::vec3(0, 0, 0),
			glm::vec3(0, 1, 0));

        programForCube = std::make_shared<ShaderProgram>(std::string(SHADER_DIR) + "/Cube");
        programForTorus = std::make_shared<ShaderProgram>(std::string(SHADER_DIR) + "/Torus");
		programForTorusNormals = std::make_shared<ShaderProgram>(std::string(SHADER_DIR) + "/Normals");
		programForLightBox = std::make_shared<ShaderProgram>(std::string(SHADER_DIR) + "/Lightbox");

		// create box for light position
		lightbox = std::make_shared<Cube>();
		if(!lightbox->createVertexArray(0, 1, 2, 3))
		{
			return false;
		};

		lightbox->setPosition(glm::vec3(0.0, 0.5, -1.5));
		lightbox->setScaling(glm::vec3(0.1, 0.1, 0.1));
		lightboxColor = glm::vec3(1.0, 1.0, 1.0);

		// Init models
		cube = std::make_shared<Cube>();
		bool constructed = cube->createVertexArray(0, 1, 2, 3);
		if (!constructed) return constructed;
		cube->setPosition(glm::vec3(-2.5, 0.5, 1.5));
        cube->setScaling(glm::vec3(1.5, 1.5, 1.5));

		torus = std::make_shared<Torus>();
		constructed = torus->createVertexArray(0, 1, 2, 3);
		torus->setPosition(glm::vec3(1.5, 0.0, 0.0));

        // Init multiline field for normals of objects
        normalsTorus = std::make_shared<MultiLine>(torus->getPositions(),
                                                         torus->getNormals());
        constructed = normalsTorus->createVertexArray(0, 1, 2, 3);
        normalsTorus->setPosition(glm::vec3(1.0, 0.0, 0.0));

		light.ambientTerm = glm::vec3(1.0, 1.0, 1.0);
		light.diffuseTerm = glm::vec3(1.0, 1.0, 1.0);
		light.specularTerm = glm::vec3(1.0, 1.0, 1.0);

		/* TODO: load the following textures here:
		 *       - cubetex - the diffuse texture
		 *       - cubetexSpec - the specular map
		 *       - torustex - the diffuse texture for the torus
		 *       - torustexSpec - the specular map for the torus
		 *      The easist thing will be if you start with the diffuse
		 *      texture for the cube. Don't forget to initialize the shared pointers existing
		 *      already in this class for this purpose.
		 */

		glActiveTexture(GL_TEXTURE0);
		cubetex = std::make_shared<Texture>();
		cubetex->loadFromFile(std::string(RES_DIR) + "/container.png");
		// cubetex->loadFromFile(std::string(RES_DIR) + "/wood.jpg");
		// cubetex->loadFromFile(std::string(RES_DIR) + "/obi-wan.png");

		glActiveTexture(GL_TEXTURE1);
		cubetexSpec = std::make_shared<Texture>();
		cubetexSpec->loadFromFile(std::string(RES_DIR) + "/container_specular.png");

		glActiveTexture(GL_TEXTURE2);
		torustex = std::make_shared<Texture>();
		// torustex->loadFromFile(std::string(RES_DIR) + "/container.png");
		// torustex->loadFromFile(std::string(RES_DIR) + "/golddiag.jpg");
		// torustex->loadFromFile(std::string(RES_DIR) + "/wood.jpg");
		// torustex->loadFromFile(std::string(RES_DIR) + "/obi-wan.png");
		torustex->loadFromFile(std::string(RES_DIR) + "/brickwall.jpg");

		glActiveTexture(GL_TEXTURE3);
		torustexSpec = std::make_shared<Texture>();
		// torustexSpec->loadFromFile(std::string(RES_DIR) + "/container_specular.png");
		torustexSpec->loadFromFile(std::string(RES_DIR) + "/brickwall_specular.jpg");

		// End TODO

        return constructed;
	}

    bool GLExample::update()
    {
		torus->setRotation(glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		if(animationDir == Forward)
		{
			if (animation > 1.5) {
				animationDir = Backward;
			} else {
				animation += 0.01;
			}
		} else {
			if (animation < -3.0) {
				animationDir = Forward;
			}
			else {
				animation -= 0.01;
			}
		}
		lightbox->setPosition(glm::vec3(animation, 0.5, -0.5));
        return true;
    }

	bool GLExample::render()
	{
		glEnable(GL_DEPTH_TEST);

        // Clear the color and depth buffers
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glEnable(GL_CULL_FACE);
        glCullFace(GL_BACK);

		renderLightBox();

		addLightVariables(programForCube);
		addLightVariables(programForTorus);

        renderCubes();
        renderTorus();
		// update();
		return true;
	}

	void GLExample::addLightVariables(const std::shared_ptr<ShaderProgram>& _program) {
		_program->bind();
		glUniform3fv(_program->getUniformLocation("camPos"), 1, &cam.getPosition()[0]);
		glUniform3fv(_program->getUniformLocation("light.position"), 1, &lightbox->getPosition()[0]);
		glUniform3fv(_program->getUniformLocation("light.ambient"), 1, &light.ambientTerm[0]);
		glUniform3fv(_program->getUniformLocation("light.diffuse"), 1, &light.diffuseTerm[0]);
		glUniform3fv(_program->getUniformLocation("light.specular"), 1, &light.specularTerm[0]);
		_program->unbind();
	}

    void GLExample::renderCubes() {
        programForCube->bind();
		/* TODO: bind textures for shaders with glBindTexture and glActiveTexture.
		 *       check the OpenGL documentation to understand these commands.
		 *       Also, remember that you will have to set the uniform variables in
		 *       the shader correctly as well so that the program know which uniform
		 *       variable in the shader is meant to be which texture layer when
		 *       used with glActiveTexture.
		 */

		glActiveTexture(GL_TEXTURE0);
		cubetex->bind(); // no need to bind them, it happens in the loadFromFile()
		GLint texDiff = programForCube->getUniformLocation("texDiff");
		glUniform1i(texDiff, 0);

		glActiveTexture(GL_TEXTURE1);
		cubetexSpec->bind(); // no need to bind them, it happens in the loadFromFile()
		GLint texSpec = programForCube->getUniformLocation("texSpec");
		glUniform1i(texSpec, 1);

		// End TODO

        mvpMatrix = cam.getViewProjectionMatrix() * cube->getModelMatrix();
		glUniformMatrix4fv(programForCube->getUniformLocation("modelMatrix"), 1, GL_FALSE, &cube->getModelMatrix()[0][0]);
		glUniformMatrix4fv(programForCube->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
        cube->draw();

		/* TODO: unbind textures by setting all glBindTextures for all active texture layers
		 *       to zero.
		 */

		cubetex->unbind();
		cubetexSpec->unbind();

		// End TODO
        programForCube->unbind();
    }

    void GLExample::renderTorus()
    {
        programForTorus->bind();

		// TODO: set bindings

		glActiveTexture(GL_TEXTURE0);
		torustex->bind(); // no need to bind them, it happens in the loadFromFile()
		GLint texDiff = programForTorus->getUniformLocation("texDiff");
		glUniform1i(texDiff, 0);

		glActiveTexture(GL_TEXTURE1);
		torustexSpec->bind(); // no need to bind them, it happens in the loadFromFile()
		GLint texSpec = programForTorus->getUniformLocation("texSpec");
		glUniform1i(texSpec, 1);

		// End TODO

		mvpMatrix = cam.getViewProjectionMatrix() * torus->getModelMatrix();
		glUniformMatrix4fv(programForTorus->getUniformLocation("modelMatrix"), 1, GL_FALSE, &torus->getModelMatrix()[0][0]);
		glUniformMatrix4fv(programForTorus->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
        torus->draw();

        programForTorus->unbind();

		/* TODO: unbind textures by setting all glBindTextures for all active texture layers
		*       to zero.
		*/

		torustex->unbind();
		torustexSpec->unbind();

		// End TODO

		// draw torus normals
		if(drawTorusNormals)
		{
			programForTorusNormals->bind();
			mvpMatrix = cam.getViewProjectionMatrix() * torus->getModelMatrix();
			glUniformMatrix4fv(programForTorusNormals->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
			normalsTorus->draw();
			programForTorusNormals->unbind();
		}
    }

	void GLExample::renderLightBox()
	{
		programForLightBox->bind();
		mvpMatrix = cam.getViewProjectionMatrix() * lightbox->getModelMatrix();
		glUniform3fv(programForLightBox->getUniformLocation("objectColor"), 1,&lightboxColor[0]);
		glUniformMatrix4fv(programForLightBox->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
		lightbox->draw();
		programForLightBox->unbind();
	}

	bool GLExample::end()
	{
        programForCube->deleteShaderProgramFromGPU();
        programForTorus->deleteShaderProgramFromGPU();
		programForTorusNormals->deleteShaderProgramFromGPU();
		return true;
	}
}

