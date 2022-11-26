#pragma once

#ifndef HZN_ASSETMANAGER_H
#define HZN_ASSETMANAGER_H

#include "HorizonEngine.h"
#include "pch.h"
#include <Renderer/Texture.h>
#include <Renderer/Sprite.h>
#include <Audio/AudioSource.h>



namespace Hzn
{
	class AudioSource;

	struct SpriteSheetIdentifier
	{
		std::shared_ptr<Texture2D> spriteSheet;
		glm::vec2 cellSize;
	};

	class AssetManager
	{
	public:
		// Texture storage
		static std::map<std::string, std::pair<std::shared_ptr<Texture2D>, glm::vec2>> textureStorage;
		//Audio storage
		static std::map<std::string, std::shared_ptr<AudioSource>> audioStorage;
		//SpriteStorage
		static std::map<std::string, std::shared_ptr<Sprite2D>> spriteStorage;

		static std::map<std::string, std::string> spriteFormat;


		static void init(const std::filesystem::path& directoryPath);
		static void destroy();
		static void loadAudio(std::string path);

		static void loadSpriteSheet(std::string path, const glm::vec2& cellSize)
		{
			auto texture = Texture2D::create(path);
			textureStorage[path] = { texture, cellSize };
			auto width = texture->getWidth();
			auto height = texture->getHeight();
			// (0, 0) to (width, height).
			// i * cellsize / width, j * cellsize / height
			for (int i = 0; i < width / cellSize.x; ++i)
			{
				for(int j = 0; j < height / cellSize.y; ++j)
				{
					std::string sheetPathPos = path + "-;" + std::to_string(i) + ";" + std::to_string(j);
					spriteStorage[sheetPathPos] = Sprite2D::create(texture, { i, j }, cellSize);
				}
			}

		}

		static void loadTexture(std::string path)
		{
			auto texture = Texture2D::create(path);
			textureStorage[path] = { texture, {texture->getWidth(), texture->getHeight()}};
		}

		/*static void loadSprite(std::string sheetPath, const glm::vec2& pos)
		{
			std::string sheetPathPos = sheetPath + "-;" + std::to_string(pos.x) + ";" + std::to_string(pos.y);
			spriteStorage[sheetPathPos] = Sprite2D::create(spriteSheetStorage.at(sheetPath).spriteSheet, { pos.x, pos.y }, { textureStorage.at(sheetPath).cellSize.x, spriteSheetStorage.at(sheetPath).cellSize.y });
		}*/

		static std::shared_ptr<Texture2D> getTexture(std::string texturePath)
		{
			if (textureStorage.find(texturePath) == textureStorage.end())
			{
				loadTexture(texturePath);
			}
			return textureStorage.at(texturePath).first;
		}


		static std::shared_ptr<Sprite2D> getSprite(std::string sheetPath, const glm::vec2& pos)
		{
			std::string sheetPathPos = sheetPath + "-;" + std::to_string((int)pos.x) + ";" + std::to_string((int)pos.y);

			if (spriteStorage.find(sheetPathPos) == spriteStorage.end()) return nullptr;

			return spriteStorage.at(sheetPathPos);
		}

		static std::shared_ptr<AudioSource> getAudio(std::string audioPath)
		{
			if (audioStorage.find(audioPath) == audioStorage.end())
			{
				loadAudio(audioPath);
			}

			return audioStorage.at(audioPath);
		}

	private:
	};

}


#endif