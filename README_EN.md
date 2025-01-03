# Basic clean architecture UE-5.x
This project is a UE-5 C++ application with a basic principle of a clean architecture-based structure, with separation of components and their responsibilities using use cases.

In the Example structure below we are creating a basic movement component for our Character, separating the responsibilities into layers and decoupling the component, which can be reused in any other part of the system through use cases.

[Read the article for more details](https://medium.com/@rafaelvaloto/implementação-básica-clean-architecture-na-ue-5-com-c-ba690104fa24)

## Project Structure

```
└───NewProject
    │   NewProject.Build.cs
    │   NewProject.cpp
    │   NewProject.h
    │   
    ├───Commons
    │   ├───Helpers
    │   │       EntitiesAssetsLoadHelper.h
    │   │       
    │   ├───Providers
    │   │   └───Entities
    │   │           EntityFactoryRegistry.h
    │   │           
    │   └───Rules
    │       │   FRuleManager.h
    │       │   
    │       └───SelectorPoseSearchDatabaseRules
    │               FActorIdleRule.h
    │               FActorWalkStartRule.h
    │               FActorWalkStopRule.h
    │
    ├───Entities
    │   └───PoseSearchDatabases
    │           PSD_DenseStandIdlesEntity.h
    │           PSD_SparseStandWalkStartsEntity.h
    │           PSD_SparseStandWalkStopsEntity.h
    │
    ├───Enums
    │   ├───CharacterStates
    │   │       PlayerCharacterStateEnum.h
    │   │
    │   └───PoseSearchDatabaseModeStates
    │           PoseSearchDatabaseModeStateEnum.h
    │           SelectorDatabaseValidateRuleModeEnum.h
    │
    ├───Interfaces
    │   ├───CharacterComponents
    │   │       InputCharacterInterface.h
    │   │       UpdateAttributesCharacterComponentInterface.h
    │   │       UpdateStateCharacterComponentInterface.h
    │   │       UpdateTrajectoryCharacterComponentInterface.h
    │   │
    │   ├───Helpers
    │   │       EntityAsset.h
    │   │       RuleBase.h
    │   │
    │   ├───MotionMatchHelpersComponents
    │   │       SelectorPoseSearchDatabaseInterface.h
    │   │
    │   └───StaticMeshActorComponents
    │           SplineDrawComponentInterface.h
    │
    ├───Private
    │   ├───Application
    │   │   ├───BallStaticMeshActor
    │   │   │       BallStaticMeshActor.cpp
    │   │   │
    │   │   ├───PlayerCharacter
    │   │   │       PlayerCharacter.cpp
    │   │   │
    │   │   └───PlayerController
    │   │           JogPlayerController.cpp
    │   │
    │   ├───Components
    │   │   ├───Character
    │   │   │       InputCharacterComponent.cpp
    │   │   │       UpdateAttributesCharacterComponent.cpp
    │   │   │       UpdateStateCharacterComponent.cpp
    │   │   │       UpdateTrajectoryCharacterComponent.cpp
    │   │   │
    │   │   ├───MotionMatchHelpers
    │   │   │       SelectorPoseSearchDatabaseComponent.cpp
    │   │   │
    │   │   └───StaticMeshActor
    │   │           SplineDrawComponent.cpp
    │   │
    │   └───UseCases
    │       ├───Character
    │       ├───CharacterTrajectoryComponent
    │       │       CharacterTrajectoryComponentUseCase.cpp
    │       │
    │       ├───InputCharacterComponent
    │       │       MovementCharacterUseCase.cpp
    │       │
    │       ├───SelectorPoseSearchDatabaseComponent
    │       │       UpdateNodePoseSearchDatabaseUseCase.cpp
    │       │       UpdatePoseSearchDatabaseWithDescelerationUseCase.cpp
    │       │
    │       ├───SplineDrawComponent
    │       │       TrajectoryRuntimeDrawUseCase.cpp
    │       │
    │       ├───UpdateBaseAttributesComponent
    │       │       UpdateAttributesCharacterComponentUseCase.cpp
    │       │
    │       └───UpdateStateCharacterComponent
    │               UpdateStateCharacterComponentUseCase.cpp
    │
    └───Public
        ├───Application
        │   ├───BallStaticMeshActor
        │   │       BallStaticMeshActor.h
        │   │
        │   ├───GameInstance
        │   │       PlayerGameInstance.h
        │   │
        │   ├───PlayerCharacter
        │   │       PlayerCharacter.h
        │   │
        │   └───PlayerController
        │           JogPlayerController.h
        │
        ├───Components
        │   ├───Character
        │   │       InputCharacterComponent.h
        │   │       UpdateAttributesCharacterComponent.h
        │   │       UpdateStateCharacterComponent.h
        │   │       UpdateTrajectoryCharacterComponent.h
        │   │
        │   ├───MotionMatchHelpers
        │   │       SelectorPoseSearchDatabaseComponent.h
        │   │
        │   └───StaticMeshActor
        │           SplineDrawComponent.h
        │
        └───UseCases
            ├───CharacterTrajectoryComponent
            │       CharacterTrajectoryComponentUseCase.h
            │
            ├───InputCharacterComponent
            │       MovementCharacterUseCase.h
            │
            ├───SelectorPoseSearchDatabaseComponent
            │       UpdateNodePoseSearchDatabaseUseCase.h
            │       UpdatePoseSearchDatabaseWithDescelerationUseCase.h
            │
            ├───SplineDrawComponent
            │       TrajectoryRuntimeDrawUseCase.h
            │
            ├───UpdateAttributesCharacterComponent
            │       UpdateAttributesCharacterComponentUseCase.h
            │
            └───UpdateStateCharacterComponent
                    UpdateStateCharacterComponentUseCase.h


```