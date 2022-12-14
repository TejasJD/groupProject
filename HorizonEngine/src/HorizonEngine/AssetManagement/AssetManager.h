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

	/// <summary>
	/// A struct for pointing to a sprite sheet of type 'Texture 2D'
	/// and GLM's 2D vector class
	/// </summary>
	struct SpriteSheetIdentifier
	{
		std::shared_ptr<Texture2D> spriteSheet;
		glm::vec2 cellSize;
	};

	/// <summary>
	/// Asset manager class 
	/// </summary>
	class AssetManager
	{
	public:
		//! Texture storage
		static std::map<std::string, std::pair<std::shared_ptr<Texture2D>, glm::vec2>> textureStorage;
		//! Audio storage
		static std::map<std::string, std::shared_ptr<AudioSource>> audioStorage;
		//! SpriteStorage
		static std::map<std::string, std::shared_ptr<Sprite2D>> spriteStorage;
		//! Sprite formatting
		static std::map<std::string, std::string> spriteFormat;


		static bool init(const std::filesystem::path& directoryPath);
		static void destroy();
		static void loadAudio(std::string path);

		/// <summary>
		/// Loads spritesheet
		/// </summary>
		/// <param name="path"></param>
		/// <param name="cellSize"></param>
		static void loadSpriteSheet(std::filesystem::path path, const glm::vec2& cellSize)
		{
			auto texture = Texture2D::create(path.string());
			textureStorage[path.filename().string()] = {texture, cellSize};
			auto width = texture->getWidth();
			auto height = texture->getHeight();
			// (0, 0) to (width, height).
			// i * cellsize / width, j * cellsize / height
			for (int i = 0; i < width / cellSize.x; ++i)
			{
				for(int j = 0; j < height / cellSize.y; ++j)
				{
					std::string sheetPathPos = path.filename().string() + "-;" + std::to_string(i) + ";" + std::to_string(j);
					spriteStorage[sheetPathPos] = Sprite2D::create(texture, { i, j }, cellSize);
				}
			}

		}

		static void loadTexture(std::filesystem::path path)
		{
			auto texture = Texture2D::create(path.string());
			textureStorage[path.filename().string()] = {texture, {texture->getWidth(), texture->getHeight()}};
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