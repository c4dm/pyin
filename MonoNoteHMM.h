/* -*- c-basic-offset: 4 indent-tabs-mode: nil -*-  vi:set ts=8 sts=4 sw=4: */
/*
    This file is Copyright (c) 2012 Matthias Mauch

*/

#ifndef _MONONOTEHMM_H_
#define _MONONOTEHMM_H_

#include "MonoNoteParameters.h"
#include "SparseHMM.h"

#include <boost/math/distributions.hpp>

#include <vector>
#include <cstdio>

using std::vector;

class MonoNoteHMM : public SparseHMM
{
public:
    MonoNoteHMM();
    const std::vector<double> calculateObsProb(const vector<pair<double, double> >);
    double getMidiPitch(size_t index);
    double getFrequency(size_t index);
    void build();
    MonoNoteParameters par;
    vector<boost::math::normal> pitchDistr;
};

#endif
