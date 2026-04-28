#include <lomiriplugin.h>

#include <string>
#include <vector>

// Search results in the drawer
struct LomiriPluginDrawerSearchResult {
    const std::string title;
    const std::string sourceIcon;
};

// Implementing the "search" & "search results" interface
class LomiriPluginDrawerSearch {
public:
    void search(const std::string& query) const;
    LomiriPluginDrawerSearchResult* get() const;
    LomiriPluginDrawerSearchResult* next() const;
private:
    mutable std::vector<LomiriPluginDrawerSearchResult> searchResults;
    mutable std::vector<LomiriPluginDrawerSearchResult>::iterator cit;
};

// Only one instantiation
static LomiriPluginDrawerSearch globalDrawerSearch;

// Initiate a search based on the parameter "query"
void LomiriPluginDrawerSearch::search(const std::string& query) const
{
    searchResults.clear();

    for (int i = 0; i < 3; i++) {
        const LomiriPluginDrawerSearchResult res {
            .title = "Example plugin",
            .sourceIcon = ""
        };
        searchResults.push_back(res);
    }

    cit = searchResults.begin();

    return;
}

// Get the DrawerSearchResult at the current position.
LomiriPluginDrawerSearchResult* LomiriPluginDrawerSearch::get() const
{
    return &(*cit);
}

// Get the next DrawerSearchResult, or nullptr if at the end.
LomiriPluginDrawerSearchResult* LomiriPluginDrawerSearch::next() const
{
    const auto it = (cit + 1);

    if (it == searchResults.end())
        return nullptr;

    cit = it;
    return &(*cit);
}

// Public API starts here
extern "C" {

// The set of features this plugin implements.
LomiriPluginFeatures lomiri_plugin_features()
{
    return LomiriPluginFeatures::DrawerSearchResultsFeature;
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
    case LomiriPluginFeatures::DrawerSearchResultsFeature:
        return static_cast<LomiriPluginInterface>(&globalDrawerSearch);
    default:
        return nullptr;
    }
}

// Initiating a search for "query"
void lomiri_plugin_drawersearch_search(LomiriPluginInterface interface, const char* query)
{
    const auto drawer_search = static_cast<LomiriPluginDrawerSearch*>(interface);
    if (!drawer_search)
        return;

    drawer_search->search(std::string(query));
}

// Get the DrawerSearchResult of the current position.
LomiriDrawerSearchResult lomiri_plugin_drawersearch_get(LomiriPluginInterface interface)
{
    const auto drawer_search = static_cast<LomiriPluginDrawerSearch*>(interface);
    if (!drawer_search)
        return nullptr;

    const auto result = drawer_search->get();
    return static_cast<LomiriDrawerSearchResult>(result);
}

// Get the DrawerSearchResult of the next position.
LomiriDrawerSearchResult lomiri_plugin_drawersearch_next(LomiriPluginInterface interface)
{
    const auto drawer_search = static_cast<LomiriPluginDrawerSearch*>(interface);
    if (!drawer_search)
        return nullptr;

    const auto result = drawer_search->next();
    return static_cast<LomiriDrawerSearchResult>(result);
}

// Returns the title of the DrawerSearchResult.
const char* lomiri_plugin_drawersearch_result_title(LomiriDrawerSearchResult result)
{
    const auto res = static_cast<LomiriPluginDrawerSearchResult*>(result);
    if (!res)
        return nullptr;

    return res->title.c_str();
}

// Returns an optional icon URL of the DrawerSearchResult.
const char* lomiri_plugin_drawersearch_result_sourceicon(LomiriDrawerSearchResult result)
{
    const auto res = static_cast<LomiriPluginDrawerSearchResult*>(result);
    if (!res)
        return nullptr;

    return res->sourceIcon.c_str();
}

// TODO: Missing native interfaces exported into the WASM runtime.
//       Required for updating the model from inside the plugin,
//       or open URLs returned by the search result.

void lomiri_plugin_drawersearch_result_open(LomiriDrawerSearchResult result)
{
}

} // extern "C"
