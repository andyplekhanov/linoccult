#ifndef __VEC4F_H
#define __VEC4F_H

#include "Vec3f.h"

namespace CGLA {

	/** A four dimensional floating point vector. 
			This class is also used (via typedef) for
			homogeneous vectors.
	*/

	class Vec4f: public ArithVec<double,Vec4f,4>
	{
	public:
  
		/// Construct a (0,0,0,0) homogenous Vector
		Vec4f(): ArithVec<double,Vec4f,4>(0,0,0,0.0) {}

		/// Construct a (0,0,0,0) homogenous Vector
		explicit Vec4f(double _a): ArithVec<double,Vec4f,4>(_a,_a,_a,_a) {}

		/// Construct a 4D vector
		Vec4f(double _a, double _b, double _c, double _d): 
			ArithVec<double,Vec4f,4>(_a,_b,_c,_d) {}

		/// Construct a homogenous vector (a,b,c,1)
		Vec4f(double _a, double _b, double _c): 
			ArithVec<double,Vec4f,4>(_a,_b,_c,1.0) {}

		/// Construct a homogenous vector from a non-homogenous.
		explicit Vec4f(const Vec3f& v): 
			ArithVec<double,Vec4f,4>(v[0],v[1],v[2],1.0) {}

		/// Construct a homogenous vector from a non-homogenous.
		explicit Vec4f(const Vec3f& v,double _d): 
			ArithVec<double,Vec4f,4>(v[0],v[1],v[2],_d) {}

		/// Divide all coordinates by the fourth coordinate
		void de_homogenize();  

		operator Vec3f() const
		{
			double k = 1.0f/data[3];
			return  Vec3f(data[0]*k,data[1]*k,data[2]*k);
		}

		/// Compute Euclidean length.
		double length() const 
    {
      return sqrt(data[0]*data[0]+
                  data[1]*data[1]+
									data[2]*data[2]+
                  data[3]*data[3]);
    }
	};

	/** This function divides a vector (x,y,z,w) by w 
			to obtain a new 4D vector where w=1. */
	inline void Vec4f::de_homogenize() 
	{
		double k = 1.0f/data[3];
		data[0] = data[0]*k;
		data[1] = data[1]*k;
		data[2] = data[2]*k;
		data[3] = 1.0;
	}

}
#endif

