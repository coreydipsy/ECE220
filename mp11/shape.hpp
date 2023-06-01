// kaiyiyu2, ayu39, kothary3
//This is a program that gets the input from a text file, 
//create the objects in the file, 
//and output the max area and max volume



#ifndef SHAPE_H_
#define SHAPE_H_

#include<iostream>
#include<cmath>
#include<string>
#include<algorithm>
#include<list>
#include<fstream>
#include<iomanip>    

using namespace std;

//Base class
//Please implement Shape's member functions
//constructor, getName()
class Shape{
public:
	//Base class' constructor should be called in derived classes'
	//constructor to initizlize Shape's private variable 
  	Shape(string name) {
		name_ = name;//store the argument name in the variable
		
	}
	
  	string getName() {
		return name_;//helper function to get private variable

	}
	
  	virtual double getArea() const = 0;
  	virtual double getVolume() const = 0;
	
private:
  string name_;


};

//Rectangle
//Please implement the member functions of Rectangle:
//constructor, getArea(), getVolume(), operator+, operator-

template <class T>
class Rectangle : public Shape{
public:
  	Rectangle<T>(T width = 0, T length = 0):Shape("Rectangle") {
		width_ = width;//not sure if I put a T in front, no, i wouldn't put a int in front in this case
		length_ = length;


	}
	
  	double getArea() const {
		return (double) length_ * width_; //caculate area

	}
	
  	double getVolume() const {//caculate volume
		return 0;

	}
	
	Rectangle<T> operator + (const Rectangle<T>& rec) {//define operators
		T add_rec_width = width_ + rec.getWidth();
		T add_rec_length = length_ + rec.getLength();
		Rectangle<T>* add_rec = new Rectangle(add_rec_width,add_rec_length);
		return *add_rec;

		


	}
	
	Rectangle<T> operator - (const Rectangle<T>& rec) {//define operators
		T sub_rec_width = width_ - rec.getWidth();
		T sub_rec_length = length_ - rec.getLength();
		if(sub_rec_width <= 0){
			if(sub_rec_length <= 0){
				Rectangle<T>* sub_rec = new Rectangle(0,0);
				return *sub_rec;
			}
			Rectangle<T>* sub_rec = new Rectangle(0,sub_rec_length);
			return *sub_rec;
		}else{
			if(sub_rec_length <= 0){
				Rectangle<T>* sub_rec = new Rectangle(sub_rec_width,0);
				return *sub_rec;
			}
			Rectangle<T>* sub_rec = new Rectangle(sub_rec_width,sub_rec_length);
			return *sub_rec;
		}

	} 
	
	T getWidth() const { 
		return width_;//helper function to get private variable

	}
	
	T getLength() const { 
		return length_;//helper function to get private variable

	}
private:
	T width_;
        T length_;

};

//Circle
//Please implement the member functions of Circle:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Circle : public Shape{
public:
  	Circle(double radius):Shape("Circle") {
		radius_ = radius;
	}
	
  	double getArea() const{
		return (double)radius_ * radius_ * M_PI;//caculate area

	}
	
 	double getVolume() const{//caculate volume
		return 0;

	}
	
  	Circle operator + (const Circle& cir){//define operators
		double cir_add_radius = radius_ + cir.getRadius();
		Circle* add_cir = new Circle (cir_add_radius);
		return *add_cir;
		
	}
	
	Circle operator - (const Circle& cir){//define operators
		double cir_sub_radius = radius_ - cir.getRadius();
		if(cir_sub_radius > 0){
			Circle* sub_cir = new Circle (cir_sub_radius);
			return *sub_cir;
		}
		Circle* sub_cir = new Circle (0);
		return *sub_cir;
	} 

	double getRadius() const { 
		return radius_;//helper function to get private variable

	}
	
private:
	double radius_;

};



//Sphere
//Please implement the member functions of Sphere:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here

class Sphere : public Shape{
public:
  	Sphere(double radius):Shape("Sphere") {
		radius_ = radius;

	}

  	double getVolume() const {//caculate volume
		return (double)(4.0/3.0) * radius_ * radius_ * radius_ * M_PI;

	}	
	
  	double getArea() const {
		return (double)4 * radius_ * radius_ * M_PI;//caculate area

	}

	Sphere operator + (const Sphere& sph) {//define operators
		double sph_add_radius = radius_ + sph.getRadius();
		Sphere* add_sph = new Sphere(sph_add_radius);
		return *add_sph;

	}

