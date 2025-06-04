// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/NPD_LidarScannerComponent.h"

#include "Actors/Player/NPD_PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Engine/StaticMeshActor.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Misc/MapErrors.h"

UNPD_LidarScannerComponent::UNPD_LidarScannerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	ScannerRange = 8000.0f;
	ScannerAngle = 25.0f;
	ScanDuration = 7.f;
	
	MaxNumRays = 2000;
	MaxNumPointsTilRemoval = 10000;
	LidarScansTilWaypoint = 10;

	bClearOnEndScan = false;
	bScanComplete = false;
	bLiDARHitClear = false;
	bInitializeLidar = true;

	Start = FVector::ZeroVector;
	End = FVector::ZeroVector;

	LiDARMeshPointMaterial = nullptr;
	LiDARPointMesh = nullptr;
	LiDARMeshRedPoint = nullptr;
	InstancedMeshComponent = nullptr;
	RedWaypointMeshComponent = nullptr;
	

}

void UNPD_LidarScannerComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (!Player)
		Player = Cast<ANPD_PlayerCharacter>(GetOwner());

	QueryParams.AddIgnoredActor(Player);
}


void UNPD_LidarScannerComponent::MakeStartAndEnd(FVector& StartPoint, FVector& EndPoint)
{
	const float AngleSine = UKismetMathLibrary::DegSin(ScannerAngle);

	const float XYRange = AngleSine * ScannerRange;

	const float RandomX = FMath::FRandRange(-1.0f, 1.0f);
	const float RandomY = FMath::FRandRange(-1.0f, 1.0f);

	if (!Player)
		Player = Cast<ANPD_PlayerCharacter>(GetOwner());
		
	if (!Player) return;

	const UCameraComponent* Camera = Player->GetComponentByClass<UCameraComponent>();

	if (!Camera) return;

	const FVector CameraLocation = Camera->GetComponentLocation();

	const FVector XVectorMultiStart = Camera->GetRightVector() * RandomX * 10;
	const FVector YVectorMultiStart = Camera->GetUpVector() * RandomY * 10;

	StartPoint = CameraLocation + XVectorMultiStart + YVectorMultiStart;

	const FVector Range = Camera->GetForwardVector() * ScannerRange;
	const FVector XVectorMultiEnd = Camera->GetRightVector() * RandomX * XYRange;
	const FVector YVectorMultiEnd = Camera->GetUpVector() * RandomY * XYRange;

	EndPoint = CameraLocation + XVectorMultiEnd + YVectorMultiEnd + Range;
	
}

void UNPD_LidarScannerComponent::RemoveLidarPoints() 
{
	if (InstancedMeshComponent)
	{
		InstancedMeshComponent->ClearInstances();
	}
}

void UNPD_LidarScannerComponent::StartLidarScan()
{
	if (!bLidarActivated)
	{
		UE_LOG(LogTemp, Display, TEXT("Lidar Scanner activated 1"));
		ActivateLidar();
		bLidarActivated = true;
	}
		
	if (!bScanComplete)
	{
		ScanLidar();
		//timer delegate cooloffperiod
		FTimerDelegate Delegate;
		Delegate.BindLambda([this]()
			{
				bScanComplete = false;
			});
		GetWorld()->GetTimerManager().SetTimer(LiDARScanningTimerHandle, Delegate, 3.f, false);
	}
}

