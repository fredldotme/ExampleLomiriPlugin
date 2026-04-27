#include <tideplugin.h>

#include <string>
#include <iostream>
#include <vector>

extern "C" {

// Basic interface as required by plugins
class LomiriPluginHostInterface {};

// Search results in the drawer
struct LomiriPluginDrawerSearchResult {
    std::string title;
    std::string iconSource;
};

// Implementing the "search results" interface
class LomiriPluginDrawerSearch : public LomiriPluginHostInterface {
public:
    void search(const std::string& contents);
    LomiriPluginDrawerSearchResult* find();
    LomiriPluginDrawerSearchResult* next();
private:
    std::vector<LomiriPluginDrawerSearchResult> searchResults;
    std::vector<LomiriPluginDrawerSearchResult>::iterator cit;
};

// Only one instantiation
static LomiriPluginDrawerSearch globalDrawerSearch;

// Initiate a search based on the query parameter "contents"
bool LomiriPluginDrawerSearch::search(const std::string& contents)
{
#if 0
    completionResults.clear();
    for (int i = 0; i < 3; i++) {
        TidePluginAutoCompleterResult res;
        res.kind = AutoCompletorKind::Variable;
        res.type = "int";
        res.identifier = "PluginWorking_" + std::to_string(i);
        res.detail = "ExamplePlugin";
        completionResults.push_back(res);
    }
#endif

    cit = searchResults.begin();

    return true;
}

// Get the DrawerSearchResult at the current position.
LomiriPluginDrawerSearchResult* LomiriPluginDrawerSearch::find()
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

// The set of features the plugin implements.
LomiriPluginFeatures lomiri_plugin_features()
{
    return LomiriPluginFeatures::LomiriDrawerResultsFeature;
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
    case LomiriPluginFeatures::LomiriDrawerResultsFeature:
        return static_cast<LomiriPluginInterface>(&globalDrawerSearch);
    default:
        return nullptr;
    }
}

// Initiating a search for "contents"
void lomiri_plugin_drawersearch_search(LomiriPluginInterface interface, const char* contents)
{
    auto drawer_search = static_cast<LomiriPluginDrawerSearch*>(interface);
    if (!drawer_search)
        return;

    const auto result = drawer_search->search(std::string(contents));
    std::cout << "Result: " << result;
}

// Get the DrawerSearchResult of the current position.
LomiriDrawerSearchResult lomiri_plugin_drawersearch_find(LomiriPluginInterface interface,
                                                         const char* hint)
{
    auto drawer_search = static_cast<LomiriPluginDrawerSearch*>(interface);
    if (!drawer_search)
        return nullptr;

    const auto result = drawer_search->find();
    return static_cast<LomiriDrawerSearchResult>(result);
}

// Get the DrawerSearchResult of the next position.
LomiriDrawerSearchResult lomiri_plugin_drawersearch_next(LomiriPluginInterface interface)
{
    if (!interface)
        return nullptr;

    const auto drawer_search = static_cast<LomiriPluginDrawerSearch*>(interface);
    return static_cast<LomiriDrawerSearchResult>(drawer_search->next());
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