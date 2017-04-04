#include "scenevolume.h"



SceneVolume::SceneVolume()
	:origin_(0, 0, 0), selected_(false), hover_(false){
}


SceneVolume::~SceneVolume(){

}

const BoundingBoxf3& SceneVolume::BBox()const {
	return bbox_;
}

BoundingBoxf3& SceneVolume::BBox() {
	return bbox_;
}

void SceneVolume::SetBBox(const BoundingBoxf3& bbox){
	bbox_ = bbox;
}


const Pointf3& SceneVolume::Origin()const {
	return origin_;
}

Pointf3& SceneVolume::Origin() {
	return origin_;
}

void SceneVolume::SetOrigin(const Pointf3& origin) {
	origin_ = origin_;
}

bool SceneVolume::Selected()const {
	return selected_;
}

void SceneVolume::SetSelected(bool flag) {
	selected_ = flag;
}

bool SceneVolume::Hover()const {
	return hover_;
}

void SceneVolume::SetHover(bool flag) {
	hover_ = flag;
}

void SceneVolume::LoadMesh(const TriangleMesh& mesh) {
	verts_.load_mesh(mesh);
}

const GLVertexArray& SceneVolume::Verts() const{
	return verts_;
}

GLVertexArray& SceneVolume::Verts() {
	return verts_;
}

void SceneVolume::SetVerts(const GLVertexArray& verts) {
	verts_ = verts;
}



