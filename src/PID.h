#ifndef PID_H
#define PID_H

#include <iostream>
#include <math.h>
#include <vector>

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;
	double pre_error;

	int d_bufer_size_;
	double *d_buffer;
	double d_sum;
	int d_idx;

	bool isFirstUpdate = true;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;
	double control;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
	void Init(double Kp, double Ki, double Kd, int d_buf_size);

  /*
  * Update the PID error variables given cross track error.
  */
	void UpdateError(double error);

  /*
  * Calculate the total PID error.
  */
	double getControlCommand();
private:
#ifdef WITH_GNUPLOT
	FILE *error_file;
	FILE *control_terms_file;
	FILE *gp_;
	void updateGraphFromFile();
#endif
};

#endif /* PID_H */
