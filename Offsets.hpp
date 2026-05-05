#pragma once
#include <cstdint>

// Patch 2.7.0

namespace Offsets {

	inline uintptr_t UWorld = 0x82694e0;
	inline uintptr_t GNames = 0x800e3e0;

	inline uintptr_t LocalPlayers = 0x38;
	inline uintptr_t PlayerController = 0x30;
	inline uintptr_t PlayerCameraManager = 0x348;
	inline uintptr_t AcknowledgedPawn = 0x338;
	inline uintptr_t PawnPrivate = 0x308;
	inline uintptr_t TeamIndex = 0x428;
	inline uintptr_t InventoryComponent = 0x458;

	inline uintptr_t OwningGameInstance = 0x1B8;
	inline uintptr_t GameState = 0x158;
	inline uintptr_t PlayerArray = 0x2A8;

	inline uintptr_t RootComponent = 0x198;

	inline uintptr_t Mesh = 0x340;
	inline uintptr_t SkeletalMesh = 0x700;
	inline uintptr_t BoneArray = 0x720;
	inline uintptr_t BoneArrayBackup = 0x730;
	inline uintptr_t VisibilityBasedAnimTickOption = 0x874;
	inline uintptr_t Flags = 0x878;
	inline uintptr_t RefSkeleton = 0x1B8;
	inline uintptr_t RelativeLocation = 0x128;
	inline uintptr_t ComponentToWorld = 0x280;

	inline uintptr_t CameraCachePrivate = 0x22B0;

	inline uintptr_t CurrentGun = 0x118;
	inline uintptr_t TimeBetweenShots = 0x3f8;
	inline uintptr_t GunUpRecoil = 0x3fc;
	inline uintptr_t AccuracyHip = 0x414;
	inline uintptr_t MaxMagazineAmmo = 0x3f0;
	inline uintptr_t MaxStockAmmo = 0x3f4;
	inline uintptr_t CurrentMagazineAmmo = 0x704;
	inline uintptr_t CurrentStockAmmo = 0x708;
	inline uintptr_t GunShootingType = 0x39f;
	inline uintptr_t CurrentSpread = 0x734;
