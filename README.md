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

class MyCustomNode : public rclcpp::Node
{
public:
    /** ROS 2 基础 C++ 节点构造函数 */
    MyCustomNode() : Node("node_name")
    {
        // 可在此处添加自定义初始化逻辑（如定时器、发布者、订阅者等）
    }
};

int main(int argc, char** argv)
{
    // 初始化 rclcpp
    rclcpp::init(argc, argv);
    // 创建节点智能指针实例（ROS 2 推荐使用智能指针）
    auto node = std::make_shared<MyCustomNode>();
    // 保持节点运行（阻塞式）
    rclcpp::spin(node);
    // 关闭 rclcpp，释放资源
    rclcpp::shutdown();
    return 0;
}
