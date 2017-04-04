/************************************************************************/
/*                    console output the debug info.                    */
/************************************************************************/

#ifndef _CONSOLE_H
#define _CONSOLE_H
#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

//CConsoleOutput����ҪΪ����QT����ӿ���̨����
class CConsoleOutput
{
public:
	//output information in console 
	static void Destory();
	static CConsoleOutput * Instance();
public:
	virtual ~CConsoleOutput();

protected:
	CConsoleOutput();

private:
	static CConsoleOutput* m_instance;
	FILE *file;
};

#endif

