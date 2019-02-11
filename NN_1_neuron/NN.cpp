#include <iostream>
#include <fstream>
#include "NN_defs.h"


int main() {


    int Train_set_size=8;
    float Error_tot_min = 0;

    //Neurons Define
    float learning_rate=0.2;
    float L_o_N_0_Ins[2] = {0,0};
    float L_o_N_0_Out[1];
    float Targets[1];
    float L_o_N_0_ErrN;
    float Error_NN_tot;
    Neuron Neuron(2,learning_rate,L_o_N_0_Ins,L_o_N_0_Out,&L_o_N_0_ErrN);
    //Iterations Define
    int cycles=100000;
    int point;
    //Starting Weights
    Neuron.GetWeights();
    std::cout<<std::endl;
    //Open Log File
    std::ofstream Log;
    Log.open("Log");
    if (!Log)
    {
        std::cerr << "Unable to open file 'Log'";
        exit(1);   // call system to stop
    }
    //Log File Header
    //      1    2  3  4    5   6   7      8          9       10      11
    Log<<"Iteracion W0 W1 Bias In1 In2 target Prediction Error_N Impulse Error"<<std::endl;

    //Neural Learning
    for(int f_cycle=0;f_cycle<=cycles;f_cycle++)
    {
        point=rand()% Train_set_size;
        Get_train_set_value("Train_set",point,2,L_o_N_0_Ins,1,Targets);
        //if (f_cycle < 1000)
        if (f_cycle % 100 == 0)
        {
            Error_NN_tot=0;
            for(int f_point=0;f_point<=Train_set_size-1;f_point++)
            {
                Get_train_set_value("Train_set",f_point,2,L_o_N_0_Ins,1,Targets);
                Neuron.think();
                Error_NN_tot = Error_NN_tot + Err(Targets[0],L_o_N_0_Out[0]);
                Log<<f_cycle<<" "<<Neuron.Weights[0]<<" "<<Neuron.Weights[1]<<" "<<Neuron.Bias<<" "<<Neuron.Ins[0]<<" "<<Neuron.Ins[1]<<" "<<Targets[0]<<" "<<*Neuron.Out<<" "<<L_o_N_0_ErrN<<" "<<Neuron.Impulse<<" "<<Error_NN_tot<<std::endl;
            }
            if (Error_NN_tot<Error_tot_min) {break;}
        }
        Neuron.Learn(Targets[0]);
    }
    Log.close();
    //Final Weights
    Neuron.GetWeights();
    std::cout<<std::endl;

    //Map Plotting
    std::ofstream Map;
    Map.open("Map");
    if (!Map)
    {
        std::cerr << "Unable to open file 'Map'";
        exit(1);   // call system to stop
    }
    Map<<"#X Y Z"<<std::endl;
    for(float f_point_x=-5;f_point_x<7;f_point_x=f_point_x+0.5)
    {
        for(float f_point_y=-5;f_point_y<7;f_point_y=f_point_y+0.5)
        {
            L_o_N_0_Ins[0]=f_point_x;
            L_o_N_0_Ins[1]=f_point_y;
            Neuron.think();
            Map<<f_point_x<<" "<<f_point_y<<" "<<L_o_N_0_Out[0]<<std::endl;
        }
    }
    Map.close();
    system("gnuplot -p 'plot_NN'");
    return 0;
}
