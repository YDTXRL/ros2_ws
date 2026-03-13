#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/int64.hpp"

class NumberPublisher : public rclcpp::Node
{
public:
    /** ROS 2 基础 C++ 节点构造函数 */
    NumberPublisher() : Node("number_publisher"), number_(2)
    {
        publisher_ = this->create_publisher<std_msgs::msg::Int64>("number", 10);
        // 创建定时器，每 1 秒发布一次数字
        number_timer_ = this->create_timer(
            std::chrono::seconds(1),
            std::bind(&NumberPublisher::publish_number, this)
        );
        RCLCPP_INFO(this->get_logger(), "Number publisher node has been started.");
    }

private:
    /** 发布者 */
    rclcpp::Publisher<std_msgs::msg::Int64>::SharedPtr publisher_;
    /** 要发布的数字 */
    int64_t number_;
    /** 定时器 */
    rclcpp::TimerBase::SharedPtr number_timer_;
    /** 发布数字 */
    void publish_number()
    {
        auto message = std_msgs::msg::Int64();
        message.data = number_;
        publisher_->publish(message);
        number_++;
        RCLCPP_INFO(this->get_logger(), "Publishing number: %ld", message.data);
    }
};

int main(int argc, char** argv)
{
    // 初始化 rclcpp
    rclcpp::init(argc, argv);
    // 创建节点智能指针实例（ROS 2 推荐使用智能指针）
    auto node = std::make_shared<NumberPublisher>();
    // 保持节点运行（阻塞式）
    rclcpp::spin(node);
    // 关闭 rclcpp，释放资源
    rclcpp::shutdown();
    return 0;
}
