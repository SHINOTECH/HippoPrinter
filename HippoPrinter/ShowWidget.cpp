#include "ShowWidget.h"

#include <algorithm>

#include<QLabel>
#include <QIcon>
#include <glut.h>


#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QDebug>
#include <QContextMenuEvent>
#include <QAction>
#include <QMenu>
#include <QInputDialog>

const float DEFAULT_COLOR[4] = { 1,1,0,1};
const float SELECTED_COLOR[4] = { 0, 1, 0, 1 };
const float HOVER_COLOR[4] = { 0.4,0.9,0,1 };

ShowWidget::ShowWidget(QWidget * parent)
	:QGLWidget(parent),
	enable_picking_(true),
	hovered_volume_index_(-1),
	selected_volume_index_(-1),
	left_pressed_(false),
	right_pressed_(true),
	cur_mouse_x_(0), cur_mouse_y_(0),
	pre_mouse_x_(0), pre_mouse_y_(0)
{
	setMouseTracking(true);
	InitModel();

	max_bbox_.defined = true;
	SetDefaultBedShape();
	
	InitActions();
}


//************************************************************************
// 日期：2016/12/20 
// 返回: 
// 功能: 析构函数
//************************************************************************

ShowWidget::~ShowWidget(){
	
}

void ShowWidget::initializeGL() {
	glClearColor(1, 1, 1, 1);
	glColor3f(1, 0, 0);
	glEnable(GL_DEPTH_TEST);
	glClearDepth(1.0);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_MULTISAMPLE);

	glDisable(GL_BLEND);
	glEnable(GL_NORMALIZE);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glColor4f(1, 1, 1, 1);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	GLfloat light_model_ambient0[] = { 0.3,0.3,0.3,1 };
	GLfloat light0_diffuse0[] = { 0.5,0.5,0.5,1 };
	GLfloat light_specular0[] = { 0.2,0.2,0.2,1 };
	GLfloat light_position0[] = { -0.5,-0.5,1,0 };
	glLightfv(GL_LIGHT0, GL_POSITION, light_position0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_model_ambient0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular0);

	GLfloat light_model_ambient1[] = { 0.3,0.3,0.3,1 };
	GLfloat light0_diffuse1[] = { 0.2,0.2,0.2,1 };
	GLfloat light_specular1[] = {0.3,0.3,0.3,1};
	GLfloat light_position1[] = { 1,0,1,0 };
	glLightfv(GL_LIGHT1, GL_POSITION, light_position1);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_model_ambient1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light0_diffuse1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular1);
	
	trackball_.center = vcg::Point3f(0, 0, 0);
	trackball_.radius = 50;
	
	glLoadIdentity();
	//gluLookAt(1, 1, 1, 0, 0, 0, 0, 0, 1);
}


