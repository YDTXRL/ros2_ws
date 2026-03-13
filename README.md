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
'''python'''
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






# ROS 2 常用消息包参考
## 官方消息包分类（按用途）
| 消息包名称          | 核心用途                                  | 常用消息示例                          | 适用场景                          |
|---------------------|-------------------------------------------|---------------------------------------|-----------------------------------|
| `std_msgs`          | 最基础的通用类型（数字、字符串、布尔）    | `Int64`/`Float64`/`String`/`Bool`     | 快速验证逻辑、简单数据传输        |
| `example_interfaces`| 教学示例用（语义无实际业务含义）          | `Int64`/`Float64`/`Empty`             | 学习阶段、入门练手                |
| `geometry_msgs`     | 几何相关（坐标、点、姿态、变换）          | `Point`/`Pose`/`Twist`（速度）/`Transform` | 机器人位姿、运动控制              |
| `sensor_msgs`       | 传感器数据（相机、激光、IMU、雷达）      | `Image`（图像）/`LaserScan`（激光）/`Imu`（IMU） | 传感器数据采集、处理              |
| `nav_msgs`          | 导航相关（路径、里程计、地图）            | `Odometry`（里程计）/`Path`（路径）   | 机器人导航、定位                  |
| `action_msgs`       | 动作通信基础类型                          | `GoalStatus`/`CancelGoal`             | 长时动作控制（如导航、抓取）      |
| `diagnostic_msgs`   | 设备诊断、状态监控                        | `DiagnosticStatus`/`KeyValue`         | 系统健康监控、故障排查            |

## 实用操作指令
### 1. 查找已安装的消息包
```bash
ros2 pkg list | grep msgs