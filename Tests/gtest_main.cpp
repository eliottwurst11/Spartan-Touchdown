/**
 * @file gtest_main.cpp
 * @author Hamin Paik
 */

#include "gtest/gtest.h"
#include <wx/wx.h> // Include for wxWidgets functions
#include <wx/filefn.h> // Include for wxSetWorkingDirectory

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    wxInitAllImageHandlers();
    wxSetWorkingDirectory(L"../../");
    return RUN_ALL_TESTS();
}