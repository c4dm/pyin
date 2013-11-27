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

#ifndef _YINUTIL_H_
#define _YINUTIL_H_

#include "vamp-sdk/FFT.h"
#include "MeanFilter.h"

#include <cmath>

#include <iostream>
#include <vector>
#include <exception>

using std::vector;

class YinUtil
{
public:
    static double sumSquare(const double *in, const size_t startInd, const size_t endInd);
    static void difference(const double *in, double *yinBuffer, const size_t yinBufferSize);
    static void fastDifference(const double *in, double *yinBuffer, const size_t yinBufferSize);
    static void cumulativeDifference(double *yinBuffer, const size_t yinBufferSize);
    static int absoluteThreshold(const double *yinBuffer, const size_t yinBufferSize, const double thresh);
    static vector<double> yinProb(const double *yinBuffer, const size_t prior, const size_t yinBufferSize);
    static double parabolicInterpolation(const double *yinBuffer, const size_t tau,
                                         const size_t yinBufferSize);
};

#endif
