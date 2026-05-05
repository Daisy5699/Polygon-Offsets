#pragma once
#include <core/unreal/offsets/offsets.hpp>
#include <shared/includes.hpp>

#define M_PI 3.14159265358979323846
#define M_PI_2 1.57079632679489661923

#include <cmath>

namespace Unreal
{
	template < typename T >
	struct TArray
	{
		T *data = nullptr;
		int32_t count = 0;
		int32_t max = 0;

		T operator[] ( int32_t index ) const
		{
			return data[ index ];
		}

		bool is_valid ( ) const
		{
			return data && count > 0;
		}
	};

	struct FQuat
	{
		double x = 0.0;
		double y = 0.0;
		double z = 0.0;
		double w = 1.0;

		FQuat ( ) = default;

		FQuat ( double x , double y , double z , double w ) : x( x ), y( y ), z( z ), w( w )
		{}
	};

	struct FVector
	{
		double x = 0.0;
		double y = 0.0;
		double z = 0.0;

		FVector ( ) = default;

		FVector ( double x , double y , double z ) : x( x ), y( y ), z( z )
		{}

		FVector operator+ ( const FVector & o ) const
		{
			return { x + o.x , y + o.y , z + o.z };
		}

		FVector operator- ( const FVector & o ) const
		{
			return { x - o.x , y - o.y , z - o.z };
		}

		FVector operator* ( double s ) const
		{
			return { x * s , y * s , z * s };
		}

		FVector operator/ ( double s ) const
		{
			return { x / s , y / s , z / s };
		}

		double dot ( const FVector & o ) const
		{
			return x * o.x + y * o.y + z * o.z;
		}

		double length ( ) const
		{
			return sqrt( x * x + y * y + z * z );
		}

		double distance ( const FVector & o ) const
		{
			return ( *this - o ).length( );
		}

		bool is_zero ( ) const
		{
			return x == 0.0 && y == 0.0 && z == 0.0;
		}
	};

	struct FVector2D
	{
		double x = 0.0;
		double y = 0.0;

		FVector2D ( ) = default;

		FVector2D ( double x , double y ) : x( x ), y( y )
		{}

		bool is_zero ( ) const
		{
			return x == 0.0 && y == 0.0;
		}
	};

	struct FVector4
	{
		double x = 0.0;
		double y = 0.0;
		double z = 0.0;
		double w = 0.0;

		FVector4 ( ) = default;

		FVector4 ( double x , double y , double z , double w ) : x( x ), y( y ), z( z ), w( w )
		{}
	};

	struct FRotator
	{
		double pitch = 0.0;
		double yaw = 0.0;
		double roll = 0.0;

		FRotator ( ) = default;

		FRotator ( double pitch , double yaw , double roll ) : pitch( pitch ), yaw( yaw ), roll( roll )
		{}

		FRotator operator+ ( const FRotator & o ) const
		{
			return { pitch + o.pitch , yaw + o.yaw , roll + o.roll };
		}

		FRotator operator- ( const FRotator & o ) const
		{
			return { pitch - o.pitch , yaw - o.yaw , roll - o.roll };
		}

		FVector forward ( ) const
		{
			double cp = cos( pitch * M_PI / 180.0 );
			double sp = sin( pitch * M_PI / 180.0 );
			double cy = cos( yaw * M_PI / 180.0 );
			double sy = sin( yaw * M_PI / 180.0 );
			return { cp * cy , cp * sy , sp };
		}

		void clamp ( )
		{
			if ( pitch > 89.0 ) pitch = 89.0;
			if ( pitch < -89.0 ) pitch = -89.0;
			while ( yaw > 180.0 ) yaw -= 360.0;
			while ( yaw < -180.0 ) yaw += 360.0;
			roll = 0.0;
		}
	};

	struct FMatrix
	{
		double m[ 4 ][ 4 ] = {};

		FMatrix ( )
		{
			memset( m , 0 , sizeof( m ) );
		}

		explicit FMatrix ( const FRotator & rot )
		{
			memset( m , 0 , sizeof( m ) );

			double sp = sin( rot.pitch * M_PI / 180.0 ) , cp = cos( rot.pitch * M_PI / 180.0 );
			double sy = sin( rot.yaw * M_PI / 180.0 ) , cy = cos( rot.yaw * M_PI / 180.0 );
			double sr = sin( rot.roll * M_PI / 180.0 ) , cr = cos( rot.roll * M_PI / 180.0 );

			m[ 0 ][ 0 ] = cp * cy;
			m[ 0 ][ 1 ] = cp * sy;
			m[ 0 ][ 2 ] = sp;
			m[ 0 ][ 3 ] = 0.0;

			m[ 1 ][ 0 ] = sr * sp * cy - cr * sy;
			m[ 1 ][ 1 ] = sr * sp * sy + cr * cy;
			m[ 1 ][ 2 ] = -sr * cp;
			m[ 1 ][ 3 ] = 0.0;

			m[ 2 ][ 0 ] = -( cr * sp * cy + sr * sy );
			m[ 2 ][ 1 ] = cy * sr - cr * sp * sy;
			m[ 2 ][ 2 ] = cr * cp;
			m[ 2 ][ 3 ] = 0.0;

			m[ 3 ][ 0 ] = 0.0;
			m[ 3 ][ 1 ] = 0.0;
			m[ 3 ][ 2 ] = 0.0;
			m[ 3 ][ 3 ] = 1.0;
		}

