// Fill out your copyright notice in the Description page of Project Settings.


#include "UseCases/SelectorPoseSearchDatabaseComponent/UpdateNodePoseSearchDatabaseUseCase.h"
#include "Components/MotionMatchHelpers/SelectorPoseSearchDatabaseComponent.h"

void UUpdateNodePoseSearchDatabaseUseCase::Handle
(
	const TScriptInterface<ISelectorPoseSearchDatabaseInterface>& Component
)
{
	Component->LoadDatabaseAsset("C:\\Users\\rafae\\Documents\\Unreal Projects\\NewProject\\Source\\NewProject\\Entities\\PoseSearchDatabases");
}
