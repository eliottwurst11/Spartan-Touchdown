/**
 * @file GoalpostVisitor.h
 * @author Nishit Nagpal
 *
 * Defines a visitor for a goalpost
 */

#ifndef GAME_GOALPOSTVISITOR_H
#define GAME_GOALPOSTVISITOR_H

#include "ItemVisitor.h"

/**
 * Visitor for a goalpost
 */
class GoalpostVisitor : public ItemVisitor {
private:

    /// the football we are matching the hit to the goalpost with
    std::shared_ptr<Football> mFootball;

    /// pointer to the hit goalpost
    Goalpost* mGoalpost = nullptr;

public:
    /**
     * construct this goalpost visitor
     * @param football pointer to the football we are comparing with
     */
    GoalpostVisitor(std::shared_ptr<Football> football) : mFootball(std::move(football)) {}

    /**
     * Getter for the Goalpost
     * @return Pointer to a Goalpost
     */
    Goalpost* GetGoalpost() const { return mGoalpost; }

    /**
     * Setter for the Goalpost
     * @param goalpost Goalpost to set
     */
    void SetGoalpost(Goalpost* goalpost) { mGoalpost = goalpost; }


    /**
     * Visit a Goalpost object
     * @param goalpost Goalpost to visit
     */
    void VisitGoalpost(Goalpost* goalpost) override;
};


#endif //GAME_GOALPOSTVISITOR_H
