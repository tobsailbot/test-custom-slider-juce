#pragma once


typedef AudioProcessorValueTreeState::SliderAttachment   SliderAttachment;
typedef AudioProcessorValueTreeState::ButtonAttachment   ButtonAttachment;
typedef AudioProcessorValueTreeState::ComboBoxAttachment ComboBoxAttachment;

enum DisplayNamePosition { DisplayNameNone, DisplayNameLeft, DisplayNameRight, DisplayNameAbove, DisplayNameBelow };

Colour getBackgroundColor()
{
    return Colour::fromFloatRGBA(0.8f, 0.4f, 0.4f, 1.f);
}

Colour getForegroundColor()
{
    return Colours::black;
}

class OtherLookAndFeel : public juce::LookAndFeel_V4
{
public:
    OtherLookAndFeel()
    {
        setColour(juce::Slider::thumbColourId, juce::Colours::blue);
        setColour(juce::Slider::rotarySliderFillColourId, juce::Colours::orange);
        setColour(juce::Slider::rotarySliderOutlineColourId, juce::Colours::black);
    }

    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider& slider) override
    {
        auto outline = slider.findColour(Slider::rotarySliderOutlineColourId);
        auto fill = slider.findColour(Slider::rotarySliderFillColourId);
        juce::Image background;
        juce::Image emoji;
        juce::Image emoji2;

        auto bounds = Rectangle<int>(x, y, width, height).toFloat();
        auto trasformer = AffineTransform::AffineTransform().scaled(0.8f);
        auto scaling_1 = 1.0;

        //background = juce::ImageCache::getFromMemory(BinaryData::background_jpg, BinaryData::background_jpgSize);
        //g.drawImageWithin(background, 0, 0, bounds.getWidth(), bounds.getHeight(), juce::RectanglePlacement::stretchToFit);

        // renderizar la imagen png
        emoji = juce::ImageCache::getFromMemory(BinaryData::emoji_png, BinaryData::emoji_pngSize);
        emoji2 = juce::ImageCache::getFromMemory(BinaryData::emoji_png, BinaryData::emoji_pngSize);

        //g.drawImageWithin(emoji, 0, 0, bounds.getWidth(), bounds.getHeight(), juce::RectanglePlacement::stretchToFit);
        float actual_val = slider.getValue();

        /* Si el valor de slider es >0.50 entonces scalar imagen a cierto valor,  */
        if (actual_val > 0.5) {
            scaling_1 = 0.2;
        }
        else {
            scaling_1 = 1.0;
        }

        // rotacion de la imagen, teniendo en cuenta el valor del slider y seteando puntos centrales de pivot
        // . scaled = es el metodo que setea la escala, y que puede ser variable

        // Dibuja la imagen png y la hace rotar
        //g.drawImageTransformed(emoji, trasformer.rotated(actual_val*4, (512.0f*0.8f)/2, (512.0f * 0.8f)/2).scaled(1.0));

        //g.drawImageTransformed(emoji, trasformer);
        
        //emoji.desaturate();
       // emoji.multiplyAllAlphas(0.5);
        DBG(slider.getValue());

        auto radius = jmin(bounds.getWidth()/2, bounds.getHeight()/2) - 2.0f;
        auto toAngle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        auto lineW = jmin(20.0f, radius * 0.5f);
        auto arcRadius = radius - lineW * 0.5f;

        auto rx = 0.0;
        auto ry = 0.0;
        auto rw = radius ;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

        // fill
        g.setColour(juce::Colours::blue);
        g.fillEllipse(rx, ry, rw, rw);
        // outline
        g.setColour(juce::Colours::red);
        g.drawEllipse(rx, ry, rw, rw, 1.0f);

        // fondo del arco, background
       // Path backgroundArc;
       // backgroundArc.addCentredArc(bounds.getCentreX(),
         //   bounds.getCentreY(),
           // arcRadius,
            //arcRadius,
           // 0.0f,
           // rotaryStartAngle,
           // rotaryEndAngle,
           // true);

        // g.setColour(outline);

        // g.strokePath(backgroundArc, PathStrokeType(lineW, PathStrokeType::curved, PathStrokeType::rounded));


        // Crea un nuevo path con linea punteada
        Path p;

        /* draw your arc */
        p.startNewSubPath(0.0, bounds.getHeight() * 0.5);
        p.addCentredArc(bounds.getCentreX(),
            bounds.getCentreY(),
            arcRadius,
            arcRadius,
            0.0f,
            rotaryStartAngle,
            rotaryEndAngle,
            true);

        g.setColour(juce::Colours::black);

        /* create path stroke type, */
        PathStrokeType stroke(2.0);

        /* create an array for your dash lengths */
        float dash[2] = { 20.0, 2.0};
        auto dash_transform = AffineTransform::AffineTransform();

        /* create the dashes */
        stroke.createDashedStroke(p, p, dash, 1);
        stroke.setStrokeThickness(10.0);
        /* paint */
        g.strokePath(p, stroke);

        // interior del arcorelleno, fill
        if (slider.isEnabled())
        {
            Path valueArc;
            valueArc.addCentredArc(bounds.getCentreX(),
                bounds.getCentreY(),
                arcRadius,
                arcRadius,
                0.0f,     // offset del arco fill
                rotaryStartAngle,
                toAngle,
                true);

            g.setColour(fill);

            /* create path stroke type, */
            PathStrokeType stroke_value(5.0);

            /* create the dashes */
            stroke.createDashedStroke(valueArc, valueArc, dash, 1);

            /* paint */
            g.strokePath(valueArc, stroke_value);
            g.setOpacity(1.0f);
        }







        //auto thumbWidth = lineW * 0;
        //Point<float> thumbPoint(bounds.getCentreX() + arcRadius * std::cos(toAngle - MathConstants<float>::halfPi),
        //                        bounds.getCentreY() + arcRadius * std::sin(toAngle - MathConstants<float>::halfPi));

        //g.setColour(slider.findColour(Slider::thumbColourId));
        //g.fillEllipse(Rectangle<float>(thumbWidth, thumbWidth).withCentre(thumbPoint));
    }