void ShowWidget::paintGL() {
	
	

	glClearColor(1, 1, 1, 1);
	glClearDepth(1);
	glDepthFunc(GL_LESS);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

	gluLookAt(0.06, 0, 0.1, 0, 1, 0, 0, 0, 1);
	trackball_.GetView();
	trackball_.Apply();

	glTranslatef(-max_bbox_.center().x, -max_bbox_.center().y, -max_bbox_.center().z);

	if (enable_picking_) {
		glDisable(GL_LIGHTING);
		DrawVolumes(true);
		glFlush();
		glFinish();

		GLbyte color[4];
		glReadPixels(cur_mouse_x_, height() - cur_mouse_y_, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &color);
		int volume_index = color[0] + color[1] * 256 + color[2] * 256 * 256 - 1;
		if (hovered_volume_index_ >= 0 && hovered_volume_index_ < volumes_.size()) {
			volumes_[hovered_volume_index_].SetHover(false);
		}
		if (volume_index >= 0 && volume_index < volumes_.size()) {
			hovered_volume_index_ = volume_index;
			volumes_[volume_index].SetHover(true);
		}
		else {
			hovered_volume_index_ = -1;
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glFlush();
		glFinish();
		glEnable(GL_LIGHTING);
	}

	//绘制背景

	//绘制坐标系
	glDisable(GL_LIGHTING);
	DrawXYZ();
	glEnable(GL_LIGHTING);
	DrawBedShape();
	DrawVolumes();

	
	glPopMatrix();
	
}


void ShowWidget::resizeGL(int width, int height) {
	if (height == 0) {
		height = 1;
	}
	glViewport(0, 0, static_cast<GLint>(width), static_cast<GLint>(height));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	Pointf3 max_bbox_size = max_bbox_.size();
	float max_size = std::max(std::max(max_bbox_size.x, max_bbox_size.y), max_bbox_size.z) * 2;
	int min_viewport_size = std::min(width, height);

	float zoom = min_viewport_size / max_size;

	float x = width / zoom;
	float y = height / zoom;
	float depth = std::max(std::max(max_bbox_size.x, max_bbox_size.y), max_bbox_size.z) * 2;
	//glOrtho(-x / 2, x / 2, -y / 2, y / 2, -depth, depth * 2);
	//glOrtho(-width / 2, width / 2, -height / 2, height / 2, -50, 50);
	glOrtho(-280, 280, -280, 280, -280, 280);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	//gluLookAt(1, 1, 1, 0, 0, 0, 0, 0, 1);
}


void ShowWidget::InitModel() {
	char* model_name = "3Dowllovely_face.stl";
	LoadModel(model_name);
}


void ShowWidget::DrawXYZ()
{
	glDisable(GL_DEPTH_TEST);

	Pointf3 bbox_size = max_bbox_.size();
	float axis_len = std::max(std::max(bbox_size.x, bbox_size.y), bbox_size.z) * 0.3;

	glLineWidth(2);
	float fCursor[4];
	glGetFloatv(GL_CURRENT_COLOR, fCursor);	//获取当前颜色

	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0); //X
	glVertex3f(0, 0, 0);
	glVertex3f(axis_len, 0, 0);

	glColor3f(0.0, 1.0, 0.0);//Y
	glVertex3f(0, 0, 0);
	glVertex3f(0, axis_len, 0);

	glEnable(GL_DEPTH_TEST);
	glColor3f(0.0, 0.0, 1.0);//Z
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, axis_len);
	glEnd();

	glColor4fv(fCursor);
	glLineWidth(1.0);
}



