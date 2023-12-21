/**
 * @file Machine.h
 * @author trang
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINE_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINE_H
#include <string>
#include <memory>
#include <b2_math.h>
#include <b2_world.h>
#include <b2_body.h>
#include "ContactListener.h"
class Component;
/**
 * The machine
 */
class Machine
{
private:


    int mX = 0;         ///< Machine x location
    int mY = 0;         ///< Machine y location
    int mFrame = 0;     ///< Current frame
    int mMachine = 1;///< Machine number
    /// The flag
    int mFlag = 1;
    /// The box2d world
    std::shared_ptr<b2World> mWorld;
    /// The component
    std::vector<std::shared_ptr<Component>> mComponents;
    /// The installed contact filter
    std::shared_ptr<ContactListener> mContactListener;
    /// How many pixels there are for each CM
    double mPixelsPerCentimeter = 1.5;
public:
    /**
     * Constructor
     * @param machine
     */
    Machine(int machine);

    /**
    * Set the position for the root of the machine
    * @param location X,Y location in pixels
    */
    void SetLocation(wxPoint location) { mX = location.x; mY = location.y; }

    /**
     * Get the root position of the machine
     * @return location x,y in pixels as a point
     */
    wxPoint GetLocation() {return wxPoint(mX, mY);}
    /**
     * Draw the machine
     * @param graphics
     */
    void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics);

    /**
    * Set the current machine animation frame
    * @param frame Frame number
    */
    void SetMachineFrame(int frame);

    /**
    * Set the machine number
    * @param machine An integer number. Each integer makes a different machine
    */
    void SetMachine(int machine) { mMachine = machine; }

    /**
    * Get the current machine number
    * @return Machine number
    */
    int GetMachine() { return mMachine; }

    /**
     * Add components to the machine
     * @param component
     */
    void AddComponent(std::shared_ptr<Component> component);
    /**
     * Draw the machine
     * @param graphics
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    /**
     * Update the machine through time
     * @param elapsed
     */
    void Update(double elapsed);
    /**
     * Reset the machine
     */
    void Reset();
    /**
     * Set the flag
     * @param flag
     */
    void SetFlag(int flag);


};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINE_H
