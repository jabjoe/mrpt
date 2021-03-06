/* +---------------------------------------------------------------------------+
   |                     Mobile Robot Programming Toolkit (MRPT)               |
   |                          http://www.mrpt.org/                             |
   |                                                                           |
   | Copyright (c) 2005-2014, Individual contributors, see AUTHORS file        |
   | See: http://www.mrpt.org/Authors - All rights reserved.                   |
   | Released under BSD License. See details in http://www.mrpt.org/License    |
   +---------------------------------------------------------------------------+ */

#include "kinematics-precomp.h"  // Precompiled headers

#include <mrpt/kinematics.h>

#include <mrpt/utils/CStartUpClassesRegister.h>


using namespace mrpt::kinematics;
using namespace mrpt::utils;

void registerAllClasses_mrpt_kinematics();

CStartUpClassesRegister  mrpt_kinematics_class_reg(&registerAllClasses_mrpt_kinematics);

/*---------------------------------------------------------------
					registerAllClasses_mrpt_kinematics
  ---------------------------------------------------------------*/
void registerAllClasses_mrpt_kinematics()
{
	registerClass( CLASS_ID( CKinematicChain ) );

}

