#ifndef ShowWidget_H__
#define ShowWidget_H__

#pragma once
#include <iostream>
#include <vector>

#include <QGLWidget>

#include <src/libslic3r/Model.hpp>
#include <src/libslic3r/TriangleMesh.hpp>

#include <wrap/gui/trackball.h>
#include <vcg/space/deprecated_point2.h>

#include "scenevolume.h"

class ShowWidget :
	public QGLWidget
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
	void mouseMoveEvent(QMouseEvent *event);
	void wheelEvent(QWheelEvent* event);
	void mousePressEvent(QMouseEvent* event);
	void mouseReleaseEvent(QMouseEvent *event);
	void keyReleaseEvent(QKeyEvent *event);

public:
	void ShowSTL();

	void DrawXYZ();

	void LoadModel(char* file_name);

private:
	void DrawVolumes(bool fakecolor = false) const;
	void ReloadVolumes();

private:
	vcg::Trackball trackball_;

	TriangleMesh trimesh_;	//当前的三维模型	

	Model model_;
	std::vector<SceneVolume> volumes_;


	BoundingBoxf3 bbox_;
	

	int mouse_pos_x_;
	int mouse_pos_y_;

	bool enable_picking_;
	int hovered_volume_index_;
	int selected_volume_index_;
};
#endif // ShowWidget_H__

