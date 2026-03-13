#!/usr/bin/env python3
import rclpy
from rclpy.node import Node

class MyCustomNode(Node):
    def __init__(self):
        # 调用父类构造函数，命名节点
        super().__init__('my_node_name')
        # 初始化计数器，初始值为0
        self.counter_ = 0
        # 创建定时器：1秒触发一次print_hello函数
        self.timer_ = self.create_timer(1.0, self.print_hello)

    # 定时器回调函数：每秒执行一次
    def print_hello(self):
        # 打印日志，包含当前计数器值
        self.get_logger().info("Hello " + str(self.counter_))
        # 计数器自增1
        self.counter_ += 1

def main(args=None):
    rclpy.init(args=args)          # 初始化rclpy
    node = MyCustomNode()          # 创建节点实例
    rclpy.spin(node)               # 保持节点运行（阻塞）
    rclpy.shutdown()               # 关闭rclpy

if __name__ == '__main__':
    main()
