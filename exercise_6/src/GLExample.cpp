#include "GLExample.h"
#include "Cube.h"
#include <iostream>

namespace cgCourse
{
	GLExample::GLExample(glm::uvec2 _windowSize, std::string _title): GLApp(_windowSize, _title, false) {}

	bool GLExample::init()
	{
		// Framebuffer size and window size may be different in high-DPI displays
		// setup camera with standard view (static for our case)
		cam.create(	getFramebufferSize(),
					glm::vec3(3, 3, -3),
					glm::vec3(0, 0, 0),
					glm::vec3(0, 1, 0)
					);

		programForCube = std::make_shared<ShaderProgram>(std::string(SHADER_DIR) + "/Cube");
		programForTorus = std::make_shared<ShaderProgram>(std::string(SHADER_DIR) + "/Torus");
		programForTorusNormals = std::make_shared<ShaderProgram>(std::string(SHADER_DIR) + "/Normals");
		programForLightBox = std::make_shared<ShaderProgram>(std::string(SHADER_DIR) + "/Lightbox");

		// create box for light position
		lightbox = std::make_shared<Cube>();
		if(!lightbox->createVertexArray(0, 1, 2, 3, 4))
			return false;

		lightbox->setPosition(glm::vec3(0.0, 0.5, -1.0));
		lightbox->setScaling(glm::vec3(0.05, 0.05, 0.05));
		lightboxColor = glm::vec3(1.0, 1.0, 1.0);

		// Init models
		cube = std::make_shared<Cube>();
		if(!cube->createVertexArray(0, 1, 2, 3, 4))
			return false;

		cube->setPosition(glm::vec3(-2.5, 0.5, 1.5));
		cube->setScaling(glm::vec3(1.5, 1.5, 1.5));

		torus = std::make_shared<Torus>();
		if(!torus->createVertexArray(0, 1, 2, 3, 4))
			return false;

		torus->setPosition(glm::vec3(1.5, 0.0, 0.0));

		// Init multiline field for normals of objects
		normalsTorus = std::make_shared<MultiLine>(torus->getPositions(), torus->getNormals());
		if(!normalsTorus->createVertexArray(0, 1, 2, 3, 4))
			return false;

		normalsTorus->setPosition(glm::vec3(1.0, 0.0, 0.0));

		light.ambientTerm = {1, 1, 1};
		light.diffuseTerm = {1, 1, 1};
		light.specularTerm = {1, 1, 1};


		/* TODO: load the following textures here:
		 *       - cubeNormaltex - the normal texture for the cube
		 *       - torusNormaltex - the normal texture for the torus
		 *       It is also possible to use the brickwall for the cube, may be it is easier to debug.
		 */
		cubeNormaltex = std::make_shared<Texture>();
		cubeNormaltex->loadFromFile(std::string(RES_DIR) + "/container_normal.jpg");

		torusNormaltex = std::make_shared<Texture>();
		torusNormaltex->loadFromFile(std::string(RES_DIR) + "/brickwall_normal.jpg");
		// END TODO


		cubetex = std::make_shared<Texture>();
		cubetex->loadFromFile(std::string(RES_DIR) + "/container.png");

		cubetexSpec = std::make_shared<Texture>();
		cubetexSpec->loadFromFile(std::string(RES_DIR) + "/container_specular.png");

		torustex = std::make_shared<Texture>();
		torustex->loadFromFile(std::string(RES_DIR) + "/brickwall.jpg");

		torustexSpec = std::make_shared<Texture>();
		torustexSpec->loadFromFile(std::string(RES_DIR) + "/brickwall_specular.jpg");

		return true;
	}

	bool GLExample::update()
	{
		torus->setRotation(glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		if(animationDir == Forward)
		{
			if(animation > 1.5)
				animationDir = Backward;
			else
				animation += 0.01;
		}
		else
		{
			if(animation < -4.0)
				animationDir = Forward;
			else
				animation -= 0.01;
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

		update();

		renderLightBox();

		addLightVariables(programForCube);
		addLightVariables(programForTorus);

		renderCubes();
		renderTorus();

		return true;
	}

	void GLExample::addLightVariables(const std::shared_ptr<ShaderProgram> & program)
	{
		program->bind();
		glUniform3fv(program->getUniformLocation("camPos"), 1, &cam.getPosition()[0]);
		glUniform3fv(program->getUniformLocation("light.position"), 1, &lightbox->getPosition()[0]);
		glUniform3fv(program->getUniformLocation("light.ambient"), 1, &light.ambientTerm[0]);
		glUniform3fv(program->getUniformLocation("light.diffuse"), 1, &light.diffuseTerm[0]);
		glUniform3fv(program->getUniformLocation("light.specular"), 1, &light.specularTerm[0]);
		program->unbind();
	}

	void GLExample::renderCubes()
	{
		programForCube->bind();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, cubetex->getTexHandle());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, cubetexSpec->getTexHandle());

		glUniform1i(programForCube->getUniformLocation("cubetex"), 0);
		glUniform1i(programForCube->getUniformLocation("cubetexSpec"), 1);

		/* TODO: bind the normal map textures for shaders with glBindTexture and glActiveTexture.
		 *       check the OpenGL documentation to understand these commands.
		 *       Also, remember that you will have to set the uniform variables in
		 *       the shader correctly as well so that the program know which uniform
		 *       variable in the shader is meant to be which texture layer when
		 *       used with glActiveTexture.
		 */

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, cubeNormaltex->getTexHandle());
		glUniform1i(programForCube->getUniformLocation("cubeNormaltex"), 2);

		// END TODO


		mvpMatrix = cam.getViewProjectionMatrix() * cube->getModelMatrix();
		glUniformMatrix4fv(programForCube->getUniformLocation("modelMatrix"), 1, GL_FALSE, &cube->getModelMatrix()[0][0]);
		glUniformMatrix4fv(programForCube->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
		cube->draw();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);


		/* TODO: unbind textures by setting all glBindTextures for all active texture layers
		 *       to zero.
		 */

		// glActiveTexture(GL_TEXTURE2);
		// glBindTexture(GL_TEXTURE_2D, 0);

		// END TODO


		programForCube->unbind();
	}

	void GLExample::renderTorus()
	{
		programForTorus->bind();

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, torustex->getTexHandle());
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, torustexSpec->getTexHandle());

		glUniform1i(programForTorus->getUniformLocation("torustex"), 0);
		glUniform1i(programForTorus->getUniformLocation("torustexSpec"), 1);


		/* TODO: apply the normal map for the torus as well
		 *       analogue to the function above.
		 */

		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, this->torusNormaltex->getTexHandle());
		glUniform1i(programForTorus->getUniformLocation("torusNormaltex"), 2);

		// END TODO


		mvpMatrix = cam.getViewProjectionMatrix() * torus->getModelMatrix();
		glUniformMatrix4fv(programForTorus->getUniformLocation("modelMatrix"), 1, GL_FALSE, &torus->getModelMatrix()[0][0]);
		glUniformMatrix4fv(programForTorus->getUniformLocation("mvpMatrix"), 1, GL_FALSE, &mvpMatrix[0][0]);
		torus->draw();


		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, 0);


		/* TODO: unbind textures by setting all glBindTextures for all active texture layers
		*       to zero.
		*/

		// glActiveTexture(GL_TEXTURE2);
		// glBindTexture(GL_TEXTURE_2D, 0);


		// END TODO


		programForTorus->unbind();

		drawTorusNormals = false;
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
		glUniform3fv(programForLightBox->getUniformLocation("objectColor"), 1, &lightboxColor[0]);
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

