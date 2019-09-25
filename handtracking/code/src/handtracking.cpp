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

#include <handtracking.h>
#include <lumin/node/RootNode.h>
#include <lumin/ui/Cursor.h>
#include <ml_logging.h>
#include <scenes.h>
#include <PrismSceneManager.h>
#include <lumin/event/GestureInputEventData.h>


using namespace lumin;
using namespace lumin::input;

namespace {
	//consts for the rotation axis (y), the rotation angle, and the rotation interval
	const glm::vec3 y(0.0f, 1.0f, 0.0f);
	const float rotate = 0.3f;
	const float duration = 0.0f;
	//vector that will contain the position of the hand's finger tip
	glm::vec3 handPos;
	//bool variable that will turn true if the earth rotates, false otherwise
	bool OK = false;
	//bool variable that will turn true if the Finger gesture is recognized, false otherwise
	bool Finger = false;

	//Nodes to link to the 3D models
	Node* modelEarth;
	Node* modelCube;
	TransformNode* transformNodeEarth;
	TransformNode* transformNodeCube;
}



handtracking::handtracking() {
	ML_LOG(Debug, "handtracking Constructor.");

	// Place your constructor implementation here.
}

handtracking::~handtracking() {
	ML_LOG(Debug, "handtracking Destructor.");

	// Place your destructor implementation here.
}

const glm::vec3 handtracking::getInitialPrismSize() const {
	return glm::vec3(5.0f, 5.0f, 5.0f);
}

void handtracking::createInitialPrism() {
	prism_ = requestNewPrism(getInitialPrismSize());
	if (!prism_) {
		ML_LOG(Error, "handtracking Error creating default prism.");
		abort();
	}
	prismSceneManager_ = new PrismSceneManager(prism_);
}

int handtracking::init() {

	ML_LOG(Debug, "handtracking Initializing.");

	createInitialPrism();
	lumin::ui::Cursor::SetEnabled(prism_, false);
	spawnInitialScenes();

	uint32_t handGestureFlags =
		uint32_t(HandGestureFlags::kHandOk) |
		uint32_t(HandGestureFlags::kHandFinger);
	prism_->startTrackHandGesture(handGestureFlags);

	prism_->setHandGestureFilterConfidenceLevel(0.9f);

	//Find the model nodes in the scene and cast them to a TransformNode
	modelCube = prism_->findNode("cube", prism_->getRootNode());
	transformNodeCube = static_cast<lumin::TransformNode*>(modelCube);
	modelEarth = prism_->findNode("earth", prism_->getRootNode());
	transformNodeEarth = static_cast<lumin::TransformNode*>(modelEarth);


	return 0;
}

int handtracking::deInit() {
	ML_LOG(Debug, "handtracking Deinitializing.");

	// Place your deinitialization here.

	return 0;
}


void handtracking::spawnInitialScenes() {

	// Iterate over all the exported scenes
	for (auto& exportedSceneEntry : scenes::externalScenes) {

		// If this scene was marked to be instanced at app initialization, do it
		const SceneDescriptor &sd = exportedSceneEntry.second;
		if (sd.getInitiallySpawned()) {
			lumin::Node* const spawnedRoot = prismSceneManager_->spawn(sd);
			if (spawnedRoot) {
				if (!prism_->getRootNode()->addChild(spawnedRoot)) {
					ML_LOG(Error, "handtracking Failed to add spawnedRoot to the prism root node");
					abort();
				}
			}
		}
	}
}

bool handtracking::updateLoop(float fDelta) {
	if (OK) {
		//rotate the earth
		transformNodeEarth->rotateBy(y, rotate * fDelta, duration);
	}
	if (Finger) {
		glm::mat4 prism_inverse_matrix = glm::inverse(prism_->getTransform());
		handPos = prism_inverse_matrix * glm::vec4(handPos, 1.0f);
		transformNodeCube->setLocalPosition(handPos);
	}
	return true;
}

bool handtracking::eventListener(ServerEvent* anEvent) {

	if (anEvent->isInputEventType()) {
		ServerEventTypeValue serverEventType = anEvent->getServerEventTypeValue();
		if (serverEventType == GestureInputEventData::GetServerEventTypeValue()) {
			const GestureInputEventData* gestureEventData = static_cast<GestureInputEventData*>(anEvent);
			const GestureType gestureType = gestureEventData->getGesture();
			if (gestureType == GestureType::HAND_OK) {
				OK = true;
				Finger = false;
			}
			else if (gestureType == GestureType::HAND_FINGER) {
				Finger = true;
				OK = false;
				gestureEventData->getHandGestureKeypoint(HandGestureKeypointName::INDEX_FINGER_TIP, handPos.x, handPos.y, handPos.z);
			}
		}
	}
	return false;
}