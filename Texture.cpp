#include"Texture.h"

//laden der texture
Texture::Texture(const char* image, const char* texType, GLuint slot, GLenum format, GLenum pixelType)
{
	type = texType;

	int widthImg, heightImg, numColCh;
	// Dreht die Texture vertikall
	stbi_set_flip_vertically_on_load(true);
	//liest das bild von einer datai und speichert es in bytes
	unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);

	//generiert die texture
	glGenTextures(1, &ID);

	glActiveTexture(GL_TEXTURE0 + slot);
	unit = slot;
	glBindTexture(GL_TEXTURE_2D, ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// wenn GL_CLAMP_TO_BORDER benutzt wird :)
	// float flatColor[] = {0.0f, 0.0f, 0.0f, 1.0f}
	// glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

	// Generates the Texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
	//               type          colorCh    width    height	   imgcolorCh    datatype      imgdata

	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(bytes);

	glBindTexture(GL_TEXTURE_2D, 0);

}

//nehmen Uniform vom vert/frag shader
void Texture::texUnit(Shader& shader, const char* uniform, GLuint unit)
{
	GLuint texUni = glGetUniformLocation(shader.ID, uniform);

	shader.Activate();

	glUniform1i(texUni, unit);
}


void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, ID);
}

void Texture::Unbind()
{
	glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}
