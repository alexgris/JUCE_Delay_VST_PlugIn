
#include <JuceHeader.h>
#include "LevelMeter.h"
#include "LookAndFeel.h"

//==============================================================================
LevelMeter::LevelMeter(Measurement& measurementL_, Measurement& measurementR_)
    :measurementL(measurementL_), measurementR(measurementR_),
    dbLevelL(clampdB), dbLevelR(clampdB)
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
    setOpaque(true);
    startTimerHz(refreshRate);
    decay = 1.0f - std::exp(-1.0f / (float(refreshRate) * 0.2f));
}

LevelMeter::~LevelMeter()
{
}

void LevelMeter::paint (juce::Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    const auto bounds = getLocalBounds();
    g.fillAll(Colors::LevelMeter::background);
    drawLevel(g, dbLevelL, 0, 7);
    drawLevel(g, dbLevelR, 9, 7);
    g.setFont(Fonts::getFont(10.0f));
    for (float db = maxdB; db >= mindB; db -= stepdB) {
        int y = positionForLevel(db);
        g.setColour(Colors::LevelMeter::tickLine);
        g.fillRect(0, y, 16, 1);

        g.setColour(Colors::LevelMeter::tickLabel);
        g.drawSingleLineText(juce::String(int(db)), bounds.getWidth(), y + 3, juce::Justification::right);
    }

/*
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));   // clear the background

    g.setColour (juce::Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (14.0f));
    g.drawText ("LevelMeter", getLocalBounds(),
                juce::Justification::centred, true);   // draw some placeholder text
    */
}

void LevelMeter::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..
    maxPos = 4.0f;
    minPos = float(getHeight()) - 4.0f;

}

void LevelMeter::timerCallback() {

    //dbLevelL = juce::Decibels::gainToDecibels(measurementL.load(), clampdB);
    //dbLevelR = juce::Decibels::gainToDecibels(measurementR.load(), clampdB);

    updateLevel(measurementL.readAndReset(), levelL, dbLevelL);
    updateLevel(measurementR.readAndReset(), levelR, dbLevelR);

    repaint();

    //DBG("left: " << measurementL.load() << ", right: " << measurementR.load());

}

void LevelMeter::drawLevel(juce::Graphics& g, float level, int x, int width) {

    int y = positionForLevel(level);
    if (level > 0.0f) {
        int y0 = positionForLevel(0.0f);
        g.setColour(Colors::LevelMeter::tooLoud);
        g.fillRect(x, y, width, y0 - y);
        g.setColour(Colors::LevelMeter::levelOK);
        g.fillRect(x, y0, width, getHeight() - y0);
    }
    else if (y < getHeight()) {
        g.setColour(Colors::LevelMeter::levelOK);
        g.fillRect(x, y, width, getHeight() - y);
    }

}

void LevelMeter::updateLevel(float newLevel, float& smoothedLevel, float& leveldB) const {

    if (newLevel > smoothedLevel) {
        smoothedLevel = newLevel; //instantanious attack
    }
    else {
        smoothedLevel += (newLevel - smoothedLevel) * decay;
    }

    if (smoothedLevel > clampLevel) {
        leveldB = juce::Decibels::gainToDecibels(smoothedLevel);
    }
    else {
        leveldB = clampdB;
    }

}
