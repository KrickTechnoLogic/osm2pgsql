
#ifndef TAGTRANSFORM_H
#define TAGTRANSFORM_H

#include "config.h"
#include "osmtypes.hpp"

#include <string>

struct options_t;
struct export_list;

#ifdef HAVE_LUA
extern "C" {
    #include <lua.h>
}
#endif



class tagtransform {
public:
	tagtransform(const options_t *options_);
	~tagtransform();

    bool filter_tags(osmium::OSMObject const &o,
                     int *polygon, int *roads, const export_list &exlist,
                     taglist_t &out_tags, bool strict = false);
    unsigned filter_rel_member_tags(const taglist_t &rel_tags,
        const multitaglist_t &member_tags, const rolelist_t &member_roles,
        int *member_superseded, int *make_boundary, int *make_polygon, int *roads,
        const export_list &exlist, taglist_t &out_tags, bool allow_typeless = false);

private:
    bool lua_filter_basic_tags(osmium::OSMObject const &o,
                               int *polygon, int *roads, taglist_t &out_tags);
    bool c_filter_basic_tags(osmium::OSMObject const &o, int *polygon,
                             int *roads, const export_list &exlist,
                             taglist_t &out_tags, bool strict);
    unsigned int lua_filter_rel_member_tags(const taglist_t &rel_tags,
        const multitaglist_t &members_tags, const rolelist_t &member_roles,
        int *member_superseded, int *make_boundary, int *make_polygon, int *roads,
        taglist_t &out_tags);
    void check_lua_function_exists(const std::string &func_name);


	const options_t* options;
	const bool transform_method;
#ifdef HAVE_LUA
	lua_State *L;
    const std::string m_node_func, m_way_func, m_rel_func, m_rel_mem_func;
#endif

};

#endif //TAGTRANSFORM_H
