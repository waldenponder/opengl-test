#pragma once
#include <osg/vec3>
#include "osg/Vec4"
#include "osg/Vec4f"

#include <iostream>
#include "osg/Material"
#include <algorithm>
#include "Light.h"

using namespace std;
using std::cout;
using std::endl;

#define F_B osg::Material::FRONT_AND_BACK

#define begin_name_scpae(N) namespace N {
#define end_name_space }




begin_name_scpae(Color)

const osg::Vec4  White(255, 255, 255, 255);
const osg::Vec4  Red(255, 0, 0, 255);
const osg::Vec4  Green(0, 255, 0, 255);
const osg::Vec4  Blue(0, 0, 255, 255);
const osg::Vec4  Magenta(255, 0, 255, 255);
const osg::Vec4  Cyan(0, 255, 255, 255);
const osg::Vec4  Yellow(255, 255, 0, 255);
const osg::Vec4  Black(0, 0, 0, 255);
const osg::Vec4  Aquamarine(112, 219, 147, 255);
const osg::Vec4  BakerChocolate(92, 51, 23, 255);
const osg::Vec4  BlueViolet(159, 95, 159, 255);
const osg::Vec4  Brass(181, 166, 66, 255);
const osg::Vec4  BrightGold(217, 217, 25, 255);
const osg::Vec4  Brown(166, 42, 42, 255);
const osg::Vec4  Bronze(140, 120, 83, 255);
const osg::Vec4  BronzeII(166, 125, 61, 255);
const osg::Vec4  CadetBlue(95, 159, 159, 255);
const osg::Vec4  CoolCopper(217, 135, 25, 255);
const osg::Vec4  Copper(184, 115, 51, 255);
const osg::Vec4  Coral(255, 127, 0, 255);
const osg::Vec4  CornFlowerBlue(66, 66, 111, 255);
const osg::Vec4  DarkBrown(92, 64, 51, 255);
const osg::Vec4  DarkGreen(47, 79, 47, 255);
const osg::Vec4  DarkGreenCopper(74, 118, 110, 255);
const osg::Vec4  DarkOliveGreen(79, 79, 47, 255);
const osg::Vec4  DarkOrchid(153, 50, 205, 255);
const osg::Vec4  DarkPurple(135, 31, 120, 255);
const osg::Vec4  DarkSlateBlue(107, 35, 142, 255);
const osg::Vec4  DarkSlateGrey(47, 79, 79, 255);
const osg::Vec4  DarkTan(151, 105, 79, 255);
const osg::Vec4  DarkTurquoise(112, 147, 219, 255);
const osg::Vec4  DarkWood(133, 94, 66, 255);
const osg::Vec4  DimGrey(84, 84, 84, 255);
const osg::Vec4  DustyRose(133, 99, 99, 255);
const osg::Vec4  Feldspar(209, 146, 117, 255);
const osg::Vec4  Firebrick(142, 35, 35, 255);
const osg::Vec4  ForestGreen(35, 142, 35, 255);
const osg::Vec4  Gold(205, 127, 50, 255);
const osg::Vec4  Goldenrod(219, 219, 112, 255);
const osg::Vec4  Grey(192, 192, 192, 255);
const osg::Vec4  GreenCopper(82, 127, 118, 255);
const osg::Vec4  GreenYellow(147, 219, 112, 255);
const osg::Vec4  HunterGreen(33, 94, 33, 255);
const osg::Vec4  IndianRed(78, 47, 47, 255);
const osg::Vec4  Khaki(159, 159, 95, 255);
const osg::Vec4  LightBlue(192, 217, 217, 255);
const osg::Vec4  LightGrey(168, 168, 168, 255);
const osg::Vec4  LightSteelBlue(143, 143, 189, 255);
const osg::Vec4  LightWood(233, 194, 166, 255);
const osg::Vec4  LimeGreen(50, 205, 50, 255);
const osg::Vec4  MandarianOrange(228, 120, 51, 255);
const osg::Vec4  Maroon(142, 35, 107, 255);
const osg::Vec4  MediumAquamarine(50, 205, 153, 255);
const osg::Vec4  MediumBlue(50, 50, 205, 255);
const osg::Vec4  MediumForestGreen(107, 142, 35, 255);
const osg::Vec4  MediumGoldenrod(234, 234, 174, 255);
const osg::Vec4  MediumOrchid(147, 112, 219, 255);
const osg::Vec4  MediumSeaGreen(66, 111, 66, 255);
const osg::Vec4  MediumSlateBlue(127, 0, 255, 255);
const osg::Vec4  MediumSpringGreen(127, 255, 0, 255);
const osg::Vec4  MediumTurquoise(112, 219, 219, 255);
const osg::Vec4  MediumVioletRed(219, 112, 147, 255);
const osg::Vec4  MediumWood(166, 128, 100, 255);
const osg::Vec4  MidnightBlue(47, 47, 79, 255);
const osg::Vec4  NavyBlue(35, 35, 142, 255);
const osg::Vec4  NeonBlue(77, 77, 255, 255);
const osg::Vec4  NeonPink(255, 110, 199, 255);
const osg::Vec4  NewMidnightBlue(0, 0, 156, 255);
const osg::Vec4  NewTan(235, 199, 158, 255);
const osg::Vec4  OldGold(207, 181, 59, 255);
const osg::Vec4  Orange(255, 127, 0, 255);
const osg::Vec4  OrangeRed(255, 36, 0, 255);
const osg::Vec4  Orchid(219, 112, 219, 255);
const osg::Vec4  PaleGreen(143, 188, 143, 255);
const osg::Vec4  Pink(188, 143, 143, 255);
const osg::Vec4  Plum(234, 173, 234, 255);
const osg::Vec4  Quartz(217, 217, 243, 255);
const osg::Vec4  RichBlue(89, 89, 171, 255);
const osg::Vec4  Salmon(111, 66, 66, 255);
const osg::Vec4  Scarlet(140, 23, 23, 255);
const osg::Vec4  SeaGreen(35, 142, 104, 255);
const osg::Vec4  SemiSweetChocolate(107, 66, 38, 255);
const osg::Vec4  Sienna(142, 107, 35, 255);
const osg::Vec4  Silver(230, 232, 250, 255);
const osg::Vec4  SkyBlue(50, 153, 204, 255);
const osg::Vec4  SlateBlue(0, 127, 255, 255);
const osg::Vec4  SpicyPink(255, 28, 174, 255);
const osg::Vec4  SpringGreen(0, 255, 127, 255);
const osg::Vec4  SteelBlue(35, 107, 142, 255);
const osg::Vec4  SummerSky(56, 176, 222, 255);
const osg::Vec4  Tan(219, 147, 112, 255);
const osg::Vec4  Thistle(216, 191, 216, 255);
const osg::Vec4  Turquoise(173, 234, 234, 255);
const osg::Vec4  VeryDarkBrown(92, 64, 51, 255);
const osg::Vec4  VeryLightGrey(205, 205, 205, 255);
const osg::Vec4  Violet(79, 47, 79, 255);
const osg::Vec4  VioletRed(204, 50, 153, 255);
const osg::Vec4  Wheat(216, 216, 191, 255);
const osg::Vec4  YellowGreen(153, 204, 50, 255);

end_name_space