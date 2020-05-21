/*=============================================================================
 *
 *  Copyright (c) 2019 Sunnybrook Research Institute
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

#ifndef SEDEEN_SRC_PLUGINS_CREATESTAINVECTORPROFILE_CREATESTAINVECTORPROFILE_H
#define SEDEEN_SRC_PLUGINS_CREATESTAINVECTORPROFILE_CREATESTAINVECTORPROFILE_H

// Sedeen headers
#include "algorithm/AlgorithmBase.h"
#include "algorithm/Parameters.h"
#include "algorithm/Results.h"

#include <omp.h>
#include <Windows.h>
#include <fstream>
#include <memory>

// Plugin headers
//#include "ColorDeconvolutionKernel.h"
#include "StainProfile.h"
//#include "FileDialogHandling.h"

namespace sedeen {
namespace tile {

} // namespace tile

namespace algorithm {
#define round(x) ( x >= 0.0f ? floor(x + 0.5f) : ceil(x - 0.5f) )

///Create Stain Vector Profile
///This plugin creates a way for the user to define a combination
///of stain vectors to be used in the Stain Analysis plugin
class CreateStainVectorProfile : public algorithm::AlgorithmBase {
public:
    CreateStainVectorProfile();
    virtual ~CreateStainVectorProfile();

private:
    // virtual functions
    virtual void run();
    virtual void init(const image::ImageHandle& image);

    //Member methods
    //inline std::string openFile(std::string path) {};

    ///Define the save file dialog options outside of init
    sedeen::file::FileDialogOptions defineSaveFileDialogOptions();

private:
    //Member parameters
    DisplayAreaParameter m_displayArea;
    TextFieldParameter m_nameOfStainProfile;
    OptionParameter m_numberOfStainComponents;

    //Stain One
    TextFieldParameter m_nameOfStainOne;
    RegionListParameter m_regionListStainOne;
    //Stain Two
    TextFieldParameter m_nameOfStainTwo;
    RegionListParameter m_regionListStainTwo;
    //Stain Three
    TextFieldParameter m_nameOfStainThree;
    RegionListParameter m_regionListStainThree;

    OptionParameter m_stainSeparationAlgorithm;
    OptionParameter m_stainToDisplay;
    BoolParameter m_showPreviewOnly;

    SaveFileDialogParameter m_saveFileAs;

private:
    //Member variables
    std::vector<std::string> m_numComponentsOptions;
    std::vector<std::string> m_stainToDisplayOptions;

    ///The stain vector profile and its XML file handling
    std::shared_ptr<StainProfile> m_localStainProfile;
    ///Returns the shared_ptr to the local stain profile
    inline std::shared_ptr<StainProfile> GetLocalStainProfile() { return m_localStainProfile; }



//I don't know how many of these will end up being used.
    //std::string m_path_to_root;
    //std::string m_path_to_stainfile;

    //algorithm::DisplayAreaParameter m_display_area;
    //algorithm::OptionParameter m_retainment;
    //algorithm::OptionParameter m_displayOptions;
    /// Parameter for selecting threshold retainment 
    //algorithm::OptionParameter m_behavior;
    /// User defined Threshold value.
    //algorithm::DoubleParameter m_threshold;
    /// The output result
    //algorithm::ImageResult m_result;
    //algorithm::TextResult m_output_text;
    //std::string m_report;
    /// Parameter for selecting which of the intermediate result to display
    //algorithm::OptionParameter m_output_option;
    /// User region of interest
    //std::vector<algorithm::GraphicItemParameter> m_region_interest;
    //algorithm::GraphicItemParameter m_regionToProcess;

    /// The intermediate image factory after color deconvolution
    //std::shared_ptr<image::tile::Factory> m_colorDeconvolution_factory;

    /// The intermediate image factory after thresholding
    //std::shared_ptr<image::tile::Factory> m_threshold_factory;
    //std::ofstream log_file;

};

} // namespace algorithm
} // namespace sedeen

#endif