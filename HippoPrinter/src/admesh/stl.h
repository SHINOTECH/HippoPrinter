/*  ADMesh -- process triangulated solid meshes
<<<<<<< HEAD
*  Copyright (C) 1995, 1996  Anthony D. Martin <amartin@engr.csulb.edu>
*  Copyright (C) 2013, 2014  several contributors, see AUTHORS
*
*  This program is free software; you can redistribute it and/or modify
*  it under the terms of the GNU General Public License as published by
*  the Free Software Foundation; either version 2 of the License, or
*  (at your option) any later version.

*  This program is distributed in the hope that it will be useful,
*  but WITHOUT ANY WARRANTY; without even the implied warranty of
*  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*  GNU General Public License for more details.

*  You should have received a copy of the GNU General Public License along
*  with this program; if not, write to the Free Software Foundation, Inc.,
*  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*
*  Questions, comments, suggestions, etc to
*           https://github.com/admesh/admesh/issues
*/
=======
 *  Copyright (C) 1995, 1996  Anthony D. Martin <amartin@engr.csulb.edu>
 *  Copyright (C) 2013, 2014  several contributors, see AUTHORS
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.

 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 *  Questions, comments, suggestions, etc to
 *           https://github.com/admesh/admesh/issues
 */
>>>>>>> f40a78d240b8b63cb2998281c341e4544b3adecc

#ifndef __admesh_stl__
#define __admesh_stl__

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define STL_MAX(A,B) ((A)>(B)? (A):(B))
#define STL_MIN(A,B) ((A)<(B)? (A):(B))
#define ABS(X)  ((X) < 0 ? -(X) : (X))

#define LABEL_SIZE             80
#define NUM_FACET_SIZE         4
#define HEADER_SIZE            84
#define STL_MIN_FILE_SIZE      284
#define ASCII_LINES_PER_FACET  7
#define SIZEOF_EDGE_SORT       24

<<<<<<< HEAD
	typedef struct {
		double x;
		double y;
		double z;
	} stl_vertex;

	typedef struct {
		double x;
		double y;
		double z;
	} stl_normal;

	typedef char stl_extra[2];

	typedef struct {
		stl_normal normal;
		stl_vertex vertex[3];
		stl_extra  extra;
	} stl_facet;
