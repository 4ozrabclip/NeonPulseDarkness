// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NPD_PlayerComponentBase.h"
#include "NPD_LidarScannerComponent.generated.h"

class ANPD_PlayerCharacter;
/**
 * 
 */
UCLASS()
class NEONPULSEDARK_API UNPD_LidarScannerComponent : public UNPD_PlayerComponentBase
{
	GENERATED_BODY()
public:
	UNPD_LidarScannerComponent();

	virtual void BeginPlay() override;

	void ActivateLidar();
	void ScanLidar();
	void MakeRedWayPoint() const;
	void RemoveLidarPoints();
	void StartLidarScan();

	//Getters and Setters
	void SetLidarHitClear(bool InLidarHitClear) { bLiDARHitClear = InLidarHitClear;};
	void SetScanComplete(bool InbScanComplete) { bScanComplete = InbScanComplete;};
protected:
	//Lidar---------
	bool bLiDARHitClear;
	bool bScanComplete;
	
	FVector Start;
	FVector End;
	void MakeStartAndEnd(FVector& StartPoint, FVector& EndPoint);

	bool bInitializeLidar;

	short LidarScansTilWaypoint;
	
	
	UPROPERTY(EditAnywhere, Category = "LiDAR")
	float ScannerRange;
	UPROPERTY(EditAnywhere, Category = "LiDAR")
	float ScannerAngle;
	UPROPERTY(EditAnywhere, Category = "LiDAR")
	uint16 MaxNumRays;
	UPROPERTY(EditAnywhere, Category = "LiDAR")
	bool bClearOnEndScan;

	UPROPERTY(EditAnywhere, Category = "LiDAR")
	uint16 MaxNumPointsTilRemoval;
	

	UPROPERTY(EditAnywhere, Category = "LiDAR")
	UMaterialInterface* LiDARMeshPointMaterial;
	
	UPROPERTY(EditAnywhere, Category = "LiDAR")
	UMaterialInterface* LiDARMeshRedPoint;

	UPROPERTY(EditAnywhere, Category = "LiDAR")
	UStaticMesh* LiDARPointMesh;

	UPROPERTY(EditAnywhere, Category = "LiDAR")
	float ScanDuration;


	//--------------

private:
	FTimerHandle LiDARScanningTimerHandle;

	UPROPERTY()
	UInstancedStaticMeshComponent* InstancedMeshComponent;

	UPROPERTY()
	UInstancedStaticMeshComponent* RedWaypointMeshComponent;
	
	FTimerHandle MeshInstanceTimerHandle;

	FCollisionQueryParams QueryParams;

	bool bLidarActivated = false;

	
	

};
