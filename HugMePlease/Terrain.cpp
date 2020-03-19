#include "Terrain.h"


Terrain::Terrain(GLWindow& window, std::string const& filePath)
	: model(filePath, window), Object(window) {
}

void Terrain::render(const glm::mat4 viewMatrix, const glm::mat4& projection) {
	program->useProgram();

	// Model matrix
	glm::mat4 modelMatrix(1.f);
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = glm::scale(modelMatrix, scaleValue);

	// Uniforms
	program->setMat4("model", modelMatrix);
	program->setMat4("view", viewMatrix);
	program->setMat4("projection", projection);

	// Model rendering
	model.renderModel(program);
}