/*
    void drawRotarySlider(juce::Graphics& g, int x, int y, int width, int height, float sliderPos,
        const float rotaryStartAngle, const float rotaryEndAngle, juce::Slider&) override
    {
        auto radius = (float)juce::jmin(width / 2, height / 2) - 4.0f;
        auto centreX = (float)x + (float)width * 0.5f;
        auto centreY = (float)y + (float)height * 0.5f;
        auto rx = centreX - radius;
        auto ry = centreY - radius;
        auto rw = radius * 2.0f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);

        // shadow
        g.setColour(juce::Colours::black);
        g.fillEllipse(rx-9.0f, ry-8.0f, rw * 1.2f, rw * 1.2f);
        // fill
        g.setColour(juce::Colours::blue);
        g.fillEllipse(rx, ry, rw, rw);


        // outline
        g.setColour(juce::Colours::white);
        g.drawEllipse(rx, ry, rw, rw, 2.0f);


        juce::Path p;
        auto pointerLength = radius * 1.0f;
        auto pointerThickness = 5.0f;
        p.addRectangle(-pointerThickness * 0.5f, -radius, pointerThickness, pointerLength);
        p.applyTransform(juce::AffineTransform::rotation(angle).translated(centreX, centreY));

        // pointer
        g.setColour(juce::Colours::white);
        g.fillPath(p);
    }
*/

};


class WaveformComponent : public Component
{
public:
    WaveformComponent()
    {
        setSize(500, 200);
    }

    void paint(Graphics& g) override
    {
        g.fillAll(Colour(0xff0000ff));
        g.setColour(Colour(0xffffffff));

        const int numSamples = 1024;
        float samples[numSamples];

        // Obtenga los datos de muestra para la forma de onda
        // ...

        Path path;
        path.startNewSubPath(0.0f, getHeight() / 2.0f);

        for (int i = 0; i < numSamples; ++i)
        {
            const float x = static_cast<float> (i) / static_cast<float> (numSamples) * getWidth();
            const float y = (samples[i] * 0.5f + 0.5f) * getHeight();

            path.lineTo(x, y);
        }

        g.strokePath(path, PathStrokeType(2.0f));
    }
};


//==============================================================================
/**
*/
class gananciaSimpleAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    gananciaSimpleAudioProcessorEditor (gananciaSimpleAudioProcessor& p,
            AudioProcessorValueTreeState& vts)
        : AudioProcessorEditor (&p), processor (p), valueTreeState (vts), tooltip(this)
        {

        Typeface::Ptr noto = Typeface::createSystemTypefaceFor(notoSansFile, notoSansFileSize);

        //widgets.add (new SliderKnob(*this, vts, "ganancia", "right", "hslider", "editright", 0, {10, 30, 152, 30}, {172, 30, 400, 30}, &appdeslnf));
        setSize(400, 425);

        setLookAndFeel(&otherLookAndFeel);
        addAndMakeVisible(dial1);
        dial1.setSliderStyle(juce::Slider::RotaryVerticalDrag);

        dial1.setTextBoxStyle(juce::Slider::NoTextBox, false, 0, 0);
        dial1.setTextValueSuffix("dB" + vts.getParameter("ganancia")->label); // cambia valor de la etiqueta label
        new SliderAttachment( vts, "ganancia", dial1);
        dial1.setValue(0.1);
    }

    ~gananciaSimpleAudioProcessorEditor()
    {
        setLookAndFeel(nullptr);
    }


    //==============================================================================
    void paint (Graphics& g) override
    {
        g.fillAll (getBackgroundColor());
    }


    void resized() override
    {

        auto area = getLocalBounds();

        auto dialArea = area;
        dial1.setBounds(dialArea);

    }

private:
    gananciaSimpleAudioProcessor& processor;
    AudioProcessorValueTreeState& valueTreeState;
    TooltipWindow tooltip;
    OtherLookAndFeel otherLookAndFeel; // [2]
    juce::Image background;
    juce::Slider dial1;


    static const unsigned char notoSansFile[];
    static const int notoSansFileSize;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (gananciaSimpleAudioProcessorEditor)
};

#include "gananciaSimplePluginEditorResources.h"


