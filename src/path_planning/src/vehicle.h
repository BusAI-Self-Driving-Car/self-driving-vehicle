#ifndef VEHICLE_H
#define VEHICLE_H
#include <vector>
#include <utility>

using std::vector;

class Vehicle {

public:
  vector<double> max_lane_velocity = {49.5/2.24, 49.5/2.24, 49.5/2.24}; // In meters/sec
  double curr_velocity = 0.2;
  double increment_velocity = 0.2;
  double sec_to_visit_next_point = 0.02; // how many seconds should the car take to visit the next point (px, py at t+1, when the car is at t)
  int target_trajectory_distance = 30; // meters that the car should look ahead for trajectory generation
  int target_trajectory_points = 50; // num of future points to generate in the trajectory

  double x_map;
  double y_map;
  double s_frn;
  double d_frn;
  double car_yaw;
  double car_speed;
  vector<double> waypoints_s_map;
  vector<double> waypoints_x_map;
  vector<double> waypoints_y_map;

  Vehicle() {};
  ~Vehicle() {};

  void setVehicle(
    double x,
    double y,
    double s,
    double d,
    double yaw,
    double speed,
    vector<double> map_waypoints_s,
    vector<double> map_waypoints_x,
    vector<double> map_waypoints_y
  );

  vector<vector<double>> generateTrajectory(
    vector<double> previous_path_x,
    vector<double> previous_path_y
    // auto previous_path_x,
    // auto previous_path_y
  );

  // vector<vector<double>> moveSmoothlyInOneLane();
};

#endif // VEHICLE_H
