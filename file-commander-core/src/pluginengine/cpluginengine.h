#ifndef CPLUGINENGINE_H
#define CPLUGINENGINE_H

#include "cpanel.h"
#include "plugininterface/cfilecommanderplugin.h"

#include <vector>
#include <memory>


class CFileCommanderViewerPlugin;
class CPluginWindow;
class QLibrary;

class CPluginEngine : public PanelContentsChangedListener
{
public:
	static CPluginEngine& get();

	void loadPlugins();
	std::vector<QString> activePluginNames();

	void destroyAllPluginWindows();

	// CPanel observers
	void panelContentsChanged(Panel p, FileListRefreshCause operation) override;
	void itemDiscoveryInProgress(Panel p, qulonglong itemHash, size_t progress, const QString& currentDir) override;

	void selectionChanged(Panel p, const std::vector<qulonglong>& selectedItemsHashes);
	void currentItemChanged(Panel p, qulonglong currentItemHash);
	void currentPanelChanged(Panel p);

// Operations
	void viewCurrentFile();
	CPluginWindow* createViewerWindowForCurrentFile();

private:
	CPluginEngine() = default;

	CPluginEngine& operator=(const CPluginEngine& other) = delete;
	CPluginEngine(const CPluginEngine& other) = delete;
	
private:
	static PanelPosition pluginPanelEnumFromCorePanelEnum(Panel p);

	CFileCommanderViewerPlugin * viewerForCurrentFile();

private:
	std::vector<std::pair<std::shared_ptr<CFileCommanderPlugin>, std::shared_ptr<QLibrary>>> _plugins;
	std::vector<CPluginWindow*> _activeWindows;
};

#endif // CPLUGINENGINE_H