void ShowWidget::DrawVolumes(bool fakecolor)const {

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	for (int volume_index = 0; volume_index < volumes_.size(); volume_index++) {
		SceneVolume volume = volumes_[volume_index];
		
		
		glPushMatrix();
		glTranslatef(volume.Origin().x, volume.Origin().y, volume.Origin().z);

		if (fakecolor) {
			int r = ((volume_index+1) & 0x000000FF) >> 0;
			int g = ((volume_index + 1) & 0x0000FF00) >> 8;
			int b = ((volume_index + 1) & 0x00FF0000) >> 16;
			glColor4f(r / 255.0, g / 255.0, b / 255.0, 1);
		}
		else if (volume.Selected()) {
			glColor4fv(SELECTED_COLOR);
		}
		else if (volume.Hover()) {
			glColor4fv(HOVER_COLOR);
		}
		else {
			glColor4fv(DEFAULT_COLOR);
		}

		size_t max_offset = volume.Verts().verts.size();
		glCullFace(GL_BACK);
		glVertexPointer(3, GL_FLOAT, 0, volume.Verts().verts.data());
		glNormalPointer(GL_FLOAT, 0, volume.Verts().norms.data());
		glDrawArrays(GL_TRIANGLES, 0, max_offset / 3);
		
		glPopMatrix();
	}

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

void ShowWidget::DrawBedShape()const {
	float fCursor[4];
	glGetFloatv(GL_CURRENT_COLOR, fCursor);	//获取当前颜色
	glPushMatrix();
	
	glColor4f(0.8, 0.6, 0.5,0.4);
	glNormal3d(1, 1, 1);
	glDisable(GL_LIGHTING);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
	glVertex2f(-1.0, -1.0);
	glVertex2f(1, -1.0);
	glColor3f(10 / 255.0, 98 / 255.0, 144 / 255.0);
	glVertex2f(1, 1);
	glVertex2f(-1.0, 1);
	glEnd();

	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	//glPopMatrix();

	glBegin(GL_TRIANGLES);

 	glVertex3f(bed_shape_.bed_minx_miny_.x, bed_shape_.bed_minx_miny_.y, 0);
	glVertex3f(bed_shape_.bed_maxx_maxy_.x, bed_shape_.bed_maxx_maxy_.y, 0);
	glVertex3f(bed_shape_.bed_minx_maxy_.x, bed_shape_.bed_minx_maxy_.y, 0);
	
	glVertex3f(bed_shape_.bed_minx_miny_.x,bed_shape_.bed_minx_miny_.y,0);
	glVertex3f(bed_shape_.bed_maxx_miny_.x, bed_shape_.bed_maxx_miny_.y, 0);
	glVertex3f(bed_shape_.bed_maxx_maxy_.x, bed_shape_.bed_maxx_maxy_.y, 0);
	glEnd();

	glLineWidth(3);
	glColor4f(0.2, 0.2, 0.2, 0.4);
	glBegin(GL_LINES);
	for (int i = 0; i <= 180; i += 10) {
		glVertex3f(0, i, 0);
		glVertex3f(280, i, 0);
	}
	for(int i =  0; i < 280;i+=10){
		glVertex3f(i, 0, 0);
		glVertex3f(i, 180, 0);
	}
	glEnd();

	//glFlush();
	glColor4fv(fCursor);
	glEnable(GL_LIGHTING);
	
	glPopMatrix();
}


///将Qt鼠标键盘事件转换为VCG库内的鼠标键盘事件
vcg::Trackball::Button QT2VCG(Qt::MouseButton qtbt, Qt::KeyboardModifiers modifiers)
{
	int vcgbt = vcg::Trackball::BUTTON_NONE;
	if (qtbt & Qt::LeftButton) vcgbt |= vcg::Trackball::BUTTON_LEFT;
	if (qtbt & Qt::RightButton) vcgbt |= vcg::Trackball::BUTTON_RIGHT;
	if (qtbt & Qt::MidButton) vcgbt |= vcg::Trackball::BUTTON_MIDDLE;
	if (modifiers & Qt::ShiftModifier)	vcgbt |= vcg::Trackball::KEY_SHIFT;
	if (modifiers & Qt::ControlModifier) vcgbt |= vcg::Trackball::KEY_CTRL;
	if (modifiers & Qt::AltModifier) vcgbt |= vcg::Trackball::KEY_ALT;
	return vcg::Trackball::Button(vcgbt);
}

void ShowWidget::mouseMoveEvent(QMouseEvent *event) {
	pre_mouse_x_ = cur_mouse_x_;
	pre_mouse_y_ = cur_mouse_y_;

	cur_mouse_x_ = event->x();
	cur_mouse_y_ = event->y();

	if (hovered_volume_index_ == -1) {
		if (selected_volume_index_ >= 0 && selected_volume_index_ < volumes_.size()) {
			volumes_[selected_volume_index_].SetSelected(false);
		}
		selected_volume_index_ = -1;
		trackball_.MouseMove(event->x(), height()- event->y());
		update();
		return;
	}
	if (left_pressed_ && selected_volume_index_ >= 0 && selected_volume_index_ < volumes_.size()) {
		Pointf3 curPos;
		UnProject(cur_mouse_x_, height() - cur_mouse_y_, curPos);
		Pointf3 prePos;
		UnProject(pre_mouse_x_, height() - pre_mouse_y_, prePos);

		Pointf3 trans_vector(curPos.x - prePos.x, curPos.y - prePos.y, curPos.z - prePos.z);
		volumes_[selected_volume_index_].Origin().translate(trans_vector.x, trans_vector.y,0);
	}
	update();
}

void ShowWidget::wheelEvent(QWheelEvent* event) {
	if (event->delta() > 0) {
		trackball_.MouseWheel(1);
	}
	else {
		trackball_.MouseWheel(-1);
	}
	update();
}

void ShowWidget::mousePressEvent(QMouseEvent* event) {
	if (event->button() == Qt::LeftButton) {
		left_pressed_ = true;
	}
	else if (event->button() == Qt::RightButton) {
		right_pressed_ = true;
	}
	if (selected_volume_index_ >= 0 && selected_volume_index_ < volumes_.size()) {
		volumes_[selected_volume_index_].SetSelected(false);
		selected_volume_index_ = -1;
	}
	if (hovered_volume_index_ >= 0 && hovered_volume_index_ < volumes_.size()) {
		selected_volume_index_ = hovered_volume_index_;
		volumes_[selected_volume_index_].SetSelected(true);
	}
	trackball_.MouseDown(event->x(), height() - event->y(), QT2VCG(event->button(), event->modifiers()));
	update();
}

void ShowWidget::mouseReleaseEvent(QMouseEvent *event) {
	if (event->button() == Qt::LeftButton) {
		left_pressed_ = false;
	}
	else if (event->button() == Qt::RightButton) {
		right_pressed_ = false;
	}
	trackball_.MouseUp(event->x(), height() - event->y(), QT2VCG(event->button(), event->modifiers()));
}


void ShowWidget::keyReleaseEvent(QKeyEvent *event) {
	if (event->key() == Qt::Key_Control) {
		trackball_.ButtonUp(QT2VCG(Qt::NoButton, Qt::ControlModifier));
	}
	if (event->key() == Qt::Key_Shift) {
		trackball_.ButtonUp(QT2VCG(Qt::NoButton, Qt::ShiftModifier));
	}
	if (event->key() == Qt::Key_Alt) {
		trackball_.ButtonUp(QT2VCG(Qt::NoButton, Qt::AltModifier));
	}
}

void ShowWidget::contextMenuEvent(QContextMenuEvent *event) {
	right_button_menu_->clear();
	right_button_menu_->addAction(reset_trackball_action_);
	right_button_menu_->addAction(reload_volumes_action_);

	if (selected_volume_index_ != -1) {
		right_button_menu_->addSeparator();
		right_button_menu_->addAction(delete_volume_action_);

		rotate_volume_menu_ = right_button_menu_->addMenu(QString::fromLocal8Bit("旋转"));
		rotate_volume_menu_->addAction(rotate_volume_x_action_);
		rotate_volume_menu_->addAction(rotate_volume_y_action_);
		rotate_volume_menu_->addAction(rotate_volume_z_action_);

		mirror_volume_menu_ = right_button_menu_->addMenu(QString::fromLocal8Bit("镜像"));
		mirror_volume_menu_->addAction(mirror_volume_x_action_);
		mirror_volume_menu_->addAction(mirror_volume_y_action_);
		mirror_volume_menu_->addAction(mirror_volume_z_action_);

		scale_volume_menu_ = right_button_menu_->addMenu(QString::fromLocal8Bit("缩放"));
		scale_volume_menu_->addAction(scale_volume_u_action_);
		scale_volume_menu_->addAction(scale_volume_x_action_);
		scale_volume_menu_->addAction(scale_volume_y_action_);
		scale_volume_menu_->addAction(scale_volume_z_action_);
	}
	

	right_button_menu_->exec(QCursor::pos());
}


void ShowWidget::LoadModel(char* file_name) {
	TriangleMesh mesh;
	mesh.ReadSTLFile(file_name);
	//mesh.repair();

	ModelObject* new_object = model_.add_object();
	new_object->name = file_name;
	new_object->input_file = file_name;

	ModelVolume *new_volume = new_object->add_volume(mesh);

	LoadVolumes();
}

void ShowWidget::LoadVolumes() {
	volumes_.clear();
	for (ModelObject* object : model_.objects) {
		for (ModelVolume* model_volume : object->volumes) {
			SceneVolume scene_volume;
			scene_volume.SetBBox(model_volume->mesh.bounding_box());
			scene_volume.LoadMesh(model_volume->mesh);
			volumes_.push_back(scene_volume);
		}
	}
}

void ShowWidget::ReloadMaxBBox() {
	BoundingBoxf& bed_bbox = bed_shape_.BBox();
	max_bbox_.min = Pointf3(bed_bbox.min.x, bed_bbox.min.y, 0);
	max_bbox_.max = Pointf3(bed_bbox.max.x, bed_bbox.max.y, 0);

	for (SceneVolume volume : volumes_) {
		max_bbox_.merge(volume.BBox());
	}
}

void ShowWidget::SetBedShape(const BedShape& bed) {
	bed_shape_ = bed;
	ReloadMaxBBox();
}

void ShowWidget::SetDefaultBedShape() {
	bed_shape_ = BedShape(0, 280, 0, 180);
	ReloadMaxBBox();
}

void ShowWidget::InitActions() {
	right_button_menu_ = new QMenu();

	reset_trackball_action_ = new QAction(QString::fromLocal8Bit("重置"), this);
	delete_volume_action_ = new QAction(QString::fromLocal8Bit("删除"), this);
	reload_volumes_action_ = new QAction(QString::fromLocal8Bit("重载模型"), this);

	rotate_volume_x_action_ = new QAction(QString::fromLocal8Bit("绕X轴"), this);
	rotate_volume_y_action_ = new QAction(QString::fromLocal8Bit("绕Y轴"), this);
	rotate_volume_z_action_ = new QAction(QString::fromLocal8Bit("绕Z轴"), this);
	
	mirror_volume_x_action_ = new QAction(QString::fromLocal8Bit("X方向"));
	mirror_volume_y_action_ = new QAction(QString::fromLocal8Bit("Y方向"));
	mirror_volume_z_action_ = new QAction(QString::fromLocal8Bit("Z方向"));

	scale_volume_u_action_ = new QAction(QString::fromLocal8Bit("等比缩放"),this);
	scale_volume_x_action_ = new QAction(QString::fromLocal8Bit("沿X轴"), this);
	scale_volume_y_action_ = new QAction(QString::fromLocal8Bit("沿Y轴"), this);
	scale_volume_z_action_ = new QAction(QString::fromLocal8Bit("沿Z轴"), this);

	connect(reset_trackball_action_, &QAction::triggered, this, &ShowWidget::ResetTrackball);
	connect(delete_volume_action_, &QAction::triggered, this, &ShowWidget::DeleteVolume);
	connect(reload_volumes_action_ , &QAction::triggered, this, &ShowWidget::ReloadAllVolumes);

	connect(rotate_volume_x_action_, &QAction::triggered, this, &ShowWidget::RotateVolumeX);
	connect(rotate_volume_y_action_, &QAction::triggered, this, &ShowWidget::RotateVolumeY);
	connect(rotate_volume_z_action_, &QAction::triggered, this, &ShowWidget::RotateVolumeZ);

	connect(mirror_volume_x_action_, &QAction::triggered, this, &ShowWidget::MirrorVolumeX);
	connect(mirror_volume_y_action_, &QAction::triggered, this, &ShowWidget::MirrorVolumeY);
	connect(mirror_volume_z_action_, &QAction::triggered, this, &ShowWidget::MirrorVolumeZ);

	connect(scale_volume_u_action_, &QAction::triggered, this, &ShowWidget::ScaleVolumeUniformly);
	connect(scale_volume_x_action_, &QAction::triggered, this, &ShowWidget::ScaleVolumeX);
	connect(scale_volume_y_action_, &QAction::triggered, this, &ShowWidget::ScaleVolumeY);
	connect(scale_volume_z_action_, &QAction::triggered, this, &ShowWidget::ScaleVolumeZ);
}

void ShowWidget::ResetTrackball() {
	trackball_.SetIdentity();
	update();
}

void ShowWidget::UnProject(int mouse_x, int mouse_y, Pointf3& world) {
	glPushMatrix();

	GLdouble model_view[16];
	GLdouble projection[16];
	GLint view_port[4];

	glGetDoublev(GL_MODELVIEW_MATRIX, model_view);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, view_port);

	float win_z;
	glReadPixels(mouse_x, mouse_y, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &win_z);

	gluUnProject((GLdouble)mouse_x, (GLdouble)mouse_y, win_z,
		model_view, projection, view_port,
		&world.x, &world.y, &world.z);
	glPopMatrix();
}

