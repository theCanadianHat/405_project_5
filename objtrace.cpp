/*
 *  objtest.cpp
 *
 *  Program to test OBJ File reader Code
 *  Used for Programming Project 6, CPSC 405/605
 *
 *  Donald H. House,   3/30/2011
 *
 *  usage: objtest filename.obj
 *
  Loads the OBJ file and then prints the polygonal surface data structure
  corresponding to the OBJ file and any MTL file loaded with it.

Noah Herron
CPSC 405
Due April 1st 2014

Original code written by Donald H. House, modified by Noah Herron

*/

#include <cstdlib>
#include <iostream>

#include "Vector.h"
#include "OBJFile.h"
#include "PolySurf.h"

using namespace std;

//
// Load the scene and get the centroid and bounding box
//
void load_scene(PolySurf **scene, OBJFile &objfile){

  int err = objfile.read();
  *scene = objfile.getscene();

  if(err || scene == NULL){
    char *filename = objfile.getfilename();
    cerr << "OBJ file " << filename << " has errors" << endl;
    exit(2);
  }
}

//
// Validate command line, and initialize viewport width, and output filename
//
void get_commandline(int argc, char *argv[], OBJFile &objfile,std::string& wFN, int& numRays){
  int suffix;
  
  if(argc < 2)
    goto abort;
  if(argc >= 3)
    numRays = atoi(argv[2]);
  if(argc >= 4)
    wFN = argv[3];
  suffix = strlen(argv[1]) - 4;
  if(strcmp(&(argv[1][suffix]), ".obj") != 0)
    goto abort;
  objfile.setfilename(argv[1]);
  return;

abort:
  cerr << "usage: objtrace filename.obj" << endl;
  exit(1);
}

//
// Main program to load the OBJ file and print the polygonal surface
// data structure
//
int main(int argc, char* argv[]){
  OBJFile objfile;
  PolySurf *scene;	      // polygonal surface data structure
  Vector3d centroid, bboxmin, bboxmax;  // center and bounding box
  std::string writeFilename;
  int numberOfRaysPerPixel =0;

  // check the command line first, we may abort
  get_commandline(argc, argv, objfile, writeFilename,numberOfRaysPerPixel);

  cout << "Filename and RayNums: ";
  cout << writeFilename<<" "<<numberOfRaysPerPixel<<endl;

  // load scene and print the scene
  load_scene(&scene, objfile);
  cout << *scene << endl;
 
 
  // get and print the centroid and bounding box
  centroid = scene->Centroid();
  bboxmin = scene->MinBBox();
  bboxmax = scene->MaxBBox();
  cout << "Centroid = " << centroid << ", Bounding Box: (" << bboxmin << ", " << bboxmax << ")" << endl;
}
