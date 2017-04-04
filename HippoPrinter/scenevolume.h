#pragma once

#include <src/slic3r/GUI/3DScene.hpp>
class SceneVolume
{
public:
	SceneVolume();
	~SceneVolume();

	const BoundingBoxf3& BBox()const;
	BoundingBoxf3& BBox();
	void SetBBox(const BoundingBoxf3& bbox);


	const Pointf3& Origin()const;
	Pointf3& Origin();
	void SetOrigin(const Pointf3& origin);

	void SetSelected(bool flag);
	bool Selected() const;

	void SetHover(bool flag);
	bool Hover() const;

	void LoadMesh(const TriangleMesh& mesh);
	
	const GLVertexArray& Verts()const;
	GLVertexArray& Verts();
	void SetVerts(const GLVertexArray& verts);

private:
	BoundingBoxf3 bbox_;
	Pointf3 origin_;
	bool selected_;
	bool hover_;
	GLVertexArray verts_;
};

