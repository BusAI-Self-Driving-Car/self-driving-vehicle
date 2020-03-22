#ifndef FUSION_EKF_H
#define FUSION_EKF_H

#include <iostream>
#include "Eigen/Dense"
#include "measurement_package.h"

class FusionEKF{
  private:
    long long previous_timestamp_;
    Eigen::MatrixXd R_laser_;
    Eigen::MatrixXd R_radar_;
    Eigen::MatrixXd H_laser_;

  public:
    // Create a constructor to store the default values
    FusionEKF();

    // Create a desctructor
    virtual ~FusionEKF();

    void ProcessMeasurement(const MeasurementPackage &meas_package_);

};

#endif