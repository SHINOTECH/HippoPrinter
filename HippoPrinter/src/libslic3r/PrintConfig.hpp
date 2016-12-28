#ifndef slic3r_PrintConfig_hpp_
#define slic3r_PrintConfig_hpp_

#include "libslic3r.h"
#include "Config.hpp"

#define OPT_PTR(KEY) if (opt_key == #KEY) return &this->KEY

namespace Slic3r {

enum GCodeFlavor {
    gcfRepRap, gcfTeacup, gcfMakerWare, gcfSailfish, gcfMach3, gcfMachinekit, gcfNoExtrusion,
};

enum InfillPattern {
    ipRectilinear, ipGrid, ipLine, ipConcentric, ipHoneycomb, ip3DHoneycomb,
    ipHilbertCurve, ipArchimedeanChords, ipOctagramSpiral,
};

enum SupportMaterialPattern {
    smpRectilinear, smpRectilinearGrid, smpHoneycomb, smpPillars,
};

enum SeamPosition {
    spRandom, spNearest, spAligned
};

template<> inline t_config_enum_values ConfigOptionEnum<GCodeFlavor>::get_enum_values() {
    t_config_enum_values keys_map;
    keys_map["reprap"]          = gcfRepRap;
    keys_map["teacup"]          = gcfTeacup;
    keys_map["makerware"]       = gcfMakerWare;
    keys_map["sailfish"]        = gcfSailfish;
    keys_map["mach3"]           = gcfMach3;
    keys_map["machinekit"]      = gcfMachinekit;
    keys_map["no-extrusion"]    = gcfNoExtrusion;
    return keys_map;
}

template<> inline t_config_enum_values ConfigOptionEnum<InfillPattern>::get_enum_values() {
    t_config_enum_values keys_map;
    keys_map["rectilinear"]         = ipRectilinear;
    keys_map["grid"]                = ipGrid;
    keys_map["line"]                = ipLine;
    keys_map["concentric"]          = ipConcentric;
    keys_map["honeycomb"]           = ipHoneycomb;
    keys_map["3dhoneycomb"]         = ip3DHoneycomb;
    keys_map["hilbertcurve"]        = ipHilbertCurve;
    keys_map["archimedeanchords"]   = ipArchimedeanChords;
    keys_map["octagramspiral"]      = ipOctagramSpiral;
    return keys_map;
}

template<> inline t_config_enum_values ConfigOptionEnum<SupportMaterialPattern>::get_enum_values() {
    t_config_enum_values keys_map;
    keys_map["rectilinear"]         = smpRectilinear;
    keys_map["rectilinear-grid"]    = smpRectilinearGrid;
    keys_map["honeycomb"]           = smpHoneycomb;
    keys_map["pillars"]             = smpPillars;
    return keys_map;
}

template<> inline t_config_enum_values ConfigOptionEnum<SeamPosition>::get_enum_values() {
    t_config_enum_values keys_map;
    keys_map["random"]              = spRandom;
    keys_map["nearest"]             = spNearest;
    keys_map["aligned"]             = spAligned;
    return keys_map;
}

class PrintConfigDef : public ConfigDef
{
    public:
    PrintConfigDef();
};

extern PrintConfigDef print_config_def;

class PrintConfigBase : public virtual ConfigBase
{
    public:
    PrintConfigBase() {
        this->def = &print_config_def;
    };
    
