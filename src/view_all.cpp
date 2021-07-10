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


/**
 * @file color_names_node.cpp
 */

/**
 * @mainpage view_all node for color_names
 * @image html images/color_names_sample.png
 * @author Masaya Kataoka
 * @date 2020-07-17
 */

#include <color_names/color_names.hpp>
#include <rclcpp/rclcpp.hpp>
#include <visualization_msgs/msg/marker_array.hpp>

#include <chrono>

int main(int argc, char ** argv)
{
  rclcpp::init(argc, argv);
  auto node = rclcpp::Node::make_shared("view_all");

  visualization_msgs::msg::MarkerArray mrks_msg;
  visualization_msgs::msg::Marker color_mrk;
  color_mrk.header.frame_id = "/base_link";
  color_mrk.type = visualization_msgs::msg::Marker::SPHERE_LIST;
  color_mrk.scale.x = color_mrk.scale.y = color_mrk.scale.z = 0.050;
  color_mrk.id = 0;
  int id = 1;
  int count = 0;
  for (auto && data : color_names::COLOR_NAME_DICT) {
    geometry_msgs::msg::Point p;
    p.x = 0.10 * (count % 10);
    p.y = 0.10 * (count / 10);
    count++;

    visualization_msgs::msg::Marker m_txt;
    m_txt.header.frame_id = "/base_link";
    m_txt.type = visualization_msgs::msg::Marker::TEXT_VIEW_FACING;
    m_txt.id = id;
    id++;
    m_txt.text = data.first;
    m_txt.color.r = m_txt.color.g = m_txt.color.b = m_txt.color.a = 1.0;  // white
    m_txt.scale.z = 0.010;
    m_txt.pose.position = p;
    m_txt.pose.position.z += 0.050;
    m_txt.pose.orientation.w = 1;
    mrks_msg.markers.push_back(m_txt);

    color_mrk.colors.push_back(color_names::makeColorMsg(data.first, 1.0));
    color_mrk.points.push_back(p);
  }
  mrks_msg.markers.push_back(color_mrk);

  auto mrks_pub =
    node->create_publisher<visualization_msgs::msg::MarkerArray>("color_sample_marker", 1);
  rclcpp::WallRate loop_rate(std::chrono::milliseconds{500});
  while (rclcpp::ok()) {
    mrks_pub->publish(mrks_msg);
    rclcpp::spin_some(node);
    loop_rate.sleep();
  }
  rclcpp::spin(node);
  return 0;
}
