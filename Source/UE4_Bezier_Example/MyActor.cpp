// Fill out your copyright notice in the Description page of Project Settings.

#include "MyActor.h"
#include "Runtime/Engine/Public/DrawDebugHelpers.h"



/*
@param t is time in second (0~1).
*/
FVector BezierPos1(FVector b0, FVector b1, FVector b2, FVector b3, float t)
{
	return (1-t)*(1-t)*(1-t)*b0 + 3*t*(1-t)*(1-t)*b1 + 3*t*t*(1-t)*b2 + t*t*t*b3;
}

/*
@param t is time in second (0~1).
*/
FVector BezierPos2(FVector b0, FVector b1, FVector b2, FVector b3, float t)
{
	FVector b01  = FMath::Lerp(b0, b1, t);
	FVector b12  = FMath::Lerp(b1, b2, t);
	FVector b23  = FMath::Lerp(b2, b3, t);
	FVector b012 = FMath::Lerp(b01, b12, t);
	FVector b123 = FMath::Lerp(b12, b23, t);
	return FMath::Lerp(b012, b123, t);

}

/*
@param t is time in second (0~1).
*/
FQuat BezierOri(FQuat b0, FQuat b1, FQuat b2, FQuat b3, float t)
{
	// Quaternion Bezier Curve 
	// ???

	return b0;

}




// Sets default values
AMyActor::AMyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyActor::BeginPlay()
{
	Super::BeginPlay();

	// Set Key Values
	pos_b[0].Set(220,    0, 310);   // b0
	pos_b[1].Set(190, -100, 520);   // b1
	pos_b[2].Set(-180, 100, 490);   // b2
	pos_b[3].Set(-120,   0, 270);   // b3

	//ori_b[0] = ?   // b0
	//ori_b[1] = ?   // b1
	//ori_b[2] = ?   // b2
	//ori_b[3] = ?   // b3

	
	// Draw for Debug
	// Key Points
	for (int i = 0; i < 4; i++)
	{
		DrawDebugBox(
			GetWorld(),
			pos_b[i],
			FVector(10, 10, 10),   // size
			ori_b[i],
			FColor(255, 0, 255),   // color
			false, 
			100.f	// time
		);
	}

	// Lines
	for (int i = 0; i < 3; i++)
	{
		DrawDebugLine(
			GetWorld(),
			pos_b[i],
			pos_b[i + 1],
			FColor(0, 0, 0),
			false, 
			100.f
		);
	}
	
	current_time = 0.f;
	time_duration = 5.f;
}



// Called every frame
void AMyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	current_time += DeltaTime;

	if ( current_time>time_duration ) current_time = 0;

	FVector p = BezierPos1(pos_b[0], pos_b[1], pos_b[2], pos_b[3], current_time/time_duration);

	SetActorLocation(p);
}

