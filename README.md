**README_PT.md:**
[Leia o README em Português](README_PT.md)
# Basic clean architecture UE-5.x
This project is a UE-5 C++ application with a basic principle of a clean architecture-based structure, with separation of components and their responsibilities using use cases.

In the Example structure below we are creating a basic movement component for our Character, separating the responsibilities into layers and decoupling the component, which can be reused in any other part of the system through use cases.
## Project Structure

```
Source
└───Project
    ├───Interfaces
    │   ├───CharacterComponents
    │   │       InputCharacterInterface.h
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
    │   │   │
    │   │   └───StaticMeshActor
    │   │           SplineDrawComponent.cpp
    │   │
    │   └───UseCases
    │       ├───InputCharacterComponent
    │       │       MovementCharacterUseCase.cpp
    │       │
    │       └───SplineDrawComponent
    │               TrajectoryRuntimeDrawUseCase.cpp
    │
    └───Public
        ├───Application
        │   ├───BallStaticMeshActor
        │   │       BallStaticMeshActor.h
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
        │   │
        │   └───StaticMeshActor
        │           SplineDrawComponent.h
        │
        └───UseCases
            ├───InputCharacterComponent
            │       MovementCharacterUseCase.h
            │
            └───SplineDrawComponent
                    TrajectoryRuntimeDrawUseCase.h


```