    double min_object_distance() const;
};

class DynamicPrintConfig : public PrintConfigBase, public DynamicConfig
{
    public:
    DynamicPrintConfig() : PrintConfigBase(), DynamicConfig() {};
    void normalize();
};

class StaticPrintConfig : public PrintConfigBase, public StaticConfig
{
    public:
    StaticPrintConfig() : PrintConfigBase(), StaticConfig() {};
};

class PrintObjectConfig : public virtual StaticPrintConfig
{
    public:
    ConfigOptionBool                dont_support_bridges;
    ConfigOptiondoubleOrPercent      extrusion_width;
    ConfigOptiondoubleOrPercent      first_layer_height;
    ConfigOptionBool                infill_only_where_needed;
    ConfigOptionBool                interface_shells;
    ConfigOptiondouble               layer_height;
    ConfigOptionInt                 raft_layers;
    ConfigOptionEnum<SeamPosition>  seam_position;
    ConfigOptionBool                support_material;
    ConfigOptionInt                 support_material_angle;
    ConfigOptiondouble               support_material_contact_distance;
    ConfigOptionInt                 support_material_enforce_layers;
    ConfigOptionInt                 support_material_extruder;
    ConfigOptiondoubleOrPercent      support_material_extrusion_width;
    ConfigOptionInt                 support_material_interface_extruder;
    ConfigOptionInt                 support_material_interface_layers;
    ConfigOptiondouble               support_material_interface_spacing;
    ConfigOptiondoubleOrPercent      support_material_interface_speed;
    ConfigOptionEnum<SupportMaterialPattern> support_material_pattern;
    ConfigOptiondouble               support_material_spacing;
    ConfigOptiondouble               support_material_speed;
    ConfigOptionInt                 support_material_threshold;
    ConfigOptiondouble               xy_size_compensation;
    
    PrintObjectConfig() : StaticPrintConfig() {
        this->set_defaults();
    };
    
    virtual ConfigOption* optptr(const t_config_option_key &opt_key, bool create = false) {
        OPT_PTR(dont_support_bridges);
        OPT_PTR(extrusion_width);
        OPT_PTR(first_layer_height);
        OPT_PTR(infill_only_where_needed);
        OPT_PTR(interface_shells);
        OPT_PTR(layer_height);
        OPT_PTR(raft_layers);
        OPT_PTR(seam_position);
        OPT_PTR(support_material);
        OPT_PTR(support_material_angle);
        OPT_PTR(support_material_contact_distance);
        OPT_PTR(support_material_enforce_layers);
        OPT_PTR(support_material_extruder);
        OPT_PTR(support_material_extrusion_width);
        OPT_PTR(support_material_interface_extruder);
        OPT_PTR(support_material_interface_layers);
        OPT_PTR(support_material_interface_spacing);
        OPT_PTR(support_material_interface_speed);
        OPT_PTR(support_material_pattern);
        OPT_PTR(support_material_spacing);
        OPT_PTR(support_material_speed);
        OPT_PTR(support_material_threshold);
        OPT_PTR(xy_size_compensation);
        
        return NULL;
    };
};

class PrintRegionConfig : public virtual StaticPrintConfig
{
    public:
    ConfigOptionInt                 bottom_solid_layers;
    ConfigOptiondouble               bridge_flow_ratio;
    ConfigOptiondouble               bridge_speed;
    ConfigOptionEnum<InfillPattern> external_fill_pattern;
    ConfigOptiondoubleOrPercent      external_perimeter_extrusion_width;
    ConfigOptiondoubleOrPercent      external_perimeter_speed;
    ConfigOptionBool                external_perimeters_first;
    ConfigOptionBool                extra_perimeters;
    ConfigOptiondouble               fill_angle;
    ConfigOptionPercent             fill_density;
    ConfigOptionEnum<InfillPattern> fill_pattern;
    ConfigOptiondouble               gap_fill_speed;
    ConfigOptionInt                 infill_extruder;
    ConfigOptiondoubleOrPercent      infill_extrusion_width;
    ConfigOptionInt                 infill_every_layers;
    ConfigOptiondoubleOrPercent      infill_overlap;
    ConfigOptiondouble               infill_speed;
    ConfigOptionBool                overhangs;
    ConfigOptionInt                 perimeter_extruder;
    ConfigOptiondoubleOrPercent      perimeter_extrusion_width;
    ConfigOptiondouble               perimeter_speed;
    ConfigOptionInt                 perimeters;
    ConfigOptiondoubleOrPercent      small_perimeter_speed;
    ConfigOptiondouble               solid_infill_below_area;
    ConfigOptionInt                 solid_infill_extruder;
    ConfigOptiondoubleOrPercent      solid_infill_extrusion_width;
    ConfigOptionInt                 solid_infill_every_layers;
    ConfigOptiondoubleOrPercent      solid_infill_speed;
    ConfigOptionBool                thin_walls;
    ConfigOptiondoubleOrPercent      top_infill_extrusion_width;
    ConfigOptionInt                 top_solid_layers;
    ConfigOptiondoubleOrPercent      top_solid_infill_speed;
    
