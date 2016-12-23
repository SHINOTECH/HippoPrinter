#ifndef ShowWidget_H__
#define ShowWidget_H__

#pragma once
#include <QOpenGLWidget>
#include "src/libslic3r/TriangleMesh.hpp"
#include <iostream>

class ShowWidget :
	public QOpenGLWidget
{
	Q_OBJECT


public:
	ShowWidget(QWidget* parent = 0);
	~ShowWidget();
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);
	void InitModel();

public:
	void ShowSTL();

	void DrawXYZ();

private:
	TriangleMesh trimesh_;	//当前的三维模型	
};
#endif // ShowWidget_H__

