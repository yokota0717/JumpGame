/**
* @file SceneManager.hpp
* @brief �V�[���Ǘ����s���N���X���`����
* @author yokota0717
* @date 2018.10.26
*/

#pragma once
#include <iostream>
#include <stack>
#include "SceneInfo.hpp"
#include "Scene/Title.h"
#include "Scene/Stage1.h"
#include "../Utility/Error.hpp"
#include "../Utility/Utility.hpp"

namespace Scene {
	/**
	* @brief �V�[���Ǘ����s��
	*/
	class SceneManager : public IOnSceneChangedListener {
	private:
		//! �V�[���̃X�^�b�N�A������炱���ɐς�
		std::stack<AbstractScene*> sceneStack_;
	public:
		SceneManager() {
			Parameter param;
			sceneStack_.push(new Title(this, param));		//�ŏ��̃V�[����ݒ�(�^�C�g��)
		}
		~SceneManager() {
			while (!sceneStack_.empty()) {
				deleteScene();
			}
		}
		void onSceneChanged(const SceneName& scene, [[maybe_unused]]const Parameter* param, const StackPopFlag stackPopFlag) override {
			switch (stackPopFlag) {
			case StackPopFlag::NON:
				DOUT << "pre-scene is remainning"<<std::endl;
				break;
			case StackPopFlag::POP:
				DOUT << "poped scene-stack" << std::endl;
				deleteScene();
				break;
			case StackPopFlag::ALL_CLEAR:
				DOUT << "poped scene-stack all" << std::endl;
				stackClear();
			}
			switch (scene) {
			case Scene::SceneName::TITLE:
				DOUT << "Title created" << std::endl;
				sceneStack_.push(new Title(this, *param));
				break;
			case Scene::SceneName::GAME:
				DOUT << "Game created" << std::endl;
				sceneStack_.push(new Stage1(this, *param));
				break;
			case Scene::SceneName::BACK_SCENE:
				DOUT << "back pre scene" << std::endl;
				break;
			case Scene::SceneName::NON:
				std::cout << "no scene" << std::endl;
			default:
				ERR("non-defined scene is called");
				break;
			}
		}

		/**
		* @brief �X�^�b�N����Ă���V�[�������ׂď�������
		*/
		void stackClear() {
			while (!sceneStack_.empty()) {
				sceneStack_.pop();
			}
		}
		/**
		* @brief �X�^�b�N�̃g�b�v�ɂ���V�[���̃��������������
		*/
		void deleteScene() {
			delete sceneStack_.top();
			sceneStack_.top() = nullptr;
			sceneStack_.pop();
		}
		/**
		* @brief �X�^�b�N�̃g�b�v�ɂ���V�[�����X�V����
		*/
		void updateTopScene() {
			sceneStack_.top()->update();
		}
		/**
		* @brief �X�^�b�N�̃g�b�v�ɂ���V�[���̕`�������
		*/
		void renderTopScene() {
			sceneStack_.top()->render();
		}
	};
}