/*=============================================================================
 *
 *  Copyright (c) 2021 Sunnybrook Research Institute
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 *=============================================================================*/

#include "StainVectorNMF.h"
#include <armadillo>

#include <mlpack/methods/amf/amf.hpp>

#include <sstream>

#include "ODConversion.h"
#include "StainVectorMath.h"

namespace sedeen {
namespace image {

StainVectorNMF::StainVectorNMF(std::shared_ptr<tile::Factory> source,
    double ODthreshold /*= 0.15 */)
    : StainVectorMLPACK(source),
    m_sampleSize(0), //Must set to greater than 0 to ComputeStainVectors
    m_useSubsampleOfPixels(true), //If false, all pixels above OD threshold are used
    m_numStains(2),  //Can be 2 or 3
    m_avgODThreshold(ODthreshold) //assign default value
{}//end constructor

StainVectorNMF::~StainVectorNMF(void) {
}//end destructor

long int StainVectorNMF::ComputeStainVectors(double (&outputVectors)[9]) {
    if (this->GetSourceFactory() == nullptr) { return 0; }
    //Using this overload of the method requires setting the bool and sample size in advance
    const long int sampleSize = this->GetSampleSize();
    if (sampleSize <= 0) { return 0; }
    const bool useSubsample = this->GetUseSubsampleOfPixels();
    const double ODthreshold = this->GetODThreshold();

    //Sample a set of pixel values from the source
    cv::Mat samplePixels;
    auto theSampler = this->GetWSISampler();
    if (theSampler == nullptr) { return 0; }

    //Use a random subset if useSubsample is true, else get all
    long int numSampledPixels(0);
    if (useSubsample) {
        numSampledPixels = theSampler->ChooseRandomPixels(samplePixels, sampleSize, ODthreshold);
    }
    else {
        numSampledPixels = theSampler->GetAllPixels(samplePixels, ODthreshold);
    }
    //Error check
    if (numSampledPixels <= 0) { return 0; }

    //Convert samplePixels from CV to Armadillo
    arma::Mat<double> armaSamplePixels = CVMatToArmaMat<double>(samplePixels);

    //The rank sets the number of columns in the basis matrix, and rows in the encoding matrix
    //It is the number of stains we are attempting to decompose the data points into
    //Valid values are 2 and 3 (enforce this)
    if (GetNumStains() > 3 || GetNumStains() < 2) { return 0; }
    size_t rank = static_cast<size_t>(GetNumStains());
    arma::Mat<double> basisMat, encodingMat;
    mlpack::amf::NMFALSFactorizer nmfFactorizer;
    //Perform non-negative matrix factorization
    double residue = nmfFactorizer.Apply(armaSamplePixels, rank, basisMat, encodingMat);

    //The stain values are in the encoding matrix. Convert to output array
    cv::Mat encodingAsCV = ArmaMatToCVMat<double>(encodingMat);
    //Convert to C-style array and normalize rows
    double tempStainVecOutput[9] = {0.0};
    StainCVMatToCArray(encodingAsCV, tempStainVecOutput, true);
    for (int i = 0; i < 9; i++) {
        outputVectors[i] = tempStainVecOutput[i];
    }
    return numSampledPixels;
}//end single-parameter ComputeStainVectors

//This overload does not have a default value for sampleSize, so it requires 2 or 3 arguments
long int StainVectorNMF::ComputeStainVectors(double (&outputVectors)[9], bool useSubsample, long int sampleSize /*=0*/) {
    if (this->GetSourceFactory() == nullptr) { return 0; }
    //If useSubsample is false and sampleSize is 0, cannot perform calculation. Return.
    if (useSubsample == false && sampleSize <= 0) { return 0; }
    //Set member variables with the argument values
    this->SetUseSubsampleOfPixels(useSubsample);
    this->SetSampleSize(sampleSize);
    //Call the single-parameter version of this method, which uses the member variables
    return this->ComputeStainVectors(outputVectors);
}//end multi-parameter ComputeStainVectors

} // namespace image
} // namespace sedeen
