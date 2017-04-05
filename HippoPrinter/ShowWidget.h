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


class QAction;
class QMenu;
class BedShape {
public:
	Pointf bed_minx_miny_;
	Pointf bed_minx_maxy_;
	Pointf bed_maxx_miny_;
	Pointf bed_maxx_maxy_;
	BoundingBoxf bbox_;
public:
	BedShape();
	BedShape(const BedShape& bed);
	BedShape(float minx, float maxx, float miny, float maxy);
	BedShape& operator = (const BedShape& bed);
	const BoundingBoxf& BBox()const;
	BoundingBoxf& BBox();
private:
	void ReloadBBox();
};

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
	void contextMenuEvent(QContextMenuEvent *event);

public:

	void DrawXYZ();

	void LoadModel(char* file_name);

private:
	void DrawVolumes(bool fakecolor = false) const;
	void DrawBedShape()const;

	void LoadVolumes();
	void ReloadMaxBBox();


	void SetBedShape(const BedShape& bed);
	void SetDefaultBedShape();

	void InitActions();
	void UnProject(int mouse_x, int mouse_y, Pointf3& world);

private slots:
	void ResetTrackball();
	void DeleteVolume();
	void ReloadAllVolumes();

	void RotateVolumeX();
	void RotateVolumeY();
	void RotateVolumeZ();
	
	void MirrorVolumeX();
	void MirrorVolumeY();
	void MirrorVolumeZ();

	void ScaleVolumeUniformly();
	void ScaleVolumeX();
	void ScaleVolumeY();
	void ScaleVolumeZ();


private:
	vcg::Trackball trackball_;

	TriangleMesh trimesh_;	

	Model model_;
	std::vector<SceneVolume> volumes_;
	BedShape bed_shape_;


	Pointf3 origin_;
	BoundingBoxf3 max_bbox_;
	

	int cur_mouse_x_;
	int cur_mouse_y_;
	int pre_mouse_x_;
	int pre_mouse_y_;

	bool enable_picking_;
	int hovered_volume_index_;
	int selected_volume_index_;

	bool left_pressed_;
	bool right_pressed_;



	QMenu* right_button_menu_;
	QMenu* mirror_volume_menu_;
	QMenu* scale_volume_menu_;
	QMenu* rotate_volume_menu_;
	
	QAction* reset_trackball_action_;
	QAction* reload_volumes_action_;

	QAction* delete_volume_action_;
	QAction* rotate_volume_x_action_;
	QAction* rotate_volume_y_action_;
	QAction* rotate_volume_z_action_;
	
	QAction* mirror_volume_x_action_;
	QAction* mirror_volume_y_action_;
	QAction* mirror_volume_z_action_;

	QAction* scale_volume_u_action_;
	QAction* scale_volume_x_action_;
	QAction* scale_volume_y_action_;
	QAction* scale_volume_z_action_;
};
#endif // ShowWidget_H__

