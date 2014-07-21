
/*
* (WatershedPixel类)根据灰度值对图像像素进行排序
*/
#ifndef WATERSHEDPIXEL_H
#define WATERSHEDPIXEL_H

#include <vector>

class WatershedPixel {
	static const int INIT = -1;	// 用来初始化图像
	static const int MASK = -2;	// 指示新像素点将被处理（每个层级的初始值）
	static const int WSHED = 0;	// 表明像素点属于某个分水岭
	static const int FICTITIOUS = -3;	// 虚拟像素点

	int x;	// 像素点x坐标
	int y;	// 像素点y坐标
	char height;	// 像素点的灰度值
	int label;	// 用于分水岭浸没算法的标签
	int dist;	// 操作像素时用到的距离

	std::vector<WatershedPixel*> neighbours;	// 储存邻域像素

public:
	WatershedPixel(int x, int y, char height) { // 像素点构造函数
		this->x = x;
		this->y = y;
		this->height = height;
		label = INIT;
		dist = 0;
		neighbours.reserve(8);	// 用于存储8连通的邻域像素
	}
	WatershedPixel() { label = FICTITIOUS; } // 虚拟像素点构造函数

	void addNeighbour(WatershedPixel* neighbour) { // 添加邻域像素
		neighbours.push_back(neighbour);
	}
	std::vector<WatershedPixel*>& getNeighbours() { // 获取邻域像素
		return neighbours; 
	}

	/* 获取像素灰度值和坐标*/
	char getHeight() const { return height; } 
	int getIntHeight() const { return (int) height&0xff; } 
	int getX() const {	return x; }
    int getY() const {	return y; }

	/* 设置和获取标签 */
    void setLabel(int label) { this->label = label; }
    void setLabelToINIT() { label = INIT; }
    void setLabelToMASK() { label = MASK; }
    void setLabelToWSHED() { label = WSHED; }
    int getLabel() {   return label; }

	/* 判断当前标签状态 */
    bool isLabelINIT() { return label == INIT; }
    bool isLabelMASK() { return label == MASK; }
    bool isLabelWSHED() { return label == WSHED; }

	/* 设置和获取距离 */
    void setDistance(int distance) { dist = distance; }
    int getDistance() { return dist; }

	/* 判断是否为虚拟像素 */
    bool isFICTITIOUS() { return label == FICTITIOUS; }

	/* 判断是否所有邻域像素为分水岭（用于绘制最后的分水岭） */
    bool allNeighboursAreWSHED() {
        for (unsigned i = 0 ; i < neighbours.size() ; i++) {
            WatershedPixel* r =  neighbours.at(i);
            if ( !r->isLabelWSHED() ) return false;
        }
        return true;
    }
};

#endif