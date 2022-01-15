// Copyright (c) 2020 OUXT Polaris
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <color_names/color_names.hpp>
#include <iostream>
#include <string>

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
  if (c_msg.a < 0.) {
    c_msg.a = 0.;
  }
  if (c_msg.a > 1.) {
    c_msg.a = 1.;
  }

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
