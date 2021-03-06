#ifndef FUSIONEKF_H_
#define FUSIONEKF_H_

#include <iostream>
#include "Eigen/Dense"
#include "measurement_package.h"
#include "kalman_filter.h"
#include "tools.h"


class FusionEKF{
  private:
    bool is_initialized_;
    long long previous_timestamp_;
    Eigen::MatrixXd R_laser_;
    Eigen::MatrixXd R_radar_;
    Eigen::MatrixXd H_laser_;
    Eigen::MatrixXd H_radar_;

    // acceleration noise
    double noise_ax;
    double noise_ay;

    // Declare Prediction params
    Eigen::VectorXd x_;
    Eigen::MatrixXd F_;
    Eigen::MatrixXd P_;
    Eigen::MatrixXd Q_;


  public:
    // Create a constructor to store the default values
    FusionEKF();

    // Create a desctructor
    virtual ~FusionEKF();

    void ProcessMeasurement(const MeasurementPackage &meas_package_);

    KalmanFilter ekf_;
    Tools tools;

};

#endif
