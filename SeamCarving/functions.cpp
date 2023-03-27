#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using namespace std;
using std::cout, std::endl, std::string;

void initializeImage(Pixel image[][MAX_HEIGHT]) {
  // iterate through columns
  for (unsigned int col = 0; col < MAX_WIDTH; col++) {
    // iterate through rows
    for (unsigned int row = 0; row < MAX_HEIGHT; row++) {
      // initialize pixel
      image[col][row] = {0, 0, 0};
    }
  }
}

void loadImage(string filename, Pixel image[][MAX_HEIGHT], unsigned int& width, unsigned int& height) {
  // TODO: implement (part 1)
  ifstream img_file(filename);

  if(!img_file.is_open()){
    throw runtime_error(string("Failed to open ") + filename);
  }

  string type;
  img_file >> type; // grap type of file
  if(toupper(type.at(0)) != 'P' || type.at(1) != '3'){
    throw runtime_error(string("Invalid type ") + type);
  }

  int w;
  int h;
  img_file >> w;
  img_file >> h; 

  if(w > ((int)(MAX_WIDTH)) || h > ((int)(MAX_HEIGHT))){
      throw runtime_error("Invalid dimensions");
  }
  if(w <= 0 || h <= 0)
  {
    throw runtime_error("Invalid dimensions");
  }
  
  width = w;
  height = h;


  int red;
  int green;
  int blue;
  string temp; // skip to debug
  img_file >> temp; 

  for(int i = 0; i < h; ++i){
    for(int j = 0; j < w; ++j){


      img_file >> image[j][i].r;
      img_file >> image[j][i].g;
      img_file >> image[j][i].b;

  
      if(img_file.fail()){
        throw runtime_error("Invalid color value");
      }

      red = image[j][i].r; // value for the r 
      if(red < 0 || red >= 256)
      {
        throw runtime_error("Invalid color value");
      }
      green = image[j][i].g; //value for g

      if(green < 0 || green >= 256)
      {
        throw runtime_error("Invalid color value");
      }
  

      blue = image[j][i].b; //value for b
      if(blue < 0 || blue >= 256)
      {
        throw runtime_error("Invalid color value");
      }
    }
  }
  if(img_file >> temp)
  {
    throw runtime_error("Too many values"); 
  }

  img_file.close();




 
}

void outputImage(string filename, Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height) {
  // TODO: implement (part 1)

  ofstream img2_file(filename); // create file 

  if(!img2_file.is_open()){
    throw runtime_error(string("Failed to open ") + filename);
  }

//header for the file
  img2_file << "P3\n" << width << " " << height << "\n" <<  256  << "\n";

  int red;
  int green;
  int blue; 
  string temp;
  img2_file << temp;
  
  for(int i = 0; i < (int)height; i++){
    for(int j = 0; j < (int)width; j++){
      red = image[j][i].r;
      green = image[j][i].g;
      blue = image[j][i].b;
      img2_file << red << " ";
      img2_file << green << " ";
      img2_file << blue << " ";
    }
    img2_file << endl;
  }
  
  img2_file.close();

}
unsigned int energy(Pixel image[][MAX_HEIGHT], unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
  // TODO: implement (part 1)
  unsigned int Move_left; 
  unsigned int Move_right;
  unsigned int up;
  unsigned int down;

  //Move_left
  if(x == width - 1)
  {
    Move_left = x + 1 - width;
  }
  else{
    Move_left  = x + 1; 
  }

  //Move_right 
  if(x == 0){
    Move_right = x - 1 + width;
  }
  else{
    Move_right = x - 1;
  }

  //up

  if(y == 0){
    up = y - 1 + height;

  }
  else{
    up = y -1;
  }

  //down 
  if(y == height - 1){
    
    down = y + 1 - height;

  }
  else{
    down = y + 1;
  }

  unsigned int R_x = image[Move_left][y].r - image[Move_right][y].r; 
  unsigned int G_x = image[Move_left][y].g - image[Move_right][y].g;
  unsigned int B_x = image[Move_left][y].b - image[Move_right][y].b;
  
  unsigned int delx = R_x * R_x + G_x * G_x + B_x * B_x;

  unsigned int R_y = image[x][up].r - image[x][down].r;
  unsigned int G_y = image[x][up].g - image[x][down].g;
  unsigned int B_y = image[x][up].b - image[x][down].b;

  unsigned int dely = R_y * R_y + G_y * G_y + B_y * B_y;

  int energy = delx + dely;

  return energy;

}

// uncomment functions as you implement them (part 2)
unsigned int loadVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int start_col, unsigned int width, unsigned int height, unsigned int seam[]) {
  // TODO: implement (part 2)


  // row should be initialized to 0 
  
  int total_energy = energy(image,start_col,0,width,height);

  seam[0] = start_col; // set to first element of the array. initialize

  for(unsigned int i = 1; i < height; i++){
   unsigned int foward,left,right; // variables required for greedy algorithm -- energy
   unsigned int temp_col = seam[i - 1];
   foward = energy(image,temp_col,i,width,height);

   if(temp_col == 0){ // first 
    left = UINT32_MAX;
   }

   else{
    left = energy(image,temp_col-1,i,width,height);
   }

   if(temp_col == width -1){ // last one
      right = UINT32_MAX;
   }
   else { // middle
     right = energy(image,temp_col+1, i, width, height);
   }



  if(foward < left){
    if(foward <= right){
      total_energy += foward;
      seam[i] = temp_col;
    }
    else{ // mvoe right
      total_energy += right; 
      seam[i] = temp_col + 1;
    }
  }
  else if(foward < right){
    if(foward <= left){
      total_energy += foward;
      seam[i] = temp_col; 
    }
    else{ // move left
      total_energy += left;
      seam[i] = temp_col - 1;
    }

  }
  else if (foward > left || foward > right) {  
      if (right <= left) {
        total_energy += right;
        seam[i] = temp_col + 1;
      }
      else {
        total_energy += left;
        seam[i] = temp_col - 1;
      }
    }
  else{
    total_energy += foward;
    seam[i] = temp_col;
  }
 }

  return total_energy;
}

// unsigned int loadHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int start_row, unsigned int width, unsigned int height, unsigned int seam[]) {
//   // TODO: implement (part 2)
//   return 0;
// }

void findMinVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height, unsigned int seam[]) {
  // TODO: implement (part 2)


  unsigned int minimal = loadVerticalSeam(image,0,width,height,seam);

  unsigned int temp_index = 0; 
  unsigned int current = -1;
  for(unsigned int i = 1; i < width; ++i)
  {
    current = loadVerticalSeam(image,i,width,height,seam);
    if(current < minimal){
      minimal = current;
      temp_index = i;
    }
  }
  loadVerticalSeam(image,temp_index,width,height,seam); 


}

// void findMinHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height, unsigned int seam[]) {
//   // TODO: implement (part 2)
// }

void removeVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int& width, unsigned int height, unsigned int verticalSeam[]) {
  // TODO: implement (part 2)

  for(unsigned int i = 0; i < height; i++)
    for(unsigned int j =  0; j < width-1; j++)
      if(j >= verticalSeam[i])
        image[j][i] = image[j + 1 ][i];

      
  width = width - 1;

}

// void removeHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int& height, unsigned int horizontalSeam[]) {
//   // TODO: implement (part 2)
// }