	Sphere operator - (const Sphere& sph) {//define operators
		double sph_sub_radius = radius_ - sph.getRadius();
		if(sph_sub_radius>0){
			Sphere* sub_sph = new Sphere(sph_sub_radius);
			return *sub_sph;
		}
		Sphere* sub_sph = new Sphere(0);
		return *sub_sph;


	} 
	
	double getRadius() const {
		return radius_;//helper function to get private variable

	}

private:
	double radius_;

};

//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
class RectPrism : public Shape{
public:
  	RectPrism(double width, double length, double height):Shape("RectPrism") {
		length_ = length;
		width_ = width;
		height_ = height;
	}
	
  	double getVolume() const {//caculate volume
		return (double)length_ * width_ * height_;

	}
  	
	double getArea() const {
		return (double)2 * (length_ * width_ + length_ * height_ + width_ * height_);//caculate area

	}
	
	RectPrism operator + (const RectPrism& rectp){//define operators
		double pri_add_length = length_ + rectp.getLength();
		double pri_add_width = width_ +  rectp.getWidth();
		double pri_add_height = height_ + rectp.getHeight();
		RectPrism* add_pri = new RectPrism(pri_add_width,pri_add_length,pri_add_height);
		return *add_pri;

	}
	
	RectPrism operator - (const RectPrism& rectp){//define operators
		double pri_sub_length = length_ - rectp.getLength();
		double pri_sub_width = width_ -  rectp.getWidth();
		double pri_sub_height = height_ - rectp.getHeight();

		if(pri_sub_length<0){
			pri_sub_length = 0;
		}
		if(pri_sub_width<0){
			pri_sub_width = 0;
		}
		if(pri_sub_height<0){
			pri_sub_height = 0;
		}
		RectPrism* sub_pri = new RectPrism(pri_sub_width,pri_sub_length,pri_sub_height);
		return *sub_pri;


	}	
	
	double getWidth() const { 
		return width_;//helper function to get private variable

	}
	
	double getLength() const { 
		return length_;//helper function to get private variable

	}
	
	double getHeight() const { 
		return height_;//helper function to get private variable

	}
  
private:
  	double length_;
  	double width_;
  	double height_;

};

// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects 
static list<Shape*> CreateShapes(char* file_name) {

	list<Shape*> shape_ptr_list;
	
	int count;
	string name;
	ifstream ifs (file_name, std::ifstream::in);//create input
	ifs >> count;//store text input into variables
	
	for(int i = 0; i<count; i++){//loop through every element
		//if name = what is in the file
		ifs >> name; 
		if(name == "Rectangle"){
			double rec_width;
			double rec_length;
			ifs >> rec_width >> rec_length;
			Shape* new_rect = new Rectangle<double>(rec_width,rec_length);
			shape_ptr_list.push_back(new_rect);
		}
		if(name == "Circle"){
			double cir_radius;
			ifs>> cir_radius;
			Shape* new_cir = new Circle(cir_radius);
			shape_ptr_list.push_back(new_cir);
			
		}
		if(name == "Sphere"){
			double sph_radius;
			ifs >> sph_radius;
			Shape* new_sph = new Sphere(sph_radius);
			shape_ptr_list.push_back(new_sph);
		}
		if(name == "RectPrism"){
			double pri_length;
			double pri_width;
			double pri_height;
			ifs >> pri_width >> pri_length >> pri_height;
			Shape* new_pri = new RectPrism(pri_width,pri_length,pri_height);
			shape_ptr_list.push_back(new_pri);
		}

	}
	

	ifs.close();


	return shape_ptr_list;
}

// call getArea() of each object 
// return the max area
static double MaxArea(list<Shape*> shapes){
	double max_area = 0;
	//use iterator to go through evey element and output the max value
	for (list<Shape*>::iterator it = shapes.begin(); it != shapes.end(); it++) {
		if((*it)->getArea() > max_area){//dereference it twice since itself is a pointer and the list contains pointers, deref twice to get val
			max_area = (*it)->getArea();
		}
	}

	return max_area;
}

// call getVolume() of each object 
// return the max volume
static double MaxVolume(list<Shape*> shapes){
	double max_volume = 0;
	//use iterator to go through evey element and output the max value
	for (list<Shape*>::iterator it = shapes.begin(); it != shapes.end(); it++) {
		if((*it)->getVolume() > max_volume){//dereference it twice since itself is a pointer and the list contains pointers, deref twice to get val
			max_volume = (*it)->getVolume();
		}
	}

	return max_volume;
}
#endif