#define SIZEOF_STL_FACET       50

	typedef enum { binary, ascii, inmemory } stl_type;

	typedef struct {
		stl_vertex p1;
		stl_vertex p2;
		int        facet_number;
	} stl_edge;

	typedef struct stl_hash_edge {
		unsigned       key[6];
		int            facet_number;
		int            which_edge;
		struct stl_hash_edge  *next;
	} stl_hash_edge;

	typedef struct {
		int   neighbor[3];
		char  which_vertex_not[3];
	} stl_neighbors;

	typedef struct {
		int   vertex[3];
	} v_indices_struct;

	typedef struct {
		char          header[81];
		stl_type      type;
		int           number_of_facets;
		stl_vertex    max;
		stl_vertex    min;
		stl_vertex    size;
		double         bounding_diameter;
		double         shortest_edge;
		double         volume;
		double         surface_area;
		unsigned      number_of_blocks;
		int           connected_edges;
		int           connected_facets_1_edge;
		int           connected_facets_2_edge;
		int           connected_facets_3_edge;
		int           facets_w_1_bad_edge;
		int           facets_w_2_bad_edge;
		int           facets_w_3_bad_edge;
		int           original_num_facets;
		int           edges_fixed;
		int           degenerate_facets;
		int           facets_removed;
		int           facets_added;
		int           facets_reversed;
		int           backwards_edges;
		int           normals_fixed;
		int           number_of_parts;
		int           malloced;
		int           freed;
		int           facets_malloced;
		int           collisions;
		int           shared_vertices;
		int           shared_malloced;
	} stl_stats;

	typedef struct {
		FILE          *fp;
		stl_facet     *facet_start;
		stl_edge      *edge_start;
		stl_hash_edge **heads;
		stl_hash_edge *tail;
		int           M;
		stl_neighbors *neighbors_start;
		v_indices_struct *v_indices;
		stl_vertex    *v_shared;
		stl_stats     stats;
		char          error;
	} stl_file;


	extern void stl_open(stl_file *stl, char *file);
	extern void stl_close(stl_file *stl);
	extern void stl_stats_out(stl_file *stl, FILE *file, char *input_file);
	extern void stl_print_edges(stl_file *stl, FILE *file);
	extern void stl_print_neighbors(stl_file *stl, char *file);
	extern void stl_put_little_int(FILE *fp, int value_in);
	extern void stl_put_little_double(FILE *fp, double value_in);
	extern void stl_write_ascii(stl_file *stl, const char *file, const char *label);
	extern void stl_write_binary(stl_file *stl, const char *file, const char *label);
	extern void stl_write_binary_block(stl_file *stl, FILE *fp);
	extern void stl_check_facets_exact(stl_file *stl);
	extern void stl_check_facets_nearby(stl_file *stl, double tolerance);
	extern void stl_remove_unconnected_facets(stl_file *stl);
	extern void stl_write_vertex(stl_file *stl, int facet, int vertex);
	extern void stl_write_facet(stl_file *stl, char *label, int facet);
	extern void stl_write_edge(stl_file *stl, char *label, stl_hash_edge edge);
	extern void stl_write_neighbor(stl_file *stl, int facet);
	extern void stl_write_quad_object(stl_file *stl, char *file);
	extern void stl_verify_neighbors(stl_file *stl);
	extern void stl_fill_holes(stl_file *stl);
	extern void stl_fix_normal_directions(stl_file *stl);
	extern void stl_fix_normal_values(stl_file *stl);
	extern void stl_reverse_all_facets(stl_file *stl);
	extern void stl_translate(stl_file *stl, double x, double y, double z);
	extern void stl_translate_relative(stl_file *stl, double x, double y, double z);
	extern void stl_scale_versor(stl_file *stl, double versor[3]);
	extern void stl_scale(stl_file *stl, double factor);
	extern void stl_rotate_x(stl_file *stl, double angle);
	extern void stl_rotate_y(stl_file *stl, double angle);
	extern void stl_rotate_z(stl_file *stl, double angle);
	extern void stl_mirror_xy(stl_file *stl);
	extern void stl_mirror_yz(stl_file *stl);
	extern void stl_mirror_xz(stl_file *stl);
	extern void stl_open_merge(stl_file *stl, char *file);
	extern void stl_invalidate_shared_vertices(stl_file *stl);
	extern void stl_generate_shared_vertices(stl_file *stl);
	extern void stl_write_obj(stl_file *stl, char *file);
	extern void stl_write_off(stl_file *stl, char *file);
	extern void stl_write_dxf(stl_file *stl, char *file, char *label);
	extern void stl_write_vrml(stl_file *stl, char *file);
	extern void stl_calculate_normal(double normal[], stl_facet *facet);
	extern void stl_normalize_vector(double v[]);
	extern void stl_calculate_volume(stl_file *stl);
	extern void stl_calculate_surface_area(stl_file *stl);

	extern void stl_repair(stl_file *stl, int fixall_flag, int exact_flag, int tolerance_flag, double tolerance, int increment_flag, double increment, int nearby_flag, int iterations, int remove_unconnected_flag, int fill_holes_flag, int normal_directions_flag, int normal_values_flag, int reverse_all_flag, int verbose_flag);

	extern void stl_initialize(stl_file *stl);
	extern void stl_count_facets(stl_file *stl, char *file);
	extern void stl_allocate(stl_file *stl);
	extern void stl_read(stl_file *stl, int first_facet, int first);
	extern void stl_facet_stats(stl_file *stl, stl_facet facet, int first);
	extern void stl_reallocate(stl_file *stl);
	extern void stl_add_facet(stl_file *stl, stl_facet *new_facet);
	extern void stl_get_size(stl_file *stl);

	extern void stl_clear_error(stl_file *stl);
	extern int stl_get_error(stl_file *stl);
	extern void stl_exit_on_error(stl_file *stl);
=======
//STL顶点
typedef struct {
  double x;
  double y;
  double z;
} stl_vertex;

//STL 法向量
typedef struct {
  double x;
  double y;
  double z;
} stl_normal;

typedef char stl_extra[2];

//STL三角面片
typedef struct {
  stl_normal normal;
  stl_vertex vertex[3];
  stl_extra  extra;
} stl_facet;
#define SIZEOF_STL_FACET       50

typedef enum {binary, ascii, inmemory} stl_type;

//STL边
typedef struct {
  stl_vertex p1;
  stl_vertex p2;
  int        facet_number;
} stl_edge;

//STL的哈希边
typedef struct stl_hash_edge {
  unsigned       key[6];
  int            facet_number;
  int            which_edge;
  struct stl_hash_edge  *next;
} stl_hash_edge;

//STL相邻
typedef struct {
  int   neighbor[3];
  char  which_vertex_not[3];
} stl_neighbors;

//STL顶点索引
typedef struct {
  int   vertex[3];
} v_indices_struct;


//STL状态
typedef struct {
  char          header[81];		//头
  stl_type      type;		//类型
  int           number_of_facets;	//三角面片数量
  stl_vertex    max;	//顶点
  stl_vertex    min;	//
  stl_vertex    size;	//
  double         bounding_diameter;	//边界半径
  double         shortest_edge;	//最短边长
  double         volume;		//体积
  unsigned      number_of_blocks;	
  int           connected_edges;	//相连的边数
  int           connected_facets_1_edge;	
  int           connected_facets_2_edge;
  int           connected_facets_3_edge;
  int           facets_w_1_bad_edge;
  int           facets_w_2_bad_edge;
  int           facets_w_3_bad_edge;
  int           original_num_facets;
  int           edges_fixed;
  int           degenerate_facets;
  int           facets_removed;		//移除的三角面片数量
  int           facets_added;		//添加的三角面片数量
  int           facets_reversed;	//翻转的三角面片数量
  int           backwards_edges;	
  int           normals_fixed;		//固定不变的法线数量
  int           number_of_parts;	//part数量
  int           malloced;			//分配了内存
  int           freed;				//释放了内存
  int           facets_malloced;	//分配了三角面片内存
  int           collisions;			//碰撞
  int           shared_vertices;	//共享的顶点数量
  int           shared_malloced;	//
} stl_stats;

