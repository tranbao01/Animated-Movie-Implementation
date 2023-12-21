/**
 * @file Hamster.h
 * @author trang
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_HAMSTER_H
#define CANADIANEXPERIENCE_MACHINELIB_HAMSTER_H
#include "Component.h"
#include "PhysicsPolygon.h"
#include "RotationSource.h"
#include "IRotationSource.h"
#include <b2_world_callbacks.h>
#include "ContactListener.h"
class RotationSource;
class PhysicsPolygon;
class Polygon;
/**
 * The hamster
 */
class Hamster:public Component,public b2ContactListener,public IRotationSource
{
private:
    /// The polygon object for the goal image
    std::vector<cse335::Polygon> mHamsters ;
    /// Hamster image 0
    cse335::Polygon mHamster0;
    /// Hamster image 1
    cse335::Polygon mHamster1;
    /// Hamster image 2
    cse335::Polygon mHamster2;
    /// Hamster image 3
    cse335::Polygon mHamster3;


    /// Physics polygon for the backboard/post
    cse335::Polygon mWheel;

    /// Polygon that we are going to hit to
    /// determine the basket has been scored
    cse335::PhysicsPolygon mCage;
    /// The position of the hamster cage
    wxPoint2DDouble mPosition;
    /// The rotation
    double mRotation = 0;
    /// The speed
    double mSpeed = 0;
    /// Initially running or not
    bool mIrun = false;
    /// Running or not
    bool mRun = false;
    /// Hamster state
    int mHamsterIndex = 0;
    /// Rotation source for this component
    RotationSource mSource;
    /// mX
    double mX =0;


public:
    /**
     * Constructor
     * @param imagesDir
     */
    Hamster(std::wstring imagesDir);
    /** Copy constructor disabled */
    Hamster(const Hamster &) = delete;
    /** Assignment operator disabled */
    void operator=(const Hamster &) = delete;
   /**
    * Set the initial position
    * @param x
    * @param y
    */
    void SetInitialPosition(double x, double y);
    /**
     * Draw the body
     * @param graphics
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    /**
     * Set the image
     * @param filename
     */
    void SetImage(std::wstring filename);
    /**
     * Set position
     * @param x
     * @param y
     */
    void SetPosition(double x,double y);


    /**
     * Install the physics
     * @param world
     */
    void InstallPhysics(std::shared_ptr<b2World> world) override;
    /**
     * Get the physics body
     * @return
     */
    b2Body* GetBody() override;
    /**
     * Set Machine
     * @param machine
     */
    void SetMachine(Machine* machine) override;
    /**
     * Update
     * @param elapsed
     */
    void Update(double elapsed) override;
    /**
     * Reset
     */
    void Reset() override;
    /**
     * Begin Contact
     * @param contact
     */
    void BeginContact(b2Contact *contact) override;
    /**
     * Pre solve
     * @param contact
     * @param oldManifold
     */
    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold) override;
    /**
     * Add listener
     * @param listener
     */
    void AddListener(std::shared_ptr<ContactListener> listener) override;
    /**
     * Set initially running
     * @param run
     */
    void SetInitiallyRunning(bool run);
    /**
     * Set speed
     * @param speed
     */
    void SetSpeed(double speed) {mSpeed = speed;};
    /**
     * Rotate source
     * @param rotation
     * @param speed
     */
    void RotateSource(double rotation,double speed) override;
    /**
 * Get a pointer to the source object
 * @return Pointer to RotationSource object
 */
    RotationSource *GetSource() { return &mSource; }
    /**
     * Add sink
     * @param component
     */
    void AddSink(std::shared_ptr<IRotationSink>  component);
    /**
     * Get shaft position
     * @return
     */
    wxPoint2DDouble GetShaftPosition();


};

#endif //CANADIANEXPERIENCE_MACHINELIB_HAMSTER_H
