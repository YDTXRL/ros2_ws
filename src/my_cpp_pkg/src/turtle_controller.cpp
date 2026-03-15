#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int64.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "turtlesim/msg/pose.hpp"

class TurtleControllerNode : public rclcpp::Node
{
public:
    /** ROS 2 基础 C++ 节点构造函数 */
    TurtleControllerNode() : Node("turtle_controller")
    {
        tur_vel_pub_ = this->create_publisher<geometry_msgs::msg::Twist>("turtle1/cmd_vel", 10);
        pose_vel_sub_ = this->create_subscription<turtlesim::msg::Pose>(
            "turtle1/pose", 10,
            std::bind(&TurtleControllerNode::pose_vel_callback, this, std::placeholders::_1));
        RCLCPP_INFO(this->get_logger(), "Turtle controller node has been started.");
    }

private:
    /** 发布者 */
    rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr tur_vel_pub_;
    /** 订阅者 */
    rclcpp::Subscription<turtlesim::msg::Pose>::SharedPtr pose_vel_sub_;
    /** 订阅者回调函数 */
    void pose_vel_callback(const turtlesim::msg::Pose::SharedPtr pose)
    {
        auto vel_msg = geometry_msgs::msg::Twist();
        if (pose->x<5.0){
            vel_msg.linear.x = 1.0;
            vel_msg.angular.z = 1.0;
        }
        else{
            vel_msg.linear.x = 2.0;
            vel_msg.angular.z = 2.0;
        }

        tur_vel_pub_->publish(vel_msg);
    }
};

int main(int argc, char** argv)
{
    // 初始化 rclcpp
    rclcpp::init(argc, argv);
    // 创建节点智能指针实例（ROS 2 推荐使用智能指针）
    auto node = std::make_shared<TurtleControllerNode>();
    // 保持节点运行（阻塞式）
    rclcpp::spin(node);
    // 关闭 rclcpp，释放资源
    rclcpp::shutdown();
    return 0;
}