void UNPD_LidarScannerComponent::ActivateLidar()
{
	TArray<AActor*> FoundActors;

	UE_LOG(LogTemp, Error, TEXT("Lidar Scanner Activated 2"));

	UGameplayStatics::GetAllActorsOfClass(GetWorld(),
		AStaticMeshActor::StaticClass(),
		FoundActors);
	if (FoundActors.Num() > 0)
	{
		if (AStaticMeshActor* StaticMeshActor = Cast<AStaticMeshActor>(FoundActors[0]))
		{
			UE_LOG(LogTemp, Error, TEXT("Lidar Scanner Activated 3"));
			InstancedMeshComponent = NewObject<UInstancedStaticMeshComponent>(StaticMeshActor);
			InstancedMeshComponent->RegisterComponent();
			InstancedMeshComponent->AttachToComponent(StaticMeshActor->GetRootComponent(),
				FAttachmentTransformRules::KeepWorldTransform);
			InstancedMeshComponent->SetEnableGravity(false);
			InstancedMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			InstancedMeshComponent->SetMaterial(0, LiDARMeshPointMaterial);
			InstancedMeshComponent->SetStaticMesh(LiDARPointMesh);

			RedWaypointMeshComponent = NewObject<UInstancedStaticMeshComponent>(StaticMeshActor);
			RedWaypointMeshComponent->RegisterComponent();
			RedWaypointMeshComponent->AttachToComponent(StaticMeshActor->GetRootComponent(),
				FAttachmentTransformRules::KeepWorldTransform);
			RedWaypointMeshComponent->SetEnableGravity(false);
			RedWaypointMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			RedWaypointMeshComponent->SetMaterial(0, LiDARMeshRedPoint);
			RedWaypointMeshComponent->SetStaticMesh(LiDARPointMesh);
		}
	}
}

void UNPD_LidarScannerComponent::ScanLidar()
{
	/*if (LidarSpraySound && SpecialSoundsAudioComponent)
	{
		SpecialSoundsAudioComponent->SetSound(LidarSpraySound);
		SpecialSoundsAudioComponent->Play();
	}*/

	for (size_t NumRays = 0; NumRays < MaxNumRays; NumRays++)
	{
		FVector StartPoint;
		FVector EndPoint;
		MakeStartAndEnd(StartPoint, EndPoint);
		FHitResult HitResult;
		bool bHit = GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartPoint,
			EndPoint,
			ECC_Visibility,
			QueryParams
		);
		if (!bHit) continue;

		if (InstancedMeshComponent)
		{
			FVector Scale(1.f, 1.f, 1.f);
			FTransform InstanceTransform(
				FRotator::ZeroRotator,
				HitResult.ImpactPoint,
				Scale);

			int LidarPointCount = InstancedMeshComponent->GetInstanceCount();
			if (LidarPointCount <= MaxNumPointsTilRemoval)
			{
				InstancedMeshComponent->AddInstance(InstanceTransform);
			}
			else
			{
				if(InstancedMeshComponent->RemoveInstance(0))
				{
					InstancedMeshComponent->AddInstance(InstanceTransform);
				}
			}
		}
	}
	
	if (LidarScansTilWaypoint <= 1)
	{
		MakeRedWayPoint();
		LidarScansTilWaypoint = 10;
	}
	else
	{
		LidarScansTilWaypoint--;
	}
	bScanComplete = true;
}

void UNPD_LidarScannerComponent::MakeRedWayPoint() const
{
	float HalfAngleSpread = 15.0f;

	for (size_t NumRays = 0; NumRays < 20; NumRays++)
	{
		float Angle = FMath::Lerp(-HalfAngleSpread, HalfAngleSpread, 
								 static_cast<float>(NumRays) / (20.0f - 1.0f));
		FVector Direction = Player->GetActorForwardVector().RotateAngleAxis(Angle, FVector::UpVector);
      
		FVector StartPoint = Player->GetActorLocation();
		FVector EndPoint = StartPoint + (Direction * ScannerRange);
		FHitResult HitResult;

		bool bHit = GetWorld()->LineTraceSingleByChannel(
			HitResult,
			StartPoint,
			EndPoint,
			ECC_Visibility,
			QueryParams
		);
		FVector Scale(1.f, 1.f, 1.f);
		FTransform InstanceTransform(
			FRotator::ZeroRotator,
			HitResult.ImpactPoint, 
			Scale);
		RedWaypointMeshComponent->AddInstance(InstanceTransform);
	}

}