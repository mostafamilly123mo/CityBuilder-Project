#pragma once

#include "UsefulStuff.h"

GLboolean GLFWRunner();
GLvoid render(std::vector<std::pair<std::pair<int, int>, OBJECT_TYPE>>& objects, int coolorMapWidth, int colorMapHeight, ENVIRONMENT_TIME environmentTime, GROUND_TYPE groundType, GLuint building4FloorsCount);
GLuint loadCubemap(vector<std::string> faces);
GLvoid loadModels();
GLvoid processInput(GLFWwindow* window);
GLvoid framebufferSizeCallback(GLFWwindow* window, int width, int height);
GLvoid GLFWDestroyer();
GLvoid deltaTimeUpdater();
GLvoid scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
GLvoid mouseCallBack(GLFWwindow* window, double xpos, double ypos);

// camera
Camera camera;
GLfloat lastX;
GLfloat lastY;
GLboolean firstMouse = true;

// timing
// time between current frame and last frame
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;

// GLFW stuff
GLFWwindow* window;
const GLuint SCR_WIDTH = 1280;
const GLuint SCR_HEIGHT = 720;

// OpenGl arrays and Buffers
GLuint VAOsNumber = 0, VBOsNumber = 0, EBOsNumber = 0;
GLuint* VAOs = nullptr, * VBOs = nullptr, * EBOs = nullptr;

// irrklang sound
irrklang::ISoundEngine* SoundEngine = irrklang::createIrrKlangDevice();
irrklang::ISound* sound;

// Models

Model streetModel;
Model building1Model;
Model building2Model;
Model building3Model;
Model building4ModelsFloor0;
Model building4ModelsFloor1;
Model building4ModelsFloor2;
Model floorModel;
Model rockFloor;
Model sandFloor;
Model grassFloor;
Model lampModel;
Model treeModel;
Model carModel;
Model blendModel;

GLboolean GLFWRunner()
{
	lastX = SCR_WIDTH / 2.0f;
	lastY = SCR_HEIGHT / 2.0f;

	// initialize and configure glfw
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// window creation
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Modern OpenGL WINDOW BUFFER", NULL, NULL);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		GLFWDestroyer();
		return false;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	glfwSetCursorPosCallback(window, mouseCallBack);
	glfwSetScrollCallback(window, scrollCallback);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// glew init
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		GLFWDestroyer();
		return false;
	}

	stbi_set_flip_vertically_on_load(true);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return true;
}

