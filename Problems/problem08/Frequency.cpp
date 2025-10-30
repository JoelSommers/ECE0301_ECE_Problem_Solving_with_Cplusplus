#include "Frequency.hpp"

#include <stdexcept>
#include <cmath>

// TODO: default constructor and constructor with args
Frequency::Frequency()
{
    num_components=301;
    increment=0.1;
    zeros();
}

Frequency::Frequency(int num, double i)
{
    if (num<0||num>MAX_COMPONENTS_NUM||i<=0){
        throw std::invalid_argument{"Invalid Arguement"};
    }
    num_components=num;
    increment=i;
}

// TODO: accessors
int Frequency::get_component() const
{
    return num_components;
}

double Frequency::get_increment() const
{
  return increment;
}

// provided: assign zero amplitudes to frequencies
void Frequency::zeros()
{
    for (int i = 0; i < num_components; i++)
    {
        freq_data[i].frequencies = static_cast<double>(i) * increment;
        freq_data[i].amplitudes = 0.0;
    }
}

// TODO: assign constant amplitudes to all frequencies
void Frequency::constant(double val)
{
    if (val<0){
        throw std::invalid_argument{"Invalid Arguement"};
    }

    for (int i = 0; i < num_components; i++)
    {
        freq_data[i].frequencies = static_cast<double>(i) * increment;
        freq_data[i].amplitudes = val;
    }
}

// TODO: gaussian build-up
void Frequency::Gaussian(double A, double alpha)
{
    if (A<=0||alpha<=0){
        throw std::invalid_argument{"Invalid Arguement"};
    }

    for (int i=0;i<num_components;i++){
        freq_data[i].frequencies = A*sqrt(M_PI/alpha)*exp(-(pow(i,2))/(4*alpha));
    }
    
}

bool Frequency::operator==(const Frequency &fcomp) const
{
    // TODO: overloaded operators
    return true;
}

// provided: exports
void Frequency::export_frequency(double freq[], double amps[]) const
{
    for (int i = 0; i < num_components; i++)
    {
        freq[i] = freq_data[i].frequencies;
        amps[i] = freq_data[i].amplitudes;
    }
}

bool Frequency::export_csv(const std::string &outfile) const
{
    std::ofstream filewrite(outfile + ".csv");
    if (!filewrite.fail())
    {
        filewrite << "w, |F(w)|" << std::endl;
        for (int i = 0; i < num_components; i++)
        {
            filewrite << freq_data[i].frequencies << ", " << freq_data[i].amplitudes << std::endl;
        }
        // Close file
        filewrite.close();
        return true;
    }
    return false;
}