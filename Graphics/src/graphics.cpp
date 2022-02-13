class Vector{
private:
  int x, y;
public:
  Vector(int x, int y){
    SetVector(x, y);
  }

  void SetX(int x){
    this->x=x;
  }
  void SetY(int y){
    this->y=y;
  }
  void SetVector(int x, int y){
    this->x=x; this->y=y;
  }
  int GetX(){
    return x;
  }
  int GetY(){
    return y;
  }

  Vector AddVector(Vector v){
    return Vector(x+v.GetX(), y+v.GetY());
  }
  Vector SubtractVector(Vector v){
    return Vector(x-v.GetX(), y-v.GetY());
  }
};

class Point{
private:
  int x, y;
public:
  Point(int x, int y){
    SetPoint(x, y);
  }

  void SetX(int x){
    this->x=x;
  }
  void SetY(int y){
    this->y=y;
  }
  void SetPoint(int x, int y){
    this->x=x; this->y=y;
  }
  int GetX(){
    return x;
  }
  int GetY(){
    return y;
  }

  Point AddVector(Vector v){

  }
  Point SubtractVector(Vector v){

  }
  Vector SubtractPoint(Point p){
    return Vector(x-p.GetX(), y-p.GetY());
  }

  void Draw(){

  }
};