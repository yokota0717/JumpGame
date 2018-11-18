/**
* @file GameManager.h
* @brief �Q�[���N���X���`����
*/

#pragma once
#include "../System/Input/Input.h"
#include "../System/ResourceManager/ResourceManager.h"
#include "../Scene/SceneManager.hpp"
#include "../System/TaskSystem/TaskSystem.h"
#include "../System/FPS/FPS.hpp"
#include "../System/Camera/Camera.h"

/**
* @brief �Q�[���Ǘ��N���X
*/
class GameManager final {
	//! �f�o�b�O���[�h�ؑ֗p
	bool debug_;
	//! �V�[���Ǘ��p
	Scene::SceneManager* sceneManager_;
	//! FPS�Œ�
	FPS fps_;
public:
	//! �J����
	Camera2D camera_;

	GameManager();
	~GameManager();
	void init();
	void fin();

	//!���͊֘A
	Keyboard kb;
	Mouse mouse;
	GPad pad;

	/**
	* @brief ���C�����[�v
	*/
	void mainLoop();

	/**
	* @brief ���݃f�o�b�O���[�h���N��������Ԃ�
	* @return bool �f�o�b�O���[�h�N�������ǂ���
	*/
	bool debugMode();
};

//! �Q�[���Ǘ��I�u�W�F�N�g
extern GameManager* game;