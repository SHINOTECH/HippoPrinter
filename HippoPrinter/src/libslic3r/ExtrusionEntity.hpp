#ifndef slic3r_ExtrusionEntity_hpp_
#define slic3r_ExtrusionEntity_hpp_

#include "libslic3r.h"
#include "Polygon.hpp"
#include "Polyline.hpp"

namespace Slic3r {

class ExPolygonCollection;
class ExtrusionEntityCollection;
class Extruder;

/* Each ExtrusionRole value identifies a distinct set of { extruder, speed } */
enum ExtrusionRole {
    erNone,
    erPerimeter,
    erExternalPerimeter,
    erOverhangPerimeter,
    erInternalInfill,
    erSolidInfill,
    erTopSolidInfill,
    erBridgeInfill,
    erGapFill,
    erSkirt,
    erSupportMaterial,
    erSupportMaterialInterface,
};

/* Special flags describing loop */
enum ExtrusionLoopRole {
    elrDefault,
    elrContourInternalPerimeter,
    elrSkirt,
};

class ExtrusionEntity
{
    public:
    virtual bool is_collection() const {
        return false;
    };
    virtual bool is_loop() const {
        return false;
    };
    virtual bool can_reverse() const {
        return true;
    };
    virtual ExtrusionEntity* clone() const = 0;
    virtual ~ExtrusionEntity() {};
    virtual void reverse() = 0;
    virtual Point first_point() const = 0;
    virtual Point last_point() const = 0;
    virtual Polygons grow() const = 0;
    virtual double min_mm3_per_mm() const = 0;
    virtual Polyline as_polyline() const = 0;
    virtual double length() const { return 0; };
};

typedef std::vector<ExtrusionEntity*> ExtrusionEntitiesPtr;

class ExtrusionPath : public ExtrusionEntity
{
    public:
    Polyline polyline;
    ExtrusionRole role;
    double mm3_per_mm;  // mm^3 of plastic per mm of linear head motion
    float width;
    float height;
    
    ExtrusionPath(ExtrusionRole role) : role(role), mm3_per_mm(-1), width(-1), height(-1) {};
    ExtrusionPath* clone() const;
    void reverse();
    Point first_point() const;
    Point last_point() const;
    void intersect_expolygons(const ExPolygonCollection &collection, ExtrusionEntityCollection* retval) const;
    void subtract_expolygons(const ExPolygonCollection &collection, ExtrusionEntityCollection* retval) const;
    void clip_end(double distance);
    void simplify(double tolerance);
    virtual double length() const;
    bool is_perimeter() const;
    bool is_infill() const;
    bool is_solid_infill() const;
    bool is_bridge() const;
    Polygons grow() const;
    double min_mm3_per_mm() const {
        return this->mm3_per_mm;
    };
    Polyline as_polyline() const {
        return this->polyline;
    };

    private:
    void _inflate_collection(const Polylines &polylines, ExtrusionEntityCollection* collection) const;
};

typedef std::vector<ExtrusionPath> ExtrusionPaths;

class ExtrusionLoop : public ExtrusionEntity
{
    public:
    ExtrusionPaths paths;
    ExtrusionLoopRole role;
    
    ExtrusionLoop(ExtrusionLoopRole role = elrDefault) : role(role) {};
    ExtrusionLoop(const ExtrusionPaths &paths, ExtrusionLoopRole role = elrDefault)
        : paths(paths), role(role) {};
    ExtrusionLoop(const ExtrusionPath &path, ExtrusionLoopRole role = elrDefault)
        : role(role) {
        this->paths.push_back(path);
    };
    bool is_loop() const {
        return true;
    };
    bool can_reverse() const {
        return false;
    };
    ExtrusionLoop* clone() const;
    bool make_clockwise();
    bool make_counter_clockwise();
    void reverse();
    Point first_point() const;
    Point last_point() const;
    Polygon polygon() const;
    virtual double length() const;
    bool split_at_vertex(const Point &point);
    void split_at(const Point &point);
    void clip_end(double distance, ExtrusionPaths* paths) const;
    bool has_overhang_point(const Point &point) const;
    bool is_perimeter() const;
    bool is_infill() const;
    bool is_solid_infill() const;
    Polygons grow() const;
    double min_mm3_per_mm() const;
    Polyline as_polyline() const {
        return this->polygon().split_at_first_point();
    };
};

}

#endif
