//Ivan-Jago Coric
//Jana Christopher
//Stefan Koekkoek
//
//
#include "Neuron.h"

neuron::neuron(const vector<float>& WeightVector, const float& BiasNumber) //constructor 1
{
	setWeights(WeightVector); //gives provided parameters to the class
	setNumberOfInputs(Weights.size());
	setBias(BiasNumber);
}

neuron::neuron(const int& WeightVectorSize) //constructor 2
{
	setNumberOfInputs(WeightVectorSize);
	Weights.resize(WeightVectorSize);

	std::generate(Weights.begin(), Weights.end(), //generates random weights using algorithms and lambda function
		[&]() {
		return randomize(-1, 1);
	});

	Bias = randomize(-1, 1);
}


neuron::~neuron() //destructor
{
}

neuron::neuron(const neuron &Neuron1) //copy constructor
{
	Weights = Neuron1.Weights;
	Bias = Neuron1.Bias;
	Output = Neuron1.Output;
}

neuron& neuron::operator = (const neuron& Neuron1) //assignment operator
{
	if (&Neuron1 != this)
	{
		Weights = Neuron1.Weights;
		Bias = Neuron1.Bias;
		Output = Neuron1.Output;
	}
	return *this;
}

float neuron::randomize(const float& Minimum,const float& Maximum)
{
	random_device RandomDevice; //Initializes random engine
	mt19937 Generator(RandomDevice()); //Mersenne Twister 19937 generator, rng
	uniform_real_distribution<float> Distribution(Minimum, Maximum); //uniform probability distribution between Minimum and Maximum
	return Distribution(Generator); //Generate random weights
}

void neuron::setWeights(const vector<float>& WeightVector)
{
	Weights = WeightVector; //sets the weights

}

void neuron::setBias(const float& BiasNumber)
{
	Bias = BiasNumber; //sets the bias
}

void neuron::setNumberOfInputs(const int& InitNumberOfInputs)
{
	if (0 >= InitNumberOfInputs) //sets the number of inputs for the neurons
	{
		throw invalid_argument("setNumberOfInputs(): input must be a positive int greater than 0");
	}

	NumberOfInputs = InitNumberOfInputs;
}

vector<float> neuron::getWeights()
{
	return Weights; //returns the weights
}

float neuron::getBias()
{
	return Bias; //returns the bias
}


const int neuron::getNumberOfInputs()
{
	return NumberOfInputs; //returns the number of inputs for the neurons
}

void neuron::sigmoid(float& z)
{

	z = 1/ (1 + exp(-z)); // sigmoid function

}


float neuron::dsigmoid()
{
	return Output*(1 - Output);;
}


void neuron::activateFunc(const vector<float>& input)
{
	Output = 0;
	Output = std::inner_product(Weights.begin(), Weights.end(), input.begin(),-Bias) ; //std algorithm to calculate the inner product, i.e. sum of products

}

float neuron::resultFunc(const vector<float>& input) //calculates the output of a neuron
{
	activateFunc(input);
	sigmoid(Output);
    //return rounded values, value of Output remains unchanged so that dsigmoid keeps working
    //if Output >= 0.5, round to 1, otherwise to 0
    if(Output  >= 0.5){return  1; }
    else{ return 0;}
}