typedef struct {
  FILE          *fp;	//文件指针
  stl_facet     *facet_start;	//三角面片指针开始地址
  stl_edge      *edge_start;	//边指针开始地址
  stl_hash_edge **heads;	//头
  stl_hash_edge *tail;	//尾	
  int           M;
  stl_neighbors *neighbors_start;			//相邻的指针地址
  v_indices_struct *v_indices;		//顶点索引指针
  stl_vertex    *v_shared;	//
  stl_stats     stats;	//状态指针
  char          error;
} stl_file;


extern void stl_open(stl_file *stl, char *file);
extern void stl_close(stl_file *stl);
extern void stl_stats_out(stl_file *stl, FILE *file, char *input_file);
extern void stl_print_edges(stl_file *stl, FILE *file);
extern void stl_print_neighbors(stl_file *stl, char *file);
extern void stl_put_little_int(FILE *fp, int value_in);
extern void stl_put_little_double(FILE *fp, double value_in);
extern void stl_write_ascii(stl_file *stl, const char *file, const char *label);
extern void stl_write_binary(stl_file *stl, const char *file, const char *label);
extern void stl_write_binary_block(stl_file *stl, FILE *fp);
extern void stl_check_facets_exact(stl_file *stl);
extern void stl_check_facets_nearby(stl_file *stl, double tolerance);
extern void stl_remove_unconnected_facets(stl_file *stl);
extern void stl_write_vertex(stl_file *stl, int facet, int vertex);
extern void stl_write_facet(stl_file *stl, char *label, int facet);
extern void stl_write_edge(stl_file *stl, char *label, stl_hash_edge edge);
extern void stl_write_neighbor(stl_file *stl, int facet);
extern void stl_write_quad_object(stl_file *stl, char *file);
extern void stl_verify_neighbors(stl_file *stl);
extern void stl_fill_holes(stl_file *stl);
extern void stl_fix_normal_directions(stl_file *stl);
extern void stl_fix_normal_values(stl_file *stl);
extern void stl_reverse_all_facets(stl_file *stl);
extern void stl_translate(stl_file *stl, double x, double y, double z);
extern void stl_translate_relative(stl_file *stl, double x, double y, double z);
extern void stl_scale_versor(stl_file *stl, double versor[3]);
extern void stl_scale(stl_file *stl, double factor);
extern void stl_rotate_x(stl_file *stl, double angle);
extern void stl_rotate_y(stl_file *stl, double angle);
extern void stl_rotate_z(stl_file *stl, double angle);
extern void stl_mirror_xy(stl_file *stl);
extern void stl_mirror_yz(stl_file *stl);
extern void stl_mirror_xz(stl_file *stl);
extern void stl_open_merge(stl_file *stl, char *file);
extern void stl_invalidate_shared_vertices(stl_file *stl);
extern void stl_generate_shared_vertices(stl_file *stl);
extern void stl_write_obj(stl_file *stl, char *file);
extern void stl_write_off(stl_file *stl, char *file);
extern void stl_write_dxf(stl_file *stl, char *file, char *label);
extern void stl_write_vrml(stl_file *stl, char *file);
extern void stl_calculate_normal(double normal[], stl_facet *facet);
extern void stl_normalize_vector(double v[]);
extern void stl_calculate_volume(stl_file *stl);

extern void stl_repair(stl_file *stl, int fixall_flag, int exact_flag, int tolerance_flag, double tolerance, int increment_flag, double increment, int nearby_flag, int iterations, int remove_unconnected_flag, int fill_holes_flag, int normal_directions_flag, int normal_values_flag, int reverse_all_flag, int verbose_flag);

extern void stl_initialize(stl_file *stl);
extern void stl_count_facets(stl_file *stl, char *file);
extern void stl_allocate(stl_file *stl);
extern void stl_read(stl_file *stl, int first_facet, int first);
extern void stl_facet_stats(stl_file *stl, stl_facet facet, int first);
extern void stl_reallocate(stl_file *stl);
extern void stl_add_facet(stl_file *stl, stl_facet *new_facet);
extern void stl_get_size(stl_file *stl);

extern void stl_clear_error(stl_file *stl);
extern int stl_get_error(stl_file *stl);
extern void stl_exit_on_error(stl_file *stl);
>>>>>>> f40a78d240b8b63cb2998281c341e4544b3adecc

#ifdef __cplusplus
}
#endif

#endif
