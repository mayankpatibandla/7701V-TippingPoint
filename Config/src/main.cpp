#include "vex.h"
#include <vector>
#include <fstream>

using namespace vex;
using namespace std;

int fontToInt(fontType font){
  switch(font){
    case fontType::mono12:  return 12;
    case fontType::mono15:  return 15;
    case fontType::mono20:  return 20;
    case fontType::mono30:  return 30;
    case fontType::mono40:  return 40;
    case fontType::mono60:  return 60;
    case fontType::prop20:  return 20;
    case fontType::prop30:  return 30;
    case fontType::prop40:  return 40;
    case fontType::prop60:  return 60;
    case fontType::cjk16:   return 16;
  }
}

struct Toggle{
  int x, y;
  string text;
};

struct Button{
  int x, y, width, height;
  string text;
  color text_color;
  color bg_color;
  fontType font;
};

struct MultiButton{
  int x, y, width, height;
  int size, state;
  vector<string> text;
  vector<color> text_color;
  vector<color> bg_color;
  fontType font;
public:
  void setState(int newState){
    if(newState < 0){state = size-1; return;}
    state = newState > size-1 ? 0 : newState;
  }
};

struct Slider{
  int x, y, width, height;
  int min, max, step;
  color text_color;
  color bg_color;
};

struct Menu{
  int id;
  vector<Button> buttons;
  vector<Toggle> toggles;
  vector<MultiButton> multiButtons;
  vector<Slider> sliders;
  int rowSize;
  Menu(int id, vector<Button> buttons = {}, vector<Toggle> toggles = {}, vector<MultiButton> multiButtons = {}, vector<Slider> sliders = {}, int rowSize=4):
    id(id), buttons(buttons), toggles(toggles), multiButtons(multiButtons), sliders(sliders), rowSize(rowSize)
  {}
private:
  int currentSelection = 0;
public:
  int getCurrentSelection(){return currentSelection;}
  void setCurrentSelection(int newSelection){
    if(buttons.size() != 0){
      if(newSelection < 0){currentSelection = 0; return;}
      currentSelection = newSelection > buttons.size()-1 ? buttons.size()-1 : newSelection;
    }
    else if(multiButtons.size() != 0){
      if(newSelection < 0){currentSelection = 0; return;}
      currentSelection = newSelection > multiButtons.size()-1 ? multiButtons.size()-1 : newSelection;
    }
  }
};

vector<MultiButton> mainMenuButtons = {
  {
    0, 0, 120, 120, 5, 0,
    {"Red", "Blue", "Skills", "Test", "None"},
    {color(255, 255, 255), color(255, 255, 255), color(255, 255, 255), color(255, 255, 255), color(255, 255, 255)},
    {color(255, 0, 0), color(0, 0, 255), color(27, 62, 89), color(7, 94, 7), color(28, 27, 3)},
    mono20
  },
  {
    120, 0, 120, 120, 2, 0, 
    {"Left", "Right"},
    {color(255, 255, 255), color(255, 255, 255)},
    {color(66, 15, 23), color(10, 76, 84)},
    mono20
  },
  {
    240, 0, 120, 120, 2, 0, 
    {"AWP", "Neutral"},
    {color(255, 255, 255), color(255, 255, 255)},
    {color(66, 15, 23), color(10, 76, 84)},
    mono20
  },
  {
    360, 0, 120, 120, 2, 0, 
    {"Main", "Other"},
    {color(255, 255, 255), color(255, 255, 255)},
    {color(66, 15, 23), color(10, 76, 84)},
    mono20
  },
  {
    0, 120, 120, 120, 1, 0,
    {"SAVE [X]"},
    {color(255, 255, 255)},
    {color(10, 61, 35)},
    mono20
  }
};

Menu autonSelectMenu = Menu(0, {}, {}, mainMenuButtons);

void drawMenu(Menu& menu){
  //buttons
  for(int i=0; i<menu.buttons.size(); i++){
    if(menu.getCurrentSelection()==i)Brain.Screen.setPenColor(color(255,255,255));
    else Brain.Screen.setPenColor(menu.buttons[i].bg_color);
    Brain.Screen.setFillColor(menu.buttons[i].bg_color);
    Brain.Screen.drawRectangle(menu.buttons[i].x, menu.buttons[i].y, menu.buttons[i].width, menu.buttons[i].height);
    Brain.Screen.setFont(menu.buttons[i].font);
    Brain.Screen.setPenColor(menu.buttons[i].text_color);
    Brain.Screen.printAt(((menu.buttons[i].width/2) - ((menu.buttons[i].text.size() * fontToInt(menu.buttons[i].font))/4)) + menu.buttons[i].x - (menu.buttons[i].text.size()%2==0?0:5),
    menu.buttons[i].height/2 + fontToInt(menu.buttons[i].font)/4 + menu.buttons[i].y,
    menu.buttons[i].text.c_str());
  }

  //multi buttons
  for(int i=0; i<menu.multiButtons.size(); i++){
    if(menu.getCurrentSelection()==i)Brain.Screen.setPenColor(color(255,255,255));
    else Brain.Screen.setPenColor(menu.multiButtons[i].bg_color[menu.multiButtons[i].state]);
    Brain.Screen.setFillColor(menu.multiButtons[i].bg_color[menu.multiButtons[i].state]);
    Brain.Screen.drawRectangle(menu.multiButtons[i].x, menu.multiButtons[i].y, menu.multiButtons[i].width, menu.multiButtons[i].height);
    Brain.Screen.setFont(menu.multiButtons[i].font);
    Brain.Screen.setPenColor(menu.multiButtons[i].text_color[menu.multiButtons[i].state]);
    Brain.Screen.printAt(((menu.multiButtons[i].width/2) - ((menu.multiButtons[i].text[menu.multiButtons[i].state].size() * fontToInt(menu.multiButtons[i].font))/4)) + menu.multiButtons[i].x - (menu.multiButtons[i].text.size()%2==0?0:5),
    menu.multiButtons[i].height/2 + fontToInt(menu.multiButtons[i].font)/4 + menu.multiButtons[i].y,
    menu.multiButtons[i].text[menu.multiButtons[i].state].c_str());
  }
}