    PrintRegionConfig() : StaticPrintConfig() {
        this->set_defaults();
    };
    
    virtual ConfigOption* optptr(const t_config_option_key &opt_key, bool create = false) {
        OPT_PTR(bottom_solid_layers);
        OPT_PTR(bridge_flow_ratio);
        OPT_PTR(bridge_speed);
        OPT_PTR(external_fill_pattern);
        OPT_PTR(external_perimeter_extrusion_width);
        OPT_PTR(external_perimeter_speed);
        OPT_PTR(external_perimeters_first);
        OPT_PTR(extra_perimeters);
        OPT_PTR(fill_angle);
        OPT_PTR(fill_density);
        OPT_PTR(fill_pattern);
        OPT_PTR(gap_fill_speed);
        OPT_PTR(infill_extruder);
        OPT_PTR(infill_extrusion_width);
        OPT_PTR(infill_every_layers);
        OPT_PTR(infill_overlap);
        OPT_PTR(infill_speed);
        OPT_PTR(overhangs);
        OPT_PTR(perimeter_extruder);
        OPT_PTR(perimeter_extrusion_width);
        OPT_PTR(perimeter_speed);
        OPT_PTR(perimeters);
        OPT_PTR(small_perimeter_speed);
        OPT_PTR(solid_infill_below_area);
        OPT_PTR(solid_infill_extruder);
        OPT_PTR(solid_infill_extrusion_width);
        OPT_PTR(solid_infill_every_layers);
        OPT_PTR(solid_infill_speed);
        OPT_PTR(thin_walls);
        OPT_PTR(top_infill_extrusion_width);
        OPT_PTR(top_solid_infill_speed);
        OPT_PTR(top_solid_layers);
        
        return NULL;
    };
};

class GCodeConfig : public virtual StaticPrintConfig
{
    public:
    ConfigOptionString              before_layer_gcode;
    ConfigOptionString              end_gcode;
    ConfigOptionString              extrusion_axis;
    ConfigOptiondoubles              extrusion_multiplier;
    ConfigOptiondoubles              filament_diameter;
    ConfigOptionBool                gcode_comments;
    ConfigOptionEnum<GCodeFlavor>   gcode_flavor;
    ConfigOptionString              layer_gcode;
    ConfigOptiondouble               max_print_speed;
    ConfigOptiondouble               max_volumetric_speed;
    ConfigOptiondouble               pressure_advance;
    ConfigOptiondoubles              retract_length;
    ConfigOptiondoubles              retract_length_toolchange;
    ConfigOptiondoubles              retract_lift;
    ConfigOptiondoubles              retract_lift_above;
    ConfigOptiondoubles              retract_lift_below;
    ConfigOptiondoubles              retract_restart_extra;
    ConfigOptiondoubles              retract_restart_extra_toolchange;
    ConfigOptiondoubles              retract_speed;
    ConfigOptionString              start_gcode;
    ConfigOptionString              toolchange_gcode;
    ConfigOptiondouble               travel_speed;
    ConfigOptionBool                use_firmware_retraction;
    ConfigOptionBool                use_relative_e_distances;
    ConfigOptionBool                use_volumetric_e;
    
    GCodeConfig() : StaticPrintConfig() {
        this->set_defaults();
    };
    
