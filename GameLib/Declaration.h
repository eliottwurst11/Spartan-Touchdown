/**
 * @file Declaration.h
 * @author Matthew Lopez
 *
 * Definition for the Declaration class. Declaration objects extract data from
 * and xml level file when loading the file, and use that data to construct
 * and load Item objects into the Level.
 *
 * The Declaration class has children, since some items that the xml file describes
 * have extra data associated with them that needs to be passed to those items' constructors.
 */

#ifndef GAME_DECLARATION_H
#define GAME_DECLARATION_H

/**
 * Declaration class definition used for passing xml data into Item constructors
 */
class Declaration {
private:
    /// holds the image name
    std::wstring mImageName;

    /// ID as a std::wstring
    std::wstring mId;

public:

    Declaration(std::wstring id, std::wstring name);

    /// disable the default constructor
    Declaration() = delete;

    /// disable the copy constructor
    Declaration(const Declaration &) = delete;

    /// disable assignment operator
    void operator=(const Declaration &) = delete;

    virtual ~Declaration();

    /**
     * Gets the name of the image that the declaration was made with
     * @return the name of the image as a wstring
     */
    std::wstring GetImageName() { return mImageName; }

    /**
     * Gets the std::wstring ID of the declaration
     * @return the ID of the declaration
     */
    std::wstring GetID() { return mId; }

    /**
     * Get the value for the Item. Overridden by the CoinDeclaration class since
     * coins have associated values in points.
     * @return 0 by default, unless overridden by a child class
     */
    virtual int GetValue() { return 0; }

    /**
     * Get a left-moving alternate image file for an Item
     * @return a file name describing a left-moving version of an Item's image
     */
    virtual std::wstring GetImageLeft() { return L""; }

    /**
     * Get a left-moving alternate image file for an Item
     * @return a file name describing a right-moving version of an Item's image
     */
    virtual std::wstring GetImageRight() { return L""; }

    /**
     * Gets the solid image for the item. By default there is none,
     * and only the derived version of this class will actually have one.
     * @return the image name of the solid image associated with this declaration as a wstring
     */
    virtual std::wstring GetSolidImageName() { return L""; }

    /**
     * Gets the breaking image for the item. By default, there is none,
     * and only the derived version of this class will actually have one.
     * @return the image name of the breaking image associated with this declaration as a wstring
     */
    virtual std::wstring GetBreakingImageName(){ return L""; }
};


#endif //GAME_DECLARATION_H