GLvoid render(std::vector<std::pair<std::pair<int, int>, OBJECT_TYPE>>& objects,
			  int coolorMapWidth, int colorMapHeight,
			  ENVIRONMENT_TIME environmentTime, GROUND_TYPE groundType,
			  GLuint building4FloorsCount)
{

	// build and compile shaders
	// -------------------------
	Shader modelShader("Shaders/model_loading_vertex.shader", "Shaders/model_loading_fragment.shader");
	Shader skyboxShader("Shaders/skybox_vertex.shader", "Shaders/skybox_fragment.shader");
	Shader blendShader("Shaders/blend_vertex.shader", "Shaders/blend_fragment.shader");

	// =================================================================
	// calculate the number of lamps
	int numberOfLambs = 0;
	for (auto& object : objects)
		if (object.second == LAMP)
			numberOfLambs++;

	modelShader.use();
	modelShader.setInt("LAMPS_NUMBER", numberOfLambs);
	// =================================================================

	loadModels();

	//===================================================================
	// SkyBox
	stbi_set_flip_vertically_on_load(false);

	unsigned int skyboxVAO, skyboxVBO;
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);

	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(SKYBOX_VERTICES), &SKYBOX_VERTICES,
				 GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	vector<std::string> faces;
	if (environmentTime == DAY || environmentTime == NONE)
	{
		faces.push_back("resources/textures/skybox/day/right.jpg");
		faces.push_back("resources/textures/skybox/day/left.jpg");
		faces.push_back("resources/textures/skybox/day/top.jpg");
		faces.push_back("resources/textures/skybox/day/bottom.jpg");
		faces.push_back("resources/textures/skybox/day/front.jpg");
		faces.push_back("resources/textures/skybox/day/back.jpg");
	}
	else
	{
		faces.push_back("resources/textures/skybox/night/right.jpg");
		faces.push_back("resources/textures/skybox/night/left.jpg");
		faces.push_back("resources/textures/skybox/night/top.jpg");
		faces.push_back("resources/textures/skybox/night/bottom.jpg");
		faces.push_back("resources/textures/skybox/night/front.jpg");
		faces.push_back("resources/textures/skybox/night/back.jpg");
	}

	unsigned int cubemapTexture = loadCubemap(faces);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);

	stbi_set_flip_vertically_on_load(true);

	//===================================================================
	// start the sound

	if (environmentTime == DAY || environmentTime == NONE)
		sound = SoundEngine->play2D("resources/audio/morning_sound.mp3", true,
									false, true);
	else
		sound = SoundEngine->play2D("resources/audio/night_sound.mp3", true, false,
									true);

	sound->setVolume(0.08);

	//===================================================================
	// render loop

	while (!glfwWindowShouldClose(window))
	{
		deltaTimeUpdater();
		processInput(window);

		glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// view/projection transformations

		//===================================================================
		// config lighting
		modelShader.use();
		modelShader.setVec3("viewPos", camera.Position);
		modelShader.setVec3("material.specular", 0.5f, 0.5f, 0.5f);
		modelShader.setFloat("material.shininess", 64.0f);
		modelShader.setVec3("material.diffuse", 0.5f, 0.5f, 0.5f);
		modelShader.setVec3("dirLight.direction", -0.2f, -1.0f, -0.3f);

		if (environmentTime == DAY || environmentTime == NONE)
		{
			modelShader.setVec3("dirLight.ambient", 0.3f, 0.3f, 0.3f);
			modelShader.setVec3("dirLight.diffuse", 0.6f, 0.6f, 0.6f);
			modelShader.setVec3("dirLight.specular", 0.6f, 0.6f, 0.6f);

			int lampNumber = 0;
			for (auto& object : objects)
			{
				if (object.second == LAMP)
				{
					int x = object.first.first - coolorMapWidth / 2;
					int y = object.first.second - colorMapHeight / 2;
					string number = std::to_string(lampNumber++);
					modelShader.setVec3("pointLights[" + number + "].position", glm::vec3(x, 1.0f, y));
					modelShader.setVec3("pointLights[" + number + "].ambient", 0.0f, 0.0f, 0.0f);
					modelShader.setVec3("pointLights[" + number + "].diffuse", 0.0f, 0.0f, 0.0f);
					modelShader.setVec3("pointLights[" + number + "].specular", 0.0f, 0.0f, 0.0f);
					modelShader.setFloat("pointLights[" + number + "].constant", 1.0f);
					modelShader.setFloat("pointLights[" + number + "].linear", 0.09f);
					modelShader.setFloat("pointLights[" + number + "].quadratic", 0.032f);
				}
			}
		}
		else if (environmentTime == NIGHT)
		{
			modelShader.setVec3("dirLight.ambient", 0.05f, 0.05f, 0.05f);
			modelShader.setVec3("dirLight.diffuse", 0.4f, 0.4f, 0.4f);
			modelShader.setVec3("dirLight.specular", 0.5f, 0.5f, 0.5f);

			int lampNumber = 0;
			for (auto& object : objects)
			{
				if (object.second == LAMP)
				{
					int x = object.first.first - coolorMapWidth / 2;
					int y = object.first.second - colorMapHeight / 2;
					string number = std::to_string(lampNumber++);
					modelShader.setVec3("pointLights[" + number + "].position", glm::vec3(x, 1, y));
					modelShader.setVec3("pointLights[" + number + "].ambient", 0.05f, 0.05f, 0.05f);
					modelShader.setVec3("pointLights[" + number + "].diffuse", 0.8f, 0.8f, 0.8f);
					modelShader.setVec3("pointLights[" + number + "].specular", 1.0f, 1.0f, 1.0f);
					modelShader.setFloat("pointLights[" + number + "].constant", 1.0f);
					modelShader.setFloat("pointLights[" + number + "].linear", 0.09);
					modelShader.setFloat("pointLights[" + number + "].quadratic", 0.032);
				}
			}
		}

		//===================================================================

		modelShader.setVec3("spotLight.position", camera.Position);
		modelShader.setVec3("spotLight.direction", camera.Front);
		modelShader.setVec3("spotLight.ambient", 0.0f, 0.0f, 0.0f);
		modelShader.setVec3("spotLight.diffuse", 0.0f, 0.0f, 0.0f);
		modelShader.setVec3("spotLight.specular", 0.0f, 0.0f, 0.0f);
		modelShader.setFloat("spotLight.constant", 1.0f);
		modelShader.setFloat("spotLight.linear", 0.09f);
		modelShader.setFloat("spotLight.quadratic", 0.032f);
		modelShader.setFloat("spotLight.cutOff", glm::cos(glm::radians(12.5f)));
		modelShader.setFloat("spotLight.outerCutOff", glm::cos(glm::radians(15.0f)));

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		modelShader.setMat4("projection", projection);
		modelShader.setMat4("view", view);

		// Floor
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(0.0f, -2.5f, 0.0f));
		model = glm::scale(model, glm::vec3(coolorMapWidth, 1, colorMapHeight));
		modelShader.setMat4("model", model);

		if (groundType == SOLID)
			floorModel.Draw(modelShader.ID);
		else if (groundType == ROCKS)
			rockFloor.Draw(modelShader.ID);
		else if (groundType == SAND)
			sandFloor.Draw(modelShader.ID);
		else if (groundType == GRASS)
			grassFloor.Draw(modelShader.ID);

		//===================================================================
		// drawing all the models
		for (auto& object : objects)
		{
			int x = object.first.first - coolorMapWidth / 2;
			int y = object.first.second - colorMapHeight / 2;

			OBJECT_TYPE objectType = object.second;

			switch (objectType)
			{
				case STREET_HORIZONTAL:
					{
						model = glm::mat4(1.0f);
						model = glm::translate(model, glm::vec3(x, -3.48f, y));
						model = glm::scale(model, glm::vec3(15, 1, 5));
						modelShader.setMat4("model", model);
						streetModel.Draw(modelShader.ID);
						break;
					}
				case STREET_VERTICAL:
					{
						model = glm::mat4(1.0f);
						model = glm::translate(model, glm::vec3(x, -3.50f, y));
						model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
						model = glm::scale(model, glm::vec3(15, 1, 5));
						modelShader.setMat4("model", model);
						streetModel.Draw(modelShader.ID);
						break;
					}
				case BUILDING1:
					{
						model = glm::mat4(1.0f);
						model = glm::translate(model, glm::vec3(x, -2.3f, y));
						model = glm::scale(model, glm::vec3(2.5, 2.5, 2.5));
						modelShader.setMat4("model", model);
						building1Model.Draw(modelShader.ID);
						break;
					}
				case BUILDING2:
					{
						model = glm::mat4(1.0f);
						model = glm::translate(model, glm::vec3(x, -2.3f, y));
						model = glm::scale(model, glm::vec3(5, 5, 5));
						modelShader.setMat4("model", model);
						building2Model.Draw(modelShader.ID);
						break;
					}
				case BUILDING3:
					{
						model = glm::mat4(1.0f);
						model = glm::translate(model, glm::vec3(x, -5.4f, y));
						model = glm::scale(model, glm::vec3(35, 35, 35));
						modelShader.setMat4("model", model);
						building3Model.Draw(modelShader.ID);
						break;
					}
				case BUILDING4:
					{
						if (building4FloorsCount <= 3)
							building4FloorsCount = 2;

						int ditanceBetweenFloors = 0;

						model = glm::mat4(1.0f);
						model = glm::translate(model, glm::vec3(x, 0, y));
						model = glm::scale(model, glm::vec3(5, 5, 5));
						modelShader.setMat4("model", model);
						building4ModelsFloor0.Draw(modelShader.ID);
						ditanceBetweenFloors += 10.5;

						for (int i = 2; i <= building4FloorsCount + 1; i++)
						{
							if (i % 2 == 0)
							{
								model = glm::mat4(1.0f);
								model = glm::translate(model, glm::vec3(x, ditanceBetweenFloors, y));
								model = glm::scale(model, glm::vec3(5, 5, 5));
								modelShader.setMat4("model", model);
								building4ModelsFloor2.Draw(modelShader.ID);
							}
							else
							{
								model = glm::mat4(1.0f);
								model = glm::translate(model, glm::vec3(x, ditanceBetweenFloors, y));
								model = glm::scale(model, glm::vec3(5, 5, 5));
								modelShader.setMat4("model", model);
								building4ModelsFloor1.Draw(modelShader.ID);
							}
							ditanceBetweenFloors += 10.5;

						}

						break;
					}
				case LAMP:
					{
						model = glm::mat4(1.0f);
						model = glm::translate(model, glm::vec3(x, -2.5, y));
						model = glm::scale(model, glm::vec3(4, 4, 4));
						modelShader.setMat4("model", model);
						lampModel.Draw(modelShader.ID);
						break;
					}
				case CAR:
					{
						model = glm::mat4(1.0f);
						model = glm::translate(model, glm::vec3(x, -2.5, y));
						model = glm::scale(model, glm::vec3(4, 4, 4));
						modelShader.setMat4("model", model);
						carModel.Draw(modelShader.ID);
						break;
					}
				case TREE:
					{
						model = glm::mat4(1.0f);
						model = glm::translate(model, glm::vec3(x, -2.5, y));
						model = glm::scale(model, glm::vec3(1, 1, 1));
						modelShader.setMat4("model", model);
						treeModel.Draw(modelShader.ID);
						break;
					}
				case BLENDING_OBJECT:
					{
						blendShader.use();
						blendShader.setMat4("projection", projection);
						blendShader.setMat4("view", view);
						model = glm::mat4(1.0f);
						model = glm::translate(model, glm::vec3(x, -0.3f, y));
						model = glm::scale(model, glm::vec3(1, 1, 1));
						blendShader.setMat4("model", model);
						blendModel.Draw(blendShader.ID);
						break;
					}
			}
		}
		//===================================================================

		glDepthFunc(GL_LEQUAL); // change depth function so depth test passes when
								// values are equal to depth buffer's content
		skyboxShader.use();
		view = glm::mat4(glm::mat3(camera.GetViewMatrix())); // remove translation from the view matrix
		skyboxShader.setMat4("view", view);
		skyboxShader.setMat4("projection", projection);
		// skybox cube
		glBindVertexArray(skyboxVAO);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS); // set depth function back to default

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse
		// moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//===================================================================
}

