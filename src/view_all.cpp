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

/**
 * @file color_names_node.cpp
 */

/**
 * @mainpage view_all node for color_names
 * @image html images/color_names_sample.png
 * @author Masaya Kataoka
 * @date 2020-07-17
 */

#include <chrono>
#include <color_names/color_names.hpp>
#include <rclcpp/rclcpp.hpp>
#include <visualization_msgs/msg/marker_array.hpp>

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
