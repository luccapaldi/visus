// Luc Capaldi
// Visus

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

// store image in PPM format
void save_ppm(void)
{
 // define image constants
 const int WIDTH = 256;
 const int HEIGHT = 256;
 const float INTENSITY = 256.0;

 // write formatting information to program output
 //std::cout << "P3\n" << WIDTH << ' ' << HEIGHT << "\n255\n"; 
 // iterate over each pixel (left to right, top to bottom)
 for (int i = 0; i < HEIGHT; i++)
   {
     std::cerr << "Lines remaining: " << HEIGHT-i << "\n" << std::flush;
     // output progress
     for (int j = 0; j < WIDTH; j++)
       {
	 // calculate pixel intensity
	 float r= ((double) i / HEIGHT) * INTENSITY;
         float g = ((double) j / WIDTH) * INTENSITY;
         float b = 0.25 * INTENSITY;

         // write info to program output
         std:: cout << r << ' ' << g << ' ' << b << '\n';
       }
   }
 std::cerr << "\nDone.\n";
};

// 3D Vector class 
class Vector3d
{
private:
  double x, y, z;
public:
  // CONSTRUCTORS
  // Example Usage: Vector3d v1(1,2,3);
  inline Vector3d() { x = 0, y = 0, z = 0; }
  inline Vector3d(double xi, double yi, double zi) { x = xi, y = yi, z = zi; }
  
  // DESTRUCTORS (no dynamic memory allocation)
  //~Vector3d();

  // MODIFIERS (setters)
  inline void setx(double xi) { x = xi; }
  inline void sety(double yi) { y = yi; }
  inline void setz(double zi) { z = zi; }

  // ACCESSORS (getters)
  inline double getx() { return x; }
  inline double gety() { return y; }
  inline double getz() { return z; }

  // METHODS 
  // Example Usage: v1.asString() 
  const std::string asString()
  {
    return "<" + std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ">";
  }

  // Example Usage: Vector3d v2 = v1.scale(5)
  Vector3d scale(double c)
  {
    return Vector3d(this->x * c, this->y * c, this->z * c);
  }

  // Example Usage: double n = v1.norm()
  double norm(void)
  {
    double xn = (this->x) * (this->x);
    double yn = (this->y) * (this->y);
    double zn = (this->z) * (this->z);
    return sqrt(xn + yn + zn);
  }

  // Example Usage: Vector3d v2 = v1.unit()
  Vector3d unit()
  {
    double xn = (this->x) * (this->x);
    double yn = (this->y) * (this->y);
    double zn = (this->z) * (this->z);
    double mag = sqrt(xn + yn + zn);
    return Vector3d((this->x)/mag, (this->y)/mag, (this->z)/mag);
  }
  
  // Example Usage: double v3 = v1.dot(v2)
  double dot(Vector3d b)
  {
    return (this->x * b.getx()) + (this->y * b.gety()) + (this->z * b.getz());
  }

  // Example Usage: Vector3d v3 = v1.cross(v2)
  Vector3d cross(Vector3d b)
  {
    double xc = (this->y * b.getz()) - (this->z * b.gety());
    double yc = -((this->x * b.getz()) - (this->z * b.getx()));
    double zc = (this->x * b.gety()) - (this->y * b.getx());
    return Vector3d(xc, yc, zc);
  }

  // OPERATOR OVERLOADING
  // Example Usage: Vector3d v3 = v1 + v2
  Vector3d operator+(Vector3d b)
  {
    double xa = this->x + b.getx();
    double ya = this->y + b.gety();
    double za = this->z + b.getz();
    return Vector3d(xa, ya, za);
  }

  // Example Usage: Vector3d v3 = v1 - v2
  Vector3d operator-(Vector3d b)
  {
    double xs = this->x - b.getx();
    double ys = this->y - b.gety();
    double zs = this->z - b.getz();
    return Vector3d(xs, ys, zs);
  }
};

int main(void)
{
  // Instantiate two vectors
  Vector3d v1(1,2,3);
  Vector3d v2(4,5,6);
  std::cout << "v1: " << v1.asString() << std::endl;
  std::cout << "v2: " << v2.asString() << std::endl;

  // Dot and cross products
  double v12_dot = v1.dot(v2);
  Vector3d v3 = v1.cross(v2);
  Vector3d v4 = v2.cross(v1);
  std::cout << "v1 dot v2: " << v12_dot << std::endl;
  std::cout << "v1 cross v2: " << v3.asString() << std::endl;
  std::cout << "v2 cross v1: " << v4.asString() << std::endl;

  // Operator overload
  Vector3d v5 = v1 + v2;
  Vector3d v6 = v1 - v2;
  std::cout << "v1 + v2 : " << v5.asString() << std::endl;
  std::cout << "v1 - v2 : " << v6.asString() << std::endl;

  // Other common vector operations
  Vector3d v7 = v1.scale(5);
  double v1n = v1.norm();
  Vector3d v9 = v1.unit();
  std::cout << "5*v1 : " << v7.asString() << std::endl;
  std::cout << "Norm of v1: " << v1n << std::endl;
  std::cout << "Unit of v1: " << v9.asString() << std::endl;
};
