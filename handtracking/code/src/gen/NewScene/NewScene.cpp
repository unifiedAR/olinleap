// -- WARNING -- WARNING -- WARNING -- WARNING -- WARNING -- WARNING --
//
// THE CONTENTS OF THIS FILE IS GENERATED BY CODE AND
// ANY MODIFICATIONS WILL BE OVERWRITTEN
//
// -- WARNING -- WARNING -- WARNING -- WARNING -- WARNING -- WARNING --

// %BANNER_BEGIN%
// ---------------------------------------------------------------------
// %COPYRIGHT_BEGIN%
//
// Copyright (c) 2018 Magic Leap, Inc. All Rights Reserved.
// Use of this file is governed by the Creator Agreement, located
// here: https://id.magicleap.com/creator-terms
//
// %COPYRIGHT_END%
// ---------------------------------------------------------------------
// %BANNER_END%

// %SRC_VERSION%: 1

#include <SceneDescriptor.h>
#include <SpawnedSceneBase.h>
#include <NewScene/NewScene.h>

namespace scenes {

  namespace NewScene {

    SpawnedScene::SpawnedScene(const SceneDescriptor& sceneDescriptor, lumin::Node* root)
    : SpawnedSceneBase(sceneDescriptor, root) {
      earth = lumin::ModelNode::CastFrom(root->findChild(externalNodes::earth));
      cube = lumin::ModelNode::CastFrom(root->findChild(externalNodes::cube));
    }

    SpawnedScene::~SpawnedScene() {
    }

    SpawnedSceneBase* createSpawnedScene(const SceneDescriptor& sceneDescriptor, lumin::Node* root) {
      using namespace externalNodes;
      SpawnedScene* spawnedScene = new SpawnedScene(sceneDescriptor, root);
      return spawnedScene;
    }

    class Handlers : public SpawnedSceneHandlers
    {
    public:
      Handlers(SpawnedScene& ss);

    private:

      struct earthHandlers {
        earthHandlers(SpawnedScene& ss);
      };
      earthHandlers earthHandlers_;
      struct cubeHandlers {
        cubeHandlers(SpawnedScene& ss);
      };
      cubeHandlers cubeHandlers_;
    };
    
    Handlers::earthHandlers::earthHandlers(SpawnedScene& ss)
      {
    }
    Handlers::cubeHandlers::cubeHandlers(SpawnedScene& ss)
      {
    }
    
    Handlers::Handlers(SpawnedScene& ss)
    : SpawnedSceneHandlers(ss),
      earthHandlers_(ss),
      cubeHandlers_(ss)
      {
    }
    
    SpawnedSceneHandlers* createSpawnedSceneHandlers(SpawnedSceneBase& ssb) {
      return new Handlers(static_cast<SpawnedScene&>(ssb));
    }
  }
}
