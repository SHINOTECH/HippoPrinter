#include "ShowWidget.h"


#include<QLabel>
#include <QIcon>
#include <glut.h>
#include "RenderGraphic.h"

//************************************************************************
// ���ڣ�2016/12/20 
// ����: QWidget * parent
// ����: 
// ����: ���캯��
//************************************************************************
ShowWidget::ShowWidget(QWidget * parent)
	:QOpenGLWidget(parent){

	InitModel();

	
}

//************************************************************************
// ���ڣ�2016/12/20 
// ����: 
// ����: ��������
//************************************************************************
ShowWidget::~ShowWidget(){
	
}

//************************************************************************
// ���ڣ�2016/12/20 
// ����: void
// ����: ��ʼ���ؼ�
//************************************************************************
void ShowWidget::initializeGL() {
	glShadeModel(GL_SMOOTH);
	glClearColor(1.0, 1.0, 1.0, 0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}


//************************************************************************
// ���ڣ�2016/12/20 
// ����: void
// ����: ���ƿؼ�
//************************************************************************
void ShowWidget::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(0.0, 0.0, -20.0);
	ShowSTL();
	DrawXYZ();
	update();
}


//************************************************************************
// ���ڣ�2016/12/20 
// ����: int width
// ����: int height
// ����: void
// ����: �ı�ؼ��ߴ�
//************************************************************************

void ShowWidget::resizeGL(int width, int height) {
	if (height == 0) {
		height = 1;
	}
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, static_cast<GLfloat>(width) / static_cast<GLfloat>(height), 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

//************************************************************************
// ���ڣ�2016/12/20 
// ����: void
// ����: ��ʼ��ģ��
//************************************************************************
void ShowWidget::InitModel() {
	char* stl_file_name = "3Dowllovely_face.stl";
	trimesh_.ReadSTLFile(stl_file_name);
	trimesh_.repair();
}


//************************************************************************
// ���ڣ�2016/12/20 
// ����: void
// ����: ���ô��ڷ��
//************************************************************************

//************************************************************************
// ���ڣ�2016/12/20 
// ����: void
// ����: ��ʾSTLģ��
//************************************************************************
void ShowWidget::ShowSTL(){
	RenderGraphic* render = RenderGraphic::GetSingleton();
	render->DrawSTLInTriangles(trimesh_.stl);
}



//************************************************************************
// ���ڣ�2016/12/20 
// ����: void
// ����: ����������
//************************************************************************
void ShowWidget::DrawXYZ()
{
	glPushMatrix();
	glLineWidth(2);
	float fCursor[4];
	glGetFloatv(GL_CURRENT_COLOR, fCursor);	//��ȡ��ǰ��ɫ

	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0); //X
	glVertex3f(0, 0, 0);
	glVertex3f(0.2, 0, 0);

	glColor3f(0.0, 1.0, 0.0);//Y
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0.2, 0);

	glColor3f(0.0, 0.0, 1.0);//Z
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 0.2);
	glEnd();

	glColor4fv(fCursor);
	glLineWidth(1.0);
	glPopMatrix();
}

