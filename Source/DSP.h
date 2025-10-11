/*
  ==============================================================================

    DSP.h
    Created: 11 Oct 2025 11:45:42am
    Author:  Alex

  ==============================================================================
*/

#pragma once

#include <cmath>


inline void panningEqualPower(float panning, float& left, float& right) {

    float x = 0.7853981633974483f * (panning + 1.0f);
    left = std::cos(x);
    right = std::sin(x);

}
