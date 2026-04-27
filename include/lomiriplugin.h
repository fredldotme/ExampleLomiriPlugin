#ifndef LOMIRI_PLUGININTERFACE_H
#define LOMIRI_PLUGININTERFACE_H

#ifdef __cplusplus
extern "C"{
#endif

enum LomiriPluginFeatures {
    NoneFeature = 0,
    DrawerResultsFeature = (1 << 1),
};

// Specializations
typedef void* LomiriPluginInterface;
typedef void* LomiriDrawerSearchResult;
typedef void* LomiriDrawerSearchModel;

// Plugins define publicly available functions
#define PUBLIC __attribute__((visibility("default")))

// Main entry points
LomiriPluginFeatures PUBLIC lomiri_plugin_features();
const char* PUBLIC lomiri_plugin_name();
const char* PUBLIC lomiri_plugin_description();
LomiriPluginInterface PUBLIC lomiri_plugin_get_interface(const LomiriPluginFeatures feature);

// LomiriDrawerSearch interface
void PUBLIC lomiri_plugin_drawersearch_search(LomiriPluginInterface interface, const char* contents);
LomiriDrawerSearchResult PUBLIC lomiri_plugin_drawersearch_find(LomiriPluginInterface interface);
LomiriDrawerSearchResult PUBLIC lomiri_plugin_drawersearch_next(LomiriPluginInterface interface);

// LomiriDrawerSearchResults
const char* PUBLIC lomiri_plugin_drawersearch_result_title(LomiriDrawerSearchResult result);
const char* PUBLIC lomiri_plugin_drawersearch_result_sourceicon(LomiriDrawerSearchResult result);
void PUBLIC lomiri_plugin_drawersearch_result_open(LomiriDrawerSearchResult result);

#ifdef __cplusplus
}
#endif
#endif