GLuint loadCubemap(vector<std::string> faces)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	int width, height, nrChannels;
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data =
			stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height,
						 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cube map texture failed to load at path: " << faces[i]
				<< std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	return textureID;
}

GLvoid loadModels()
{
	std::cout << "Models loading started" << std::endl;

	streetModel.loadModel("resources/models/street/street.obj");

	building1Model.loadModel("resources/models/building1/Cottage_FREE.obj");
	building2Model.loadModel("resources/models/building2/building_interior.obj");
	building3Model.loadModel("resources/models/building3/asiaBuilding.obj");
	building4ModelsFloor0.loadModel("resources/models/building5/floor0.obj");
	building4ModelsFloor1.loadModel("resources/models/building5/floor1.obj");
	building4ModelsFloor2.loadModel("resources/models/building5/floor2.obj");

	floorModel.loadModel("resources/models/floor - SOLID/untitled.obj");
	rockFloor.loadModel("resources/models/floor - ROCK/untitled.obj");
	sandFloor.loadModel("resources/models/floor - SAND/untitled.obj");
	grassFloor.loadModel("resources/models/floor - GRASS/untitled.obj");

	lampModel.loadModel("resources/models/lamp/lamp.obj");
	treeModel.loadModel("resources/models/tree/tree.obj");
	carModel.loadModel("resources/models/car/car.obj");
	blendModel.loadModel("resources/models/ball/ball.obj");

	std::cout << "Models loading ended" << std::endl;
}

// process all input: query GLFW whether relevant keys are pressed/released
// this frame and react accordingly
GLvoid processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		camera.MovementSpeed = 200;

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, deltaTime);

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, deltaTime);

	camera.MovementSpeed = 50;
}

// glfw: whenever the window size changed (by OS or user resize) this callback
// function executes
GLvoid framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

GLvoid mouseCallBack(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

GLvoid scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}

// This method is used to update the delta Time
GLvoid deltaTimeUpdater()
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

// terminate the glfw and to delete all the buffers that used
GLvoid GLFWDestroyer()
{
	if (VAOs != nullptr)
		delete[] VAOs;

	if (VBOs != nullptr)
		delete[] VBOs;

	if (EBOs != nullptr)
		delete[] EBOs;

	if (sound != nullptr)
	{
		sound->stop();
		sound->drop();
	}

	glfwTerminate();
}
