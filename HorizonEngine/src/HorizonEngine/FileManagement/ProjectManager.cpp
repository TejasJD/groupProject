#include "pch.h"
#include "ProjectManager.h"

#include "HorizonEngine/SceneManagement/SceneManager.h"

namespace Hzn
{
	std::shared_ptr<Project> ProjectManager::s_Project = nullptr;

	std::shared_ptr<Project> ProjectManager::create(const std::string& name, const std::filesystem::path& directoryPath)
	{
		if(s_Project)
		{
			save();
		}
		s_Project = std::make_shared<Project>(name, directoryPath);
		return s_Project;
	}

	void ProjectManager::newScene(const std::string& name)
	{
		if(!s_Project)
		{
			throw std::runtime_error("trying to create new scene outside the project!");
		}
		std::filesystem::path projectDir = s_Project->m_Path.parent_path();
		std::filesystem::path sceneDir = projectDir.string() + "\\scenes";

		// create a scenes directory if it doesn't exist.
		if(!std::filesystem::exists(sceneDir))
		{
			std::filesystem::create_directory(sceneDir);
		}

		// create a scene file.
		std::filesystem::path sceneFilePath = sceneDir.string() + "\\" + name + ".scene";

		s_Project->m_Scene = SceneManager::create(sceneFilePath);
	}

	void ProjectManager::openScene(const std::string& name)
	{
		if (!s_Project)
		{
			throw std::runtime_error("trying to create new scene outside the project!");
		}
		std::filesystem::path projectDir = s_Project->m_Path.parent_path();
		std::filesystem::path sceneDir = projectDir.string() + "\\scenes";

		HZN_CORE_ASSERT(std::filesystem::exists(sceneDir), "no scenes directory!");

		std::filesystem::path sceneFile = sceneDir.string() + "\\" + name + ".scene";

		s_Project->m_Scene = SceneManager::open(sceneFile);
	}

	std::shared_ptr<Project> ProjectManager::open(const std::filesystem::path& projectFilePath)
	{
		if(s_Project)
		{
			close();
		}
		return s_Project = std::make_shared<Project>(projectFilePath);
	}

	void ProjectManager::save()
	{
		if(s_Project)
		{
			std::filesystem::path projectFile = s_Project->m_Path;
			std::ofstream os(projectFile, std::ios::binary);
			os << "ActiveScene" << " " << ":" << " " << s_Project->m_Scene->m_Path.string();
			os.close();

			SceneManager::save();
		}
	}

	void ProjectManager::close()
	{
		save();
			SceneManager::close();
		s_Project.reset();
	}
}