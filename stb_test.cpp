#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

using namespace std;

int main() {
	std::cout << "Hello, STB_Image" << std::endl;

	string inputPath = "./yangchaoyue.png";
	int imageWidth, imageHeight, nrComponents;

	// 加载图片获取宽、高、颜色通道信息
	unsigned char *imagedata = stbi_load(inputPath.c_str(), &imageWidth, &imageHeight, &nrComponents, STBI_default);
    std::cout << "测试 STB_Image 读取到的信息为：imageWidth = "<< imageWidth << 
             ",imageHeight = "<<imageHeight << ", nrComponents = " << nrComponents 
             << std::endl;  

    // 输出的宽和高为原来的一半
	int outputWidth = imageWidth / 2;
	int outputHeight = imageHeight / 2;
    // 申请内存
	auto *outputImageData = (unsigned char *)malloc(outputWidth * outputHeight * nrComponents);
    std::cout << "测试 STBIR_RESIZE, 改变后的图片尺寸为：outputWidth = "<< outputWidth<<", outputHeight = "<< outputHeight << std::endl;
	// 改变图片尺寸
	stbir_resize(imagedata, imageWidth, imageHeight, 0, outputImageData, outputWidth, outputHeight, 0, STBIR_TYPE_UINT8, nrComponents, STBIR_ALPHA_CHANNEL_NONE, 0,
		STBIR_EDGE_CLAMP, STBIR_EDGE_CLAMP,
		STBIR_FILTER_BOX, STBIR_FILTER_BOX,
		STBIR_COLORSPACE_SRGB, nullptr
		);

	string outputPath = "./yangchaoyue_output.png";
    std::cout << "测试 STB_WRITE 要写入的地址为： "<< outputPath << std::endl;
	// 写入图片
	stbi_write_png(outputPath.c_str(), outputWidth, outputHeight, nrComponents, outputImageData, 0);

	stbi_image_free(imagedata);
	stbi_image_free(outputImageData);
	return 0;
}
