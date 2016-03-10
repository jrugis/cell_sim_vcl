/*
 * cVCLSolver.cpp
 *
 *  Created on: Mar 7, 2016
 *      Author: jrug001
 */

#include <iostream>

// enable Eigen wrappers within ViennaCL
#define VIENNACL_HAVE_EIGEN

#include "viennacl/linalg/jacobi_precond.hpp"
#include "viennacl/linalg/gmres.hpp"

#include "cVCLSolver.h"
#include "cCellMesh.h"

cVCLSolver::cVCLSolver(MatrixXXC &Amat){
	std::cout << "<SOLVER> initialising the solver..." << std::endl;
	// initialise pointer to A
    A = &Amat;
	// etc
}

cVCLSolver::~cVCLSolver(){
	// anything to destroy?
}

void cVCLSolver::step(MatrixX1C &solvec, MatrixX1C &rhsvec){
    // MatrixX1C result;
    viennacl::linalg::gmres_tag my_gmres_tag(1e-6, 500, 40);
    
    std::cout << " " << (*A)(1,1) << " ";
    
    // solve
    solvec = viennacl::linalg::solve(*A, rhsvec, my_gmres_tag);
    
    std::cout << my_gmres_tag.iters() << " " << my_gmres_tag.error() << " " << solvec(1);
}
