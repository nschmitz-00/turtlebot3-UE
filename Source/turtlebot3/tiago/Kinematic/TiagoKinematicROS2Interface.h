/**
* @file TiagoKinematicROS2Interface.h
 * @author nschmitz
 */

#pragma once

#include "Robots//RRRobotROS2Interface.h"
#include "TiagoKinematicROS2Interface.generated.h"

UCLASS(ClassGroup = (Custom))
class RAPYUTASIMULATIONPLUGINS_API UTiagoKinematicROS2Interface : public URRRobotROS2Interface
{
    GENERATED_BODY()

protected:
    /**
     * @brief Init tiago's ros parameter and set to publish odom as topic and tf.
     *
     */
    void SetupROSParams() override
    {
        bPublishOdom = true;
        bPublishOdomTf = true;
        bPublishJointTf = false; //Use only if robot state publisher isnt used - idk why you should do that
        JointTfPublicationFrequencyHz = 50;
        OdomPublicationFrequencyHz = 50;
        bUseActorNameAsNamespace = false;
    };
};