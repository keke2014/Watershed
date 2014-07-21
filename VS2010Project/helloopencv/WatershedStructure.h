
/*
*  (WatershedStructure类)用于存储像素点WatershedPixel
*   并生成各像素点的邻域像素
*/
#ifndef WATERSHEDSTRUCTURE_H
#define WATERSHEDSTRUCTURE_H

#include <algorithm>
#include "WatershedPixel.h"

class WatershedStructure {
    std::vector<WatershedPixel*> watershedStructure;

public:
    WatershedStructure(char* pixels, int width, int height) {	// 结构体构造函数

        watershedStructure.reserve(width * height);	 // 根据像素点总数预分配空间
        /* 将每个像素点信息存入结构体 */
        for (int y = 0; y < height; ++y)
            for (int x = 0; x < width; ++x)
                watershedStructure.push_back(new WatershedPixel(x, y, pixels[x+y*width]));

        /* 计算各个像素点的8连通邻域像素 */
        for (int y = 0; y < height; ++y) {
            int offset = y * width;
            int topOffset = offset + width;
            int bottomOffset = offset - width;

            for (int x = 0; x < width; ++x) {
				int currentindex = x + y*width;	// 当前像素点索引
                WatershedPixel* currentPixel = watershedStructure.at(currentindex);

				if (x - 1 >= 0) {
                    currentPixel->addNeighbour(watershedStructure.at(currentindex-1)); // 左邻域
                    if (y - 1 >= 0)	 // 左下角
                        currentPixel->addNeighbour(watershedStructure.at(currentindex-1 - width));
                    if (y + 1 < height)	 // 左上角
                        currentPixel->addNeighbour(watershedStructure.at(currentindex-1 + width));
                }

                if (x + 1 < width) {
                    currentPixel->addNeighbour(watershedStructure.at(currentindex+1)); // 右邻域
                    if (y - 1 >= 0)	 // 右下角
                        currentPixel->addNeighbour(watershedStructure.at(currentindex+1 - width));
                    if (y + 1 < height) // 右上角
                        currentPixel->addNeighbour(watershedStructure.at(currentindex+1 + width));
                }

                if (y - 1 >= 0) // 下邻域
                    currentPixel->addNeighbour(watershedStructure.at(currentindex-width));

                if (y + 1 < height)	 // 上邻域
                    currentPixel->addNeighbour(watershedStructure.at(currentindex+width));
            }
        }

		/* 根据灰度值对结构体中的所有像素点从小到大进行排序 */
        std::sort(watershedStructure.begin(), watershedStructure.end(),
			[](WatershedPixel * pl, WatershedPixel * pr) { return pl->getIntHeight() < pr->getIntHeight(); });
    } // 构造结束

    ~WatershedStructure() {	// 释放像素类所占空间
        while (!watershedStructure.empty()) {
            WatershedPixel* p = watershedStructure.back();
            delete p; p = NULL;
            watershedStructure.pop_back();
        }
    }

    int size() { return watershedStructure.size(); }	// 返回像素点总数

    WatershedPixel* at(int i) { return watershedStructure.at(i); }	// 返回某个像素点
};

#endif