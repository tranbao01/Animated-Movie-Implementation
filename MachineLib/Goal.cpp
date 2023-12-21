/**
 * @file Goal.cpp
 * @author trang
 */
#include "pch.h"
#include "Goal.h"
#include "ContactListener.h"
#include <b2_world_callbacks.h>
#include <b2_contact.h>
#include <sstream>
#include <iomanip>
/// Image to draw for the goal
const std::wstring GoalImage = L"/goal.png";

/// Size to draw the entire goal post image
/// This does not go into the physics system at all
const auto GoalSize = wxSize(65, 247);

/// Size to create a rectangle in the physics system only
/// (does not draw) to reflect off of the backboard and post
const auto PostSize = wxSize(10, 250);

/// Size of a target object inside the goal net that
/// we'll consider a score when touched by a ball
const auto TargetSize = wxSize(20, 5);

/// The color of the scoreboard background
const auto ScoreboardBackgroundColor = wxColor(24, 69, 59);

/// Width of the black line around the scoreboard
const int ScoreboarderLineWidth = 3;

/// Scoreboard font size (height) in cm
/// The font color is white
const int ScoreboardFontSize = 20;

/// Rectangle that represents the location relative to the
/// goal position for the scoreboard and its size.
const auto ScoreboardRectangle = wxRect2DDouble(5, 280, 30, 20);

/// Location of the scoreboard text relative to the
/// scoreboard location in cm.
const auto ScoreboardTextLocation = wxPoint2DDouble(9, 299);

/// Position of the goalpost polygon relative to the entire goal
/// This plus the location set by SetPosition is where to draw
/// the goalpost PhysicsPolygon object.
const wxPoint2DDouble PostPosition = wxPoint2DDouble(22, 0);

/// Position of the basket goal polygon relative to the entire goal
/// This plus the location set by SetPosition is where to draw
/// the goalpost PhysicsPolygon object.
const wxPoint2DDouble GoalPosition = wxPoint2DDouble(-12, 165);
void Goal::SetInitialPosition(double x, double y)
{
    mPost.SetInitialPosition(x,y);
    mGoal.SetInitialPosition(x,y);
}
void Goal::SetImage(std::wstring filename)
{
    mPost.SetImage(filename);
    mGoal.SetImage(filename);
}
void Goal::InstallPhysics(std::shared_ptr<b2World> world)
{
    mPost.InstallPhysics(world);
    mGoal.InstallPhysics(world);
}
void Goal::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
//    mPolygon.DrawPolygon(graphics, mPosition.m_x, mPosition.m_y, 0);

    double x = mPosition.m_x;
    double y = mPosition.m_y;

    // Brush and pen to draw the scoreboard
    wxBrush brush(ScoreboardBackgroundColor);
    graphics->SetBrush(brush);
    wxPen pen(*wxBLACK, ScoreboarderLineWidth);
    graphics->SetPen(pen);

    // Draw it
    graphics->DrawRectangle(x + ScoreboardRectangle.m_x, y + ScoreboardRectangle.m_y,
                            ScoreboardRectangle.m_width, ScoreboardRectangle.m_height);

    // Score to a string
    std::wstringstream score;
    score << std::setw(2) << std::setfill(L'0') << mScore << std::endl;

    // Font to draw the score
    wxFont font(wxSize(0, ScoreboardFontSize),
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_NORMAL);
    graphics->SetFont(font, *wxWHITE);

    // From the centimeter pixels page
    graphics->PushState();
    graphics->Translate(x + ScoreboardTextLocation.m_x, y + ScoreboardTextLocation.m_y);
    graphics->Scale(1, -1);
    graphics->DrawText(score.str(), 0, 0);
    graphics->PopState();
    graphics->PushState();
    graphics->Translate(mPosition.m_x-26 ,mPosition.m_y );
    mPolygon.DrawPolygon(graphics,0,0,0);
    graphics->PopState();

}
void Goal::Update(double elapsed)
{

}
void Goal::Reset()
{
    mScore = 0;
}
void Goal::SetMachine(Machine *machine)
{
    Component::SetMachine(machine);
}
Goal::Goal(std::wstring imagesDir)
{
    mPolygon.Rectangle(mPosition.m_x,mPosition.m_y,GoalSize.x,GoalSize.y);
    mGoal.Rectangle(mPosition.m_x+GoalPosition.m_x,mPosition.m_y+GoalPosition.m_y,TargetSize.x,TargetSize.y);
    mPost.Rectangle(mPosition.m_x+PostPosition.m_x,mPosition.m_y+PostPosition.m_y,PostSize.x,PostSize.y);
    mPolygon.SetImage(imagesDir+GoalImage);
}
b2Body *Goal::GetBody()
{
    return nullptr;
}
void Goal::SetPosition(double x, double y)
{
    mPosition = wxPoint(x,y);
    mPost.SetInitialPosition(x,y);
    mGoal.SetInitialPosition(x,y);
}
/**
 * Handle a contact beginning
 * @param contact Contact object
 */
void Goal::BeginContact(b2Contact *contact)
{
    mScore += 2;

}

/**
 * Handle before the solution of a contact with the
 * scoreboard target object. We take this time to
 * turn off the contact, so the ball will pass through.
 * @param contact Contqct object
 * @param oldManifold Manifold object
 */
void Goal::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
    contact->SetEnabled(false);
}
void Goal::AddListener(std::shared_ptr<ContactListener> listener)
{
    listener->Add(mGoal.GetBody(),this);
}
