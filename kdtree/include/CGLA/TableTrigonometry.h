#ifndef __TABLETRIGONOMETRY_H
#define __TABLETRIGONOMETRY_H

#include <vector>
#include "CGLA.h"
#include "Common/CommonDefs.h"

namespace CGLA {

	namespace TableTrigonometry
	{
		typedef unsigned short int Angle;

		const Angle  ANGLE_MAX = USHRT_MAX>>2;
		const double ANGLE_FACTOR = double(ANGLE_MAX) / M_PI_2;
	
		class CosTable
		{
			std::vector<double> tab;

		public:
		
			CosTable(): tab(ANGLE_MAX+1)
			{
				for(int i=0;i<ANGLE_MAX+1; i++)
					tab[i] = cos(i/ANGLE_FACTOR);
			}
		
			double operator[](int i) const {return tab[i];}
		};

		const CosTable& COS_TABLE();

		inline double angle2float(Angle theta)
		{
			static double MPI2 = (double)(M_PI * 2);
			switch(theta & 3)
				{
				case 0: return   (theta>>2)/ANGLE_FACTOR;
				case 1: return M_PI - (theta>>2)/ANGLE_FACTOR;
				case 2: return M_PI + (theta>>2)/ANGLE_FACTOR;
				case 3: return MPI2 - (theta>>2)/ANGLE_FACTOR;
				}
			return 0;	
		}

		inline double t_cos(Angle theta)
		{
			switch(theta & 3)
				{
				case 0: return   COS_TABLE()[ theta>>2 ];
				case 1: return - COS_TABLE()[ theta>>2 ];
				case 2: return - COS_TABLE()[ theta>>2 ];
				case 3: return   COS_TABLE()[ theta>>2 ];
				}
			return 0;
		}

		inline double t_sin(Angle theta)
		{
			switch(theta & 3)
				{
				case 0: return   COS_TABLE()[ ANGLE_MAX - (theta>>2) ];
				case 1: return   COS_TABLE()[ ANGLE_MAX - (theta>>2) ];
				case 2: return - COS_TABLE()[ ANGLE_MAX - (theta>>2) ];
				case 3: return - COS_TABLE()[ ANGLE_MAX - (theta>>2) ];
				}
			return 0;
		}

		inline Angle t_atan(double x, double y)
		{
			Angle theta = Angle( acos(fabs(x)/sqrt(x*x+y*y)) * ANGLE_FACTOR );
			Angle key = (x>=0 ? (y>=0 ? 0 : 3) : (y>=0 ? 1 : 2));
			return (theta<<2) | key;
		}

	}


}
#endif
