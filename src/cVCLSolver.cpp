/*
 * cVCLSolver.cpp
 *
 *  Created on: Mar 7, 2016
 *      Author: jrug001
 */

#include <iostream>

#include "cVCLSolver.h"
#include "cCellMesh.h"

cVCLSolver::cVCLSolver(MatrixXXC &Amat){
	std::cout << "<SOLVER> initialising the solver..." << std::endl;
	// initialise pointer to A
	// etc
}

cVCLSolver::~cVCLSolver(){
	// anything to destroy?
}

void cVCLSolver::step(MatrixX1C &solvec, MatrixX1C &rhsvec){
	// solve
}
