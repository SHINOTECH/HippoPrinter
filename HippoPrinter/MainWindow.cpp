#include "mainwindow.h"
#include <iostream>

#include<QSize>
#include <QString>
#include <QDebug>

#include <QSplitter>
#include <QTabWidget>
#include <QVBoxLayout>

#include <QListWidget>
#include <QStackedWidget>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	//ui.setupUi(this);
	setWindowTitle(QString::fromLocal8Bit("Hippo"));
	//setMinimumSize(QSize(1000, 800));
	
	//��ʼ���˵��Ͳ˵���
	initActions();	
	initMenus();
	initWidgets();

	setCentralWidget(mainSplitter);
	setContentsMargins(5, 5, 10, 5);
	statusBar()->showMessage(tr("Ready"));

	if (!isMaximized()) {
		showMaximized();
	}
}


void MainWindow::initActions() {

	/*�ļ��˵��µĲ���*/
	//��ģ��
	load_model_action_ = new QAction(QString::fromLocal8Bit("��ģ��"));
	load_model_action_->setShortcut(tr("Ctrl+O"));
	load_model_action_->setStatusTip(QString::fromLocal8Bit("��ģ���ļ�"));
	
	//����ģ��
	save_model_action_ = new QAction(QString::fromLocal8Bit("����ģ��"));
	save_model_action_->setShortcut(tr("Ctrl+S"));
	save_model_action_->setStatusTip(QString::fromLocal8Bit("����ģ���ļ�"));

	//����GCode�ļ�
	save_GCode_action_ = new QAction(QString::fromLocal8Bit("����G����"));
	save_GCode_action_->setShortcut(tr("Ctrl+G"));
	save_GCode_action_->setStatusTip(QString::fromLocal8Bit("����GCode�ļ�"));

	//��ӡģ��
	print_action_ = new QAction(QString::fromLocal8Bit("��ӡģ��"));
	print_action_->setShortcut(tr("Ctrl+P"));
	print_action_->setStatusTip(QString::fromLocal8Bit("��ӡ��άģ��"));

	//���ƽ̨
	clear_platform_action_ = new QAction(QString::fromLocal8Bit("���ƽ̨"));
	clear_platform_action_->setStatusTip(QString::fromLocal8Bit("���������άģ��"));

	//�˳�����
	quit_action_ = new QAction(QString::fromLocal8Bit("�˳�"));
	quit_action_->setShortcut(tr("Ctrl+Q"));
	quit_action_->setStatusTip(QString::fromLocal8Bit("�˳�����"));


	/*���ò˵��µĲ���*/
	//���ô�ӡ����
	global_setting_action_ = new QAction(QString::fromLocal8Bit("��ӡ������"));
	global_setting_action_->setStatusTip(QString::fromLocal8Bit("���ô�ӡ����ز���"));


	/*�����˵��µĲ���*/
	//��ȡHippo����
	about_hippo_action_ = new QAction(QString::fromLocal8Bit("����Hippo"));
	about_hippo_action_->setStatusTip(QString::fromLocal8Bit("����Hippo������"));

	//��ȡ����ֲ�
	about_manual_action_ = new QAction(QString::fromLocal8Bit("ʹ���ֲ�"));
	about_manual_action_->setStatusTip(QString::fromLocal8Bit("���ʹ���ֲ�"));

	//��ȡQt����
	about_qt_action_ = new QAction(QString::fromLocal8Bit("����Qt"));
	about_qt_action_->setStatusTip(QString::fromLocal8Bit("��ȡ����Qt������"));
}

void MainWindow::SetupWindowStyle() {
	setWindowFlags(windowFlags() | Qt::FramelessWindowHint | Qt::X11BypassWindowManagerHint | Qt::Tool);
	setAttribute(Qt::WA_TranslucentBackground);
	setWindowState(Qt::WindowNoState | Qt::WindowFullScreen);
	setFocusPolicy(Qt::NoFocus);
	setWindowOpacity(1.0);

	setWindowIcon(QIcon(":/resources/icon.png"));
}

//************************************
// ����: big-hippo
// ���ڣ�2016/12/19 
// ����: void
// ����: ��ʼ���˵���
//************************************
void MainWindow::initMenus() {
	//�ļ��˵�
	file_menu_ = menuBar()->addMenu(QString::fromLocal8Bit("�ļ�"));
	file_menu_->addAction(load_model_action_);
	file_menu_->addAction(save_model_action_);
	file_menu_->addAction(save_GCode_action_);
	file_menu_->addSeparator();
	file_menu_->addAction(print_action_);
	file_menu_->addAction(clear_platform_action_);
	file_menu_->addSeparator();
	file_menu_->addAction(quit_action_);

	//���ò˵�
	setting_menu_ = menuBar()->addMenu(QString::fromLocal8Bit("����"));
	setting_menu_->addAction(global_setting_action_);
	

	//�����˵�
	help_menu_ = menuBar()->addMenu(QString::fromLocal8Bit("����"));
	help_menu_->addAction(about_hippo_action_);
	help_menu_->addAction(about_hippo_action_);
	help_menu_->addAction(about_hippo_action_);
}



//************************************
// ����: big-hippo
// ���ڣ�2016/12/19 
// ����: void
// ����:
//************************************
void MainWindow::initWidgets() {
	printConfigWidget = new PrintConfigWidget();
	filConfigWidget = new FilamentConfigWidget();
	printerConfigWidget = new PrinterConfigWidget();

	leftTabWidget = new QTabWidget();
	leftTabWidget->addTab(printConfigWidget, QString::fromLocal8Bit("��ӡ����"));
	leftTabWidget->addTab(filConfigWidget, QString::fromLocal8Bit("�Ĳ�����"));
	leftTabWidget->addTab(printerConfigWidget, QString::fromLocal8Bit("��ӡ������"));
	
	showWidget = new ShowWidget();

	mainSplitter = new QSplitter(Qt::Horizontal,0);
	mainSplitter->setOpaqueResize(true);
	mainSplitter->addWidget(leftTabWidget);
	mainSplitter->addWidget(showWidget);
	mainSplitter->setStretchFactor(0, 1);
	mainSplitter->setStretchFactor(1, 3);
}

