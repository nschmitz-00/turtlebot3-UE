/**
 * @file RRTiagoROS2Interface.h
 * @author nschmitz
 */

#pragma once

#include "Robots//RRRobotROS2Interface.h"
#include "RRTiagoROS2InterfaceOld.generated.h"

UCLASS(ClassGroup = (Custom))
class RAPYUTASIMULATIONPLUGINS_API URRTiagoROS2InterfaceOld : public URRRobotROS2Interface
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
        bPublishJointTf = true;
        JointTfPublicationFrequencyHz = 30;
        bUseActorNameAsNamespace = false;
    };
};