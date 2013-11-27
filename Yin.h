/* -*- c-basic-offset: 4 indent-tabs-mode: nil -*-  vi:set ts=8 sts=4 sw=4: */
/*
    This file is Copyright (c) 2012 Chris Cannam
  
    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use, copy,
    modify, merge, publish, distribute, sublicense, and/or sell copies
    of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
    MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR
    ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
    CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
    WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#ifndef _YIN_H_
#define _YIN_H_

#include "vamp-sdk/FFT.h"
#include "MeanFilter.h"

#include <cmath>

#include <iostream>
#include <vector>
#include <exception>

using std::vector;
using std::pair;



class Yin
{
public:
    Yin(size_t frameSize, size_t inputSampleRate, double thresh = 0.2);
    virtual ~Yin();

    struct YinOutput {
        double f0;
        double periodicity;
        double rms;
        vector<double> salience;
        vector<pair<double, double> > freqProb;
        YinOutput() :  f0(0), periodicity(0), rms(0), 
            salience(vector<double>(0)), freqProb(vector<pair<double, double> >(0)) { }
        YinOutput(double _f, double _p, double _r) :
            f0(_f), periodicity(_p), rms(_r), 
            salience(vector<double>(0)), freqProb(vector<pair<double, double> >(0)) { }
        YinOutput(double _f, double _p, double _r, vector<double> _salience) :
            f0(_f), periodicity(_p), rms(_r), salience(_salience), 
            freqProb(vector<pair<double, double> >(0)) { }
    };
    
    int setThreshold(double parameter);
    int setThresholdDistr(float parameter);
    int setFrameSize(size_t frameSize);
    // int setRemoveUnvoiced(bool frameSize);
    YinOutput process(const double *in) const;
    YinOutput processProbabilisticYin(const double *in) const;

private:
    mutable size_t m_frameSize;
    mutable size_t m_inputSampleRate;
    mutable double m_thresh;
    mutable size_t m_threshDistr;
    mutable size_t m_yinBufferSize;
    // mutable bool m_removeUnvoiced;
};

#endif
