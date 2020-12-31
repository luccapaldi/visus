// Luc Capaldi
// Visus, Draft 1

#include <iostream>
#include <vector>
#include <string>
#include <cmath>

// CLASSES:

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

  // Example Usage: Vector3d v2 = t - v1
  Vector3d operator-(double t)
  {
    return Vector3d((this->x) - t, (this->y) - t, (this->z) - t);
  }

  // Example Usage: Vector3d v2 = t + v1
  Vector3d operator+(double t)
  {
    return Vector3d((this->x) + t, (this->y) + t, (this->z) + t);
  }

  // Example Usage: Vector3d v2 = v1 * t
  Vector3d operator*(double t)
  {
    return Vector3d((this->x) * t, (this->y) * t, (this->z) * t);
  }

  // Example Usage: Vector3d v2 = v1/t
  Vector3d operator/(double t)
  {
    return Vector3d(this->x * (1/t), this->y * (1/t), this->z * (1/t));
  }

  // Function to write a single pixel to the standard ouput stream
  // Example Usage: ---
  void write_pixel()
  {
    const float MAX = 256.0;
    // Translate [0, 255] and write the RGB values
    std::cout << (MAX * this->x) << ' '    // r
              << (MAX * this->y) << ' '    // g
	      << (MAX * this->z) << '\n';  // b
  }
};

// Define type aliases for vec3
//using Point3d = Vector3d;  // 3D point
//using color = Vector3d;    // RGB color

class Ray : public Vector3d  // inherit from Vector3d class
{
private:
  Vector3d orig;
  Vector3d dir;
public:
  // CONSTRUCTORS
  inline Ray() { orig = Vector3d(), dir = Vector3d() ; }
  inline Ray(Vector3d orig_in, Vector3d dir_in) { orig = orig_in, dir = dir_in; }
  
  // DESTRUCTORS (no dynamic memory allocation
  //~Ray();

  // MODIFIERS (setters)
  inline void set_dirx(double xi) { dir.setx(xi); }
  inline void set_diry(double yi) { dir.sety(yi); }
  inline void set_dirz(double zi) { dir.setz(zi); }

  inline void set_origx(double xi) { orig.setx(xi); }
  inline void set_origy(double yi) { orig.sety(yi); }
  inline void set_origz(double zi) { orig.setz(zi); }

  // ACCESSORS (getters)
  inline double get_dirx() { return dir.getx(); }
  inline double get_diry() { return dir.gety(); }
  inline double get_dirz() { return dir.getz(); }

  inline double get_origx() { return orig.getx(); }
  inline double get_origy() { return orig.gety(); }
  inline double get_origz() { return orig.getz(); }

  inline Vector3d origin() { return orig; }
  inline Vector3d direction() {return dir; }

  // METHODS
  // Example Usage: p1 r1.at(5) // time = 5
  Vector3d at(double t)
  {
    return orig + (dir*t);
  }

  // Create color gradient from white to blue
  // blended_value = (1 - t) * start_value + t * end_value for 0 <= t <= 1
  Vector3d ray_color()
  {
    //std::cout << dir.unit().gety() << std::endl;
    double t = 0.5 * (dir.unit().gety() + 1.0);
    return (Vector3d(1.0, 1.0, 1.0) * (1.0 - t)) + (Vector3d(0.5, 0.7, 1.0) * t);
  }

};

// FUNCTIONS:

// store image in PPM format
void save_ppm(void)
{
  // Image (constants):
  const double aspect_ratio = 16.0 / 9.0;
  const int WIDTH = 400;
  const int HEIGHT = (int) (WIDTH / aspect_ratio);

  // Camera:
  double viewport_height = 2.0;
  double viewport_width = aspect_ratio * viewport_height;
  double focal_length = 1.0;

  // Set origin at (0, 0, 0)
  Vector3d origin = Vector3d(0, 0, 0);
  Vector3d horizontal = Vector3d(viewport_width, 0, 0);
  Vector3d vertical = Vector3d(0, viewport_width, 0);
  // define lower left corner
  Vector3d ll_corner = origin - (horizontal/2) - (vertical/2) - Vector3d(0, 0, focal_length);

  // Render:
  std::cout << "P3\n" << WIDTH << ' ' << HEIGHT << "\n255\n";
  for (int j = 0; j < HEIGHT; j++)
    {
      // output progress
      //std::cerr << "Lines remaining: " << HEIGHT-j << "\n" << std::flush;
      for (int i = 0; i < WIDTH; i++)
	{
	  // define a ray starting at the origin that points to each pixel in turn
	  double u = double (i) / WIDTH;
	  double v = double (j) / HEIGHT;
	  Vector3d dir = Vector3d(ll_corner + (horizontal * u) + (horizontal * v) - origin);
	  Ray r = Ray(origin, dir);

	  // color the background pixels 
	  Vector3d pixel_color = r.ray_color();
	  pixel_color.write_pixel();
	}
    }
  //std::cerr << "\nDone.\n";
};


int main(void)
{
  save_ppm();
  //std::cout << "Hello World!" << std::endl;
};



// Example vector operations:

// Instantiate two vectors
//Vector3d v1(1,2,3);
//Vector3d v2(4,5,6);
//std::cout << "v1: " << v1.asString() << std::endl;
//std::cout << "v2: " << v2.asString() << std::endl;
//
//// Dot and cross products
//double v12_dot = v1.dot(v2);
//Vector3d v3 = v1.cross(v2);
//Vector3d v4 = v2.cross(v1);
//std::cout << "v1 dot v2: " << v12_dot << std::endl;
//std::cout << "v1 cross v2: " << v3.asString() << std::endl;
//std::cout << "v2 cross v1: " << v4.asString() << std::endl;
//
//// Operator overload
//Vector3d v5 = v1 + v2;
//Vector3d v6 = v1 - v2;
//Vector3d v7 = 5 * v1
//std::cout << "v1 + v2 : " << v5.asString() << std::endl;
//std::cout << "v1 - v2 : " << v6.asString() << std::endl;
//std::cout << "5 * v1 : " << v7.asString() << std::endl;
//
//// Other common vector operations
//double v1n = v1.norm();
//Vector3d v9 = v1.unit();
//std::cout << "Norm of v1: " << v1n << std::endl;
//std::cout << "Unit of v1: " << v9.asString() << std::endl;
