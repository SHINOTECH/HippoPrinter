#ifndef __RENDERGRAPHIC_H__
#define __RENDERGRAPHIC_H__
#pragma once

#include <src/admesh/stl.h>

class RenderGraphic
{

public:
	RenderGraphic();
	~RenderGraphic();
	static RenderGraphic* GetSingleton();
	static void DestroySingleton();

	void DrawSTLInPoints(stl_file &stl);
	void DrawSTLInTriangles(stl_file &stl);
	void DrawSTLInLines(stl_file &stl);

private:
	static RenderGraphic* render_;
};

#endif // __RenderGraphic_H__
