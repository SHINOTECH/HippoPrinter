#include "RenderGraphic.h"

#include <unordered_set>
#include <utility>
#include <QOpenGLFunctions>
#include <iostream>
#include <QDebug>
RenderGraphic* RenderGraphic::render_ = nullptr;

RenderGraphic::RenderGraphic(){
}


RenderGraphic::~RenderGraphic(){

}

//************************************
// ���ڣ�2016/12/20 
// ����: RenderGraphic *
// ����: ��ȡ����
//************************************
RenderGraphic * RenderGraphic::GetSingleton(){
	if (!render_) {
		render_ = new RenderGraphic;
	}
	return render_;
}

//************************************
// ���ڣ�2016/12/20 
// ����: void
// ����: �ݻٵ���
//************************************
void RenderGraphic::DestroySingleton(){
	if (render_) {
		delete render_;
		render_ = nullptr;
	}
}

//************************************
// ���ڣ�2016/12/20 
// ����: stl_file * stl
// ����: void
// ����: �Ե��Ƶ���ʽ����STL
//************************************
void RenderGraphic::DrawSTLInPoints(stl_file &stl) {
	std::unordered_set<int> vertex_set;

	float original_point_size;
	glGetFloatv(GL_POINT_SIZE, &original_point_size);
	glBegin(GL_POINTS);
	glPointSize(2.0);	//Point��С

	v_indices_struct* temp_v_indices = stl.v_indices;
	stl_facet* facet_array = stl.facet_start;

	for (int facet_index = 0; facet_index < stl.stats.number_of_facets; facet_index++) {
		int vertex_index1 = temp_v_indices[facet_index].vertex[0];
		if (vertex_set.find(vertex_index1) != vertex_set.end()) {
			vertex_set.insert(vertex_index1);
			glVertex3f(facet_array[facet_index].vertex[0].x,
				facet_array[facet_index].vertex[0].y,
				facet_array[facet_index].vertex[0].z);
		}

		int vertex_index2 = temp_v_indices[facet_index].vertex[1];
		if (vertex_set.find(vertex_index2) != vertex_set.end()) {
			vertex_set.insert(vertex_index2);
			glVertex3f(facet_array[facet_index].vertex[1].x,
				facet_array[facet_index].vertex[1].y,
				facet_array[facet_index].vertex[1].z);
		}

		int vertex_index3 = temp_v_indices[facet_index].vertex[2];
		if (vertex_set.find(vertex_index3) != vertex_set.end()) {
			vertex_set.insert(vertex_index3);
			glVertex3f(facet_array[facet_index].vertex[2].x,
				facet_array[facet_index].vertex[2].y,
				facet_array[facet_index].vertex[2].z);
		}
	}
	glEnd();

	glPointSize(original_point_size);
}

//************************************
// ���ڣ�2016/12/20 
// ����: stl_file * stl
// ����: void
// ����: ����ά������ʽ����STL
//************************************
void RenderGraphic::DrawSTLInTriangles(stl_file &stl) {
	stl_facet* facet_array = stl.facet_start;

	glColor3f(0.0, 0.0, 0.0);
	glBegin(GL_TRIANGLES);
	for (int facet_index = 0; facet_index < stl.stats.number_of_facets; ++facet_index) {
		glVertex3f(facet_array[facet_index].vertex[0].x, facet_array[facet_index].vertex[0].y, facet_array[facet_index].vertex[0].z);
		glVertex3f(facet_array[facet_index].vertex[1].x, facet_array[facet_index].vertex[1].y, facet_array[facet_index].vertex[1].z);
		glVertex3f(facet_array[facet_index].vertex[2].x, facet_array[facet_index].vertex[2].y, facet_array[facet_index].vertex[2].z);
// 		qDebug()<<"coordinate:��" << facet_array[facet_index].vertex[0].x << "  "
// 			<< facet_array[facet_index].vertex[0].y << "  "
// 			<< facet_array[facet_index].vertex[0].z;
// 		std::cout << facet_array[facet_index].vertex[0].x << "  "
// 			<< facet_array[facet_index].vertex[0].y << "  "
// 			<< facet_array[facet_index].vertex[0].z << std::endl;
	}
	glEnd();
}

//************************************
// ���ڣ�2016/12/20 
// ����: stl_file * stl
// ����: void
// ����: ���ߵ���ʽ����STL
//************************************
void RenderGraphic::DrawSTLInLines(stl_file &stl){
	int edge_allocated = stl.stats.number_of_facets * 3;
	glBegin(GL_LINES);
	for (int edge_index = 0; edge_index < edge_allocated; ++edge_index) {
		glVertex3f(stl.edge_start[edge_index].p1.x, 
			stl.edge_start[edge_index].p1.y,
			stl.edge_start[edge_index].p1.z);
		glVertex3f(stl.edge_start[edge_index].p2.x,
			stl.edge_start[edge_index].p2.y,
			stl.edge_start[edge_index].p2.z);
	}
	glEnd();
}

