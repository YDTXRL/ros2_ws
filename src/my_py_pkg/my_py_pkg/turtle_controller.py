#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from example_interfaces.msg import Int64  # 导入整数消息类型
from geometry_msgs.msg import Twist  # 导入速度消息类型
from turtlesim.msg import Pose  # 导入位姿消息类型

class TurtleControllerNode(Node):
    """ROS 2 基础 Python 节点类"""
    def __init__(self):
        # 初始化父类，设置节点名称
        super().__init__("turtle_controller")
        # 可在此处添加自定义初始化逻辑（如定时器、发布者、订阅者等）
        self.turtle_vel_publisher_ = self.create_publisher(Twist, "turtle1/cmd_vel", 10)
        self.turtle_pose_subscriber_ = self.create_subscription(
            Pose, "turtle1/pose", self.pose_callback, 10
        )

        self.get_logger().info("TurtleControllerNode has been started.")

    def pose_callback(self, pose: Pose):
        msg = Twist()
        if pose.x < 5.0:
            msg.linear.x = 1.0
            msg.angular.z = 1.0
        else:
            msg.linear.x = 10.0
            msg.angular.z = 5.0
        self.turtle_vel_publisher_.publish(msg)

        self.get_logger().info(f"Published velocity: {msg.linear.x}, {msg.angular.z}")

def main(args=None):
    """节点主函数"""
    # 初始化 rclpy
    rclpy.init(args=args)
    # 创建节点实例
    node = TurtleControllerNode()
    # 保持节点运行（阻塞式）
    rclpy.spin(node)
    # 关闭 rclpy，释放资源
    rclpy.shutdown()

if __name__ == "__main__":
    # 脚本直接运行时执行主函数
    main()