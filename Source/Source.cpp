/*
============================
=Mandelbrot and Julia sets=
============================
Updated on Fri Aug 14 2020
@author : Ahmed Al-kharusi

The "olcPixelGameEngine.h" is a single header file that enables us to draw graphics.
This is created by javidx9 (OneLoneCoder). I used this and the example template provided
in his repo to draw the sandpile matrix.
please download it from his repo
https://github.com/OneLoneCoder/olcPixelGameEngine
*/

#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "Complex.h"
#include <iomanip>
#include <iostream>
#include <string>

void print_about();
std::string print_menu();
int mandelbrot(Complex& domain, unsigned int& range);
int julia(Complex zo, Complex& domain,unsigned int& range, double& r, unsigned int& n);

class JuliaSets : public olc::PixelGameEngine 
{public:
	JuliaSets() 
	{
		sAppName = "Julia Sets";
	}

private:
	Complex c3{ -0.70176,- 0.3842 };//initail Julia set parameter
	double x_start{ -2.0 };
	unsigned int range{ 100 };
	double r{2.0}; //convergence
	int colour_map = 0; 
	unsigned int mandelbrot_size = 700;
	double real_mouse_loc = 0;
	double im_mouse_loc = 0;
	unsigned int polynomial_power = 2;

public:	
	bool OnUserCreate() override
	{	
		DrawString(ScreenWidth() - 800, ScreenHeight() - 350, print_menu(), olc::WHITE, 2);
		//this plots the mandelbrot
		double x_start{ -2.0 };
		for (size_t i{ 0 };i < mandelbrot_size;i++) {
			x_start += 3.0 / mandelbrot_size;
			double y_start{ -1.5 };
			for (size_t j{ 0 };j < mandelbrot_size;j++) {
				y_start += 3.0 / mandelbrot_size;
				Complex temp{ x_start,y_start };
				if( mandelbrot(temp, range) == range)//change this for the Julia set
					Draw(i + ScreenWidth() - mandelbrot_size - 100, j + 100, olc::WHITE);
			}
		}

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{	
		if (GetKey(olc::Key::A).bHeld) print_about();

		if (GetKey(olc::Key::S).bHeld)
			r += 0.01;
		if (GetKey(olc::Key::D).bHeld)
			r -= 0.01;
		if (GetKey(olc::Key::X).bPressed) {
			if (polynomial_power >2)
				polynomial_power -= 1;
		}

		if (GetKey(olc::Key::Z).bPressed) {
			polynomial_power += 1;
		}
		if (GetMouse(0).bHeld) {
			//displays the location of the mouse with respect to the mandelbrot set
			real_mouse_loc = (static_cast<double>(GetMouseX()) - (1920 - mandelbrot_size / 2.0 - 100.0)) * (3.0 / mandelbrot_size) - 0.5;
			im_mouse_loc = (static_cast<double>(-GetMouseY()) + mandelbrot_size / 2 + 100.0) * (3.0 / mandelbrot_size);
			if(real_mouse_loc <= 1 && real_mouse_loc >= -2)
				c3.real = real_mouse_loc;
			if(im_mouse_loc <= 1.5 && im_mouse_loc >= -1.5)
				c3.imaginary = im_mouse_loc;
			
		}
		
		//Plots the julia set
		x_start = -2;
		for (size_t i{ 0 };i < ScreenHeight();i++) {
			x_start += (4.0)/ScreenHeight();
			double y_start{ 2 };
			for (size_t j{ 0 };j < ScreenHeight();j++) {
				y_start -= (4.0)/ ScreenHeight();
				Complex temp{ x_start,y_start };
				colour_map = julia(temp, c3, range, r, polynomial_power);
				
				//Colour map 
				switch (colour_map)
				{
				case 21:
					Draw(i, j, olc::Pixel(51,0,0));
					break;
				case 20:
					Draw(i, j, olc::Pixel(51, 25, 0));
					break;
				case 19:
					Draw(i,j,olc::Pixel(84,52,11));
					break;
				case 18:
					Draw(i,j, olc::Pixel(104, 64,11 ));
					break;
				case 17:
					Draw(i,j, olc::Pixel(201,137 ,53 ));
					break;
				case 16:
					Draw(i,j, olc::Pixel(196,172 ,123 ));
					break;
				case 15:
					Draw(i,j, olc::Pixel(206,188 ,150 ));
					break;
				case 14:
					Draw(i,j, olc::Pixel(186, 242,250 ));
					break;
				case 13:	
					Draw(i, j, olc::Pixel(135, 226, 240));
					break;
				case 12:
					Draw(i,j, olc::Pixel(78, 202,220 ));
					break;
				case 11:
					Draw(i,j, olc::Pixel(59, 171,188 ));
					break;
				case 10:
					Draw(i,j, olc::Pixel(165,103 ,206 ));
					break;
				case 9:
					Draw(i,j, olc::Pixel(141,76 ,183 ));
					break;
				case 8:
					Draw(i,j, olc::Pixel(116, 56, 156));
					break;
				case 7:
					Draw(i,j, olc::Pixel(121, 32, 181));
					break;
				case 6:
					Draw(i,j, olc::Pixel(120, 39, 175));
					break;
				case 5:
					Draw(i,j, olc::Pixel(99, 37, 230));
					break;
				case 4:
					Draw(i,j, olc::Pixel(94, 31, 240));
					break;
				case 3:
					Draw(i,j, olc::Pixel(51,51,255 ));
					break;
				case 2:
					Draw(i,j, olc::Pixel(0,0,152 ));
					break;
				case 1:
					Draw(i,j, olc::Pixel(0,0,102 ));
					break;
				case 0:
					Draw(i,j, olc::Pixel(0,0,51 ));
					break;
				default:
					Draw(i,j, olc::Pixel(0,0,0));
					break;

				}
					

			}

		}
		DrawString(10, 10, "C =" + std::to_string(c3.real) + " + i " + std::to_string(c3.imaginary) +"			" +" R = "+std::to_string(r) + "		Power of Z (N): "+std::to_string(polynomial_power), olc::WHITE, 2);

		return true;
		
	}
};
std::string print_menu() {
	std::ostringstream oss;
	oss << std::setw(15) << std::left << "SELECT A POINT IN THE "  << "\n\n"
		<< std::setw(15) << std::left << "MANDELBROT SET (MOUSE LEFT KEY)" << "\n\n"
		<< std::setw(45) << std::left << std::setfill('_') << "" << "\n\n" << std::setfill(' ')
		<< std::setw(45) << std::left << std::setfill('_') << "" << "\n\n" << std::setfill(' ')
		<< std::setw(15) << std::left << "MENU" << "| KEY (HOLD) " << "\n\n"
		<< std::setw(15) << std::left << std::setfill('_') << "" << "\n\n" << std::setfill(' ')
		<< std::setw(15) << std::left << "INCREASE N" << "| Z " 
		<< std::setw(15) << std::right << "DECREASE N" << "| X " << "\n\n"
		<< std::setw(15) << std::left << "INCREASE R" << "| S " 
		<< std::setw(15) << std::right << "DECREASE R" << "| D " << "\n\n"
		<< std::setw(15) << std::left << "ABOUT " << "| A " <<"  (SEE THE OTHER WINDOW)" <<"\n\n"
		<< std::setw(45) << std::left << std::setfill('_') << "" << "\n\n" << std::setfill(' ')
		<< std::endl;
	std::string str = oss.str();
	return str;
}

int main() {
	JuliaSets object;
	if (object.Construct(1920, 1080, 1, 1))
		object.Start();
	return 0;
}

int mandelbrot(Complex& domain, unsigned int& range) {
	Complex zo{ 0, 0 };
	Complex result{ 0,0 };
	for (size_t i{ 0 };i < range;i++) {
		result = (zo * zo) + domain;
		zo = result;

		double ans = result.re() * result.re() + result.im() * result.im();
		if (ans >= 4)
			return i;
	}
	return range;
}
int julia(Complex zo,  Complex& domain, unsigned int& range, double& r, unsigned int &n) {
	
	Complex result{ 0,0 };
	for (size_t i{ 0 };i < range;i++) {
		result = zo.power(n) + domain;
		zo = result;
		double ans = result.re() * result.re() + result.im() * result.im();
		
		if (ans >= r*r)
			return i;
	}

	return range;
}
void print_about() {
	std::cout << "\n\n=============================================================================\nJulia and Mandelbrot sets\n========================================================================================\nUpdated on Aug 14 2020\n@author: Ahmed Alkharusi\nI used the olcPixelGameEngine to generate the graphics.\nThe olcPixelGameEngine.h is a single header file that enables us to draw graphics.\nThis is created by javidx9(OneLoneCoder).\nplease download it from his repo\nhttps ://github.com/OneLoneCoder/olcPixelGameEngine " << std::endl;
}
