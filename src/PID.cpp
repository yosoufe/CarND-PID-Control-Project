#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {
	error_file = std::fopen("error","w");
	std::fclose(error_file);

	control_terms_file = std::fopen("control_terms","w");
	std::fclose(control_terms_file);

	gp_ = popen("gnuplot -persist" , "w");
}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
	this->Kp = Kp;
	this->Ki = Ki;
	this->Kd = Kd;
	p_error = 0;
	i_error = 0;
	d_error = 0;
	pre_error = 0;
}

void PID::UpdateError(double error) {
	p_error = error;
	i_error += error;
	d_error = error - pre_error;
	pre_error = error;

}

double PID::getControlCommand() {
	control = Kp * p_error + Ki * i_error + Kd * d_error;
	updateGraphFromFile();
	return control;
}

void PID::updateGraphFromFile(){
	error_file = std::fopen("error","a");
	if(error_file != NULL){
		std::string toWrite = std::to_string(p_error) + '\n'; // error
		std::fwrite(toWrite.c_str(),1,toWrite.length(),error_file);
		std::fclose(error_file);
	}

	control_terms_file = std::fopen("control_terms","a");
	if(control_terms_file != NULL){
		std::string toWrite = std::to_string(control) + ' ' + // control
				std::to_string(p_error * Kp) + ' ' +							// p_term
				std::to_string(i_error * Ki) + ' ' +							// i_term
				std::to_string(d_error * Kd) + '\n';							// d_term
		std::fwrite(toWrite.c_str(),1,toWrite.length(),control_terms_file);
		std::fclose(control_terms_file);
	}

	if (gp_!=NULL){
		fprintf(gp_ , "call '../plotScript.gp'\n");
		std::fflush(gp_);
	}
}
