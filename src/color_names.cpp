/*
Copyright (c) 2019 shuhei yoshida

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/


#include <color_names/color_names.hpp>
#include <string>

#include <iostream>

namespace color_names
{
/**
 * @brief generate std_msgs::msg::ColorRGBA message from hsv values
 * @param h hue
 * @param s saturation
 * @param v value
 * @param alpha alpha value of the color
 * @return std_msgs::msg::ColorRGBA
 */
std_msgs::msg::ColorRGBA fromHsv(double h, double s, double v, double alpha)
{
  std_msgs::msg::ColorRGBA color;
  color.a = alpha;
  float r = v;
  float g = v;
  float b = v;
  if (s > 0.0f) {
    h *= 6.0f;
    int i = static_cast<int>(h);
    float f = h - static_cast<float>(i);
    switch (i) {
      default:
      case 0:
        g *= 1 - s * (1 - f);
        b *= 1 - s;
        break;
      case 1:
        r *= 1 - s * f;
        b *= 1 - s;
        break;
      case 2:
        r *= 1 - s;
        b *= 1 - s * (1 - f);
        break;
      case 3:
        r *= 1 - s;
        g *= 1 - s * f;
        break;
      case 4:
        r *= 1 - s * (1 - f);
        g *= 1 - s;
        break;
      case 5:
        g *= 1 - s;
        b *= 1 - s * f;
        break;
    }
  }
  color.r = r;
  color.g = g;
  color.b = b;
  return color;
}

/**
 * @brief generate std_msgs::msg::ColorRGBA message from color name
 * @param preset_name the name of the color
 * @param alpha alpha value of the color
 * @return std_msgs::msg::ColorRGBA
 */
std_msgs::msg::ColorRGBA makeColorMsg(std::string preset_name, double alpha)
{
  std_msgs::msg::ColorRGBA c_msg;
  c_msg.a = alpha;
  if (c_msg.a < 0.) {c_msg.a = 0.;}
  if (c_msg.a > 1.) {c_msg.a = 1.;}

  auto found_itr = COLOR_NAME_DICT.find(preset_name);
  if (found_itr != COLOR_NAME_DICT.end()) {
    c_msg.r = found_itr->second[0];
    c_msg.g = found_itr->second[1];
    c_msg.b = found_itr->second[2];
  } else {
    c_msg.r = 0;
    c_msg.g = 0;
    c_msg.b = 0;
  }
  return c_msg;
}
}  // namespace color_names
