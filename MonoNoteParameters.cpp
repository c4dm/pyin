#include "MonoNoteParameters.h"

MonoNoteParameters::MonoNoteParameters() :
    minPitch(36), 
    nPPS(3), 
    nS(43), 
    nSPP(4), // states per pitch
    n(0),
    initPi(0), 
    pAttackSelftrans(0.99),
    pStableSelftrans(0.99),
    pStable2Silent(0.005),
    pSilentSelftrans(0.99), 
    sigma2Note(1.5),
    maxJump(13),
    pInterSelftrans(0.99),
    priorPitchedProb(.7),
    priorWeight(0.5),
    minSemitoneDistance(.5),
    sigmaYinPitchAttack(4), 
    sigmaYinPitchStable(0.9),
    sigmaYinPitchInter(4),
    yinTrust(0.1)
{
    // just in case someone put in a silly value for pRelease2Unvoiced
    n = nPPS * nS * nSPP;
}

MonoNoteParameters::~MonoNoteParameters()
{
}