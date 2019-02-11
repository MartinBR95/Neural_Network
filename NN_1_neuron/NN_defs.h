#pragma once
#include "iostream"
#include <iomanip>

float Sigmoid(float In);
float dSigmoid(float In);
double Err(float Prediction, float Target);
float dErr(float Prediction, float Target);
void Train(int &neuron,float target);
void Get_train_set_value(std::string File,int Value,int NumIns,float *In_values,int NumOuts,float *Out_values);

class Neuron
{
    public:
    int NumIns;
    float *Ins;
    float *Weights;
    float Bias;
    float Impulse = 0;
    float *Out;
    float Learning_rate = 0.1;

    float *Error_N;
    Neuron(int numIns,float learning_rate,float *ins, float *out,float *error_n)
    {
         Learning_rate = learning_rate;
         Ins           = ins;
         NumIns        = numIns;
         Weights       = new float[NumIns];
         srand (time(NULL));
         Bias          = (float)((rand()%100)-50)/5;
         Out           = out;
         *Out          = 0;
         Error_N       = error_n;
         for (int f_w = 0; f_w <= numIns-1; f_w++)
         {
             Weights[f_w]  = (float)((rand()%100)-50)/5;
         }
     }
     void GetWeights()
     {
         std::cout<<"W0: " << Weights[0];
         for (int f_w = 1; f_w <= NumIns-1; f_w++)
         {
             std::cout<<", W"<< f_w<< ": " << Weights[f_w];
         }
         std::cout<<", Bias: "<< Bias;
     }

     void think()
     {
         Impulse = Bias;
         for (int f_in =0;f_in <= NumIns-1;f_in++)
         {
             Impulse = Impulse + Weights[f_in]*Ins[f_in];
         }

         *Out = Sigmoid(Impulse);
     }

     void Calc_Err_N_last_layer (float target)
     {
         *Error_N = dErr(target,*Out)*dSigmoid(Impulse);
     }

     void Calc_Err_N_Backpropagation (int num_n_next,float *Errors_N_next,float *Ws_N_next)
     {
         for (int f_n_next = 0; f_n_next <= num_n_next-1; f_n_next++)
         {
             *Error_N = *Error_N + Errors_N_next[f_n_next]*Ws_N_next[f_n_next];
         }
         *Error_N = *Error_N * dSigmoid(Impulse);
     }

     void Learn (float target)
     {
         think();
         Calc_Err_N_last_layer(target);

         for (int f_w = 0; f_w <= NumIns-1; f_w++)
         {
             Weights[f_w]=Weights[f_w]-Learning_rate*(*Error_N)*Ins[f_w];
         }
         Bias = Bias-Learning_rate* (*Error_N);
     }
};
