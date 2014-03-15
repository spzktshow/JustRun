//
//  MSGeometry.h
//  HelloCpp
//
//  Created by RockLee on 13-9-29.
//
//

#ifndef __HelloCpp__MSGeometry__
#define __HelloCpp__MSGeometry__
#include <cocos2d.h>
#include "moonSugar.h"

NS_MS_BEGIN
/********Matrix****/
class MSMatrix
{
public:
    MSMatrix(int col, int row);
    int col;
    int row;
};

/********MatrixIndex*******/
class MSMatrixIndex
{
public:
    MSMatrixIndex(int colIndex, int rowIndex);
    int colIndex;
    int rowIndex;
};

/*********Node***********/
class MSNode
{
public:
    MSMatrixIndex* matrixIndex;
    MSMatrix* matrix;
    
    MSNode(int col, int row, int colIndex, int rowIndex);
    virtual ~MSNode();
};

/******************Matrix3d**********/
class MSMatrix3D : public MSMatrix
{
public:
	MSMatrix3D(int x, int y, int z);
	MSMatrix3D(int col, int row);//y = 0;
	int x;//col
	int y;//
	int z;//row
};

/*******************MatrixIndex3d*************/
class MSMatrixIndex3D : public MSMatrixIndex
{
public:
	MSMatrixIndex3D(int xIndex, int yIndex, int zIndex);
	MSMatrixIndex3D(int colIndex, int rowIndex);//y = 0;
	int xIndex;//colIndex
	int yIndex;//
	int zIndex;//rowIndex
};

/*******************Point3D*************/
class MSPoint3D : public cocos2d::Point
{
public:
	MSPoint3D(float xValue, float yValue, float zValue);
	float z;
};
/*************Node3D***************/
class MSNode3D : public MSNode
{
public:
	MSNode3D(int x, int y, int z, int xIndex, int yIndex, int zIndex);
	MSNode3D(int col, int row, int colIndex, int rowIndex);
	MSMatrixIndex3D* matrixIndex3d;
	MSMatrix3D* matrix3d;

	~MSNode3D();
};

/************coordinateUitls**********************/
class CoordinateUtils
{
public:
	static float calculateCoordinateSystem(float y, const cocos2d::Size & size);
};

NS_MS_END;

#endif /* defined(__HelloCpp__MSGeometry__) */