		FMatrix operator* ( const FMatrix & o ) const
		{
			FMatrix result{};
			for ( int row = 0; row < 4; ++row )
				for ( int col = 0; col < 4; ++col )
					result.m[ row ][ col ] =
						m[ row ][ 0 ] * o.m[ 0 ][ col ] +
						m[ row ][ 1 ] * o.m[ 1 ][ col ] +
						m[ row ][ 2 ] * o.m[ 2 ][ col ] +
						m[ row ][ 3 ] * o.m[ 3 ][ col ];
			return result;
		}
	};

	struct FTransform
	{
		FQuat rotation = {};
		FVector translation = {};
		char pad[ 0x4 ];
		FVector scale = {};
		char pad2[ 0x4 ];

		FMatrix to_matrix ( ) const
		{
			FMatrix mat{};

			mat.m[ 3 ][ 0 ] = translation.x;
			mat.m[ 3 ][ 1 ] = translation.y;
			mat.m[ 3 ][ 2 ] = translation.z;

			double x2 = rotation.x + rotation.x;
			double y2 = rotation.y + rotation.y;
			double z2 = rotation.z + rotation.z;

			double xx2 = rotation.x * x2;
			double yy2 = rotation.y * y2;
			double zz2 = rotation.z * z2;

			mat.m[ 0 ][ 0 ] = ( 1.0 - ( yy2 + zz2 ) ) * scale.x;
			mat.m[ 1 ][ 1 ] = ( 1.0 - ( xx2 + zz2 ) ) * scale.y;
			mat.m[ 2 ][ 2 ] = ( 1.0 - ( xx2 + yy2 ) ) * scale.z;

			double yz2 = rotation.y * z2;
			double wx2 = rotation.w * x2;
			mat.m[ 2 ][ 1 ] = ( yz2 - wx2 ) * scale.z;
			mat.m[ 1 ][ 2 ] = ( yz2 + wx2 ) * scale.y;

			double xy2 = rotation.x * y2;
			double wz2 = rotation.w * z2;
			mat.m[ 1 ][ 0 ] = ( xy2 - wz2 ) * scale.x;
			mat.m[ 0 ][ 1 ] = ( xy2 + wz2 ) * scale.y;

			double xz2 = rotation.x * z2;
			double wy2 = rotation.w * y2;
			mat.m[ 2 ][ 0 ] = ( xz2 + wy2 ) * scale.x;
			mat.m[ 0 ][ 2 ] = ( xz2 - wy2 ) * scale.z;

			mat.m[ 0 ][ 3 ] = 0.0;
			mat.m[ 1 ][ 3 ] = 0.0;
			mat.m[ 2 ][ 3 ] = 0.0;
			mat.m[ 3 ][ 3 ] = 1.0;

			return mat;
		}
	};

	struct FCameraView
	{
		FVector location = {};
		FRotator rotation = {};
		float fov = 0.f;
	};

	struct FCameraCacheEntry
	{
		float timestamp = 0.f;
		char pad[ 12 ];
		FCameraView view = {};
	};

	inline FVector2D WorldToScreen (
		const FVector & world_location ,
		const FVector & camera_location ,
		const FRotator & camera_rotation , float fov , float screen_width , float
		screen_height )
	{
		FMatrix rot_mat( camera_rotation );

		FVector delta = world_location - camera_location;

		FVector axis_x{ rot_mat.m[ 0 ][ 0 ] , rot_mat.m[ 0 ][ 1 ] , rot_mat.m[ 0 ][ 2 ] };
		FVector axis_y{ rot_mat.m[ 1 ][ 0 ] , rot_mat.m[ 1 ][ 1 ] , rot_mat.m[ 1 ][ 2 ] };
		FVector axis_z{ rot_mat.m[ 2 ][ 0 ] , rot_mat.m[ 2 ][ 1 ] , rot_mat.m[ 2 ][ 2 ] };

		FVector transformed{
				delta.dot( axis_y ) ,
				delta.dot( axis_z ) ,
				delta.dot( axis_x )
			};

		if ( transformed.z < 0.001 )
			return {};

		double fov_rad = static_cast< double >( fov ) * M_PI / 180.0;
		double half_fov = tan( fov_rad / 2.0 );

		return {
				( screen_width / 2.0 ) + transformed.x / ( half_fov * transformed.z ) * ( screen_width / 2.0 ) ,
				( screen_height / 2.0 ) - transformed.y / ( half_fov * transformed.z ) * ( screen_height / 2.0 )
			};
	}
}
