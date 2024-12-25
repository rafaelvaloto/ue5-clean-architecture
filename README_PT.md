**README_PT.md:**

# Projeto Básico Clean Architecture UE-5.x
Este projeto é uma aplicação em C++ para UE-5 com o princípio básico de uma estrutura baseada em arquitetura limpa, com separação de componentes e suas responsabilidades usando casos de uso.

Na estrutura abaixo, estamos criando um componente básico de movimento para o nosso Personagem, separando as responsabilidades em camadas e desacoplando o componente, que pode ser reutilizado em qualquer outra parte do sistema através do caso de uso.
## Estrutura do Projeto

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
