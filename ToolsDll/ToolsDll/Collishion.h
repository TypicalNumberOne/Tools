//Colishion.h 碰撞

#ifndef _COLLISHION_H_
#define _COLLISHION_H_

#include "ToolsDll.h"

//碰撞盒体
class TOOLSDLL_API CollisionBoxBody
{
private:
	//盒体宽度
	int BoxWidth;
	//盒体高度
	int BoxHeight;
	//盒体中心点
	int BoxCentralPoint;

private:
	//图像宽度
	int ImageWidth;
	//图像宽度
	int ImageHeight;	

public:
	//碰撞盒体初始化
	CollisionBoxBody(int boxWidth, int boxHeight,
		int imageWidth,	int imageHeight, int boxCentralPoint)
	{
		this->BoxWidth = boxWidth;
		this->BoxHeight = boxHeight;
		this->ImageWidth = imageWidth;
		this->ImageHeight = imageWidth;
		this->BoxCentralPoint = boxCentralPoint;
	}

};

//盒体位置
class TOOLSDLL_API BoxBodyLocation
{

};

//碰撞
class TOOLSDLL_API Collision
{
private:
	std::vector<CollisionBoxBody> vecCollisionBoxBody;

public:
	//碰撞 初始化
	Collision(CollisionBoxBody& collisionBoxBody)
	{
		this->vecCollisionBoxBody.push_back(collisionBoxBody);
	}

	//盒体碰撞管理
	bool BoxCollisionManage();

	//碰撞检测
	bool CollisionDetection();
};

#endif