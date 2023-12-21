/**
 * @file Pulley.h
 * @author trang
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_PULLEY_H
#define CANADIANEXPERIENCE_MACHINELIB_PULLEY_H
#include"Component.h"
#include "IRotationSink.h"
#include "IRotationSource.h"
#include "PhysicsPolygon.h"
#include "RotationSink.h"
#include "RotationSource.h"
class RotationSink;
class RotationSource;
class PhysicsPolygon;
/**
 * The pulley
 */
class Pulley:public Component,public IRotationSink,public IRotationSource
{
private:
    /// Polygon object
    cse335::Polygon mPolygon;
    /// The radius
    double mRadius = 0;
    /// The position
    wxPoint2DDouble mPosition = wxPoint2DDouble(0,0);
    /// The rotation sink
    RotationSink mSink;
    /// The rotation source
    RotationSource mSource;
    /// The rotation
    double mRotation = 0;
    /// The speed
    double mSpeed =0;
    /// If the speed have been set by another pulley
    bool mSetSpeedFlag = false;
    /// Belt1 startpoint
    wxPoint2DDouble mStartPoint1 =wxPoint2DDouble(0,0);
    /// Belt2 startpoint
    wxPoint2DDouble mStartPoint2 =wxPoint2DDouble(0,0);
    ///Belt1 endpoint
    wxPoint2DDouble mEndPoint1 = wxPoint2DDouble(0,0);
    /// Belt2 endpoint
    wxPoint2DDouble mEndPoint2 =wxPoint2DDouble(0,0);
    /// Whether to draw a belt
    bool mDrawbelt = false;
    /// Driven pulley
    std::shared_ptr<Pulley> mPulley = nullptr;
public:
    virtual ~Pulley() {}

    /** Copy constructor disabled */
    Pulley(const Pulley &) = delete;
    /** Assignment operator disabled */
    void operator=(const Pulley &) = delete;
    /**
     * Constructor
     * @param radius
     */
    Pulley(double radius);

    /**
     * Draw the component
     * @param graphics
     */
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    /**
     * Update the component through time
     * @param elapsed
     */
    void Update(double elapsed) override;
    /**
     * Reset the component
     */
    void Reset() override;
    /**
     * Set the machine
     * @param machine
     */
    void SetMachine(Machine *machine) override;
    /**
     * Install Physic
     * @param world
     */
    void InstallPhysics(std::shared_ptr<b2World> world) override;
    /**
     * Add listener
     * @param listener
     */
    void AddListener(std::shared_ptr<ContactListener> listener) override;
    /**
     * Get the center of the pulley
     * @return
     */
    wxPoint2DDouble GetCenter() {return mPosition;}
    /**
     * Get the body of the pulley
     * @return
     */
    b2Body* GetBody() override;
    /**
     * Set the position of the pulley
     * @param x
     * @param y
     */
    void SetPosition(double x,double y);
    /**
     * Set the image of the pulley
     * @param filename
     */
    void SetImage(std::wstring filename);
    /**
     * Rotate the source
     * @param rotation
     * @param speed
     */
    void RotateSource(double rotation,double speed) override;
    /**
     * Rotate the sink
     * @param rotation
     * @param speed
     */
    void Rotate(double rotation,double speed) override;
    /**
     * Add to the list of rotation sink
     * @param rs
     */
    void AddSink(std::shared_ptr<IRotationSink> rs) override;
    /**
     * Get the list of rotation sink of this pulley
     * @return
     */
    RotationSink *GetSink() {return &mSink;}
    /**
     * Drive another pulley
     * @param p
     */
    void Drive(std::shared_ptr<Pulley> p);
    /**
     * Get the source
     * @return
     */
    RotationSource *GetSource() {return &mSource;}
    /**
     * Get the radius
     * @return
     */
    double GetRadius() {return mRadius;}
    /**
     * Set the speed
     * @param speed
     */
    void SetSpeed(double speed);
    /**
     * Get the speed
     * @return
     */
    double GetSpeed() {return mSpeed;}
};

#endif //CANADIANEXPERIENCE_MACHINELIB_PULLEY_H
