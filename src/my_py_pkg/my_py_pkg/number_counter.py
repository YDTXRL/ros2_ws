import rclpy
from rclpy.node import Node
from example_interfaces.msg import Int64  # 导入整数消息类型


class NumberCounterNode(Node):
    """ROS 2 基础 Python 节点类"""
    def __init__(self):
        # 初始化父类，设置节点名称
        super().__init__("number_counter")
        # 可在此处添加自定义初始化逻辑（如定时器、发布者、订阅者等）
        self.number_subscriber_ = self.create_subscription(Int64, "number", self.number_callback, 10)
        self.get_logger().info("Number counter has been started.")
        self.counter_ = 0

    def number_callback(self, msg):
        self.counter_ += msg.data 
        self.get_logger().info(f"Received number: {self.counter_}")

def main(args=None):
    """节点主函数"""
    # 初始化 rclpy
    rclpy.init(args=args)
    # 创建节点实例
    node = NumberCounterNode()
    # 保持节点运行（阻塞式）
    rclpy.spin(node)
    # 关闭 rclpy，释放资源
    rclpy.shutdown()

if __name__ == "__main__":
    # 脚本直接运行时执行主函数
    main()
