#include "ShowWidget.h"


#include<QLabel>
#include <QIcon>
#include <glut.h>
#include "RenderGraphic.h"

//************************************************************************
// 日期：2016/12/20 
// 参数: QWidget * parent
// 返回: 
// 功能: 构造函数
//************************************************************************
ShowWidget::ShowWidget(QWidget * parent)
	:QOpenGLWidget(parent){

	InitModel();

	
}

//************************************************************************
// 日期：2016/12/20 
// 返回: 
// 功能: 析构函数
//************************************************************************
ShowWidget::~ShowWidget(){
	
}

//************************************************************************
// 日期：2016/12/20 
// 返回: void
// 功能: 初始化控件
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
// 日期：2016/12/20 
// 返回: void
// 功能: 绘制控件
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
// 日期：2016/12/20 
// 参数: int width
// 参数: int height
// 返回: void
// 功能: 改变控件尺寸
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
// 日期：2016/12/20 
// 返回: void
// 功能: 初始化模型
//************************************************************************
void ShowWidget::InitModel() {
	char* stl_file_name = "3Dowllovely_face.stl";
	trimesh_.ReadSTLFile(stl_file_name);
	trimesh_.repair();
}


//************************************************************************
// 日期：2016/12/20 
// 返回: void
// 功能: 设置窗口风格
//************************************************************************

//************************************************************************
// 日期：2016/12/20 
// 返回: void
// 功能: 显示STL模型
//************************************************************************
void ShowWidget::ShowSTL(){
	RenderGraphic* render = RenderGraphic::GetSingleton();
	render->DrawSTLInTriangles(trimesh_.stl);
}



//************************************************************************
// 日期：2016/12/20 
// 返回: void
// 功能: 绘制坐标轴
//************************************************************************
void ShowWidget::DrawXYZ()
{
	glPushMatrix();
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

	glColor3f(0.0, 0.0, 1.0);//Z
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 0.2);
	glEnd();

	glColor4fv(fCursor);
	glLineWidth(1.0);
	glPopMatrix();
}

