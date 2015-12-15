// Fill out your copyright notice in the Description page of Project Settings.

#include "Test2DPlatformer.h"
#include "Bunny.h"
#include "PaperSpriteComponent.h"

FName ABunny::SpriteComponentName(TEXT("Sprite0"));

// Sets default values
ABunny::ABunny()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    
    // Setup the assets
    struct FConstructorStatics
    {
        ConstructorHelpers::FObjectFinderOptional<UPaperSprite> IdleSpriteAsset;
        FConstructorStatics()
        : IdleSpriteAsset(TEXT("/Game/Sprites/HeroSprite"))
        {
        }
    };
    static FConstructorStatics ConstructorStatics;
    
    IdleSprite = ConstructorStatics.IdleSpriteAsset.Get();

    // Create a dummy root component we can attach things to.
    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
    UE_LOG(LogTemp, Warning, TEXT("Bunny"));
    this->DisableComponentsSimulatePhysics();
    
    // Try to create the sprite component
    /*Sprite = CreateOptionalDefaultSubobject<UPaperSpriteComponent>(ABunny::SpriteComponentName);
    if (Sprite)
    {
        Sprite->AlwaysLoadOnClient = true;
        Sprite->AlwaysLoadOnServer = true;
        Sprite->bOwnerNoSee = false;
        Sprite->bAffectDynamicIndirectLighting = true;
        Sprite->PrimaryComponentTick.TickGroup = TG_PrePhysics;
        Sprite->AttachParent = RootComponent;
        static FName CollisionProfileName(TEXT("CharacterMesh"));
        Sprite->SetCollisionProfileName(CollisionProfileName);
        Sprite->bGenerateOverlapEvents = false;
        
        // Enable replication on the Sprite component so animations show up when networked
        Sprite->SetIsReplicated(true);
        Sprite->SetSprite(IdleSprite);
        Sprite->SetActive(false);
        
    } else {
        UE_LOG(LogTemp, Warning, TEXT("Problem creating sprite"));
    }*/

    bReplicates = true;
    
    FVector v = GetActorLocation();
    posX = v.X;
    posY = v.Z;
    speedX = FMath::FRandRange(0, 1) * 5;
    speedY = FMath::FRandRange(0, 1) * 5 - 2.5f;

}

// Called when the game starts or when spawned
void ABunny::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABunny::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

    posX += speedX;
    posY += speedY;
    speedY += gravity;
    
    if( posX > maxX )
    {
        speedX *= -1;
        posX = maxX;
    }
    else if( posX < minX )
    {
        speedX *= -1;
        posX = minX;
    }
    
    if( posY > maxY )
    {
        speedY *= -0.8f;
        posY = maxY;
        if( FMath::FRandRange(0, 1) > 0.5f )
            speedY -= 3 + FMath::FRandRange(0, 1) * 4;
    }
    else if( posY < minY )
    {
        speedY = 0;
        posY = minY;
    }
    newPos.X = posX;
    newPos.Y = 0;
    newPos.Z = posY;
    
    SetActorLocation(newPos);

}

// Called to bind functionality to input
void ABunny::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}
