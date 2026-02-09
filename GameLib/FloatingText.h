/**
 * @file FloatingText.h
 * @author Hamin Paik
 *
 * Represents a piece of text that floats up and fades out.
 */

#ifndef GAME_FLOATINGTEXT_H
#define GAME_FLOATINGTEXT_H

#include <string>
#include <wx/graphics.h>

/**
 * Class for text that floats up and fades out
 */
class FloatingText {
public:
    FloatingText(std::wstring text, double x, double y,
        bool growing = false,
        double yVelocity = -100,
        double fontSize = 40,
        bool darkGreen = false
        );

    void Update(double elapsed);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    /**
     * Checks if the text animation has finished
     * @return true if the text's lifetime is over
     */
    bool IsFinished() const { return mTimer <= 0; }

    /**
     * Gets the current Y position (for testing).
     * @return Y position in virtual pixels.
     */
    double GetY() const { return mY; }

    /**
     * Gets the current Y velocity (for testing).
     * @return Y velocity in virtual pixels per second.
     */
    double GetYVelocity() const { return mYVelocity; }

private:
    /// The text to display
    std::wstring mText;

    /// Current X position in virtual pixels
    double mX;

    /// Current Y position in virtual pixels
    double mY;

    /// Upward velocity in virtual pixels per second
    double mYVelocity = -100.0; ///< Negative is up

    /// Total lifetime of the text in seconds
    double mDuration = 1.5;

    /// Current time remaining
    double mTimer;

    /// Font size
    int mFontSize = 40;

    /// indicates if the text should grow
    bool mGrowing;

    /// factor to grow the text
    double mGrowFactor = 50;

    /// is the text dark green
    bool mDarkGreen = false;
};

#endif //GAME_FLOATINGTEXT_H