void ShowWidget::DeleteVolume() {
	if (selected_volume_index_ == -1) {
		return;
	}
	model_.delete_object(selected_volume_index_);
	selected_volume_index_ = -1;
	LoadVolumes();
	update();
}

void ShowWidget::RotateVolumeX() {
	bool ok;
	double input_num = QInputDialog::getDouble(this,
		QString::fromLocal8Bit("绕X轴旋转"),
		QString::fromLocal8Bit("旋转的角度："),
		0,
		-180, 180,
		2,
		&ok);
	if (ok) {
		if (input_num == 0.00) {
			return;
		}
		model_.objects[selected_volume_index_]->rotate(input_num, Axis::X);
		LoadVolumes();
		update();
	}
	return;
}

void ShowWidget::RotateVolumeY() {
	bool ok;
	double input_num = QInputDialog::getDouble(this,
		QString::fromLocal8Bit("绕Y轴旋转"),
		QString::fromLocal8Bit("旋转的角度："),
		0,
		-180, 180,
		2,
		&ok);
	if (ok) {
		if (input_num == 0.00) {
			return;
		}
		model_.objects[selected_volume_index_]->rotate(input_num, Axis::Y);
		LoadVolumes();
		update();
	}
	return;
}

void ShowWidget::RotateVolumeZ() {
	bool ok;
	double input_num = QInputDialog::getDouble(this,
		QString::fromLocal8Bit("绕Z轴旋转"),
		QString::fromLocal8Bit("旋转的角度："),
		0,
		-180, 180,
		2,
		&ok);
	if (ok) {
		if (input_num == 0.00) {
			return;
		}
		model_.objects[selected_volume_index_]->rotate(input_num, Axis::Z);
		LoadVolumes();
		update();
	}
	return;
}

