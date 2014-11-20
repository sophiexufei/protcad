//*******************************************************************************************************
//*******************************************************************************************************
//*************************************                      ********************************************
//*************************************  protOptSolvent 1.1  ********************************************
//*************************************                      ********************************************
//*******************************************************************************************************
//******** -sidechain and backbone optimization with a burial-based scaling of electrostatics- **********
//*******************************************************************************************************

/////// Just specify a infile and outfile, it will optimize to a generally effective minimum.

//--Program setup----------------------------------------------------------------------------------------
#include <iostream>
#include <string>
#include <time.h>
#include <sstream>
#include "ensemble.h"
#include "PDBInterface.h"
int main (int argc, char* argv[])
{
	//--Running parameters
	if (argc !=3)
	{
		cout << "protOptSolvent <inFile.pdb> <outFile.pdb>" << endl;
		exit(1);
	}
	enum aminoAcid {A,R,N,D,Dh,C,Cx,Q,E,Eh,Hd,He,Hn,Hp,I,L,K,M,F,P,O,S,T,W,Y,V,G,dA,dR,dN,dD,dDh,dC,dCx,dQ,dE,dEh,dHd,dHe,dHn,dHp,dI,dL,dK,dM,dF,dP,dO,dS,dT,dW,dY,dV};
	string infile = argv[1];
	PDBInterface* thePDB = new PDBInterface(infile);
	ensemble* theEnsemble = thePDB->getEnsemblePointer();
	molecule* pMol = theEnsemble->getMoleculePointer(0);
	protein* _prot = static_cast<protein*>(pMol);
	_prot->silenceMessages();
	residue::setCutoffDistance(9.0);
    pmf::setScaleFactor(0.0);
	rotamer::setScaleFactor(0.0);
    microEnvironment::setScaleFactor(0.0);
	amberVDW::setScaleFactor(1.0);
	amberVDW::setRadiusScaleFactor(1.0);
	amberVDW::setLinearRepulsionDampeningOff();
	amberElec::setScaleFactor(1.0);
	solvation::setItsScaleFactor(0.0);
	string outFile;

	cout << endl << "\t*protOptSolvent*" << endl << endl << "Starting Energy is: " << _prot->intraSoluteEnergy(true) << endl << endl << "Optimization running..." << endl;
	_prot->protOptSolvent(300);

//--Print final energy and write a pdb file--------------------------------------------------------------
	cout << endl << "Optimization is complete!" << endl;
	cout << "Final energy is: " << _prot->intraSoluteEnergy(true) << endl << endl;
	
	outFile = argv[2];
	pdbWriter(_prot, outFile);
	return 0;
}

