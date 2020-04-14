#ifndef PASER_H_
#define PARSER_H_

#include <sstream>
#include <fstream>
#include <math.h>
#include <vector>
#include "map.h"

using namespace std;

struct control {
  // The controls of a vehicle is defined by its velocity and yaw_rate about the z axis
  double velocity; // meter/sec
  double yawrate;  // rad/sec
};

struct landmark {
  // The landmark points is defined by its id, x coordinate and y coordinate
  int id;
  double x;   // x position [meter]
  double y;   // x position [meter]
};


struct ground_truth {

	double x;		  // Global vehicle x position [meter]
	double y;		  // Global vehicle y position [meter]
	double theta;	// Global vehicle yaw [rad]
};

// ------------------------------------------------------------------------
// Read Map Landmarks
// ------------------------------------------------------------------------
inline bool read_map_data(string filename, Map &map) {
  /*
  About the data:
    The map data has three columns
      1. x: the x position of the landmark in the map cartesian coordinate system
      2. y: the y position of the landmark in the map cartesian coordinate system
      3. id: the landmark id
  */
	// Get file of map:
	ifstream in_file_map(filename.c_str(), ifstream::in);
	// Return if we can't open the file.
	if (!in_file_map) {
		return false;
	}

	// Declare single line of map file:
	string line_map;

	// Run over each single line:
	while(getline(in_file_map, line_map)){

		istringstream iss_map(line_map);

		// Declare landmark values and ID:
		float landmark_x_f, landmark_y_f;
		int id_i;

		// Read data from current line to values::
		iss_map >> landmark_x_f;
		iss_map >> landmark_y_f;
		iss_map >> id_i;

		// Declare single_landmark:
		Map::single_landmark_s single_landmark_temp;

		// Set values
		single_landmark_temp.id_i = id_i;
		single_landmark_temp.x_f  = landmark_x_f;
		single_landmark_temp.y_f  = landmark_y_f;

		// Add to landmark list of map:
		map.landmark_list.push_back(single_landmark_temp);
	}
	return true;
}


// ------------------------------------------------------------------------
// Read Control Data
// ------------------------------------------------------------------------
inline bool read_control_data(string filename, vector<control>& control_meas) {
  /*
  About the data:
    The control data has three columns
      1. velocity: the velocity of the vehicle at time t
      2. yawrate: the turn angle about the z axis of the vehicle coordinate frame
  */
	// Get file of position measurements:
	ifstream in_file_pos(filename.c_str(), ifstream::in);
	// Return if we can't open the file.
	if (!in_file_pos) {
		return false;
	}

	// Declare single line of position measurement file:
	string line_pos;

	// Run over each single line:
	while(getline(in_file_pos, line_pos)){

		istringstream iss_pos(line_pos);

		// Declare position values:
		double velocity, yawrate;

		// Declare single control measurement:
		control meas;

		//read data from line to values:

		iss_pos >> velocity;
		iss_pos >> yawrate;


		// Set values
		meas.velocity = velocity;
		meas.yawrate = yawrate;

		// Add to list of control measurements:
		control_meas.push_back(meas);
	}
	return true;
}


// ------------------------------------------------------------------------
// Read GroundTruths
// ------------------------------------------------------------------------
inline bool read_gt_data(std::string filename, std::vector<ground_truth>& gt) {

	// Get file of position measurements:
	ifstream in_file_pos(filename.c_str(), ifstream::in);
	// Return if we can't open the file.
	if (!in_file_pos) {
		return false;
	}

	// Declare single line of position measurement file:
	string line_pos;

	// Run over each single line:
	while(getline(in_file_pos, line_pos)){

	istringstream iss_pos(line_pos);

		// Declare position values:
		double x, y, azimuth;

		// Declare single ground truth:
		ground_truth single_gt;

		//read data from line to values:
		iss_pos >> x;
		iss_pos >> y;
		iss_pos >> azimuth;

		// Set values
		single_gt.x = x;
		single_gt.y = y;
		single_gt.theta = azimuth;

		// Add to list of control measurements and ground truth:
		gt.push_back(single_gt);
	}
	return true;
}


#endif