void ShowWidget::MirrorVolumeX() {
	model_.objects[selected_volume_index_]->mirror(Axis::X);
	LoadVolumes();
	update();
}

void ShowWidget::MirrorVolumeY() {
	model_.objects[selected_volume_index_]->mirror(Axis::Y);
	LoadVolumes();
	update();
}

void ShowWidget::MirrorVolumeZ() {
	model_.objects[selected_volume_index_]->mirror(Axis::Z);
	LoadVolumes();
	update();
}

void ShowWidget::ScaleVolumeUniformly() {
	bool ok;
	double input_num = QInputDialog::getDouble(this,
		QString::fromLocal8Bit("等比缩放"),
		QString::fromLocal8Bit("比例（0-100）："),
		100,
		0, 1000,
		2,
		&ok);
	if (ok) {
		if (input_num == 0.00 || input_num == 100.00) {
			return;
		}
		model_.objects[selected_volume_index_]->scale(Pointf3(input_num/100.0, input_num/100.0, input_num/100.0));
		LoadVolumes();
		update();
	}
	return;
}

void ShowWidget::ScaleVolumeX() {
	bool ok;
	double input_num = QInputDialog::getDouble(this,
		QString::fromLocal8Bit("X轴方向缩放"),
		QString::fromLocal8Bit("比例（0-100）："),
		100,
		0, 1000,
		2,
		&ok);
	if (ok) {
		if (input_num == 0.00 || input_num == 100.00) {
			return;
		}
		model_.objects[selected_volume_index_]->scale(Pointf3(input_num / 100.0, 1, 1));
		LoadVolumes();
		update();
	}
	return;
}

