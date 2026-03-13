#include "rclcpp/rclcpp.hpp"
#include <chrono>
#include <functional>

// 自定义节点类，继承自rclcpp::Node
class MyCustomNode : public rclcpp::Node
{
public:
    // 构造函数：初始化节点名称和计数器，创建定时器
    MyCustomNode() : Node("my_node_name"), counter_(0)
    {
        // 创建1秒周期的定时器，绑定回调函数print_hello
        timer_ = this->create_wall_timer(
            std::chrono::seconds(1),
            std::bind(&MyCustomNode::print_hello, this)
        );
    }

private:
    // 定时器回调函数：每秒打印日志并自增计数器
    void print_hello()
    {
        RCLCPP_INFO(this->get_logger(), "Hello %d", counter_);
        counter_++;
    }

    // 成员变量：计数器和定时器指针
    int counter_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char** argv)
{
    // 初始化rclcpp
    rclcpp::init(argc, argv);
    // 创建自定义节点的智能指针实例
    auto node = std::make_shared<MyCustomNode>();
    // 阻塞式运行节点（保持节点存活）
    rclcpp::spin(node);
    // 关闭rclcpp，释放资源
    rclcpp::shutdown();
    return 0;
}
