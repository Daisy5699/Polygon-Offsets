namespace unreal
{
    class UWorld;
    class AGameStateBase;
    class APlayerState;
    class APawn;
    class APlayerController;
    class APlayerCameraManager;
    class USceneComponent;
    class USkeletalMeshComponent;
    class AWeapon;

    class UWorld
    {
    public:
        static auto Get( ) -> UWorld*
        {
            return kernel->read<UWorld*>( kernel->m_module_base + offsets::UWorld );
        }

        auto OwningGameInstance( ) -> uintptr_t
        {
            return kernel->read<uintptr_t>( (uintptr_t)this + offsets::OwningGameInstance );
        }

        auto GameState( ) -> AGameStateBase*
        {
            return kernel->read<AGameStateBase*>( (uintptr_t)this + offsets::GameState );
        }

        auto PersistentLevel( ) -> uintptr_t
        {
            return kernel->read<uintptr_t>( (uintptr_t)this + 0x30 );
        }

        auto LocalPlayers( ) -> uintptr_t
        {
            auto game_instance = OwningGameInstance( );
            return kernel->read<uintptr_t>( game_instance + offsets::LocalPlayers );
        }

        auto LocalPlayerController( ) -> APlayerController*
        {
            auto players = LocalPlayers( );
            auto local   = kernel->read<uintptr_t>( players );
            return kernel->read<APlayerController*>( local + offsets::PlayerController );
        }
    };

    class AGameStateBase
    {
    public:
        auto PlayerArray( ) -> TArray<APlayerState*>
        {
            return kernel->read<TArray<APlayerState*>>( (uintptr_t)this + offsets::PlayerArray );
        }
    };

    class APlayerController
    {
    public:
        auto AcknowledgedPawn( ) -> APawn*
        {
            return kernel->read<APawn*>( (uintptr_t)this + offsets::AcknowledgedPawn );
        }

        auto CameraManager( ) -> APlayerCameraManager*
        {
            return kernel->read<APlayerCameraManager*>( (uintptr_t)this + offsets::PlayerCameraManager );
        }
    };

    class APlayerCameraManager
    {
    public:
        auto CameraCache( ) -> FCameraCacheEntry
        {
            return kernel->read<FCameraCacheEntry>( (uintptr_t)this + 0x22B0 );
        }

        auto Location( ) -> FVector
        {
            return kernel->read<FVector>( (uintptr_t)this + 0x22B0 + 0x10 );
        }

        auto Rotation( ) -> FRotator
        {
            return kernel->read<FRotator>( (uintptr_t)this + 0x22B0 + 0x10 + 0x18 );
        }

        auto Fov( ) -> float
        {
            return kernel->read<float>( (uintptr_t)this + 0x22B0 + 0x10 + 0x30 );
        }
    };

    class USceneComponent
    {
    public:
        auto RelativeLocation( ) -> FVector
        {
            return kernel->read<FVector>( (uintptr_t)this + offsets::RelativeLocation );
        }

        auto ComponentToWorld( ) -> FTransform
        {
            return kernel->read<unreal::FTransform>( (uintptr_t)this + offsets::ComponentToWorld );
        }
    };

    class USkeletalMeshComponent : public USceneComponent
    {
    public:
        auto BoneArray( ) -> uintptr_t
        {
            auto arr = kernel->read<uintptr_t>( (uintptr_t)this + offsets::BoneArray );
            if ( !arr )
                arr = kernel->read<uintptr_t>( (uintptr_t)this + offsets::BoneArrayBackup );
            return arr;
        }

        auto GetBone( int index ) -> FTransform
        {
            return kernel->read<FTransform>( BoneArray( ) + ( index * sizeof( FTransform ) ) );
        }

        auto GetBonePosition( int index ) -> FVector
        {
            auto ctw         = kernel->read<FTransform>( (uintptr_t)this + offsets::ComponentToWorld );
            auto bone        = GetBone( index );
            auto bone_matrix = bone.to_matrix( ) * ctw.to_matrix( );
            return { bone_matrix.m[3][0], bone_matrix.m[3][1], bone_matrix.m[3][2] };
        }

        auto VisibilityTickOption( ) -> uint8_t
        {
            return kernel->read<uint8_t>( (uintptr_t)this + offsets::VisibilityBasedAnimTickOption );
        }

        auto Flags( ) -> uint8_t
        {
            return kernel->read<uint8_t>( (uintptr_t)this + offsets::Flags );
        }
    };

    class AWeapon
    {
    public:
        auto TimeBetweenShots( ) -> float
        {
            return kernel->read<float>( (uintptr_t)this + offsets::TimeBetweenShots );
        }

        auto GunUpRecoil( ) -> float
        {
            return kernel->read<float>( (uintptr_t)this + offsets::GunUpRecoil );
        }

        auto AccuracyHip( ) -> float
        {
            return kernel->read<float>( (uintptr_t)this + offsets::AccuracyHip );
        }

        auto MaxMagazineAmmo( ) -> int32_t
        {
            return kernel->read<int32_t>( (uintptr_t)this + offsets::MaxMagazineAmmo );
        }

        auto MaxStockAmmo( ) -> int32_t
        {
            return kernel->read<int32_t>( (uintptr_t)this + offsets::MaxStockAmmo );
        }

        auto CurrentMagazineAmmo( ) -> int32_t
        {
            return kernel->read<int32_t>( (uintptr_t)this + offsets::CurrentMagazineAmmo );
        }

        auto CurrentStockAmmo( ) -> int32_t
        {
            return kernel->read<int32_t>( (uintptr_t)this + offsets::CurrentStockAmmo );
        }

        auto CurrentSpread( ) -> float
        {
            return kernel->read<float>( (uintptr_t)this + offsets::CurrentSpread );
        }

        auto ShootingType( ) -> uint8_t
        {
            return kernel->read<uint8_t>( (uintptr_t)this + offsets::GunShootingType );
        }
    };

    class APlayerState
    {
    public:
        auto PawnPrivate( ) -> APawn*
        {
            return kernel->read<APawn*>( (uintptr_t)this + offsets::PawnPrivate );
        }

        auto TeamIndex( ) -> int32_t
        {
            return kernel->read<int32_t>( (uintptr_t)this + offsets::TeamIndex );
        }
    };

    class APawn
    {
    public:
        auto RootComponent( ) -> USceneComponent*
        {
            return kernel->read<USceneComponent*>( (uintptr_t)this + offsets::RootComponent );
        }

        auto Mesh( ) -> USkeletalMeshComponent*
        {
            return kernel->read<USkeletalMeshComponent*>( (uintptr_t)this + offsets::Mesh );
        }

        auto CurrentGun( ) -> AWeapon*
        {
            auto inventory = kernel->read<uintptr_t>( (uintptr_t)this + offsets::InventoryComponent );
            return kernel->read<AWeapon*>( inventory + offsets::CurrentGun );
        }

        auto Location( ) -> FVector
        {
            auto rc = RootComponent( );
            if ( !rc ) return {};
            return rc->RelativeLocation( );
        }
    };
}