    virtual ConfigOption* optptr(const t_config_option_key &opt_key, bool create = false) {
        OPT_PTR(before_layer_gcode);
        OPT_PTR(end_gcode);
        OPT_PTR(extrusion_axis);
        OPT_PTR(extrusion_multiplier);
        OPT_PTR(filament_diameter);
        OPT_PTR(gcode_comments);
        OPT_PTR(gcode_flavor);
        OPT_PTR(layer_gcode);
        OPT_PTR(max_print_speed);
        OPT_PTR(max_volumetric_speed);
        OPT_PTR(pressure_advance);
        OPT_PTR(retract_length);
        OPT_PTR(retract_length_toolchange);
        OPT_PTR(retract_lift);
        OPT_PTR(retract_lift_above);
        OPT_PTR(retract_lift_below);
        OPT_PTR(retract_restart_extra);
        OPT_PTR(retract_restart_extra_toolchange);
        OPT_PTR(retract_speed);
        OPT_PTR(start_gcode);
        OPT_PTR(toolchange_gcode);
        OPT_PTR(travel_speed);
        OPT_PTR(use_firmware_retraction);
        OPT_PTR(use_relative_e_distances);
        OPT_PTR(use_volumetric_e);
        
        return NULL;
    };
    
    std::string get_extrusion_axis() const
    {
        if ((this->gcode_flavor.value == gcfMach3) || (this->gcode_flavor.value == gcfMachinekit)) {
            return "A";
        } else if (this->gcode_flavor.value == gcfNoExtrusion) {
            return "";
        } else {
            return this->extrusion_axis.value;
        }
    };
};

class PrintConfig : public GCodeConfig
{
    public:
    ConfigOptionBool                avoid_crossing_perimeters;
    ConfigOptionPoints              bed_shape;
    ConfigOptionInt                 bed_temperature;
    ConfigOptiondouble               bridge_acceleration;
    ConfigOptionInt                 bridge_fan_speed;
    ConfigOptiondouble               brim_width;
    ConfigOptionBool                complete_objects;
    ConfigOptionBool                cooling;
    ConfigOptiondouble               default_acceleration;
    ConfigOptionInt                 disable_fan_first_layers;
    ConfigOptiondouble               duplicate_distance;
    ConfigOptiondouble               extruder_clearance_height;
    ConfigOptiondouble               extruder_clearance_radius;
    ConfigOptionPoints              extruder_offset;
    ConfigOptionBool                fan_always_on;
    ConfigOptionInt                 fan_below_layer_time;
    ConfigOptionStrings             filament_colour;
    ConfigOptiondouble               first_layer_acceleration;
    ConfigOptionInt                 first_layer_bed_temperature;
    ConfigOptiondoubleOrPercent      first_layer_extrusion_width;
    ConfigOptiondoubleOrPercent      first_layer_speed;
    ConfigOptionInts                first_layer_temperature;
    ConfigOptionBool                gcode_arcs;
    ConfigOptiondouble               infill_acceleration;
    ConfigOptionBool                infill_first;
    ConfigOptionInt                 max_fan_speed;
    ConfigOptionInt                 min_fan_speed;
    ConfigOptiondouble               min_print_speed;
    ConfigOptiondouble               min_skirt_length;
    ConfigOptionString              notes;
    ConfigOptiondoubles              nozzle_diameter;
    ConfigOptionBool                only_retract_when_crossing_perimeters;
    ConfigOptionBool                ooze_prevention;
    ConfigOptionString              output_filename_format;
    ConfigOptiondouble               perimeter_acceleration;
    ConfigOptionStrings             post_process;
    ConfigOptiondouble               resolution;
    ConfigOptiondoubles              retract_before_travel;
    ConfigOptionBools               retract_layer_change;
    ConfigOptiondouble               skirt_distance;
    ConfigOptionInt                 skirt_height;
    ConfigOptionInt                 skirts;
    ConfigOptionInt                 slowdown_below_layer_time;
    ConfigOptionBool                spiral_vase;
    ConfigOptionInt                 standby_temperature_delta;
    ConfigOptionInts                temperature;
    ConfigOptionInt                 threads;
    ConfigOptiondouble               vibration_limit;
    ConfigOptionBools               wipe;
    ConfigOptiondouble               z_offset;
    
