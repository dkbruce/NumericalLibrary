#include <iostream>
#include <vector>
#include <math.h>


double dot(std::vector<double> x, std::vector<double> y)
{
	double sum = 0;
	for (int i = 0; i < x.size(); ++i)
	{
		sum += x[i] * y[i];
	}
	return sum;
}

double lpNorm(std::vector<double> x, double p = 2)
{
	double sum = 0;
	for (int i = 0; i < x.size(); ++i)
	{
		sum += pow(abs(x[i]), p);
	}
	return pow(sum, 1 / p);
}

std::vector<double> scalarMult(float scal, std::vector<double> vec)
{
	std::vector<double> output;
	output.reserve(vec.size());
	for (int i = 0; i < vec.size(); ++i)
	{
		output.push_back(scal * vec[i]);
	}
	return output;
}

std::vector<double> vectorAdd(std::vector<double> x, std::vector<double> y)
{
	std::vector<double> output;
	output.reserve(x.size());
	for (int i = 0; i < x.size(); ++i)
	{
		output.push_back(x[i] + y[i]);
	}
	return output;
}

std::vector<double> gradientDescent(
	double (*f)(std::vector<double>),
	std::vector<double>(*gradf)(std::vector<double>),
	std::vector<double> init_pos,
	double step = 3e-2,
	double epsilon = 1e-5,
	bool verbose = true
)
{
	double difference = HUGE_VAL;
	std::vector<double> x = init_pos;
	double before, after = 0;
	unsigned int step_num = 0;

	while (difference > epsilon)
	{
		before = f(x);
		x = vectorAdd(x, scalarMult(-1, scalarMult(step, gradf(x))));
		after = f(x);
		difference = abs(after - before);
		step_num += 1;
		if (verbose)
		{
			std::cout << "Step number: " << step_num << " function value: " << after << std::endl;
		}
	}

	if (f(x) == INFINITY || f(x) == -INFINITY)
	{
		std::cout << "ERROR: function value is infinite. f may be nonconvex." << std::endl;
		return std::vector<double> {};
	}

	std::cout << "Optimizer: ";
	for (int i = 0; i < x.size(); ++i)
	{
		std::cout << x.at(i) << " ";
	}
	std::cout << std::endl;
	std::cout << "Optimal value: " << f(x) << std::endl;
	return x;
}

double f(std::vector<double> input)
{
	return pow(input[0], 2) + pow(input[1], 4);
}

std::vector<double> gradf(std::vector<double> input)
{
	return { 2 * input[0], 4 * pow(input[1], 3) };
}

int main()
{
	std::vector<double> optimizer = gradientDescent(f, gradf, { 2, 2 });

	return 0;
}