int useMenu(Menu& menu){
  if(Controller.ButtonLeft.pressing()){
    menu.setCurrentSelection(menu.getCurrentSelection()-1);
  }
  else if(Controller.ButtonRight.pressing()){
    menu.setCurrentSelection(menu.getCurrentSelection()+1);
  }
  else if(Controller.ButtonDown.pressing()){
    menu.setCurrentSelection(menu.getCurrentSelection()+menu.rowSize);
  }
  else if(Controller.ButtonUp.pressing()){
    menu.setCurrentSelection(menu.getCurrentSelection()-menu.rowSize);
  }
  else if(Controller.ButtonA.pressing()){
    return 1;
  }
  else if(Controller.ButtonB.pressing()){
    return -1;
  }
  else if(Controller.ButtonX.pressing()){
    return 2;
  }
  return 0;
}

void saveFiles(){
  Brain.Screen.clearScreen();
  Brain.Screen.setPenColor(white);
  Brain.Screen.setFillColor(black);
  Brain.Screen.setFont(mono40);
  Brain.Screen.printAt(0, 40, "Saving Config Files...");
  Brain.Screen.render();
  if(!Brain.SDcard.isInserted()){
    Brain.Screen.clearScreen();
    Brain.Screen.setFont(mono60);
    Brain.Screen.printAt(0, 40, "No SD Card!");
    Brain.Screen.render();
    while(!Brain.SDcard.isInserted())Controller.rumble("-.");
  }
  ofstream ofs;
  ofs.open("config/color.txt");
  ofs << autonSelectMenu.multiButtons[0].state;
  ofs.close();
  ofs.open("config/side.txt");
  ofs << autonSelectMenu.multiButtons[1].state;
  ofs.close();
  ofs.open("config/version.txt");
  ofs << autonSelectMenu.multiButtons[2].state;
  ofs.close();
  ofs.open("config/type.txt");
  ofs << autonSelectMenu.multiButtons[3].state;
  ofs.close();
  Brain.Screen.clearScreen();
  Brain.Screen.setFont(mono40);
  Brain.Screen.printAt(0, 40, "Config Files Saved!");
  Brain.Screen.render();
  Brain.Screen.setFont(mono20);
  wait(3, sec);
}

int main(){
  if(!Brain.SDcard.isInserted()){
    Brain.Screen.setFont(mono60);
    Brain.Screen.printAt(0, 60, "No SD Card!");
    Brain.Screen.setFont(mono20);
    while(!Brain.SDcard.isInserted())Controller.rumble("-.");
  }

  ifstream ifs;
  ifs.open("config/color.txt");
  ifs >> autonSelectMenu.multiButtons[0].state;
  ifs.close();
  ifs.open("config/side.txt");
  ifs >> autonSelectMenu.multiButtons[1].state;
  ifs.close();
  ifs.open("config/version.txt");
  ifs >> autonSelectMenu.multiButtons[2].state;
  ifs.close();
  ifs.open("config/type.txt");
  ifs >> autonSelectMenu.multiButtons[3].state;
  ifs.close();

  Menu& currentMenu = autonSelectMenu;
  currentMenu.setCurrentSelection(0);
  Brain.Screen.render();
while(true){
  int waitTime = 250;
  Brain.Screen.clearScreen();
  drawMenu(currentMenu);
  switch(useMenu(currentMenu)){
    if(currentMenu.id == 0){
      case 1:{//select button
        switch(currentMenu.getCurrentSelection()){
          case 0:{
            currentMenu.multiButtons[0].setState(currentMenu.multiButtons[0].state+1);
          }break;
          case 1:{
            currentMenu.multiButtons[1].setState(currentMenu.multiButtons[1].state+1);
          }break;
          case 2:{
            currentMenu.multiButtons[2].setState(currentMenu.multiButtons[2].state+1);
          }break;
          case 3:{
            currentMenu.multiButtons[3].setState(currentMenu.multiButtons[3].state+1);
          }break;
          case 4:{
            saveFiles();
          }break;
          default:{
            waitTime = 5;
          }break;
        }
      }break;
      case -1:{//back
      }break;
      case 2:{//save
        saveFiles();
      }break;
    }
  }
  Brain.Screen.render();
  wait(waitTime, msec);
}
return 0;}