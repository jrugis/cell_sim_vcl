/*
 * cVCLSolver.h
 *
 *  Created on: Mar 7, 2016
 *      Author: jrug001
 */

#ifndef CVCLSOLVER_H_
#define CVCLSOLVER_H_

typedef double tCalcs;

#include <string>
#include <Eigen/Dense>
#include "viennacl/compressed_matrix.hpp"

typedef Eigen::Matrix<tCalcs, Eigen::Dynamic, Eigen::Dynamic> MatrixXXC;
typedef Eigen::Matrix<tCalcs, Eigen::Dynamic, 1> MatrixX1C;
typedef viennacl::compressed_matrix<tCalcs> VCLSparseMat;

class cVCLSolver {
public:
	cVCLSolver(MatrixXXC &Amat);
	virtual ~cVCLSolver();
	void step(MatrixX1C &solvec, MatrixX1C &rhsvec);

private:
	MatrixXXC *A; // system matrix
};

#endif /* CVCLSOLVER_H_ */
