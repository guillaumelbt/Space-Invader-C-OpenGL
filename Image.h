#ifndef Image_h 
#define Image_h 

#include <string>

class Image
{
public:
	int width;
	int height;
	int nrChannels;
	unsigned char* pixel_data;
	int texture_slot;

	Image();	
	Image(const char file[], int tex_slot);
	Image(std::string file, int tex_slot);
	Image(const Image& obj);
	~Image();
};

#endif