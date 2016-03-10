/*
 * cVCLSolver.cpp
 *
 *  Created on: Mar 7, 2016
 *      Author: jrug001
 */

#include <iostream>
#include <Eigen/Sparse>

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
    // convert A matrix to sparse format
    int nrows = (*A).rows();
    int ncols = (*A).cols();
    std::cout << "A size: " << (*A).rows() << " x " << (*A).cols();
    Eigen::SparseMatrix<tCalcs, Eigen::RowMajor> sparseA;
    sparseA = (*A).sparseView();
    
    // temporary; vcl copy doesn't like MatrixX1C
    Eigen::VectorXd evec_rhs(ncols);
    Eigen::VectorXd evec_sol(ncols);
    for (int i = 0; i < ncols; i++){
        evec_rhs(i) = rhsvec(i);
    }
    
    std::cout << " " << (*A)(1,1) << " ";
    
    // convert to viennacl matrix/vector types
    VCLSparseMat vcl_sparseA(nrows, ncols);
    viennacl::vector<tCalcs> vcl_rhs(ncols);
    viennacl::vector<tCalcs> vcl_sol(ncols);
    
    viennacl::copy(sparseA, vcl_sparseA);
    viennacl::copy(rhsvec, vcl_rhs);
    
    // set up preconditioner (Jacobi with default settings)
    viennacl::linalg::jacobi_precond<VCLSparseMat> vcl_jacobi(vcl_sparseA, viennacl::linalg::jacobi_tag());
    
    // solve
    viennacl::linalg::gmres_tag my_gmres_tag(1e-8, 500, 80);
    vcl_sol = viennacl::linalg::solve(vcl_sparseA, vcl_rhs, my_gmres_tag, vcl_jacobi);
    
    // copy data back to Eigen matrix/vectors (is this only required for the solution?)
    viennacl::copy(vcl_sol, evec_sol);
    // temporary; vcl copy doesn't like MatrixX1C
    for (int i = 0; i < ncols; i++){
        solvec(i) = evec_sol(i);
    }
    
    std::cout << my_gmres_tag.iters() << " " << my_gmres_tag.error() << " " << solvec(1);
}
