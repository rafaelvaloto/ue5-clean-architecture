# Basic clean architecture UE-5.x

This project is a eu-5 c++ application with a basic principle of a clean architecture-based structure, with separation of components and their responsibilities using use cases.


In the Example structure below we are creating a basic movement component for our Character, separating the responsibilities into layers and decoupling the component, which can be reused in any other part of the system through useCase.

## Estrutura do Projeto

- Source
  - Project
      - Interfaces
          - PlayerCharacter ``` -- Interfaces dos components de PlayerCharacter ```
              - IMovementCharacterInterface.cpp
              ```
                class NEWPROJECT_API IMovementCharacterInterface
                {
                    GENERATED_BODY()
                    public:
                        virtual void Move(FVector InputController) = 0;
                }
            ```
      - Private
          - Application
              - PlayerCharacter
                  - APlayerCharacter.cpp ``` -- Representa o personagem do jogo ```
                  ```
                    // Sets default values
                    APlayerCharacter::APlayerCharacter()
                    {
                        PrimaryActorTick.bCanEverTick = true;
                
                        // Inicialize o componente de movimentação
                        MovementPlayerCharacter = CreateDefaultSubobject<UMovementCharacterComponent>(TEXT("IMovementComponent"));
                    }

                ```
              - PlayerController
                  - APlayerController.cpp 
                  ``` 
                    // Recebe a entrada do controle do jogador e chama o UseCase UMovementCharacterUseCase
                    
                    AJogPlayerController::Move()
                    {
                        APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetPawn());
                        if (!PlayerCharacter)
                        {
                            UE_LOG(LogTemp, Warning, TEXT("PlayerCharacter not found"));
                            return;
                        }
                
                        // Chama UseCase HandleCharacterMovement passando as entradas do controle...
                
                        FVector InputVector = InputController.Get<FVector>();
                        UMovementCharacterUseCase::HandleCharacterMovement(PlayerCharacter->MovementPlayerCharacter, InputVector);
                    }
                    
                  ```
          - Components
            - PlayerCharacter 
              - CMovementCharacterComponent.cpp ``` -- Implementa a interface IMovementCharacterInterface```
              ```
                //  CMovementCharacterComponent.h
                class NEWPROJECT_API UMovementCharacterComponent : public UActorComponent, public IMovementCharacterInterface
                {
                    public:
                        virtual void Move(FVector InputController) override;
                }
              
                // CMovementCharacterComponent.cpp
                void UMovementCharacterComponent::Move(FVector InputController)
                {
                    UE_LOG(LogTemp, Warning, TEXT("Movement component, %s"), *InputController.ToString());
          
                    // Adicionar a entrada do controle para a movimentacao do personagem...
                }
              ```
          - UseCases
            - PlayerCharacter
              - MovementCharacterUseCase.cpp
              ```
                // Lógica de movimentacao
                
                void UMovementCharacterUseCase::HandleCharacterMovement(TScriptInterface<IMovementCharacterInterface> MovementComponent, FVector InputController)
                {
                      MovementComponent->Move(InputController);
                } 
              ```
