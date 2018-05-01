/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                  This file is part of the class library                   */
/*       SoPlex --- the Sequential object-oriented simPlex.                  */
/*                                                                           */
/*    Copyright (C) 1996-2018 Konrad-Zuse-Zentrum                            */
/*                            fuer Informationstechnik Berlin                */
/*                                                                           */
/*  SoPlex is distributed under the terms of the ZIB Academic Licence.       */
/*                                                                           */
/*  You should have received a copy of the ZIB Academic License              */
/*  along with SoPlex; see the file COPYING. If not email to soplex@zib.de.  */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**@file   example.cpp
 * @brief  simple example of how to build up and solve an lp using the SoPlex callable library
 *
 * @author Ambros Gleixner
 */

#include <iostream>
#include "soplex.h"

using namespace soplex;


int main()
{
   SoPlex mysoplex;

   /* set the objective sense */
   mysoplex.setIntParam(SoPlex::OBJSENSE, SoPlex::OBJSENSE_MINIMIZE);

   /* we first add variables */
   DSVector dummycol(0);
   mysoplex.addColReal(LPCol(2.0, dummycol, infinity, 15.0));
   mysoplex.addColReal(LPCol(3.0, dummycol, infinity, 20.0));

   /* then constraints one by one */
   DSVector row1(2);
   row1.add(0, 1.0);
   row1.add(1, 5.0);
   mysoplex.addRowReal(LPRow(100.0, row1, infinity));

   /* NOTE: alternatively, we could have added the matrix nonzeros in dummycol already; nonexisting rows are then
    * automatically created. */

   /* write LP in .lp format */
   mysoplex.writeFileReal("dump.lp", NULL, NULL, NULL);

   /* solve LP */
   SPxSolver::Status stat;
   DVector prim(2);
   DVector dual(1);
   stat = mysoplex.optimize();

   /* get solution */
   if( stat == SPxSolver::OPTIMAL )
   {
      mysoplex.getPrimalReal(prim);
      mysoplex.getDualReal(dual);
      std::cout << "LP solved to optimality.\n";
      std::cout << "Objective value is " << mysoplex.objValueReal() << ".\n";
      std::cout << "Primal solution is [" << prim[0] << ", " << prim[1] << "].\n";
      std::cout << "Dual solution is [" << dual[0] << "].\n";
   }

   return 0;
}
