#pragma once

#include "HorizonEngine.h"

#ifndef HZN_MODALS_H
#define HZN_MODALS_H




class Modals {
	friend class EditorLayer;
	friend class ContentBrowser;
private:
	static void openProject();
	static std::string projectRootFolder;
	static std::shared_ptr<Hzn::Texture> folderIcon;
	static std::shared_ptr<Hzn::Texture> fileIcon;
	static std::shared_ptr<Hzn::Texture> previousIcon;
	static std::shared_ptr<Hzn::Texture> nextIcon;
	static std::filesystem::path m_CurrentDirectory;
	static std::string currentScenePath;
	static char projectNameBuffer[512];
	static char directoryPathBuffer[1024];
	static char sceneNameBuffer[256];
	static bool request_NewProject;
	static bool request_NewScene;
	static bool canCreateProject;

public:
	static void getCenterWindow();
	static bool getNewProJPopup();
	static bool getNewScenePopup();
};

#endif // !HZN_MODALS_H