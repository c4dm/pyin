#ifndef _MONONOTEPARAMETERS_H_
#define _MONONOTEPARAMETERS_H_

#include <iostream>
#include <vector>
#include <exception>

using std::vector;

class MonoNoteParameters
{
public:
    MonoNoteParameters();
    virtual ~MonoNoteParameters();
    
    // model architecture parameters
    size_t minPitch; // lowest pitch in MIDI notes
    size_t nPPS; // number of pitches per semitone
    size_t nS; // number of semitones
    size_t nSPP; // number of states per pitch
    size_t n; // number of states (will be calcualted from other parameters)
    
    // initial state probabilities
    vector<double> initPi; 
    
    // transition parameters
    double pAttackSelftrans;
    double pStableSelftrans;
    double pStable2Silent;
    double pSilentSelftrans;
    double sigma2Note; // standard deviation of next note Gaussian distribution
    double maxJump;
    double pInterSelftrans;
    
    double priorPitchedProb;
    double priorWeight;

    double minSemitoneDistance; // minimum distance for a transition
    
    double sigmaYinPitchAttack;
    double sigmaYinPitchStable;
    double sigmaYinPitchInter;
    
    double yinTrust;
    
};

#endif