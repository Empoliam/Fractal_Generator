#include <iostream>
#include <complex>
#include <fstream>

using namespace std;

int main() {

	const double xCenter = -3.0 / 4.0 + 0.1;
	const double yCenter = 0.4;
	const double xSpan = 0.1;

	const double epsilon = 3;
	const int maxIter = 128*3; //Make multiple of 3 for good behaviour
	const int thirdIter = maxIter / 3;
	const double scale = thirdIter / 255.0;

	const int width = 720;
	const int height = 1280;

	double XDIV = xSpan / width;

	ofstream imageOut("mandel.ppm", ios_base::out);

	//header
	imageOut << "P3\n" << width << " " << height << "\n" << 255 << "\n";//imageOut << "P2\n" << width << " " << height << "\n" << 255 << "\n";

	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {

			double real = xCenter + (x - width / 2.0) * XDIV;
			double imag = yCenter - (y - height / 2.0) * XDIV;

			complex<double> z(0, 0);
			complex<double> c(real, imag);

			int iterations = 1;

			while (iterations < maxIter)
			{
				z = z * z + c;
				if (abs(z) > epsilon) break;
				iterations++;
			}

			int colOut = floor((int)((iterations % thirdIter) * scale));
			if (iterations == maxIter)
			{
				imageOut << 0 << " " << 0 << " " << 0 << " ";
			}
			else if (iterations > 2*thirdIter)
			{
				imageOut << 255 << " " << colOut << " " << 255 << " ";
			}
			else if (iterations > thirdIter)
			{
				imageOut << colOut << " " << 0 << " " << 255 << " ";
			}
			else
			{
				imageOut << 0 << " " << 0 << " " << colOut << " ";
			}
			

		}
		imageOut << "\n";
	}

	imageOut.close();


	return 0;

}