#ifndef slic3r_Flow_hpp_
#define slic3r_Flow_hpp_

#include "libslic3r.h"
#include "Config.hpp"
#include "ExtrusionEntity.hpp"

namespace Slic3r {

#define BRIDGE_EXTRA_SPACING 0.05
#define OVERLAP_FACTOR 1.0

enum FlowRole {
    frExternalPerimeter,
    frPerimeter,
    frInfill,
    frSolidInfill,
    frTopSolidInfill,
    frSupportMaterial,
    frSupportMaterialInterface,
};

class Flow
{
    public:
    double width, height, nozzle_diameter;
    bool bridge;
    
    Flow(double _w, double _h, double _nd, bool _bridge = false)
        : width(_w), height(_h), nozzle_diameter(_nd), bridge(_bridge) {};
    double spacing() const;
    double spacing(const Flow &other) const;
    double mm3_per_mm() const;
    coord_t scaled_width() const {
        return scale_(this->width);
    };
    coord_t scaled_spacing() const {
        return scale_(this->spacing());
    };
    coord_t scaled_spacing(const Flow &other) const {
        return scale_(this->spacing(other));
    };
    
    static Flow new_from_config_width(FlowRole role, const ConfigOptiondoubleOrPercent &width, double nozzle_diameter, double height, double bridge_flow_ratio);
    static Flow new_from_spacing(double spacing, double nozzle_diameter, double height, bool bridge);
    
    private:
    static double _bridge_width(double nozzle_diameter, double bridge_flow_ratio);
    static double _auto_width(FlowRole role, double nozzle_diameter, double height);
    static double _width_from_spacing(double spacing, double nozzle_diameter, double height, bool bridge);
    static double _spacing(double width, double nozzle_diameter, double height, double bridge_flow_ratio);
};

}

#endif
