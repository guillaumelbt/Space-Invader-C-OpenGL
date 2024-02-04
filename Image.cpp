

#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION 
#include "stb_image.h"

#include <assert.h>


Image::Image() 
{
	width = 0;
	height = 0;
	nrChannels = 0;
	pixel_data = NULL;
	texture_slot = 0;
}

Image::Image(const char file[], int tex_slot) 
{
	pixel_data = stbi_load(file, &width, &height, &nrChannels, 0);
	assert(("failed to load image", (pixel_data != 0)));
	texture_slot = tex_slot;
}

Image::Image(std::string file, int tex_slot)
{
	pixel_data = stbi_load(file.c_str(), &width, &height, &nrChannels, 0);
	assert(("failed to load image "+file, (pixel_data != 0)));
	texture_slot = tex_slot;
}

Image::Image(const Image& obj) 
{
	this->width = obj.width;
	this->height = obj.height;
	this->nrChannels = obj.nrChannels;
	this->pixel_data = obj.pixel_data;
	this->texture_slot = obj.texture_slot;
}

Image::~Image()
{
	stbi_image_free(pixel_data); 
}