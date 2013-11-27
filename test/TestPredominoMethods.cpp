/* -*- c-basic-offset: 4 indent-tabs-mode: nil -*-  vi:set ts=8 sts=4 sw=4: */

#include "PredominoMethods.h"

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <boost/test/floating_point_comparison.hpp>

BOOST_AUTO_TEST_SUITE(TestPredominoMethods)

BOOST_AUTO_TEST_CASE(pickNPeaks)
{
    vector<float> invec;
    invec.push_back(0);
    invec.push_back(1);
    invec.push_back(2);
    invec.push_back(1);
    invec.push_back(3);
    invec.push_back(3);
    invec.push_back(4);
    invec.push_back(0);
    invec.push_back(1);
    invec.push_back(0);
    
    vector<size_t> outvec = PredominoMethods::pickNPeaks(invec, 2);
    BOOST_CHECK_EQUAL(outvec[0], 2);
    BOOST_CHECK_EQUAL(outvec[1], 6);
    
}

BOOST_AUTO_TEST_CASE(zeroPad)
{
    size_t nIn = 4;
    size_t nPadded = 8;
    float *in = new float[nIn];
    in[0] = 1; in[1] = 2; in[2] = 3; in[3] = 4;
    float *out = new float[nPadded];
    PredominoMethods::zeroPad(in, out, nIn, nPadded);
    
    BOOST_CHECK_EQUAL(out[0], 3);
    BOOST_CHECK_EQUAL(out[1], 4);
    for (size_t i = 2; i < nPadded - nIn/2; ++i) {
        BOOST_CHECK_EQUAL(out[i], 0);
    }
    BOOST_CHECK_EQUAL(out[6], 1);
    BOOST_CHECK_EQUAL(out[7], 2);
    
    delete [] in;
    delete [] out;
}

BOOST_AUTO_TEST_CASE(applyWindow)
{
    size_t n = 4;
    vector<float> in;
    vector<float> win;
    for (size_t i = 0; i < n; ++i) {
        in.push_back(i);
        win.push_back(i);
    }
    PredominoMethods::applyWindow(&in, win);
    for (size_t i = 0; i < n; ++i) {
        BOOST_CHECK_EQUAL(in[i], i*i);
    }
}

BOOST_AUTO_TEST_CASE(hannWindow4)
{
    size_t n = 4;
    vector<float> hw = PredominoMethods::hannWindow(n);
    // for (size_t i = 0; i < n; ++i) {
    //     std::cerr << hw[i] << std::endl;
    // }

    BOOST_CHECK_CLOSE_FRACTION(hw[0], 0.1382, .0001);
    BOOST_CHECK_CLOSE_FRACTION(hw[1], 0.3618, .0001);
    BOOST_CHECK_CLOSE_FRACTION(hw[2], 0.3618, .0001);
    BOOST_CHECK_CLOSE_FRACTION(hw[3], 0.1382, .0001);
}

BOOST_AUTO_TEST_CASE(parabolicInterpolation)
{
    vector<float> mag1;
    mag1.push_back(1); mag1.push_back(2); mag1.push_back(1);
    vector<size_t> peakIndices1;
    peakIndices1.push_back(1);
    vector<float> interpolated1 = PredominoMethods::parabolicInterpolation(mag1, peakIndices1);
    BOOST_CHECK_CLOSE_FRACTION(interpolated1[0], 0, 0.001);

    vector<float> mag2;
    mag2.push_back(1); mag2.push_back(1); mag1.push_back(0);
    vector<size_t> peakIndices2;
    peakIndices2.push_back(1);
    vector<float> interpolated2 = PredominoMethods::parabolicInterpolation(mag2, peakIndices2);
    BOOST_CHECK_CLOSE_FRACTION(interpolated2[0], -0.5, 0.001);
}

BOOST_AUTO_TEST_CASE(convertMagnitude2dB)
{
    vector<float> mag;
    mag.push_back(1.01); 
    vector<float> magdb = PredominoMethods::convertMagnitude2dB(mag);
    BOOST_CHECK_CLOSE_FRACTION(magdb[0], 0.0864, 0.001);
}

BOOST_AUTO_TEST_CASE(generateOutputFrequencies)
{
    vector<float> f = PredominoMethods::generateOutputFrequencies(110, 2, 50);
    BOOST_CHECK_CLOSE_FRACTION(f[0], 110, 0.001);
    BOOST_CHECK_CLOSE_FRACTION(f[1], 113.2232, 0.001);
}

BOOST_AUTO_TEST_CASE(timedomain2magnitude)
{
    float *in = new float[4];
    in[0] = 1;
    in[1] = 2;
    in[2] = 3;
    in[3] = 2;
    vector<float> mag = PredominoMethods::timedomain2magnitude(in, 4, 0);
    // for (size_t i = 0; i < 4; ++i) std::cerr << mag[i] << std::endl;
    delete [] in;
    BOOST_CHECK_CLOSE_FRACTION(mag[0], 8, 0.001);
    BOOST_CHECK_CLOSE_FRACTION(mag[1], 2, 0.001);
    BOOST_CHECK_CLOSE_FRACTION(mag[2], 0, 0.001);
    BOOST_CHECK_CLOSE_FRACTION(mag[3], 2, 0.001);
}

BOOST_AUTO_TEST_SUITE_END()

