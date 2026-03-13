常用技巧：只 build 某一个包
colcon build --packages-select my_py_pkg


#git checkout -b 分支名
#git checkout 分支名


git switch -c 分支名
git switch 分支名
git branch
git branch -d 分支名
git merge 分支名

git push
git pull
git add .
git commit -m "说明"




## Python 节点模板
### 完整代码
```python
#!/usr/bin/env python3
import rclpy
from rclpy.node import Node

class MyCustomNode(Node):
    """ROS 2 基础 Python 节点类"""
    def __init__(self):
        # 初始化父类，设置节点名称
        super().__init__("node_name")
        # 可在此处添加自定义初始化逻辑（如定时器、发布者、订阅者等）

def main(args=None):
    """节点主函数"""
    # 初始化 rclpy
    rclpy.init(args=args)
    # 创建节点实例
    node = MyCustomNode()
    # 保持节点运行（阻塞式）
    rclpy.spin(node)
    # 关闭 rclpy，释放资源
    rclpy.shutdown()

if __name__ == "__main__":
    # 脚本直接运行时执行主函数
    main()


## cpp 节点模板
### 完整代码
#include "rclcpp/rclcpp.hpp"

#自定义节点类，继承自rclcpp::Node
class MyCustomNode : public rclcpp::Node
{
public:
    #构造函数：初始化节点名称和计数器，创建定时器
    MyCustomNode() : Node("my_node_name"), counter_(0)
    {
        #创建1秒周期的定时器，绑定回调函数print_hello
        timer_ = this->create_wall_timer(
            std::chrono::seconds(1),
            std::bind(&MyCustomNode::print_hello, this)
        );
    }

private:
    #定时器回调函数：每秒打印日志并自增计数器
    void print_hello()
    {
        RCLCPP_INFO(this->get_logger(), "Hello %d", counter_);
        counter_++;
    }

    #成员变量：计数器和定时器指针
    int counter_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char** argv)
{
    #初始化rclcpp
    rclcpp::init(argc, argv);
    #创建自定义节点的智能指针实例
    auto node = std::make_shared<MyCustomNode>();
    #阻塞式运行节点（保持节点存活）
    rclcpp::spin(node);
    #关闭rclcpp，释放资源
    rclcpp::shutdown();
    return 0;
}
