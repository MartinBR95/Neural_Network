#include "cmath"
#include "iostream"
#include <fstream>
#include <iomanip>
#include "NN_defs.h"

float Sigmoid(float In)
{
    return 1/(1+exp(-In));
}

float dSigmoid(float In)
{
    return Sigmoid(In)*(1-Sigmoid(In));
}

double Err(float target, float prediction)
{
    return pow(target-prediction,2)/2;
}

float dErr(float target, float prediction)
{
    return (target-prediction)*-1;
}

double Error_NN (int numOuts,float *outs,float *targets)
{
    double Error_NN = 0;
    for (int f_outs = 0; f_outs <= numOuts -1 ; f_outs++)
    {
        Error_NN = Error_NN + Err(targets[f_outs],outs[f_outs]);
    }
    return Error_NN;
}

void Get_train_set_value(std::string File,int Value,int NumIns,float *In_values,int NumOuts,float *Out_values)
{

    std::ifstream Train_set_file;
    Train_set_file.open(File);
    if (!Train_set_file)
    {
        std::cerr << "Unable to open file '"<<File<<"'";
        exit(1);   // call system to stop
    }
    std::string Line;
    int Line_cntr=0;
    while (std::getline(Train_set_file, Line))
    {
        Line_cntr=Line_cntr+1;
        if (Line_cntr == Value)
        {
            //std::cout<<"Processing: "<<Line<<std::endl;
            for(int f_ins=0;f_ins<=NumIns-1;f_ins++)
            {
                In_values[f_ins] = stof(Line.substr(0, Line.find_first_of(" ,")));
                //std::cout<<"In_values["<<f_ins<<"]= "<<In_values[f_ins]<<std::endl;
                Line.erase(0, Line.find_first_of(" ,")+1);
            }
            for(int f_outs=0;f_outs<=NumOuts-1;f_outs++)
            {
                Out_values[f_outs] = stof(Line.substr(0, Line.find_first_of(" ,")));
                //std::cout<<"Out_values["<<f_outs<<"]= "<<Out_values[f_outs]<<std::endl;
                Line.erase(0, Line.find_first_of(" ,")+1);
            }
        }
    }
}
