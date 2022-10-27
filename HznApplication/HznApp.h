#pragma once

#ifndef HZNAPP_HZNAPP_H
#define HZNAPP_HZNAPP_H
// ********** Edior Layer **********

class EditorLayer : public Hzn::Layer
{
private:
	Hzn::Scene* openScene;
	std::string projectRootFolder;
	std::vector<std::shared_ptr<Hzn::TreeNode<std::string>>> nodes;
	std::string contextObject = "";
	bool openContext = false;
	std::shared_ptr<Hzn::GameObject> copiedGameObject;
public:
	EditorLayer(const std::string& name = "Editor Layer");

	virtual void onAttach() override;

	virtual void onDetach() override;

	virtual void onRenderImgui() override;

	virtual void onEvent(Hzn::Event& event) override;

private:
	void setupDockSpace(bool* pOpen);
	void dockWidgets(ImGuiID dockspace_id);
	void drawMenuBar(bool* pOpen);
	void drawScene();
	void drawObjectBehaviour();
	void drawHierarchy();
	void drawProjectExplorer();
	void drawConsole();
	bool ButtonCenteredOnLine(const char* label, float alignment = 0.5f);

	void drawHierarchyNode(std::shared_ptr<Hzn::TreeNode<std::string>> node);
};

class HznApp : public Hzn::App
{
public:
	HznApp()
	{
		Hzn::Renderer2D::init();
	}
	~HznApp()
	{
		Hzn::Renderer2D::destroy();
	}
};

#endif // !HZNAPP_HZNAPP_H
