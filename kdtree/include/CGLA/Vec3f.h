#ifndef __VEC3F_H
#define __VEC3F_H

#include "ArithVec.h"
#include "Vec3i.h"
#include "Vec3usi.h"

namespace CGLA {
	class Vec3d;
	class Quaternion;

	/** 3D float vector.
			Class Vec3f is the vector typically used in 3D computer graphics. 
			The class has many constructors since we may need to convert from
			other vector types. Most of these are explicit to avoid automatic
			conversion. 
	*/
	class Vec3f: public ArithVec<double,Vec3f,3>
	{
	public:

		/// Construct 0 vector.
		Vec3f(){}

		/// Construct a 3D double vector.
		Vec3f(double a, double b, double c): ArithVec<double,Vec3f,3>(a,b,c) {}

		/// Construct a vector with 3 identical coordinates.
		explicit Vec3f(double a): ArithVec<double,Vec3f,3>(a,a,a) {}

		/// Construct from a 3D int vector
		explicit Vec3f(const Vec3i& v): ArithVec<double,Vec3f,3>(v[0],v[1],v[2]) {}
	
		/// Construct from a 3D unsigned int vector.
		explicit Vec3f(const Vec3usi& v): ArithVec<double,Vec3f,3>(v[0],v[1],v[2]) {}

		/// Construct from a 3D double vector.
		explicit Vec3f(const Vec3d&);

		/// Construct from a Quaternion. ((NOTE: more explanation needed))
		explicit Vec3f(const Quaternion&);
		
		/// Compute Euclidean length.
		double length() const 
    {
      return sqrt(data[0]*data[0]+
                  data[1]*data[1]+
                  data[2]*data[2]);
    }
    
		/// Normalize vector.
		void normalize() 
    {
      (*this) /= length();
    }

		/** Get the vector in spherical coordinates.
				The first argument (theta) is inclination from the vertical axis.
				The second argument (phi) is the angle of rotation about the vertical 
				axis. The third argument (r) is the length of the vector. */
		void get_spherical( double&, double&, double& ) const;

		/** Assign the vector in spherical coordinates.
				The first argument (theta) is inclination from the vertical axis.
				The second argument (phi) is the angle of rotation about the vertical 
				axis. The third argument (r) is the length of the vector. */
		void set_spherical( double, double, double);

	};


	/// Returns normalized vector
	inline Vec3f normalize(const Vec3f& v) 
	{
		return v/v.length();
	}


	/// Returns cross product of arguments
	inline Vec3f cross( const Vec3f& x, const Vec3f& y ) 
	{
		return Vec3f( x[1] * y[2] - x[2] * y[1], 
									x[2] * y[0] - x[0] * y[2], 
									x[0] * y[1] - x[1] * y[0] );
	}

	/** Compute basis of orthogonal plane.
			Given a vector Compute two vectors that are orothogonal to it and 
			to each other. */
	void orthogonal(const Vec3f&,Vec3f&,Vec3f&);


}
#endif