    PrintConfig() : GCodeConfig() {
        this->set_defaults();
    };
    
    virtual ConfigOption* optptr(const t_config_option_key &opt_key, bool create = false) {
        OPT_PTR(avoid_crossing_perimeters);
        OPT_PTR(bed_shape);
        OPT_PTR(bed_temperature);
        OPT_PTR(bridge_acceleration);
        OPT_PTR(bridge_fan_speed);
        OPT_PTR(brim_width);
        OPT_PTR(complete_objects);
        OPT_PTR(cooling);
        OPT_PTR(default_acceleration);
        OPT_PTR(disable_fan_first_layers);
        OPT_PTR(duplicate_distance);
        OPT_PTR(extruder_clearance_height);
        OPT_PTR(extruder_clearance_radius);
        OPT_PTR(extruder_offset);
        OPT_PTR(fan_always_on);
        OPT_PTR(fan_below_layer_time);
        OPT_PTR(filament_colour);
        OPT_PTR(first_layer_acceleration);
        OPT_PTR(first_layer_bed_temperature);
        OPT_PTR(first_layer_extrusion_width);
        OPT_PTR(first_layer_speed);
        OPT_PTR(first_layer_temperature);
        OPT_PTR(gcode_arcs);
        OPT_PTR(infill_acceleration);
        OPT_PTR(infill_first);
        OPT_PTR(max_fan_speed);
        OPT_PTR(min_fan_speed);
        OPT_PTR(min_print_speed);
        OPT_PTR(min_skirt_length);
        OPT_PTR(notes);
        OPT_PTR(nozzle_diameter);
        OPT_PTR(only_retract_when_crossing_perimeters);
        OPT_PTR(ooze_prevention);
        OPT_PTR(output_filename_format);
        OPT_PTR(perimeter_acceleration);
        OPT_PTR(post_process);
        OPT_PTR(resolution);
        OPT_PTR(retract_before_travel);
        OPT_PTR(retract_layer_change);
        OPT_PTR(skirt_distance);
        OPT_PTR(skirt_height);
        OPT_PTR(skirts);
        OPT_PTR(slowdown_below_layer_time);
        OPT_PTR(spiral_vase);
        OPT_PTR(standby_temperature_delta);
        OPT_PTR(temperature);
        OPT_PTR(threads);
        OPT_PTR(vibration_limit);
        OPT_PTR(wipe);
        OPT_PTR(z_offset);
        
        // look in parent class
        ConfigOption* opt;
        if ((opt = GCodeConfig::optptr(opt_key, create)) != NULL) return opt;
        
        return NULL;
    };
};

class HostConfig : public virtual StaticPrintConfig
{
    public:
    ConfigOptionString              octoprint_host;
    ConfigOptionString              octoprint_apikey;
    ConfigOptionString              serial_port;
    ConfigOptionInt                 serial_speed;
    
    HostConfig() : StaticPrintConfig() {
        this->set_defaults();
    };
    
    virtual ConfigOption* optptr(const t_config_option_key &opt_key, bool create = false) {
        OPT_PTR(octoprint_host);
        OPT_PTR(octoprint_apikey);
        OPT_PTR(serial_port);
        OPT_PTR(serial_speed);
        
        return NULL;
    };
};

class FullPrintConfig
    : public PrintObjectConfig, public PrintRegionConfig, public PrintConfig, public HostConfig
{
    public:
    virtual ConfigOption* optptr(const t_config_option_key &opt_key, bool create = false) {
        ConfigOption* opt;
        if ((opt = PrintObjectConfig::optptr(opt_key, create)) != NULL) return opt;
        if ((opt = PrintRegionConfig::optptr(opt_key, create)) != NULL) return opt;
        if ((opt = PrintConfig::optptr(opt_key, create)) != NULL) return opt;
        if ((opt = HostConfig::optptr(opt_key, create)) != NULL) return opt;
        return NULL;
    };
};

}

#endif
