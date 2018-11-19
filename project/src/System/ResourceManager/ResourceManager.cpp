/**
* @file ResourceManager.cpp
* @brief 画像データのハンドル管理クラスの処理を記述する
* @author yokota0717
* @date 2018.10.27
* @param history
- 2018.10.29 yokota0717
-# サウンドの追加
-# ResourceManager追加に伴う変更
-# DXライブラリのハンドル解放処理を追加
*/

#include "ResourceManager.h"

//---------------------------------------------------------------------------------------------

void ResourceManager::GraphFactory::initLoad() {
	//★★★アプリケーション開始時に読み込みたい画像はここでロードする★★★
	//int handle = LoadGraph("./data/image/player.png");
	ResourceManager::getGraphFac().getGraph("sky.bmp");
	//int handle = LoadGraph("./data/image/sky.bmp");
	//if (handle != -1) {
	//	singlePool_.insert(std::make_pair("./data/image/sky.bmp", handle));
	//}
}
void ResourceManager::SoundFactory::initLoad() {
	//★★★アプリケーション開始時に読み込みたいサウンドはここでロードする★★★
}

//---------------------------------------------------------------------------------------------

ResourceManager::GraphFactory::GraphFactory()
	:
	path("./data/image/")
{}

ResourceManager::GraphFactory::~GraphFactory() {
	//for (auto it = divPool_.begin(); it != divPool_.end(); ++it) {
	//	if (it->second) {
	//		//delete it->second;
	//		free(it->second);
	//	}
	//	it->second = nullptr;
	//}
	divPool_.clear();
	InitGraph();
}

int ResourceManager::GraphFactory::createGraph(const std::string& fileName) {
	int handle = LoadGraph(fileName.c_str());
	return handle;
}

int* ResourceManager::GraphFactory::createGraphDiv(const std::string& fileName, const int allNum, const int xNum, const int yNum, const int xSize, const int ySize) {
	//int* handle = (int*)malloc(sizeof(int)*allNum);
	//if (handle == nullptr) { return nullptr; }
	
	
	/**
	* @note DivGraphの解放処理に困っている
	*/

	std::vector<int> handle;
	LoadDivGraph(fileName.c_str(), allNum, xNum, yNum, xSize, ySize, handle);
	return handle;
	//free(handle);
}

int ResourceManager::GraphFactory::getGraph(const std::string& fileName) {
	std::string file = path + fileName;
	auto it = singlePool_.find(file);
	if (it != singlePool_.end()) {
		return it->second;
	}
	int newGraph = createGraph(file);
	if (newGraph != -1) {
		singlePool_.insert(std::make_pair(fileName, newGraph));
	}
	return newGraph;
}

int* ResourceManager::GraphFactory::getGraphDiv(const std::string& fileName, const int allNum, const int xNum, const int yNum, const int xSize, const int ySize) {
	std::string file = path + fileName;
	auto it = divPool_.find(file);
	if (it != divPool_.end()) {
		return it->second;
	}
	int* newGraph = createGraphDiv(file.c_str(), allNum, xNum, yNum, xSize, ySize);
	if (*newGraph != -1) {
		divPool_.insert(std::make_pair(fileName, newGraph));
	}
	return newGraph;
}

//---------------------------------------------------------------------------------------------

ResourceManager::SoundFactory::SoundFactory()
	:
	path("./data/sound/")
{}	

ResourceManager::SoundFactory::~SoundFactory()
{
	InitSoundMem();
}

int ResourceManager::SoundFactory::loadSound(std::string& fileName) {
	int handle = LoadSoundMem(fileName.c_str());
	return handle;
}

int ResourceManager::SoundFactory::loadSoundAsync(std::string& fileName) {
	SetUseASyncLoadFlag(true);	//非同期読み込みフラグをtrueに
	int handle = LoadSoundMem(fileName.c_str());
	SetUseASyncLoadFlag(false);
	return 1;
}

int ResourceManager::SoundFactory::getSound(const std::string& fileName) {
	std::string file = path + fileName;
	auto it = pool_.find(file);
	if(it != pool_.end()){
		return it->second;
	}
	int newSound = loadSound(file);
	if (newSound != -1) {	//読み込みに失敗していなかったらコンテナに追加
		pool_.insert(std::make_pair(fileName, newSound));
	}
	return newSound;
}

//---------------------------------------------------------------------------------------------

ResourceManager::ResourceManager() {}

ResourceManager::~ResourceManager() {}

void ResourceManager::init() {
	static std::unique_ptr<GraphFactory> graphfac_ = std::make_unique<GraphFactory>();
	static std::unique_ptr<SoundFactory> soundfac_ = std::make_unique<SoundFactory>();
	graphfac_->initLoad();
	soundfac_->initLoad();
}

ResourceManager::GraphFactory& ResourceManager::getGraphFac() {
	static std::unique_ptr<GraphFactory> graphfac_ = std::make_unique<GraphFactory>();
	return *graphfac_;
}

ResourceManager::SoundFactory& ResourceManager::getSoundFac() {
	static std::unique_ptr<SoundFactory> soundfac_ = std::make_unique<SoundFactory>();
	return *soundfac_;
}
