#include "ShowWidget.h"


#include<QLabel>
#include <QIcon>
#include <glut.h>


#include <QMouseEvent>
#include <QOpenGLFunctions>
#include <QDebug>

const float DEFAULT_COLOR[4] = { 1,1,0,1};
const float SELECTED_COLOR[4] = { 0, 1, 0, 1 };
const float HOVER_COLOR[4] = { 0,1,0,1 };

ShowWidget::ShowWidget(QWidget * parent)
	:QGLWidget(parent),
	enable_picking_(true),
	hovered_volume_index_(-1),
	selected_volume_index_(-1)
{
	setMouseTracking(true);
	InitModel();

	
}

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
	
	

	/*float ambient_and_diffuse[] = { 0.5,0.3,0.3,1 };
	float material_specular[] = { 1,1,1,1 };
	float material_emission[] = { 0.1,0,0,0.9 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, ambient_and_diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, material_specular);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 50);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, material_emission);
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);*/

	trackball_.center = vcg::Point3f(0, 0, 0);
	trackball_.radius = 1;

	glLoadIdentity();
}


void ShowWidget::paintGL() {
	
	glClearColor(1, 1, 1, 1);
	glClearDepth(1);
	glDepthFunc(GL_LESS);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
	trackball_.GetView();
	trackball_.Apply();

	if (enable_picking_) {
		glDisable(GL_LIGHTING);
		DrawVolumes(true);
		glFlush();
		glFinish();

		GLbyte color[4];
		glReadPixels(mouse_pos_x_, height() - mouse_pos_y_, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &color);
		int volume_index = color[0] + color[1] * 256 + color[2] * 256 * 256 - 1;
		qDebug() << volume_index << " , " << hovered_volume_index_;
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

	float r = width / (static_cast<float>(height));
	glOrtho(-2,2,-2,2,-2,2);

	glMatrixMode(GL_MODELVIEW);
}


void ShowWidget::InitModel() {
	char* model_name = "block.stl";
	LoadModel(model_name);
}


void ShowWidget::ShowSTL(){
}



void ShowWidget::DrawXYZ()
{
	glDisable(GL_DEPTH_TEST);
	glLineWidth(2);
	float fCursor[4];
	glGetFloatv(GL_CURRENT_COLOR, fCursor);	//获取当前颜色

	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0); //X
	glVertex3f(0, 0, 0);
	glVertex3f(0.2, 0, 0);

	glColor3f(0.0, 1.0, 0.0);//Y
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.2, 0);

	glEnable(GL_DEPTH_TEST);
	glColor3f(0.0, 0.0, 1.0);//Z
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 0.2);
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
	mouse_pos_x_ = event->x();
	mouse_pos_y_ = event->y();
	if (hovered_volume_index_ == -1) {
		trackball_.MouseMove(event->x(), event->y());
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
	trackball_.MouseDown(event->x(), height() - event->y(), QT2VCG(event->button(), event->modifiers()));
	update();
}

void ShowWidget::mouseReleaseEvent(QMouseEvent *event) {
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


void ShowWidget::LoadModel(char* file_name) {
	TriangleMesh mesh;
	mesh.ReadSTLFile(file_name);
	//mesh.repair();

	ModelObject* new_object = model_.add_object();
	new_object->name = file_name;
	new_object->input_file = file_name;

	ModelVolume *new_volume = new_object->add_volume(mesh);

	ReloadVolumes();
}

void ShowWidget::ReloadVolumes() {
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