void ShowWidget::ScaleVolumeY() {
	bool ok;
	double input_num = QInputDialog::getDouble(this,
		QString::fromLocal8Bit("Y轴方向缩放"),
		QString::fromLocal8Bit("比例（0-100）："),
		100,
		0, 1000,
		2,
		&ok);
	if (ok) {
		if (input_num == 0.00 || input_num == 100.00) {
			return;
		}
		model_.objects[selected_volume_index_]->scale(Pointf3(1, input_num/100.0, 1));
		LoadVolumes();
		update();
	}
	return;
}

void ShowWidget::ScaleVolumeZ() {
	bool ok;
	double input_num = QInputDialog::getDouble(this,
		QString::fromLocal8Bit("Z轴方向缩放"),
		QString::fromLocal8Bit("比例（0-100）："),
		100,
		0, 1000,
		2,
		&ok);
	if (ok) {
		if (input_num == 0.00 || input_num == 100.00) {
			return;
		}
		model_.objects[selected_volume_index_]->scale(Pointf3(1, 1, input_num / 100.0));
		LoadVolumes();
		update();
	}
	return;
}

void ShowWidget::ReloadAllVolumes() {
	LoadVolumes();
	update();
}
BedShape::BedShape() :
	bed_minx_miny_(0, 0), bed_minx_maxy_(0, 0), bed_maxx_miny_(0, 0), bed_maxx_maxy_(0, 0) {
	ReloadBBox();
}

BedShape::BedShape(const BedShape& bed)
	:bed_minx_miny_(bed.bed_minx_miny_),
	bed_minx_maxy_(bed.bed_minx_maxy_),
	bed_maxx_miny_(bed.bed_maxx_miny_),
	bed_maxx_maxy_(bed.bed_maxx_maxy_){
	ReloadBBox();
}

BedShape::BedShape(float minx, float maxx, float miny, float maxy) 
	:bed_minx_miny_(minx,miny),
	bed_minx_maxy_(minx,maxy),
	bed_maxx_miny_(maxx,miny),
	bed_maxx_maxy_(maxx,maxy){
	ReloadBBox();
}

BedShape& BedShape::operator =(const BedShape& bed) {
	bed_minx_miny_ = bed.bed_minx_miny_;
	bed_minx_maxy_ = bed.bed_minx_maxy_;
	bed_maxx_miny_ = bed.bed_maxx_miny_;
	bed_maxx_maxy_ = bed.bed_maxx_maxy_;
	ReloadBBox();
	return *this;
}

const BoundingBoxf& BedShape::BBox()const {
	return bbox_;
}

BoundingBoxf& BedShape::BBox() {
	return bbox_;
}

void BedShape::ReloadBBox() {
	bbox_.min = bed_minx_miny_;
	bbox_.max = bed_maxx_maxy_;
}