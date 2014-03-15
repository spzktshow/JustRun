//
//  MSGeometry.cpp
//  HelloCpp
//
//  Created by RockLee on 13-9-29.
//
//

#include "MSGeometry.h"

USING_NS_CC;
NS_MS_BEGIN
/***Matrix**/
MSMatrix::MSMatrix(int col, int row)
{
    this->col = col;
    this->row = row;
}
/********MatrixIndex*****/
MSMatrixIndex::MSMatrixIndex(int colIndex, int rowIndex)
{
    this->colIndex = colIndex;
    this->rowIndex = rowIndex;
}
/********MSNode***********/
MSNode::MSNode(int col, int row, int colIndex, int rowIndex)
{
    matrixIndex = new MSMatrixIndex(colIndex, rowIndex);
    matrix = new MSMatrix(col, row);
}

MSNode::~MSNode()
{
    delete matrixIndex;
    delete matrix;
}
/******Matrix3d**********/
MSMatrix3D::MSMatrix3D(int col, int row):MSMatrix(col, row)
{
	x = col;
	z = row;
	y = 0;
}

MSMatrix3D::MSMatrix3D(int xValue, int yValue, int zValue):MSMatrix(xValue, zValue)
{
	x = xValue;
	y = yValue;
	z = zValue;
}
/*************MatrixIndex3d***************/
MSMatrixIndex3D::MSMatrixIndex3D(int colIndex, int rowIndex):MSMatrixIndex(colIndex, rowIndex)
{
	xIndex = colIndex;
	yIndex = 0;
	zIndex = rowIndex;
}

MSMatrixIndex3D::MSMatrixIndex3D(int xIndexValue, int yIndexValue, int zIndexValue):MSMatrixIndex(xIndexValue, zIndexValue)
{
	xIndex = xIndexValue;
	yIndex = yIndexValue;
	zIndex = zIndexValue;
}
/*****************MSPoint3D********/
MSPoint3D::MSPoint3D(float xValue, float yValue, float zValue):CCPoint(xValue, yValue)
{
	z = zValue;
}
/*******************MSNode3D********/
MSNode3D::MSNode3D(int x, int y, int z, int xIndex, int yIndex, int zIndex):MSNode(x, z, xIndex, zIndex)
{
	matrixIndex3d = new MSMatrixIndex3D(xIndex, yIndex, zIndex);
	matrix3d = new MSMatrix3D(x, y, z);
}
MSNode3D::MSNode3D(int col, int row, int colIndex, int rowIndex):MSNode(col, row, colIndex, rowIndex)
{
	matrixIndex3d = new MSMatrixIndex3D(colIndex, 0, rowIndex);
	matrix3d = new MSMatrix3D(col, 0, row);
}
MSNode3D::~MSNode3D()
{
	delete matrix3d;
	delete matrixIndex3d;
}

/*****************CoordinateUtils*****************************/
float CoordinateUtils::calculateCoordinateSystem(float y, const Size & size)
{
	return (size.height - y);
}

NS_MS_END;