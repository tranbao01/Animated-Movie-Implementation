    /**
 * @file Goal.h
 * @author trang
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_GOAL_H
#define CANADIANEXPERIENCE_MACHINELIB_GOAL_H
#include "Component.h"
#include "PhysicsPolygon.h"
#include <b2_world_callbacks.h>
#include "ContactListener.h"
class PhysicsPolygon;
class Polygon;
/**
 * The Goal
 */
class Goal:public Component,public b2ContactListener
{
private:
    /// The polygon object for the goal image
    cse335::Polygon mPolygon;

    /// Physics polygon for the backboard/post
    cse335::PhysicsPolygon mPost;

    /// Polygon that we are going to hit to
    /// determine the basket has been scored
    cse335::PhysicsPolygon mGoal;
    ///Goal Position
    wxPoint2DDouble mPosition = wxPoint2DDouble(0,0);
    /// The score
    int mScore = 0;

public:
    /**
     * Constructor
     * @param imagesDir
     */
    Goal(std::wstring imagesDir);
    /**
     * Set initial position
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
     * Set the position
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
     * Get the body
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
     *
     */
    void BeginContact(b2Contact *contact) override;
    /**
     * Pre Solve
     *
     *
     */
    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold) override;
    /**
     * Add listener
     * @param listener
     */
    void AddListener(std::shared_ptr<ContactListener> listener) override;
};

#endif //CANADIANEXPERIENCE_MACHINELIB_GOAL_H
