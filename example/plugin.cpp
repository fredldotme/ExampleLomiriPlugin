#include <lomiriplugin.h>

#include <string>
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

// Basic interface as required by plugins
class LomiriPluginHostInterface {};

// Search results in the drawer
struct LomiriPluginDrawerSearchResult {
    std::string title;
    std::string sourceIcon;
};

// Implementing the "search results" interface
class LomiriPluginDrawerSearch : public LomiriPluginHostInterface {
public:
    void search(const std::string& query);
    LomiriPluginDrawerSearchResult* get();
    LomiriPluginDrawerSearchResult* next();
private:
    std::vector<LomiriPluginDrawerSearchResult> searchResults;
    std::vector<LomiriPluginDrawerSearchResult>::iterator cit;
};

// Only one instantiation
static LomiriPluginDrawerSearch globalDrawerSearch;

// Initiate a search based on the query parameter "contents"
void LomiriPluginDrawerSearch::search(const std::string& query)
{
    searchResults.clear();

    for (int i = 0; i < 3; i++) {
        LomiriPluginDrawerSearchResult res;
        res.title = "Example Plugin";
        res.sourceIcon = "";
        searchResults.push_back(res);
    }

    cit = searchResults.begin();

    return;
}

// Get the DrawerSearchResult at the current position.
LomiriPluginDrawerSearchResult* LomiriPluginDrawerSearch::get()
{
    return &(*cit);
}

// Get the next DrawerSearchResult, or nullptr if at the end.
LomiriPluginDrawerSearchResult* LomiriPluginDrawerSearch::next()
{
    auto it = (cit + 1);

    if (it == searchResults.end())
        return nullptr;

    cit = it;
    return &(*it);
}

// The set of features this plugin implements.
LomiriPluginFeatures lomiri_plugin_features()
{
    return LomiriPluginFeatures::DrawerResultsFeature;
}

// Name of the Lomiri Plugin.
const char* lomiri_plugin_name()
{
    return "ExampleDrawerSearchPlugin";
}

// Description of Lomiri Plugin.
const char* lomiri_plugin_description()
{
    return "Showcasing plugin integration into the Lomiri Drawer";
}

// Get an interface to the requested feature.
LomiriPluginInterface lomiri_plugin_get_interface(const LomiriPluginFeatures feature)
{
    switch (feature) {
    case LomiriPluginFeatures::DrawerResultsFeature:
        return static_cast<LomiriPluginInterface>(&globalDrawerSearch);
    default:
        return nullptr;
    }
}

// Initiating a search for "contents"
void lomiri_plugin_drawersearch_search(LomiriPluginInterface interface, const char* query)
{
    auto drawer_search = static_cast<LomiriPluginDrawerSearch*>(interface);
    if (!drawer_search)
        return;

    drawer_search->search(std::string(query));
}

// Get the DrawerSearchResult of the current position.
LomiriDrawerSearchResult lomiri_plugin_drawersearch_get(LomiriPluginInterface interface)
{
    auto drawer_search = static_cast<LomiriPluginDrawerSearch*>(interface);
    if (!drawer_search)
        return nullptr;

    const auto result = drawer_search->get();
    return static_cast<LomiriDrawerSearchResult>(result);
}

// Get the DrawerSearchResult of the next position.
LomiriDrawerSearchResult lomiri_plugin_drawersearch_next(LomiriPluginInterface interface)
{
    auto drawer_search = static_cast<LomiriPluginDrawerSearch*>(interface);
    if (!drawer_search)
        return nullptr;

    const auto result = drawer_search->next();
    return static_cast<LomiriDrawerSearchResult>(result);
}

// Returns the title of the DrawerSearchResult.
const char* lomiri_plugin_drawersearch_result_title(LomiriDrawerSearchResult result)
{
    if (!result)
        return nullptr;

    const auto res = static_cast<LomiriPluginDrawerSearchResult*>(result);
    return res->title.c_str();
}

// Returns an optional icon of the DrawerSearchResult.
const char* lomiri_plugin_drawersearch_result_sourceicon(LomiriDrawerSearchResult result)
{
    if (!result)
        return nullptr;

    const auto res = static_cast<LomiriPluginDrawerSearchResult*>(result);
    return res->sourceIcon.c_str();
}

// TODO: Missing native interfaces exported into the WASM runtime.
//       Required for updating the model from inside the plugin,
//       or open URLs returned by the search result.

void lomiri_plugin_drawersearch_result_open(LomiriDrawerSearchResult result)
{
}

#ifdef __cplusplus
}
#endif